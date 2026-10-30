// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern "C" void *memset(void *, int, unsigned long);
struct B { u32 f0; u32 n; u8 pad8[8]; u32 f16; u8 pad20[4]; void *f24; };
struct R;
struct E { u8 pad[12]; virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19(); virtual void e20(); virtual void put(u32, u32, void *); };
struct Y { u8 pad[20]; virtual void yA(); virtual void clear(); virtual void y0(); virtual void y1(); virtual void y2(); virtual void y3(); virtual void y4(); virtual void y5(); virtual void y6(); virtual void y7(); virtual void y8(); virtual void y9(); virtual void init(R *, B *, int); virtual E *get(u32); };
struct X { u8 pad[16]; virtual void x0(); virtual void x1(); virtual void x2(); virtual void x3(); virtual void x4(); virtual void x5(); virtual void x6(); virtual void x7(); virtual void x8(); virtual Y *mk(int); };
struct F { virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7(); virtual void f8(); virtual void f9(); virtual void f10(); virtual X *mkx(); virtual void rel(X *); };
struct K { u8 pad[116]; virtual void k0(); virtual void k1(); virtual void k2(); virtual void k3(); virtual void k4(); virtual void k5(); virtual void k6(); virtual void k7(); virtual void k8(); virtual void k9(); virtual void k10(); virtual void k11(); virtual u32 sz(); };
struct R { u8 pad[48]; virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3(); virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7(); virtual void r8(); virtual void r9(); virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15(); virtual F *fac(); K *f52; };
struct S { R *f0; u32 f4; u32 f8; u32 f12; u32 f16; u8 f20[28]; u32 f48; };
struct T { R *f0; X *f4; Y *f8; u32 f12; u8 f16[112]; u32 w[14]; };
void fn_80133A18(X *, R *, int, int);
void fn_8013F908(T *t, S *s) {
    if (t->f8) {
        if (t->f4) {
            t->f8->clear();
            t->f0->fac()->rel(t->f4);
        }
        t->f0 = 0;
        t->f4 = 0;
        t->f8 = 0;
        t->f12 = 0;
        memset(t->f16, 0, 112);
        for (int j = 0; j < 14; j++) t->w[j] = 0;
    }
    t->f0 = s->f0;
    t->f4 = t->f0->fac()->mkx();
    fn_80133A18(t->f4, t->f0, 1, 0);
    t->f8 = t->f4->mk(0);
    t->f12 = s->f48;
    B b;
    memset(&b, 0, sizeof(B));
    b.f24 = t->f4;
    b.f0 = s->f4;
    b.f16 = s->f12;
    u32 k = t->f0->f52->sz();
    b.n = s->f8 / k;
    u32 rem = s->f8 % k;
    b.n++;
    t->f8->init(t->f0, &b, 0);
    u32 i;
    for (i = 0; i < b.n - 1; i++) t->f8->get(i)->put(k, s->f16, s->f20);
    t->f8->get(i)->put(rem, s->f16, s->f20);
}

} /* extern "C" */
