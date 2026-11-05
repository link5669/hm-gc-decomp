// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { u8 pad[20]; const u16 *keys; } S8021C470;
f64 fn_800EFE78(f64 x);
static inline s32 First8021C470(const u16 *k) { return k[0]; }
#pragma opt_propagation off
void fn_8021C470(const S8021C470 *s, s32 start, s32 count, s32 len, s32 *outA, s32 *outB, f32 *outT, f32 x) {
    s32 B;
    const u16 *lo;
    const u16 *keys;
    s32 L;
    const u16 *mid;
    s32 t;
    s32 A;
    s32 den;
    const u16 *last;
    const u16 *hi;
    f32 num;
    s32 first;
    t = (s32)(f32)fn_800EFE78(x); keys = s->keys + start; first = First8021C470(keys); last = keys + count - 1;
    if (t < first) {
        L = *last;
        num = x + (f32)(len - L);
        den = (len - L) + First8021C470(keys);
        *outA = count - 1;
        *outB = 0;
    } else if (t >= (L = *last)) {
        num = x - (f32)L;
        den = (len - L) + First8021C470(keys);
        *outA = count - 1;
        *outB = 0;
    } else {
        lo = keys; hi = last;
        while (lo + 1 != hi) {
            mid = lo + ((hi - lo) >> 1);
            if (*mid > t) hi = mid; else lo = mid;
        }
        A = *lo; B = *hi;
        num = x - (f32)A;
        den = B - A;
        *outA = lo - keys;
        *outB = hi - keys;
    }
    *outT = num / (f32)den;
}
#pragma opt_propagation reset

} /* extern "C" */
