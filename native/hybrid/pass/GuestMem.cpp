// GuestMem: LLVM 18 new-PM module pass (plugin) for the hybrid native port (see ../DESIGN.md).
// Input: a decomp unit compiled by clang for powerpc-unknown-eabi at -O0 (big-endian ILP32, opaque pointers).
// Output (in place): an x86-64 module in which every pointer is a 32-bit guest address (i32) and all memory
// accesses go through the guest accessors (hm_ld32 ... from hmrt.c), plus a thunk hmt_XXXXXXXX(CPU *) per native
// function with a guest address, and a data blob for module-private constants placed in a reserved guest region.
//
// Configuration (environment, read when the pass runs):
//   GM_SYMS   files (':'-separated): lines "G name addr size" (global ELF symbols) and "L name addr size" (this unit's locals)
//   GM_ENTRIES file: hex addresses of recompiled entry points (fn_XXXXXXXX exists); others go through rt_call
//   GM_DENY   file: names / hex addresses that must stay recompiled
//   GM_DATA   hex base address of this unit's reserved data region;  GM_UNIT  identifier for the blob symbol
//   GM_META   output file: per-function status, signatures, blob placement, warnings
//   GM_NOCALL file: hex addresses that native code must not call (OSSaveContext: its call sites are setjmps)
//   GM_HOST   file: names of host helper functions callable directly (e.g. __frsqrte)
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/GetElementPtrTypeIterator.h"
#include "llvm/IR/Operator.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/Support/raw_ostream.h"
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <regex>
#include <stdexcept>

using namespace llvm;

namespace {
struct Fail : std::runtime_error { using std::runtime_error::runtime_error; };
static std::string str(const Value *v) { std::string s; raw_string_ostream os(s); v->print(os); return s.substr(0, 160); }
static std::string tstr(const Type *t) { std::string s; raw_string_ostream os(s); t->print(os); return s; }

struct Sym { uint32_t addr, size; };

// CPU struct layout (runtime/ppc.h)
static const unsigned CPU_R = 0, CPU_F = 128, CPU_CR = 640;

struct GuestMem {
  Module &M;
  LLVMContext &C;
  DataLayout DL;     // the PPC data layout (guest)
  Type *I8, *I16, *I32, *I64, *F32, *F64, *VoidT, *PtrT;
  std::map<std::string, Sym> gsyms, lsyms;
  std::map<std::string, std::vector<std::pair<uint32_t, Sym>>> lstatic;   // base name -> [(N, sym)] for "name$N"
  std::set<uint32_t> entries, denyAddr, noCall;
  std::set<std::string> denyName, hostFns, asmFns;
  bool isAsmFn(const std::string &n) {   // plain name, or the name inside an Itanium-mangled one
    if (asmFns.count(n)) return true;
    if (n.rfind("_Z", 0) != 0) return false;
    for (size_t i = 2; i < n.size();) {
      if (!isdigit((unsigned char)n[i])) { i++; continue; }
      size_t j = i; while (j < n.size() && isdigit((unsigned char)n[j])) j++;
      size_t len = std::stoul(n.substr(i, j - i));
      if (j + len <= n.size() && asmFns.count(n.substr(j, len))) return true;
      i = j + (j + len <= n.size() ? len : 0);
    }
    return false;
  }
  std::map<const GlobalValue *, uint32_t> addr;     // guest address of globals / functions
  std::set<const GlobalVariable *> badGV;           // unresolvable (mutable, not in ELF)
  std::map<const GlobalVariable *, std::string> gvNote;
  std::vector<uint8_t> blob;
  uint32_t dataBase = 0x81800000;
  std::string unit = "u", metaPath;
  std::ostringstream meta;
  std::map<Function *, Function *> NF;
  std::map<const Function *, std::pair<uint32_t, int>> dtor;   // Itanium D0/D1/D2 -> MWCC __dt__ (this, short dealloc)              // old -> new native function
  std::map<Function *, std::string> failReason;
  GlobalVariable *gCPU = nullptr, *gIrq = nullptr;
  std::map<const GlobalValue *, std::string> oname;   // original (pre-rename) names
  std::string on(const GlobalValue *g) { auto it = oname.find(g); return it != oname.end() ? it->second : g->getName().str(); }

  GuestMem(Module &M) : M(M), C(M.getContext()), DL(M.getDataLayout()) {
    I8 = Type::getInt8Ty(C); I16 = Type::getInt16Ty(C); I32 = Type::getInt32Ty(C); I64 = Type::getInt64Ty(C);
    F32 = Type::getFloatTy(C); F64 = Type::getDoubleTy(C); VoidT = Type::getVoidTy(C); PtrT = PointerType::get(C, 0);
  }

  // ---------------- configuration
  static std::string env(const char *n) { const char *v = getenv(n); return v ? v : ""; }
  void loadConfig() {
    std::stringstream files(env("GM_SYMS")); std::string f;
    while (std::getline(files, f, ':')) {
      std::ifstream in(f); std::string k, n; uint32_t a, s;
      while (in >> k >> n >> std::hex >> a >> s >> std::dec) {
        Sym sy{a, s};
        if (k == "G") { if (!gsyms.count(n)) gsyms[n] = sy; }
        else {
          lsyms[n] = sy;
          auto d = n.rfind('$');
          if (d != std::string::npos && d + 1 < n.size() && isdigit((unsigned char)n[d + 1]))
            lstatic[n.substr(0, d)].push_back({(uint32_t)atoi(n.c_str() + d + 1), sy});
        }
      }
      for (auto &kv : lstatic) std::sort(kv.second.begin(), kv.second.end(), [](auto &x, auto &y) { return x.first < y.first; });
    }
    if (auto f = env("GM_ENTRIES"); !f.empty()) { std::ifstream in(f); uint32_t a; while (in >> std::hex >> a) entries.insert(a); }
    if (auto f = env("GM_DENY"); !f.empty()) {
      std::ifstream in(f); std::string w;
      while (in >> w) {
        if (w[0] == '#') { std::getline(in, w); continue; }
        if (std::regex_match(w, std::regex("(0x)?[0-9A-Fa-f]{8}"))) denyAddr.insert((uint32_t)std::stoul(w, nullptr, 16));
        else denyName.insert(w);
      }
    }
    if (auto f = env("GM_NOCALL"); !f.empty()) { std::ifstream in(f); uint32_t a; while (in >> std::hex >> a) noCall.insert(a); }
    if (auto f = env("GM_ASMFN"); !f.empty()) { std::ifstream in(f); std::string w; while (in >> w) asmFns.insert(w); }
    if (auto f = env("GM_HOST"); !f.empty()) { std::ifstream in(f); std::string w; while (in >> w) hostFns.insert(w); }
    if (auto v = env("GM_DATA"); !v.empty()) dataBase = (uint32_t)std::stoul(v, nullptr, 16);
    if (auto v = env("GM_UNIT"); !v.empty()) unit = v;
    metaPath = env("GM_META");
  }

  // ---------------- symbol resolution
  // clang names of statics -> MWCC ELF names
  bool lookupLocalStatic(const std::string &n, std::map<std::string, int> &seen, Sym &out) {
    std::smatch m;
    std::string base;
    static const std::regex zl("_ZL(\\d+)(.*)");
    static const std::regex zz("_ZZ.*E(\\d+)([A-Za-z_][A-Za-z0-9_]*?)(_\\d+)?");
    static const std::regex cs("[A-Za-z_][A-Za-z0-9_]*\\.([A-Za-z_][A-Za-z0-9_]*)(\\.\\d+)?");
    if (std::regex_match(n, m, zl)) {
      size_t len = std::stoul(m[1]); std::string rest = m[2];
      if (rest.size() >= len) { std::string b = rest.substr(0, len); if (lsyms.count(b)) { out = lsyms[b]; return true; } base = b; }
    } else if (std::regex_match(n, m, zz)) base = m[2];
    else if (std::regex_match(n, m, cs)) base = m[1];
    if (base.empty()) return false;
    auto it = lstatic.find(base);
    if (it == lstatic.end()) return false;
    int k = seen[base]++;
    if (k >= (int)it->second.size()) return false;
    out = it->second[k].second;
    return true;
  }

