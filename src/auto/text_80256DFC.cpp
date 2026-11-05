// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern void *lbl_8035B738;
extern void *lbl_802F2554[];
extern f32 lbl_803666B0;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
} /* extern "C" */
struct C800604C4 {
    ~C800604C4();
};
struct C80261CB0 : C800604C4 {
    C80261CB0();
    u8 pad0[80];
};
struct C80257738 : C80261CB0 {
    f32 f50[3];
    f32 f5c[3];
    f32 f68[3];
    u8 pad74[64];
    u32 fb4;
    u32 fb8;
    u32 fbc;
    C80257738() {
        *(void **)this = lbl_802F2554;
        fb4 = 0;
        fbc = 0;
        fb8 = 0;
        f50[0] = lbl_803666B0;
        f50[1] = lbl_803666B0;
        f50[2] = lbl_803666B0;
        f68[0] = lbl_803666B0;
        f68[1] = lbl_803666B0;
        f68[2] = lbl_803666B0;
        f5c[0] = lbl_803666B0;
        f5c[1] = lbl_803666B0;
        f5c[2] = lbl_803666B0;
    }
};
extern "C" {

C80257738 *fn_80256DFC(s32 n)
{
    C80257738 *p;
    if (n <= 1) {
        if (lbl_8035B738 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035B738);
        p = new C80257738;
        fn_800F7E98();
        if (p == 0) {
            fn_800604C4(-4, 0, 0, 0);
        }
        return p;
    }
    if (lbl_8035B738 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035B738);
    p = new C80257738[n];
    fn_800F7E98();
    if (p == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    return p;
}

} /* extern "C" */
