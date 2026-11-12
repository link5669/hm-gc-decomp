// One translation unit: fn_80077010, fn_80077944, fn_80078308 (GC/2.0p1 + lmw). fn_80077010 and fn_80078308
// share the int->float constant lbl_8035F630, which this unit owns as its compiler literal (.sdata2).
// fn_80077010 is register-equivalent, fn_80078308 schedule-equivalent. The string pool lbl_80298060 belongs
// to a larger original TU (80072.. units), so it is addressed through an extern base (opt_propagation off).
#include "common.h"

// global scope: its constructor is the real symbol __ct__9C801883E0Fv
struct C801883E0 { u8 pad[0xcc]; C801883E0(); };

namespace n80077010 {
extern "C" {
}
struct Var { u32 a, b; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void *get(int); };
struct VP { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void play(char *, int, int, int, int); };
struct B { u32 a, b; };
struct K { u8 pad[192]; virtual void a0(); virtual void a1(); virtual void a2(); virtual void get(B *, int); };
struct V3 { f32 x, y, z; };
struct N { u8 pad[0x98]; u32 f98; };
struct Z { u8 pad[0x10]; void *f10; u8 pad14[0xc]; u32 f20; };
struct FT { u8 pad[0xc]; void (*fc)(void *, V3 *); u8 pad10[0x130 - 0x10]; void (*f130)(void *, V3 *); };
struct R { u8 pad[0x168]; u8 f168[0x18]; u8 f180[1]; };
struct M { u8 pad[0x2c50]; R **f2c50; };
struct T {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(int, int, int, int, V3 *);
    u8 pad4[8]; void *fc; void *f10; u8 pad14[0x1a8 - 0x14]; f32 f1a8; f32 f1ac; u8 pad1b0[0x434 - 0x1b0]; VP *f434; u8 pad438[8]; N *f440; N *f444; u8 pad448[0x458 - 0x448]; Z *f458;
    u8 pad45c[0x4cc - 0x45c]; int f4cc; u8 pad4d0[0x50c - 0x4d0]; u32 *f50c; u8 pad510[8]; void *f518; void *f51c; void *f520; void *f524; void *f528; void *f52c; void *f530; void *f534;
    void *f538; int *f53c; int *f540; int *f544; int *f548; void *f54c; f32 f550; f32 f554; f32 *f558; void *f55c; u8 pad560[0x61c - 0x560]; void *f61c; u8 pad620[0x62c - 0x620]; u32 *f62c;
    u8 pad630[0x674 - 0x630]; void *f674; u8 pad678[4]; void *f67c; void *f680; int f684; void *f688; u8 pad68c[4]; void *f690; u8 pad694[4]; void *f698; void *f69c; f32 f6a0; void *f6a4; void *f6a8;
    u8 pad6ac[0x6b8 - 0x6ac]; void *f6b8; void *f6bc; f32 f6c0; u8 pad6c4[0x6d4 - 0x6c4]; void *f6d4; };
struct G { u8 pad[0x24]; u8 *f24; u8 pad28[0x90 - 0x28]; u8 f90[1]; };
struct W { u8 pad[0xc]; void *fc; };
extern "C" {
extern char lbl_80298060[];
extern FT lbl_803286D0;
extern void *lbl_80359F2C;
extern void *lbl_8035A0A4;
extern u8 *lbl_8035A1DC;
extern int lbl_8035A238, lbl_8035A24C, lbl_8035A250, lbl_8035A254, lbl_8035A258, lbl_8035A25C;
extern void *lbl_8035B478;
extern G *lbl_8035B65C;
extern K *lbl_8035B684;
extern int lbl_8035B6E8, lbl_8035B6EC;
extern W *lbl_8035B754;
extern u32 lbl_8035F3E8, lbl_8035F3F0, lbl_8035F400;
extern f32 lbl_8035F3EC, lbl_8035F548, lbl_8035F60C;
extern char lbl_8035F3F4[1], lbl_8035F470[6], lbl_8035F578[8], lbl_8035F5CC[8], lbl_8035F5F4[8], lbl_8035F5FC[8], lbl_8035F604[8], lbl_8035F610[8], lbl_8035F618[8], lbl_8035F620[8], lbl_8035F628[7];
Var *fn_80207198(void *, char *, int);
void *fn_8023D13C(T *, char *, int);
void fn_8002FD10(K *, B *);
int fn_800F6CD0(const void *, const void *);
void fn_8003D130(void *, int);
void *fn_800F8274(void *, char *);
Var *fn_80110AA4(void *, char *);
Var **fn_8010FFD0(void *, char *, int);
void *fn_80110030(void *, char *, int);
Var *fn_8010FFFC(void *, void *, char *, int);
void *fn_80110444(void *, char *, int);
Var **fn_8010FEDC(void *, void *, char *, int);
void *fn_800F9398(void *, char *);
void *fn_800F9788(void *, char *, char *);
int fn_80239024(T *);
void fn_8002C5A4(void *, f32);
static inline void *Look(R *r, char *grp, char *name) {
    if (!grp || !*grp) return fn_800F9398(r->f168, name);
    return fn_800F9788(r->f180, grp, name);
}
static inline int IsA(B *b8, B *b10) { return fn_800F6CD0(b8, lbl_8035F3F4) || (fn_800F6CD0(b8, lbl_8035F470) && fn_800F6CD0(b10, lbl_8035F578)); }
static inline bool IsB(B *b8) { return fn_800F6CD0(b8, lbl_8035F3F4) || fn_800F6CD0(b8, lbl_8035F470); }
#pragma opt_propagation off
int fn_80077010(T *t) {
    char *str = lbl_80298060;
    B b10, b8;
    void *x;
    void *g;
    int res;
    void *o;
    int f;
    bool h;
    V3 m;
    V3 v;
    t->f690 = fn_80207198(lbl_8035B65C->f24 + 0x3e0, lbl_8035F5F4, 0)->get(0);
    t->f688 = fn_8023D13C(t, lbl_8035F5FC, 1);
    t->f538 = fn_8023D13C(t, (str + 396), 1);
    t->f53c = (int *)fn_8023D13C(t, (str + 408), 1);
    lbl_8035B684->get(&b10, -1);
    fn_8002FD10(lbl_8035B684, &b8);
    if (fn_800F6CD0(&b10, lbl_8035F470)) fn_8003D130(lbl_8035A0A4, 0);
    o = fn_800F8274(lbl_8035B478, lbl_8035F604);
    t->f540 = (int *)fn_80110AA4(o, (str + 420))->get(0);
    f = (u8)IsA(&b8, &b10);
    if (f) {
        if (t->f53c) *t->f540 = *t->f53c;
        else *t->f540 = 1;
    }
    t->f558 = (f32 *)fn_8023D13C(t, (str + 432), 1);
    t->f55c = fn_8023D13C(t, (str + 448), 1);
    if (t->f558) t->f554 = *t->f558;
    else t->f554 = lbl_8035F3EC;
    t->f550 = t->f554;
    t->f50c = (u32 *)fn_80207198(lbl_8035A1DC + 0x3e0, (str + 468), 0)->get(0);
    if (t->f62c) {
        if (*t->f50c == 0x40) *t->f62c |= lbl_8035F3E8;
        else *t->f62c &= ~0x800;
    }
    if (*(int *)(lbl_8035A1DC + 0x36ac)) {
        Var **q = fn_8010FFD0(lbl_8035B65C->f90, (str + 480), 0);
        if (q) *t->f50c = *(u32 *)((u8 *)*q + 0xc);
        q = fn_8010FFD0(lbl_8035B65C->f90, (str + 508), 0);
        if (q) {
            t->f1a8 = t->f1a8 + ((f32)*(int *)((u8 *)*q + 0xc) - t->f1a8);
            *t->f548 = (int)t->f1a8;
        }
    }
    t->f698 = fn_8023D13C(t, (str + 520), 1);
    t->f6a8 = fn_8023D13C(t, (str + 532), 1);
    t->f69c = fn_8023D13C(t, (str + 544), 1);
    t->f6d4 = fn_80110030(lbl_8035B65C->f90, (str + 556), 0);
    t->f6b8 = fn_8010FFFC(t->fc, t->f10, (str + 580), 1);
    t->f6bc = fn_8010FFFC(t->fc, t->f10, (str + 596), 1)->get(0);
    t->f524 = fn_8010FFFC(t->fc, t->f10, (str + 612), 1)->get(0);
    t->f6a4 = fn_8023D13C(t, (str + 624), 1);
    t->f6a0 = *(f32 *)fn_8023D13C(t, (str + 644), 1);
    {
        f32 *p = (f32 *)fn_8023D13C(t, (str + 664), 0);
        if (p) t->f6c0 = *p;
        else t->f6c0 = lbl_8035F60C;
    }
    x = lbl_8035B754->fc;
    g = fn_80110444(x, lbl_8035F610, 0);
    t->f518 = (*fn_8010FEDC(x, g, (str + 684), 1))->get(0);
    t->f51c = (*fn_8010FEDC(x, g, (str + 704), 1))->get(0);
    t->f520 = (*fn_8010FEDC(x, g, (str + 724), 1))->get(0);
    t->f528 = (*fn_8010FEDC(x, g, (str + 744), 1))->get(0);
    t->f61c = (*fn_8010FEDC(x, g, (str + 760), 1))->get(0);
    t->f530 = (*fn_8010FEDC(x, g, (str + 780), 1))->get(0);
    t->f534 = (*fn_8010FEDC(x, g, (str + 804), 1))->get(0);
    x = lbl_8035B754->fc;
    t->f52c = (*fn_8010FEDC(x, fn_80110444(x, lbl_8035F618, 0), (str + 824), 1))->get(0);
    {
        char *a = (char *)fn_8023D13C(t, (str + 840), 0);
        char *b = (char *)fn_8023D13C(t, (str + 864), 0);
        if (a && b) {
            R **rr = (*(M **)lbl_8035B684)->f2c50;
            t->f674 = Look(*rr, b, a);
            t->f67c = Look(*rr, lbl_8035F620, (str + 900));
        }
    }
    t->f680 = fn_8023D13C(t, (str + 912), 1);
    t->f54c = fn_8010FFFC(t->fc, t->f10, (str + 932), 1);
    res = fn_80239024(t);
    t->f544 = (int *)fn_80110AA4(o, lbl_8035F628)->get(0);
    if (*t->f544 <= 0) *t->f544 = 1;
    t->f548 = (int *)fn_80110AA4(o, (str + 956))->get(0);
    if (f) *t->f548 = (int)t->f1a8;
    t->f1a8 = (f32)*t->f548;
    h = IsB(&b8);
    if (h) *t->f544 = (int)t->f1a8;
    t->f1ac = (f32)*t->f544;
    lbl_8035A238 = 0;
    t->f4cc = 0;
    if (t->f4cc == 0) {
        if (t->f440) {
            t->f434->play(lbl_8035F5CC, 0, 0, 0, 0);
            t->f440->f98 |= lbl_8035F400;
            t->f440 = 0;
        }
        if (t->f444) {
            t->f444->f98 |= lbl_8035F400;
            t->f444 = 0;
        }
    }
    v.x = lbl_8035F548;
    v.y = lbl_8035F548;
    v.z = lbl_8035F548;
    t->v14(0, 0, 0, 0, &v);
    lbl_803286D0.f130(t->f458->f10, &m);
    m.z = lbl_8035F3EC;
    {
        Z *z = t->f458;
        lbl_803286D0.fc(z->f10, &m);
        z->f20 |= lbl_8035F3F0;
    }
    fn_8002C5A4(lbl_80359F2C, lbl_8035F3EC);
    lbl_8035B6EC = 0;
    lbl_8035B6E8 = 0;
    if (h) {
        lbl_8035A24C = 0;
        lbl_8035A250 = 0;
        lbl_8035A254 = 0;
        lbl_8035A258 = 0;
        lbl_8035A25C = 0;
    }
    t->f684 = lbl_8035A254 == 0;
    return res;
}
}
#pragma opt_propagation reset
} // namespace n80077010

