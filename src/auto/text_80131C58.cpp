// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern char lbl_8029E818[];
void fn_80060568(const char *, int, int, int);
struct E { u32 f0, f4, f8; u8 pad12[2]; u8 f14; u8 pad15; };
void fn_8021F4A4(E *);
struct Y { u8 pad[4]; u32 f4; u8 pad8[4]; virtual u32 map(u32); };
struct A12 { u8 pad[12]; virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void go(); };
struct A8 { u8 pad[8]; virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void go(); };
struct S24 { u8 pad[16]; virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual Y *get(u32); };
struct T { u32 n0; u32 n1; u8 pad8[4]; u32 n2; E *f16; virtual void t0(); virtual void t1(); virtual A12 *g4(u32); virtual A8 *g5(u32); virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual Y *g13(u32); S24 *f24; };
void fn_80131C58(T *t) {
    u32 j;
    u32 i;
    for (i = 0; i < t->n0; i++) if (t->g4(i)) t->g4(i)->go();
    for (i = 0; i < t->n1; i++) if (t->g5(i)) t->g5(i)->go();
    for (j = 0; j < t->n2; j++) {
        i = t->f16[j].f14;
        Y *y;
        if (t->n0) {
            if (i >= t->n0) fn_80060568(lbl_8029E818, 0, 0, 0);
            y = t->g13(i);
        } else {
            y = t->f24->get(i);
        }
        if (y->f4 & 0x20) {
            t->f16[j].f0 = y->map(t->f16[j].f0);
            t->f16[j].f4 = y->map(t->f16[j].f4);
            t->f16[j].f8 = y->map(t->f16[j].f8);
            fn_8021F4A4(&t->f16[j]);
        }
    }
}

} /* extern "C" */
