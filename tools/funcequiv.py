#!/usr/bin/env python3
"""Functional-equivalence check (translation validation) of one compiled function
against the original (EXPERIMENTAL, branch sched-equiv, worker wTV 2026-11-12).

Unlike tools/equivcheck.py (same instructions, other registers / other order inside a
block) this proves that two DIFFERENT instruction sequences compute the same thing:
instructions may sit in other basic blocks, in other registers, be duplicated or merged,
and the two functions may have different sizes.  Nothing here is linked or accepted by
the build; the tool only answers "proved equivalent" or "not proved" (= reject).

Method
  Both functions are decoded (PowerPC 750CL subset below) and executed symbolically
  with z3: GPRs, CTR, LR as 32-bit vectors, CR as eight 4-bit fields, XER[CA] / XER[SO]
  as single bits, FPRs as 64-bit vectors, memory as an array of bytes (big endian).
  Integer instructions have their exact semantics (checked against unicorn by
  --selftest), except divw/divwu/mulhw/mulhwu/cntlzw which are uninterpreted functions
  (equal inputs give equal results, nothing else is known).  Every floating-point
  operation is an uninterpreted function of its inputs and of the FP environment, one
  symbol per opcode (fadd is not fsub, fadds is not fadd, operands are not commutative);
  fmr/fneg/fabs/fnabs/lfd/stfd are exact bit operations.  psq_st / psq_l with W=0 and
  GQR0 (the callee-saved FPR save / restore of the compiler) are uninterpreted functions
  of the register, of its second paired-single slot (tracked per FPR) and of the FP
  environment.
  Cut points: function entry, every loop header (target of a retreating edge of a
  depth-first walk), every call, every return / tail call.  The two versions are run in
  tandem from a pair of cut points to the next pair along every path (a conditional
  branch forks the path; a direction that contradicts the path condition syntactically is
  dropped).  When both stand at a cut point these must be of the same kind (the CFG
  shape over cut points has to match), and the following is PROVED under the path
  condition (identical terms, else an unsat answer of the solver; "unknown" counts as
  not proved; a failure only does not count when the path condition itself is unsat):
    call    same target (same address; bctrl: same CTR, blrl: same LR); every volatile
            register the callee may read (Program.inputs_of of the original program;
            r3-r10 / f1-f8 / cr1 for an indirect callee) has the same value in the same
            register; r1, r2, r13 are the same; memory is the same (all of it, the stack
            frame included);
    return  r3, every volatile register some caller may read after the return
            (Program.retuse: r4 / f1 only when readable), every callee-saved register
            (r14-r31, f14-f31 with their second slots, cr2-cr4), r1, r2, r13, LR and
            memory are the same;
    tail    both of the above;
    loop    memory is the same; the registers that carry the same value in both versions
            at the header are found as the greatest fixpoint of "equal on every edge
            into the header" (a partition of all registers of both versions and of
            constants: the simulation relation; it is proved inductively because the
            header pair is explored again whenever the relation got weaker);
    stores  between two cut points the two versions make the same stores: there is a
            one-to-one matching of stores with the same size, the same address and the
            same value (their order may differ only if memory is still provably the
            same at the next cut point, i.e. they cannot overlap).
  A load reads the byte array as it is at that point (only stores that provably do not
  overlap are skipped), so a load that moved across a store or a call only passes when
  it provably reads the same value.
  After a call: memory is one new unknown shared by both versions (the callee got the
  same inputs); a volatile register is the same new unknown in both versions when the
  callee cannot return it unchanged (Program.thru_of) or when it held the same value
  in both before the call, otherwise it is a different unknown in each version; LR is
  always a different unknown; callee-saved registers, r1, r2, r13 keep their values.
  When there are too many paths between the cut points (path / step budget), a second
  attempt also cuts at every join of the control flow: sound in the same way, but an
  instruction that moved across a join is then usually no longer followed.

Always assumed (as equivcheck rule d does): a callee is a deterministic function of the
  registers it reads and of memory, obeys the ABI for callee-saved registers and does
  not interpret the caller's callee-saved registers; r13 / r2 hold the small-data bases
  at function entry; .rodata / .sdata2 are never written (a load from a constant address
  there yields the bytes of the DOL); the FPSCR status bits are not observed (mffs,
  mtfsf, record-form FP instructions are rejected) and the second paired-single slot of a
  volatile FPR is not read across a call or return; XER[SO] is never set
  (overflow-enable forms are rejected).
Optional assumptions (off by default; --policy turns on all three, they are the ones
  equivcheck rules d / f already make for linked functions):
  --frame       r1-based accesses at non-negative offsets, while r1 is the function's own
                frame pointer, do not overlap constant addresses inside the DOL image /
                bss (rule 'global'); and when no frame address leaves r1 in either
                version (SchedCtx._escapes) the own frame [0, N) is a memory of its own
                that only r1-based accesses reach (rule 'pointer').
  --fp-commute  fadd(s) / fmul(s) and the factors of f(n)madd(s) / f(n)msub(s) may be
                exchanged (differs in the NaN payload when both operands are NaN).
  --leftover    what a call leaves in a volatile register other than r3 / r4 / f1 only
                matters when the function reads it with its own instructions (or a
                caller does after the return), not when a later callee "may read" it.
Rejected (never accepted): anything not decoded here (paired-single arithmetic, cache
  and system instructions, mfspr/mtspr other than LR/CTR, lwarx/stwcx., string
  instructions ...), bctr without link (jump tables, indirect tail calls), conditional
  branches out of the function, calls to an address that is not a function start, any
  `lis` of a hardware address high half (0xCC00, 0xCD00, 0xE000: volatile memory keeps
  its access order), a relocation against a local symbol of our object that cannot be
  tied to an address of the original (read-only literals excepted: they get a pseudo
  address and are known by their bytes only), a solver time-out, a blown budget.
Limits: a different stack frame layout, a callee-saved register saved by one version
  only, a loop that keeps differently derived values (i vs 4*i), a different loop /
  call structure, pointers that may alias a frame whose address escapes, FP expressions
  that differ (fmadd against fmul + fadd) are not proved, even when equivalent.

Usage:
  funcequiv.py --selftest              semantics against unicorn, synthetic pairs with
                                       mutations that must be rejected, real pairs with
                                       mutations that must be rejected
  funcequiv.py --list U ...            U = unit, unit:fn[,fn] or a function name; compares
                                       build/<v>/src/<unit>.o with the original DOL
  funcequiv.py --check                 every function of config/<v>/funcequiv.txt must be
                                       proved (objects, not the linked DOL)
  funcequiv.py --fuzz FN ...           run both versions in unicorn on random states and
                                       compare calls, results and memory (a sanity check
                                       of the prover, independent of z3; no proof)
  options: --policy | --frame --fp-commute --leftover, --limit SECONDS, --debug
Needs z3 (and unicorn for --selftest / --fuzz): /home/mi/Decomp/hm-work/venv-tv/bin/python.
"""
import argparse
import ctypes
import os
import random
import re
import signal
import struct
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import equivcheck as E  # noqa: E402  (decoder tables, DOL / object readers, whole-program facts)
import z3  # noqa: E402

ROOT = E.ROOT
sys.setrecursionlimit(20000)

BV32 = z3.BitVecSort(32)
BV8 = z3.BitVecSort(8)
MEMSORT = z3.ArraySort(BV32, BV8)
M32 = 0xFFFFFFFF
ONE1 = z3.BitVecVal(1, 1)
ZERO1 = z3.BitVecVal(0, 1)
RET = -1
DEBUG = False
ALIAS = False           # the alias rules (--frame) are on for the pair being checked
FPCOMM = False          # --fp-commute: fadd/fmul operands may be exchanged (as equivcheck rule d)


class Reject(Exception):
    pass


def S(x):
    return z3.simplify(x)


def bv(v, n=32):
    return z3.BitVecVal(v & ((1 << n) - 1), n)


def sext16(v):
    return v - 0x10000 if v & 0x8000 else v


_ufs = {}


def UF(name, res, *args):
    """Uninterpreted function application (one symbol per name and signature)."""
    key = (name, res, tuple(a.size() for a in args))
    f = _ufs.get(key)
    if f is None:
        f = _ufs[key] = z3.Function('%s_%d' % (name, len(_ufs)), *([a.sort() for a in args] + [z3.BitVecSort(res)]))
    return f(*args)


def UFc(name, res, a, b):
    """Commutative uninterpreted function (mulhw, mulhwu): operands in a fixed order."""
    if a.get_id() > b.get_id():
        a, b = b, a
    return UF(name, res, a, b)


def split(a):
    """(base term, constant offset) of a simplified address."""
    if z3.is_bv_value(a):
        return None, a.as_long()
    if a.decl().kind() == z3.Z3_OP_BADD:
        ch = a.children()
        if z3.is_bv_value(ch[0]):
            rest = ch[1]
            for c in ch[2:]:
                rest = rest + c
            if len(ch) > 2:
                rest = S(rest)
            return rest, ch[0].as_long()
    return a, 0


def same_base(a, b):
    return (a is None and b is None) or (a is not None and b is not None and a.eq(b))


RO = None      # (address, size) -> bytes of read-only data, or None; set while a pair is checked


class RoData:
    """Constant memory: .rodata / .sdata2 of the original DOL (extent of the symbols of
    symbols.txt in those sections) and the read-only literals of our object that have no
    address in the original (`fakes`: (pseudo address, bytes), addresses below 0x8000)."""

    def __init__(self, prog, fakes=()):
        self.dol = prog.dol
        rng = getattr(prog, 'rorng', None)
        if rng is None:
            rng = {}
            rx = re.compile(r'^\S+ = (\.rodata|\.sdata2):0x([0-9A-Fa-f]+);(?:.*size:0x([0-9A-Fa-f]+))?')
            for line in open(prog.symfile):
                m = rx.match(line)
                if m:
                    a = int(m.group(2), 16)
                    e = a + int(m.group(3) or '0', 16)
                    lo, hi = rng.get(m.group(1), (a, e))
                    rng[m.group(1)] = (min(lo, a), max(hi, e))
            rng = prog.rorng = sorted(rng.values())
        self.rng = rng
        self.fakes = list(fakes)

    def is_global(self, addr, size):
        """The bytes lie in a section of the DOL or in its bss range (never on the stack)."""
        d = self.dol
        for _off, a, sz, _t in d.secs:
            if a <= addr and addr + size <= a + sz:
                return True
        b = getattr(d, 'bss', None)
        return bool(b) and b[0] <= addr and addr + size <= b[0] + b[1]

    def __call__(self, addr, size):
        if addr < 0x8000:
            for a, data in self.fakes:
                if a <= addr and addr + size <= a + len(data):
                    return data[addr - a:addr - a + size]
            return None
        for lo, hi in self.rng:
            if lo <= addr and addr + size <= hi:
                off = self.dol.find(addr)
                if off is not None and self.dol.find(addr + size - 1) == off + size - 1:
                    return self.dol.data[off:off + size]
        return None


class Mem:
    """Byte array with a log of the stores since the last cut point. `arr` is the exact
    semantics; the log only lets a load skip stores that provably do not overlap (same
    base term and disjoint constant ranges; or, with the alias rules on, one access in the
    function's own stack frame and the other at a constant address inside the DOL image /
    bss) or take the stored value directly."""
    __slots__ = ('arr', 'log', 'base')

    def __init__(self, arr, log=None, base=None):
        self.arr = arr
        self.log = log if log is not None else []
        self.base = base if base is not None else arr

    def copy(self):
        return Mem(self.arr, list(self.log), self.base)

    @staticmethod
    def _cls(base, off, size, cls):
        if cls is None and ALIAS and base is None and RO is not None and RO.is_global(off, size):
            return 'G'
        return cls

    def store(self, addr, val, size, cls=None):
        base, off = split(addr)
        arr = self._put(self.arr, addr, val, size)
        self.arr = arr
        self.log.append((base, off, size, val, arr, self._cls(base, off, size, cls), addr))

    @staticmethod
    def _put(arr, addr, val, size):
        for k in range(size):
            hi = 8 * (size - k) - 1
            arr = z3.Store(arr, S(addr + k), S(z3.Extract(hi, hi - 7, val)))
        return arr

    def load(self, addr, size, cls=None):
        base, off = split(addr)
        if base is None and RO is not None:                   # read-only data is never written
            data = RO(off, size)
            if data is not None:
                return bv(int.from_bytes(data, 'big'), 8 * size)
        cls = self._cls(base, off, size, cls)
        log = self.log
        keep = []                                             # stores that may reach the bytes, newest first
        for idx in range(len(log) - 1, -1, -1):
            e = log[idx]
            if same_base(e[0], base):
                d = (off - e[1]) & M32
                if d < e[2] or ((e[1] - off) & M32) < size:   # overlaps
                    keep.append(idx)
                    if d < e[2] and d + size <= e[2]:         # covers all of it: older stores are dead
                        if len(keep) == 1:
                            hi = 8 * (e[2] - d) - 1
                            return S(z3.Extract(hi, hi - 8 * size + 1, e[3]))
                        break
            elif not (cls and e[5] and cls != e[5]):          # unknown base: may alias
                keep.append(idx)
        # The value is read from the start array with only those stores applied, in their
        # order: the term does not depend on where provably disjoint stores sit.
        if keep and keep[-1] == 0 and keep[0] == len(keep) - 1:
            arr = log[keep[0]][4]                             # all stores up to there: already built
        else:
            arr = self.base
            for idx in reversed(keep):
                e = log[idx]
                arr = self._put(arr, e[6], e[3], e[2])
        bs = [z3.Select(arr, S(addr + k)) for k in range(size)]
        return S(z3.Concat(*bs)) if size > 1 else S(bs[0])


