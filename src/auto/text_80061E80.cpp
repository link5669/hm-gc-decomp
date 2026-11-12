// fn_80061E80: main menu/attract state loop (states 2 -> 1). Register-equivalent (regequiv.txt): all instructions
// match, register coloring differs; volatile st init + volatile lbl_8035A0A4 read fixed the fn_8003C674 arg schedule (wNV).
// Its two local objects are C800315E4 and C80034A10 (dtors renamed from dtor_80031570 / dtor_8003493C for DESTROYLOCAL).
#include "common.h"

struct C800315E4 {
    u8 p0[0x68];
    u32 f68;
    u32 f6c;
    u8 p70[0x1c];
    u32 f8c;
    u8 p90[0x340 - 0x90];
    C800315E4();
    ~C800315E4();
};
struct C80034A10 {
    u8 p0[0x68];
    u32 f68;
    u32 f6c;
    u8 p70[0x1c];
    u32 f8c;
    u8 p90[0x2c4 - 0x90];
    u32 f2c4;
    u8 p2c8[0xc38 - 0x2c8];
    C80034A10();
    ~C80034A10();
};
struct C801829F8 {
    u8 p[0x78];
    C801829F8();
};
struct V2c50;
struct V2c44;
struct V2c34 {
    u8 pad[0x8];
    u32 f2c3c;
    u8 pad2[4];
    V2c44 *f2c44;
    u8 pad3[4];
    void *f2c4c;
    V2c50 *f2c50;
    u8 pad4[0x30 - 0x20];
    virtual void dv8();
    virtual void dvc();
    virtual void dv10();
    virtual void dv14();
    virtual void dv18();
    virtual void dv1c();
    virtual int v20();
};
struct V2c44 {
    virtual void d08(); virtual void d0c(); virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24(); virtual void d28(); virtual void d2c(); virtual void d30(); virtual void d34();
    virtual void d38(); virtual void d3c(); virtual void d40(); virtual void d44(); virtual void d48(); virtual void d4c();
    virtual void d50(); virtual void d54(); virtual void d58(); virtual void d5c(); virtual void d60(); virtual void d64();
    virtual void d68(); virtual void d6c(); virtual void d70();
    virtual void *v74();
};
struct V0_30 {
    u8 pad[0x30];
    virtual void d08(); virtual void d0c(); virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24();
    virtual void v28(int);
};
struct V2c50 {
    V0_30 *f0;
    u8 pad[0x1930 - 4];
    virtual void d08(); virtual void d0c(); virtual void d10();
    virtual void v14(u32, int, int);
    virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24(); virtual void d28(); virtual void d2c(); virtual void d30(); virtual void d34();
    virtual void d38(); virtual void d3c(); virtual void d40(); virtual void d44(); virtual void d48(); virtual void d4c();
    virtual void d50(); virtual void d54(); virtual void d58(); virtual void d5c(); virtual void d60(); virtual void d64();
    virtual void d68(); virtual void d6c(); virtual void d70(); virtual void d74(); virtual void d78(); virtual void d7c();
    virtual void d80(); virtual void d84(); virtual void d88(); virtual void d8c(); virtual void d90(); virtual void d94();
    virtual void d98(); virtual void d9c(); virtual void da0(); virtual void da4(); virtual void da8(); virtual void dac();
    virtual void db0(); virtual void db4(); virtual void db8(); virtual void dbc(); virtual void dc0(); virtual void dc4();
    virtual void dc8(); virtual void dcc(); virtual void dd0(); virtual void dd4(); virtual void dd8(); virtual void ddc();
    virtual void de0(); virtual void de4(); virtual void de8(); virtual void dec(); virtual void df0(); virtual void df4();
    virtual void df8(); virtual void dfc();
    virtual void v100();
};
struct V50 {
    u8 pad[0x50];
    virtual void d08(); virtual void d0c(); virtual void d10(); virtual void d14();
    virtual void v18(V2c50 *);
};
struct V3410 {
    virtual void d08(); virtual void d0c(); virtual void d10(); virtual void d14(); virtual void d18();
    virtual void v1c();
};
struct VInner {
    virtual void d08(); virtual void d0c(); virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24(); virtual void d28(); virtual void d2c(); virtual void d30();
    virtual u32 v34();
    virtual void v38(u32);
};
struct VSnd {
    u8 pad0[4];
    struct { VInner *f0; } *f4;
    u8 pad[0x58 - 8];
    virtual void d08(); virtual void d0c(); virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24(); virtual void d28(); virtual void d2c(); virtual void d30(); virtual void d34();
    virtual void d38(); virtual void d3c(); virtual void d40(); virtual void d44(); virtual void d48(); virtual void d4c();
    virtual void d50(); virtual void d54(); virtual void d58();
    virtual void v5c(int);
    virtual void v60(int, f32);
    virtual void d64();
    virtual void v68(f32);
};
struct V1c {
    u8 pad[0x1c];
    virtual void d08(); virtual void d0c(); virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20();
    virtual void v24(int);
};
struct V24 {
    u8 pad[0x24];
    virtual void d08(); virtual void d0c(); virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24();
    virtual void *v28(int);
};
struct B7BC { u8 pad[0x14]; V24 *f14; };
struct VD0 {
    u8 pad0[0xc0];
    s32 fc0;
    u8 pad[0xd0 - 0xc4];
    virtual void d08(); virtual void d0c(); virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24();
    virtual void v28(int);
};
struct V18 {
    virtual void d08(); virtual void d0c(); virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24(); virtual void d28(); virtual void d2c(); virtual void d30(); virtual void d34();
    virtual void d38(); virtual void d3c(); virtual void d40(); virtual void d44(); virtual void d48(); virtual void d4c();
    virtual void d50(); virtual void d54(); virtual void d58(); virtual void d5c(); virtual void d60();
    virtual VD0 **v64(void *);
};
struct B5E4 { u8 pad[0x18]; V18 *f18; u8 pad2[0x68 - 0x1c]; void *f68; };
struct VC0 {
    u8 pad[0xc0];
    virtual void d08(); virtual void d0c(); virtual void d10();
    virtual void v14(void *, int);
    virtual void d18();
    virtual void *v1c(void *);
};
struct V100 {
    u8 pad[0x100];
    virtual void d08(); virtual void d0c(); virtual void d10();
    virtual void v14(void *, f32);
};
struct Tim { u8 pad[0x14]; f32 f14; };
struct Fade { u8 pad[0x10]; u32 f10; u8 pad2[8]; s32 f1c; };
struct Node { u8 pad[0x40]; u16 f40; u8 pad2[6]; u16 f48; };
struct R351c { u8 pad[0x1c0]; s32 f1c0; };
struct B460 { u8 pad[8]; u8 *f8; };

