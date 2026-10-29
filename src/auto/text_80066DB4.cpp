// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u32 lbl_8035B738;
extern f32 lbl_8035E758;
extern u8 lbl_802BD3A8[];
extern u8 lbl_802BD300[];
void fn_800604C4(s32 code, s32 a, s32 b, s32 c);
void fn_800F7EC0(u32 heap);
void fn_800F7E98(void);
} /* extern "C" */
struct C800665E0 { u8 b[364]; C800665E0(); };
struct C8006900C : C800665E0 {
    f32 f364;
    f32 f368;
    u32 f372;
    u32 f376;
    u32 f380;
    u32 f384;
    u32 f388;
    u8 pad392[408 - 392];
    u32 f408;
    u32 f412;
    u32 f416;
    f32 f420;
    u32 f424;
    u32 f428;
    void *f432;
    C8006900C();
    ~C8006900C();
};
struct C8006900C_A : C800665E0 {
    f32 f364;
    f32 f368;
    u32 f372;
    u32 f376;
    u32 f380;
    u32 f384;
    u32 f388;
    u8 pad392[408 - 392];
    u32 f408;
    u32 f412;
    u32 f416;
    f32 f420;
    u32 f424;
    u32 f428;
    void *f432;
    C8006900C_A() {
        *(void **)this = lbl_802BD3A8;
        f388 = 0;
        f364 = lbl_8035E758;
        f368 = lbl_8035E758;
        f372 = 0;
        f376 = 0;
        f380 = 0;
        f416 = 0;
        f420 = lbl_8035E758;
        f408 = 0;
        f428 = 0;
        f432 = lbl_802BD300;
    }
};
extern "C" {
C8006900C *fn_80066DB4(s32 n) {
    C8006900C *p;
    if (n <= 1) {
        if (lbl_8035B738 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B738);
        p = (C8006900C *)new C8006900C_A;
        fn_800F7E98();
        if (p == 0) fn_800604C4(-4, 0, 0, 0);
        return p;
    } else {
        if (lbl_8035B738 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B738);
        p = new C8006900C[n];
        fn_800F7E98();
        if (p == 0) fn_800604C4(-4, 0, 0, 0);
        return p;
    }
}

} /* extern "C" */
