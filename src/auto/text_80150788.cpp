// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef f32 M80150788[3][4];
extern volatile f32 lbl_80364544;
extern volatile f32 lbl_8036453C;
double fn_800F030C(double);
double fn_800EFDA4(double);
void fn_80150B38(void *, M80150788);
void fn_80150788(void *self, f32 a) {
    volatile f32 m[3][4];
    f32 zero, one; f32 s, c;
    s = fn_800F030C(a);
    c = fn_800EFDA4(a);
    m[0][1] = s;
    m[0][0] = c;
    zero = lbl_80364544;
    m[0][2] = zero;
    m[1][0] = -s;
    m[1][1] = c;
    m[1][2] = zero;
    m[2][0] = zero;
    m[2][1] = zero;
    one = lbl_8036453C;
    m[2][2] = one;
    fn_80150B38(self, (f32 (*)[4])m);
}

} /* extern "C" */