struct P {
    u8 pad0[0x2c34];
    V2c34 f2c34;
    u8 pad2c68[0x33b8 - 0x2c68];
    s32 f33b8;
    u8 pad33bc[0x33cc - 0x33bc];
    void *f33cc;
    C801829F8 *f33d0;
    void *f33d4;
    C801829F8 *f33d8;
    u8 pad33dc[4];
    void *f33e0;
    u8 pad33e4[4];
    void *f33e8;
    u8 pad33ec[4];
    u32 f33f0;
    u8 pad33f4[0x3404 - 0x33f4];
    s32 f3404;
    s32 f3408;
    u8 pad340c[4];
    V3410 f3410;
    u8 pad3414[0x34e0 - 0x3414];
    u32 f34e0;
    u8 pad34e4[4];
    u32 f34e8;
    u8 pad34ec[0x351c - 0x34ec];
    R351c *f351c;
    u8 pad3520[0x3530 - 0x3520];
    u8 f3530[0x20];
    u8 f3550[0x38];
    s32 f3588;
    u8 pad358c[0x3690 - 0x358c];
    u32 f3690;
    u8 pad3694[0x36cc - 0x3694];
    void *f36cc;
    void *f36d0;
    u8 pad36d4[0x370c - 0x36d4];
    Node *f370c;
    VSnd *f3710;
    VSnd *f3714;
};

