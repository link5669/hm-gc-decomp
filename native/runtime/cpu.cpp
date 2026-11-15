// CPU-side runtime services for recompiled code: indirect calls, SPRs, time base, paired-single
// quantized loads/stores, cache ops, MMIO entry points.
#include "rt.h"
#include <cstdarg>
#include <ctime>
#include <vector>
#include <algorithm>

extern "C" {
struct FnEnt { u32 addr; GuestFn fn; };
struct NameEnt { u32 addr; const char *name; };
extern const FnEnt rt_func_table[];
extern const size_t rt_func_count;
extern const NameEnt rt_func_names[];
extern const size_t rt_func_name_count;
extern const NameEnt rt_data_syms[];
extern const size_t rt_data_sym_count;
}

CPU g_cpu;
int g_log_level = 1;

static const u32 TBL_LO = 0x80000000u, TBL_HI = 0x80400000u;
static GuestFn *g_dense;

void rt_init_calls() {
    g_dense = (GuestFn *)calloc((TBL_HI - TBL_LO) / 4, sizeof(GuestFn));
    for (size_t i = 0; i < rt_func_count; i++) {
        u32 a = rt_func_table[i].addr;
        if (a >= TBL_LO && a < TBL_HI) g_dense[(a - TBL_LO) / 4] = rt_func_table[i].fn;
    }
}

const char *rt_func_name(u32 addr, u32 *off) {
    size_t lo = 0, hi = rt_func_name_count;
    while (hi - lo > 1) { size_t m = (lo + hi) / 2; if (rt_func_names[m].addr <= addr) lo = m; else hi = m; }
    if (rt_func_name_count && rt_func_names[lo].addr <= addr) { if (off) *off = addr - rt_func_names[lo].addr; return rt_func_names[lo].name; }
    if (off) *off = 0;
    return "?";
}

u32 rt_sym(const char *name) {
    for (size_t i = 0; i < rt_data_sym_count; i++) if (!strcmp(rt_data_syms[i].name, name)) return rt_data_syms[i].addr;
    for (size_t i = 0; i < rt_func_name_count; i++) if (!strcmp(rt_func_names[i].name, name)) return rt_func_names[i].addr;
    return 0;
}

void rt_fatal(const char *fmt, ...) {
    va_list ap; va_start(ap, fmt);
    fprintf(stderr, "FATAL: "); vfprintf(stderr, fmt, ap); fprintf(stderr, "\n");
    va_end(ap);
    CPU *c = &g_cpu; u32 off;
    fprintf(stderr, "  lr=%08X (%s) r1=%08X r3=%08X r4=%08X r5=%08X\n", c->lr, rt_func_name(c->lr, &off), c->r[1], c->r[3], c->r[4], c->r[5]);
    // walk the guest stack (back chain + saved LR)
    u32 sp = c->r[1];
    for (int i = 0; i < 24 && ISRAM(sp) && sp; i++) {
        u32 next = ld32(sp); if (!ISRAM(next) || next <= sp) break;
        u32 lr = ld32(next + 4);
        fprintf(stderr, "  #%d %08X %s+0x%X\n", i, lr, rt_func_name(lr, &off), off);
        sp = next;
    }
    fflush(stderr);
    abort();
}

extern "C" void rt_call(CPU *RESTRICT c, u32 addr) {
    GuestFn fn = (addr >= TBL_LO && addr < TBL_HI && !(addr & 3)) ? g_dense[(addr - TBL_LO) / 4] : nullptr;
    if (unlikely(!fn)) rt_fatal("indirect call to unknown address %08X", addr);
    fn(c);
}

extern "C" void rt_unimpl(CPU *RESTRICT c, u32 pc, u32 ins) {
    u32 off = 0; rt_fatal("unimplemented instruction %08X at %08X (%s+0x%X)", ins, pc, rt_func_name(pc, &off), off);
}
extern "C" void rt_trap(CPU *RESTRICT c, u32 pc) { u32 off = 0; rt_fatal("trap at %08X (%s+0x%X)", pc, rt_func_name(pc, &off), off); }
extern "C" void rt_sc(CPU *RESTRICT c, u32 pc) {
    // __OSSystemCallVector: used by PPCSync-like helpers; nothing to do natively.
    VLOG("sc at %08X\n", pc);
}
extern "C" void rt_rfi(CPU *RESTRICT c, u32 pc) {
    // rfi used as a jump (RealMode -> Config24MB, which rfi's back to LR): msr = SRR1, go to SRR0.
    c->msr = c->spr[27];
    u32 t = c->spr[26] | 0x80000000u;
    if (t == (c->lr | 0x80000000u)) return;        // "return" to the caller
    rt_call(c, t);
}

