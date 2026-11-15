#include "common.h"
extern "C" f32 lbl_8035B99C;
extern "C" {
__declspec(section ".sdata2") u32 lbl_8035B9A0 = 0x800;
__declspec(section ".sdata2") char lbl_8035B9A4[8] = "ROOMCLR";
__declspec(section ".sdata2") char lbl_8035B9AC[6] = "Level";
__declspec(section ".sdata2") char wZB_pad9B2[2] = {0, 0};
__declspec(section ".sdata2") char lbl_8035B9B4[8] = "mausolm";
__declspec(section ".sdata2") char lbl_8035B9BC[8] = "%d:%02d";
__declspec(section ".sdata2") f32 lbl_8035B9C4 = 0.01667f;
__declspec(section ".sdata2") f32 lbl_8035B9C8 = 0.1f;
}

namespace n8002B760 {

extern "C" {

#define V4(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3();
struct VA { u8 pad[8]; virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5();
    virtual void set(s32 *v, s32 a, s32 b); };
struct VB { V4(a) V4(b) V4(c) V4(d) V4(e) V4(f) V4(g) V4(h) virtual void i0();
    virtual void play(char *s, s32 a, s32 b, s32 c, s32 d); };
struct VO { u8 pad[0x80]; V4(a) V4(b) V4(c) V4(d) V4(e) virtual void Show(s32); };
struct VN { u8 pad[8]; virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void *name(s32); };
struct VR { u8 pad[0xc]; void *fc; void *f10; };
struct E { u8 pad[0x9c]; u32 f9c; };
struct S { u8 pad[0x68]; u32 f68; u32 f6c; void *f70; };
struct F { u8 pad[4]; f32 f4; f32 f8; u8 pad2[4]; u8 *f10; };
struct M { u8 pad[0xb0]; F *fb0; };
struct T { u8 pad[0x28]; void *f28; };
struct SL { u8 pad[0x28]; s32 *f28; };
struct C800FB754 { u8 d[20]; };
struct G { u8 pad[0x14]; f32 dt; };
struct W { u8 pad[0x18c]; E *f18c; u8 pad2[0x20c - 0x190]; u32 f20c; u8 pad3[0x240 - 0x210]; s32 f240;
    u8 pad4[0x540 - 0x244]; s32 *f540; u8 pad5[0x560 - 0x544]; s32 f560; };

void fn_8026820C(void *, s32);
void fn_80268178(void *, s32);
s32 fn_8003CC3C(void *);
s32 fn_8003CDA4(void *);
s32 fn_8003C930(void *);
VR *fn_802288FC(void *, char *);
VN **fn_8010FEDC(void *, void *, char *, s32);
void fn_800F6E88(void *, void *);
void __ct__9C80253F24Fiiii(void *, char *, s32, s32, s32);
void fn_80180600(void *, f32);
void fn_8002BDD4(u8 *, f32);
void fn_80236CB0(E *, s32);
void fn_80039EA4(void *, f32);
void fn_8002C150(u8 *);
s32 fn_801CCA8C(void *, u32 *, void *, u32);
void *fn_800F9398(void *, void *);
void *fn_800F9788(void *, char *, void *);
void __ct__9C800FB754Fv(C800FB754 *);
void fn_800FB700(C800FB754 *, char *, s32);
void fn_800E8F6C(char *, char *, ...);
void fn_800FA5D8(C800FB754 *, char *);
void fn_80109DD4(void *, C800FB754 *);
void fn_800FB6D8(C800FB754 *);
void fn_8002C5A4(u8 *, f32);
void fn_8002CA0C(u8 *, f32);

extern void *lbl_8035A0A4;
extern u8 *lbl_8035B65C;
extern void *lbl_8035B79C;
extern void *lbl_8035B308;
extern void *lbl_8035A02C;
extern G *lbl_8035B488;
extern char lbl_8035B9A4[8];
extern char lbl_8035B9AC[6];
extern char lbl_8035B9B4[8];
extern char lbl_8035B9BC[8];
extern char lbl_80294430[];
extern char lbl_80294440[];
extern f32 lbl_8035B99C, lbl_8035B9C4, lbl_8035B9C8, lbl_8035B960;

#define PA(o) (*(VA **)(p + (o)))
#define PO(o) (*(VO **)(p + (o)))
#define PF(o) (*(f32 *)(p + (o)))
#define PW (*(W **)(p + 0x2e8))
#define PE (*(E **)(p + 8))

static inline s32 Diff(void *g) {
    s32 a = fn_8003CC3C(g);
    return a - fn_8003CDA4(g);
}

static inline void *Find(u8 *q, char *n, void *a) {
    if (n == 0 || *n == 0) return fn_800F9398(q + 0x90, a);
    return fn_800F9788(q + 0xa8, n, a);
}

void fn_8002B760(u8 *p, s32 arg) {
    char sbuf[20];
    C800FB754 str;
    char tbuf[12];
    char nbuf[8];
    s32 v;
    T *tl;
    u32 ti;
    SL *sl;
    u32 si;
    f32 dt;
    if (PA(0x240)) {
        v = Diff(lbl_8035A0A4);
        PA(0x240)->set(&v, 0, 1);
        if (v == 0 && *(s32 *)(p + 0x248) != 0 && *(s32 *)(lbl_8035B65C + 0xb80) == 0) {
            fn_8026820C(lbl_8035B79C, 5);
            fn_80268178(lbl_8035B79C, 4);
            (*(VB **)(p + 0x2e8))->play(lbl_8035B9A4, 0, 0, 0, 0);
            PO(0x1c4)->Show(1);
            VR *r = fn_802288FC(lbl_8035B308, lbl_8035B9AC);
            void *b = r->f10;
            void *a = r->fc;
            if (b) {
                VN **n = fn_8010FEDC(a, b, lbl_80294430, 0);
                if (n) {
                    fn_800F6E88(nbuf, (*n)->name(0));
                    if (nbuf[0]) __ct__9C80253F24Fiiii(lbl_8035B65C, nbuf, 0, 0, 0);
                }
            }
        }
        *(s32 *)(p + 0x248) = v;
    }
    if (PA(0x23c)) {
        v = fn_8003C930(lbl_8035A0A4);
        PA(0x23c)->set(&v, 0, 1);
    }
    dt = lbl_8035B488->dt;
    if (PF(0x2f4) > lbl_8035B99C) {
        PF(0x2f4) -= dt;
        if (PF(0x2f4) <= lbl_8035B99C) {
            PO(0x1f0)->Show(0);
            PO(0x1f4)->Show(0);
            PF(0x2f4) = lbl_8035B99C;
        }
    }
    fn_80180600(*(void **)(p + 0xb4), dt);
    if (PF(0x260) <= *(f32 *)(*(u8 **)(p + 0x238) + 0xc)) PF(0x260) += dt;
    fn_8002BDD4(p, dt);
    if (PW->f560 == 1) {
        if (PE && PE->f9c) {
            fn_80236CB0(PE, 0);
            PE = 0;
        }
    } else {
        E *e = PW->f18c;
        if (PE != e) {
            if (PE && PE->f9c) fn_80236CB0(PE, 0);
            if (e && e->f9c) fn_80236CB0(e, 1);
            PE = e;
        }
    }
    fn_80039EA4(lbl_8035A02C, lbl_8035B488->dt);
    if (arg && PW->f240 == 0) {
        fn_8002C150(p);
        ti = 0;
        PF(0x268) -= dt;
        S *s = *(S **)(p + 0x1bc);
        fn_801CCA8C(s->f70, &ti, &tl, s->f68);
        void *tx = tl->f28;
        u32 w = PW->f20c;
        M *m = (M *)Find(*(u8 **)(p + 0xac), lbl_8035B9B4, lbl_80294440);
        if (m) {
            if (PF(0x268) < *(f32 *)&lbl_8035B99C) PF(0x268) = lbl_8035B99C;
            __ct__9C800FB754Fv(&str);
            fn_800FB700(&str, sbuf, 10);
            F *f = m->fb0;
            f32 t = ((f32)(s32)*(u16 *)(f->f10 + 0x34) - f->f4) / f->f8;
            fn_800E8F6C(tbuf, lbl_8035B9BC, (s32)(lbl_8035B9C4 * t), (s32)t % 60);
            fn_800FA5D8(&str, tbuf);
            if (w) fn_80109DD4(tx, &str);
            else fn_80109DD4(tx, &str);
            fn_800FB6D8(&str);
        }
        fn_8002C5A4(p, dt);
    }
    fn_8002CA0C(p, dt);
    si = 0;
    s32 sc = *PW->f540;
    S *s2 = *(S **)(p + 0x1b4);
    fn_801CCA8C(s2->f70, &si, &sl, s2->f68);
    sl->f28[3] = sc;
    if (*(s32 *)(*(u8 **)(p + 0x244) + 0xc) == 2) {
        if (PF(0x280) > lbl_8035B99C) {
            PF(0x280) -= dt;
            VO *o = PO(0x1b4);
            if (*(u32 *)((u8 *)o + 0x6c) & 1) {
                if (o) o->Show(0);
            } else {
                if (o) o->Show(1);
            }
        } else if (PF(0x280) < lbl_8035B99C) {
            VO *o = PO(0x1b4);
            if (o) o->Show(1);
        }
    }
    if (PF(0x27c) > lbl_8035B99C) {
        PF(0x27c) -= dt;
    } else {
        s32 *a = *(s32 **)(p + 0x274);
        s32 av = *a;
        s32 *b = *(s32 **)(p + 0x278);
        s32 bv = *b;
        if (av != bv) {
            if (bv > av) {
                *b = av;
            } else if (bv < av) {
                *b = bv + 1;
                if (**(s32 **)(p + 0x278) >= 10 && **(s32 **)(p + 0x274) >= 10) {
                    **(s32 **)(p + 0x274) -= 10;
                    W *w2 = PW;
                    (*w2->f540)++;
                    if (*w2->f540 < 0) *w2->f540 = 0;
                    PF(0x280) = lbl_8035B960;
                    **(s32 **)(p + 0x278) = 0;
                }
            }
            PF(0x27c) = lbl_8035B9C8;
        }
    }
}

}
} /* namespace n8002B760 */
#undef PA
#undef PE
#undef PF
#undef PO
#undef PW
#undef V4