extern "C" {
extern char lbl_80297350[];
extern void *lbl_8035B5E4;
extern VC0 *lbl_8035B684;
extern void *lbl_8035A1D8;
extern u32 lbl_8035B65C;
extern void *lbl_8035A0A4;
extern Fade *lbl_8035A01C;
extern B7BC *lbl_8035B7BC;
extern void *lbl_8035B79C;
extern Tim *lbl_8035B488;
extern V100 *lbl_8035B7C8;
extern void *lbl_8035B7C4;
extern u32 *lbl_8035B418;
extern B460 *lbl_8035B460;
extern char lbl_8035E5A8[4], lbl_8035E5B0[4], lbl_8035E5B8[4], lbl_8035E658[4], lbl_8035E660[4], lbl_8035E668[4];
extern char lbl_8035E638[4], lbl_8035E670[4], lbl_8035E5C8[4], lbl_8035E5D0[4], lbl_8035E678[4], lbl_8035E680[4];
extern char lbl_8035E68C[4], lbl_8035E698[4];
extern f32 lbl_8035E688, lbl_8035E694;

void fn_80030E98(C800315E4 *, P *, void *, void *, void *);
void fn_80251428(void *, char *);
void fn_80251488(void *, char *);
int fn_8003AEEC(void *);
int fn_80030610(C800315E4 *);
void fn_80031434(C800315E4 *);
void fn_8003AD38(void *, const char *, s32, s32, s32);
void fn_8003BA20(void *, void *);
void fn_8003B5F8(void *, const char *);
void fn_80216044(void *, const char *);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_8012ACAC(void *, void *, const char *, int, int);
void fn_8018182C(C801829F8 *, u8 *, const char *, int);
void fn_80215FDC(void *);
void fn_80033C38(C80034A10 *, P *, void *, void *, void *);
void fn_8003B87C(void *, int);
int fn_80032CC4(C80034A10 *);
void __ct__9C80253F24Fiiii(u32, char *, int, int, int);
void fn_800338E8(C80034A10 *);
int fn_8003C674(void *, const char *, s32 **);
s32 fn_8003C8E4(void *);
void fn_8003D130(void *, s32);
void fn_80039988(Fade *);
f32 fn_80268A70(void *);
void *fn_800F8274(void *, void *);
V1c *fn_8026D254(void *, void *);
void fn_801FEC18(VSnd *, void *, u32, u32, int);
s32 fn_80253664(void *, int);
void fn_8023EA4C(Tim *);
void fn_80038058(void *);
void fn_802516A4(void *, int);
void fn_800396C0(Fade *);
void fn_800F6E88(char *, char *);
Node *fn_801AAF74(Node *, u32);
void *fn_801AAF94(Node *, u32, u32);
V50 *fn_800F9398(void *, void *);
void fn_8003E5F4(void *);
void fn_802119D8(void *);
void fn_800315E4(C800315E4 *);
}

inline C800315E4::C800315E4() { fn_800315E4(this); }

static inline void Check(void *p, s32 code) { if (!p) fn_800604C4(code, 0, 0, 0); }

static inline void Frame(P *p, V50 *a, V50 *b) {
    fn_802516A4(lbl_8035B5E4, 1);
    p->f2c34.f2c50->v14(lbl_8035A01C->f10, 7, 0);
    a->v18(p->f2c34.f2c50);
    b->v18(p->f2c34.f2c50);
    p->f2c34.f2c50->v100();
    p->f2c34.f2c50->f0->v28(1);
}