def apart(x, y):
    """Two log entries that provably do not overlap."""
    if same_base(x[0], y[0]):
        return ((y[1] - x[1]) & M32) >= x[2] and ((x[1] - y[1]) & M32) >= y[2]
    return bool(x[5] and y[5] and x[5] != y[5])


def same_stores(ma, mb):
    """The two memories started from the same array and got the same stores (same address,
    size and value terms), and every two stores that come in the other order in the other
    version provably do not overlap: the arrays are equal."""
    la, lb = ma.log, mb.log
    if not ma.base.eq(mb.base) or len(la) != len(lb):
        return False
    used = [False] * len(lb)
    perm = []
    for x in la:
        for k, y in enumerate(lb):
            if not used[k] and x[1] == y[1] and x[2] == y[2] and same_base(x[0], y[0]) and x[3].eq(y[3]):
                used[k] = True
                perm.append(k)
                break
        else:
            return False
    for i in range(len(perm)):
        for j in range(i + 1, len(perm)):
            if perm[i] > perm[j] and not apart(la[i], la[j]):
                return False
    return True


LOCS = [('r', i) for i in range(32)] + [('f', i) for i in range(32)] + [('p', i) for i in range(32)] + \
    [('cr', i) for i in range(8)] + ['ctr', 'lr', 'ca', 'so', 'env', 'mem', 'fmem']


def loc_sort(loc):
    if loc in ('mem', 'fmem'):
        return MEMSORT
    if loc in ('ca', 'so'):
        return z3.BitVecSort(1)
    if loc in ('ctr', 'lr', 'env'):
        return BV32
    return {'r': BV32, 'f': z3.BitVecSort(64), 'p': z3.BitVecSort(64), 'cr': z3.BitVecSort(4)}[loc[0]]


def loc_name(loc):
    return loc if isinstance(loc, str) else '%s%d' % loc


def mask_locs(m):
    out = []
    for b in range(72):
        if m >> b & 1:
            out.append(('r', b) if b < 32 else ('f', b - 32) if b < 64 else ('cr', b - 64))
    return out


class St:
    __slots__ = ('g', 'f', 'p', 'cr', 'ctr', 'lr', 'ca', 'so', 'env', 'mem', 'fmem', 'stores')

    def copy(self):
        s = St()
        s.g, s.f, s.p, s.cr = list(self.g), list(self.f), list(self.p), list(self.cr)
        s.ctr, s.lr, s.ca, s.so, s.env = self.ctr, self.lr, self.ca, self.so, self.env
        s.mem = self.mem.copy()
        s.fmem = self.fmem.copy()
        s.stores = list(self.stores)
        return s

    def get(self, loc):
        if isinstance(loc, tuple):
            return {'r': self.g, 'f': self.f, 'p': self.p, 'cr': self.cr}[loc[0]][loc[1]]
        return self.mem.arr if loc == 'mem' else self.fmem.arr if loc == 'fmem' else getattr(self, loc)

    def set(self, loc, v):
        if isinstance(loc, tuple):
            {'r': self.g, 'f': self.f, 'p': self.p, 'cr': self.cr}[loc[0]][loc[1]] = v
        elif loc == 'mem':
            self.mem = Mem(v)
        elif loc == 'fmem':
            self.fmem = Mem(v)
        else:
            setattr(self, loc, v)


def rmask(mb, me):
    if mb <= me:
        return ((1 << (32 - mb)) - 1) & ~((1 << (31 - me)) - 1) & M32
    return (((1 << (32 - mb)) - 1) | ~((1 << (31 - me)) - 1)) & M32


def b1(c):
    return z3.If(c, ONE1, ZERO1)


def cmpf(a, b, signed, so):
    lt = a < b if signed else z3.ULT(a, b)
    gt = a > b if signed else z3.UGT(a, b)
    return S(z3.Concat(b1(lt), b1(gt), b1(a == b), so))


def add3(a, b, c):
    """a + b + c with the carry out (c: 1-bit term)."""
    t = z3.ZeroExt(1, a) + z3.ZeroExt(1, b) + z3.ZeroExt(32, c)
    return S(z3.Extract(31, 0, t)), S(z3.Extract(32, 32, t))


LOADS = {32: (4, 0, 0), 33: (4, 0, 1), 34: (1, 0, 0), 35: (1, 0, 1), 40: (2, 0, 0), 41: (2, 0, 1),
         42: (2, 1, 0), 43: (2, 1, 1)}                    # size, sign-extend, update
STORES = {36: (4, 0), 37: (4, 1), 38: (1, 0), 39: (1, 1), 44: (2, 0), 45: (2, 1)}
XLOADS = {23: (4, 0, 0), 55: (4, 0, 1), 87: (1, 0, 0), 119: (1, 0, 1), 279: (2, 0, 0), 311: (2, 0, 1),
          343: (2, 1, 0), 375: (2, 1, 1)}
XSTORES = {151: (4, 0), 183: (4, 1), 215: (1, 0), 247: (1, 1), 407: (2, 0), 439: (2, 1)}
FOPS = {18: ('fdiv', 'ab'), 20: ('fsub', 'ab'), 21: ('fadd', 'ab'), 25: ('fmul', 'ac'), 28: ('fmsub', 'acb'),
        29: ('fmadd', 'acb'), 30: ('fnmsub', 'acb'), 31: ('fnmadd', 'acb')}
SIGN64 = 1 << 63


