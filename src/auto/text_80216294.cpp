// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct A80216294 {
    virtual void *v0(void *e);
    virtual void v1(void *x);
};
struct M80216294 {
    u8 pad[16];
    virtual void v0();
    virtual void v1();
};
struct S80216294 {
    void *f0;
    A80216294 *f4;
    u8 pad8[92 - 8];
    u32 f92;
    u32 f96;
    u32 *f100;
};
extern "C" {
void fn_800F9638(void *p);
void fn_80208154(void *p);
void fn_800F9654(void *p, u8 *v);
void fn_800F994C(void *p, void *d);
void fn_800604C4(s32 a, s32 b, s32 c, s32 d);
void fn_800F7EC0(void *p);
void fn_800F7E98(void);
void fn_802081C0(void *p, A80216294 *a, void *c);
extern void *lbl_8035B1C0;
extern void *lbl_8035B1D8;
extern void *lbl_8035B1D0;
extern void *lbl_8035B1F8;
extern void *lbl_8035B208;

void fn_80216294(S80216294 *self, A80216294 *a, u32 b, void *c, void *d, void *e) {
    u32 i;
    if (self->f100 != 0) {
        if (self->f100 != 0) delete[] self->f100;
        if (self->f0 != 0) self->f4->v1(self->f0);
        fn_800F9638((u8 *)self + 32);
        ((M80216294 *)((u8 *)self + 56))->v1();
        fn_80208154((u8 *)self + 8);
        lbl_8035B1C0 = 0;
        lbl_8035B1D8 = 0;
        lbl_8035B1D0 = 0;
        self->f0 = 0;
        self->f4 = 0;
        self->f92 = 0;
        self->f96 = 0;
        self->f100 = 0;
    }
    self->f4 = a;
    self->f96 = b;
    {
        u8 tmp = 0;
        fn_800F9654((u8 *)self + 32, &tmp);
    }
    fn_800F994C((u8 *)self + 56, d);
    if (lbl_8035B208 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B208);
    self->f100 = new u32[self->f96];
    fn_800F7E98();
    if (self->f100 == 0) fn_800604C4(-4, 0, 0, 0);
    for (i = 0; i < self->f96; i++) self->f100[i] = 0;
    if (e != 0) self->f0 = a->v0(e);
    fn_802081C0((u8 *)self + 8, a, c);
    lbl_8035B1C0 = self;
    lbl_8035B1F8 = self;
    lbl_8035B1D8 = self;
    lbl_8035B1D0 = self;
}

} /* extern "C" */
