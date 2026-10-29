// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern void *lbl_8035B738;
extern u8 lbl_802F2C2C[];
extern f32 lbl_80366B20;
extern f32 lbl_80366B18;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);

} /* extern "C" */
struct C80261CB0 {
    C80261CB0();
};
struct N_802636DC : C80261CB0 {
    u8 *vt;
    u8 pad[172];
    s32 f176, f180, f184, f188, f192, f196, f200;
    f32 f204, f208, f212, f216;
    s32 f220;
    f32 f224, f228, f232, f236;
    s32 f240, f244, f248;
    u8 pad252[4];
    s32 f256;
    N_802636DC() {
        vt = lbl_802F2C2C;
        f176 = 2; f180 = 0; f184 = 2; f188 = 0; f192 = 1; f196 = 1; f200 = 0;
        f204 = lbl_80366B20; f208 = lbl_80366B18; f236 = lbl_80366B18;
        f220 = 0; f224 = lbl_80366B18; f228 = lbl_80366B18; f212 = lbl_80366B18; f216 = lbl_80366B20;
        f240 = -1; f244 = 0; f248 = 0; f232 = lbl_80366B18; f256 = 0;
    }
};
struct C80264998 {
    u8 d[260];
    C80264998();
    ~C80264998();
};
extern "C" {

void *fn_802636DC(s32 n) {
    if (n <= 1) {
        N_802636DC *p;
        if (!lbl_8035B738) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B738);
        p = new N_802636DC;
        fn_800F7E98();
        if (!p) fn_800604C4(-4, 0, 0, 0);
        return p;
    } else {
        C80264998 *p;
        if (!lbl_8035B738) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B738);
        p = new C80264998[n];
        fn_800F7E98();
        if (!p) fn_800604C4(-4, 0, 0, 0);
        return p;
    }
}

} /* extern "C" */