def step(st, w, addr, lo, hi, fr=0, own=0):
    """Execute one instruction on st (fr: size of the function's own stack frame when r1
    is its frame pointer here and the frame rule is on). Returns None (fall through) or
    ('jmp', index) | ('br', cond, index|RET, index) | ('call', target|'ctr'|'lr') |
    ('ret',) | ('tail', target).  Raises Reject for anything unknown."""
    op = w >> 26
    D = (w >> 21) & 31
    A = (w >> 16) & 31
    B = (w >> 11) & 31
    g = st.g
    simm = sext16(w & 0xFFFF)
    uimm = w & 0xFFFF
    i = (addr - lo) >> 2

    def bad(why='unsupported instruction'):
        raise Reject('%s %08x at %08x' % (why, w, addr))

    def ea_d():
        return S(g[A] + simm) if A else bv(simm)

    def mm(off, size):
        # (memory, tag, class) of a displacement access: the own frame is a memory of its
        # own (fr), or at least known to be apart from globals (own)
        if fr and A == 1:
            if (op == 37 and D == 1) or (0 <= off and off + size <= fr):
                return st.fmem, 1, 'F'
            if off < fr and off + size > 0:
                bad('access across the edge of the stack frame')
        if own and A == 1 and ((op == 37 and D == 1) or 0 <= off):
            return st.mem, 0, 'F'                           # on the stack (this frame or above): no global
        return st.mem, 0, None

    def ea_x():
        return S(g[A] + g[B]) if A else g[B]

    def rec(v):
        st.cr[0] = cmpf(v, bv(0), True, st.so)

    def crbit(bi):
        k = 3 - (bi & 3)
        return z3.Extract(k, k, st.cr[bi >> 2])

    def setf(d, v, tag, *src):
        # The second paired-single slot of the target: some function of the result, of the
        # slot's old content and of the sources' slots (single-precision results are copied
        # into it, double-precision ones leave it alone; which one is not modelled).
        ins = [st.p[d], st.env] + [st.p[r] for r in src]
        st.p[d] = UF('ps1_' + tag, 64, v, *ins)
        st.f[d] = v

    def bcond(bo, bi):
        cs = []
        if not bo & 4:
            st.ctr = S(st.ctr - 1)
            cs.append(st.ctr == 0 if bo & 2 else st.ctr != 0)
        if not bo & 16:
            cs.append(crbit(bi) == (1 if bo & 8 else 0))
        return S(z3.And(*cs)) if cs else None

    if op == 14:
        g[D] = S(g[A] + simm) if A else bv(simm)
    elif op == 15:
        g[D] = S(g[A] + (simm << 16)) if A else bv(simm << 16)
    elif op in (12, 13):
        g[D], st.ca = add3(g[A], bv(simm), ZERO1)
        if op == 13:
            rec(g[D])
    elif op == 8:
        g[D], st.ca = add3(~g[A], bv(simm), ONE1)
    elif op == 7:
        g[D] = S(g[A] * simm)
    elif op in (10, 11):
        if D & 3:
            bad()
        st.cr[D >> 2] = cmpf(g[A], bv(uimm if op == 10 else simm), op == 11, st.so)
    elif op == 24:
        g[A] = S(g[D] | uimm)
    elif op == 25:
        g[A] = S(g[D] | (uimm << 16))
    elif op == 26:
        g[A] = S(g[D] ^ uimm)
    elif op == 27:
        g[A] = S(g[D] ^ (uimm << 16))
    elif op == 28:
        g[A] = S(g[D] & uimm)
        rec(g[A])
    elif op == 29:
        g[A] = S(g[D] & (uimm << 16))
        rec(g[A])
    elif op in (20, 21, 23):
        m = rmask((w >> 6) & 31, (w >> 1) & 31)
        if op == 23:
            rot = z3.RotateLeft(g[D], g[B] & 31)
        else:
            rot = z3.RotateLeft(g[D], B) if B else g[D]
        g[A] = S((rot & m) | (g[A] & (~m & M32))) if op == 20 else S(rot & m)
        if w & 1:
            rec(g[A])
    elif op in LOADS:
        size, sx, upd = LOADS[op]
        if upd and (A == 0 or A == D):
            bad()
        ea = ea_d()
        m, tag, cls = mm(simm, size)
        v = m.load(ea, size, cls)
        g[D] = v if size == 4 else S(z3.SignExt(32 - 8 * size, v) if sx else z3.ZeroExt(32 - 8 * size, v))
        if upd:
            g[A] = ea
    elif op in STORES:
        size, upd = STORES[op]
        if upd and A == 0:
            bad()
        ea = ea_d()
        v = g[D] if size == 4 else S(z3.Extract(8 * size - 1, 0, g[D]))
        m, tag, cls = mm(simm, size)
        m.store(ea, v, size, cls)
        st.stores.append((ea, size, v, tag))
        if upd:
            g[A] = ea
    elif op == 46:                                        # lmw
        if A == 0 or A >= D:
            bad()
        m, tag, cls = mm(simm, 4 * (32 - D))
        for k, r in enumerate(range(D, 32)):
            g[r] = m.load(S(g[A] + simm + 4 * k), 4, cls)
    elif op == 47:                                        # stmw
        base = g[A] if A else bv(0)
        m, tag, cls = mm(simm, 4 * (32 - D))
        for k, r in enumerate(range(D, 32)):
            ea = S(base + simm + 4 * k)
            m.store(ea, g[r], 4, cls)
            st.stores.append((ea, 4, g[r], tag))
    elif op in (48, 49, 50, 51):                          # lfs(u) lfd(u)
        if op & 1 and A == 0:
            bad()
        ea = ea_d()
        m, tag, cls = mm(simm, 4 if op < 50 else 8)
        setf(D, UF('s2d', 64, m.load(ea, 4, cls)) if op < 50 else m.load(ea, 8, cls), 'lf%d' % (op < 50))
        if op & 1:
            g[A] = ea
    elif op in (56, 60):                                  # psq_l / psq_st fD, d(rA), 0, qr0
        if w & 0xF000:
            bad('psq_l/psq_st other than W=0, GQR0')
        d12 = w & 0xFFF
        d12 = d12 - 0x1000 if d12 & 0x800 else d12
        ea = S((g[A] if A else bv(0)) + d12)
        m, tag, cls = mm(d12, 8)
        if op == 56:
            lo_ = m.load(S(ea + 4), 4, cls)
            v = UF('psq_l0', 64, m.load(ea, 4, cls), st.env)
            st.p[D] = UF('psq_l1', 64, lo_, st.env)
            st.f[D] = v
        else:
            v = S(z3.Concat(UF('psq_st0', 32, st.f[D], st.env), UF('psq_st1', 32, st.p[D], st.env)))
            m.store(ea, v, 8, cls)
            st.stores.append((ea, 8, v, tag))
    elif op in (52, 53, 54, 55):                          # stfs(u) stfd(u)
        if op & 1 and A == 0:
            bad()
        ea = ea_d()
        v, size = (UF('d2s', 32, st.f[D]), 4) if op < 54 else (st.f[D], 8)
        m, tag, cls = mm(simm, size)
        m.store(ea, v, size, cls)
        st.stores.append((ea, size, v, tag))
        if op & 1:
            g[A] = ea
    elif op == 18:
        if w & 2:
            bad()
        rel = w & 0x03FFFFFC
        t = (addr + (rel - (1 << 26) if rel & (1 << 25) else rel)) & M32
        if w & 1:
            return ('call', t)
        if lo <= t < hi:
            return ('jmp', (t - lo) >> 2)
        return ('tail', t)
    elif op == 16:
        if w & 3:
            bad()
        t = (addr + sext16(w & 0xFFFC)) & M32
        if not lo <= t < hi:
            bad('conditional branch out of the function')
        c = bcond(D, A)
        if c is None:
            return ('jmp', (t - lo) >> 2)
        return ('br', c, (t - lo) >> 2, i + 1)
    elif op == 19:
        xo = (w >> 1) & 1023
        if xo == 16:                                      # bclr
            if B:
                bad()
            c = bcond(D, A)
            if c is None:
                return ('call', 'lr') if w & 1 else ('ret',)
            if w & 1:
                bad()
            return ('br', c, RET, i + 1)
        if xo == 528:                                     # bcctr
            if D & 20 != 20 or B or not w & 1:
                bad('bctr without link (jump table / indirect tail call)')
            return ('call', 'ctr')
        if w & 1:
            bad()
        if xo == 0:                                       # mcrf
            if w & 0x0063F800:
                bad()
            st.cr[D >> 2] = st.cr[A >> 2]
        elif xo in (257, 449, 193, 225, 33, 289, 129, 417):
            a, b = crbit(A), crbit(B)
            v = {257: a & b, 449: a | b, 193: a ^ b, 225: ~(a & b), 33: ~(a | b), 289: ~(a ^ b),
                 129: a & ~b, 417: a | ~b}[xo]
            f = st.cr[D >> 2]
            k = D & 3
            parts = [z3.Extract(3 - j, 3 - j, f) if j != k else v for j in range(4)]
            st.cr[D >> 2] = S(z3.Concat(*parts))
        else:
            bad()
    elif op == 31:
        xo = (w >> 1) & 1023
        rc = w & 1
        if xo in (0, 32):                                 # cmp cmpl
            if D & 3 or rc:
                bad()
            st.cr[D >> 2] = cmpf(g[A], g[B], xo == 0, st.so)
        elif xo in XLOADS:
            if rc:
                bad()
            size, sx, upd = XLOADS[xo]
            if upd and (A == 0 or A == D):
                bad()
            ea = ea_x()
            v = st.mem.load(ea, size)
            g[D] = v if size == 4 else S(z3.SignExt(32 - 8 * size, v) if sx else z3.ZeroExt(32 - 8 * size, v))
            if upd:
                g[A] = ea
        elif xo in XSTORES:
            if rc:
                bad()
            size, upd = XSTORES[xo]
            if upd and A == 0:
                bad()
            ea = ea_x()
            v = g[D] if size == 4 else S(z3.Extract(8 * size - 1, 0, g[D]))
            st.mem.store(ea, v, size)
            st.stores.append((ea, size, v, 0))
            if upd:
                g[A] = ea
        elif xo in (535, 567, 599, 631):                  # lfsx lfsux lfdx lfdux
            if rc or (xo in (567, 631) and A == 0):
                bad()
            ea = ea_x()
            setf(D, UF('s2d', 64, st.mem.load(ea, 4)) if xo < 599 else st.mem.load(ea, 8), 'lf%d' % (xo < 599))
            if xo in (567, 631):
                g[A] = ea
        elif xo in (663, 695, 727, 759, 983):             # stfsx stfsux stfdx stfdux stfiwx
            if rc or (xo in (695, 759) and A == 0):
                bad()
            ea = ea_x()
            if xo == 983:
                v, size = S(z3.Extract(31, 0, st.f[D])), 4
            elif xo < 727:
                v, size = UF('d2s', 32, st.f[D]), 4
            else:
                v, size = st.f[D], 8
            st.mem.store(ea, v, size)
            st.stores.append((ea, size, v, 0))
            if xo in (695, 759):
                g[A] = ea
        elif xo == 339:                                   # mfspr
            spr = (A | B << 5)
            if rc or spr not in (8, 9):
                bad()
            g[D] = st.lr if spr == 8 else st.ctr
        elif xo == 467:                                   # mtspr
            spr = (A | B << 5)
            if rc or spr not in (8, 9):
                bad()
            if spr == 8:
                st.lr = g[D]
            else:
                st.ctr = g[D]
        elif xo == 19:                                    # mfcr
            if rc or A or B:
                bad()
            g[D] = S(z3.Concat(*st.cr))
        elif xo == 144:                                   # mtcrf
            if rc or w & 0x00100800:
                bad()
            fxm = (w >> 12) & 0xFF
            for k in range(8):
                if fxm & (0x80 >> k):
                    st.cr[k] = S(z3.Extract(31 - 4 * k, 28 - 4 * k, g[D]))
        else:
            a, b, s = g[A], g[B], g[D]
            tgt = D
            if xo == 266:
                v = a + b
            elif xo == 40:
                v = b - a
            elif xo == 104 and not B:
                v = -a
            elif xo == 235:
                v = a * b
            elif xo == 75:
                v = UFc('mulhw', 32, a, b)
            elif xo == 11:
                v = UFc('mulhwu', 32, a, b)
            elif xo == 491:
                v = UF('divw', 32, a, b)
            elif xo == 459:
                v = UF('divwu', 32, a, b)
            elif xo == 10:
                v, st.ca = add3(a, b, ZERO1)
            elif xo == 8:
                v, st.ca = add3(~a, b, ONE1)
            elif xo == 138:
                v, st.ca = add3(a, b, st.ca)
            elif xo == 136:
                v, st.ca = add3(~a, b, st.ca)
            elif xo == 202 and not B:
                v, st.ca = add3(a, bv(0), st.ca)
            elif xo == 200 and not B:
                v, st.ca = add3(~a, bv(0), st.ca)
            elif xo == 234 and not B:
                v, st.ca = add3(a, bv(M32), st.ca)
            elif xo == 232 and not B:
                v, st.ca = add3(~a, bv(M32), st.ca)
            else:
                tgt = A
                if xo == 28:
                    v = s & b
                elif xo == 60:
                    v = s & ~b
                elif xo == 444:
                    v = s | b
                elif xo == 412:
                    v = s | ~b
                elif xo == 316:
                    v = s ^ b
                elif xo == 476:
                    v = ~(s & b)
                elif xo == 124:
                    v = ~(s | b)
                elif xo == 284:
                    v = ~(s ^ b)
                elif xo == 24:
                    v = z3.If(z3.Extract(5, 5, b) == 1, bv(0), s << (b & 31))
                elif xo == 536:
                    v = z3.If(z3.Extract(5, 5, b) == 1, bv(0), z3.LShR(s, b & 31))
                elif xo == 792:
                    big = z3.Extract(5, 5, b) == 1
                    n = b & 31
                    sh = s >> n
                    lost = (s & ~(bv(M32) << n)) != 0
                    v = z3.If(big, s >> 31, sh)
                    st.ca = S(b1(z3.And(s < 0, z3.Or(z3.And(big, s != 0), z3.And(z3.Not(big), lost)))))
                elif xo == 824:
                    v = s >> B
                    st.ca = S(b1(z3.And(s < 0, (s & ((1 << B) - 1)) != 0)))
                elif xo == 26 and not B:
                    v = UF('cntlzw', 32, s)
                elif xo == 922 and not B:
                    v = z3.SignExt(16, z3.Extract(15, 0, s))
                elif xo == 954 and not B:
                    v = z3.SignExt(24, z3.Extract(7, 0, s))
                else:
                    bad()
            v = S(v)
            g[tgt] = v
            if rc:
                rec(v)
    elif op in (59, 63):
        f = st.f
        xo5 = (w >> 1) & 31
        xo = (w >> 1) & 1023
        C = (w >> 6) & 31
        if w & 1:
            bad('record-form FP instruction')
        if xo5 in FOPS and (op == 63 or xo5 != 0):
            name, order = FOPS[xo5]
            used = {'ab': (A, B), 'ac': (A, C), 'acb': (A, C, B)}[order]
            if ('b' not in order and B) or ('c' not in order and C):
                bad()
            name += 's' if op == 59 else ''
            if FPCOMM and xo5 != 18 and xo5 != 20 and f[used[0]].get_id() > f[used[1]].get_id():
                used = (used[1], used[0]) + used[2:]        # fadd / fmul / the factors of fmadd..
            setf(D, UF(name, 64, *([f[r] for r in used] + [st.env])), name, *used)
        elif op == 59 and xo5 == 24 and not A and not C:
            setf(D, UF('fres', 64, f[B], st.env), 'fres', B)
        elif op == 63 and xo5 == 26 and not A and not C:
            setf(D, UF('frsqrte', 64, f[B], st.env), 'frsqrte', B)
        elif op == 63 and xo5 == 23:
            setf(D, UF('fsel', 64, f[A], f[C], f[B]), 'fsel', A, C, B)
        elif op == 63 and xo in (0, 32):
            if D & 3:
                bad()
            st.cr[D >> 2] = UF('fcmpu' if xo == 0 else 'fcmpo', 4, f[A], f[B])
        elif op == 63 and xo in (12, 14, 15) and not A:
            name = {12: 'frsp', 14: 'fctiw', 15: 'fctiwz'}[xo]
            setf(D, UF(name, 64, f[B], st.env), name, B)
        elif op == 63 and xo == 72 and not A:
            setf(D, f[B], 'fmr', B)
        elif op == 63 and xo == 40 and not A:
            setf(D, S(f[B] ^ SIGN64), 'fneg', B)
        elif op == 63 and xo == 264 and not A:
            setf(D, S(f[B] & (SIGN64 - 1)), 'fabs', B)
        elif op == 63 and xo == 136 and not A:
            setf(D, S(f[B] | SIGN64), 'fnabs', B)
        else:
            bad()
    else:
        bad()
    return None


class Side:
    def __init__(self, words, addr):
        self.words = words
        self.addr = addr
        self.n = len(words)
        self.end = addr + 4 * self.n
        self.headers = self._headers()
        self.joins = self._joins()
        self.fr = [0] * self.n                              # own frame as a memory of its own
        self.own = [0] * self.n                             # own frame known apart from globals
        self.frame = self._frame()
        self.noescape = not E.SchedCtx._escapes(words)

    def _frame(self):
        """(per-instruction flag: r1 is the function's own frame pointer, frame size) as
        equivcheck.SchedCtx._frame, over this version's own control flow; None when r1 is
        written by anything but stwu r1,-N(r1) / addi r1,r1,N / lwz r1,0(r1)."""
        n = self.n
        st = [None] * n
        if not n:
            return None
        st[0] = False
        size = None
        work = [0]
        alloc = set()
        while work:
            i = work.pop()
            w = self.words[i]
            cur = st[i]
            if E.SchedCtx._wmask(w) & 2:
                if w >> 16 == 0x9421 and w & 0x8000 and not cur and size in (None, 0x10000 - (w & 0xFFFF)):
                    size = 0x10000 - (w & 0xFFFF)
                    cur = True
                    alloc.add(i)
                elif cur and (w == 0x38210000 | size or w == 0x80210000) and size < 0x8000:
                    cur = False
                else:
                    return None
            for t in self._succ(i):
                if t >= n:
                    continue
                if st[t] is None:
                    st[t] = cur
                    work.append(t)
                elif st[t] != cur:
                    return None
        if not size:
            return None
        return [size if (st[i] or i in alloc) else 0 for i in range(n)], size

    def use_frame(self, apart):
        self.own = self.frame[0]
        if apart:
            self.fr = self.frame[0]

    def _succ(self, i):
        w = self.words[i]
        op = w >> 26
        a = self.addr + 4 * i
        if op == 18:
            rel = w & 0x03FFFFFC
            t = (a + (rel - (1 << 26) if rel & (1 << 25) else rel)) & M32
            if w & 1:
                return [i + 1]
            return [(t - self.addr) >> 2] if self.addr <= t < self.end else []
        if op == 16:
            t = (a + sext16(w & 0xFFFC)) & M32
            if not self.addr <= t < self.end:
                return []
            ti = (t - self.addr) >> 2
            return [ti] if (w >> 21) & 20 == 20 else [ti, i + 1]
        if op == 19 and (w >> 1) & 1023 in (16, 528):
            return [i + 1] if w & 1 or (w >> 21) & 20 != 20 else []
        return [i + 1]

    def _joins(self):
        """Instructions with more than one predecessor (reachable code only)."""
        n = self.n
        preds = [0] * n
        seen = [False] * n
        work = [0] if n else []
        while work:
            i = work.pop()
            if seen[i]:
                continue
            seen[i] = True
            for t in set(self._succ(i)):
                if t < n:
                    preds[t] += 1
                    work.append(t)
        return set(i for i in range(n) if preds[i] > 1) - self.headers

    def _headers(self):
        """Targets of the retreating edges of a depth-first walk: every cycle has one."""
        n = self.n
        color = [0] * n
        heads = set()
        stack = [(0, iter(self._succ(0)))] if n else []
        if n:
            color[0] = 1
        while stack:
            i, it = stack[-1]
            for t in it:
                if t >= n:
                    continue
                if color[t] == 0:
                    color[t] = 1
                    stack.append((t, iter(self._succ(t))))
                    break
                if color[t] == 1:
                    heads.add(t)
            else:
                color[i] = 2
                stack.pop()
        return heads


class Cur:
    __slots__ = ('sd', 'st', 'i', 'first', 'stop')

    def __init__(self, sd, st, i, first):
        self.sd, self.st, self.i, self.first, self.stop = sd, st, i, first, None

    def fork(self):
        c = Cur(self.sd, self.st.copy(), self.i, self.first)
        c.stop = self.stop
        return c


class StubEnv:
    """Most conservative callee facts (synthetic tests)."""

    def is_fn(self, t):
        return True

    def inputs_of(self, t):
        return E.ARGS_ALL

    def thru_of(self, t):
        return E.VOL

    def retuse(self, a):
        return E.RETREGS


class ProgEnv:
    def __init__(self, prog):
        self.prog = prog
        self.sda = dict(prog.sda)
        prog._solve_webs()

    def is_fn(self, t):
        return t in self.prog.fns

    def inputs_of(self, t):
        return self.prog.inputs_of(t)

    def thru_of(self, t):
        return self.prog.thru_of(t)

    def retuse(self, a):
        return self.prog.retuse(a)


VOL_LOCS = mask_locs(E.VOL) + [('p', i) for i in range(14)]
NONVOL_LOCS = mask_locs(E.NONVOL) + [('p', i) for i in range(14, 32)]
KEEP_LOCS = [('r', 1), ('r', 2), ('r', 13)]
ALL = [(s, l) for s in 'ou' for l in LOCS]