extern "C" void fn_80061E80(P *p) {
    char *s = lbl_80297350;
    C800315E4 a;
    u8 *tbl = (u8 *)p + 0x3040;
    p->f33f0 = 0;
    int done = 0;
    while (!done) {
        void *g = lbl_8035B5E4;
        p->f3408 = p->f3404;
        switch (p->f3404) {
        case 2:
            p->f3404 = 1;
            fn_80030E98(&a, p, p->f33e0, p->f36cc, p->f36d0);
            a.f68 = p->f34e0;
            a.f6c = p->f34e8;
            fn_80251428(g, lbl_8035E5A8);
            fn_80251428(g, lbl_8035E5B0);
            fn_80251428(g, lbl_8035E5B8);
            while (!fn_8003AEEC(p->f3530)) {
            }
            while (fn_80030610(&a) && !(p->f2c34.f2c3c & 8) && p->f2c34.v20()) {
                if (a.f8c & 2) {
                    done = 1;
                    break;
                }
            }
            fn_80031434(&a);
            break;
        case 1: {
            if (p->f351c->f1c0 == 1) {
                fn_8003AD38(p->f3530, s + 0x280, 1, 0, 1);
                p->f351c->f1c0 = 0;
            }
            u8 tmp[8];
            lbl_8035B684->v14(tmp, -1);
            fn_8003BA20(p->f3550, lbl_8035B684->v1c(tmp));
            p->f3588 = 1;
            fn_8003B5F8(p->f3550, s + 0x28c);
            fn_8003B5F8(p->f3550, lbl_8035E658);
            if (p->f33b8 == 0) {
                fn_80216044(p->f33e0, s + 0x298);
                Check(lbl_8035A1D8, -2);
                fn_800F7EC0(lbl_8035A1D8);
                p->f33d0 = new C801829F8;
                fn_800F7E98();
                Check(p->f33d0, -4);
                Check(lbl_8035A1D8, -2);
                fn_800F7EC0(lbl_8035A1D8);
                p->f33d8 = new C801829F8;
                fn_800F7E98();
                Check(p->f33d8, -4);
                p->f33d4 = p->f2c34.f2c44->v74();
                p->f33cc = p->f2c34.f2c44->v74();
                fn_8012ACAC(p->f33d4, p->f2c34.f2c4c, lbl_8035E660, 1, 0);
                fn_8012ACAC(p->f33cc, p->f2c34.f2c4c, lbl_8035E668, 1, 0);
                fn_8018182C(p->f33d0, tbl, lbl_8035E668, 1);
                fn_8018182C(p->f33d8, tbl, lbl_8035E660, 1);
                fn_80215FDC(p->f33e0);
                p->f33b8 = 1;
            }
            fn_8003B5F8(p->f3550, s + 0x2a4);
            C80034A10 b;
            fn_8003B5F8(p->f3550, s + 0x2b4);
            fn_80033C38(&b, p, p->f33e0, p->f36cc, p->f36d0);
            p->f33f0 = lbl_8035B65C;
            fn_8003B5F8(p->f3550, s + 0x2d0);
            b.f68 = p->f34e0;
            fn_8003B5F8(p->f3550, s + 0x2e8);
            b.f6c = p->f34e8;
            b.f2c4 = p->f3690;
            fn_80251488(g, lbl_8035E5A8);
            fn_80251488(g, lbl_8035E5B0);
            fn_80251488(g, lbl_8035E5B8);
            fn_80251488(g, lbl_8035E638);
            fn_80251488(g, lbl_8035E670);
            fn_80251488(g, lbl_8035E5C8);
            fn_80251488(g, lbl_8035E5D0);
            fn_8003B5F8(p->f3550, s + 0x308);
            p->f3588 = 0;
            fn_8003B87C(p->f3550, 1);
            while (fn_80032CC4(&b) && !(p->f2c34.f2c3c & 8) && p->f2c34.v20()) {
                if ((b.f8c & 2) || (p->f2c34.f2c3c & 8)) {
                    done = 1;
                    break;
                }
            }
            __ct__9C80253F24Fiiii(lbl_8035B65C, s + 0x324, 0, 0, 0);
            {
                B5E4 *h = (B5E4 *)lbl_8035B5E4;
                VD0 *d = *h->f18->v64(h->f68);
                if (d->fc0 != 0) d->v28(1);
            }
            p->f33f0 = 0;
            fn_800338E8(&b);
            s32 *st; *(s32 * volatile *)&st = 0;
            if (fn_8003C674(*(void * volatile *)&lbl_8035A0A4, s + 0x330, &st) == 0) {
                *st = 0;
            } else if (*st == 2) {
                V1c *e2;
                u32 i1;
                void *opt;
                V1c *e1;
                s32 mode;
                void *g2;
                V50 *w1;
                char name[8];
                u32 i;
                void *found;
                V50 *w2;
                bool on;
                u32 i2;
                Node *n;
                bool quit;
                void *bank;
                f32 vol;
                *st = 1;
                mode = fn_8003C8E4(lbl_8035A0A4);
                fn_8003D130(lbl_8035A0A4, 0);
                fn_8003AD38(p->f3530, s + 0x33c, 1, 0, 1);
                g2 = lbl_8035B5E4;
                fn_80251428(g2, lbl_8035E5D0);
                fn_80251428(g2, lbl_8035E670);
                fn_80039988(lbl_8035A01C);
                bank = lbl_8035B7BC->f14->v28(0);
                vol = fn_80268A70(lbl_8035B79C);
                p->f3710 = (VSnd *)fn_800F8274(bank, lbl_8035E678);
                e1 = fn_8026D254(lbl_8035B7BC, lbl_8035E680);
                e1->v24(0);
                i1 = p->f3710->f4->f0->v34();
                p->f3710->v60(0, vol);
                p->f3710->v68(lbl_8035E688);
                p->f3714 = (VSnd *)fn_800F8274(bank, s + 0x348);
                e2 = fn_8026D254(lbl_8035B7BC, lbl_8035E68C);
                e2->v24(0);
                i2 = p->f3714->f4->f0->v34();
                p->f3714->v60(0, vol);
                p->f3714->v68(lbl_8035E694);
                fn_801FEC18(p->f3710, e1, i1, i2, 0);
                fn_801FEC18(p->f3714, e2, i2, i1, 0);
                p->f3410.v1c();
                opt = fn_800F8274(lbl_8035B5E4, lbl_8035E5C8);
                on = fn_80253664(opt, 0x4c) == 1;
                quit = 0;
                while (lbl_8035A01C->f1c == 0 && !quit) {
                    fn_8023EA4C(lbl_8035B488);
                    fn_80038058(&p->f3410);
                    fn_802516A4(lbl_8035B5E4, 1);
                    lbl_8035B7C8->v14(lbl_8035B7C4, lbl_8035B488->f14);
                    fn_800396C0(lbl_8035A01C);
                    if (on) {
                        if (fn_80253664(opt, 0x4c) == 0) on = 0;
                    } else {
                        if (fn_80253664(opt, 0x4c) == 1) quit = 1;
                    }
                }
                p->f3710->v5c(0);
                p->f3710->f4->f0->v38(i1);
                p->f3710 = 0;
                p->f3714->v5c(0);
                p->f3714->f4->f0->v38(i2);
                p->f3714 = 0;
                switch (mode) {
                case 1: fn_800F6E88(name, s + 0x354); break;
                case 2: fn_800F6E88(name, s + 0x360); break;
                case 0:
                default: fn_800F6E88(name, s + 0x36c); break;
                }
                n = p->f370c;
                found = 0;
                for (i = 0; i < n->f40; i++) {
                    for (u32 j = 0; j < fn_801AAF74(n, i)->f48 && !found; j++) {
                        u32 k = *lbl_8035B418;
                        found = fn_800F8274(fn_801AAF94(fn_801AAF74(n, i), j, k), name);
                    }
                    if (found) break;
                }
                if (!found) {
                    for (i = 0; i < n->f48 && !found; i++)
                        found = fn_800F8274(fn_801AAF94(n, i, *lbl_8035B418), name);
                }
                w1 = fn_800F9398(lbl_8035B460->f8 + 0x18, s + 0x378);
                w2 = fn_800F9398(lbl_8035B460->f8 + 0x54, lbl_8035E698);
                *(void **)((u8 *)w2 + 0x58) = found;
                fn_8003E5F4(lbl_8035A0A4);
                if (fn_80253664(opt, 0x4c) == 1) {
                    while (fn_80253664(opt, 0x4c) == 1) Frame(p, w1, w2);
                }
                while (fn_80253664(opt, 0x4c) == 0) Frame(p, w1, w2);
                fn_80251488(g2, lbl_8035E670);
                fn_80251488(g2, lbl_8035E5D0);
            }
            break;
        }
        default:
            done = 1;
            break;
        }
        fn_802119D8(p->f33e8);
    }
}