  bool symFor(const std::string &n, bool local, Sym &s) {
    if (local) { auto it = lsyms.find(n); if (it != lsyms.end()) { s = it->second; return true; } }
    auto it = gsyms.find(n); if (it != gsyms.end()) { s = it->second; return true; }
    if (!local) { auto it2 = lsyms.find(n); if (it2 != lsyms.end()) { s = it2->second; return true; } }
    return false;
  }

  // Itanium-mangled C++ names (as clang emits them) -> MWCC-mangled ELF names, for the common simple cases.
  std::string mwParams(const std::string &it) {
    static const std::map<char, std::string> b = {{'v', "v"}, {'i', "i"}, {'j', "Ui"}, {'c', "c"}, {'a', "Sc"}, {'h', "Uc"},
        {'s', "s"}, {'t', "Us"}, {'l', "l"}, {'m', "Ul"}, {'f', "f"}, {'d', "d"}, {'b', "b"}, {'x', "x"}, {'y', "Ux"}};
    std::string o;
    for (size_t i = 0; i < it.size();) {
      char ch = it[i];
      if (ch == 'P') { o += 'P'; i++; }
      else if (ch == 'R') { o += 'R'; i++; }
      else if (ch == 'K') { o += 'C'; i++; }
      else if (isdigit((unsigned char)ch)) { size_t j = i; while (j < it.size() && isdigit((unsigned char)it[j])) j++; size_t n = std::stoul(it.substr(i, j - i)); o += it.substr(i, j - i + n); i = j + n; }
      else if (b.count(ch)) { o += b.at(ch); i++; }
      else return "";
    }
    return o;
  }
  bool symForItanium(const std::string &n, Sym &s) {
    static const std::map<std::string, std::string> ops = {{"_Znwm", "__nw__FUl"}, {"_Znwj", "__nw__FUl"}, {"_Znam", "__nwa__FUl"},
        {"_Znaj", "__nwa__FUl"}, {"_ZdlPv", "__dl__FPv"}, {"_ZdaPv", "__dla__FPv"}};
    auto oi = ops.find(n);
    if (oi != ops.end()) return symFor(oi->second, false, s);
    std::smatch m;
    static const std::regex ctor("_ZN(\\d+)(\\w+?)C[12]E(.*)");
    static const std::regex meth("_ZN(K?)(\\d+)(\\w+?)(\\d+)(\\w+?)E(.*)");
    static const std::regex fn("_Z(\\d+)(\\w+)");
    std::string prefix, params;
    if (std::regex_match(n, m, ctor) && std::stoul(m[1]) == m[2].length()) { prefix = "__ct__" + m[1].str() + m[2].str() + "F"; params = m[3]; }
    else if (std::regex_match(n, m, meth) && std::stoul(m[2]) == m[3].length() && std::stoul(m[4]) == m[5].length()) {
      prefix = m[5].str() + "__" + m[2].str() + m[3].str() + (m[1].length() ? "CF" : "F"); params = m[6];
    } else if (std::regex_match(n, m, fn)) {
      size_t len = std::stoul(m[1]); std::string rest = m[2];
      if (rest.size() < len) return false;
      prefix = rest.substr(0, len) + "__F"; params = rest.substr(len);
    } else return false;
    std::string mp = mwParams(params);
    if (!mp.empty() && symFor(prefix + mp, false, s)) return true;
    if (!mp.empty() && lsyms.count(prefix + mp)) { s = lsyms[prefix + mp]; return true; }
    // unique overload with that prefix
    int cnt = 0; Sym one{};
    for (auto *tab : {&lsyms, &gsyms})
      for (auto it = tab->lower_bound(prefix); it != tab->end() && it->first.compare(0, prefix.size(), prefix) == 0; ++it) { cnt++; one = it->second; }
    if (cnt == 1) { s = one; return true; }
    return false;
  }

  void resolveGlobals() {
    std::map<std::string, int> seen;
    uint32_t cur = dataBase;
    std::vector<GlobalVariable *> place;
    for (GlobalVariable &G : M.globals()) {
      std::string n = G.getName().str();
      Sym s;
      bool local = G.hasLocalLinkage();
      uint64_t sz = G.getValueType()->isSized() ? DL.getTypeAllocSize(G.getValueType()) : 0;
      if (n.rfind("llvm.", 0) == 0) continue;
      if (symFor(n, local, s) || (local && lookupLocalStatic(n, seen, s))) {
        addr[&G] = s.addr;
        if (!G.isDeclaration() && s.size && sz && s.size != sz && !(G.getValueType()->isArrayTy() && sz < s.size)) {
          meta << "warn size " << n << " ir=" << sz << " elf=" << s.size << "\n";
          if (local) { badGV.insert(&G); gvNote[&G] = "size mismatch with ELF symbol"; }
        }
        continue;
      }
      if (G.isDeclaration()) { badGV.insert(&G); gvNote[&G] = "unresolved extern"; continue; }
      if (!G.isConstant() && !(G.hasGlobalUnnamedAddr() && G.getName().starts_with(".str"))) {
        // mutable data the recompiled code could not see (or a header tentative definition of data that lives
        // elsewhere): functions using it stay recompiled.
        meta << "warn private-mutable " << n << " size " << sz << "\n";
        badGV.insert(&G); gvNote[&G] = "private mutable data";
        continue;
      }
      place.push_back(&G);
    }
    for (GlobalVariable *G : place) {
      uint64_t sz = DL.getTypeAllocSize(G->getValueType());
      uint64_t al = std::max<uint64_t>(4, DL.getPreferredAlign(G).value());
      cur = (cur + al - 1) & ~(uint32_t)(al - 1);
      addr[G] = cur;
      meta << "data " << G->getName().str() << " " << std::hex << cur << std::dec << " " << sz << "\n";
      cur += sz ? sz : 1;
    }
    cur = (cur + 7) & ~7u;
    blob.assign(cur - dataBase, 0);
    for (GlobalVariable *G : place) {
      if (!G->hasInitializer()) continue;
      try { serialize(G->getInitializer(), addr[G] - dataBase); }
      catch (Fail &e) { badGV.insert(G); gvNote[G] = std::string("initializer: ") + e.what(); }
    }
    for (Function &F : M) {
      Sym s;
      if (F.isIntrinsic()) continue;
      if (symFor(F.getName().str(), F.hasLocalLinkage(), s) || symForItanium(F.getName().str(), s)) addr[&F] = s.addr;
      else {
        std::smatch m; std::string n = F.getName().str();
        static const std::regex dt("_ZN(\\d+)(\\w+?)D([012])Ev");
        if (std::regex_match(n, m, dt) && std::stoul(m[1]) == m[2].length()) {
          Sym d; if (symFor("__dt__" + m[1].str() + m[2].str() + "Fv", false, d) || symFor("__dt__" + m[1].str() + m[2].str() + "Fv", true, d))
            dtor[&F] = {d.addr, m[3] == "0" ? 1 : 0};
        }
      }
    }
    for (GlobalAlias &A : M.aliases()) {
      const GlobalValue *t = dyn_cast<GlobalValue>(A.getAliasee()->stripPointerCasts());
      Sym s;
      if (symFor(A.getName().str(), A.hasLocalLinkage(), s) || symForItanium(A.getName().str(), s)) addr[&A] = s.addr;
      else if (t && addr.count(t)) addr[&A] = addr[t];
    }
  }