namespace n8002BDC8 {
extern "C" {
/* Functions from 0x8002BDC8 to 0x8002BDD4, found by decomp-toolkit. */

s32 fn_8002BDC8(void) {
    return 0;
}

int fn_8002BDD0(int a) { return a; }

}
} /* namespace n8002BDC8 */

extern "C" {
__declspec(section ".sdata2") f32 lbl_8035B9D8 = 1.0f;
}
#define lbl_8035B9DC 1.5f
#define lbl_8035B9E0 -0.5f
#define lbl_8035B9E4 0.33f
#define lbl_8035B9E8 0.66f
#define lbl_8035B9EC 4.0f
namespace n8002BDD4 {
#pragma push
#pragma use_lmw_stmw on
extern "C" {
/* QV=2.0p1; lbl_8035B99C etc are the .sdata2 pool literals (values of 1.0f..6.0f are placeholders for lbl_8035B9D8..EC) */
struct Rc { u8 pad[72]; f32 x0; u8 pad2[4]; f32 x1; };
struct El { u8 pad[8]; f32 v; u8 pad2[4]; };
struct Lst { u8 pad[16]; El *e; s32 *ok; };
struct Pl { u8 pad[424]; f32 w; f32 h; u8 pad2[904]; f32 *sc; u8 pad3[392]; s32 f6c4; };
struct Gx { u8 pad[644]; s32 busy; u8 pad2[8]; f32 t; };
struct Gm { u8 pad[140]; u32 flags; u8 pad2[2784]; Gx *gx; };
struct Tx { u8 pad[12]; f32 w; };
struct Obj {
    u8 pad[360];
    f32 t1;      /* 360 */
    s32 v1;      /* 364 */
    f32 t0;      /* 368 */
    s32 v0;      /* 372 */
    u8 pad2[4];
    Lst *lst;    /* 380 */
    u8 pad3[8];
    Rc *r0;      /* 392 */
    u8 pad4[4];
    Rc *r1;      /* 400 */
    u8 pad5[4];
    Rc *r2;      /* 408 */
    u8 pad6[4];
    Rc *r3;      /* 416 */
    Rc *r4;      /* 420 */
    s32 n;       /* 424 */
    Tx *ta;      /* 428 */
    Tx *tb;      /* 432 */
    u8 pad7[184];
    s32 *o1;     /* 620 */
    s32 *o0;     /* 624 */
    u8 pad8[116];
    Pl *pl;      /* 744 */
};
double fn_800F049C(double);
extern Gm *lbl_8035B65C;
extern volatile f32 lbl_80359F50;
extern volatile s8 lbl_80359F54;
extern f32 lbl_8035B99C;

static inline u8 Skip(Gm *g) { u8 a; Gx *gx; u8 b; a = 0; b = a; gx = g->gx; if (gx->busy || gx->t != *(volatile f32 *)&lbl_8035B99C) b = 1; if (b && !(g->flags & 0x10)) a = 1; return a; }
static inline El *At(Lst *l, s32 i) { return l->ok[i] ? l->e + i : 0; }
/* wQG: sb reused for lbl_80359F50 scale (FP colouring), __fmadds operand order. wSF: Skip with locals declared a, gx, b (a = 0; b = a); second element via Lst local + At() inline */
void fn_8002BDD4(Obj *o, f32 dt)
{
    f32 sa = lbl_8035B99C;
    f32 ra = sa, sb = sa, sc = sa;
    f32 tgt;
    Pl *p;
    El *e;
    f32 q;
    if (!lbl_80359F54) { lbl_80359F50 = lbl_8035B9D8; lbl_80359F54 = 1; }
    tgt = lbl_8035B9D8;
    p = o->pl;
    if (p) {
        Gm *g;
        u8 busy, skip;
        if (p->f6c4) tgt = lbl_8035B9DC;
        g = lbl_8035B65C;
        skip = Skip(g);
        if (!skip) {
            f32 d = tgt - lbl_80359F50;
            if ((f32)__fabs(d) > lbl_8035B99C)
                lbl_80359F50 = __fmadds(lbl_8035B9D8 - (f32)fn_800F049C(lbl_8035B9E0 * dt), d, lbl_80359F50);
        }
        p = o->pl;
        sb = lbl_80359F50;
        sa = p->h * sb;
        ra = p->h / p->w;
        sb = p->w * sb;
        sc = sb / (p->sc ? *p->sc : lbl_8035B99C);
    }
    if (o->t0 > lbl_8035B99C) { *o->o0 = o->v0; o->t0 -= dt; }
    else *o->o0 = 0;
    if (o->t1 > *(f32 *)&lbl_8035B99C) { *o->o1 = o->v1; o->t1 -= dt; }
    else if (ra <= lbl_8035B99C) *o->o1 = 3;
    else if (ra <= lbl_8035B9E4) *o->o1 = 2;
    else if (ra <= lbl_8035B9E8) *o->o1 = 1;
    else *o->o1 = 0;
    if (o->lst->ok[0]) e = o->lst->e; else e = 0;
    q = sa / sb;
    e->v = sc * (o->r0->x1 - o->r0->x0);
    {
        f32 v = e->v;
        Lst *l = o->lst;
        El *e2 = At(l, 1);
        e2->v = q * v;
        v = v + o->r0->x0;
        o->r1->x0 = v;
        o->r1->x1 = lbl_8035B9EC + v;
    }
    {
        f32 k = lbl_8035B9D8;
        if (lbl_8035B99C != o->ta->w) k = o->tb->w / o->ta->w;
        o->r2->x0 = o->r2->x1 - (f32)o->n * k;
        {
            f32 y = o->r2->x1 - (f32)o->n;
            o->r3->x0 = y - lbl_8035B9EC;
            o->r3->x1 = y;
        }
        o->r4->x0 = o->r4->x1 - (f32)o->n;
    }
}
}
#pragma pop
} /* namespace n8002BDD4 */

