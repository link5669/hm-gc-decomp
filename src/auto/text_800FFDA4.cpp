// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_803637A0;
extern f32 lbl_803637A8;
#pragma fp_contract off
void fn_800FFDA4(const f32 *q, f32 *a, f32 *b, f32 *c) {
    f32 y, x, z, w, s, xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;
    x = q[0];
    y = q[1];
    z = q[2];
    w = q[3];
    s = lbl_803637A0 / (w * w + (z * z + (x * x + y * y)));
    xs = x * s;
    ys = y * s;
    zs = z * s;
    wx = w * xs;
    wy = w * ys;
    wz = w * zs;
    xx = x * xs;
    xy = x * ys;
    xz = x * zs;
    yy = y * ys;
    yz = y * zs;
    zz = z * zs;
    a[0] = lbl_803637A8 - (yy + zz);
    a[1] = xy - wz;
    a[2] = xz + wy;
    b[0] = xy + wz;
    b[1] = lbl_803637A8 - (xx + zz);
    b[2] = yz - wx;
    c[0] = xz - wy;
    c[1] = yz + wx;
    c[2] = lbl_803637A8 - (xx + yy);
}
#pragma fp_contract reset

} /* extern "C" */
