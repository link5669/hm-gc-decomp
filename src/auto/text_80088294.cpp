#include "common.h"
namespace N80088294 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

struct V3 { f32 x, y, z; };
struct G { u8 pad[16]; void *h; u8 pad20[12]; u32 fl; };
struct N {
    u8 pad0[48];
    G *g;
    u8 pad52[52];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void s11();
};
struct T { u8 pad[12]; void (*f12)(void *, V3 *); };
extern T lbl_803286D0;
struct F152 { u32 fl0; u8 pad[148]; u32 fl152; };
struct P {
    u8 pad0[524];
    void *a524;
    u8 pad528[92];
    s32 i620;
    u8 pad624[80];
    N *n704;
    u8 pad708[32];
    F152 *f740;
    u8 pad744[8];
    F152 *f752;
    F152 *f756;
    u8 pad760[112];
    f32 f872;
    u8 pad876[16];
    s32 st892;
    u8 pad896[4];
    f32 f900;
    u8 pad904[4];
    s32 i908;
    u8 pad912[24];
    V3 base;
};
extern f32 lbl_8035FEB8, lbl_8035FEF4, lbl_8035FF08;
extern u32 lbl_8035FEA0, lbl_8035FEA4;
extern char lbl_8035FEF8[8], lbl_8035FF00[8];
extern void *lbl_8035B65C;
void fn_800885A0(P *, f32);
void __ct__9C80253F24Fiiii(void *, char *, P *, int, int);
void fn_802494A4(void *, int);
void fn_80241DD0(void *, char *, P *, int, int, int);
void fn_80190C98(N *);
void fn_80088B54(P *, f32);
void fn_8005E6BC(P *, f32);
void fn_8005E00C(P *, f32);
int rand(void);

void fn_80088294(P *p, f32 dt) {
    if (p->i620) {
        switch (p->st892) {
        case 0:
            fn_800885A0(p, dt);
            break;
        case 1:
            p->f900 -= dt;
            if (p->f900 <= lbl_8035FEB8) {
                if (p->f740) p->f740->fl0 &= ~0x800;
                if (p->f752) {
                    p->f752->fl152 |= lbl_8035FEA0;
                    p->f752->fl0 &= ~0x800;
                }
                if (p->f756) {
                    p->f756->fl152 |= lbl_8035FEA0;
                    p->f756->fl0 &= ~0x800;
                }
                if (p->i908 == 0) __ct__9C80253F24Fiiii(lbl_8035B65C, lbl_8035FEF8, p, 0, 0);
                fn_802494A4(p->a524, 0);
                fn_80241DD0(p->a524, lbl_8035FF00, p, 0, 0, 0);
                p->st892 = 2;
            }
            break;
        case 2:
            if (p->n704) {
                V3 v;
                f32 z, b;
                f32 a;
                N *n;
                G *g;
                p->n704->s11();
                {
                    s32 r = rand() % 1000u;
                    a = lbl_8035FEF4 * (f32)r;
                }
                {
                    s32 r = rand() % 1000u;
                    b = lbl_8035FEF4 * (f32)r;
                    v.y = a;
                    *(volatile f32 *)&v.x = b; z = *(volatile f32 *)&lbl_8035FEB8; v.z = z;
                }
                v.x = b + p->base.x;
                v.y += p->base.y;
                v.z = z + p->base.z;
                n = p->n704;
                g = n->g;
                if (g) {
                    lbl_803286D0.f12(g->h, &v);
                    g->fl |= lbl_8035FEA4;
                    fn_80190C98(n);
                }
            }
            {
                s32 r = rand() % 30000u;
                f32 d = lbl_8035FEF4 * (f32)r;
                d = lbl_8035FF08 + d;
                p->f872 = d;
            }
            p->st892 = 3;
            break;
        case 3:
            fn_80088B54(p, dt);
            break;
        }
    }
    fn_8005E6BC(p, dt);
    fn_8005E00C(p, dt);
}

} /* extern "C" */

}
namespace N800885A0 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

struct V3 { f32 x, y, z; };

struct M30 { u8 pad[0x10]; void *f10; u8 pad14[0xc]; u32 f20; };
class Node { public:
    u32 f0; u8 pad4[0x2c]; void *f30; u8 pad34[0x68 - 0x34];
    virtual void n0(); virtual void n1(); virtual void upd(); virtual void n3(); virtual void n4(); virtual void n5();
    virtual void n6(); virtual void n7(); virtual void n8(); virtual void n9(); virtual void n10();
    virtual void tick(f32 dt); };
