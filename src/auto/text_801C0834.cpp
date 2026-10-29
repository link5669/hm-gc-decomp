// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u32 lbl_8035AFCC;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(u32);
void fn_800F7E98(void);
} /* extern "C" */
struct E_801C0834 { u32 f0; u8 pad[24]; };
struct L_801C0834 { u32 f0; E_801C0834 *f4; u32 f8; };
struct S_801C0834 {
    u32 f0, f4, f8, f12, f16;
    u8 pad20[32];
    u32 f52;
    f32 f56, f60, f64, f68, f72, f76, f80, f84, f88, f92, f96, f100;
    u32 *f104;
    u32 f108;
    L_801C0834 *f112;
    u32 f116, f120, f124;
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(L_801C0834 *);
};
extern "C" {
void fn_801C0834(S_801C0834 *self, S_801C0834 *o) {
    u32 n;
    u32 i;
    self->f0 = o->f0;
    if (o->f108 & 2) self->f108 |= 2; else self->f108 &= ~2;
    self->f4 = o->f4;
    self->f8 = o->f8;
    self->f12 = o->f12;
    self->f16 = o->f16;
    self->f52 = o->f52;
    self->f56 = o->f56;
    self->f60 = o->f60;
    self->f64 = o->f64;
    self->f68 = o->f68;
    self->f72 = o->f72;
    self->f76 = o->f76;
    self->f80 = o->f80;
    self->f84 = o->f84;
    self->f88 = o->f88;
    self->f92 = o->f92;
    self->f96 = o->f96;
    self->f100 = o->f100;
    self->v12(o->f112);
    if (self->f112 != 0) {
        n = self->f112->f8;
        if (lbl_8035AFCC == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035AFCC);
        self->f104 = new u32[n];
        fn_800F7E98();
        if (self->f104 == 0) fn_800604C4(-4, 0, 0, 0);
        for (i = 0; i < n; i++) {
            self->f104[i] = o->f104 ? o->f104[i] : o->f112->f4[i].f0;
        }
    }
    self->f108 = o->f108;
    self->f116 = o->f116;
    self->f120 = o->f120;
    self->f124 = o->f124;
}

} /* extern "C" */
