// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_802BCCA8[];
extern volatile f32 lbl_8035E4A8;
extern f32 lbl_8035E4CC;
extern void *lbl_8035B320;
void __ct__9C80233124Fv(void *);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
} /* extern "C" */

struct C80233124 {
    C80233124() { __ct__9C80233124Fv(this); }
    ~C80233124();
};

struct C8013ECE4 {
    u8 b[8];
    C8013ECE4();
    ~C8013ECE4();
};

struct C802BCCA8 {
    void *vt;
    C802BCCA8() { vt = lbl_802BCCA8; }
};

struct C8005F938 {
    u8 pad[888];
    C8005F938();
    ~C8005F938();
};

struct C8005F938_A : C80233124 {
    C802BCCA8 vt;
    u8 b4[0x320];
    C8013ECE4 m324[3];
    u8 b33C[0x3c];
    C8005F938_A() {
        u8 *p = (u8 *)this;
        *(f32 *)(p + 840) = lbl_8035E4A8;
        *(f32 *)(p + 728) = lbl_8035E4A8;
        *(f32 *)(p + 732) = lbl_8035E4A8;
        *(f32 *)(p + 736) = lbl_8035E4A8;
        *(s32 *)(p + 752) = 0;
        *(s32 *)(p + 756) = 0;
        *(s32 *)(p + 760) = 0;
        *(s32 *)(p + 764) = 0;
        *(s32 *)(p + 768) = 0;
        *(s32 *)(p + 772) = 0;
        *(s32 *)(p + 776) = 0;
        *(s32 *)(p + 780) = 0;
        *(s32 *)(p + 740) = 0;
        *(s32 *)(p + 744) = 0;
        *(s32 *)(p + 720) = 0;
        *(s32 *)(p + 724) = 0;
        *(s32 *)(p + 608) = 1;
        *(s32 *)(p + 748) = 0;
        *(s32 *)(p + 868) = 0;
        *(s32 *)(p + 876) = 0;
        *(f32 *)(p + 872) = lbl_8035E4CC;
        *(u8 *)(p + 884) = 0;
        *(s32 *)(p + 828) = 0;
        *(s32 *)(p + 832) = 0;
        *(s32 *)(p + 836) = 0;
    }
};

extern "C" {

void *fn_8005FA14(s32 n) {
    C8005F938_A *p;
    C8005F938 *a;

    if (n <= 1) {
        if (lbl_8035B320 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035B320);
        p = new C8005F938_A;
        fn_800F7E98();
        if (p == 0) {
            fn_800604C4(-4, 0, 0, 0);
        }
        return p;
    }
    if (lbl_8035B320 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035B320);
    a = new C8005F938[n];
    fn_800F7E98();
    if (a == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    return a;
}

} /* extern "C" */
