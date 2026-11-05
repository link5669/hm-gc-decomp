// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_803637A4;
extern f32 lbl_803637A8;
extern const f64 lbl_803637B0;
extern const f64 lbl_803637B8;

static inline f32 sqrtf_801002B0(f32 x) {
    volatile f32 y;
    if (x > lbl_803637A4) {
        f64 guess = __frsqrte((f64)x);
        guess = lbl_803637B0 * guess * __fnmsub(x, guess * guess, lbl_803637B8);
        guess = lbl_803637B0 * guess * __fnmsub(x, guess * guess, lbl_803637B8);
        guess = lbl_803637B0 * guess * __fnmsub(x, guess * guess, lbl_803637B8);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

typedef struct Quat801002B0 { f32 x, y, z, w; } Quat801002B0;

#pragma opt_common_subs off
#pragma fp_contract off
void fn_801002B0(Quat801002B0 *q) {
    f32 len2 = q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w;
    f32 inv;
    if (lbl_803637A4 == len2) {
        q->x = lbl_803637A4;
        q->y = lbl_803637A4;
        q->z = lbl_803637A4;
        q->w = lbl_803637A8;
        return;
    }
    inv = lbl_803637A8 / sqrtf_801002B0(len2);
    q->x *= inv;
    q->y *= inv;
    q->z *= inv;
    q->w *= inv;
}
#pragma fp_contract reset
#pragma opt_common_subs reset

} /* extern "C" */
