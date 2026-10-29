// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern void *lbl_8035B738;
extern u8 lbl_802F29A0[];
extern f32 lbl_80357AE0[3];
extern f32 lbl_80366950;
extern f32 lbl_80366954;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void __ct__9C80257738Fv(void *p);

} /* extern "C" */
struct C800604C4 { C800604C4() { __ct__9C80257738Fv(this); } ~C800604C4(); };
struct V802F29A0 { u8 *vt; V802F29A0() { vt = lbl_802F29A0; } };
struct C8025E920 { C8025E920(); ~C8025E920(); };

struct N_8025C444 : C800604C4 {
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
    u8 pad188[0x1b0 - 0x188];
    N_8025C444() {
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
};
struct C8025E5B4 {
    u8 d[0x1b0];
    C8025E5B4();
    ~C8025E5B4();
};
extern "C" {

void *fn_8025C444(s32 n) {
    if (n <= 1) {
        N_8025C444 *p;
        if (!lbl_8035B738) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B738);
        p = new N_8025C444;
        fn_800F7E98();
        if (!p) fn_800604C4(-4, 0, 0, 0);
        return p;
    } else {
        C8025E5B4 *p;
        if (!lbl_8035B738) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B738);
        p = new C8025E5B4[n];
        fn_800F7E98();
        if (!p) fn_800604C4(-4, 0, 0, 0);
        return p;
    }
}

} /* extern "C" */