def normalize(raw):
    out, idx = {}, {}
    for k in ALL:
        lab = raw[k]
        if isinstance(lab, tuple) and lab[0] == 'k':
            out[k] = lab
        else:
            out[k] = idx.setdefault(lab, len(idx))
    return out


class Checker:
    def __init__(self, env, addr, owords, uwords, steps=200000, paths=4000, timeout=5000, frame=False,
                 ro=None, leftover=False, joins=False, limit=None):
        self.env = env
        self.joins = joins                                  # every join of the CFG is a cut point as well
        self.deadline = time.time() + limit if limit else None
        self.ro = ro
        # Rule 'leftover' (assumption of equivcheck rule d): what a call leaves in a volatile
        # register other than r3/r4/f1 is garbage that only matters when this function reads
        # it with its own instructions, or a caller does after the return, before it is
        # written again (Fn.xlive of both versions: a later call that can pass the register
        # through does not end its life, a later callee that "may read" it does not count).
        self.left = None
        if leftover:
            fo, fu = E.Fn('o', addr, owords), E.Fn('u', addr, uwords)
            if not fo.opaque and not fu.opaque:
                ru = env.retuse(addr)
                self.left = (fo.xlive(ru, env.thru_of) + [0], fu.xlive(ru, env.thru_of) + [0])
        self.addr = addr
        self.o = Side(owords, addr)
        self.u = Side(uwords, addr)
        self.alias = bool(frame)
        self.frame = False
        if frame and self.o.frame and self.u.frame:         # rules 'global' / 'pointer' of equivcheck rule f
            self.frame = self.o.noescape and self.u.noescape
            self.o.use_frame(self.frame)
            self.u.use_frame(self.frame)
        self.budget = steps
        self.paths = paths
        self.solver = z3.Solver()
        self.timeout = timeout
        self.solver.set('timeout', timeout)
        self.nodes = {}
        self.meta = {}
        self.fresh = 0
        self.stats = {'nodes': 0, 'explore': 0, 'paths': 0, 'solver': 0}

    # ---- solver ----------------------------------------------------------
    def feasible(self, pc):
        """False only when the path condition is proved contradictory (short time-out:
        an undecided path counts as possible and has to pass every check)."""
        if not pc:
            return True
        self.stats['solver'] += 1
        s = self.solver
        s.set('timeout', 1500)
        s.push()
        s.add(*pc)
        r = s.check()
        s.pop()
        s.set('timeout', self.timeout)
        return r != z3.unsat

    def prove(self, pc, claim_false):
        """True when pc and claim_false cannot hold together."""
        self.stats['solver'] += 1
        s = self.solver
        s.push()
        s.add(*pc)
        s.add(claim_false)
        r = s.check()
        s.pop()
        return r == z3.unsat

    def var(self, loc):
        self.fresh += 1
        srt = loc_sort(loc)
        return z3.Const('v%d_%s' % (self.fresh, loc_name(loc)), srt)

    # ---- driver ----------------------------------------------------------
    def run(self):
        global RO, ALIAS
        RO, ALIAS = self.ro, self.alias
        try:
            return self._run()
        finally:
            RO, ALIAS = None, False

    def _run(self):
        for sd, who in ((self.o, 'original'), (self.u, 'ours')):
            for w in sd.words:
                if w >> 26 == 15 and (w & 0xFFFF) in E.HWHI:
                    raise Reject('hardware address in %s' % who)
        entry = {k: LOCS.index(k[1]) for k in ALL}
        for r, v in getattr(self.env, 'sda', {}).items():   # r13 / r2 always hold the small-data bases
            entry[('o', ('r', r))] = entry[('u', ('r', r))] = ('k', 32, v)
        key = ('E', 0, 0)
        self.nodes[key] = normalize(entry)
        self.meta[key] = None
        work = [key]
        while work:
            key = work.pop()
            self.stats['explore'] += 1
            if self.stats['explore'] > 3000:
                raise Reject('too many cut-point explorations')
            self.pending = []
            self.explore(key)
            for k2, part, meta, pc in self.pending:
                old = self.nodes.get(k2)
                if old is None:
                    if not self.feasible(pc):
                        continue
                    self.nodes[k2] = part
                    self.meta[k2] = meta
                    work.append(k2)
                    continue
                raw = {}
                for k in ALL:
                    a, b = old[k], part[k]
                    raw[k] = a if a == b and isinstance(a, tuple) else (a, b)
                new = normalize(raw)
                if new != old and self.feasible(pc):
                    self.nodes[k2] = new
                    if k2 not in work:
                        work.append(k2)
        self.stats['nodes'] = len(self.nodes)
        return True

    def explore(self, key):
        part = self.nodes[key]
        vals = {}
        sts = {}
        for side in 'ou':
            st = St()
            st.g, st.f, st.p, st.cr = [None] * 32, [None] * 32, [None] * 32, [None] * 8
            st.stores = []
            for loc in LOCS:
                lab = part[(side, loc)]
                if isinstance(lab, tuple):
                    v = bv(lab[2], lab[1])
                else:
                    v = vals.get(lab)
                    if v is None:
                        v = vals[lab] = self.var(loc)
                st.set(loc, v)
            sts[side] = st
        kind, io, iu = key
        first = True
        if kind == 'C':
            t = self.meta[key]
            thru = self.env.thru_of(t if isinstance(t, int) else None)
            if part[('o', 'mem')] != part[('u', 'mem')] or part[('o', 'fmem')] != part[('u', 'fmem')]:
                raise Reject('internal: memory differs at a call')
            for loc in VOL_LOCS + ['ctr', 'ca', 'so', 'env']:
                pre = part[('o', loc)] == part[('u', loc)]
                if isinstance(loc, tuple):
                    bit = {'r': E.GP, 'f': E.FP, 'p': E.FP, 'cr': E.CRF}[loc[0]] + loc[1]
                    shared = pre or not thru >> bit & 1
                    if not shared and self.left and not E.RETREGS >> bit & 1:
                        shared = not (self.left[0][io + 1] | self.left[1][iu + 1]) >> bit & 1
                else:
                    shared = pre
                v = self.var(loc)
                sts['o'].set(loc, v)
                sts['u'].set(loc, v if shared else self.var(loc))
                if DEBUG and not shared and loc[0] != 'p':
                    print('DEBUG call at %08x/%08x to %s: %s not the same before, may pass through' % (
                        self.o.addr + 4 * key[1], self.u.addr + 4 * key[2],
                        '%08x' % t if isinstance(t, int) else t, loc_name(loc)))
            sts['o'].lr = self.var('lr')
            sts['u'].lr = self.var('lr')
            for loc in ('mem', 'fmem'):
                m = self.var(loc)
                sts['o'].set(loc, m)
                sts['u'].set(loc, m)
            io, iu, first = io + 1, iu + 1, False
        a = Cur(self.o, sts['o'], io, first)
        b = Cur(self.u, sts['u'], iu, first)
        self.tandem(a, b, [], frozenset())

    def advance(self, c):
        sd, st = c.sd, c.st
        i = c.i
        first = c.first
        c.first = False
        while True:
            if not first and i in sd.headers:
                c.i = i
                return ('loop',)
            if not first and self.joins and i in sd.joins:
                c.i = i
                return ('join',)
            first = False
            if i >= sd.n:
                raise Reject('execution falls off the end of the function')
            self.budget -= 1
            if self.budget < 0:
                raise Reject('step budget exhausted (too many paths between cut points)')
            if self.deadline and not self.budget & 255 and time.time() > self.deadline:
                raise Reject('time limit')
            r = step(st, sd.words[i], sd.addr + 4 * i, sd.addr, sd.end, sd.fr[i], sd.own[i])
            if r is None:
                i += 1
            elif r[0] == 'jmp':
                i = r[1]
            else:
                c.i = i
                return r

    def tandem(self, a, b, pc, pcset):
        while True:
            for c in (a, b):
                if c.stop is None:
                    c.stop = self.advance(c)
            for c in (a, b):
                if c.stop[0] != 'br':
                    continue
                _k, cond, tt, tf = c.stop
                ncond = S(z3.Not(cond))
                for cnd, neg, tgt in ((cond, ncond, tt), (ncond, cond, tf)):
                    if z3.is_false(cnd) or neg.get_id() in pcset:
                        continue
                    c2 = c.fork()
                    if tgt == RET:
                        c2.stop = ('ret',)
                    else:
                        c2.i, c2.stop = tgt, None
                    oth = (b if c is a else a).fork()
                    if z3.is_true(cnd) or cnd.get_id() in pcset:
                        npc, nset = pc, pcset
                    else:
                        npc, nset = pc + [cnd], pcset | {cnd.get_id()}
                    if c is a:
                        self.tandem(c2, oth, npc, nset)
                    else:
                        self.tandem(oth, c2, npc, nset)
                return
            ka, kb = a.stop[0], b.stop[0]
            if ka == 'join' and kb not in ('join', 'loop'):  # a join is a cut point only together with one
                a.stop, a.first = None, True
                continue
            if kb == 'join' and ka not in ('join', 'loop'):
                b.stop, b.first = None, True
                continue
            self.arrive(a, b, pc)
            return

    def where(self, a, b):
        return 'orig %08x / ours %08x' % (self.o.addr + 4 * a.i, self.u.addr + 4 * b.i)

    def arrive(self, a, b, pc):
        self.stats['paths'] += 1
        if self.stats['paths'] > self.paths:
            raise Reject('path budget exhausted')
        try:
            self._arrive(a, b, pc)
        except Reject:
            if self.feasible(pc):                           # a failure on an impossible path is none
                raise

    def _arrive(self, a, b, pc):
        ka, kb = a.stop, b.stop
        at = self.where(a, b)
        kind, kind2 = ['loop' if k[0] == 'join' else k[0] for k in (ka, kb)]
        if kind != kind2:
            raise Reject('control flow differs: original at a %s, ours at a %s (%s)' % (ka[0], kb[0], at))
        so, su = a.st, b.st
        req = []
        tgt = None
        if kind in ('call', 'tail'):
            tgt = ka[1]
            if tgt != kb[1]:
                raise Reject('call target differs (%s)' % at)
            if isinstance(tgt, int):
                if not self.env.is_fn(tgt):
                    raise Reject('call to %08x, not a function start (%s)' % (tgt, at))
                req += mask_locs(self.env.inputs_of(tgt) & E.VOL)   # callee-saved registers are no inputs
            else:
                req += mask_locs(E.ARGS_ALL) + [tgt]
            req += KEEP_LOCS
        if kind in ('ret', 'tail'):
            req += NONVOL_LOCS + KEEP_LOCS + ['lr']
        if kind == 'ret':
            req += mask_locs(E.R3 | self.env.retuse(self.addr))
        req += ['mem', 'fmem']
        # stores: one-to-one
        la, lb = so.stores, su.stores
        if len(la) != len(lb):
            raise Reject('%d stores in the original, %d in ours before %s' % (len(la), len(lb), at))
        inorder = so.mem.base.eq(su.mem.base) and so.fmem.base.eq(su.fmem.base) and \
            all(x[1] == y[1] and x[3] == y[3] and x[0].eq(y[0]) and x[2].eq(y[2]) for x, y in zip(la, lb))
        if not inorder:
            left = list(lb)
            rest = []
            for x in la:
                for k, y in enumerate(left):
                    if x[1] == y[1] and x[3] == y[3] and x[0].eq(y[0]) and x[2].eq(y[2]):
                        del left[k]
                        break
                else:
                    rest.append(x)
            for x in rest:
                cand = sorted(range(len(left)), key=lambda k: not left[k][0].eq(x[0]))
                for k in cand[:4]:
                    y = left[k]
                    if x[1] == y[1] and x[3] == y[3] and self.prove(pc, z3.Or(x[0] != y[0], x[2] != y[2])):
                        del left[k]
                        break
                else:
                    if DEBUG:
                        print('DEBUG store %s\n  orig: %s\n  ours left: %s' % (at, str(x)[:1500], str(left)[:3000]))
                    raise Reject('a store of the original has no counterpart in ours before %s' % at)
        proved = []
        seen = set()
        for loc in req:
            if loc in seen:
                continue
            seen.add(loc)
            x, y = so.get(loc), su.get(loc)
            if x.eq(y):
                continue
            if loc in ('mem', 'fmem') and (inorder or same_stores(getattr(so, loc), getattr(su, loc))):
                pass                                        # same stores on the same array, order immaterial
            elif not self.prove(pc, x != y):
                if DEBUG and loc in ('mem', 'fmem'):
                    for who, st_ in (('orig', so), ('ours', su)):
                        print('DEBUG %s stores of %s:' % (loc, who))
                        for e in getattr(st_, loc).log:
                            print('   %s+%d size %d class %s value %s' % (
                                str(e[0]).replace('\n', ' ')[:60], e[1] - (1 << 32 if e[1] >> 31 else 0), e[2], e[5],
                                str(e[3]).replace('\n', ' ')[:100]))
                elif DEBUG:
                    print('DEBUG %s at %s\n  orig: %s\n  ours: %s\n  pc: %s' % (
                        loc_name(loc), at, str(x)[:3000], str(y)[:3000], str(pc)[:1500]))
                raise Reject('%s differs at the %s (%s)' % (loc_name(loc), kind, at))
            elif DEBUG:
                print('DEBUG solver proved %s at %s' % (loc_name(loc), at))
            proved.append(loc)
        if kind in ('ret', 'tail'):
            return
        # relation: registers of both versions that hold the same term
        raw = {}
        parent = {}

        def find(x):
            while x in parent:
                x = parent[x]
            return x
        for side, st in (('o', so), ('u', su)):
            for loc in LOCS:
                t = st.get(loc)
                if z3.is_bv_value(t):
                    raw[(side, loc)] = ('k', t.size(), t.as_long())
                else:
                    raw[(side, loc)] = t.get_id()
        for loc in proved:
            x, y = find(raw[('o', loc)]), find(raw[('u', loc)])
            if x != y:
                if isinstance(y, tuple):
                    x, y = y, x
                parent[y] = x
        for k in raw:
            raw[k] = find(raw[k])
        key = ('C' if kind == 'call' else 'L', a.i, b.i)
        self.pending.append((key, normalize(raw), tgt, pc))