namespace n80077944 {

extern "C" {
}
#define F(T, p, off) (*(T *)((u8 *)(p) + (off)))
struct B { u32 a, b; };
struct K { u8 pad[192]; virtual void a0(); virtual void a1(); virtual void a2(); virtual void get(B *, int); };
struct V3 { f32 x, y, z; };
struct Q4 { f32 a, b, c, d; };
struct C4 { u8 r, g, b, a; };
struct Z { u8 pad[0x10]; void *f10; u8 pad14[0xc]; u32 f20; };
struct N { u32 f0; u8 pad4[0x30 - 4]; Z *f30; u8 pad34[0x48 - 0x34]; void *f48; u8 pad4c[0x78 - 0x4c]; f32 *f78; };
struct FT { u8 pad[0xc]; void (*fc)(void *, V3 *); u8 pad10[0x130 - 0x10]; void (*f130)(void *, V3 *); };
struct DB { u8 names[0x18]; u8 groups[0x18]; };
struct W90 { u8 pad[0x90]; DB db; };
struct WF0 { u8 pad[0xf0]; DB db; };
struct A2 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void *get28(); };
struct A1 { u8 pad[0x30]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual A2 *get44(); };
struct A3 { u8 pad[0x14]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void *get40(int); };
struct S5 { u8 pad[0x1930]; virtual void v0(); virtual void set0c(void *, void *, int); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void set4c(void *);
    virtual void w18(); virtual void w19(); virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31(); virtual void w32(); virtual void w33(); virtual void w34(); virtual void w35(); virtual void w36(); virtual void w37(); virtual void w38(); virtual void w39(); virtual void w40(); virtual void w41(); virtual void w42(); virtual void w43(); virtual void w44(); virtual void w45(); virtual void w46(); virtual void w47(); virtual void w48(); virtual void w49(); virtual void w50(); virtual void w51(); virtual void w52(); virtual void w53(); virtual void w54(); virtual void w55(); virtual void w56(); virtual void w57(); virtual void w58(); virtual void w59(); virtual void w60(); virtual void w61(); virtual void w62(); virtual void set104(C4 *); };
