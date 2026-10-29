// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_8036453C;
extern f32 lbl_80364540;

#pragma fp_contract off
void fn_80152234(f32 *m, const f32 *q) {
    f32 ys;
    f32 xs;
    f32 y;
    f32 x;
    f32 z;
    f32 yz;
    f32 s;
    f32 w;
    f32 zs;
    f32 wx;
    f32 wy;
    f32 xx;
    f32 wz;
    f32 xy;
    f32 xz;
    f32 yy;
    f32 zz;
    x = q[0];
    y = q[1];
    z = q[2];
    w = q[3];
    s = lbl_80364540 / (w * w + (z * z + (x * x + y * y)));
    zs = z * s;
    ys = y * s;
    xs = x * s;
    zz = z * zs;
    yy = y * ys;
    xx = x * xs;
    wz = w * zs;
    xy = x * ys;
    wy = w * ys;
    xz = x * zs;
    m[0] = lbl_8036453C - (yy + zz);
    m[1] = xy + wz;
    wx = w * xs;
    yz = y * zs;
    m[2] = xz - wy;
    m[4] = xy - wz;
    m[5] = lbl_8036453C - (xx + zz);
    m[6] = yz + wx;
    m[8] = xz + wy;
    m[9] = yz - wx;
    m[10] = lbl_8036453C - (xx + yy);
}
#pragma fp_contract reset

} /* extern "C" */
