// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V { f32 x, y, z; };
struct E { u8 pad[8]; u8 r, g, b; u8 pad11[33]; u32 f44; };
struct L { u32 n; E **arr; };
struct R { u8 pad[20]; V f20; f32 f32_; u8 pad36[24]; f32 f60; f32 f64; f32 f68; f32 f72; };
struct Q { u8 pad[16]; R *f16; };
struct P { u8 pad[16]; void *f16; u8 pad20[12]; u32 f32_; };
struct FT { u8 pad[12]; void (*f12)(void *, V *); };
extern FT lbl_803286D0;
struct A { u32 f0; u8 pad4[104]; L *f108; u8 pad112[8]; void *f120; u8 pad124[20]; u8 *f144; };
struct O { u32 f0; u8 pad4[44]; P *f48; u8 pad52[56]; void *f108; u8 pad112[40]; u32 f152; f32 f156; u8 pad160[12]; f32 f172; };
struct M { V v; };
struct T;
extern T *lbl_8035A1A8;
extern u32 lbl_8035E4BC, lbl_8035E4C0, lbl_8035E49C, lbl_8035E4A0, lbl_8035E4A4;
extern f32 lbl_8035E4A8, lbl_8035E4C4, lbl_8035E4C8, lbl_8035E4CC, lbl_8035A270;
extern int lbl_80359748;
struct T { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void get(V *, V *, V *, V *, int); virtual void set(V *, V *, V *, V *, int);
    u8 pad4[28]; V f20v; u8 pad44[236]; V f280; u8 pad292[48]; f32 f340; u8 pad344[384]; V f728; A *f740; A *f744; O *f748; O *f752[2]; u8 pad760[80]; f32 f840; f32 f844; u8 pad848[20]; void **f868; f32 f872; };
void fn_80231AD8(T *, void *, int, V *, char *);
void fn_80190C98(O *);
void fn_80107F3C(void *, V *);
void fn_80196688(O *);
void fn_80101414(V *, V *, f32);
void fn_80101820(V *);

static inline void Bright(L *l) {
    E *e;
    u32 i;
    for (i = 0; i < l->n; i++) {
        e = l->arr[i];
        if (e->f44 & 0x10) {
            e->r = 0xff; e->g = 0xff; e->b = 0xff;
            e->f44 |= lbl_8035E4BC;
        }
    }
}

static inline void BrightO(O *o) {
    E *e; L *l; u32 i;
    if (o) {
        l = (L *)o->f108;
        if (l) {
            for (i = 0; i < l->n; i++) {
                e = l->arr[i];
                if (e->f44 & 0x10) {
                    e->r = 0xff; e->g = 0xff; e->b = 0xff;
                    e->f44 |= lbl_8035E4BC;
                }
            }
        }
    }
}