  // ---------------- constants
  uint64_t evalInt(const Constant *c) {   // integer-or-pointer constant -> value (guest addresses for pointers)
    if (auto *ci = dyn_cast<ConstantInt>(c)) return ci->getZExtValue();
    if (isa<ConstantPointerNull>(c) || isa<UndefValue>(c) || isa<ConstantAggregateZero>(c)) return 0;
    if (auto *ga = dyn_cast<GlobalAlias>(c)) {
      if (addr.count(ga)) return addr[ga];
      return evalInt(cast<Constant>(ga->getAliasee()));
    }
    if (auto *gv = dyn_cast<GlobalVariable>(c)) {
      if (badGV.count(gv)) throw Fail("global " + gv->getName().str() + " (" + gvNote[gv] + ")");
      auto it = addr.find(gv); if (it == addr.end()) throw Fail("no address for " + gv->getName().str());
      return it->second;
    }
    if (auto *f = dyn_cast<Function>(c)) {
      auto it = addr.find(f); if (it == addr.end()) throw Fail("address of non-guest function " + f->getName().str());
      return it->second;
    }
    if (auto *ce = dyn_cast<ConstantExpr>(c)) {
      unsigned w = ce->getType()->isPointerTy() ? 32 : ce->getType()->getIntegerBitWidth();
      uint64_t mask = w >= 64 ? ~0ull : ((1ull << w) - 1);
      switch (ce->getOpcode()) {
      case Instruction::GetElementPtr: {
        auto *g = cast<GEPOperator>(ce);
        APInt off(32, 0);
        if (!g->accumulateConstantOffset(DL, off)) throw Fail("non-constant gep constexpr");
        return (evalInt(cast<Constant>(g->getPointerOperand())) + off.getZExtValue()) & 0xFFFFFFFFu;
      }
      case Instruction::PtrToInt: case Instruction::IntToPtr: case Instruction::BitCast:
      case Instruction::Trunc: case Instruction::ZExt:
        return evalInt(ce->getOperand(0)) & mask;
      case Instruction::SExt: {
        unsigned sw = ce->getOperand(0)->getType()->getIntegerBitWidth();
        int64_t v = (int64_t)(evalInt(ce->getOperand(0)) << (64 - sw)) >> (64 - sw);
        return (uint64_t)v & mask;
      }
      case Instruction::Add: return (evalInt(ce->getOperand(0)) + evalInt(ce->getOperand(1))) & mask;
      case Instruction::Sub: return (evalInt(ce->getOperand(0)) - evalInt(ce->getOperand(1))) & mask;
      case Instruction::Mul: return (evalInt(ce->getOperand(0)) * evalInt(ce->getOperand(1))) & mask;
      case Instruction::Xor: return (evalInt(ce->getOperand(0)) ^ evalInt(ce->getOperand(1))) & mask;
      case Instruction::Shl: return (evalInt(ce->getOperand(0)) << evalInt(ce->getOperand(1))) & mask;
      default: break;
      }
    }
    throw Fail("constant " + str(c));
  }

  void put(uint64_t off, uint64_t v, unsigned n) { for (unsigned i = 0; i < n; i++) blob[off + i] = (uint8_t)(v >> (8 * (n - 1 - i))); }

  void serialize(const Constant *c, uint64_t off) {
    Type *t = c->getType();
    if (isa<ConstantAggregateZero>(c) || isa<UndefValue>(c) || isa<ConstantPointerNull>(c)) return;
    if (auto *fp = dyn_cast<ConstantFP>(c)) {
      APInt b = fp->getValueAPF().bitcastToAPInt();
      put(off, b.getZExtValue(), t->isFloatTy() ? 4 : 8);
      if (!t->isFloatTy() && !t->isDoubleTy()) throw Fail("fp type");
      return;
    }
    if (t->isIntegerTy() || t->isPointerTy()) {
      unsigned n = t->isPointerTy() ? 4 : (unsigned)DL.getTypeStoreSize(t);
      if (n > 8) throw Fail("wide int");
      put(off, evalInt(c), n);
      return;
    }
    if (auto *cds = dyn_cast<ConstantDataSequential>(c)) {
      uint64_t es = DL.getTypeAllocSize(cds->getElementType());
      for (unsigned i = 0; i < cds->getNumElements(); i++) serialize(cds->getElementAsConstant(i), off + i * es);
      return;
    }
    if (auto *ca = dyn_cast<ConstantArray>(c)) {
      uint64_t es = DL.getTypeAllocSize(ca->getType()->getElementType());
      for (unsigned i = 0; i < ca->getNumOperands(); i++) serialize(ca->getOperand(i), off + i * es);
      return;
    }
    if (auto *cs = dyn_cast<ConstantStruct>(c)) {
      const StructLayout *sl = DL.getStructLayout(cs->getType());
      for (unsigned i = 0; i < cs->getNumOperands(); i++) serialize(cs->getOperand(i), off + sl->getElementOffset(i));
      return;
    }
    throw Fail("initializer " + str(c));
  }

  // ---------------- types
  Type *mapTy(Type *t) {
    if (t->isPointerTy()) return I32;
    if (t->isIntegerTy() || t->isFloatTy() || t->isDoubleTy() || t->isVoidTy()) return t;
    if (auto *st = dyn_cast<StructType>(t)) {
      for (Type *e : st->elements()) if (e->isPointerTy() || e->isAggregateType()) throw Fail("aggregate " + tstr(t));
      return t;
    }
    throw Fail("type " + tstr(t));
  }
  bool scalarMem(Type *t) {
    return t->isPointerTy() || t->isFloatTy() || t->isDoubleTy() ||
           (t->isIntegerTy() && (t->getIntegerBitWidth() == 8 || t->getIntegerBitWidth() == 16 ||
                                 t->getIntegerBitWidth() == 32 || t->getIntegerBitWidth() == 64));
  }

  FunctionType *nativeType(Function *F) {
    std::vector<Type *> ps;
    for (Argument &a : F->args()) {
      Type *t = mapTy(a.getType());
      if (t->isAggregateType()) throw Fail("aggregate param");
      ps.push_back(t);
    }
    Type *r = mapTy(F->getReturnType());
    if (r->isAggregateType()) throw Fail("aggregate return");
    return FunctionType::get(r, ps, false);
  }

  // ---------------- runtime declarations
  FunctionCallee rtFn(const char *name, Type *ret, std::vector<Type *> ps) {
    return M.getOrInsertFunction(name, FunctionType::get(ret, ps, false));
  }
  Value *cpuPtr(IRBuilder<> &B, unsigned off) { return B.CreateConstGEP1_32(I8, gCPU, off); }
  Value *cpuPtr(IRBuilder<> &B, Value *c, unsigned off) { return B.CreateConstGEP1_32(I8, c, off); }

  Value *gload(IRBuilder<> &B, Type *t, Value *a, bool vol) {
    const char *v = vol ? "v" : "";
    std::string pre = std::string("hm_ld") + v;
    if (t->isPointerTy() || t->isIntegerTy(32)) return B.CreateCall(rtFn((pre + "32").c_str(), I32, {I32}), {a});
    if (t->isIntegerTy(8)) return B.CreateCall(rtFn((pre + "8").c_str(), I8, {I32}), {a});
    if (t->isIntegerTy(16)) return B.CreateCall(rtFn((pre + "16").c_str(), I16, {I32}), {a});
    if (t->isIntegerTy(64)) return B.CreateCall(rtFn((pre + "64").c_str(), I64, {I32}), {a});
    if (t->isFloatTy()) return B.CreateBitCast(B.CreateCall(rtFn((pre + "32").c_str(), I32, {I32}), {a}), F32);
    if (t->isDoubleTy()) return B.CreateBitCast(B.CreateCall(rtFn((pre + "64").c_str(), I64, {I32}), {a}), F64);
    throw Fail("load type " + tstr(t));
  }
  void gstore(IRBuilder<> &B, Value *v, Value *a, bool vol) {
    Type *t = v->getType();
    std::string pre = std::string("hm_st") + (vol ? "v" : "");
    if (t->isFloatTy()) { v = B.CreateBitCast(v, I32); t = I32; }
    if (t->isDoubleTy()) { v = B.CreateBitCast(v, I64); t = I64; }
    if (!t->isIntegerTy()) throw Fail("store type " + tstr(t));
    unsigned w = t->getIntegerBitWidth();
    if (w != 8 && w != 16 && w != 32 && w != 64) throw Fail("store width");
    B.CreateCall(rtFn((pre + std::to_string(w)).c_str(), VoidT, {I32, t}), {a, v});
  }

