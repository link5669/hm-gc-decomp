// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_802F0FDC[];
extern void *lbl_8035B320;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void __ct__9C80233124Fv(void *);
} /* extern "C" */

struct C80227BE4 {
    u8 pad[724];
    C80227BE4();
    ~C80227BE4();
};

struct C80227C20 {
    u8 *vt;
    u8 pad[720];
    C80227C20() {
        __ct__9C80233124Fv(this);
        vt = lbl_802F0FDC;
    }
};

extern "C" {

void *fn_80227C20(s32 n) {
    C80227C20 *p;
    C80227BE4 *a;

    if (n <= 1) {
        if (lbl_8035B320 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035B320);
        p = new C80227C20;
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
    a = new C80227BE4[n];
    fn_800F7E98();
    if (a == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    return a;
}

} /* extern "C" */