class Node2 : public Node { public: u8 pad6c[0x78 - 0x6c]; void *f78; };
struct Grp { u8 pad[0x30]; M30 *f30; };
struct FT { void *f0, *f4, *f8; void (*fc)(void *, V3 *); void *f10[8]; void (*f30)(void *, V3 *, V3 *); };

struct Fl { u32 f0; f32 f4; u8 pad8[0x28]; u32 f30; };
struct FH { u8 pad[8]; Fl *f8; };
struct TH { u32 f0; u8 pad4[0x74]; void *f78; u8 pad7c[8]; FH *f84; u32 f88; };
struct Mgr { u8 pad[0xc]; void *fc; };

class Tk { public:
    virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3(); virtual void t4(); virtual void t5();
    virtual void t6(); virtual void t7(); virtual void t8(); virtual void t9(); virtual void t10(); virtual void t11();
    virtual void t12(); virtual void t13();
    virtual void tick(f32 dt);
};

class Obj { public:
    virtual void o0(); virtual void o1(); virtual void o2(); virtual void o3(); virtual void o4(); virtual void o5();
    virtual void o6(); virtual void o7(); virtual void o8(); virtual void o9(); virtual void o10(); virtual void o11();
    virtual void o12();
    virtual void getXf(V3 *pos, V3 *fwd, V3 *up, V3 *right, s32 a);
    virtual void o14(); virtual void o15(); virtual void o16();
    virtual void o17();
    virtual void o18();
    virtual void o19(); virtual void o20();
    virtual void o21(); virtual void o22(); virtual void o23(); virtual void o24(); virtual void o25(); virtual void o26();
    virtual void o27(); virtual void o28(); virtual void o29(); virtual void o30(); virtual void o31(); virtual void o32();
    virtual void msg(void *id, s32 a, s32 b, s32 c, s32 d);
    virtual void o34(); virtual void o35(); virtual void o36();
    virtual void kill(s32 a, V3 *v, void *h);
    u8 pad4[0x40];
    V3 f44;
    u8 pad50[0x268 - 0x50];
    f32 f268;
    s32 on;
    u8 pad270[0x2c0 - 0x270];
    TH *f2c0;
    s32 f2c4;
    u8 pad2c8[0x2d8 - 0x2c8];
    V3 f2d8;
    Node2 *f2e4;
    Node2 *f2e8;
    Grp *f2ec;
    Node2 *f2f0[2];
    Grp *f2f8[5];
    u8 pad30c[0x348 - 0x30c];
    f32 f348;
    u8 pad34c[8];
    f32 f354;
    u8 pad358[4];
    f32 f35c;
    u8 pad360[8];
    f32 f368;
    u8 pad36c[0x378 - 0x36c];
    Tk *f378;
    u8 pad37c[0x39c - 0x37c];
    V3 f39c;
    V3 f3a8;
    u8 pad3b4[0x438 - 0x3b4];
    f32 f438;
    f32 *f43c;
};

extern u32 lbl_8035FEA4, lbl_8035FEA8;
extern f32 lbl_8035FEB8, lbl_8035FEC8, lbl_8035FED4, lbl_8035FF18, lbl_8035FF1C;
extern Mgr *lbl_8035B65C;
extern Obj *lbl_8035A1A8;
extern FT lbl_803286D0;

void fn_8005E6BC(Obj *o, f32 dt);
void fn_80230928(Obj *o, f32 dt);
void fn_80238618(Obj *o, f32 dt);
void fn_80107F3C(void *o, V3 *s);
void fn_80190C98(void *o);
void fn_801907D8(void *o);
void fn_80107244(void *o, V3 *v);
void fn_8019B7E8(void *m, TH *h);
s32 fn_80264E0C(V3 *a, V3 *b, V3 *c, V3 *d, s32 *e, s32 *f, void **g, s32 h, s32 i, s32 j, s32 k, s32 l, s32 m, s32 n, s32 o);

inline void SetPos(Grp *g, V3 *v) {
    M30 *m = g->f30;
    if (m) {
        lbl_803286D0.fc(m->f10, v);
        m->f20 |= lbl_8035FEA4;
        fn_80190C98(g);
    }
}
inline void SetAx(Grp *g, V3 *a, V3 *b) {
    M30 *m = g->f30;
    if (m) {
        lbl_803286D0.f30(m->f10, a, b);
        m->f20 |= lbl_8035FEA4;
        fn_80190C98(g);
    }
}
inline void GetPos(Node2 *n, V3 *v) {
    if (n->f30) fn_80107244(n->f30, v);
    else { v->x = lbl_8035FEB8; v->y = lbl_8035FEB8; v->z = lbl_8035FEB8; }
}
inline Fl *GetFl(TH *h) { FH *q = h->f84; if (q == 0) return 0; return q->f8; }

