// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct V3 { f32 x, y, z; };
struct L { u8 pad[16]; u32 f16; s32 type; V3 dir; V3 pos; };
struct B { u8 pad[104]; virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void *mtx(); };
struct R { u8 pad[6448]; virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3(); virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7(); virtual void r8(); virtual void r9();
    virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15(); virtual void r16(); virtual void r17(); virtual void r18(); virtual void r19();
    virtual void r20(); virtual void r21(); virtual void r22(); virtual void r23(); virtual void r24(); virtual void r25(); virtual void r26(); virtual void r27(); virtual void r28(); virtual void r29();
    virtual void r30(); virtual void r31(); virtual void r32(); virtual void clear(void *);
    virtual void point(u32, u32, V3 *); virtual void dirl(u32, u32, V3 *); virtual void spot(u32, u32, V3 *, V3 *); };
struct E { L *l; u32 q; };
struct LT { u32 n; E e[1]; };
struct S { u8 pad[8]; R *r; u8 pad2[552 - 12]; LT *lt; };
extern "C" {
void fn_80103F78(void *m, V3 *v, V3 *o, s32 n);
void fn_80104004(void *m, V3 *v, V3 *o);

static inline void xfp(B *b, V3 *v, V3 *o) {
    void *m = b->mtx();
    if (m) fn_80104004(m, v, o);
    else { o->x = v->x; o->y = v->y; o->z = v->z; }
}
static inline void xfd(B *b, V3 *v, V3 *o) {
    void *m = b->mtx();
    if (m) fn_80103F78(m, v, o, 1);
    else { o->x = v->x; o->y = v->y; o->z = v->z; }
}

void fn_8018AFF4(L *l, S *s, void *unused, u32 idx, void *x, B *b) {
    R *r = s->r;
    V3 p;
    V3 d;
    if (!idx) r->clear(x);
    if (s->lt->n > idx && s->lt->e[idx].l == l) return;
    switch (l->type) {
    case 1:
        if (!b) r->point(idx, l->f16, &l->pos);
        else { xfp(b, &l->pos, &p); r->point(idx, l->f16, &p); }
        break;
    case 0:
        if (!b) r->dirl(idx, l->f16, &l->dir);
        else { xfd(b, &l->dir, &d); r->dirl(idx, l->f16, &d); }
        break;
    case 2:
        if (!b) r->spot(idx, l->f16, &l->pos, &l->dir);
        else { xfp(b, &l->pos, &p); xfd(b, &l->dir, &d); r->spot(idx, l->f16, &p, &d); }
        break;
    }
}

} /* extern "C" */