  // ---------------- per-function translation
  struct FnState {
    Function *F, *N;
    std::map<const Value *, Value *> VM;
    std::map<const BasicBlock *, BasicBlock *> BM;
    std::map<const AllocaInst *, uint32_t> slot;          // guest-stack allocas: offset from locals base
    std::set<const AllocaInst *> hostA;
    std::map<const CallBase *, std::vector<uint32_t>> byvalSlot;
    uint32_t outArea = 0, localsSize = 0, maxAlign = 8, frame = 0;
    Value *sp0 = nullptr, *sp = nullptr, *locals = nullptr;
    std::vector<std::pair<PHINode *, PHINode *>> phis;
    std::set<std::pair<const BasicBlock *, const BasicBlock *>> backEdges;
  };

  // PowerPC EABI argument assignment for a call / function type (as clang lowered it)
  struct ArgLoc { int kind; int reg; uint32_t stk; };  // kind: 0 gpr, 1 gpr pair (i64), 2 fpr, 3 stack word, 4 stack dword
  std::vector<Type *> argTypes(CallBase *CB) { std::vector<Type *> v; for (auto &a : CB->args()) v.push_back(a->getType()); return v; }
  std::vector<ArgLoc> assign(FunctionType *FT, uint32_t &stackBytes) { std::vector<Type *> v(FT->param_begin(), FT->param_end()); return assign(v, stackBytes); }
  std::vector<ArgLoc> assign(const std::vector<Type *> &tys, uint32_t &stackBytes) {
    std::vector<ArgLoc> out;
    int g = 3, f = 1; uint32_t st = 0;
    for (Type *t : tys) {
      if (t->isFloatTy() || t->isDoubleTy()) {
        if (f > 8) throw Fail("float arg on stack");
        out.push_back({2, f++, 0});
      } else if (t->isIntegerTy(64)) {
        if (g % 2 == 0) g++;
        if (g <= 9) { out.push_back({1, g, 0}); g += 2; }
        else { g = 11; st = (st + 7) & ~7u; out.push_back({4, 0, st}); st += 8; }
      } else if (t->isPointerTy() || (t->isIntegerTy() && t->getIntegerBitWidth() <= 32)) {
        if (g <= 10) out.push_back({0, g++, 0});
        else { out.push_back({3, 0, st}); st += 4; }
      } else throw Fail("arg type " + tstr(t));
    }
    stackBytes = st;
    return out;
  }

  void analyze(FnState &S) {
    Function *F = S.F;
    uint32_t off = 0;
    auto alloc = [&](uint64_t size, uint64_t al) {
      al = std::max<uint64_t>(al, 4);
      if (al > S.maxAlign) S.maxAlign = (uint32_t)al;
      off = (off + al - 1) & ~(uint32_t)(al - 1);
      uint32_t r = off; off += (uint32_t)size; return r;
    };
    for (BasicBlock &BB : *F)
      for (Instruction &I : BB) {
        if (auto *AI = dyn_cast<AllocaInst>(&I)) {
          if (!AI->isStaticAlloca()) throw Fail("dynamic alloca");
          Type *t = AI->getAllocatedType();
          bool host = scalarMem(t) && cast<ConstantInt>(AI->getArraySize())->isOne();
          for (const User *U : AI->users()) {
            if (!host) break;
            if (auto *L = dyn_cast<LoadInst>(U)) { if (L->getType() != t) host = false; }
            else if (auto *St = dyn_cast<StoreInst>(U)) { if (St->getValueOperand() == AI || St->getValueOperand()->getType() != t) host = false; }
            else host = false;
          }
          if (host) S.hostA.insert(AI);
          else {
            uint64_t sz = DL.getTypeAllocSize(t) * cast<ConstantInt>(AI->getArraySize())->getZExtValue();
            S.slot[AI] = alloc(sz ? sz : 1, AI->getAlign().value());
          }
        } else if (auto *CB = dyn_cast<CallBase>(&I)) {
          if (isa<IntrinsicInst>(CB)) continue;
          uint32_t sb = 0;
          assign(argTypes(CB), sb);
          S.outArea = std::max(S.outArea, sb);
          for (unsigned i = 0; i < CB->arg_size(); i++)
            if (Type *bt = CB->getAttributes().getParamByValType(i)) S.byvalSlot[CB].push_back(alloc(DL.getTypeAllocSize(bt), std::max<uint64_t>(4, CB->getParamAlign(i).valueOrOne().value())));
            else S.byvalSlot[CB].push_back(0);
        }
      }
    S.localsSize = off;
    S.outArea = (S.outArea + 7) & ~7u;
    if (S.localsSize || S.outArea) {
      uint32_t pad = S.maxAlign > 8 ? S.maxAlign - 8 : 0;
      S.frame = (8 + S.outArea + S.localsSize + pad + 7) & ~7u;
    }
    // back edges (DFS)
    std::set<const BasicBlock *> onStack, done;
    std::vector<std::pair<const BasicBlock *, unsigned>> st;
    const BasicBlock *E = &F->getEntryBlock();
    st.push_back({E, 0}); onStack.insert(E);
    while (!st.empty()) {
      const BasicBlock *bb = st.back().first;
      unsigned k = st.back().second;
      const Instruction *T = bb->getTerminator();
      if (k >= T->getNumSuccessors()) { onStack.erase(bb); done.insert(bb); st.pop_back(); continue; }
      st.back().second++;
      const BasicBlock *s = T->getSuccessor(k);
      if (onStack.count(s)) S.backEdges.insert(std::make_pair(bb, s));
      else if (!done.count(s)) { onStack.insert(s); st.push_back({s, 0}); }
    }
  }

  Value *val(FnState &S, IRBuilder<> &B, Value *v) {
    if (auto *c = dyn_cast<Constant>(v)) {
      if (isa<GlobalValue>(c) || isa<ConstantExpr>(c) || isa<ConstantPointerNull>(c) || c->getType()->isPointerTy())
        return ConstantInt::get(mapTy(c->getType()), evalInt(c));
      if (isa<UndefValue>(c)) return Constant::getNullValue(mapTy(c->getType()));
      if (isa<ConstantInt>(c) || isa<ConstantFP>(c) || isa<ConstantAggregateZero>(c)) return c;
      throw Fail("operand constant " + str(c));
    }
    auto it = S.VM.find(v);
    if (it == S.VM.end()) throw Fail("unmapped value " + str(v));
    return it->second;
  }

  Value *fitInt(IRBuilder<> &B, Value *v, Type *t, bool sext = false) {
    unsigned a = v->getType()->getIntegerBitWidth(), b = t->getIntegerBitWidth();
    if (a == b) return v;
    if (a > b) return B.CreateTrunc(v, t);
    return sext ? B.CreateSExt(v, t) : B.CreateZExt(v, t);
  }

  Value *addrOf(FnState &S, IRBuilder<> &B, Value *p) { return val(S, B, p); }

