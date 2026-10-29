// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct B32 { u8 d[32]; };
struct SelfB {
    void *f0;
    virtual void v0(); virtual void v1(); virtual void v2();
    u8 pad8[4];
    B32 *f12;
    u8 pad16[4];
    u32 f20;
};
extern "C" {
void fn_800C49A8(s32);
void fn_800C6EC8(void);
void fn_800C9FC8(void);
s32 fn_800B91B8(void);
void fn_800B9238(s32);
void fn_800C8080(s32);
void fn_800CA090(s32);
void fn_800BB284(void);
void fn_800BBD48(f32);
void fn_800BBD40(f32);
void fn_801FE7C0(void);
void fn_800C885C(void (*)(void));
void *memset(void *, int, unsigned long);
void *fn_802077F8(u32);
void fn_80207510(void *, void *, u32);
void fn_801FB674(SelfB *, void *);
extern f32 lbl_803656C8;

void fn_801FE54C(SelfB *self, void *arg) {
    B32 buf __attribute__((aligned(32)));
    B32 *p;
    u32 i;
    s32 r;
    if (self->f0) self->v2();
    fn_800C49A8(0);
    fn_800C6EC8();
    fn_800C9FC8();
    r = fn_800B91B8();
    self->f20 = (r != 1);
    switch (r != 1) {
    case 0:
        fn_800B9238(1);
        fn_800C8080(0);
        fn_800CA090(1);
        break;
    case 1:
        fn_800B9238(0);
        fn_800C8080(0);
        fn_800CA090(0);
        break;
    case 2:
        fn_800B9238(1);
        fn_800C8080(1);
        fn_800CA090(2);
        break;
    case 3:
        fn_800B9238(1);
        fn_800C8080(2);
        fn_800CA090(3);
        break;
    }
    fn_800BB284();
    fn_800BBD48(lbl_803656C8);
    fn_800BBD40(lbl_803656C8);
    fn_800C885C(fn_801FE7C0);
    memset(&buf, 0, 32);
    self->f12 = (B32 *)fn_802077F8(256);
    for (i = 0, p = self->f12; i < 8; i++, p++) {
        fn_80207510(p, &buf, 32);
    }
    fn_801FB674(self, arg);
}

} /* extern "C" */