struct S4 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void *get6c(); virtual void u26(); virtual void u27(); virtual void u28(); virtual void u29(); virtual void u30(); virtual void u31(); virtual void u32(); virtual S5 *get8c(); };
extern "C" {
extern char lbl_80298060[];
extern FT lbl_803286D0;
extern u8 *lbl_8035A1DC;
extern void *lbl_8035B320;
extern u8 *lbl_8035B460;
extern u8 *lbl_8035B65C;
extern K *lbl_8035B684;
extern u32 lbl_8035F3E8, lbl_8035F3F0;
extern f32 lbl_8035F638, lbl_8035F63C, lbl_8035F4E0, lbl_8035F45C, lbl_8035F490, lbl_8035F690, lbl_8035F3EC;
extern char lbl_8035F3F4[1];
extern char lbl_8035F640[8], lbl_8035F648[8], lbl_8035F5E4[8], lbl_8035F650[8], lbl_8035F658[8], lbl_8035F660[8], lbl_8035F668[8], lbl_8035F670[8], lbl_8035F678[8];
extern char lbl_8035F5A0[8], lbl_8035F680[8], lbl_8035F688[8], lbl_8035F414[8], lbl_8035F41C[8], lbl_8035F424[8], lbl_8035F434[8], lbl_8035F40C[8], lbl_8035F694[8], lbl_8035F69C[8];
void fn_8023D504(void *);
N *fn_800F9398(void *, char *);
N *fn_800F9788(void *, char *, char *);
void fn_800604C4(int, int, int, int);
void fn_800F7EC0(void *);
void fn_800F7E98();
void fn_80188144(void *, void *, void *, int);
void fn_8022F828(void *, void *);
u32 *fn_801955D8(void *);
int fn_800F6CD0(const void *, const void *);
void fn_80107F3C(void *, V3 *);
void fn_8019B7E8(void *, N *);
void *fn_800F8274(void *, char *);
void fn_80129938(void *, void *);
void fn_80129564(void *, Q4 *, f32, f32);
void fn_80190C98(N *);
N *fn_801952A0(N *);
void fn_80190940(N *, N *);
static inline N *Look(W90 *w, char *grp, char *name) {
    if (!grp || !*grp) return fn_800F9398(w->db.names, name);
    return fn_800F9788(w->db.groups, grp, name);
}
static inline N *LookF(WF0 *w, char *grp, char *name) {
    if (!grp || !*grp) return fn_800F9398(w->db.names, name);
    return fn_800F9788(w->db.groups, grp, name);
}
static inline N *Find(char *name) { return fn_800F9398(F(u8 *, lbl_8035B460, 8) + 0x90, name); }
static inline void SetQ(Q4 *q, f32 a, f32 b, f32 c, f32 d) { q->a = a; q->b = b; q->c = c; q->d = d; }
static inline void Fix(char *name) {
    N *p = Find(name);
    if (!p->f48) fn_8019B7E8(F(void *, lbl_8035B65C, 0xc), p);
    p->f0 &= ~0x800;
}
static inline void Place(N *n, V3 *v) {
    Z *z = n->f30;
    if (z) {
        lbl_803286D0.fc(z->f10, v);
        z->f20 |= lbl_8035F3F0;
        fn_80190C98(n);
    }
}
void fn_80077944(u8 *t, void *b) {
    char *str = lbl_80298060;
    fn_8023D504(t + 0x468);
    fn_8023D504(t + 0x494);
    F(f32, t, 0x478) = lbl_8035F638;
    F(f32, t, 0x480) = lbl_8035F63C;
    F(f32, t, 0x4a4) = lbl_8035F638;
    F(f32, t, 0x4ac) = lbl_8035F63C;
    F(N *, t, 0x448) = LookF(*F(WF0 **, lbl_8035A1DC, 0x2c50), lbl_8035F3F4, lbl_8035F640);
    F(N *, t, 0x44c) = LookF(*F(WF0 **, lbl_8035A1DC, 0x2c50), lbl_8035F3F4, lbl_8035F648);
    if (!lbl_8035B320) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B320);
    F(C801883E0 *, t, 0x424) = new C801883E0;
    fn_800F7E98();
    if (!F(void *, t, 0x424)) fn_800604C4(-4, 0, 0, 0);
    fn_80188144(F(void *, t, 0x424), F(void *, lbl_8035B460, 8), F(void *, t, 0xa0), 0);
    fn_8022F828(t, b);
    F(void *, t, 0x5ac) = F(void *, F(u8 *, lbl_8035B460, 8), 8);
    *fn_801955D8(F(void *, t, 0x9c)) |= lbl_8035F3E8;
    F(N *, t, 0x740) = fn_800F9398(F(u8 *, lbl_8035B460, 8) + 0xcc, str + 0x3c8);
    {
        N *v = F(N *, t, 0x740);
        F(N *, fn_801955D8(F(void *, t, 0x9c)), 0x7c) = v;
    }
    F(N *, t, 0x428) = Look(F(W90 *, lbl_8035B460, 8), lbl_8035F3F4, lbl_8035F5E4);
    F(N *, t, 0x42c) = Look(F(W90 *, lbl_8035B460, 8), lbl_8035F3F4, lbl_8035F650);
    F(N *, t, 0x450) = Look(F(W90 *, lbl_8035B460, 8), lbl_8035F3F4, lbl_8035F658);
    {
        B bb;
        lbl_8035B684->get(&bb, -1);
        if (fn_800F6CD0(&bb, lbl_8035F660)) F(N *, t, 0x430) = Look(F(W90 *, lbl_8035B460, 8), lbl_8035F3F4, lbl_8035F668);
    }
    if (F(N *, t, 0x430)) {
        V3 v;
        v.x = lbl_8035F4E0;
        v.y = lbl_8035F4E0;
        v.z = lbl_8035F4E0;
        if (F(N *, t, 0x430)->f78) fn_80107F3C(F(N *, t, 0x430)->f78, &v);
        F(N *, t, 0x430)->f0 |= lbl_8035F3E8;
        if (!F(N *, t, 0x430)->f48) fn_8019B7E8(F(void *, lbl_8035B65C, 0xc), F(N *, t, 0x430));
    }
    F(N *, t, 0x438) = Look(F(W90 *, lbl_8035B460, 8), lbl_8035F3F4, lbl_8035F670);
    F(N *, t, 0x43c) = fn_800F9398(lbl_8035A1DC + 0x30d0, lbl_8035F678);
    F(void *, t, 0x454) = fn_800F8274(F(void *, F(u8 *, t, 0xa0), 0xa8), str + 0x3d4);
    F(void *, t, 0x458) = fn_800F8274(F(void *, F(u8 *, t, 0xa0), 0xa8), lbl_8035F5A0);
    F(void *, t, 0x5f4) = (*F(A1 **, t, 0x5ac))->get44()->get28();
    F(N *, t, 0x5f0) = fn_800F9398(*F(u8 **, t, 0x5ac) + 0x78, lbl_8035F680);
    {
        void *k = ((A3 *)fn_800F9398(*F(u8 **, t, 0x5ac) + 0x3c, lbl_8035F688))->get40(0);
        C4 c;
        Q4 q;
        F(S4 *, t, 0x5f8) = F(S4 *, F(u8 *, lbl_8035B460, 0xc), 0x2c44);
        F(S5 *, t, 0x5fc) = F(S4 *, t, 0x5f8)->get8c();
        F(S5 *, t, 0x5fc)->set0c(*F(void **, t, 0x5ac), k, 0);
        F(S5 *, t, 0x5fc)->set4c(F(void *, t, 0x5f0));
        c.r = 0xff;
        c.g = 0xff;
        c.b = 0xff;
        c.a = 0xff;
        F(S5 *, t, 0x5fc)->set104(&c);
        F(void *, t, 0x600) = F(S4 *, t, 0x5f8)->get6c();
        fn_80129938(F(void *, t, 0x600), *F(void **, t, 0x5ac));
        *(volatile f32 *)&q.a = lbl_8035F45C;
        *(volatile f32 *)&q.b = lbl_8035F45C;
        f32 h = *(volatile f32 *)&lbl_8035F490;
        *(volatile f32 *)&q.c = h;
        *(volatile f32 *)&q.d = h;
        fn_80129564(*(void *volatile *)&F(void *, t, 0x600), &q, h, *(volatile f32 *)&lbl_8035F690);
    }
    {
        f32 *y = F(N *, t, 0x424)->f78;
        if (y) {
            F(f32, t, 0x6dc) = F(f32, y, 0x28);
            F(f32, t, 0x6e0) = F(f32, y, 0x2c);
            F(f32, t, 0x6e4) = F(f32, y, 0x30);
        } else {
            F(f32, t, 0x6dc) = lbl_8035F490;
            F(f32, t, 0x6e0) = lbl_8035F490;
            F(f32, t, 0x6e4) = lbl_8035F490;
        }
    }
    {
        f32 *y = F(N *, t, 0x428)->f78;
        if (y) {
            F(f32, t, 0x6f4) = F(f32, y, 0x28);
            F(f32, t, 0x6f8) = F(f32, y, 0x2c);
            F(f32, t, 0x6fc) = F(f32, y, 0x30);
        } else {
            F(f32, t, 0x6f4) = lbl_8035F490;
            F(f32, t, 0x6f8) = lbl_8035F490;
            F(f32, t, 0x6fc) = lbl_8035F490;
        }
    }
    Fix(lbl_8035F414);
    Fix(str + 0x3c);
    Fix(lbl_8035F41C);
    Fix(str + 0x54);
    Fix(lbl_8035F424);
    Fix(str + 0x6c);
    Fix(lbl_8035F434);
    Fix(str + 0x78);
    Fix(lbl_8035F40C);
    Fix(str + 0x30);
    F(N *, t, 0x718) = Find(lbl_8035F694);
    F(N *, t, 0x720) = Find(str + 0x3e0);
    if (F(N *, t, 0x720) && F(N *, t, 0x718)) {
        V3 v;
        Z *z = F(N *, t, 0x720)->f30;
        if (z) lbl_803286D0.f130(z->f10, &v);
        else {
            v.x = lbl_8035F3EC;
            v.y = lbl_8035F3EC;
            v.z = lbl_8035F3EC;
        }
        b = F(N *, t, 0x718);
        Place((N *)b, &v);
        N *p = Find(lbl_8035F69C);
        if (p) {
            N *q = fn_801952A0(p);
            if (q) {
                V3 w;
                fn_80190940(q, F(N *, t, 0x718));
                w.x = lbl_8035F3EC;
                w.y = lbl_8035F3EC;
                w.z = lbl_8035F3EC;
                Place(q, &w);
            }
        }
    }
    F(f32, t, 0x670) = lbl_8035F3EC;
    F(N *, t, 0x62c) = Find(str + 0x3ec);
}

} /* extern "C" */
#undef F
} // namespace n80077944

