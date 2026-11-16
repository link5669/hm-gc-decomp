// Guest-memory helpers for native (GuestMem-translated) code. Compiled to x86-64 bitcode and linked into each
// translated unit before optimisation (llvm-link --only-needed --internalize), so they inline.
// Same semantics as runtime/ppc.h ld32/st32 (RAM fast path, MMIO slow path).
#include "../../runtime/ppc.h"
#include <stddef.h>
#define HM __attribute__((always_inline))

extern CPU g_cpu;

HM u8 hm_ld8(u32 a) { return ld8(a); }
HM u16 hm_ld16(u32 a) { return ld16(a); }
HM u32 hm_ld32(u32 a) { return ld32(a); }
HM u64 hm_ld64(u32 a) { return ld64(a); }
HM void hm_st8(u32 a, u8 v) { st8(a, v); }
HM void hm_st16(u32 a, u16 v) { st16(a, v); }
HM void hm_st32(u32 a, u32 v) { st32(a, v); }
HM void hm_st64(u32 a, u64 v) { st64(a, v); }

// volatile variants: the host access itself is volatile so it is never merged or hoisted
#define VRAM(a, T) (*(volatile T *)HP(a))
HM u8 hm_ldv8(u32 a) { if (likely(ISRAM(a))) return VRAM(a, u8); return mmio_read8(a); }
HM u16 hm_ldv16(u32 a) { if (likely(ISRAM(a))) return __builtin_bswap16(VRAM(a, u16)); return mmio_read16(a); }
HM u32 hm_ldv32(u32 a) { if (likely(ISRAM(a))) return __builtin_bswap32(VRAM(a, u32)); return mmio_read32(a); }
HM u64 hm_ldv64(u32 a) { return ((u64)hm_ldv32(a) << 32) | hm_ldv32(a + 4); }
HM void hm_stv8(u32 a, u8 v) { if (likely(ISRAM(a))) VRAM(a, u8) = v; else mmio_write8(a, v); }
HM void hm_stv16(u32 a, u16 v) { if (likely(ISRAM(a))) VRAM(a, u16) = __builtin_bswap16(v); else mmio_write16(a, v); }
HM void hm_stv32(u32 a, u32 v) { if (likely(ISRAM(a))) VRAM(a, u32) = __builtin_bswap32(v); else mmio_write32(a, v); }
HM void hm_stv64(u32 a, u64 v) { hm_stv32(a, (u32)(v >> 32)); hm_stv32(a + 4, (u32)v); }

static int ram_range(u32 a, u32 n) { return ISRAM(a) && (a & 0x01FFFFFFu) + (u64)n <= 0x02000000u; }
void hm_memmove(u32 d, u32 s, u32 n) {
    if (!n) return;
    if (ram_range(d, n) && ram_range(s, n)) { memmove(HP(d), HP(s), n); return; }
    if (d > s && d < s + n) { while (n--) st8(d + n, ld8(s + n)); return; }
    for (u32 i = 0; i < n; i++) st8(d + i, ld8(s + i));
}
void hm_memset(u32 d, u8 v, u32 n) {
    if (!n) return;
    if (ram_range(d, n)) { memset(HP(d), v, n); return; }
    for (u32 i = 0; i < n; i++) st8(d + i, v);
}
HM void hm_chk(void) { if (unlikely(rt_irq_flag)) rt_irq_check(&g_cpu); }

// host implementations of MWCC intrinsics the front end declares (mwcc_compat.h)
double hmh___frsqrte(double x) { return 1.0 / sqrt(x); }
float hmh___frsqrtes(float x) { return (float)(1.0 / sqrt((double)x)); }
double hmh___fres(double x) { return (double)(float)(1.0 / x); }
float hmh___fress(float x) { return (float)(1.0 / (double)x); }
float hmh_fmaf(float a, float b, float c) { return fmaf(a, b, c); }
double hmh_fma(double a, double b, double c) { return fma(a, b, c); }