  // Marshal a call to guest code (recompiled fn_X, or rt_call for indirect / unknown entries).
  Value *guestCall(FnState &S, IRBuilder<> &B, CallBase *CB, std::vector<Value *> args, bool direct, uint32_t target, Value *dyn) {
    FunctionType *FT = CB->getFunctionType();
    uint32_t sb = 0;
    std::vector<Type *> tys; for (Value *v : args) tys.push_back(v->getType());
    auto locs = assign(tys, sb);
    bool anyFP = false;
    for (unsigned i = 0; i < args.size(); i++) {
      Value *v = args[i];
      const ArgLoc &L = locs[i];
      if (L.kind == 2) {
        anyFP = true;
        if (v->getType()->isFloatTy()) v = B.CreateFPExt(v, F64);
        B.CreateStore(v, cpuPtr(B, CPU_F + 8 * L.reg));
      } else if (L.kind == 1 || L.kind == 4) {
        Value *hi = B.CreateTrunc(B.CreateLShr(v, 32), I32), *lo = B.CreateTrunc(v, I32);
        if (L.kind == 1) { B.CreateStore(hi, cpuPtr(B, CPU_R + 4 * L.reg)); B.CreateStore(lo, cpuPtr(B, CPU_R + 4 * (L.reg + 1))); }
        else { Value *a = B.CreateAdd(S.sp, B.getInt32(8 + L.stk)); gstore(B, hi, a, false); gstore(B, lo, B.CreateAdd(a, B.getInt32(4)), false); }
      } else {
        bool sx = i < CB->arg_size() && CB->getAttributes().hasParamAttr(i, Attribute::SExt);
        if (v->getType()->getIntegerBitWidth() < 32) v = sx ? B.CreateSExt(v, I32) : B.CreateZExt(v, I32);
        if (L.kind == 0) B.CreateStore(v, cpuPtr(B, CPU_R + 4 * L.reg));
        else gstore(B, v, B.CreateAdd(S.sp, B.getInt32(8 + L.stk)), false);
      }
    }
    if (FT->isVarArg()) {   // CR bit 6 (cr1 EQ): set when FP args are passed in registers
      Value *p = cpuPtr(B, CPU_CR + 1);
      Value *cr = B.CreateAnd(B.CreateLoad(I8, p), B.getInt8(~2));
      if (anyFP) cr = B.CreateOr(cr, B.getInt8(2));
      B.CreateStore(cr, p);
    }
    if (dyn) B.CreateCall(rtFn("rt_call", VoidT, {PtrT, I32}), {gCPU, dyn});
    else if (direct) {
      char nm[32]; snprintf(nm, sizeof nm, "fn_%08X", target);
      B.CreateCall(rtFn(nm, VoidT, {PtrT}), {gCPU});
    } else B.CreateCall(rtFn("rt_call", VoidT, {PtrT, I32}), {gCPU, B.getInt32(target)});
    Type *rt = FT->getReturnType();
    if (rt->isVoidTy()) return nullptr;
    if (rt->isFloatTy()) return B.CreateFPTrunc(B.CreateLoad(F64, cpuPtr(B, CPU_F + 8)), F32);
    if (rt->isDoubleTy()) return B.CreateLoad(F64, cpuPtr(B, CPU_F + 8));
    if (rt->isIntegerTy(64)) {
      Value *hi = B.CreateZExt(B.CreateLoad(I32, cpuPtr(B, CPU_R + 12)), I64), *lo = B.CreateZExt(B.CreateLoad(I32, cpuPtr(B, CPU_R + 16)), I64);
      return B.CreateOr(B.CreateShl(hi, 32), lo);
    }
    if (rt->isPointerTy() || rt->isIntegerTy()) {
      Value *r = B.CreateLoad(I32, cpuPtr(B, CPU_R + 12));
      return fitInt(B, r, mapTy(rt));
    }
    throw Fail("return type " + tstr(rt));
  }

  void checkpoint(IRBuilder<> &B) { B.CreateCall(rtFn("hm_chk", VoidT, {})); }

  void translateCall(FnState &S, IRBuilder<> &B, CallBase *CB) {
    if (!isa<CallInst>(CB)) throw Fail("invoke/callbr");
    if (CB->isInlineAsm()) throw Fail("inline asm");
    Function *callee = CB->getCalledFunction();
    Value *cv = CB->getCalledOperand()->stripPointerCasts();
    if (!callee) callee = dyn_cast<Function>(cv);
    if (auto *ga = dyn_cast<GlobalAlias>(cv)) callee = dyn_cast<Function>(ga->getAliasee()->stripPointerCasts());
    if (callee && callee->isIntrinsic()) { translateIntrinsic(S, B, CB, callee); return; }
    std::vector<Value *> args;
    for (unsigned i = 0; i < CB->arg_size(); i++) {
      Value *v = val(S, B, CB->getArgOperand(i));
      if (Type *bt = CB->getAttributes().getParamByValType(i)) {   // caller-made copy, passed by pointer (PPC32 SVR4)
        Value *dst = B.CreateAdd(S.locals, B.getInt32(S.byvalSlot[CB][i]));
        B.CreateCall(rtFn("hm_memmove", VoidT, {I32, I32, I32}), {dst, v, B.getInt32((uint32_t)DL.getTypeAllocSize(bt))});
        v = dst;
      }
      args.push_back(v);
    }
    Value *res = nullptr;
    bool done = false;
    if (callee) {
      auto nit = NF.find(callee);
      if (nit != NF.end() && callee->getFunctionType() == CB->getFunctionType()) {
        std::vector<Value *> a2;
        FunctionType *NT = nit->second->getFunctionType();
        for (unsigned i = 0; i < args.size(); i++) {
          Value *v = args[i];
          if (v->getType() != NT->getParamType(i)) throw Fail("native call arg type");
          a2.push_back(v);
        }
        res = B.CreateCall(nit->second, a2);
        done = true;
      } else if (hostFns.count(on(callee)) && !addr.count(callee)) {
        std::vector<Type *> pts; for (Value *v : args) pts.push_back(v->getType());
        FunctionCallee h = M.getOrInsertFunction("hmh_" + on(callee), FunctionType::get(mapTy(CB->getType()), pts, false));
        (void)h;
        res = B.CreateCall(h, args);
        done = true;
      } else {
        auto ait = addr.find(callee);
        if (ait == addr.end() && dtor.count(callee)) {   // MWCC destructor: extra `short dealloc` argument
          auto [da, fl] = dtor[callee];
          args.push_back(B.getInt32(fl));
          res = guestCall(S, B, CB, args, entries.count(da) > 0, da, nullptr);
          if (!CB->getType()->isVoidTy()) S.VM[CB] = res;
          return;
        }
        if (ait != addr.end() && noCall.count(ait->second)) throw Fail("calls " + on(callee) + " (must stay recompiled: setjmp call site)");
        if (ait == addr.end()) throw Fail("call to unknown function " + on(callee) +
                                          (failReason.count(callee) ? " (failed: " + failReason[callee] + ")" : ""));
        res = guestCall(S, B, CB, args, entries.count(ait->second) > 0, ait->second, nullptr);
        done = true;
      }
    }
    if (!done) {
      Value *t = val(S, B, CB->getCalledOperand());
      res = guestCall(S, B, CB, args, false, 0, t);
    }
    if (!CB->getType()->isVoidTy()) S.VM[CB] = res;
  }

  void translateIntrinsic(FnState &S, IRBuilder<> &B, CallBase *CB, Function *callee) {
    Intrinsic::ID id = callee->getIntrinsicID();
    auto A = [&](unsigned i) { return val(S, B, CB->getArgOperand(i)); };
    switch (id) {
    case Intrinsic::dbg_declare: case Intrinsic::dbg_value: case Intrinsic::dbg_label:
    case Intrinsic::lifetime_start: case Intrinsic::lifetime_end: case Intrinsic::assume:
    case Intrinsic::experimental_noalias_scope_decl:
      return;
    case Intrinsic::memcpy: case Intrinsic::memmove: {
      B.CreateCall(rtFn("hm_memmove", VoidT, {I32, I32, I32}), {A(0), A(1), fitInt(B, A(2), I32)});
      return;
    }
    case Intrinsic::memset:
      B.CreateCall(rtFn("hm_memset", VoidT, {I32, I8, I32}), {A(0), A(1), fitInt(B, A(2), I32)});
      return;
    case Intrinsic::fmuladd: {
      // PPC fmadd(s): fused. float: the product of two floats is exact in double -> close to fused.
      Value *a = A(0), *b = A(1), *c = A(2);
      if (a->getType()->isFloatTy()) {
        Value *r = B.CreateFAdd(B.CreateFMul(B.CreateFPExt(a, F64), B.CreateFPExt(b, F64)), B.CreateFPExt(c, F64));
        S.VM[CB] = B.CreateFPTrunc(r, F32);
      } else S.VM[CB] = B.CreateFAdd(B.CreateFMul(a, b), c);
      return;
    }
    case Intrinsic::fabs: case Intrinsic::sqrt: case Intrinsic::floor: case Intrinsic::ceil: case Intrinsic::trunc:
    case Intrinsic::round: case Intrinsic::copysign: case Intrinsic::ctlz: case Intrinsic::cttz: case Intrinsic::ctpop:
    case Intrinsic::bswap: case Intrinsic::umul_with_overflow: case Intrinsic::uadd_with_overflow:
    case Intrinsic::usub_with_overflow: case Intrinsic::smul_with_overflow: case Intrinsic::sadd_with_overflow:
    case Intrinsic::ssub_with_overflow: case Intrinsic::smax: case Intrinsic::smin: case Intrinsic::umax:
    case Intrinsic::umin: case Intrinsic::abs: case Intrinsic::fshl: case Intrinsic::fshr: case Intrinsic::expect:
    case Intrinsic::minnum: case Intrinsic::maxnum: case Intrinsic::fma: case Intrinsic::trap: case Intrinsic::sin:
    case Intrinsic::cos: case Intrinsic::pow: case Intrinsic::exp: case Intrinsic::log: {
      std::vector<Value *> a;
      for (unsigned i = 0; i < CB->arg_size(); i++) a.push_back(A(i));
      CallInst *ci = B.CreateCall(callee->getFunctionType(), callee, a);
      if (!CB->getType()->isVoidTy()) S.VM[CB] = ci;
      return;
    }
    default:
      throw Fail("intrinsic " + callee->getName().str());
    }
  }

