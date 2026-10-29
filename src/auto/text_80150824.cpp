// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef f32 M80150824[3][4];
extern volatile f32 lbl_80364544;
extern volatile f32 lbl_8036453C;
double fn_800F030C(double);
double fn_800EFDA4(double);
void fn_80150B38(void *, M80150824);
void fn_80150824(void *self, f32 a) {
    volatile f32 m[3][4];
    f32 zero, one; f32 s, c;
    s = fn_800F030C(a);
    c = fn_800EFDA4(a);
    m[0][0] = c;
    zero = lbl_80364544;
    m[0][1] = zero;
    m[0][2] = -s;
    m[1][0] = zero;
    one = lbl_8036453C;
    m[1][1] = one;
    m[1][2] = zero;
    m[2][0] = s;
    m[2][1] = zero;
    m[2][2] = c;
    fn_80150B38(self, (f32 (*)[4])m);
}

} /* extern "C" */
