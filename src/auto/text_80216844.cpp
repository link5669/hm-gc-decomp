// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u32 lbl_803658B0;
struct C4 { u8 r, g, b, a; };
struct S8 { u32 w[2]; };
struct Cfg { void *f0; S8 f4; S8 f12; u32 f20; u32 f24; f32 f28; u32 f32; u32 f36; u32 f40; u32 f44; S8 f48; u32 f56; u32 f60; u32 f64; u32 f68; u32 f72; };
struct G0;
struct Q28 { void *f0; };
struct G88 { u8 pad[28]; Q28 *f28; };
struct G92 { u8 pad[16]; virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void setup(void *, int, int, int, int); virtual void x7(); virtual G88 *mk(int); };
struct G0 { u8 pad[16]; virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void *mk(int); };
struct F0 { virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual G0 *make(); virtual void x6(); virtual void x7(); virtual void x8(); virtual G92 *make2(); };
struct D4 { u8 pad[48]; virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual F0 *fac(); };
struct B { D4 *f0; G92 *f4; u8 pad8[12]; C4 c20; int f24; u8 pad28[56]; int f84; void **f88; };
struct T { G0 *f0; D4 *d4; S8 f8; S8 f16; u32 f24c; void *f28; f32 f32; u32 f36; u32 f40; u32 f44; u32 f48; S8 f52; u32 f60; u32 f64; u32 f68; u32 f72; u32 f76; u32 f80; u8 pad84[4]; G88 *f88; G92 *f92; };
void fn_8012FD28(B *);
void fn_80138050(G0 *, D4 *, int, int, int, int, int, int);
void fn_80130B4C(G88 *, B *);
void fn_80216844(T *t, Cfg *c) {
    B b;
    fn_8012FD28(&b);
    t->d4 = (D4 *)c->f0;
    t->f8 = c->f4;
    t->f16 = c->f12;
    t->f24c = c->f20;
    t->f28 = (void *)c->f24;
    t->f32 = c->f28;
    t->f36 = c->f32;
    t->f40 = c->f36;
    t->f44 = c->f40;
    t->f48 = c->f44;
    t->f52 = c->f48;
    t->f60 = c->f56;
    t->f64 = c->f60;
    t->f68 = c->f64;
    t->f72 = c->f68;
    t->f76 = c->f72;
    if ((t->f76 & 2) && !t->f24c) {
        t->f0 = t->d4->fac()->make();
        fn_80138050(t->f0, t->d4, 1, 0, 1, 0, 0, 0);
        t->f24c = (u32)t->f0->mk(0);
        t->f92 = t->d4->fac()->make2();
        t->f92->setup(t->d4, 0, 1, 1, 0);
        t->f88 = t->f92->mk(0);
        b.f24 = 2;
        b.f4 = t->f92;
        b.c20.r = 255; b.c20.g = 0; b.c20.b = 0; b.c20.a = 255;
        b.f0 = t->d4;
        b.f84 = 1;
        b.f88 = (void **)&t->f24c;
        fn_80130B4C(t->f88, &b);
        t->f88->f28->f0 = (void *)t->f24c;
    }
    t->f80 |= lbl_803658B0;
}

} /* extern "C" */