namespace n8002C150 {
#pragma push
#pragma use_lmw_stmw on

extern "C" {
struct Vec { f32 x, y, z; };
struct Y { u8 pad[16]; void *f16; u8 pad20[12]; u32 f32; };
struct X { u32 f0; u8 pad[44]; Y *f48; };
struct E { u32 f0, f4, f8; X *f12; Vec c; int f28; f32 sc; u8 pad[24 - 36 + 12]; };
struct FT { u8 pad[12]; void (*setPos)(void *, Vec *); u8 pad16[304 - 16]; void (*getPos)(void *, Vec *); };
struct G { u8 pad[20]; f32 dt; };
extern G *lbl_8035B488;
extern u8 lbl_803286D0[];
extern f32 lbl_8035B99C;
extern u32 lbl_8035B964;
extern u32 lbl_8035B9A0;
void fn_80190C98(X *);
void fn_8002C150(E *ep) {
    E *e = ep;
    u32 i = 0;
    f32 dt = lbl_8035B488->dt;
    FT *ft = (FT *)lbl_803286D0;
    for (; i < 6; i++, e = (E *)((u8 *)e + 24)) {
        if (!e->f12) continue;
        if (e->f28) {
            Vec v;
            f32 s0, ns, k, inv;
            f32 dx, dz, dy;
            if (e->f12->f48) ft->getPos(e->f12->f48->f16, &v);
            else { v.x = lbl_8035B99C; v.y = lbl_8035B99C; v.z = lbl_8035B99C; }
            *(volatile f32 *)&v.x = dx = v.x - e->c.x; *(volatile f32 *)&v.y = dy = v.y - e->c.y; *(volatile f32 *)&v.z = dz = v.z - e->c.z;
            s0 = *(volatile f32 *)&e->sc; ns = s0 - dt; k = *(volatile f32 *)&lbl_8035B9D8;
            inv = k / s0;
            v.x = dx * inv; v.y = dy * inv; v.z = dz * inv;
            e->sc = ns;
            f32 s1 = e->sc;
            *(volatile f32 *)&v.x = v.x * s1; *(volatile f32 *)&v.y = v.y * s1; *(volatile f32 *)&v.z = v.z * s1;
            f32 z0 = *(volatile f32 *)&lbl_8035B99C;
            if (s1 < z0) { v.x = z0; v.y = z0; v.z = z0; }
            v.x += e->c.x; v.y += e->c.y; v.z += e->c.z;
            {
                X *x = e->f12;
                Y *y = x->f48;
                if (y) {
                    ft->setPos(y->f16, &v);
                    y->f32 |= lbl_8035B964;
                    fn_80190C98(x);
                }
            }
            e->f12->f0 |= lbl_8035B9A0;
            if (e->sc < lbl_8035B9E0) {
                e->f28 = 0;
                e->f12->f0 &= ~0x800;
            }
        } else {
            e->f12->f0 &= ~0x800;
        }
    }
}
}
#pragma pop
} /* namespace n8002C150 */

