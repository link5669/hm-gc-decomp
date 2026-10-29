// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern void *lbl_8035B530;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void *memset(void *, s32, u32);
void fn_800F8E38(void *, u32);
void fn_800F87F0(void *, u32, void *);
} /* extern "C" */
struct E80249AC4 { u32 key; u8 data[8]; };
struct B80249AC4 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual s32 v5();
};
struct C80249AC4 : B80249AC4 {
    u8 pad4[16];
    u8 f20[20];
    E80249AC4 *f40;
    u32 f44;
    u8 pad48[44];
    s32 f92;
    u8 pad96[16];
    u32 *f112;
    u32 *f116;
};
extern "C" {
s32 fn_80249AC4(C80249AC4 *self) {
    u32 i;
    if (self->v5()) self->v3();
    fn_800F8E38(self->f20, self->f44 * 10 / 7);
    for (i = 0; i < self->f44; i++) {
        fn_800F87F0(self->f20, self->f40[i].key, self->f40[i].data);
    }
    if (self->f92 != 0) {
        if (lbl_8035B530 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B530);
        self->f112 = new u32[self->f92];
        fn_800F7E98();
        if (self->f112 == 0) fn_800604C4(-4, 0, 0, 0);
        memset(self->f112, 0, self->f92 * 4);
        if (lbl_8035B530 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B530);
        self->f116 = new u32[self->f92];
        fn_800F7E98();
        if (self->f116 == 0) fn_800604C4(-4, 0, 0, 0);
        memset(self->f116, 0, self->f92 * 4);
    }
    return 0;
}

} /* extern "C" */