static inline void VSet(V *v, f32 x, f32 y, f32 z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

static inline void Fin(T *t) {
    O *o;
    u32 i;
    for (i = 0; i < 2; i++) {
        if (t->f752[i]) {
            t->f752[i]->f0 |= lbl_8035E4A0;
            o = t->f752[i];
            o->f156 = lbl_8035E4A8;
            o->f152 &= ~6;
            o->f172 = lbl_8035E4A8;
            fn_80196688(o);
            t->f752[i]->f152 |= lbl_8035E4A4;
            t->f752[i]->f152 &= ~8;
        }
    }
}

void fn_8005D9EC(T *t, void *a, int b, V *c, char *d, L *nl) {
    V p0, p1, p2, p3, sv;
    A *ap;
    L *l;
    u32 i;
    O *o;
    ap = t->f740;
    if (ap) {
        l = ap->f108;
        if (!l) l = (L *)(ap->f144 + 0x1c);
        if (l) {
            Bright(l);
        }
    }
    ap = t->f744;
    if (ap) {
        l = ap->f108;
        if (!l) l = (L *)(ap->f144 + 0x1c);
        if (l) {
            Bright(l);
        }
    }
    BrightO(t->f752[0]);
    BrightO(t->f752[1]);
    t->f844 = lbl_8035E4A8;
    t->f840 = lbl_8035E4A8;
    fn_80231AD8(t, a, b, c, d);
    t->get(&p0, &p1, &p2, &p3, 0);
    *(volatile f32 *)&p0.x = p0.x - lbl_8035E4A8;
    *(volatile f32 *)&p0.y = p0.y - lbl_8035E4A8;
    { f32 m, z;
    z = p0.z - *(volatile f32 *)&lbl_8035E4C4;
    *(volatile f32 *)&p0.z = z;
    m = *(volatile f32 *)&lbl_8035E4C8;
    p0.x = p0.x - m * p1.x;
    p0.y = p0.y - m * p1.y;
    p0.z = z - m * p1.z; }
    if (t->f748) {
        P *pp;
        Q *q;
        R *r;
        V *src;
        lbl_8035A1A8 = t;
        { O *w = *(O * volatile *)&t->f748; w->f0 |= *(volatile u32 *)&lbl_8035E4C0; }
        src = (V *)t->f868[3];
        q = (Q *)t->f748->f108;
        { f32 z = *(volatile f32 *)&src->z; f32 y = *(volatile f32 *)&src->y;
        r = *(R * volatile *)&q->f16;
        VSet(&r->f20, *(volatile f32 *)&src->x, y, z); }
        r->f32_ = lbl_8035E4CC;
        t->f872 = lbl_8035E4CC;
        o = t->f748;
        pp = o->f48;
        if (pp) {
            lbl_803286D0.f12(pp->f16, &p0);
            pp->f32_ |= lbl_8035E49C;
            fn_80190C98(o);
        }
        q->f16->f64 = *(f32 *)((u8 *)t + 0x314);
        q->f16->f68 = *(f32 *)((u8 *)t + 0x318);
        q->f16->f72 = *(f32 *)((u8 *)t + 0x31c);
        q->f16->f60 = *(f32 *)((u8 *)t + 0x320);
    }
    if (t->f740 || t->f744) {
        f32 s;
        t->f728.x = lbl_8035E4A8;
        t->f728.y = lbl_8035E4A8;
        t->f728.z = lbl_8035E4A8;
        if (t->f740 && t->f740->f120) fn_80107F3C(t->f740->f120, &t->f728);
        if (t->f744 && t->f744->f120) fn_80107F3C(t->f744->f120, &t->f728);
        t->set(&p0, 0, 0, 0, 0);
        if (nl) {
            if (t->f740) t->f740->f108 = nl;
            if (t->f744) t->f744->f108 = nl;
        }
        *(volatile f32 *)&sv.x = t->f280.x;
        *(volatile f32 *)&sv.y = t->f280.y;
        *(volatile f32 *)&sv.z = t->f280.z;
        s = t->f340;
        int g = *(volatile int *)&lbl_80359748;
        if (g == 1 || g == 5) {
            fn_80101414(&sv, &t->f20v, lbl_8035A270);
            p1 = sv;
            fn_80101820(&p1);
            p2.x = p1.y * p3.z - p1.z * p3.y;
            p2.y = p1.z * p3.x - p1.x * p3.z;
            p2.z = p1.x * p3.y - p1.y * p3.x;
            fn_80101820(&p2);
            p3.x = p2.y * p1.z - p2.z * p1.y;
            p3.y = p2.z * p1.x - p2.x * p1.z;
            p3.z = p2.x * p1.y - p2.y * p1.x;
            fn_80101820(&p3);
            t->set(&p0, &p1, &p2, &p3, 0);
        }
        t->f280 = sv;
        t->f340 = s;
        if (t->f740) t->f740->f0 |= lbl_8035E4A0;
        if (t->f744) t->f744->f0 |= lbl_8035E4A0;
    }
    Fin(t);
    *((u8 *)t + 0x374) &= ~1;
}

} /* extern "C" */
