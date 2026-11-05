// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_801515F8(f32 m[4][4], const f32 *a, const f32 *b) {
    f32 dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    f32 d = dot + a[3];
    m[0][0] = d - b[0] * a[0];
    m[1][0] = -(b[1] * a[0]);
    m[2][0] = -(b[2] * a[0]);
    m[3][0] = -a[0];
    m[0][1] = -(b[0] * a[1]);
    m[1][1] = d - b[1] * a[1];
    m[2][1] = -(b[2] * a[1]);
    m[3][1] = -a[1];
    m[0][2] = -(b[0] * a[2]);
    m[1][2] = -(b[1] * a[2]);
    m[2][2] = d - b[2] * a[2];
    m[3][2] = -a[2];
    m[0][3] = -(b[0] * a[3]);
    m[1][3] = -(b[1] * a[3]);
    m[2][3] = -(b[2] * a[3]);
    m[3][3] = dot;
}

} /* extern "C" */
