/* Functions from 0x80151710 to 0x80151958, found by decomp-toolkit. */
#include "common.h"

extern "C" {
extern f32 lbl_80364540;
extern f32 lbl_8036453C;
extern f32 lbl_80364544;


/* QV=2.0p1 */
void fn_80151710(f32 m[4][4], const f32 *p) {
    f32 x2;
    f32 y2 = p[1];
    f32 z2 = p[2];
    f32 x = p[0];
    x2 = x * lbl_80364540;
    y2 *= lbl_80364540;
    z2 *= lbl_80364540;
    m[0][0] = lbl_8036453C - x2 * x;
    m[1][0] = -(x2 * p[1]);
    m[2][0] = -(x2 * p[2]);
    m[3][0] = lbl_80364544;
    m[0][1] = -(y2 * x);
    m[1][1] = lbl_8036453C - y2 * p[1];
    m[2][1] = -(y2 * p[2]);
    m[3][1] = lbl_80364544;
    m[0][2] = -(z2 * x);
    m[1][2] = -(z2 * p[1]);
    m[2][2] = lbl_8036453C - z2 * p[2];
    m[3][2] = lbl_80364544;
    x2 *= -p[3];
    y2 *= -p[3];
    z2 *= -p[3];
    m[0][3] = x2;
    m[1][3] = y2;
    m[2][3] = z2;
    m[3][3] = lbl_8036453C;
}
void fn_801517E4(void *arg0, f32 farg0, f32 farg1) {
    extern f32 lbl_8036453C;
    extern f32 lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0) = (f32) lbl_8036453C;
    M2C_FIELD(arg0, f32 *, 4) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 8) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x10) = farg0;
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) lbl_8036453C;
    M2C_FIELD(arg0, f32 *, 0x18) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x1C) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x20) = farg1;
    M2C_FIELD(arg0, f32 *, 0x24) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x28) = (f32) lbl_8036453C;
    M2C_FIELD(arg0, f32 *, 0x2C) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x30) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x38) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) lbl_8036453C;
}

void fn_80151860(void *arg0, f32 farg0, f32 farg1) {
    extern f32 lbl_8036453C;
    extern f32 lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0) = (f32) lbl_8036453C;
    M2C_FIELD(arg0, f32 *, 4) = farg0;
    M2C_FIELD(arg0, f32 *, 8) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) lbl_8036453C;
    M2C_FIELD(arg0, f32 *, 0x18) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x1C) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x24) = farg1;
    M2C_FIELD(arg0, f32 *, 0x28) = (f32) lbl_8036453C;
    M2C_FIELD(arg0, f32 *, 0x2C) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x30) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x38) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) lbl_8036453C;
}

void fn_801518DC(void *arg0, f32 farg0, f32 farg1) {
    extern f32 lbl_8036453C;
    extern f32 lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0) = (f32) lbl_8036453C;
    M2C_FIELD(arg0, f32 *, 4) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 8) = farg0;
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) lbl_8036453C;
    M2C_FIELD(arg0, f32 *, 0x18) = farg1;
    M2C_FIELD(arg0, f32 *, 0x1C) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x24) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x28) = (f32) lbl_8036453C;
    M2C_FIELD(arg0, f32 *, 0x2C) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x30) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x38) = (f32) lbl_80364544;
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) lbl_8036453C;
}

} /* extern "C" */
