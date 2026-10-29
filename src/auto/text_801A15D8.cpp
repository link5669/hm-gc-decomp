// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct X801A15D8 { u8 pad[16]; virtual void m0(s32); virtual void m1(); };
struct C801A15D8 { X801A15D8 *x; u32 f4; u32 f8; };
struct Y801A15D8 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void set(u32); };
struct G801A15D8 { u8 pad[48]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual Y801A15D8 *get(); };
struct H801A15D8 { u32 f0; G801A15D8 *g; };
struct Z801A15D8 { u8 pad[16]; u32 f16; u32 f20; u8 pad24[12]; virtual void v0(); virtual void v1(); virtual void del(s32); };
struct L801A15D8 { u32 f0; };
struct E801A15D8 { u8 pad[28]; };
struct S801A15D8 { u32 flags; u8 pad4[40]; H801A15D8 *h; u8 pad48[24]; L801A15D8 *l; u8 pad76[32]; u32 f108; u32 n; E801A15D8 *arr; Z801A15D8 *z; u32 f124; u8 pad128[4]; C801A15D8 *c; u32 f136; u32 f140; };
void fn_8017A5C4(C801A15D8 *);
void __dt__9C8017AB98Fv(C801A15D8 *, s16);
void fn_8019B6B8(u32, S801A15D8 *);
void fn_8018CF20(E801A15D8 *);
void __dla__FPv(void *);
void fn_80190F14(S801A15D8 *);

static inline BOOL active801A15D8(C801A15D8 *c) {
    return c->x != 0 || c->f8 != 0;
}

void fn_801A15D8(S801A15D8 *self) {
    Y801A15D8 *y;
    u32 i;
    if (self->c != 0) {
        if (active801A15D8(self->c) && self->c->x != 0 && (self->flags & 0x8000)) {
            self->c->x->m1();
            if (self->c->x != 0) {
                self->c->x->m0(1);
            }
        }
        fn_8017A5C4(self->c);
        __dt__9C8017AB98Fv(self->c, 1);
    }
    if (self->l != 0) {
        fn_8019B6B8(self->l->f0, self);
    }
    if (self->z != 0 && (self->flags & 0x1000)) {
        y = self->h->g->get();
        y->set(self->z->f16);
        y->set(self->z->f20);
        if (self->z != 0) {
            self->z->del(1);
        }
    }
    if (self->arr != 0) {
        for (i = 0; i < self->n; i++) {
            fn_8018CF20(&self->arr[i]);
        }
        if (self->arr != 0) {
            __dla__FPv((u8 *)self->arr - 16);
        }
    }
    fn_80190F14(self);
    self->f108 = 0;
    self->n = 0;
    self->arr = 0;
    self->z = 0;
    self->f124 = 0;
    self->f136 = 0;
    self->c = 0;
    self->f140 = 0;
}

} /* extern "C" */