namespace n8002C34C {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {



} /* extern "C" */

extern "C" {
extern s32 lbl_8035A02C;
void fn_80039F78(int, int);
void fn_8019AA94(int, int);
struct VCall_fn_8002C34C_0 { char vptr_pad[0x1930]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void m(int, int, int); };
struct VCall_fn_8002C34C_1 { char vptr_pad[0x1930]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void m(); };

void fn_8002C34C(s32 param_1, s32 param_2) {
    if ((*(s32 *)(param_1 + 0x288) == 0) || (*(u32 *)(param_1 + 0xcc) != 0)) {
        ((VCall_fn_8002C34C_0 *)(param_2))->m((s32)(*(u32 *)(param_1 + 0xc4)), (s32)(6), (s32)(0));
        if (*(u32 *)(param_1 + 0xc0) != 0) {
            fn_8019AA94((int)(*(u32 *)(param_1 + 0xc0)), (int)(*(u32 *)(param_1 + 0xac)));
        }
        ((VCall_fn_8002C34C_1 *)(param_2))->m();
    }
    fn_80039F78((int)(lbl_8035A02C), (int)(param_2));
}
}
} /* namespace n8002C34C */

namespace n8002C3EC {
extern "C" {
/* Functions from 0x8002C3EC to 0x8002C414, found by decomp-toolkit. */

extern f32 lbl_8035B99C;

void fn_8002C3EC(u8 *arg0, s32 arg1) {
    if (arg1 != 0) {
        *(s32 *)(arg0 + 0x284) = (u8)(*(s32 *)(arg0 + 0x284) == 0);
    }
}

void fn_8002C408(u8 *arg0) {
    *(f32 *)(arg0 + 0x260) = lbl_8035B99C;
}


}
} /* namespace n8002C3EC */

