// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct SB {
    u32 f0;
    u16 f4;
    u16 f6;
    virtual void v0(); virtual void v1(); virtual void v2();
};
struct S : SB {
    u8 pad[12];
    void *f24;
};
extern "C" {
typedef struct H {
    u8 pad[24];
    u32 f24;
    u32 f28;
} H;
extern H *lbl_8035ACF0;
void fn_800604C4(s32 a, s32 b, s32 c, s32 d);
void fn_800F7EC0(void *heap);
void fn_800F7E98(void);

void fn_8015C498(S *self, u32 n, u16 flags) {
    if (self->f0 != 0) self->v2();
    self->f0 = n;
    self->f4 = flags;
    self->f6 = 1;
    if (lbl_8035ACF0->f24 >= 5) lbl_8035ACF0->f28 = lbl_8035ACF0->f24;
    else lbl_8035ACF0->f28 = 5;
    if (self->f4 & 0x10) {
        if (lbl_8035ACF0 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035ACF0);
        self->f24 = new u8[self->f0];
        fn_800F7E98();
        if (self->f24 == 0) fn_800604C4(-4, 0, 0, 0);
    } else if (self->f4 & 0x20) {
        if (lbl_8035ACF0 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035ACF0);
        self->f24 = new u32[self->f0];
        fn_800F7E98();
        if (self->f24 == 0) fn_800604C4(-4, 0, 0, 0);
    } else {
        if (lbl_8035ACF0 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035ACF0);
        self->f24 = new u16[self->f0];
        fn_800F7E98();
        if (self->f24 == 0) fn_800604C4(-4, 0, 0, 0);
    }
    lbl_8035ACF0->f28 = lbl_8035ACF0->f24;
}

} /* extern "C" */
