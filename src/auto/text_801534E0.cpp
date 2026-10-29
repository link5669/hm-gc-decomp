/* Functions from 0x801534E0 to 0x80153B24, found by decomp-toolkit. */
#include "common.h"

extern "C" {

typedef struct {
    f32 m[4][4];
} Mtx44Struct;

extern f32 lbl_80364564;
extern f32 lbl_80364560;

f32 fn_80153574(f32 *m) {
    return m[10] * (m[0] * m[5]) + m[8] * (m[1] * m[6]) + m[9] * (m[2] * m[4])
         - m[8] * (m[2] * m[5]) - m[10] * (m[1] * m[4]) - m[9] * (m[0] * m[6]);
}

void fn_801535CC(void *arg0, f32 farg0) {
    M2C_FIELD(arg0, f32 *, 0) = (f32) (M2C_FIELD(arg0, f32 *, 0) * farg0);
    M2C_FIELD(arg0, f32 *, 4) = (f32) (M2C_FIELD(arg0, f32 *, 4) * farg0);
    M2C_FIELD(arg0, f32 *, 8) = (f32) (M2C_FIELD(arg0, f32 *, 8) * farg0);
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) (M2C_FIELD(arg0, f32 *, 0x10) * farg0);
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) (M2C_FIELD(arg0, f32 *, 0x14) * farg0);
    M2C_FIELD(arg0, f32 *, 0x18) = (f32) (M2C_FIELD(arg0, f32 *, 0x18) * farg0);
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) (M2C_FIELD(arg0, f32 *, 0x20) * farg0);
    M2C_FIELD(arg0, f32 *, 0x24) = (f32) (M2C_FIELD(arg0, f32 *, 0x24) * farg0);
    M2C_FIELD(arg0, f32 *, 0x28) = (f32) (M2C_FIELD(arg0, f32 *, 0x28) * farg0);
}

void fn_8015363C(f32 *m, f32 v) {
    m[0] = lbl_80364560;
    m[1] = lbl_80364564;
    m[2] = lbl_80364564;
    m[3] = lbl_80364564;
    m[4] = lbl_80364564;
    m[5] = lbl_80364560;
    m[6] = lbl_80364564;
    m[7] = lbl_80364564;
    m[8] = lbl_80364564;
    m[9] = lbl_80364564;
    m[10] = v;
    m[11] = lbl_80364564;
    m[12] = lbl_80364564;
    m[13] = lbl_80364564;
    m[14] = lbl_80364564;
    m[15] = lbl_80364560;
}

void fn_801536BC(f32 *m, f32 v) {
    m[0] = lbl_80364560;
    m[1] = lbl_80364564;
    m[2] = lbl_80364564;
    m[3] = lbl_80364564;
    m[4] = lbl_80364564;
    m[5] = v;
    m[6] = lbl_80364564;
    m[7] = lbl_80364564;
    m[8] = lbl_80364564;
    m[9] = lbl_80364564;
    m[10] = lbl_80364560;
    m[11] = lbl_80364564;
    m[12] = lbl_80364564;
    m[13] = lbl_80364564;
    m[14] = lbl_80364564;
    m[15] = lbl_80364560;
}

void fn_8015373C(f32* m, f32 x) {
    m[0] = x;
    m[1] = lbl_80364564;
    m[2] = lbl_80364564;
    m[3] = lbl_80364564;
    m[4] = lbl_80364564;
    m[5] = lbl_80364560;
    m[6] = lbl_80364564;
    m[7] = lbl_80364564;
    m[8] = lbl_80364564;
    m[9] = lbl_80364564;
    m[10] = lbl_80364560;
    m[11] = lbl_80364564;
    m[12] = lbl_80364564;
    m[13] = lbl_80364564;
    m[14] = lbl_80364564;
    m[15] = lbl_80364560;
}

void fn_801537BC(f32* m, f32* v) {
    f32 a = v[0];
    f32 b = v[1];
    f32 c = v[2];
    m[0] = a;
    m[1] = lbl_80364564;
    m[2] = lbl_80364564;
    m[3] = lbl_80364564;
    m[4] = lbl_80364564;
    m[5] = b;
    m[6] = lbl_80364564;
    m[7] = lbl_80364564;
    m[8] = lbl_80364564;
    m[9] = lbl_80364564;
    m[10] = c;
    m[11] = lbl_80364564;
    m[12] = lbl_80364564;
    m[13] = lbl_80364564;
    m[14] = lbl_80364564;
    m[15] = lbl_80364560;
}

void fn_80153840(f32* m, f32 x) {
    m[0] = x;
    m[1] = lbl_80364564;
    m[2] = lbl_80364564;
    m[3] = lbl_80364564;
    m[4] = lbl_80364564;
    m[5] = x;
    m[6] = lbl_80364564;
    m[7] = lbl_80364564;
    m[8] = lbl_80364564;
    m[9] = lbl_80364564;
    m[10] = x;
    m[11] = lbl_80364564;
    m[12] = lbl_80364564;
    m[13] = lbl_80364564;
    m[14] = lbl_80364564;
    m[15] = lbl_80364560;
}