namespace n80078308 {

struct V3 { f32 x, y, z; };
struct T7 { V3 p; f32 q[4]; };
struct K8 { u32 a, b; };
#define V(n) virtual void n();
struct Nd { u8 p[16]; void *f16; u8 p20[12]; u32 f32; };
struct Hd { u8 p[48]; Nd *f48; };
class O { public: V(o0) V(o1) V(o2) V(o3) V(o4) V(o5) V(o6) V(o7) V(o8) V(o9) V(o10) V(o11) V(o12) V(o13) V(o14) V(o15) V(o16) V(o17) V(o18) V(o19) };
struct FT { u8 p[12]; void (*f12)(void *, V3 *); u8 p16[288]; void (*f304)(void *, V3 *); };
struct GB { u8 p[8]; u8 *f8; };
#define F(o, off, t) (*(t *)((u8 *)(o) + (off)))
extern "C" {
extern char lbl_80298060[];
extern u32 lbl_8035A238;
extern volatile u32 lbl_8035A264;
extern f32 lbl_8035F3EC, lbl_8035F45C, lbl_8035F490;
extern u32 lbl_8035F3E8, lbl_8035F3F0;
extern void *lbl_80359F2C;
extern void *volatile lbl_8035B65C;
extern void *lbl_8035B684;
extern GB *lbl_8035B460;
extern char lbl_8035F3F4[8], lbl_8035F5D4[8];
extern FT lbl_803286D0;
void fn_8022BF30(O *, int, int, f32);
void fn_8022BE28(O *, int);
void fn_8002B42C(void *, int);
void fn_8022F700(O *);
void __ct__9C80253F24Fiiii(void *, char *, int, int, int);
void fn_8002FD10(void *, K8 *);
void fn_800F6E88(K8 *, void *);
int fn_800F6CD0(K8 *, void *);
void *fn_800F9398(u8 *, void *);
void fn_80241DD0(void *, char *, int, int, K8 *, int);
void fn_80107244(Nd *, V3 *);
void fn_801075B8(Nd *, f32 *);
void fn_80190C98(Hd *);
}
extern "C" void fn_80078308(O *o) {
    char *s = lbl_80298060;
    V3 v;
    f32 tq[4];
    V3 tp;
    K8 b;
    K8 n;
    lbl_8035A238 = 0;
    F(o, 1376, u32) = 0;
    F(o, 1360, f32) = lbl_8035F3EC;
    fn_8022BF30(o, 255, 1, lbl_8035F3EC);
    fn_8022BE28(o, 0);
    F(o, 552, u32) |= 1;
    fn_8002B42C(lbl_80359F2C, 1);
    if (F(o, 1064, u32 *)) *F(o, 1064, u32 *) |= lbl_8035F3E8;
    if (F(o, 1080, u32 *)) *F(o, 1080, u32 *) |= lbl_8035F3E8;
    F(o, 1752, u32) = 1;
    F(o, 1644, f32) = F(o, 1648, f32) = lbl_8035F45C;
    fn_8022F700(o);
    if (*F(o, 1348, s32 *) <= 0) *F(o, 1348, s32 *) = 1;
    F(o, 428, f32) = *F(o, 1348, s32 *);
    F(o, 424, f32) = *F(o, 1352, s32 *);
    __ct__9C80253F24Fiiii(lbl_8035B65C, s + 1016, 0, 0, 0);
    fn_8002FD10(lbl_8035B684, &n);
    fn_800F6E88(&b, lbl_8035F3F4);
    if (!fn_800F6CD0(&n, lbl_8035F3F4) && fn_800F9398(lbl_8035B460->f8 + 144, &n)) fn_800F6E88(&b, &n);
    else if (fn_800F9398(lbl_8035B460->f8 + 144, lbl_8035F5D4)) fn_800F6E88(&b, lbl_8035F5D4);
    if (!fn_800F6CD0(&b, lbl_8035F3F4)) fn_80241DD0(F(o, 524, void *), s + 372, 0, 0, &b, 0);
    F(o, 1456, Hd *) = 0;
    if (F(o, 1456, Hd *)) {
        Hd *h = F(o, 1456, Hd *);
        f32 z = lbl_8035F3EC;
        tp.x = z; tp.y = z; tp.z = z; tq[0] = z; tq[1] = z; tq[2] = z; tq[3] = z;
        if (h->f48) fn_80107244(h->f48, &tp);
        else { tp.x = z; tp.y = z; tp.z = z; }
        if (F(o, 1456, Hd *)->f48) fn_801075B8(F(o, 1456, Hd *)->f48, tq);
        F(o, 1460, f32) = tp.x; F(o, 1464, f32) = tp.y; F(o, 1468, f32) = tp.z;
        F(o, 1472, f32) = tq[0]; F(o, 1476, f32) = tq[1]; F(o, 1480, f32) = tq[2]; F(o, 1484, f32) = tq[3];
    }
    F(o, 824, u32) = 0;
    o->o19();
    o->o17();
    lbl_8035A264 = 0;
    __ct__9C80253F24Fiiii(lbl_8035B65C, s + 1028, 0, 0, 0);
    F(o, 1676, u32) = 1;
    if (F(o, 1824, Hd *) && F(o, 1816, Hd *)) {
        Nd *y = F(o, 1824, Hd *)->f48;
        if (y) lbl_803286D0.f304(y->f16, &v);
        else { v.x = lbl_8035F3EC; v.y = lbl_8035F3EC; v.z = lbl_8035F3EC; }
        {
            Hd *z = F(o, 1816, Hd *);
            Nd *w = z->f48;
            if (w) {
                lbl_803286D0.f12(w->f16, &v);
                w->f32 |= lbl_8035F3F0;
                fn_80190C98(z);
            }
        }
    }
    F(o, 1268, u32) = 0;
    F(o, 1272, f32) = lbl_8035F490;
}
#undef V
#undef F
} // namespace n80078308