def check_pair(env, addr, owords, uwords, **kw):
    """(True, stats text) or (False, reason). When the paths between the cut points are too
    many, a second attempt cuts at every join of the control flow as well (sound, but an
    instruction that moved across a join is then no longer followed)."""
    t0 = time.time()
    limit = kw.pop('limit', None)
    for joins in (False, True):
        if limit:                                           # the first attempt gets 40% of the time
            kw['limit'] = max(limit - (time.time() - t0), 5) if joins else 0.4 * limit
        c = Checker(env, addr, owords, uwords, joins=joins, **kw)
        try:
            c.run()
            break
        except Reject as e:
            if joins or not ('budget' in str(e) or (limit and str(e) == 'time limit')):
                return False, str(e) + (' [with cuts at joins]' if joins else '')
        except z3.Z3Exception as e:
            return False, 'z3: %s' % e
    return True, 'proved (%d cut points, %d paths, %d solver calls%s%s%s)' % (
        c.stats['nodes'], c.stats['paths'], c.stats['solver'], ', frame rule' if c.frame else '',
        ', leftover rule' if c.left else '', ', fp-commute' if FPCOMM else '') + \
        (' [cuts at joins]' if c.joins else '')


# ---- our object: relocations resolved to addresses of the original ------------

class UObj(E.Obj):
    def __init__(self, path):
        E.Obj.__init__(self, path)
        d = self.d
        strndx, = struct.unpack('>H', d[0x32:0x34])
        so = self.sh[strndx][4]
        self.secname = [d[so + s[0]:d.index(b'\0', so + s[0])].decode('latin1') for s in self.sh]
        self.symsize = []
        for s in self.sh:
            if s[1] == 2:
                for o in range(s[4], s[4] + s[5], 16):
                    self.symsize.append(struct.unpack('>3I2BH', d[o:o + 16])[2])


def load_secs(P):
    """unit -> {section name: [(start, end)]} from splits.txt."""
    out = {}
    cur = None
    for line in open(P['splits']):
        if line and not line[0].isspace() and line.rstrip().endswith(':'):
            cur = out.setdefault(os.path.splitext(line.rstrip()[:-1])[0], {})
        m = re.match(r'\s+(\S+)\s+start:0x([0-9A-Fa-f]+) end:0x([0-9A-Fa-f]+)', line)
        if m and cur is not None:
            cur.setdefault(m.group(1), []).append((int(m.group(2), 16), int(m.group(3), 16)))
    return out


def sda_reg(prog, v):
    """13 / 2 for an address inside .sdata/.sbss / .sdata2/.sbss2 (extent of the symbols
    of symbols.txt in those sections), else None."""
    rng = getattr(prog, 'sdarng', None)
    if rng is None:
        rng = prog.sdarng = {}
        rx = re.compile(r'^\S+ = (\.s(?:data|bss)2?):0x([0-9A-Fa-f]+);(?:.*size:0x([0-9A-Fa-f]+))?')
        for line in open(prog.symfile):
            m = rx.match(line)
            if m:
                a = int(m.group(2), 16)
                e = a + int(m.group(3) or '0', 16)
                lo, hi = rng.get(m.group(1), (a, e))
                rng[m.group(1)] = (min(lo, a), max(hi, e))
    hit = [13 if not sec.endswith('2') else 2 for sec, (lo, hi) in rng.items() if lo <= v <= hi]
    return hit[0] if len(set(hit)) == 1 else None