static inline Grp *GG(Obj *o, u32 i) { return o->f2f8[i]; }
void fn_800885A0(Obj *o, f32 dt) {
    V3 pos;
    V3 b;
    V3 hp;
    V3 hn;
    V3 v;
    V3 s;
    V3 c;
    Grp *g0; M30 *m0; Grp *g1; M30 *m1; Grp *g2; M30 *m2; u32 i; TH *h; Grp *g3; M30 *m3;
    o->o17();
    o->f378->tick(dt);
    o->o18();
    o->on = 0;
    fn_80230928(o, dt);
    o->on = 1;
    if (o->f2e4) o->f2e4->tick(dt);
    if (o->f2e8) o->f2e8->tick(dt);
    fn_80238618(o, dt);
    o->f268 -= dt;
    o->getXf(&pos, 0, 0, 0, 0);
    f32 pz, z, y, x;
    x = *(volatile f32 *)&pos.x; y = *(volatile f32 *)&pos.y; z = *(volatile f32 *)&pos.z;
    *(volatile f32 *)&b.x = x;
    pz = *(volatile f32 *)&pos.z;
    *(volatile f32 *)&b.y = y; *(volatile f32 *)&b.z = z;
    f32 k = *(volatile f32 *)&lbl_8035FF18;
    b.z = z - k;
    pos.z = pz + k;
    s32 hit = fn_80264E0C(&pos, &b, &hp, &hn, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
    g0 = o->f2ec;
    if (g0 && lbl_8035A1A8 == o) {
        m0 = g0->f30;
        if (m0) { lbl_803286D0.fc(m0->f10, &o->f44); m0->f20 |= lbl_8035FEA4; fn_80190C98(g0); }
    }
    if (hit) {
        o->f39c = hp;
        o->kill(1, 0, 0);
        for (i = 0; i < 5; i++) {
            g1 = GG(o, i);
            if (g1) {
                f32 z = lbl_8035FEB8; *(volatile f32 *)&v.x = z; *(volatile f32 *)&v.y = *(volatile f32 *)&lbl_8035FED4; *(volatile f32 *)&v.z = z;
                m1 = g1->f30;
                if (m1) { lbl_803286D0.f30(m1->f10, &hn, &v); m1->f20 |= lbl_8035FEA4; fn_80190C98(g1); }
            }
        }
        o->f3a8 = o->f39c;
        o->f3a8.z += lbl_8035FEC8;
        g2 = (Grp *)o->f2c0;
        if (g2) {
            m2 = g2->f30;
            if (m2) { lbl_803286D0.fc(m2->f10, &o->f3a8); m2->f20 |= lbl_8035FEA4; fn_80190C98(g2); }
            h = o->f2c0;
            h->f0 |= lbl_8035FEA8;
            s.x = lbl_8035FED4; s.y = lbl_8035FED4; s.z = lbl_8035FED4;
            if (h->f78) fn_80107F3C(h->f78, &s);
            if (h->f88 == 0) fn_8019B7E8(lbl_8035B65C->fc, h);
            if (GetFl(h)) {
                Fl *f = GetFl(h);
                if (f->f30 & 1) { f->f4 = lbl_8035FEB8; f->f0 &= ~0x18; }
            }
        }
        o->f438 = *o->f43c;
    }
    if (o->f2e8) o->f2e8->tick(dt);
    for (i = 0; i < 2; i++) {
        if (o->f2f0[i]) {
            fn_801907D8(o->f2f0[i]);
            if (o->f2e4) GetPos(o->f2e4, &c);
            else if (o->f2e8) GetPos(o->f2e8, &c);
            g3 = (Grp *)o->f2f0[i];
            m3 = g3->f30;
            if (m3) { lbl_803286D0.fc(m3->f10, &c); m3->f20 |= lbl_8035FEA4; fn_80190C98(g3); }
            o->f2f0[i]->tick(dt);
        }
    }
    fn_8005E6BC(o, dt);
    f32 r;
    if (o->f348 < o->f35c) r = o->f348 / o->f35c;
    else r = lbl_8035FED4;
    if (r < lbl_8035FF18) r = lbl_8035FF18;
    o->f2d8.x = o->f354 * r;
    o->f2d8.y = o->f354 * r;
    o->f2d8.z = o->f354 * r;
    if (o->f2e4 && o->f2e4->f78) fn_80107F3C(o->f2e4->f78, &o->f2d8);
    if (o->f2e8 && o->f2e8->f78) fn_80107F3C(o->f2e8->f78, &o->f2d8);
    o->f348 += dt;
    if (o->f348 > lbl_8035FF1C) o->kill(0, 0, 0);
}

}

}
namespace N80088B54 {
// fn_80088B54 NonMatching draft: SDIFF 15 (volatile stores/loads pin constant-load order).
// split_file divides it into the game's real files (file_status shows its range).

#define VS(v) (*(volatile f32 *)&(v))
#define VK(v) (*(volatile f32 *)&(v))

extern "C" {

struct V3 { f32 x, y, z; };
struct Sph { f32 x, y, z, r; };
struct G { u8 pad[16]; void *h; u8 pad20[12]; u32 fl; };
struct El { u8 pad[0x28]; };
struct Z { u8 pad[0x24]; El *e; };
class Node { public:
    u32 f0; u16 type; u8 pad6[0x12]; f32 x, y, z, r; u8 pad28[8]; G *g; u8 pad34[0x68 - 0x34];
    virtual void n0(); virtual void n1(); virtual void upd(); virtual void n3(); virtual void n4(); virtual void n5();
    virtual void n6(); virtual void n7(); virtual void n8(); virtual void n9(); virtual void n10();
    virtual void tick(f32 dt);
    u8 pad6c[0x78 - 0x6c]; void *f78; u8 pad7c[0xa8 - 0x7c]; Z *za8; };
struct X { u8 pad[0x9c]; Node *n; u8 pada0[0x1d4 - 0xa0]; s32 *p1d4; u8 pad1d8[0x220 - 0x1d8]; s32 v220; };
struct FT { void *f0, *f4, *f8; void (*fc)(void *, V3 *); void *f10, *f14, *f18; void (*f1c)(void *, V3 *, V3 *, V3 *); };
struct F152 { u32 fl0; u8 pad[148]; u32 fl152; };
struct P {
    u8 pad0[0x26c];
    s32 on;
    u8 pad270[0x2c0 - 0x270];
    Node *n704;
    u8 pad2c4[0x2f8 - 0x2c4];
    F152 *f2f8[5];
    u8 pad30c[0x368 - 0x30c];
    f32 f872;
    u8 pad36c[0x37c - 0x36c];
    s32 st892;
    u8 pad380[0x39c - 0x380];
    V3 tgt;
    V3 base;
    u32 cnt;
    X *x[6];
    u8 pad3d0[0x3e8 - 0x3d0];
    Node *n[6];
    s32 idx[6];
    f32 tm[6];
    f32 t430;
    f32 *p434;
    f32 t438;
    u8 pad43c[4];
    f32 *p440;
    f32 *p444;
};
extern f32 lbl_8035FEB8, lbl_8035FEF4, lbl_8035FF08, lbl_8035FEC8, lbl_8035FED4, lbl_8035FF18, lbl_8035FF28;
extern f64 lbl_8035FF20;
extern u32 lbl_8035FEA0, lbl_8035FEA4, lbl_8035FEA8;
extern FT lbl_803286D0;
void fn_80190C98(Node *);
void fn_80100CF4(Sph *s);
void fn_80107244(El *, V3 *);
void fn_80101820(V3 *v);
f32 fn_80101590(V3 *a, V3 *b);
void fn_80107F3C(void *o, V3 *s);
void fn_8008930C(P *, V3 *, int, f32);
int rand(void);

inline void SetPos(Node *n, V3 *v) {
    G *g = n->g;
    if (g) {
        lbl_803286D0.fc(g->h, v);
        g->fl |= lbl_8035FEA4;
        fn_80190C98(n);
    }
}
inline void SetAxes(Node *n, V3 *a, V3 *b, V3 *c) {
    G *g = n->g;
    if (g) {
        lbl_803286D0.f1c(g->h, a, b, c);
        g->fl |= lbl_8035FEA4;
        fn_80190C98(n);
    }
}
inline void SetPos3(G *g, Node *n, V3 *v) {
    if (g) {
        lbl_803286D0.fc(g->h, v);
        g->fl |= lbl_8035FEA4;
        fn_80190C98(n);
    }
}
inline void SetAxes3(G *g, Node *n, V3 *a, V3 *b, V3 *c) {
    if (g) {
        lbl_803286D0.f1c(g->h, a, b, c);
        g->fl |= lbl_8035FEA4;
        fn_80190C98(n);
    }
}
inline f32 Rnd(u32 n) {
    s32 r = rand() % n;
    return lbl_8035FEF4 * (f32)r;
}
inline void Cross(V3 *o, const V3 *a, const V3 *b) {
    f32 x = a->y * b->z - a->z * b->y;
    f32 y = a->z * b->x - a->x * b->z;
    f32 z = a->x * b->y - a->y * b->x;
    o->x = x; o->y = y; o->z = z;
}
inline s32 IsOn(X *x) {
    if (x->v220 > 0) return 1;
    if (x->v220 < 0) return 0;
    if (x->p1d4) return *x->p1d4;
    return 1;
}

void fn_80088B54(P *p, f32 dt) {
    V3 c, side, d, up, sc;
    Sph sp;
    V3 t;
    V3 v;
    fn_80100CF4(&sp);
    if (p->n704) {
        f32 z, b;
        f32 a;
        p->n704->tick(dt);
        {
            s32 r = rand() % 1000u;
            a = lbl_8035FEF4 * (f32)r;
        }
        {
            s32 r = rand() % 1000u;
            b = lbl_8035FEF4 * (f32)r;
            v.y = a;
            *(volatile f32 *)&v.x = b; z = *(volatile f32 *)&lbl_8035FEB8; v.z = z;
        }
        v.x = b + p->base.x;
        v.y = a + p->base.y;
        v.z = z + p->base.z;
        SetPos3(p->n704->g, p->n704, &v);
    }
    {
        s32 r = rand() % 30000u;
        f32 d = lbl_8035FEF4 * (f32)r;
        d = lbl_8035FF08 + d;
        p->f872 = d;
    }
    p->st892 = 3;
    if (p->t430 <= lbl_8035FEB8) {
        p->t430 = *p->p434;
        f32 z;
        VS(t.x) = p->base.x; VS(t.y) = p->base.y; z = p->base.z; VS(t.z) = z;
        t.z = z - VK(lbl_8035FEC8);
        fn_8008930C(p, &t, 0, *p->p440);
    }
    p->t430 -= dt;
    u32 i;
    for (i = 0; i < p->cnt; i++) {
        if (p->n[i]) {
            Node *y = p->x[i]->n;
            Node *n = (Node *)(void *)p->n[i];
            if (y->type == 3) {
                fn_80107244(&y->za8->e[p->idx[i]], &c);
            } else {
                if (y->f0 & 4) y->upd();
                sp.x = y->x; sp.y = y->y; sp.z = y->z; sp.r = y->r;
                c.x = sp.x; c.y = sp.y; c.z = sp.z;
            }
            d.x = p->tgt.x - c.x;
            d.y = p->tgt.y - c.y;
            d.z = p->tgt.z - c.z;
            fn_80101820(&d);
            { f32 z0 = lbl_8035FEB8; VS(up.x) = z0; VS(up.y) = z0; VS(up.z) = VK(lbl_8035FED4); }
            Cross(&side, &d, &up);
            fn_80101820(&side);
            Cross(&up, &d, &side);
            fn_80101820(&up);
            f32 dist = fn_80101590(&c, &p->tgt) / lbl_8035FF20;
            f32 a, b;
            {
                s32 r = rand() % 4000u;
                a = lbl_8035FEF4 * (f32)r;
                a = lbl_8035FF18 + a;
            }
            {
                s32 r = rand() % 4000u;
                b = lbl_8035FEF4 * (f32)r;
                b = lbl_8035FF18 + b;
            }
            VS(sc.x) = b; sc.y = a; sc.z = dist;
            f32 k = VK(lbl_8035FF28) * dist;
            t.x = k * d.x + p->tgt.x;
            t.y = k * d.y + p->tgt.y;
            t.z = k * d.z + p->tgt.z;
            SetPos(p->n[i], &t);
            SetAxes(p->n[i], &side, &up, &d);
            if (n->f78) fn_80107F3C(n->f78, &sc);
            {
                if (Rnd(10000) < *p->p444) n->f0 |= lbl_8035FEA8;
                else n->f0 &= ~0x800;
            }
            n->tick(dt);
            if (!(p->x[i]->n->f0 & 2) || !IsOn(p->x[i])) {
                if (p->tm[i] > lbl_8035FEB8) p->tm[i] -= dt;
                else n->f0 &= ~0x800;
            }
        }
    }
    p->t438 -= dt;
    if (p->t438 <= lbl_8035FEB8) {
        for (u32 j = 0; j < 6; j++) {
            if (p->n[i]) p->n[j]->f0 &= ~0x800;
        }
        if (p->n704) p->n704->f0 &= ~0x800;
        for (u32 j = 0; j < 5; j++) {
            if (p->f2f8[j]) p->f2f8[j]->fl152 |= lbl_8035FEA0;
        }
        p->on = 0;
    }
}

} /* extern "C" */

}