namespace n8002C414 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {



} /* extern "C" */

extern "C" {
struct VCall_fn_8002C414_0 { char vptr_pad[0x80]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void m(int); };
struct VCall_fn_8002C414_1 { char vptr_pad[0x80]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void m(int); };
struct VCall_fn_8002C414_2 { char vptr_pad[0x80]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void m(int); };
struct VCall_fn_8002C414_3 { char vptr_pad[0x80]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void m(int); };
struct VCall_fn_8002C414_4 { char vptr_pad[0x80]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void m(int); };

void fn_8002C414(u32 param_1) {
    u32 iVar1;

    iVar1 = *(u32 *)(param_1 + 0x194);
    if (iVar1 != 0) {
        ((VCall_fn_8002C414_0 *)(iVar1))->m((u32)(0));
    }
    iVar1 = *(u32 *)(param_1 + 0x198);
    if (iVar1 != 0) {
        ((VCall_fn_8002C414_1 *)(iVar1))->m((u32)(0));
    }
    iVar1 = *(u32 *)(param_1 + 0x19c);
    if (iVar1 != 0) {
        ((VCall_fn_8002C414_2 *)(iVar1))->m((u32)(0));
    }
    iVar1 = *(u32 *)(param_1 + 0x1a0);
    if (iVar1 != 0) {
        ((VCall_fn_8002C414_3 *)(iVar1))->m((u32)(0));
    }
    iVar1 = *(u32 *)(param_1 + 0x1a4);
    if (iVar1 != 0) {
        ((VCall_fn_8002C414_4 *)(iVar1))->m((u32)(0));
    }
}
}
} /* namespace n8002C414 */

