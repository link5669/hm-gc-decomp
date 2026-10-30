// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern void *lbl_8035ABE0;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
extern u32 lbl_803645E0;
struct Img { u8 pad[28]; u16 f28; u16 f30; };
struct S60;
struct T;
struct Z { u8 pad[20]; virtual void z0(); virtual void z1(); virtual void setup(int, int, int, int); virtual void z3(); virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7(); virtual void z8(); virtual void z9(); virtual void z10(); virtual void z11(); virtual void attach(void *, S60 *, T *); virtual void z13(); virtual Img *get(int); };
struct S60 { u8 pad[16]; virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual Z *mk(int); u8 pad20[44]; };
struct S124 { u8 pad[32]; virtual void b0(); virtual void go(); };
struct C8012E79C { C8012E79C(); u32 f0, f4, f8, f12, f16, f20; };
struct X { u8 pad[44]; u32 f44; };
struct T { u8 pad[8]; u32 f8; u32 f12; u16 f16; u16 f18; u8 pad20[6]; u16 f26; u8 pad28[16]; C8012E79C *f44; u8 pad48[12]; S60 s60; S124 s124; };
void fn_80138050(S60 *, X *, int, int, int, int, int, int);
void fn_8012EAF4(T *, X *, S124 *, int);
void fn_8012E9F0(T *, X *, S124 *);
static inline void initA(T *t, X *x) {
    fn_80138050(&t->s60, x, 1, 0, 1, 0, 0, 0);
    Z *z = t->s60.mk(0);
    z->setup(7168, 0, 1, 0);
    z->attach(x, &t->s60, t);
    t->f16 = z->get(0)->f28;
    t->f18 = z->get(0)->f30;
    t->f26 = 1;
    if (lbl_8035ABE0 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035ABE0);
    t->f44 = new C8012E79C[t->f26];
    fn_800F7E98();
    if (t->f44 == 0) fn_800604C4(-4, 0, 0, 0);
    t->f44[0].f0 = t->f16;
    t->f44[0].f4 = t->f18;
    C8012E79C *c = t->f44;
    Img *im = z->get(0);
    c->f8 = c->f12 = 0;
    c->f16 = im->f28;
    c->f20 = im->f30;
    t->f8 |= lbl_803645E0;
}
void fn_8015BBC0(T *t, X *x) {
    if (t->f8 & 0x10) return;
    if ((t->f12 & 0x1C00) == 0x1C00) {
        initA(t, x);
    } else {
        fn_8012EAF4(t, x, &t->s124, 0);
        fn_8012E9F0(t, x, &t->s124);
        if (!(x->f44 & 4)) t->s124.go();
        t->f8 |= lbl_803645E0;
    }
}

} /* extern "C" */
