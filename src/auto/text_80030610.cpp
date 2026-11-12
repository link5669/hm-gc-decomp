#include "common.h"

extern "C" {

}
struct Str8 { u8 b[8]; };
#define DV(n) virtual void n();
#define DV4(p) DV(p##0) DV(p##1) DV(p##2) DV(p##3)
#define DV16(p) DV4(p##a) DV4(p##b) DV4(p##c) DV4(p##d)
struct Owner1C { u8 pad[0x1930]; DV(a0) DV(a1) DV(a2) virtual void m(int, int, int); DV16(a) DV16(b) DV16(c) DV(z0) DV(z1) DV(z2) DV(z3) DV(z4) DV(z5) DV(z6) DV(z7) DV(z8) DV(z9) virtual void n(); };
struct VMgr { u8 pad[0x30]; DV4(a) DV4(b) virtual void set(int); };
struct Xo { u8 pad[0x80]; DV16(a) DV4(b) virtual void show(u8); DV16(c) DV16(d) DV(e0) DV(e1) DV(e2) DV(e3) DV(e4) DV(e5) virtual void vis(int, int); virtual void vis2(int, int); };
struct Ta { u8 pad[0xc]; Xo *fc; };
struct Wd { u8 pad[0x24]; u8 *f24; u8 pad28[0x50]; Ta *f78; };
struct Gt { u8 pad[0x14]; f32 f14; };
struct Cnt { u32 f0; s32 f4; u8 pad[8]; f32 f10; u8 pad14[0xc]; s32 f20; };
struct Gm { u8 pad[0x2c4c]; VMgr *f2c4c; u8 pad2[0x369c - 0x2c50]; s32 f369c; };
struct Ia { u8 pad[0xc]; s32 fc; };
struct Ab { u8 pad[0x4c]; s32 f4c; };
struct R0 { u8 pad[0xc0]; s32 fc0; };
struct V18 { DV16(a) DV4(b) virtual void **cur(); DV(c0) DV(c1) virtual void **get(int); };
struct Yo { u8 pad[0x18]; V18 *f18; u8 pad1c[0x4c]; int f68; };
struct P {
    u8 pad0[0x14]; void *f14; u8 pad18[4]; Owner1C *f1c; u8 pad20[0x58]; Ab *f78; u8 pad7c; u8 f7d; u8 pad7e[2];
    void *f80; void *f84; u8 pad88[0x2a4 - 0x88]; int f2a4; u8 pad2a8[0x10]; s32 f2b8; u8 pad2bc[0x34];
    DV(v0) DV(v1) DV(v2) DV(v3) DV(v4) DV(v5) virtual void v6(Owner1C *);
    u8 pad2f4[0xc]; void *f300; u8 pad304[8]; Ia *f30c; Ia *f310; s32 f314; s32 *f318; u8 pad31c[4];
    s32 f320; u8 pad324[8]; Cnt *f32c; s32 f330; u8 f334[8]; u8 f33c[8];
};
extern "C" {
extern Gt *lbl_8035B488;
extern Wd *lbl_8035B65C;
extern Cnt *lbl_8035B7E4;
extern Cnt *lbl_8035A02C;
extern Gm *lbl_8035A1DC;
extern void *lbl_8035A0A4;
extern Yo *lbl_8035B5E4;
extern struct { u8 pad[4]; void *f4; } *lbl_8035B5C4;
extern u32 lbl_80359200;
extern u8 lbl_802AFC88[];
extern char lbl_80294740[];
extern f32 lbl_8035BC50, lbl_8035BC54;
extern char lbl_8035BC58[8], lbl_8035BC68[8], lbl_8035BC70[8], lbl_8035BC78[8], lbl_8035BC80[8], lbl_8035BC88[8], lbl_8035BC90[8],
    lbl_8035BC98[8], lbl_8035BCA0[8], lbl_8035BCA8[8], lbl_8035BCB0[8];
extern Str8 lbl_80359F70;
extern u32 lbl_80359F78; extern s8 lbl_80359F7C;
extern u32 lbl_80359F80; extern s8 lbl_80359F84;
extern u32 lbl_80359F88; extern s8 lbl_80359F8C;
extern u32 lbl_80359F90; extern s8 lbl_80359F94;
void fn_8003AA34(void *, void *, int);
void fn_80039EA4(void *, f32);
void fn_80039E80(void *, int, f32);
void fn_800F6E88(void *, void *);
s32 fn_800F6CD0(void *, void *);
void fn_8023EA4C(void *);
void *fn_80207198(void *, void *, int);
Xo *fn_801AA960(void *, void *, void *);
void fn_801C2368(void *, void *, int);
void fn_8003C89C(void *, void *);
void fn_8025180C(void *, void *, char *, char *, char *, u8 *, u32);
void fn_80180600(void *, f32);
void fn_80038058(void *);
void fn_8026DA8C(void *, f32);
void fn_80268504(void *, f32);
void fn_8024EB24(void *, f32);
s32 fn_8024DAE0(void *);
s32 fn_802542E8(P *);
u32 fn_800FBB9C(void);

static inline void attach(Ta *t, Xo *x) {
    if (t->fc) t->fc->vis2(0, 1);
    x->vis(0, 1);
    fn_801C2368(t, x, 1);
}
static inline void *deref(void **r) { void *v = 0; if (r) v = *r; return v; }
static inline void *deref2(void **r) { void *v = r; if (r) v = *r; return v; }
static inline void *deref3(void **r) { return r ? *r : (void *)r; }
static inline void *deref4(void **r) { void *v = r; if (v) v = *(void **)v; return v; }
static inline void *deref5(void **r) { u32 v = (u32)r; if (v) v = *(u32 *)v; return (void *)v; }
static inline void sayc(Yo *y, char *a) {
    if (((R0 *)*y->f18->get(y->f68))->fc0) {
        void **r = y->f18->get(y->f68);
        fn_8025180C(y, deref2(r), a, lbl_8035BC90, lbl_8035BC98, lbl_802AFC88, lbl_80359200);
    }
    {
        void **r = y->f18->cur();
        fn_8025180C(y, deref4(r), a, lbl_8035BCA0, lbl_8035BC98, lbl_802AFC88, lbl_80359200);
    }
}

s32 fn_80030610(P *p) {
    char buf[8];
    char *pool = lbl_80294740;
    f32 dt = lbl_8035B488->f14;
    void *q;
    s32 res;
    u8 r;

    if (p->f32c->f4 == 0) {
        fn_8003AA34(p->f32c, *(void **)((u8 *)lbl_8035B65C->f78 + 0xc), 0);
        lbl_8035B7E4->f10 = lbl_8035BC54;
    }
    fn_80039EA4(lbl_8035A02C, dt);
    if (!lbl_80359F7C) { lbl_80359F78 = 0; lbl_80359F7C = 1; }
    fn_800F6E88(buf, &lbl_80359F70);
    *(volatile u8 *)lbl_80359F70.b = 0;
    {
        Ta *a = (*(Wd *volatile *)&lbl_8035B65C)->f78;
        if (a) {
            u8 *b = *(u8 **)((u8 *)a + 4);
            if (b) {
                u8 *c = *(u8 **)(b + 0x160);
                if (c) {
                    void *d = *(void **)(c + 0xc);
                    if (d) fn_800F6E88(&lbl_80359F70, d);
                }
            }
        }
    }
    q = lbl_8035B5C4->f4;
    if (!lbl_80359F84) { lbl_80359F80 = 0; lbl_80359F84 = 1; }
    if (!lbl_80359F8C) { lbl_80359F88 = 1; lbl_80359F8C = 1; }
    if (*p->f318 == 3) {
        *p->f318 = 0;
        fn_80039E80(lbl_8035A02C, 1, lbl_8035BC50);
        while (lbl_8035A02C->f20 != 0) {
            fn_8023EA4C(lbl_8035B488);
            fn_80039EA4(lbl_8035A02C, lbl_8035B488->f14);
            p->v6(p->f1c);
            lbl_8035A1DC->f2c4c->set(1);
        }
        p->f320 = 1;
    }
    if (fn_800F6CD0(&lbl_80359F70, lbl_8035BC68) == 0 || fn_800F6CD0(buf, lbl_8035BC68) != 0) {
        if (fn_800F6CD0(&lbl_80359F70, pool + 0x1c)) {
            Wd *w;
            Ta *t;
            fn_80207198(lbl_8035B65C->f24 + 0x3e0, pool + 0x28, 0);
            *p->f318 = 1;
            w = lbl_8035B65C;
            t = w->f78;
            if (t) {
                Xo *x = fn_801AA960(*(void **)(w->f24 + 0x33b0), lbl_8035BC70, lbl_8035BC58);
                if (x) attach(t, x);
            }
        } else if (fn_800F6CD0(&lbl_80359F70, pool + 0x34)) {
            void *r = fn_80207198(lbl_8035B65C->f24 + 0x3e0, pool + 0x28, 0);
            fn_8003C89C(lbl_8035A0A4, *(void **)((u8 *)r + 0xc));
        } else if (fn_800F6CD0(&lbl_80359F70, pool + 0x40)) {
            if (p->f310->fc == 1) {
                Yo *y = lbl_8035B5E4;
                Xo *x;
                p->f314 = p->f314 % 2 + 1;
                x = fn_801AA960(*(void **)(lbl_8035B65C->f24 + 0x33b0), lbl_8035BC78, &lbl_80359F70);
                x->show(p->f314 == 1);
                x = fn_801AA960(*(void **)(lbl_8035B65C->f24 + 0x33b0), lbl_8035BC80, &lbl_80359F70);
                x->show(p->f314 == 2);
                p->f310->fc = 0;
                switch (p->f314) {
                case 1:
                    sayc(y, lbl_8035BC88);
                    break;
                case 2:
                    sayc(y, lbl_8035BCA8);
                    break;
                }
            }
        }
    }
    fn_80180600(p->f14, lbl_8035B488->f14);
    p->f7d = p->f2b8 == 0;
    if (p->f7d) fn_80038058(p->f300);
    fn_8026DA8C(p->f80, dt);
    fn_80268504(p->f84, dt);
    fn_8024EB24(q, dt);
    if (p->f330 && !fn_8024DAE0(q)) {
        Wd *w;
        Ta *t;
        p->f330 = 0;
        w = lbl_8035B65C;
        t = w->f78;
        if (t) {
            Xo *x = fn_801AA960(*(void **)(w->f24 + 0x33b0), p->f334, p->f33c);
            if (x) attach(t, x);
        }
    }
    p->f1c->m(p->f2a4, 7, 0);
    p->f1c->n();
    if (p->f30c->fc == -1) { p->f320 = 1; p->f30c->fc = 1; }
    r = 0;
    if (fn_802542E8(p) && p->f78->f4c == 0) r = 1;
    res = r;
    if (p->f320) {
        res = 0;
    } else if (fn_800F6CD0(lbl_8035BCB0, &lbl_80359F70) && p->f2b8 == 0) {
        p->f320 = 1;
    }
    if (lbl_8035A1DC->f369c && p->f330 == 0) {
        if (!lbl_80359F94) { *(volatile u32 *)&lbl_80359F90 = fn_800FBB9C(); *(volatile s8 *)&lbl_80359F94 = 1; }
        {
            u32 now = fn_800FBB9C();
            if (lbl_80359F90 + 10000 < now) p->f320 = 1;
        }
    }
    if (res == 0) lbl_8035A1DC->f2c4c->set(1);
    return res;
}

} /* extern "C" */