namespace n8002C4DC {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {



} /* extern "C" */

extern "C" {
struct VCall_fn_8002C4DC_0 { char vptr_pad[0x80]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void m(int); };
struct VCall_fn_8002C4DC_1 { char vptr_pad[0x80]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void m(int); };
struct VCall_fn_8002C4DC_2 { char vptr_pad[0x80]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void m(int); };
struct VCall_fn_8002C4DC_3 { char vptr_pad[0x80]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void m(int); };
struct VCall_fn_8002C4DC_4 { char vptr_pad[0x80]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void m(int); };

void fn_8002C4DC(u32 param_1) {
    u32 iVar1;

    iVar1 = *(u32 *)(param_1 + 0x194);
    if (iVar1 != 0) {
        ((VCall_fn_8002C4DC_0 *)(iVar1))->m((u32)(1));
    }
    iVar1 = *(u32 *)(param_1 + 0x198);
    if (iVar1 != 0) {
        ((VCall_fn_8002C4DC_1 *)(iVar1))->m((u32)(1));
    }
    iVar1 = *(u32 *)(param_1 + 0x19c);
    if (iVar1 != 0) {
        ((VCall_fn_8002C4DC_2 *)(iVar1))->m((u32)(1));
    }
    iVar1 = *(u32 *)(param_1 + 0x1a0);
    if (iVar1 != 0) {
        ((VCall_fn_8002C4DC_3 *)(iVar1))->m((u32)(1));
    }
    iVar1 = *(u32 *)(param_1 + 0x1a4);
    if (iVar1 != 0) {
        ((VCall_fn_8002C4DC_4 *)(iVar1))->m((u32)(1));
    }
}
}
} /* namespace n8002C4DC */

