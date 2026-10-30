// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u32 lbl_80364350;
struct B136;
struct Y48 { u8 pad[48]; virtual void a0(); virtual void a1(); virtual void a2(); virtual void set(void *, int, B136 *, u32, u32, u32); };
struct Y { u8 pad[42]; u16 n42; u8 b44[64]; };
struct B136 { u8 pad[8]; u32 f8; virtual void b0(); virtual void bX(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void bind(void *, int); };
struct S8 { u8 pad[20]; virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15(); virtual Y *get(u32); };
struct T { void *f0; u8 pad4[4]; S8 *f8; int f12; u8 f16[112]; u32 f128; u8 pad132[4]; B136 *f136; u32 f140; u32 f144; u32 f148; u32 f152; u32 f156[4]; u32 f172; u32 f176; u32 f180; };
int fn_8013F5E0(T *, u32, u32, u32 *);
void *fn_8013F394(T *t, u32 *cnt) {
    u32 need;
    if (*cnt == 0) {
        need = t->f136->f8 - t->f140;
        if (need < 1) need = t->f136->f8;
        if (t->f12 == 1) *cnt = need - 2;
        else *cnt = need / 3;
    } else {
        if (t->f12 == 1) need = *cnt + 2;
        else need = *cnt + *cnt + *cnt;
    }
    if (t->f140 + need > t->f136->f8) {
        if (need > t->f136->f8) return 0;
        t->f128 &= ~1;
        if (!t->f176) {
            t->f144--;
        } else {
            Y *y = t->f8->get(t->f144 - 1);
            if (t->f12 == 1) ((Y48 *)y)->set(t->f0, 8, t->f136, t->f148, t->f172, t->f176);
            else ((Y48 *)y)->set(t->f0, 4, t->f136, t->f148, t->f172, t->f176);
            u32 i;
            T *q = t;
            for (i = 0; i < t->f152; i++) { y->b44[y->n42++] = q->f156[0]; q = (T *)((u8 *)q + 4); }
        }
        t->f140 = t->f136->f8;
        if (!fn_8013F5E0(t, t->f148, t->f152, t->f156)) return 0;
        if (need > t->f136->f8) return 0;
    }
    if (!(t->f128 & 4)) {
        t->f136->bind(t->f16, 8);
        t->f128 |= lbl_80364350;
    }
    t->f180 = *cnt;
    return t->f16;
}

} /* extern "C" */
