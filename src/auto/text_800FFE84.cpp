// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
double fn_800F030C(double);
double fn_800EFDA4(double);
extern f32 lbl_803637C0;
void fn_800FFE84(f32 *q, const f32 *axis, f32 angle) {
    f32 s;
    f32 c;
    f32 h;
    h = lbl_803637C0 * angle;
    s = fn_800F030C(h);
    c = fn_800EFDA4(h);
    q[3] = c;
    q[0] = s * axis[0];
    q[1] = s * axis[1];
    q[2] = s * axis[2];
}

} /* extern "C" */