// ---- time base ----
static u64 g_tb_base, g_host_base;
static u64 host_ns() { timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts); return (u64)ts.tv_sec * 1000000000ull + ts.tv_nsec; }
u64 tb_now() { return g_tb_base + (host_ns() - g_host_base) * 81 / 2000; }
void tb_set(u64 v) { g_host_base = host_ns(); g_tb_base = v; }
extern "C" u64 rt_tb_now(void) { return tb_now(); }

extern "C" u32 rt_mftb(CPU *RESTRICT c, int upper) { u64 t = tb_now(); return upper ? (u32)(t >> 32) : (u32)t; }

// decrementer: DEC counts down at the time base rate; interrupt when it goes negative
static u64 g_dec_write_tb; static u32 g_dec_value;
bool g_dec_pending;
static u32 dec_read() { u64 el = tb_now() - g_dec_write_tb; return g_dec_value - (u32)el; }
static void dec_write(u32 v) {
    g_dec_write_tb = tb_now(); g_dec_value = v; g_dec_pending = false;
    if ((s32)v < 0) { g_dec_pending = true; rt_irq_flag = 1; ev_cancel(EV_DEC); }
    else ev_schedule(EV_DEC, g_dec_write_tb + v + 1);
}
void dec_event() { g_dec_pending = true; }

extern void lc_dma(u32 dmau, u32 dmal);
extern "C" u32 rt_mfspr(CPU *RESTRICT c, u32 n) {
    switch (n) {
    case 22: return dec_read();
    case 268: return (u32)tb_now();
    case 269: return (u32)(tb_now() >> 32);
    case 287: return 0x00083214; // PVR (Gekko)
    }
    return c->spr[n];
}
extern "C" void rt_mtspr(CPU *RESTRICT c, u32 n, u32 v) {
    switch (n) {
    case 22: dec_write(v); return;
    case 284: tb_set((tb_now() & 0xFFFFFFFF00000000ull) | v); return;
    case 285: tb_set((tb_now() & 0xFFFFFFFFull) | ((u64)v << 32)); return;
    case 923: c->spr[n] = v; if (v & 2) { lc_dma(c->spr[922], v); c->spr[n] &= ~2u; } return;  // DMA_L trigger
    }
    c->spr[n] = v;
}

extern "C" void rt_mtmsr(CPU *RESTRICT c, u32 v) {
    u32 old = c->msr; c->msr = v;
    if ((v & 0x8000) && !(old & 0x8000) && irq_pending()) rt_irq_check(c);
}

// ---- paired-single quantization ----
static inline double ldexp_s(double v, int sc) { return ldexp(v, sc); }
static double dequant(u32 ea, int type, int scale, int *size) {
    switch (type) {
    case 4: *size = 1; return ldexp_s((double)ld8(ea), -scale);
    case 5: *size = 2; return ldexp_s((double)ld16(ea), -scale);
    case 6: *size = 1; return ldexp_s((double)(s8)ld8(ea), -scale);
    case 7: *size = 2; return ldexp_s((double)(s16)ld16(ea), -scale);
    default: *size = 4; return (double)ldf32(ea);
    }
}
static void quant(u32 ea, double v, int type, int scale, int *size) {
    if (type == 0 || type < 4) { *size = 4; stf32(ea, (float)v); return; }
    double s = ldexp_s(v, scale);
    switch (type) {
    case 4: *size = 1; st8(ea, (u8)std::clamp(s, 0.0, 255.0)); break;
    case 5: *size = 2; st16(ea, (u16)std::clamp(s, 0.0, 65535.0)); break;
    case 6: *size = 1; st8(ea, (u8)(s8)std::clamp(s, -128.0, 127.0)); break;
    case 7: *size = 2; st16(ea, (u16)(s16)std::clamp(s, -32768.0, 32767.0)); break;
    }
}
static inline int sx6(u32 v) { v &= 0x3F; return (v & 0x20) ? (int)v - 64 : (int)v; }
extern "C" void rt_psq_l(CPU *RESTRICT c, u32 ea, int fd, int w, int i) {
    u32 g = c->gqr[i]; int type = (g >> 16) & 7, scale = sx6(g >> 24), sz;
    double a = dequant(ea, type, scale, &sz);
    double b = w ? 1.0 : dequant(ea + sz, type, scale, &sz);
    c->f[fd].d = a; c->ps1[fd] = b;
}
extern "C" void rt_psq_st(CPU *RESTRICT c, u32 ea, int fs, int w, int i) {
    u32 g = c->gqr[i]; int type = g & 7, scale = sx6(g >> 8), sz;
    quant(ea, c->f[fs].d, type, scale, &sz);
    if (!w) quant(ea + sz, c->ps1[fs], type, scale, &sz);
}