  Value *safeDiv(IRBuilder<> &B, Instruction::BinaryOps op, Value *a, Value *b) {
    if (auto *cb = dyn_cast<ConstantInt>(b))
      if (!cb->isZero() && !cb->isMinusOne()) return B.CreateBinOp(op, a, b);
    Type *t = a->getType();
    Value *zero = B.CreateICmpEQ(b, ConstantInt::get(t, 0));
    Value *bad = zero;
    if (op == Instruction::SDiv || op == Instruction::SRem) {
      Value *ov = B.CreateAnd(B.CreateICmpEQ(a, ConstantInt::get(t, APInt::getSignedMinValue(t->getIntegerBitWidth()))),
                              B.CreateICmpEQ(b, ConstantInt::getSigned(t, -1)));
      bad = B.CreateOr(zero, ov);
    }
    Value *d = B.CreateSelect(bad, ConstantInt::get(t, 1), b);
    Value *r = B.CreateBinOp(op, a, d);
    if (op == Instruction::SDiv) return B.CreateSelect(zero, B.CreateSelect(B.CreateICmpSLT(a, ConstantInt::get(t, 0)), ConstantInt::getSigned(t, -1), ConstantInt::get(t, 0)), r);
    if (op == Instruction::UDiv) return B.CreateSelect(zero, ConstantInt::get(t, 0), r);
    return B.CreateSelect(zero, a, r);   // rem
  }

  Value *safeShift(IRBuilder<> &B, Instruction::BinaryOps op, Value *a, Value *s) {
    Type *t = a->getType();
    unsigned w = t->getIntegerBitWidth();
    if (auto *cs = dyn_cast<ConstantInt>(s))
      if (cs->getZExtValue() < w) return B.CreateBinOp(op, a, s);
    // PowerPC slw/srw/sraw: amount taken mod 64; >= 32 gives 0 (or the sign for sraw)
    unsigned m = w == 32 ? 63 : (w == 64 ? 127 : 2 * w - 1);
    Value *am = B.CreateAnd(s, ConstantInt::get(t, m));
    Value *big = B.CreateICmpUGE(am, ConstantInt::get(t, w));
    Value *sh = B.CreateBinOp(op, a, B.CreateAnd(am, ConstantInt::get(t, w - 1)));
    Value *ov = op == Instruction::AShr ? B.CreateAShr(a, ConstantInt::get(t, w - 1)) : ConstantInt::get(t, 0);
    return B.CreateSelect(big, ov, sh);
  }

  void translateInst(FnState &S, IRBuilder<> &B, Instruction &I) {
    switch (I.getOpcode()) {
    case Instruction::Alloca: {
      auto *AI = cast<AllocaInst>(&I);
      if (S.hostA.count(AI)) {
        IRBuilder<> EB(&S.N->getEntryBlock(), S.N->getEntryBlock().begin());
        S.VM[AI] = EB.CreateAlloca(mapTy(AI->getAllocatedType()));
      } else S.VM[AI] = B.CreateAdd(S.locals, B.getInt32(S.slot[AI]));
      return;
    }
    case Instruction::Load: {
      auto *L = cast<LoadInst>(&I);
      if (L->isAtomic()) throw Fail("atomic");
      Value *p = L->getPointerOperand();
      if (auto *AI = dyn_cast<AllocaInst>(p); AI && S.hostA.count(AI)) { S.VM[L] = B.CreateLoad(mapTy(L->getType()), S.VM[AI]); return; }
      S.VM[L] = gload(B, L->getType(), val(S, B, p), L->isVolatile());
      return;
    }
    case Instruction::Store: {
      auto *St = cast<StoreInst>(&I);
      if (St->isAtomic()) throw Fail("atomic");
      Value *p = St->getPointerOperand();
      Value *v = val(S, B, St->getValueOperand());
      if (auto *AI = dyn_cast<AllocaInst>(p); AI && S.hostA.count(AI)) { B.CreateStore(v, S.VM[AI]); return; }
      if (St->getValueOperand()->getType()->isAggregateType()) throw Fail("aggregate store");
      gstore(B, v, val(S, B, p), St->isVolatile());
      return;
    }
    case Instruction::GetElementPtr: {
      auto *G = cast<GetElementPtrInst>(&I);
      if (G->getType()->isVectorTy()) throw Fail("vector gep");
      Value *base = val(S, B, G->getPointerOperand());
      int64_t c = 0; Value *acc = base;
      for (gep_type_iterator GTI = gep_type_begin(G), E = gep_type_end(G); GTI != E; ++GTI) {
        Value *idx = GTI.getOperand();
        if (StructType *st = GTI.getStructTypeOrNull()) {
          c += DL.getStructLayout(st)->getElementOffset(cast<ConstantInt>(idx)->getZExtValue());
          continue;
        }
        int64_t es = (int64_t)DL.getTypeAllocSize(GTI.getIndexedType());
        if (auto *ci = dyn_cast<ConstantInt>(idx)) { c += ci->getSExtValue() * es; continue; }
        Value *v = val(S, B, idx);
        v = fitInt(B, v, I32, true);
        acc = B.CreateAdd(acc, es == 1 ? v : B.CreateMul(v, B.getInt32((uint32_t)es)));
      }
      if (c) acc = B.CreateAdd(acc, B.getInt32((uint32_t)c));
      S.VM[G] = acc;
      return;
    }
    case Instruction::PtrToInt: S.VM[&I] = fitInt(B, val(S, B, I.getOperand(0)), I.getType()); return;
    case Instruction::IntToPtr: S.VM[&I] = fitInt(B, val(S, B, I.getOperand(0)), I32); return;
    case Instruction::BitCast:
      if (I.getType()->isPointerTy()) { S.VM[&I] = val(S, B, I.getOperand(0)); return; }
      S.VM[&I] = B.CreateBitCast(val(S, B, I.getOperand(0)), mapTy(I.getType())); return;
    case Instruction::FPToSI: case Instruction::FPToUI: {
      Value *v = val(S, B, I.getOperand(0));
      unsigned w = I.getType()->getIntegerBitWidth();
      Type *it = w < 32 ? I32 : I.getType();
      Intrinsic::ID id = I.getOpcode() == Instruction::FPToSI ? Intrinsic::fptosi_sat : Intrinsic::fptoui_sat;
      Value *r = B.CreateIntrinsic(id, {it, v->getType()}, {v});
      S.VM[&I] = fitInt(B, r, I.getType());
      return;
    }
    case Instruction::Trunc: case Instruction::ZExt: case Instruction::SExt: case Instruction::FPTrunc:
    case Instruction::FPExt: case Instruction::SIToFP: case Instruction::UIToFP:
      S.VM[&I] = B.CreateCast(cast<CastInst>(&I)->getOpcode(), val(S, B, I.getOperand(0)), mapTy(I.getType()));
      return;
    case Instruction::ICmp: {
      auto *ic = cast<ICmpInst>(&I);
      if (ic->getOperand(0)->getType()->isVectorTy()) throw Fail("vector icmp");
      S.VM[&I] = B.CreateICmp(ic->getPredicate(), val(S, B, I.getOperand(0)), val(S, B, I.getOperand(1)));
      return;
    }
    case Instruction::FCmp:
      S.VM[&I] = B.CreateFCmp(cast<FCmpInst>(&I)->getPredicate(), val(S, B, I.getOperand(0)), val(S, B, I.getOperand(1)));
      return;
    case Instruction::Select:
      S.VM[&I] = B.CreateSelect(val(S, B, I.getOperand(0)), val(S, B, I.getOperand(1)), val(S, B, I.getOperand(2)));
      return;
    case Instruction::FNeg: S.VM[&I] = B.CreateFNeg(val(S, B, I.getOperand(0))); return;
    case Instruction::Freeze: S.VM[&I] = B.CreateFreeze(val(S, B, I.getOperand(0))); return;
    case Instruction::ExtractValue: {
      auto *ev = cast<ExtractValueInst>(&I);
      S.VM[&I] = B.CreateExtractValue(val(S, B, ev->getAggregateOperand()), ev->getIndices());
      return;
    }
    case Instruction::PHI: {
      PHINode *p = B.CreatePHI(mapTy(I.getType()), cast<PHINode>(&I)->getNumIncomingValues());
      S.phis.push_back({cast<PHINode>(&I), p});
      S.VM[&I] = p;
      return;
    }
    case Instruction::Call: translateCall(S, B, cast<CallBase>(&I)); return;
    case Instruction::Ret: {
      if (S.frame) B.CreateStore(S.sp0, cpuPtr(B, CPU_R + 4));
      auto *R = cast<ReturnInst>(&I);
      if (R->getReturnValue()) B.CreateRet(val(S, B, R->getReturnValue()));
      else B.CreateRetVoid();
      return;
    }
    case Instruction::Br: {
      auto *Br = cast<BranchInst>(&I);
      bool back = false;
      for (BasicBlock *s : successors(I.getParent())) back |= S.backEdges.count({I.getParent(), s}) > 0;
      if (back) checkpoint(B);
      if (Br->isConditional()) B.CreateCondBr(val(S, B, Br->getCondition()), S.BM[Br->getSuccessor(0)], S.BM[Br->getSuccessor(1)]);
      else B.CreateBr(S.BM[Br->getSuccessor(0)]);
      return;
    }
    case Instruction::Switch: {
      auto *Sw = cast<SwitchInst>(&I);
      bool back = false;
      for (BasicBlock *s : successors(I.getParent())) back |= S.backEdges.count({I.getParent(), s}) > 0;
      if (back) checkpoint(B);
      SwitchInst *ns = B.CreateSwitch(val(S, B, Sw->getCondition()), S.BM[Sw->getDefaultDest()], Sw->getNumCases());
      for (auto &cs : Sw->cases()) ns->addCase(cs.getCaseValue(), S.BM[cs.getCaseSuccessor()]);
      return;
    }
    case Instruction::Unreachable: B.CreateUnreachable(); return;
    default:
      break;
    }
    if (auto *BO = dyn_cast<BinaryOperator>(&I)) {
      Value *a = val(S, B, BO->getOperand(0)), *b = val(S, B, BO->getOperand(1));
      auto op = BO->getOpcode();
      if (a->getType()->isVectorTy()) throw Fail("vector op");
      switch (op) {
      case Instruction::SDiv: case Instruction::UDiv: case Instruction::SRem: case Instruction::URem:
        S.VM[&I] = safeDiv(B, op, a, b); return;
      case Instruction::Shl: case Instruction::LShr: case Instruction::AShr:
        S.VM[&I] = safeShift(B, op, a, b); return;
      default:
        S.VM[&I] = B.CreateBinOp(op, a, b);
        return;
      }
    }
    throw Fail(std::string("instruction ") + I.getOpcodeName());
  }

