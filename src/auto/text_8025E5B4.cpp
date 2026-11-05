#include "common.h"

/* Uses the renamed symbol fn_8025E5B4 -> __ct__9C8025E5B4Fv (it is the constructor of C8025E5B4). */

extern "C" {
extern u8 lbl_802F29A0[];
extern f32 lbl_80357AE0[3];
extern f32 lbl_80366950;
extern f32 lbl_80366954;
}

struct C80257738 { C80257738(); ~C80257738(); };
struct V802F29A0 { u8 *vt; V802F29A0() { vt = lbl_802F29A0; } };
struct C8025E920 { C8025E920(); ~C8025E920(); };

struct C8025E5B4 : C80257738 {
    V802F29A0 m0;
    u8 pad4[0xcc - 4];
    s32 mCC;
    f32 mD0;
    f32 mD4;
    f32 mD8;
    u8 padDC[0x118 - 0xdc];
    f32 m118;
    s32 m11C;
    f32 m120;
    f32 m124;
    f32 m128;
    s32 m12C;
    s32 m130;
    u8 pad134[0x13c - 0x134];
    C8025E920 m13C;
    u8 pad13D[0x150 - 0x13d];
    s32 m150;
    u8 pad154[4];
    s32 m158;
    s32 m15C;
    f32 m160;
    u8 pad164[0x180 - 0x164];
    f32 m180;
    f32 m184;
    C8025E5B4();
};

C8025E5B4::C8025E5B4() {
    lbl_80357AE0[0] = lbl_80366950;
    lbl_80357AE0[1] = lbl_80366950;
    lbl_80357AE0[2] = lbl_80366950;
    m15C = 4;
    m158 = 0;
    m150 = 0;
    m160 = lbl_80366954;
    m180 = lbl_80366950;
    m184 = lbl_80366950;
    mCC = 0;
    mD0 = lbl_80366950;
    mD4 = lbl_80366950;
    mD8 = lbl_80366950;
    m118 = lbl_80366950;
    m11C = 0;
    m120 = lbl_80366950;
    m124 = lbl_80366950;
    m128 = lbl_80366950;
    m12C = 0;
    m130 = 0;
}
