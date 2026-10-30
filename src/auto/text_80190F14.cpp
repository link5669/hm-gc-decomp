// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern "C" void *memset(void *, int, unsigned long);
extern f32 lbl_80364B3C;
extern f32 lbl_803596E0[];
struct D48 { u8 pad[16]; void *f16; void *f20; u8 pad24[12]; virtual void d0(); virtual void d1(); virtual ~D48(); };
struct R { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void use(void *); };
struct Q { u8 pad[48]; virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual R *get(); };
struct H44 { u8 pad[4]; Q *f4; };
struct X0 { u8 pad[4]; };
struct N { u32 f0; u8 pad4[4]; f32 f8, f12, f16, f20, f24, f28, f32_, f36, f40; H44 *f44; D48 *f48; void *f52; u32 f56; u32 f60; u8 f64[4]; void **f68; u8 pad72[4]; void **f76; N *f80; N *f84; N *f88; int f92; int f96; };
void fn_8019B380(void *, N *);
void fn_8019B048(void *, N *);
static inline void rm(N *p, N *n) {
    N *c = p->f88;
    N **pp = &p->f88;
    for (; c; c = c->f84) {
        if (c == n) {
            *pp = c->f84;
            c->f84 = 0;
            c->f80 = 0;
            return;
        }
        pp = &c->f84;
    }
}
void fn_80190F14(N *n) {
    if (n->f68) fn_8019B380(*n->f68, n);
    if (n->f76) fn_8019B048(*n->f76, n);
    if (n->f80) rm(n->f80, n);
    N *c = n->f88;
    while (c) {
        N *nx = c->f84;
        rm(n, c);
        c = nx;
    }
    if (n->f48 && (n->f0 & 8)) {
        R *r = n->f44->f4->get();
        r->use(n->f48->f16);
        r->use(n->f48->f20);
        delete n->f48;
        n->f0 &= ~8;
    }
    n->f48 = 0;
    if (n->f52 && (n->f0 & 0x10)) delete (u8 *)n->f52;
    n->f0 = 0;
    n->f8 = lbl_80364B3C;
    n->f12 = lbl_80364B3C;
    n->f16 = lbl_80364B3C;
    n->f20 = lbl_803596E0[0];
    n->f24 = lbl_80364B3C;
    n->f28 = lbl_80364B3C;
    n->f32_ = lbl_80364B3C;
    n->f36 = lbl_803596E0[0];
    n->f40 = lbl_803596E0[0];
    n->f44 = 0;
    n->f48 = 0;
    n->f52 = 0;
    n->f56 = 0;
    n->f60 = 0;
    memset(n->f64, 0, 16);
    n->f80 = 0;
    n->f84 = 0;
    n->f88 = 0;
    n->f92 = -1;
    n->f96 = -1;
}

} /* extern "C" */
