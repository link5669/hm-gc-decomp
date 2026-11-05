// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_803637F4;
extern const f64 lbl_803637F8;
extern const f64 lbl_80363800;
void fn_80101624(f32 *, const f32 *, const f32 *, f32);

static inline f32 sqrtf_801009DC(f32 x) {
    volatile f32 y;
    if (x > lbl_803637F4) {
        f64 _half = lbl_803637F8;
        f64 _three = lbl_80363800;
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

#pragma opt_common_subs off
s32 fn_801009DC(const f32 *sphere, const f32 *start, const f32 *end, const f32 *len, const f32 *dir, f32 *out, f32 *outT, s32 inside) {
    f32 dx, dy, dz;
    f32 r2, d2, dot, disc, t;
    dx = sphere[0] - start[0];
    dz = sphere[2] - start[2];
    r2 = sphere[3] * sphere[3];
    dy = sphere[1] - start[1];
    d2 = dx * dx + dy * dy + dz * dz;
    if (d2 < r2) {
        return inside;
    }
    dot = dir[0] * dx + dir[1] * dy + dir[2] * dz;
    disc = dot * dot + (r2 - d2);
    if (disc <= lbl_803637F4) {
        return 0;
    }
    t = dot - sqrtf_801009DC(disc);
    if (t < lbl_803637F4 || t > *len) {
        return 0;
    }
    *outT = t / *len;
    fn_80101624(out, start, end, *outT);
    return 1;
}
#pragma opt_common_subs reset

} /* extern "C" */
