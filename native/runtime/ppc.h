// Guest CPU state and helpers used by recompiled code (build/native/gen/*.c) and the runtime.
#pragma once
#include <stdint.h>
#include <string.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#define RESTRICT __restrict__
#else
#define RESTRICT restrict
#endif

typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32; typedef uint64_t u64;
typedef int8_t s8; typedef int16_t s16; typedef int32_t s32; typedef int64_t s64;

typedef union { double d; u64 u; } FPR;

typedef struct CPU {
    u32 r[32];
    FPR f[32];          // ps0 / FPR
    double ps1[32];     // paired-single slot 1
    u8 cr[8];           // per field: 8=LT 4=GT 2=EQ 1=SO
    u32 lr, ctr;
    u8 so, ov, ca, _pad;
    u32 msr, fpscr;
    u32 gqr[8];
    u32 spr[1024];      // everything else (SRR0/1, SPRGs, HIDs, DAR, ...)
} CPU;

// Guest RAM is mapped at a fixed host address (runtime/mem.cpp maps 32 MiB there).
#define RAM ((u8 *)0x200000000ULL)
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

u32 mmio_read32(u32 a); u16 mmio_read16(u32 a); u8 mmio_read8(u32 a);
void mmio_write32(u32 a, u32 v); void mmio_write16(u32 a, u16 v); void mmio_write8(u32 a, u8 v);

#define ISRAM(a) (((a) & 0x3E000000u) == 0)
#define HP(a) (RAM + ((a) & 0x01FFFFFFu))

static inline u32 ld32(u32 a) { u32 v; if (likely(ISRAM(a))) { __builtin_memcpy(&v, HP(a), 4); return __builtin_bswap32(v); } return mmio_read32(a); }
static inline u16 ld16(u32 a) { u16 v; if (likely(ISRAM(a))) { __builtin_memcpy(&v, HP(a), 2); return __builtin_bswap16(v); } return mmio_read16(a); }
static inline u8 ld8(u32 a) { if (likely(ISRAM(a))) return *HP(a); return mmio_read8(a); }
static inline void st32(u32 a, u32 v) { if (likely(ISRAM(a))) { v = __builtin_bswap32(v); __builtin_memcpy(HP(a), &v, 4); } else mmio_write32(a, v); }
static inline void st16(u32 a, u16 v) { if (likely(ISRAM(a))) { v = __builtin_bswap16(v); __builtin_memcpy(HP(a), &v, 2); } else mmio_write16(a, v); }
static inline void st8(u32 a, u8 v) { if (likely(ISRAM(a))) *HP(a) = v; else mmio_write8(a, v); }
static inline u64 ld64(u32 a) { return ((u64)ld32(a) << 32) | ld32(a + 4); }
static inline void st64(u32 a, u64 v) { st32(a, (u32)(v >> 32)); st32(a + 4, (u32)v); }
static inline float ldf32(u32 a) { u32 v = ld32(a); float f; __builtin_memcpy(&f, &v, 4); return f; }
static inline void stf32(u32 a, float f) { u32 v; __builtin_memcpy(&v, &f, 4); st32(a, v); }
static inline double u2d(u64 u) { double d; __builtin_memcpy(&d, &u, 8); return d; }
static inline u64 d2u(double d) { u64 u; __builtin_memcpy(&u, &d, 8); return u; }
static inline double rs(double x) { return (double)(float)x; }   // round to single
static inline u32 rotl(u32 v, u32 n) { n &= 31; return n ? (v << n) | (v >> (32 - n)) : v; }

static inline u8 cmp_s(s32 a, s32 b, u8 so) { return (a < b ? 8 : a > b ? 4 : 2) | so; }
static inline u8 cmp_u(u32 a, u32 b, u8 so) { return (a < b ? 8 : a > b ? 4 : 2) | so; }
static inline u8 cmp_f(double a, double b) { return a < b ? 8 : a > b ? 4 : a == b ? 2 : 1; }
#define CRBIT(c, bi) (((c)->cr[(bi) >> 2] >> (3 - ((bi) & 3))) & 1)
#define SETCRBIT(c, bi, v) ((c)->cr[(bi) >> 2] = (u8)(((c)->cr[(bi) >> 2] & ~(1 << (3 - ((bi) & 3)))) | ((v) << (3 - ((bi) & 3)))))

// runtime services
typedef void (*GuestFn)(CPU *RESTRICT);
void rt_call(CPU *RESTRICT c, u32 addr);             // indirect call
void rt_irq_check(CPU *RESTRICT c);                  // deliver pending interrupts (if MSR[EE])
extern volatile int rt_irq_flag;
#define CHK(c) do { if (unlikely(rt_irq_flag)) rt_irq_check(c); } while (0)
void rt_mtmsr(CPU *RESTRICT c, u32 v);
u32 rt_mfspr(CPU *RESTRICT c, u32 n);
void rt_mtspr(CPU *RESTRICT c, u32 n, u32 v);
u32 rt_mftb(CPU *RESTRICT c, int upper);
void rt_psq_l(CPU *RESTRICT c, u32 ea, int fd, int w, int i);
void rt_psq_st(CPU *RESTRICT c, u32 ea, int fs, int w, int i);
void rt_dcbz(u32 ea);
void rt_trap(CPU *RESTRICT c, u32 pc);
void rt_sc(CPU *RESTRICT c, u32 pc);
void rt_rfi(CPU *RESTRICT c, u32 pc);
void rt_unimpl(CPU *RESTRICT c, u32 pc, u32 ins);
// OSSaveContext call sites: setjmp in the caller's frame (see runtime/os.cpp)
#include <setjmp.h>
jmp_buf *rt_save_jb(CPU *RESTRICT c);
void rt_after_save(CPU *RESTRICT c);

static inline double fres_(double x) { return rs(1.0 / x); }
static inline double frsqrte_(double x) { return 1.0 / sqrt(x); }
static inline u64 fctiwz_(double x) {
    s32 v; if (x != x) v = (s32)0x80000000; else if (x >= 2147483647.0) v = 0x7FFFFFFF; else if (x <= -2147483648.0) v = (s32)0x80000000; else v = (s32)x;
    return 0xFFF8000000000000ULL | (u32)v;
}
static inline u64 fctiw_(double x) {
    s32 v; if (x != x) v = (s32)0x80000000; else if (x >= 2147483647.0) v = 0x7FFFFFFF; else if (x <= -2147483648.0) v = (s32)0x80000000; else v = (s32)nearbyint(x);
    return 0xFFF8000000000000ULL | (u32)v;
}
static inline u32 divw_(u32 a, u32 b) { if (b == 0 || (a == 0x80000000u && b == 0xFFFFFFFFu)) return ((s32)a < 0 && b == 0) ? 0xFFFFFFFFu : (b == 0 ? 0 : 0x80000000u); return (u32)((s32)a / (s32)b); }
static inline u32 divwu_(u32 a, u32 b) { return b ? a / b : 0; }

#ifdef __cplusplus
}
#endif
