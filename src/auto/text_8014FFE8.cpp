/* Functions from 0x8014FFE8 to 0x8015012C, found by decomp-toolkit. */
#include "common.h"

extern "C" {


/* QV=2.0p1 */
void fn_8014FFE8(f32 *dst, const f32 *src) {
    extern f32 lbl_8036453C;
    extern f32 lbl_80364544;
    dst[3] = -(src[3] * src[0] + src[7] * src[4] + src[11] * src[8]);
    dst[7] = -(src[3] * src[1] + src[7] * src[5] + src[11] * src[9]);
    dst[11] = -(src[3] * src[2] + src[7] * src[6] + src[11] * src[10]);
    dst[15] = lbl_8036453C;
    dst[0] = src[0];
    dst[4] = src[1];
    dst[8] = src[2];
    dst[12] = lbl_80364544;
    dst[1] = src[4];
    dst[5] = src[5];
    dst[9] = src[6];
    dst[13] = lbl_80364544;
    dst[2] = src[8];
    dst[6] = src[9];
    dst[10] = src[10];
    dst[14] = lbl_80364544;
}
void fn_80150090(void *arg0) {
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;
    f32 temp_f4;
    f32 temp_f5;

    temp_f5 = M2C_FIELD(arg0, f32 *, 0x1C);
    temp_f4 = M2C_FIELD(arg0, f32 *, 0xC);
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) -((M2C_FIELD(arg0, f32 *, 0x2C) * M2C_FIELD(arg0, f32 *, 0x20)) + ((temp_f4 * M2C_FIELD(arg0, f32 *, 0)) + (temp_f5 * M2C_FIELD(arg0, f32 *, 0x10))));
    M2C_FIELD(arg0, f32 *, 0x1C) = (f32) -((M2C_FIELD(arg0, f32 *, 0x2C) * M2C_FIELD(arg0, f32 *, 0x24)) + ((temp_f4 * M2C_FIELD(arg0, f32 *, 4)) + (temp_f5 * M2C_FIELD(arg0, f32 *, 0x14))));
    M2C_FIELD(arg0, f32 *, 0x2C) = (f32) -((M2C_FIELD(arg0, f32 *, 0x2C) * M2C_FIELD(arg0, f32 *, 0x28)) + ((temp_f4 * M2C_FIELD(arg0, f32 *, 8)) + (temp_f5 * M2C_FIELD(arg0, f32 *, 0x18))));
    temp_f1 = M2C_FIELD(arg0, f32 *, 0x10);
    temp_f2 = M2C_FIELD(arg0, f32 *, 0x20);
    temp_f3 = M2C_FIELD(arg0, f32 *, 0x24);
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) M2C_FIELD(arg0, f32 *, 4);
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) M2C_FIELD(arg0, f32 *, 8);
    M2C_FIELD(arg0, f32 *, 4) = temp_f1;
    M2C_FIELD(arg0, f32 *, 0x24) = (f32) M2C_FIELD(arg0, f32 *, 0x18);
    M2C_FIELD(arg0, f32 *, 8) = temp_f2;
    M2C_FIELD(arg0, f32 *, 0x18) = temp_f3;
}

} /* extern "C" */
