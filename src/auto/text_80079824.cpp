// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u8 lbl_802C2510[];
extern void *lbl_8035B320;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void __ct__9C8005D3E0Fv(void *);

struct C800799E0 {
    u8 pad[860];
    C800799E0();
    ~C800799E0();
};

struct C80079824 {
    u8 *vt;
    u8 pad[832];
    u32 f344;
    u32 f348;
    u32 f34c;
    u8 pad2[12];
    C80079824() {
        __ct__9C8005D3E0Fv(this);
        vt = lbl_802C2510;
        f344 = 0;
        f348 = 0;
        f34c = 0;
    }
};

void *fn_80079824(s32 n) {
    C80079824 *p;
    C800799E0 *a;

    if (n <= 1) {
        if (lbl_8035B320 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035B320);
        p = new C80079824;
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
    a = new C800799E0[n];
    fn_800F7E98();
    if (a == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    return a;
}

} /* extern "C" */
