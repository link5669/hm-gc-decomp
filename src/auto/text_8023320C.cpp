// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern "C" {
extern void *lbl_8035B320;
extern u8 lbl_802F16C0[];
extern volatile f32 lbl_80365DF8;
extern volatile f32 lbl_80365E48;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
} /* extern "C" */

struct C80239B40 {
    C80239B40();
};

struct C80233124 : C80239B40 {
    u8 pad[720];
    C80233124();
    ~C80233124();
};

struct C80233124i : C80239B40 {
    u8 pad[720];
    C80233124i() {
        u8 *p = (u8 *)this;
        *(void **)(p + 0) = lbl_802F16C0;
        *(s32 *)(p + 620) = 0;
        *(s32 *)(p + 612) = 0;
        *(f32 *)(p + 616) = lbl_80365DF8;
        *(f32 *)(p + 600) = lbl_80365DF8;
        *(s32 *)(p + 604) = 0;
        *(s32 *)(p + 608) = 0;
        *(s32 *)(p + 628) = 0;
        *(s32 *)(p + 660) = 0;
        *(s32 *)(p + 664) = 0;
        *(s32 *)(p + 668) = 0;
        *(s32 *)(p + 672) = 0;
        *(s32 *)(p + 676) = 0;
        *(f32 *)(p + 632) = lbl_80365DF8;
        *(f32 *)(p + 636) = lbl_80365DF8;
        *(f32 *)(p + 640) = lbl_80365DF8;
        *(f32 *)(p + 644) = lbl_80365DF8;
        *(f32 *)(p + 648) = lbl_80365DF8;
        *(f32 *)(p + 652) = lbl_80365DF8;
        *(s32 *)(p + 656) = 0;
        *(f32 *)(p + 68) = lbl_80365E48;
        *(f32 *)(p + 72) = lbl_80365E48;
        *(f32 *)(p + 76) = lbl_80365E48;
        *(s32 *)(p + 680) = 0;
        *(s32 *)(p + 684) = 0;
        *(s32 *)(p + 704) = 0;
        *(s32 *)(p + 708) = 0;
        *(s32 *)(p + 688) = 0;
        *(s32 *)(p + 624) = 0;
        *(s32 *)(p + 712) = 0;
        *(s32 *)(p + 696) = 0;
        *(s32 *)(p + 692) = 0;
    }
};

extern "C" void *fn_8023320C(s32 n) {
    C80233124 *r;
    if (n <= 1) {
        if (lbl_8035B320 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035B320);
        r = (C80233124 *)new C80233124i;
        fn_800F7E98();
        if (r == 0) {
            fn_800604C4(-4, 0, 0, 0);
        }
        return r;
    } else {
        if (lbl_8035B320 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035B320);
        r = new C80233124[n];
        fn_800F7E98();
        if (r == 0) {
            fn_800604C4(-4, 0, 0, 0);
        }
    }
    return r;
}

} /* extern "C" */