extern "C" {
__declspec(section ".sdata2") f32 lbl_8035B9F0 = 6.2831855f;
__declspec(section ".sdata2") f32 lbl_8035B9F4 = 3.1415927f;
__declspec(section ".sdata2") f32 lbl_8035B9F8 = 32.0f;
__declspec(section ".sdata2") f32 lbl_8035B9FC = 0.125f;
__declspec(section ".sdata2") f32 lbl_8035BA00 = 0.75f;
__declspec(section ".sdata2") f32 lbl_8035BA04 = 0.25f;
__declspec(section ".sdata2") u32 lbl_8035BA08 = 1;
__declspec(section ".sdata2") f32 lbl_8035BA0C = 8e+01f;
__declspec(section ".sdata2") f32 lbl_8035BA10 = -25.0f;
__declspec(section ".sdata2") f32 lbl_8035BA14 = -8e+01f;
__declspec(section ".sdata2") f32 lbl_8035BA18 = 0.3f;
__declspec(section ".sdata2") f32 lbl_8035BA1C = 0.0001f;
}
namespace n8002C5A4 {
#pragma push
#pragma use_lmw_stmw on
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

typedef struct V3 { f32 x, y, z; } V3;
typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct Nd { u32 fl; u8 pad4[72 - 4]; u32 x72; u8 pad76[120 - 76]; void *x120; } Nd;
typedef struct Ob { u8 pad[48]; void *x48; } Ob;
typedef struct X744 { u8 pad[1228]; int x1228; u8 pad1232[1292 - 1232]; u32 *x1292; u8 pad1296[1716 - 1296]; u8 b1716; } X744;
typedef struct X580 { u8 pad[12]; int x12; } X580;
typedef struct O {
    u8 pad0[208]; V4 x208; u8 pad224[228 - 224]; Ob *x228; Ob *x232; Nd *x236[6]; Nd *x260[6]; Nd *x284[6]; Nd *x308[6];
    u8 pad332[580 - 332]; X580 *x580; u8 pad584[744 - 584]; X744 *x744;
} O;
extern u8 *lbl_8035B65C;
extern volatile f32 lbl_8035B9F4, lbl_8035B9F0;
extern f32 lbl_8035B99C, lbl_8035B9C8, lbl_8035B9F8, lbl_8035BA04;
extern volatile f32 lbl_8035B9FC, lbl_8035B960;
extern volatile f32 lbl_8035BA00;
extern u32 lbl_8035B9A0;
extern V3 lbl_80357E84;
extern volatile f32 lbl_80359F40;
extern volatile s8 lbl_80359F44;
extern volatile f32 lbl_80359F48;
extern volatile s8 lbl_80359F4C;
double fn_800EFDA4(double);
void fn_800FFE84(V4 *, V3 *, f32);
void fn_8010041C(V4 *, V4 *);
void fn_80107244(void *, V3 *);
void fn_801079E8(void *, V4 *, V3 *, int);
void fn_80190C98(Ob *);
void fn_8019B7E8(void *, Nd *);
void fn_80107F3C(void *, V3 *);
static inline void Upd(Ob *p, V4 *m, V3 *c) {
    if (p->x48) fn_80107244(p->x48, c);
    else { c->x = lbl_8035B99C; c->y = lbl_8035B99C; c->z = lbl_8035B99C; }
}
void fn_8002C5A4(O *o, f32 dt) {
    V4 m;
    V4 q;
    V3 c;
    V3 b;
    V3 a;
    void *mgr = *(void **)(lbl_8035B65C + 12);
    int bits;
    O *p;
    int bit;
    u32 i;
    if (!lbl_80359F44) { lbl_80359F40 = lbl_8035B99C; lbl_80359F44 = 1; }
    lbl_80359F40 += dt;
    {
        f32 t = lbl_80359F40;
        if (t > lbl_8035B9F4) lbl_80359F40 = t - lbl_8035B9F0;
    }
    fn_800FFE84(&q, &lbl_80357E84, lbl_8035B9C8 * (f32)fn_800EFDA4(lbl_80359F40));
    m.x = o->x208.x; m.y = o->x208.y; m.z = o->x208.z; m.w = o->x208.w;
    fn_8010041C(&m, &q);
    Upd(o->x228, &m, &c);
    {
        Ob *r = o->x228;
        if (r->x48) { fn_801079E8(r->x48, &m, &c, 0); fn_80190C98(r); }
    }
    Upd(o->x232, &m, &c);
    {
        Ob *r = o->x232;
        if (r->x48) { fn_801079E8(r->x48, &m, &c, 0); fn_80190C98(r); }
    }
    if (!lbl_80359F4C) { lbl_80359F48 = lbl_8035B99C; lbl_80359F4C = 1; }
    lbl_80359F48 = lbl_8035B9F8 * dt + lbl_80359F48;
    {
        f32 t = lbl_80359F48;
        if (t > lbl_8035B9F4) lbl_80359F48 = t - lbl_8035B9F0;
    }
    p = o;
    bit = 1;
    i = 0;
    bits = (int)*o->x744->x1292;
    for (; i < 6; i++, p = (O *)((u8 *)p + 4)) {
        if (i < 3 ? ((bits & bit) && !(bits & (bit << 3))) : (bits & bit)) {
            p->x236[0]->fl |= lbl_8035B9A0;
            p->x260[0]->fl |= lbl_8035B9A0;
            if (p->x284[0]->x72 == 0) fn_8019B7E8(mgr, p->x284[0]);
            if (p->x308[0]->x72 == 0) fn_8019B7E8(mgr, p->x308[0]);
            p->x284[0]->fl |= lbl_8035B9A0;
            p->x308[0]->fl |= lbl_8035B9A0;
            if (o->x744->x1228 && i == o->x744->b1716) {
                f32 s;
                p->x260[0]->fl |= lbl_8035B9A0;
                s = lbl_8035B9FC * (f32)fn_800EFDA4(lbl_80359F48) + lbl_8035B960;
                b.z = b.y = b.x = lbl_8035BA00;
                if (p->x260[0]->x120) fn_80107F3C(p->x260[0]->x120, &b);
                if (p->x308[0]->x120) fn_80107F3C(p->x308[0]->x120, &b);
                a.x = s; a.y = s; a.z = s;
                if (p->x236[0]->x120) fn_80107F3C(p->x236[0]->x120, &a);
                if (p->x284[0]->x120) fn_80107F3C(p->x284[0]->x120, &a);
            } else {
                b.x = lbl_8035BA04; b.y = lbl_8035BA04; b.z = lbl_8035BA04;
                if (p->x260[0]->x120) fn_80107F3C(p->x260[0]->x120, &b);
                if (p->x308[0]->x120) fn_80107F3C(p->x308[0]->x120, &b);
                a.z = a.y = a.x = lbl_8035B960;
                if (p->x236[0]->x120) fn_80107F3C(p->x236[0]->x120, &a);
                if (p->x284[0]->x120) fn_80107F3C(p->x284[0]->x120, &a);
            }
        } else {
            p->x236[0]->fl &= ~0x800;
            p->x260[0]->fl &= ~0x800;
            p->x284[0]->fl &= ~0x800;
            p->x308[0]->fl &= ~0x800;
        }
        bit <<= 1;
        if (o->x580->x12 != 2) {
            p->x236[0]->fl &= ~0x800;
            p->x260[0]->fl &= ~0x800;
        }
    }
}

} /* extern "C" */
#pragma pop
} /* namespace n8002C5A4 */

namespace n8002CA0C {
#pragma push
#pragma use_lmw_stmw on
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
            f32 x = cc->x; f32 y = cc->y; f32 z = cc->z; f32 w = cc->w;
            q->c.x = x * k; q->c.y = y * k; q->c.z = z * k; q->c.w = w;
        }
    }
}
}
#pragma pop
} /* namespace n8002CA0C */
#undef F