  void translate(Function *F, Function *N) {
    FnState S; S.F = F; S.N = N;
    if (F->isVarArg()) throw Fail("varargs definition");
    analyze(S);
    // blocks
    ReversePostOrderTraversal<Function *> RPO(F);
    std::set<BasicBlock *> reach;
    for (BasicBlock *BB : RPO) reach.insert(BB);
    BasicBlock *entry = BasicBlock::Create(C, "entry", N);
    for (BasicBlock &BB : *F) S.BM[&BB] = BasicBlock::Create(C, BB.getName(), N);
    unsigned i = 0;
    for (Argument &a : F->args()) S.VM[&a] = N->getArg(i++);
    IRBuilder<> B(entry);
    if (S.frame) {
      S.sp0 = B.CreateLoad(I32, cpuPtr(B, CPU_R + 4), "sp0");
      S.sp = B.CreateSub(S.sp0, B.getInt32(S.frame), "sp");
      gstore(B, S.sp0, S.sp, false);                     // back chain
      B.CreateStore(S.sp, cpuPtr(B, CPU_R + 4));
      Value *l = B.CreateAdd(S.sp, B.getInt32(8 + S.outArea));
      if (S.maxAlign > 8) l = B.CreateAnd(B.CreateAdd(l, B.getInt32(S.maxAlign - 1)), B.getInt32(~(S.maxAlign - 1)));
      S.locals = l;
    } else {
      S.sp = B.CreateLoad(I32, cpuPtr(B, CPU_R + 4), "sp");
      S.locals = S.sp;
    }
    B.CreateBr(S.BM[&F->getEntryBlock()]);
    for (BasicBlock *BB : RPO) {
      IRBuilder<> BB2(S.BM[BB]);
      for (Instruction &I : *BB) translateInst(S, BB2, I);
    }
    for (BasicBlock &BB : *F) if (!reach.count(&BB)) { IRBuilder<> UB(S.BM[&BB]); UB.CreateUnreachable(); }
    for (auto &[op, np] : S.phis)
      for (unsigned k = 0; k < op->getNumIncomingValues(); k++) {
        BasicBlock *ib = op->getIncomingBlock(k);
        IRBuilder<> PB(S.BM[ib]->getTerminator() ? S.BM[ib]->getTerminator() : (Instruction *)nullptr);
        Value *v = reach.count(ib) ? val(S, PB, op->getIncomingValue(k)) : Constant::getNullValue(np->getType());
        np->addIncoming(v, S.BM[ib]);
      }
  }