#pragma scheduling off
void fn_801538B8(void *arg0, void *arg1) {
    f32 a = M2C_FIELD(arg1, f32 *, 0);
    f32 b = M2C_FIELD(arg1, f32 *, 4);
    f32 c;
    M2C_FIELD(arg0, f32 *, 0) = a;
    c = M2C_FIELD(arg1, f32 *, 8);
    M2C_FIELD(arg0, f32 *, 0x14) = b;
    M2C_FIELD(arg0, f32 *, 0x28) = c;
    M2C_FIELD(arg0, f32 *, 4) = lbl_80364564;
    M2C_FIELD(arg0, f32 *, 8) = lbl_80364564;
    M2C_FIELD(arg0, f32 *, 0x10) = lbl_80364564;
    M2C_FIELD(arg0, f32 *, 0x18) = lbl_80364564;
    M2C_FIELD(arg0, f32 *, 0x20) = lbl_80364564;
    M2C_FIELD(arg0, f32 *, 0x24) = lbl_80364564;
}
#pragma scheduling reset
void fn_80153904(f32* m) {
    m[0] = lbl_80364564;
    m[1] = lbl_80364564;
    m[2] = lbl_80364564;
    m[3] = lbl_80364564;
    m[4] = lbl_80364564;
    m[5] = lbl_80364564;
    m[6] = lbl_80364564;
    m[7] = lbl_80364564;
    m[8] = lbl_80364564;
    m[9] = lbl_80364564;
    m[10] = lbl_80364564;
    m[11] = lbl_80364564;
    m[12] = lbl_80364564;
    m[13] = lbl_80364564;
    m[14] = lbl_80364564;
    m[15] = lbl_80364564;
}

extern f32 lbl_80364560;
void fn_80153988(f32* m) {
    m[0] = lbl_80364560;
    m[1] = lbl_80364560;
    m[2] = lbl_80364560;
    m[3] = lbl_80364560;
    m[4] = lbl_80364560;
    m[5] = lbl_80364560;
    m[6] = lbl_80364560;
    m[7] = lbl_80364560;
    m[8] = lbl_80364560;
    m[9] = lbl_80364560;
    m[10] = lbl_80364560;
    m[11] = lbl_80364560;
    m[12] = lbl_80364560;
    m[13] = lbl_80364560;
    m[14] = lbl_80364560;
    m[15] = lbl_80364560;
}

void fn_80153A0C(f32 *__restrict d, f32 *__restrict s) {
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = s[3];
    d[4] = s[4];
    d[5] = s[5];
    d[6] = s[6];
    d[7] = s[7];
    d[8] = s[8];
    d[9] = s[9];
    d[10] = s[10];
    d[11] = s[11];
    d[12] = s[12];
    d[13] = s[13];
    d[14] = s[14];
    d[15] = s[15];
}


s32 fn_80153A90(void) {
    return 0;
}

s32 fn_80153A98(void) {
    return 0;
}

s32 fn_80153AA0(void) {
    return 0;
}

s32 fn_80153AA8(void) {
    return 0;
}

s32 fn_80153AB0(void) {
    return 0;
}

s32 fn_80153AB8(void) {
    return 0;
}

s32 fn_80153AC0(void) {
    return 0xFFFF;
}

s32 fn_80153ACC(void) {
    return 0xFFFF;
}

u32 fn_80153AD8(u8* arg0, u32 arg1, u32 arg2) {
    u32 i;
    u32 max = 0;
    u32 n = *(u32*)(arg0 + 0x78);
    for (i = 0; i < n; i++) {
        if (arg1 == *(u32*)(arg0 + 0x7C) && arg2 == *(u32*)(arg0 + 0x80)) {
            if (*(u16*)(arg0 + 0x86) > max) {
                max = *(u16*)(arg0 + 0x86);
            }
        }
        arg0 += 0x24;
    }
    return max;
}

/* QV=2.0p1 */
void fn_801534E0(f32 *__restrict d, f32 *__restrict s) {
    d[0] = s[5]*s[10] - s[6]*s[9];
    d[1] = -(s[1]*s[10] - s[2]*s[9]);
    d[2] = s[1]*s[6] - s[2]*s[5];
    d[4] = -(s[4]*s[10] - s[6]*s[8]);
    d[5] = s[0]*s[10] - s[2]*s[8];
    d[6] = -(s[0]*s[6] - s[2]*s[4]);
    d[8] = s[4]*s[9] - s[5]*s[8];
    d[9] = -(s[0]*s[9] - s[1]*s[8]);
    d[10] = s[0]*s[5] - s[1]*s[4];
}

} /* extern "C" */
