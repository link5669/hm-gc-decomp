// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct E { u16 f0; u16 f2; virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4();
    virtual void set(void *p, s32 m, u32 n); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual u8 idx(void *p); };
struct C { u16 f0; u8 pad[18]; u8 col[4]; u16 pad24; u16 f26; u8 pad28[4];
    virtual void c0(); virtual void c1(); virtual E *get(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void act(); };
struct BS { u32 f0; u32 f4; u8 pad[12]; u32 f20; };
struct B { u8 pad[52]; BS *s; };
struct D { u32 f0; u8 pad[8]; u8 col[4]; u8 pad2[1432 - 16]; u8 *tbl; };
struct A { u8 pad[56]; u32 n; u8 f60[1076 - 60]; u8 f1076[4]; u8 f1080[4]; u8 tbl[254]; u8 i0; u8 i1; };
extern "C" {
extern u32 lbl_803643A8, lbl_803643AC, lbl_803643B0;
D *fn_801348F0(BS *s);

static inline void fill(A *a) { int i; for (i = 0; i < 254u; i++) a->tbl[i] = i + 1; }
void fn_80148330(A *a, B *b, C *c, s32 on) {
    E *e;
    s32 fl;
    D *d;
    fl = b->s->f4 & 0x200;
    d = fn_801348F0(b->s);
    if (on) d->f0 |= lbl_803643A8; else d->f0 &= ~0x40;
    if (c->f0 & 4) {
        e = c->get();
        if (e->f2 & 2) {
            if (a->n > 254) {
                e->set(a->f60, 1, 254);
                fill(a);
                a->i0 = e->idx(a->f1076);
                a->i1 = e->idx(a->f1080);
            } else {
                e->set(a->f60, 1, a->n);
            }
        } else {
            e->set(a->f60, 0, a->n);
        }
        if (fl && c->f26 & 2 && (b->s->f20 & 0x10200) == 0x10200) c->act();
        if (c->get()->f2 & 2) {
            d->f0 |= lbl_803643AC;
            d->tbl = a->tbl;
        }
    } else if (fl && c->f26 & 2) {
        d->f0 |= lbl_803643B0;
        d->col[0] = c->col[0]; d->col[1] = c->col[1]; d->col[2] = c->col[2]; d->col[3] = c->col[3];
    }
}

} /* extern "C" */
