// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_803637A4;
extern f32 lbl_803637A8;
extern f32 lbl_803637C4;
extern double fn_800F045C(double);
extern double fn_800F030C(double);

void fn_80100104(f32 *out, const f32 *a, const f32 *b, f32 t) {
    f32 sn;
    f32 omega;
    f32 bx, by, bz, bw;
    f32 s0;
    f32 inv;
    f32 s1;
    f32 dot;
    dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
    if (dot < lbl_803637A4) {
        dot = -dot;
        bx = -b[0];
        by = -b[1];
        bz = -b[2];
        bw = -b[3];
    } else {
        bx = b[0];
        by = b[1];
        bz = b[2];
        bw = b[3];
    }
    if (lbl_803637A8 - dot > lbl_803637C4) {
        omega = fn_800F045C(dot);
        sn = fn_800F030C(omega);
        inv = lbl_803637A8 / sn;
        { f32 omt = lbl_803637A8 - t; s0 = inv * (f32)fn_800F030C(omt * omega); }
        s1 = inv * (f32)fn_800F030C(t * omega);
    } else {
        s0 = lbl_803637A8 - t;
        s1 = t;
    }
    out[0] = s0 * a[0] + s1 * bx;
    out[1] = s0 * a[1] + s1 * by;
    out[2] = s0 * a[2] + s1 * bz;
    out[3] = s0 * a[3] + s1 * bw;
}

} /* extern "C" */
