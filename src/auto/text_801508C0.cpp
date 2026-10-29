// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef f32 M_08C0[3][4];
extern f32 lbl_8036453C;
extern volatile f32 lbl_80364544;
double fn_800F030C(double);
double fn_800EFDA4(double);
void fn_80150B38(void *self, M_08C0 m);

void fn_801508C0(void *self, f32 angle) {
    volatile f32 m[3][4];
    f32 s;
    f32 zero;
    f32 c;
    s = fn_800F030C(angle);
    c = fn_800EFDA4(angle);
    m[0][0] = lbl_8036453C;
    zero = lbl_80364544;
    m[0][1] = zero;
    m[0][2] = zero;
    m[1][0] = zero;
    m[1][1] = c;
    m[1][2] = s;
    m[2][0] = zero;
    m[2][1] = -s;
    m[2][2] = c;
    fn_80150B38(self, (f32 (*)[4])m);
}

} /* extern "C" */
