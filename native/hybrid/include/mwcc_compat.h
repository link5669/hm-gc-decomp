/* MWCC -> clang shims for the hybrid native front end. Included with -include before every unit.
 * __MWERKS__ is NOT defined: headers take their portable (non-asm) paths. */
#ifndef MWCC_COMPAT_H
#define MWCC_COMPAT_H

#ifdef __cplusplus
extern "C" {
#endif
/* estimates: exact PPC table semantics are provided by the runtime (linked by name) */
double __frsqrte(double);
float __frsqrtes(float);
double __fres(double);
float __fress(float);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
void *memset(void *, int, unsigned int);
void *memcpy(void *, const void *, unsigned int);
void *memmove(void *, const void *, unsigned int);
int memcmp(const void *, const void *, unsigned int);
unsigned int strlen(const char *);
}
#endif

#define __fabs(x) __builtin_fabs(x)
#define __fabsf(x) __builtin_fabsf(x)
#define __fnabs(x) (-__builtin_fabs(x))
#define __fsel(c, a, b) (((c) >= 0.0) ? (a) : (b))
#define __abs(x) ({ int __x = (x); __x < 0 ? -__x : __x; })
#define __cntlzw(x) ({ unsigned __x = (unsigned)(x); __x ? (unsigned)__builtin_clz(__x) : 32u; })
#define __rlwinm(x, sh, mb, me) \
  ({ unsigned __x = (unsigned)(x); unsigned __r = ((__x << ((sh) & 31)) | (__x >> ((32 - (sh)) & 31))); \
     unsigned __m = ((mb) <= (me)) ? ((0xFFFFFFFFu >> (mb)) & (0xFFFFFFFFu << (31 - (me)))) \
                                   : ((0xFFFFFFFFu >> (mb)) | (0xFFFFFFFFu << (31 - (me)))); \
     __r & __m; })
/* __rlwimi(a, b, sh, mb, me): insert rotl(b, sh) under mask(mb..me) into a */
#define __rlwimi(a, b, sh, mb, me) \
  ({ unsigned __a = (unsigned)(a); unsigned __b = (unsigned)(b); \
     unsigned __r = ((__b << ((sh) & 31)) | (__b >> ((32 - (sh)) & 31))); \
     unsigned __m = ((mb) <= (me)) ? ((0xFFFFFFFFu >> (mb)) & (0xFFFFFFFFu << (31 - (me)))) \
                                   : ((0xFFFFFFFFu >> (mb)) | (0xFFFFFFFFu << (31 - (me)))); \
     (__r & __m) | (__a & ~__m); })
#define __fmadds(a, b, c) __builtin_fmaf((a), (b), (c))
#define __fmsubs(a, b, c) __builtin_fmaf((a), (b), -(c))
#define __fnmadds(a, b, c) (-__builtin_fmaf((a), (b), (c)))
#define __fnmsubs(a, b, c) (-__builtin_fmaf((a), (b), -(c)))
#define __fmadd(a, b, c) __builtin_fma((a), (b), (c))
#define __fmsub(a, b, c) __builtin_fma((a), (b), -(c))
#define __fnmadd(a, b, c) (-__builtin_fma((a), (b), (c)))
#define __fnmsub(a, b, c) (-__builtin_fma((a), (b), -(c)))
#define __sync() ((void)0)
#define __isync() ((void)0)
#define __eieio() ((void)0)
#define __dcbf(a, b) ((void)0)
#define __dcbz(a, b) ((void)0)
#define __dcbt(a, b) ((void)0)
#define __dcbst(a, b) ((void)0)
#define __dcbi(a, b) ((void)0)
#define __icbi(a, b) ((void)0)

/* byte-reversed loads/stores (MWCC: __lhbrx(base, offset)) */
static inline unsigned short __hm_bswap16(unsigned short v) { return (unsigned short)((v << 8) | (v >> 8)); }
static inline unsigned __hm_bswap32(unsigned v) { return __builtin_bswap32(v); }
#define __lhbrx(p, o) ((unsigned short)__hm_bswap16(*(volatile unsigned short *)((char *)(p) + (o))))
#define __lwbrx(p, o) ((unsigned)__hm_bswap32(*(volatile unsigned *)((char *)(p) + (o))))
#define __sthbrx(v, p, o) (*(volatile unsigned short *)((char *)(p) + (o)) = __hm_bswap16((unsigned short)(v)))
#define __stwbrx(v, p, o) (*(volatile unsigned *)((char *)(p) + (o)) = __hm_bswap32((unsigned)(v)))

#endif
