#include "common.h"
extern "C" {
}
#define F(p,o,t) (*(t*)((u8*)(p)+(o)))
struct V3 { f32 x, y, z; };
struct V4 { f32 x, y, z, w; };
struct Part { volatile u32 f0; u8 p4[0x98 - 4]; u32 f98; f32 f9c; u8 pa0[0xac - 0xa0]; f32 fac; };
struct R { u8 p0[0x10]; void *f10; u8 p14[0x20 - 0x14]; u32 f20; };
struct N { volatile u32 f0; u8 p4[0x30 - 4]; R *f30; };
struct Q { u8 p0[0x14]; V4 c; };
struct P { u8 p0[0x10]; Q *f10; u8 p14[4]; V3 f18; };
struct O {
    u8 p0[0xe0]; N *e0; u8 pe4[0x14c - 0xe4]; Part *parts[6]; u8 p164[0x178 - 0x164]; s32 f178;
    u8 p17c[0x2f8 - 0x17c]; P *f2f8[4]; u8 p308[0x310 - 0x308]; V3 f310; V3 f31c; V4 col[4];
};
extern "C" {
typedef void (*Fn)(void *, V3 *);
extern Fn lbl_803286D0[];
extern u32 lbl_8035B9A0, lbl_8035BA08, lbl_8035B964;
extern f32 lbl_8035B99C, lbl_8035BA0C, lbl_8035BA10, lbl_8035BA14, lbl_8035B960, lbl_8035B9F4, lbl_8035B9F0, lbl_8035BA18;
extern f32 lbl_8035BA1C, lbl_8035BA04, lbl_8035BA00;
extern f32 lbl_80301D40[];
u32 rand(void);
void fn_80196688(Part *);
void fn_80190C98(N *);
f64 fn_800EFDA4(f32);
f64 fn_800F030C(f32);
void fn_8010121C(V3 *, f32);
void fn_8010117C(V3 *, f32);
static inline void on(O *o, int i) {
    Part *p;
    o->parts[i]->f0 |= lbl_8035B9A0;
    p = o->parts[i];
    p->f9c = lbl_8035B99C;
    p->f98 &= ~6;
    p->fac = lbl_8035B99C;
    fn_80196688(p);
    o->parts[i]->f98 |= lbl_8035BA08;
}
void fn_8002CA0C(O *o, f32 dt) {
    V3 c;
    V3 t;
    R *r;
    N *n;
    u32 i;
    f32 s;
    r = o->e0->f30;
    if (r) lbl_803286D0[76](r->f10, &c);
    else { c.x = lbl_8035B99C; c.y = lbl_8035B99C; c.z = lbl_8035B99C; }
    if (o->f178) {
        if (!(o->e0->f0 & 0x800)) o->e0->f0 |= lbl_8035B9A0;
        f32 k;
        f32 y = lbl_8035BA0C * dt + c.y;
        *(volatile f32 *)&c.y = y;
        k = *(volatile f32 *)&lbl_8035BA10;
        if (y >= k) {
            c.y = k;
            o->parts[0]->f98 &= ~8;
            o->parts[1]->f98 &= ~8;
            o->parts[2]->f98 &= ~8;
            o->parts[3]->f98 &= ~8;
            o->parts[4]->f98 &= ~8;
            o->parts[5]->f98 &= ~8;
            if (!(o->parts[0]->f0 & 0x800)) {
                on(o, 0);
                on(o, 1);
                on(o, 2);
                on(o, 3);
                on(o, 4);
                on(o, 5);
            }
        }
    } else {
        f32 k;
        f32 y = c.y - lbl_8035BA0C * dt;
        *(volatile f32 *)&c.y = y;
        k = *(volatile f32 *)&lbl_8035BA14;
        if (y <= k) {
            c.y = k;
            if (o->e0->f0 & 0x800) {
                o->e0->f0 &= ~0x800;
                o->parts[0]->f0 &= ~0x800;
                o->parts[1]->f0 &= ~0x800;
                o->parts[2]->f0 &= ~0x800;
                o->parts[3]->f0 &= ~0x800;
                o->parts[4]->f0 &= ~0x800;
                o->parts[5]->f0 &= ~0x800;
            }
        }
    }
    n = o->e0;
    r = n->f30;
    if (r) {
        lbl_803286D0[3](r->f10, &c);
        r->f20 |= lbl_8035B964;
        fn_80190C98(n);
    }
    {
        extern volatile s8 lbl_80359F3C;
        extern volatile f32 lbl_80359F38;
        if (!lbl_80359F3C) { lbl_80359F38 = lbl_8035B99C; lbl_80359F3C = 1; }
        lbl_80359F38 = lbl_8035B960 * dt + lbl_80359F38;
        { f32 p = lbl_80359F38; if (p > *(volatile f32 *)&lbl_8035B9F4) lbl_80359F38 = p - lbl_8035B9F0; }
        { f64 d = fn_800EFDA4(lbl_80359F38); f32 K = lbl_8035BA18; s = K * (f32)d; }
    }
    t = o->f310;
    fn_8010121C(&t, s);
    o->f2f8[1]->f18 = t;
    t = o->f31c;
    fn_8010117C(&t, s);
    o->f2f8[2]->f18 = t;
    for (i = 1; i < 3; i++) {
        f32 k;
        Q *q;
        f32 rr = lbl_8035BA1C * (f32)(s32)(rand() % 5000);
        lbl_80301D40[i] += rr - lbl_8035BA04;
        k = lbl_8035BA04 * (f32)fn_800F030C(lbl_80301D40[i]) + lbl_8035BA00;
        q = o->f2f8[i]->f10;
        {
            V4 *cc = &o->col[i];
            f32 x = cc->x * k, y = cc->y * k, z = cc->z * k, w = cc->w;
            q->c.x = x; q->c.y = y; q->c.z = z; q->c.w = w;
        }
    }
}
}