def our_words(prog, secs, unit, obj, name):
    """Words of our function `name` as if linked at the original address, every relocation
    resolved to the address the original uses for that symbol. Raises Reject."""
    fn = prog.byname.get(name)
    if fn is None or name not in obj.funcs:
        raise Reject('missing')
    shndx, val, size = obj.funcs[name]
    base = obj.sh[shndx][4] + val
    words = list(struct.unpack('>%dI' % (size // 4), obj.d[base:base + size]))
    fakes = {}                                              # section index -> (pseudo address, bytes)
    for off, lst in sorted(obj.rel.get(shndx, {}).items()):
        if not val <= off < val + size:
            continue
        i = (off - val) // 4
        for ty, sidx, add in lst:
            sname, _bind, sshndx, sval = obj.syms[sidx]
            known = prog.symaddr.get(sname, ())
            intext = 0 < sshndx < 0xFF00 and obj.secname[sshndx] == '.text'
            byname = sshndx == 0 or intext or (_bind != 0 and sshndx < 0xFF00)
            if byname and len(known) == 1 and not sname.startswith('@'):
                target = next(iter(known))
            elif intext and sshndx == shndx and val <= sval + add < val + size:
                target, add = fn.addr + sval - val, add     # a place inside this function
            elif intext and [n for n, f in obj.funcs.items() if f[0] == sshndx and f[1] == sval + add and
                             len(prog.symaddr.get(n, ())) == 1]:
                n = [n for n, f in obj.funcs.items() if f[0] == sshndx and f[1] == sval + add and
                     len(prog.symaddr.get(n, ())) == 1][0]
                target, add = next(iter(prog.symaddr[n])), 0  # the start of another function of the unit
            elif byname or sshndx >= 0xFF00:
                raise Reject('relocation against unknown symbol %s' % sname)
            else:                                           # local symbol of our object
                sec = obj.secname[sshndx]
                rng = secs.get(unit, {}).get(sec, ())
                shdr = obj.sh[sshndx]
                tied = len(rng) == 1 and shdr[5] <= rng[0][1] - rng[0][0]
                if tied and shdr[1] == 1:                   # PROGBITS: the bytes must be the original's
                    n = obj.symsize[sidx]
                    lo, hi = (sval, sval + n) if n else (0, shdr[5])
                    off0 = prog.dol.find(rng[0][0])
                    mine = bytearray(obj.d[shdr[4] + lo:shdr[4] + hi])
                    theirs = bytearray(prog.dol.data[off0 + lo:off0 + hi]) if off0 is not None else None
                    for ro in obj.rel.get(sshndx, {}):          # words the linker fills in are not compared
                        if lo <= ro < hi and theirs is not None:
                            mine[ro - lo:ro - lo + 4] = theirs[ro - lo:ro - lo + 4]
                    tied = theirs is not None and mine == theirs
                if tied:
                    target = rng[0][0] + sval
                elif sec in ('.sdata2', '.rodata') and shdr[1] == 1 and not obj.rel.get(sshndx):
                    # A read-only literal without a place in the original: it gets a pseudo
                    # address; only its bytes are known (loads fold to them), as an address
                    # it equals nothing of the original.
                    if sshndx not in fakes:
                        a = 0x1000 + sum((len(d) + 15) & ~7 for _a, d in fakes.values())
                        if a + shdr[5] > 0x7FF0:
                            raise Reject('read-only literals of %s too large' % sec)
                        fakes[sshndx] = (a, obj.d[shdr[4]:shdr[4] + shdr[5]])
                    target = fakes[sshndx][0] + sval
                else:
                    raise Reject('local symbol %s in %s cannot be tied to the original' % (sname or '(section)', sec))
            v = (target + add) & M32
            p = fn.addr + 4 * i
            w = words[i]
            if ty == 4:
                w = (w & ~0xFFFF) | (v & 0xFFFF)
            elif ty == 5:
                w = (w & ~0xFFFF) | (v >> 16)
            elif ty == 6:
                w = (w & ~0xFFFF) | (((v + 0x8000) >> 16) & 0xFFFF)
            elif ty == 10:
                d = (v - p) & M32
                if d & 3 or not (d < 0x02000000 or d >= 0xFE000000):
                    raise Reject('branch out of range')
                w = (w & ~0x03FFFFFC) | (d & 0x03FFFFFC)
            elif ty == 11:
                d = (v - p) & M32
                if d & 3 or not (d < 0x8000 or d >= 0xFFFF8000):
                    raise Reject('branch out of range')
                w = (w & ~0xFFFC) | (d & 0xFFFC)
            elif ty == 109:
                if v < 0x8000:                              # pseudo address: base "register" 0
                    w = (w & ~0x001FFFFF) | v
                else:
                    r = sda_reg(prog, v)
                    if r is None or r not in prog.sda or not (v - prog.sda[r] + 0x8000) & M32 < 0x10000:
                        raise Reject('SDA21 relocation: target %08x is not in a small-data section' % v)
                    w = (w & ~0x001FFFFF) | r << 16 | ((v - prog.sda[r]) & 0xFFFF)
            else:
                raise Reject('unsupported relocation type %d' % ty)
            words[i] = w
    return words, sorted(fakes.values())


class Alarm(Exception):
    pass


def _alarm(_s, _f):
    raise Alarm()


def check_fn(prog, env, secs, unit, obj, name, limit=120, **kw):
    """(proved, text, size of ours). kw: frame=True for the frame rule."""
    fn = prog.byname.get(name)
    try:
        ours, fakes = our_words(prog, secs, unit, obj, name)
    except Reject as e:
        return False, str(e), 0
    if ours == fn.words:
        return True, 'exact', 0
    kw['ro'] = RoData(prog, fakes)
    signal.signal(signal.SIGALRM, _alarm)
    signal.alarm(limit + 30)
    try:
        ok, text_ = check_pair(env, fn.addr, fn.words, ours, limit=limit, **kw)
        if ok and fakes:
            text_ += ' [read-only literals of our object matched by content, not by address]'
    except (Alarm, ctypes.ArgumentError) as e:              # (the alarm may surface inside a z3 call)
        ok, text_ = False, 'time limit (%ds) %s' % (limit, type(e).__name__)
    except RecursionError:
        ok, text_ = False, 'recursion limit'
    finally:
        signal.alarm(0)
    return ok, text_, len(ours) * 4


def paths(v):
    return {
        'build': os.path.join(ROOT, 'build', v),
        'orig': os.path.join(ROOT, 'orig', v, 'sys', 'main.dol'),
        'syms': os.path.join(ROOT, 'config', v, 'symbols.txt'),
        'splits': os.path.join(ROOT, 'config', v, 'splits.txt'),
        'allow': os.path.join(ROOT, 'config', v, 'funcequiv.txt'),
    }


class _A:
    strict = False


def setup(P):
    prog = E.load_program(_A, P)
    prog.symfile = P['syms']
    return prog, ProgEnv(prog), load_secs(P), E.load_units(P)


def unit_of(units, a):
    return next((u for u, s, e in units if s <= a < e), None)


def list_mode(args, P, names=None):
    prog, env, secs, units = setup(P)
    rc = 0
    todo = []
    for arg in (names if names is not None else args.list):
        unit, _, only = arg.partition(':')
        if not only and unit in prog.byname:
            only = unit
            unit = unit_of(units, prog.byname[unit].addr)
        todo.append((unit, set(only.split(',')) if only else None))
    objs = {}
    for unit, want in todo:
        try:
            obj = objs.get(unit) or UObj(os.path.join(P['build'], 'src', unit + '.o'))
        except (OSError, TypeError) as e:
            print('FAIL %s: %s' % (unit, e))
            rc = 1
            continue
        objs[unit] = obj
        for name in sorted(obj.funcs, key=lambda k: obj.funcs[k][1]):
            if (want and name not in want) or name not in prog.byname:
                continue
            t0 = time.time()
            ok, text_, size = check_fn(prog, env, secs, unit, obj, name, limit=args.limit, frame=args.frame, leftover=args.leftover)
            if not ok:
                rc = 1
            if text_ != 'exact' or want or args.verbose:
                print('%s %s %s: %s [%d vs %d bytes, %.1fs]' % (
                    'PASS' if ok else 'FAIL', unit, name, text_, 4 * prog.byname[name].n, size, time.time() - t0))
            sys.stdout.flush()
    return rc


# ---- --selftest -----------------------------------------------------------

def _I(op, d, a, imm):
    return op << 26 | d << 21 | a << 16 | (imm & 0xFFFF)


def _X(xo, d, a, b, rc=0):
    return 31 << 26 | d << 21 | a << 16 | b << 11 | xo << 1 | rc


NOP = 0x60000000
BLR = 0x4E800020


class Asm:
    def __init__(self, addr=0x80400000):
        self.addr = addr
        self.items = []
        self.labels = {}

    def w(self, *ws):
        self.items.extend(ws)

    def label(self, name):
        self.labels[name] = len(self.items)

    def b(self, name):
        self.items.append(('b', name))

    def bc(self, bo, bi, name):
        self.items.append(('bc', bo, bi, name))

    def bl(self, target):
        self.items.append(('bl', target))

    def words(self):
        out = []
        for i, it in enumerate(self.items):
            if isinstance(it, int):
                out.append(it)
            elif it[0] == 'b':
                out.append(18 << 26 | ((self.labels[it[1]] - i) * 4 & 0x03FFFFFC))
            elif it[0] == 'bc':
                out.append(16 << 26 | it[1] << 21 | it[2] << 16 | ((self.labels[it[3]] - i) * 4 & 0xFFFC))
            else:
                out.append(18 << 26 | ((it[1] - self.addr - 4 * i) & 0x03FFFFFC) | 1)
        return out


def li(d, v): return _I(14, d, 0, v)
def addi(d, a, v): return _I(14, d, a, v)
def mr(a, s): return _X(444, s, a, s)
def lwz(d, off, a): return _I(32, d, a, off)
def stw(s, off, a): return _I(36, s, a, off)
def add(d, a, b): return _X(266, d, a, b)


def synth(v=''):
    """One hand-made function; v selects a variant (see SYNTH_POS / SYNTH_NEG)."""
    a = Asm()
    v = v.split('+')
    P, N, C = (30, 29, 31) if 'regswap' in v else (31, 30, 29)
    a.w(_I(37, 1, 1, -48), 0x7C0802A6, stw(0, 52, 1), stw(31, 44, 1), stw(30, 40, 1), stw(29, 36, 1), stw(28, 32, 1))
    a.w(mr(P, 3), mr(N, 4))
    if 'hoist' in v:
        a.w(li(6, 3))
    a.w(li(C, 1 if 'offbyone' in v else 0))
    if 'bigger' in v:
        a.w(mr(5, 5), NOP)
    a.w(_I(11, 0, N, 0))                                  # cmpwi N,0
    a.bc(4, 1, 'skip')                                    # ble
    a.w(lwz(5, 20, P), addi(5, 5, 1), stw(5, 20, P))
    a.label('skip')
    if 'hoist' not in v:
        a.w(li(6, 3))
    a.w(stw(6, 24, P))
    a.b('cond')
    a.label('loop')
    if 'loadcall' not in v:
        a.w(lwz(28, 8, P))
    if 'swapargs' in v:
        a.w(lwz(4, 0, P), add(4, 4, C), li(3, 7))
    elif 'sched' in v:
        a.w(li(4, 7), lwz(3, 0, P), add(3, C, 3))
    else:
        a.w(lwz(3, 0, P), add(3, 3, C), li(4, 8 if 'const' in v else 7))
    a.bl(0x80300000 if 'target' not in v else 0x80300100)
    if 'loadcall' in v:
        a.w(lwz(28, 8, P))
    s1, s2, s3 = stw(3, 4, P), stw(28, 12, P), stw(C, 0, N)
    if 'dropstore' in v:
        s1 = NOP
    if 'sched' in v:
        s1, s2 = s2, s1                                   # same base, other offset: cannot alias
    if 'storealias' in v:
        s2, s3 = s3, s2                                   # other base: may alias
    a.w(s1, s2, s3)
    a.w(addi(C, C, 1))
    a.label('cond')
    a.w(_X(32 if 'unsigned' in v else 0, 0, C, N))        # cmpw / cmplw C,N
    if 'brcond' in v:
        a.bc(4, 1, 'loop')                                # ble
    else:
        a.bc(12, 0, 'loop')                               # blt
    if 'loadstore' in v:
        a.w(stw(C, 0, N), lwz(7, 8, P), stw(7, 16, P))
    else:
        a.w(lwz(7, 8, P), stw(C, 0, N), stw(7, 16, P))
    if 'escape' in v:
        a.w(addi(8, 1, 8), stw(8, 28, P))                 # the address of a frame slot gets out
    if 'frameswap' in v:
        a.w(stw(C, 4, N), stw(7, 8, 1))
    else:
        a.w(stw(7, 8, 1), stw(C, 4, N))                   # frame slot, then through a pointer
    a.w(_I(48, 1, P, 8), _I(48, 2, P, 12))               # lfs f1,8(P); lfs f2,12(P)
    a.w(59 << 26 | 1 << 21 | 1 << 16 | 2 << 11 | (20 if 'floatop' in v else 21) << 1)
    a.w(_I(52, 1, P, 20))                                 # stfs f1,20(P)
    a.w(mr(3, C) if 'retval' not in v else mr(3, N))
    a.w(lwz(0, 52, 1), lwz(31, 44, 1))
    a.w(lwz(30, 40, 1) if 'norestore' not in v else NOP)
    a.w(lwz(29, 36, 1), lwz(28, 32, 1), 0x7C0803A6, addi(1, 1, 48), BLR)
    return a.words()


SYNTH_POS = ['', 'regswap', 'hoist', 'sched', 'bigger']
SYNTH_NEG = ['swapargs', 'const', 'storealias', 'loadcall', 'dropstore', 'brcond', 'offbyone', 'unsigned',
             'floatop', 'loadstore', 'target', 'retval', 'norestore']


def synth_run():
    bad = 0
    env = StubEnv()
    base = synth()
    for a, b, frame, want in (('', 'frameswap', False, False), ('', 'frameswap', True, True),
                              ('escape', 'escape+frameswap', True, False)):
        ok, t = check_pair(env, 0x80400000, synth(a), synth(b), frame=frame)
        print('  synthetic %-10s %s: %s' % (b + ('/frame' if frame else ''), ('proved' if ok else 'rejected') +
                                           ('' if ok == want else ' (WRONG)'), t))
        bad += ok != want
    for v in SYNTH_POS:
        ok, t = check_pair(env, 0x80400000, base, synth(v))
        print('  synthetic %-10s %s: %s' % (v or 'identical', 'proved' if ok else 'NOT PROVED (must pass)', t))
        bad += not ok
    for v in SYNTH_NEG:
        ok, t = check_pair(env, 0x80400000, base, synth(v))
        print('  synthetic %-10s %s: %s' % (v, 'ACCEPTED (must be rejected)' if ok else 'rejected', t))
        bad += ok
    acc = []
    for v in SYNTH_POS + SYNTH_NEG:                         # the same with cut points at every join
        try:
            Checker(env, 0x80400000, base, synth(v), joins=True).run()
            acc.append(v or 'identical')
        except Reject:
            pass
    wrong = [v for v in acc if v in SYNTH_NEG]
    print('  with cuts at joins: proved %s%s' % (' '.join(acc), '; ACCEPTED (must be rejected): ' + ' '.join(wrong)
                                              if wrong else '; every mutation rejected'))
    bad += len(wrong)
    return bad


_INIT = {}


def concrete_state(rnd, mem_base):
    st = St()
    st.g = [bv(rnd.getrandbits(32)) for _ in range(32)]
    st.f = [bv(rnd.getrandbits(64), 64) for _ in range(32)]
    st.p = [z3.BitVec('p%d' % k, 64) for k in range(32)]
    st.env = z3.BitVec('env', 32)
    st.cr = [bv(rnd.getrandbits(4), 4) for _ in range(8)]
    st.ctr, st.lr = bv(rnd.getrandbits(32)), bv(rnd.getrandbits(32))
    st.ca, st.so = bv(rnd.getrandbits(1), 1), bv(0, 1)
    if mem_base not in _INIT:
        arr = z3.K(BV32, z3.BitVecVal(0, 8))
        init = bytes(random.Random(5).getrandbits(8) for _ in range(512))
        for k, x in enumerate(init):
            arr = z3.Store(arr, bv(mem_base + k), z3.BitVecVal(x, 8))
        _INIT[mem_base] = (arr, init)
    arr, init = _INIT[mem_base]
    st.mem = Mem(arr)
    st.fmem = Mem(arr)
    st.stores = []
    return st, init


def fidelity(count=2500, seed=1):
    """Every exactly modelled instruction against unicorn on random states; for the
    uninterpreted ones only that nothing else changes. Returns the number of mismatches."""
    try:
        from unicorn import Uc, UC_ARCH_PPC, UC_MODE_PPC32, UC_MODE_BIG_ENDIAN
        import unicorn.ppc_const as U
    except ImportError:
        print('  semantics: unicorn missing, SKIPPED')
        return 1
    rnd = random.Random(seed)
    CODE, DATA = 0x10000, 0x200000
    r5 = lambda: rnd.randrange(32)                        # noqa: E731
    dops = [14, 15, 12, 13, 8, 7, 10, 11, 24, 25, 26, 27, 28, 29, 20, 21, 23]
    mops = list(LOADS) + list(STORES) + [46, 47, 48, 49, 50, 51, 52, 53, 54, 55]
    xint = [266, 40, 104, 235, 75, 11, 491, 459, 10, 8, 138, 136, 202, 200, 234, 232, 28, 60, 444, 412, 316, 476,
            124, 284, 24, 536, 792, 824, 26, 922, 954]
    xmem = list(XLOADS) + list(XSTORES) + [535, 567, 599, 631, 663, 695, 727, 759, 983]
    crl = [257, 449, 193, 225, 33, 289, 129, 417]
    fx = [(63, 72), (63, 40), (63, 264), (63, 136), (63, 12), (63, 14), (63, 15), (63, 0), (63, 32)]
    bad = 0
    done, still, moved = {}, {}, {}
    for n in range(count):
        kind = rnd.choice(['d', 'd', 'm', 'x', 'x', 'x', 'xm', 'cr', 'f', 'fa', 'spr', 'bc', 'cmp'])
        A, B, D = r5(), r5(), r5()
        memins = False
        if kind == 'd':
            op = rnd.choice(dops)
            w = _I(op, D & (28 if op in (10, 11) else 31), A, rnd.getrandbits(16)) | (rnd.getrandbits(1) if op in (20, 21, 23) else 0)
        elif kind == 'm':
            op = rnd.choice(mops)
            A = rnd.randrange(1, 31)
            if op == 46:
                D = rnd.randrange(A + 1, 32)
            elif op in LOADS and D == A:
                D = (A + 1) % 32
            w = _I(op, D, A, rnd.randrange(-64, 64))
            memins = True
        elif kind == 'x':
            xo = rnd.choice(xint)
            if xo in (104, 202, 200, 234, 232, 26, 922, 954):
                B = 0
            w = _X(xo, D, A, B, rnd.getrandbits(1))
        elif kind == 'xm':
            xo = rnd.choice(xmem)
            A = rnd.randrange(1, 32)
            while B == A:
                B = r5()
            if xo in XLOADS and D in (A, B):
                continue
            w = _X(xo, D, A, B)
            memins = True
        elif kind == 'cr':
            xo = rnd.choice(crl + [0, 19, 144])
            if xo == 0:
                w = 19 << 26 | (D & 28) << 21 | (A & 28) << 16
            elif xo == 19:
                w = _X(19, D, 0, 0)
            elif xo == 144:
                w = 31 << 26 | D << 21 | rnd.getrandbits(8) << 12 | 144 << 1
            else:
                w = 19 << 26 | D << 21 | A << 16 | B << 11 | xo << 1
        elif kind == 'f':
            op, xo = rnd.choice(fx)
            w = op << 26 | (D & 28 if xo in (0, 32) else D) << 21 | (A if xo in (0, 32) else 0) << 16 | B << 11 | xo << 1
        elif kind == 'fa':
            op = rnd.choice([59, 63])
            x5 = rnd.choice(list(FOPS) + [23, 24, 26])
            if (x5 == 23 or x5 == 26) and op == 59 or (x5 == 24 and op == 63):
                continue
            C = r5()
            if x5 in (18, 20, 21):
                C = 0
            elif x5 == 25:
                B = 0
            elif x5 in (24, 26):
                A = C = 0
            w = op << 26 | D << 21 | A << 16 | B << 11 | C << 6 | x5 << 1
        elif kind == 'spr':
            w = _X(rnd.choice([339, 467]), D, rnd.choice([8, 9]), 0)
        elif kind == 'cmp':
            w = _X(rnd.choice([0, 32]), D & 28, A, B)
        else:
            bo = rnd.choice([12, 4, 16, 18, 20, 8, 0, 10, 2, 13, 5])
            w = 16 << 26 | bo << 21 | A << 16 | 0x40
            if rnd.getrandbits(1):
                w = 19 << 26 | bo << 21 | A << 16 | 16 << 1
        st, init = concrete_state(rnd, DATA + 0x8000 - 128)
        if rnd.getrandbits(2) == 0:
            st.g[A] = st.g[B]
        if memins:
            st.g[A] = bv(DATA + 0x8000 + rnd.randrange(-8, 8))
            if kind == 'xm':
                st.g[B] = bv(rnd.randrange(-48, 48))
        if kind == 'bc':
            st.ctr = bv(rnd.choice([0, 1, 2, rnd.getrandbits(32)]))
            st.lr = bv(CODE + 0x100)
        st0 = st.copy()
        uc = Uc(UC_ARCH_PPC, UC_MODE_PPC32 | UC_MODE_BIG_ENDIAN)
        uc.mem_map(CODE, 0x1000)
        uc.mem_map(DATA, 0x10000)
        uc.mem_write(CODE, struct.pack('>I', w))
        # unicorn keeps XER[CA] apart from the XER register: set and read it with instructions
        uc.mem_write(CODE + 0x800, struct.pack('>2I', 0x7C000010 if st.ca.as_long() else 0x30000000, 0x7C000194))
        uc.emu_start(CODE + 0x800, 0, count=1)
        uc.mem_write(DATA + 0x8000 - 128, init)
        uc.reg_write(U.UC_PPC_REG_MSR, 0x2000)
        for r in range(32):
            uc.reg_write(U.UC_PPC_REG_0 + r, st.g[r].as_long())
            uc.reg_write(U.UC_PPC_REG_FPR0 + r, st.f[r].as_long())
        for r in range(8):
            uc.reg_write(U.UC_PPC_REG_CR0 + r, st.cr[r].as_long())
        uc.reg_write(U.UC_PPC_REG_CTR, st.ctr.as_long())
        uc.reg_write(U.UC_PPC_REG_LR, st.lr.as_long())
        try:
            r = step(st, w, CODE, CODE, CODE + 0x1000)
        except Reject as e:
            print('  semantics: generated an unsupported word %08x (%s)' % (w, e))
            bad += 1
            continue
        try:
            uc.emu_start(CODE, 0, count=1)
        except Exception as e:                              # noqa: BLE001
            print('  semantics: unicorn failed on %08x: %s' % (w, e))
            bad += 1
            continue
        form = (w >> 26, (w >> 1) & 1023 if w >> 26 in (19, 31, 63) else (w >> 1) & 31 if w >> 26 == 59 else 0)
        done[form] = 1
        diffs = []
        pc = uc.reg_read(U.UC_PPC_REG_PC)
        if r is None:
            want = CODE + 4
        elif r[0] == 'jmp':
            want = CODE + 4 * r[1]
        elif r[0] == 'ret':
            want = CODE + 0x100
        elif r[0] == 'br':
            c = S(r[1])
            if not (z3.is_true(c) or z3.is_false(c)):
                diffs.append('condition not concrete')
            want = (CODE + 0x100 if r[2] == RET else CODE + 4 * r[2]) if z3.is_true(c) else CODE + 4
        else:
            want = pc
        if pc != want:
            diffs.append('pc %x vs %x' % (pc, want))

        def cmp(name, mine, theirs, old):
            mine = S(mine)
            if z3.is_bv_value(mine):
                if mine.as_long() != theirs:
                    diffs.append('%s: model %x, unicorn %x' % (name, mine.as_long(), theirs))
            elif theirs == old.as_long():                   # uninterpreted result, unicorn left it alone
                if kind not in ('f', 'fa', 'm', 'xm', 'x'):
                    diffs.append('%s: model changed it, unicorn did not' % name)
                still[form] = still.get(form, 0) + 1
            else:
                moved[form] = moved.get(form, 0) + 1
        for k in range(32):
            cmp('r%d' % k, st.g[k], uc.reg_read(U.UC_PPC_REG_0 + k), st0.g[k])
            cmp('f%d' % k, st.f[k], uc.reg_read(U.UC_PPC_REG_FPR0 + k), st0.f[k])
        for k in range(8):
            cmp('cr%d' % k, st.cr[k], uc.reg_read(U.UC_PPC_REG_CR0 + k), st0.cr[k])
        cmp('ctr', st.ctr, uc.reg_read(U.UC_PPC_REG_CTR), st0.ctr)
        cmp('lr', st.lr, uc.reg_read(U.UC_PPC_REG_LR), st0.lr)
        uc.reg_write(U.UC_PPC_REG_0, 0)
        uc.emu_start(CODE + 0x804, 0, count=1)
        cmp('ca', st.ca, uc.reg_read(U.UC_PPC_REG_0), st0.ca)
        got = bytes(uc.mem_read(DATA + 0x8000 - 128, 512))
        exp = bytearray(init)
        for ea, size, val, _tag in st.stores:
            val = S(val)
            o = ea.as_long() - (DATA + 0x8000 - 128)
            if z3.is_bv_value(val):
                exp[o:o + size] = val.as_long().to_bytes(size, 'big')
            else:
                exp[o:o + size] = got[o:o + size]             # uninterpreted (stfs): only the place is checked
        if got != bytes(exp):
            diffs.append('memory differs')
        if diffs:
            bad += 1
            if bad <= 12:
                print('  semantics MISMATCH %08x: %s' % (w, '; '.join(diffs[:3])))
    for form, k in sorted(still.items()):                  # an uninterpreted result in a register unicorn never writes
        if k >= 3 and form not in moved:
            bad += 1
            print('  semantics MISMATCH: opcode %d/%d writes a register unicorn leaves alone' % form)
    print('  semantics: %d random instructions over %d opcode forms against unicorn, %d mismatches' % (
        count, len(done), bad))
    return bad


def mutate(words, rnd):
    """(description, words) of single-instruction mutations that change the behaviour.
    (No signed/unsigned swap here: `cmpwi; beq` does not care, and the six such mutants
    this tool accepted on 2026-11-12 were all really equivalent. The synthetic pair has
    one that is not.)"""
    out = []
    idx = list(range(len(words)))
    rnd.shuffle(idx)
    kinds = set()
    for i in idx:
        w = words[i]
        op = w >> 26
        xo = (w >> 1) & 1023
        m = None
        if op in STORES or (op in (52, 54)):
            m = ('dropped store', NOP)
        elif op == 16 and (w >> 21) & 20 == 4:
            m = ('inverted branch', w ^ (8 << 21))
        elif op in (59, 63) and (w >> 1) & 31 in (20, 21):
            m = ('fadd/fsub', w ^ (1 << 1))
        elif op in (10, 11) or (op == 14 and (w >> 16) & 31 == 0):
            m = ('changed constant', w ^ 1)
        elif op == 18 and w & 1:
            m = ('other call target', (w & ~0x03FFFFFC) | ((w + 0x40) & 0x03FFFFFC))
        if m and (m[0], op) not in kinds:
            kinds.add((m[0], op))
            ws = list(words)
            ws[i] = m[1]
            out.append(('%s at +0x%x' % (m[0], 4 * i), ws))
    return out


# Real pairs that must be proved, with the mode they need ('' = strict, 'p' = --policy).
# Linked allow-listed functions (regequiv.txt / schedequiv.txt): our object against the original.
REAL_POS = [
    ('fn_80207510', ''), ('fn_8016AB80', ''), ('fn_8021F4A4', ''), ('fn_801C9F7C', ''), ('fn_8013FCD0', ''),
    ('fn_80165CF4', ''), ('fn_80039988', 'p'), ('fn_80189BA4', 'p'),
]
# Drafts that are NOT linked (their objects change): our words as they were on 2026-11-12, with
# the relocations resolved (--dump). These differ from the original across basic blocks / in size.
FIXTURES = {
    'fn_8024E004': ('',
        '9421ff607c0802a6900100a4bf2100847c7c1b787c9d23787cb92b787cde33787cff3b783861005c4bfee7a12c190002'
        '41820104408000102c19000140800014480003742c1900044080036c480001cc386100404bfee7753be00000281f0000'
        '408200307f83e378819c0010818c00147d8903a64e8004212c030000418200147f84e378386100404bfee69548000010'
        '38610040389c004c4bfee6853861004038822ba04bfee4814800005828030000418200148081004c4bfec3d57c7e1b78'
        '480000083bc0000038610014389e00144bea8db57fa3eb78388100144bea8e212c03000040820014386100403880ffff'
        '4bfee68148000034386100404bfee2f580610048280300004082ffa43bff0001281f00024180ff48386100403880ffff'
        '4bfee6513bc000007fc3f3784800218d48000284386100244bfee6913be00000281f0000408200307f83e378819c0010'
        '818c00147d8903a64e8004212c030000418200147f84e378386100244bfee5b14800001038610024389c004c4bfee5a1'
        '3861002438822ba84bfee39d480000582803000041820014808100304bfec2f17c7e1b78480000083bc000003861000c'
        '389e00144bea8cd17fa3eb783881000c4bea8d3d2c03000040820014386100243880ffff4bfee59d4800003438610024'
        '4bfee2118061002c280300004082ffa43bff0001281f00024180ff48386100243880ffff4bfee56d3bc000007fc3f378'
        '48002ca9480001a07f83e3787fa4eb7838a10008480001b57c7b1b784bffd4e12c030000418200143861005c3880ffff'
        '4bfee5314800017c7f83e3783881001c38a100084bfff5bd2c030000408200247f63db787fc4f378819b00007fe5fb78'
        '818c00307d8903a64e800421480001387fa3eb783881001c4bea8a452c030000418200143861005c3880ffff4bfee4d5'
        '480001207f83e3783881001c38a1000848000129800300282c000000418200288003001c28000002408200188003002c'
        '8063006c5400103a7c63002e4800000838600000800300702c000000418200188183000038800000818c00347d8903a6'
        '4e8004217f9be3783b2000003b400000480000247fa3eb78389b02804bea89b12c030000418200083b2000013b7b0028'
        '3b5a0001801c027c7c1a00404180ffd82c1900004082007028000005408000681c6000287fa4eb78386302807c7c1a14'
        '4bea8b25801c027c7fe4fb781c600028386302907c7c1a144bea8b0d801c027c7fc4f3781c600028386302887c7c1a14'
        '4bea8af5801c027c388000031c0000287c7c021490830298807c027c38030001901c027c3861005c3880ffff4bfee3b5'
        'bb210084800100a47c0803a6382100a04e800020'),
    'fn_8021A510': ('',
        '9421ff907c0802a690010074bf0100507c7e1b787c9823787cbc2b787cdf3378386100304bff4e657fc3f3787f04c378'
        '38a1000c38c1000848000b817c7d1b79408200247fe3fb783880000038a000004bff4a85386100303880ffff4bff4d11'
        '480003ec808100083861003080a1000c4bff4a653b0000004800008c88bd000238610020881d00013880000088fd0003'
        '54a5801e5400402e88dd00007c002a1454e7c00e7f603a1438a000107f66da143bbd00084bdeaf41387e00045764053e'
        '38c1002038a000004bff81552c0300004082001038610020388220504bed11797f04c3783861003038a000034bff45b5'
        '7f04c3783861003038a100204bff44853b1800018001000c7c1800404180ff703b600000480000b088bd000a38610020'
        '881d00093880000088dd000b54a5801e5400402e88fd00017c002a1454c6c00e891d000054e7402e88bd00087f003214'
        '8b3d00027f483a147f05c21438a000103bbd000c4bdeae917f44d3787f25cb78387e000438c100204bff80a52c030000'
        '4082001038610020388220504bed10c97f64db783861003038a000024bff470d7f64db783861003038a100204bff4569'
        '7f64db787f05c378386100304bff46793b7b0001800100087c1b00404180ff4c7f84e378386100104bed107d38610010'
        '4bed112d3c80802e38a10010388407c87c6903a62803000040810030880500007c0007742c00ffff4082000c3800ffff'
        '4800000c5400063e7c0400ae9805000038a500014200ffd8386100103880002e4bed0dd1280300004082001838610010'
        '4bed10cd3ba100107fbd1a1448000010380000003ba30001980300003b8000009381000c4800003c7f84e37838610030'
        '4bff46d57c641b787fc3f3787fa6eb7838a100104bff7a312c030000418200108061000c380300019001000c3b9c0001'
        '8001003c7c1c00404180ffc03b800000938100084800003c7f84e378386100304bff46f97c641b787fc3f3787fa6eb78'
        '38a100104bff79e12c030000418200108061000838030001900100083b9c0001800100387c1c00404180ffc080810008'
        '7fe3fb7880a1000c4bff47cd3b8000009381000c480000747f84e378386100304bff46257c641b787fc3f3787fa6eb78'
        '38a100104bff79812c030000418200487f84e378386100304bff45d58081000c7c651b787fe3fb784bff43497f84e378'
        '386100304bff45e18081000c7c651b787fe3fb784bff420d8061000c380300019001000c3b9c00018001003c7c1c0040'
        '4180ff883b80000093810008480000907f84e378386100304bff46117c641b787fc3f3787fa6eb7838a100104bff78f9'
        '2c030000418200647f84e378386100304bff4599808100087c651b787fe3fb784bff44c97f84e378386100304bff45cd'
        '808100087c651b787fe3fb784bff43197f84e378386100304bff4589808100087c651b787fe3fb784bff441d80610008'
        '38030001900100083b9c0001800100387c1c00404180ff6c386100304bff45a1386100303880ffff4bff4925bb010050'
        '800100747c0803a6382100704e800020'),
    'fn_8025E444': ('p',
        '9421ffe07c0802a63c80802f38c231409001002438e4291838a1000893e1001c7c7f1b787fe4fb788007000080670004'
        '90010008800700089061000c90010010806da45c4bff56513c608035c00230b038a37ae038800004d005000038000000'
        '7fe3fb78d0050004d0050008909f015c901f0158901f0150c00230b4d01f0160c00230b0d01f0180c00230b0d01f0184'
        '901f00ccc00230b0d01f00d0c00230b0d01f00d4c00230b0d01f00d8c00230b0d01f0118901f011cc00230b0d01f0120'
        'c00230b0d01f0124c00230b0d01f0128901f012c901f01304bff91318001002483e1001c7c0803a6382100204e800020'),
}


def _timed(limit, f, *a, **kw):
    signal.signal(signal.SIGALRM, _alarm)
    signal.alarm(limit)
    try:
        return f(*a, **kw)
    except (Alarm, RecursionError):
        return False, 'time limit'
    finally:
        signal.alarm(0)


def selftest(args, P):
    global FPCOMM
    bad = 0
    print('semantics')
    bad += fidelity()
    print('synthetic pairs')
    bad += synth_run()
    prog, env, secs, units = setup(P)
    print('real pairs (must be proved; single-instruction mutations of ours must be rejected)')
    mut = acc = 0
    cases = []
    for name, mode in REAL_POS:
        fn = prog.byname.get(name)
        unit = unit_of(units, fn.addr) if fn else None
        try:
            ours, fakes = our_words(prog, secs, unit, UObj(os.path.join(P['build'], 'src', unit + '.o')), name)
        except (OSError, TypeError, Reject) as e:
            print('  %s: NOT CHECKED (%s)' % (name, e))
            bad += 1
            continue
        cases.append((name, mode, fn, ours, fakes))
    for name, (mode, hexw) in FIXTURES.items():
        fn = prog.byname[name]
        cases.append((name + ' (draft)', mode, fn, [int(hexw[k:k + 8], 16) for k in range(0, len(hexw), 8)], ()))
    for name, mode, fn, ours, fakes in cases:
        kw = dict(frame='p' in mode, leftover='p' in mode, ro=RoData(prog, fakes))
        FPCOMM = 'p' in mode
        t0 = time.time()
        ok, text_ = _timed(args.limit, check_pair, env, fn.addr, fn.words, ours, **kw)
        diff = sum(x != y for x, y in zip(fn.words, ours)) + abs(len(ours) - fn.n)
        print('  %-22s %-6s %s: %s [%d of %d words differ, %d vs %d bytes, %.1fs]' % (
            name, 'policy' if mode else 'strict', 'proved' if ok else 'NOT PROVED (must pass)', text_, diff, fn.n,
            4 * fn.n, 4 * len(ours), time.time() - t0))
        if not ok:
            bad += 1
            continue
        for desc, ws in mutate(ours, random.Random(name))[:6]:
            mut += 1
            ok2, t2 = _timed(args.limit, check_pair, env, fn.addr, fn.words, ws, **kw)
            if ok2:
                acc += 1
                print('    mutation ACCEPTED (must be rejected): %s' % desc)
            elif args.verbose:
                print('    rejected %s: %s' % (desc, t2))
    FPCOMM = args.fp_commute
    print('  %d mutations of proved real functions, %d accepted' % (mut, acc))
    bad += acc
    print('differential runs of the drafts in unicorn (must not differ)')
    for name, (mode, hexw) in FIXTURES.items():
        fn = prog.byname[name]
        ours = [int(hexw[k:k + 8], 16) for k in range(0, len(hexw), 8)]
        done, part, skipped, diff = fuzz_pair(prog, fn, ours, (), seeds=25, retuse=env.retuse(fn.addr),
                                              inputs_of=env.inputs_of)
        print('  %-22s %d runs compared, %d by their calls only, %d not comparable%s' % (
            name, done, part, skipped, ': DIFFERENT (%s)' % diff if diff else ''))
        bad += bool(diff) or not done + part
    print('selftest: %s' % ('OK' if not bad else 'FAILED (%d)' % bad))
    return 1 if bad else 0


def dump(args, P):
    prog, env, secs, units = setup(P)
    for name in args.dump:
        fn = prog.byname[name]
        unit = unit_of(units, fn.addr)
        ours, fakes = our_words(prog, secs, unit, UObj(os.path.join(P['build'], 'src', unit + '.o')), name)
        print("    '%s': ('p', '%s'),%s" % (name, ''.join('%08x' % w for w in ours), '  # has fake literals' if fakes else ''))
    return 0


# ---- --fuzz: differential execution (independent of the prover) ----------------

def fuzz_pair(prog, fn, ours, fakes, seeds=40, steps=20000, retuse=0, inputs_of=None):
    """Run the original and ours in unicorn on the same random machine state and compare
    what the prover claims to be equal: the sequence of calls with the argument registers
    the callee may read (inputs_of), r3 (and the readable ones of r4/f1), the callee-saved registers, r1 and
    every byte written. Every callee is a stub that returns values made from its arguments;
    psq_st / psq_l (unknown to unicorn) are run as stfd / lfd. A run in which neither
    version returns within `steps` instructions only compares the calls made so far.
    Returns (runs compared to the end, runs compared by their calls only, runs not
    comparable, first difference or None). A sanity check of the prover, not a proof."""
    from unicorn import (Uc, UcError, UC_ARCH_PPC, UC_MODE_PPC32, UC_MODE_BIG_ENDIAN, UC_HOOK_CODE,
                         UC_HOOK_MEM_UNMAPPED, UC_HOOK_MEM_WRITE, UC_MEM_FETCH_UNMAPPED)
    import unicorn.ppc_const as U
    import hashlib
    dol = prog.dol
    SENT = 0x80000100
    blr = struct.pack('>I', BLR)
    lo, hi = 0x80000000, 0x80400000

    def h(*a):
        return hashlib.sha1(repr(a).encode()).digest()

    def fill(tag, n):
        # deterministic words: small numbers and multiples of 4 (pointers, call targets)
        d = bytearray(h(tag) + h(tag, 1))
        for k in range(0, 40, 4):
            if d[k] & 1:
                d[k:k + 3] = b'\0\0\0'
                d[k + 3] &= 0x1F
            else:
                d[k + 3] &= 0xFC
        return (bytes(d) * (n // 40 + 1))[:n]

    img = bytearray(blr * ((hi - lo) // 4))
    b = getattr(dol, 'bss', None)
    if b and lo <= b[0] and b[0] + b[1] <= hi:              # bss: not zero (null pointers end every run)
        img[b[0] - lo:b[0] - lo + b[1]] = fill('bss', b[1])
    for off, a, size, text in dol.secs:
        if not text and lo <= a and a + size <= hi:
            img[a - lo:a - lo + size] = dol.data[off:off + size]
    low = bytearray(0x7000)
    for a, data in fakes:
        low[a - 0x1000:a - 0x1000 + len(data)] = data

    class Machine:
        def __init__(self, words):
            words = [(w & 0x03FF0000) | (54 if w >> 26 == 60 else 50) << 26 |
                     ((w & 0xFFF) - (0x1000 if w & 0x800 else 0)) & 0xFFFF
                     if w >> 26 in (56, 60) and not w & 0xF000 else w for w in words]
            self.end = fn.addr + 4 * len(words)
            uc = self.uc = Uc(UC_ARCH_PPC, UC_MODE_PPC32 | UC_MODE_BIG_ENDIAN)
            uc.mem_map(lo, hi - lo)
            self.base = bytes(img[:fn.addr - lo]) + struct.pack('>%dI' % len(words), *words) + \
                bytes(img[self.end - lo:])
            uc.mem_write(lo, self.base)
            uc.mem_map(0x1000, 0x7000)                     # pseudo addresses of our read-only literals
            uc.mem_write(0x1000, bytes(low))
            self.pages = set()
            self.writes = {}
            self.events = []
            for b0, b1 in ((0, fn.addr - 1), (self.end, M32)):   # every instruction outside the function
                uc.hook_add(UC_HOOK_CODE, self.oncode, None, b0, b1)
            uc.hook_add(UC_HOOK_MEM_UNMAPPED, self.onmiss)
            uc.hook_add(UC_HOOK_MEM_WRITE, self.onwrite)

        def oncode(self, uc, addr, size, _u):
            if addr == SENT:
                return
            m = inputs_of(addr) if inputs_of and addr in prog.fns else E.ARGS_ALL
            g = [uc.reg_read(U.UC_PPC_REG_0 + r) for r in range(3, 11) if m >> r & 1]
            f = [uc.reg_read(U.UC_PPC_REG_FPR0 + r) for r in range(1, 9) if m >> (E.FP + r) & 1]
            self.events.append((addr, tuple(g), tuple(f)))
            d = h(self.seed, addr, g, f, len(self.events))
            for k, r in enumerate([0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]):
                v = int.from_bytes(d[k:k + 4], 'big')
                uc.reg_write(U.UC_PPC_REG_0 + r, v & ~3 if r != 3 or d[19] & 1 else v % 5)
            uc.reg_write(U.UC_PPC_REG_FPR0 + 1, struct.unpack('>Q', struct.pack('>d', d[18] / 7.0 - 9))[0])

        def onmiss(self, uc, access, addr, size, value, _u):
            try:
                for page in {addr & ~0xFFF, (addr + max(size, 1) - 1) & ~0xFFF}:
                    if page not in self.pages:
                        uc.mem_map(page, 0x1000)
                        uc.mem_write(page, blr * 1024 if access == UC_MEM_FETCH_UNMAPPED else
                                     fill((self.seed, page), 4096))
                        self.pages.add(page)
                return True
            except UcError:
                return False

        def onwrite(self, uc, access, addr, size, value, _u):
            for k in range(size):
                self.writes[(addr + k) & M32] = value >> 8 * (size - 1 - k) & 0xFF

        def run(self, seed):
            uc = self.uc
            for page in self.pages:
                uc.mem_unmap(page, 0x1000)
            for a in set(x & ~0xFFF for x in self.writes if lo <= x < hi):
                uc.mem_write(a, self.base[a - lo:a - lo + 0x1000])
            self.pages, self.writes, self.events, self.seed = set(), {}, [], seed
            rnd = random.Random(seed)
            uc.reg_write(U.UC_PPC_REG_MSR, 0x2000)
            for r in range(32):
                uc.reg_write(U.UC_PPC_REG_0 + r,
                             rnd.getrandbits(32) & ~3 if rnd.getrandbits(1) else rnd.randrange(-8, 64) & M32)
                uc.reg_write(U.UC_PPC_REG_FPR0 + r, struct.unpack('>Q', struct.pack('>d', rnd.uniform(-100, 100)))[0])
            uc.reg_write(U.UC_PPC_REG_1, 0x7F000000 + rnd.randrange(0x2000, 0x8000) * 8)
            for r, v in prog.sda.items():
                uc.reg_write(U.UC_PPC_REG_0 + r, v)
            uc.reg_write(U.UC_PPC_REG_LR, SENT)
            uc.reg_write(U.UC_PPC_REG_CTR, rnd.getrandbits(32))
            try:
                uc.emu_start(fn.addr, SENT, count=steps)
            except UcError as e:
                pc = uc.reg_read(U.UC_PPC_REG_PC)
                return None, 'unicorn: %s at %08x' % (e, pc)
            if uc.reg_read(U.UC_PPC_REG_PC) != SENT:
                return None, 'running'
            regs = [uc.reg_read(U.UC_PPC_REG_0 + r) for r in [1, 2, 3, 13] + list(range(14, 32))]
            regs += [uc.reg_read(U.UC_PPC_REG_FPR0 + r) for r in range(14, 32)]
            if retuse & E.R4:
                regs.append(uc.reg_read(U.UC_PPC_REG_4))
            if retuse & E.F1:
                regs.append(uc.reg_read(U.UC_PPC_REG_FPR0 + 1))
            return (list(self.events), regs, dict(self.writes)), None

    done = part = skipped = 0
    why = fuzz_pair.why = {}
    for seed in range(seeds):
        # A new machine for every run: CR, XER, FPSCR and the translation cache of the last
        # run would otherwise leak into this one (they differ between the two versions).
        mo, mu = Machine(fn.words), Machine(ours)
        a, ea = mo.run(seed)
        b, eb = mu.run(seed)
        if a is not None and b is not None:
            done += 1
            for what, x, y in zip(('calls', 'registers', 'memory'), a, b):
                if x != y:
                    return done, part, skipped, 'seed %d: %s differ' % (seed, what)
        elif ea == 'running' and eb == 'running':
            part += 1
            n = min(len(mo.events), len(mu.events))
            if mo.events[:n] != mu.events[:n]:
                return done, part, skipped, 'seed %d: calls differ (neither returned)' % seed
        elif (ea or eb) == 'running' or (a is None) != (b is None):
            return done, part, skipped, 'seed %d: original %s, ours %s' % (seed, ea or 'returned', eb or 'returned')
        else:
            skipped += 1
            why[ea] = why.get(ea, 0) + 1
    return done, part, skipped, None


def fuzz_mode(args, P):
    prog, env, secs, units = setup(P)
    rc = 0
    for name in args.fuzz:
        fn = prog.byname[name]
        unit = unit_of(units, fn.addr)
        try:
            ours, fakes = our_words(prog, secs, unit, UObj(os.path.join(P['build'], 'src', unit + '.o')), name)
        except (OSError, Reject) as e:
            print('SKIP %s: %s' % (name, e))
            continue
        done, part, skipped, diff = fuzz_pair(prog, fn, ours, fakes, seeds=args.seeds, retuse=env.retuse(fn.addr),
                                             inputs_of=env.inputs_of)
        print('%s %s: %d runs compared, %d by their calls only, %d not comparable%s%s' % (
            'DIFF' if diff else 'same', name, done, part, skipped, ' -- ' + diff if diff else '',
            ' (%s)' % '; '.join('%s x%d' % kv for kv in sorted(fuzz_pair.why.items())) if args.verbose else ''))
        sys.stdout.flush()
        rc |= bool(diff)
    return rc


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--version', default='GHYE6S')
    ap.add_argument('--list', nargs='+', metavar='UNIT')
    ap.add_argument('--check', action='store_true', help='prove every function of config/<v>/funcequiv.txt')
    ap.add_argument('--selftest', action='store_true')
    ap.add_argument('--dump', nargs='+', metavar='FN', help=argparse.SUPPRESS)
    ap.add_argument('--fuzz', nargs='+', metavar='FN',
                    help='run the original and ours in unicorn on random states and compare calls, results and '
                         'memory (sanity check of the prover, no proof)')
    ap.add_argument('--seeds', type=int, default=40)
    ap.add_argument('--limit', type=int, default=120, help='seconds per function')
    ap.add_argument('-v', '--verbose', action='store_true')
    ap.add_argument('--frame', action='store_true',
                    help="assume that only r1-based accesses reach the function's own stack frame when no "
                         "frame address leaves r1 (rule 'pointer' of equivcheck rule f)")
    ap.add_argument('--fp-commute', action='store_true',
                    help='fadd / fmul operands may be exchanged (as equivcheck rule d; differs for two NaNs)')
    ap.add_argument('--leftover', action='store_true',
                    help='what a call leaves in a volatile register other than r3/r4/f1 only matters when the '
                         'function reads it with its own instructions (assumption of equivcheck rule d)')
    ap.add_argument('--policy', action='store_true', help='--frame --fp-commute --leftover')
    ap.add_argument('--debug', action='store_true')
    args = ap.parse_args()
    if args.policy:
        args.frame = args.fp_commute = args.leftover = True
    global FPCOMM, DEBUG
    FPCOMM, DEBUG = args.fp_commute, args.debug
    P = paths(args.version)
    if args.selftest:
        sys.exit(selftest(args, P))
    if args.dump:
        sys.exit(dump(args, P))
    if args.fuzz:
        sys.exit(fuzz_mode(args, P))
    if args.list:
        sys.exit(list_mode(args, P))
    if args.check:
        sys.exit(list_mode(args, P, E.load_allow(P['allow'])))
    ap.print_help()
    sys.exit(2)


if __name__ == '__main__':
    main()
