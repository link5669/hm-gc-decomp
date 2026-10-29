// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_802C57F0[];
extern void *lbl_8035B320;
extern volatile f32 lbl_8035FEB8;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
} /* extern "C" */

struct C8005F938 {
    C8005F938();
    ~C8005F938();
};

struct C800899FC {
    u8 pad[1108];
    C800899FC();
    ~C800899FC();
};

struct C80089AA4 : C8005F938 {
    u8 *vt;
    u8 pad0[604];
    s32 f608;
    u8 pad1[276];
    s32 f888;
    u8 pad2[4];
    s32 f896;
    f32 f900;
    u8 pad3[4];
    s32 f908;
    f32 f912;
    f32 f916;
    f32 f920;
    u8 pad4[24];
    s32 f948;
    u8 pad5[48];
    s32 a[6];
    s32 b[6];
    u8 pad6[60];
    C80089AA4() {
        vt = lbl_802C57F0;
        f896 = 0;
        f900 = lbl_8035FEB8;
        f908 = 0;
        f888 = 0;
        f912 = lbl_8035FEB8;
        f916 = lbl_8035FEB8;
        f920 = lbl_8035FEB8;
        for (int i = 0; i < 6; i++) {
            a[i] = 0;
            b[i] = 0;
        }
        f608 = 32;
        f948 = 0;
    }
};

extern "C" {

void *fn_80089AA4(s32 n) {
    void *p;

    if (n <= 1) {
        if (lbl_8035B320 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035B320);
        p = new C80089AA4;
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
    p = new C800899FC[n];
    fn_800F7E98();
    if (p == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    return p;
}

} /* extern "C" */
