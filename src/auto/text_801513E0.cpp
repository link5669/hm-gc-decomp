// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_801513E0(f32 (*a)[4], f32 (*b)[4]) {
    f32 x0 = a[0][0];
    f32 y0 = a[0][1];
    f32 z0 = a[0][2];
    f32 x1 = a[1][0];
    f32 y1 = a[1][1];
    f32 z1 = a[1][2];
    f32 x2 = a[2][0];
    f32 y2 = a[2][1];
    f32 z2 = a[2][2];
    f32 x3 = a[3][0];
    f32 y3 = a[3][1];
    f32 z3 = a[3][2];

    a[0][0] = x0 * b[0][0] + y0 * b[1][0] + z0 * b[2][0];
    a[0][1] = x0 * b[0][1] + y0 * b[1][1] + z0 * b[2][1];
    a[0][2] = x0 * b[0][2] + y0 * b[1][2] + z0 * b[2][2];
    a[1][0] = x1 * b[0][0] + y1 * b[1][0] + z1 * b[2][0];
    a[1][1] = x1 * b[0][1] + y1 * b[1][1] + z1 * b[2][1];
    a[1][2] = x1 * b[0][2] + y1 * b[1][2] + z1 * b[2][2];
    a[2][0] = x2 * b[0][0] + y2 * b[1][0] + z2 * b[2][0];
    a[2][1] = x2 * b[0][1] + y2 * b[1][1] + z2 * b[2][1];
    a[2][2] = x2 * b[0][2] + y2 * b[1][2] + z2 * b[2][2];
    a[3][0] = x3 * b[0][0] + y3 * b[1][0] + z3 * b[2][0];
    a[3][1] = x3 * b[0][1] + y3 * b[1][1] + z3 * b[2][1];
    a[3][2] = x3 * b[0][2] + y3 * b[1][2] + z3 * b[2][2];
}

} /* extern "C" */