// ---- ARAM virtual memory region (VMAlloc'd at 0x7E000000) ----
static u8 g_vm[0x01000000];
#define ISVM(a) (((a) >> 24) == 0x7E)
#define VMP(a) (g_vm + ((a) & 0x00FFFFFF))

// ---- cache ----
u8 g_lc[0x4000];  // locked cache (0xE0000000)
extern "C" void rt_dcbz(u32 ea) {
    ea &= ~31u;
    if (ISRAM(ea)) { memset(HP(ea), 0, 32); return; }
    if ((ea >> 28) == 0xE) { memset(g_lc + (ea & 0x3FE0), 0, 32); return; }
    if (ISVM(ea)) { memset(VMP(ea), 0, 32); return; }
}
void lc_dma(u32 dmau, u32 dmal) {
    u32 mem = dmau & ~31u, lc = dmal & ~31u;
    u32 len = (((dmau & 31) << 2) | ((dmal >> 2) & 3)); if (!len) len = 128; len *= 32;
    bool load = dmal & 0x10;
    for (u32 i = 0; i < len; i += 32) {
        u8 *l = g_lc + ((lc + i) & 0x3FE0);
        if (load) memcpy(l, HP(mem + i), 32); else memcpy(HP(mem + i), l, 32);
    }
}


// ---- MMIO entry points (non-RAM addresses) ----
extern "C" u32 mmio_read32(u32 a) {
    if (ISVM(a)) { u32 v; memcpy(&v, VMP(a), 4); return __builtin_bswap32(v); }
    if ((a >> 28) == 0xE) { u32 v; memcpy(&v, g_lc + (a & 0x3FFF), 4); return __builtin_bswap32(v); }
    return hw_read(a, 4);
}
extern "C" u16 mmio_read16(u32 a) {
    if (ISVM(a)) { u16 v; memcpy(&v, VMP(a), 2); return __builtin_bswap16(v); }
    if ((a >> 28) == 0xE) { u16 v; memcpy(&v, g_lc + (a & 0x3FFF), 2); return __builtin_bswap16(v); }
    return (u16)hw_read(a, 2);
}
extern "C" u8 mmio_read8(u32 a) {
    if (ISVM(a)) return *VMP(a);
    if ((a >> 28) == 0xE) return g_lc[a & 0x3FFF];
    return (u8)hw_read(a, 1);
}
extern "C" void mmio_write32(u32 a, u32 v) {
    if (ISVM(a)) { v = __builtin_bswap32(v); memcpy(VMP(a), &v, 4); return; }
    if ((a >> 28) == 0xE) { v = __builtin_bswap32(v); memcpy(g_lc + (a & 0x3FFF), &v, 4); return; }
    hw_write(a, v, 4);
}
extern "C" void mmio_write16(u32 a, u16 v) {
    if (ISVM(a)) { v = __builtin_bswap16(v); memcpy(VMP(a), &v, 2); return; }
    if ((a >> 28) == 0xE) { v = __builtin_bswap16(v); memcpy(g_lc + (a & 0x3FFF), &v, 2); return; }
    hw_write(a, v, 2);
}
extern "C" void mmio_write8(u32 a, u8 v) {
    if (ISVM(a)) { *VMP(a) = v; return; }
    if ((a >> 28) == 0xE) { g_lc[a & 0x3FFF] = v; return; }
    hw_write(a, v, 1);
}