  // thunk: void hmt_A(CPU *c) -- unmarshal guest-ABI args, call the native function, write the result back
  void makeThunk(Function *F, Function *N, uint32_t a) {
    char nm[32]; snprintf(nm, sizeof nm, "hmt_%08X", a);
    Function *T = Function::Create(FunctionType::get(VoidT, {PtrT}, false),
                                   F->hasLinkOnceLinkage() || F->hasWeakLinkage() ? GlobalValue::WeakODRLinkage : GlobalValue::ExternalLinkage, nm, M);
    Value *c = T->getArg(0);
    IRBuilder<> B(BasicBlock::Create(C, "entry", T));
    uint32_t sb = 0;
    auto locs = assign(F->getFunctionType(), sb);
    std::vector<Value *> args;
    Value *sp = nullptr;
    // MWCC constructors return `this` in r3: void functions keep r3 as it was on entry
    Value *r3in = F->getReturnType()->isVoidTy() ? B.CreateLoad(I32, cpuPtr(B, c, CPU_R + 12)) : nullptr;
    for (unsigned i = 0; i < F->arg_size(); i++) {
      Type *nt = N->getFunctionType()->getParamType(i);
      const ArgLoc &L = locs[i];
      Value *v;
      if (L.kind == 2) { v = B.CreateLoad(F64, cpuPtr(B, c, CPU_F + 8 * L.reg)); if (nt->isFloatTy()) v = B.CreateFPTrunc(v, F32); }
      else if (L.kind == 1 || L.kind == 4) {
        Value *hi, *lo;
        if (L.kind == 1) { hi = B.CreateLoad(I32, cpuPtr(B, c, CPU_R + 4 * L.reg)); lo = B.CreateLoad(I32, cpuPtr(B, c, CPU_R + 4 * L.reg + 4)); }
        else {
          if (!sp) sp = B.CreateLoad(I32, cpuPtr(B, c, CPU_R + 4));
          Value *ad = B.CreateAdd(sp, B.getInt32(8 + L.stk));
          hi = gload(B, I32, ad, false); lo = gload(B, I32, B.CreateAdd(ad, B.getInt32(4)), false);
        }
        v = B.CreateOr(B.CreateShl(B.CreateZExt(hi, I64), 32), B.CreateZExt(lo, I64));
      } else {
        if (L.kind == 0) v = B.CreateLoad(I32, cpuPtr(B, c, CPU_R + 4 * L.reg));
        else { if (!sp) sp = B.CreateLoad(I32, cpuPtr(B, c, CPU_R + 4)); v = gload(B, I32, B.CreateAdd(sp, B.getInt32(8 + L.stk)), false); }
        v = fitInt(B, v, nt);
      }
      args.push_back(v);
    }
    Value *r = B.CreateCall(N, args);
    Type *rt = F->getReturnType();
    if (rt->isFloatTy()) B.CreateStore(B.CreateFPExt(r, F64), cpuPtr(B, c, CPU_F + 8));
    else if (rt->isDoubleTy()) B.CreateStore(r, cpuPtr(B, c, CPU_F + 8));
    else if (rt->isIntegerTy(64)) {
      B.CreateStore(B.CreateTrunc(B.CreateLShr(r, 32), I32), cpuPtr(B, c, CPU_R + 12));
      B.CreateStore(B.CreateTrunc(r, I32), cpuPtr(B, c, CPU_R + 16));
    } else if (!rt->isVoidTy()) {
      bool sx = F->hasRetAttribute(Attribute::SExt);
      Value *v = r;
      if (v->getType()->getIntegerBitWidth() < 32) v = sx ? B.CreateSExt(v, I32) : B.CreateZExt(v, I32);
      B.CreateStore(v, cpuPtr(B, c, CPU_R + 12));
    }
    if (r3in) B.CreateStore(r3in, cpuPtr(B, c, CPU_R + 12));
    B.CreateRetVoid();
  }

  static std::string sig(FunctionType *FT) {
    auto k = [](Type *t) -> char {
      if (t->isVoidTy()) return 'v'; if (t->isPointerTy()) return 'p'; if (t->isFloatTy()) return 'f';
      if (t->isDoubleTy()) return 'd'; if (t->isIntegerTy(64)) return 'l'; if (t->isIntegerTy()) return 'i'; return '?';
    };
    std::string s(1, k(FT->getReturnType())); s += ':';
    for (Type *t : FT->params()) s += k(t);
    if (FT->isVarArg()) s += "...";
    return s;
  }

  bool run() {
    loadConfig();
    resolveGlobals();
    // rename the guest-typed module contents out of the way (fn_XXXXXXXX names are needed for recompiled code)
    std::vector<Function *> olds;
    std::vector<GlobalVariable *> oldg;
    for (Function &F : M) { if (F.isIntrinsic()) continue; oname[&F] = F.getName().str(); olds.push_back(&F); }
    for (GlobalVariable &G : M.globals()) { oname[&G] = G.getName().str(); oldg.push_back(&G); }
    for (Function *F : olds) F->setName("__gm_old." + oname[F]);
    for (GlobalVariable *G : oldg) G->setName("__gm_old." + oname[G]);
    // candidate natives
    std::vector<Function *> cands;
    for (Function &F : M) {
      if (F.isDeclaration() || F.isIntrinsic()) continue;
      std::string n = on(&F);
      auto ait = addr.find(&F);
      if (denyName.count(n) || (ait != addr.end() && denyAddr.count(ait->second))) { failReason[&F] = "denied"; continue; }
      if (F.isVarArg()) { failReason[&F] = "varargs definition"; continue; }
      if (isAsmFn(n)) { failReason[&F] = "MWCC inline asm in source"; continue; }
      cands.push_back(&F);
    }
    gCPU = cast<GlobalVariable>(M.getOrInsertGlobal("g_cpu", ArrayType::get(I8, 0)));
    // iterate to a fixpoint: a failing helper (no guest address) makes its callers fail
    for (;;) {
      for (auto &kv : NF) kv.second->eraseFromParent();
      NF.clear();
      std::set<uint32_t> usedAddr;
      for (Function *F : cands) {
        if (failReason.count(F)) continue;
        try {
          auto ait = addr.find(F);
          if (ait != addr.end() && !usedAddr.insert(ait->second).second) { addr.erase(ait); ait = addr.end(); }   // C1/C2 twins
          std::string nn;
          if (ait != addr.end()) { char b[32]; snprintf(b, sizeof b, "hmn_%08X", ait->second); nn = b; }
          else nn = "hmi_" + on(F);
          GlobalValue::LinkageTypes lk = ait == addr.end() ? GlobalValue::InternalLinkage :
              (F->hasLinkOnceLinkage() || F->hasWeakLinkage() ? GlobalValue::WeakODRLinkage : GlobalValue::ExternalLinkage);
          NF[F] = Function::Create(nativeType(F), lk, nn, M);
        } catch (Fail &e) { failReason[F] = e.what(); }
      }
      bool changed = false;
      for (auto &kv : NF) {
        try { translate(kv.first, kv.second); }
        catch (Fail &e) { failReason[kv.first] = e.what(); changed = true; }
      }
      if (!changed) break;
    }
    // thunks + metadata
    for (auto &[F, N] : NF) {
      auto ait = addr.find(F);
      if (ait == addr.end()) { meta << "helper " << on(F) << "\n"; continue; }
      makeThunk(F, N, ait->second);
      char b[16]; snprintf(b, sizeof b, "%08X", ait->second);
      meta << "native " << b << " " << on(F) << " " << sig(F->getFunctionType()) << "\n";
    }
    for (auto &[F, r] : failReason) {
      auto ait = addr.find(F);
      char b[16] = "-"; if (ait != addr.end()) snprintf(b, sizeof b, "%08X", ait->second);
      meta << "fail " << b << " " << on(F) << " " << r << "\n";
    }
    // drop the guest-typed module contents
    for (GlobalAlias &A : make_early_inc_range(M.aliases())) { A.replaceAllUsesWith(PoisonValue::get(A.getType())); A.eraseFromParent(); }
    for (Function *F : olds) F->dropAllReferences();
    for (GlobalVariable *G : oldg) G->dropAllReferences();
    for (Function *F : olds) {
      F->replaceAllUsesWith(PoisonValue::get(F->getType())); F->eraseFromParent();
    }
    for (GlobalVariable *G : oldg) { G->replaceAllUsesWith(PoisonValue::get(G->getType())); G->eraseFromParent(); }
    // data blob
    if (!blob.empty()) {
      auto *init = ConstantDataArray::get(C, ArrayRef<uint8_t>(blob));
      new GlobalVariable(M, init->getType(), true, GlobalValue::ExternalLinkage, init, "hm_blob_" + unit);
      char b[16]; snprintf(b, sizeof b, "%08X", dataBase);
      meta << "blob " << b << " " << blob.size() << " hm_blob_" << unit << "\n";
    }
    if (!M.getModuleInlineAsm().empty()) { meta << "warn module-asm dropped\n"; M.setModuleInlineAsm(""); }
    M.setTargetTriple("x86_64-pc-linux-gnu");
    M.setDataLayout("e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128");
    for (Function &F : M) {   // drop PPC target attributes
      F.removeFnAttr("target-cpu"); F.removeFnAttr("target-features"); F.removeFnAttr("tune-cpu");
      if (!F.isDeclaration()) F.addFnAttr(Attribute::NoUnwind);
    }
    if (!metaPath.empty()) { std::ofstream o(metaPath); o << meta.str(); }
    return true;
  }
};

struct GuestMemPass : PassInfoMixin<GuestMemPass> {
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
    GuestMem G(M);
    G.run();
    return PreservedAnalyses::none();
  }
};
} // namespace

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "GuestMem", "0.1", [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback([](StringRef name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) {
              if (name == "guestmem") { MPM.addPass(GuestMemPass()); return true; }
              return false;
            });
          }};
}
