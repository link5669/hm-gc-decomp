// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_802AFB98[];
extern u8 lbl_802AFAF0[];
extern volatile f32 lbl_8035BE98;
extern void *lbl_8035B738;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
} /* extern "C" */

struct C800665E0 {
    C800665E0();
    ~C800665E0();
    u8 pad[364];
};

struct C800374F4_inl : C800665E0 {
    f32 f364;
    f32 f368;
    f32 f372;
    f32 f376;
    f32 f380;
    s32 f384;
    s32 f388;
    s32 f392;
    void *f396;
    C800374F4_inl() {
        *(void **)this = lbl_802AFB98;
        f364 = lbl_8035BE98;
        f368 = lbl_8035BE98;
        f372 = lbl_8035BE98;
        f376 = lbl_8035BE98;
        f380 = lbl_8035BE98;
        f384 = -1;
        f392 = 0;
        f396 = lbl_802AFAF0;
    }
};

struct C800374F4 : C800665E0 {
    u8 body[36];
    C800374F4();
    ~C800374F4();
};

extern "C" {

C800374F4 *fn_8003519C(s32 n) {
    if (n <= 1) {
        C800374F4_inl *p;
        if (lbl_8035B738 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035B738);
        p = new C800374F4_inl;
        fn_800F7E98();
        if (p == 0) {
            fn_800604C4(-4, 0, 0, 0);
        }
        return (C800374F4 *)p;
    } else {
        C800374F4 *a;
        if (lbl_8035B738 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035B738);
        a = new C800374F4[n];
        fn_800F7E98();
        if (a == 0) {
            fn_800604C4(-4, 0, 0, 0);
        }
        return a;
    }
}

} /* extern "C" */
