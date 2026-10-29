// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_802C5740[];
extern void *lbl_8035B320;
extern f32 lbl_8035FE7C;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
} /* extern "C" */

struct C8005F938 {
    C8005F938();
    ~C8005F938();
};

struct C8008790C {
    u8 pad[916];
    C8008790C();
    ~C8008790C();
};

struct C80087984 : C8005F938 {
    u8 *vt;
    u8 pad[604];
    s32 f260;
    u8 pad2[276];
    s32 f378;
    f32 f37c[4];
    s32 f38c;
    s32 f390;
    C80087984() {
        vt = lbl_802C5740;
        f378 = 0;
        for (int i = 0; i < 4; i++) f37c[i] = lbl_8035FE7C;
        f260 = 16;
        f38c = 255;
        f390 = 0;
    }
};

extern "C" {

void *fn_80087984(s32 n) {
    void *p;

    if (n <= 1) {
        if (lbl_8035B320 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035B320);
        p = new C80087984;
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
    p = new C8008790C[n];
    fn_800F7E98();
    if (p == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    return p;
}

} /* extern "C" */
