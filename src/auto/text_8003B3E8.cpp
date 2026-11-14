#include "common.h"
struct C801829F8 { char pad[0x78]; C801829F8(void); };
struct C80215B8C { char pad[52]; C80215B8C(void); };
namespace N8003B3E8 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

struct C { u8 r, g, b, a; };
struct K { u32 w[4]; };
struct R { u8 pad[6448]; virtual void a0(); virtual void a1(); virtual void a2(); virtual void draw(void *, int, int); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void b53(); virtual void b54(); virtual void b55(); virtual void b56(); virtual void b57(); virtual void b58(); virtual void end(); virtual void begin(C *); };
struct D { u8 pad[64]; K k; virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void render(R *); };
struct G { u8 pad[48]; virtual void g0(); virtual void g1(); virtual void g2(); virtual void g3(); virtual void g4(); virtual void g5(); virtual void g6(); virtual void g7(); virtual void set(int); };
struct G1DC { u8 pad[11340]; G *f11340; };
extern G1DC *lbl_8035A1DC;
void fn_80121E1C(K *);
void fn_80121DC8(K *, C *);
struct T { u8 pad[4]; void *f4; u8 pad8[16]; R *f24; D *f28; D *f32; u8 pad36[8]; D *f44; u8 pad48[52]; u32 f100; u8 pad104[4]; u32 f108; };
void fn_8003B3E8(T *t) {
    C bg;
    bg.r = 0; bg.g = 0; bg.b = 0; bg.a = 255;
    t->f24->begin(&bg);
    f32 v = 0.01f * (255.0f * (f32)(int)(t->f100 * 100 / t->f108));
    if (v > 255.0f) v = 255.0f;
    K k1;
    K k2;
    fn_80121E1C(&k1);
    fn_80121E1C(&k2);
    C y;
    C x;
    u8 c = (u32)(255.0f - v);
    x.r = c; x.g = c; x.b = c; x.a = c;
    c = (u32)v;
    y.r = c; y.g = c; y.b = c; y.a = c;
    fn_80121DC8(&k1, &y);
    fn_80121DC8(&k2, &x);
    t->f28->k = k1;
    t->f24->draw(t->f4, 7, 0);
    t->f28->k = k2;
    t->f28->render(t->f24);
    t->f32->k = k1;
    t->f32->render(t->f24);
    t->f44->render(t->f24);
    t->f24->end();
    lbl_8035A1DC->f11340->set(0);
}

} /* extern "C" */

}
#pragma explicit_zero_data on
extern "C" {
__declspec(section ".sdata2") f32 lbl_8035C158 = 0.0f;
__declspec(section ".sdata2") f32 lbl_8035C15C = 0.001f;
__declspec(section ".sdata2") f32 lbl_8035C160 = 1.0f;
}
#pragma explicit_zero_data reset
namespace N8003B5F8 {

extern "C" {
typedef struct { u8 r, g, b, a; } C4;
typedef struct { C4 c[4]; } C16;
typedef struct { u8 pad[64]; C16 cols; } Mat;
typedef struct { u8 pad[44]; Mat *mat; u8 pad2[100 - 48]; s32 cur; u32 pad3; u32 max; u32 last; } T;
extern volatile u32 lbl_8035A078;
extern volatile s8 lbl_8035A07C;
extern volatile f32 lbl_8035A080;
extern volatile s8 lbl_8035A084;
extern volatile s32 lbl_8035A088;
extern volatile s8 lbl_8035A08C;
extern f32 lbl_8035C158, lbl_8035C15C, lbl_8035C160;
u32 fn_800FBB9C(void);
void fn_80121E1C(void *p);
void fn_8003B3E8(T *t, void *p);

void fn_8003B5F8(T *t, void *p) {
    u32 dt;
    C16 c;
    if (!lbl_8035A07C) { lbl_8035A078 = fn_800FBB9C(); lbl_8035A07C = 1; }
    if (!lbl_8035A084) { lbl_8035A080 = lbl_8035C158; lbl_8035A084 = 1; }
    if (!lbl_8035A08C) { lbl_8035A088 = 1; lbl_8035A08C = 1; }
    dt = fn_800FBB9C() - lbl_8035A078;
    lbl_8035A078 = fn_800FBB9C();
    lbl_8035A080 = lbl_8035C15C * (f32)dt + lbl_8035A080;
    fn_80121E1C(&c);
    if (lbl_8035A080 > lbl_8035C160) {
        lbl_8035A080 = lbl_8035C158;
        if (lbl_8035A088 == 0) {
            c.c[0].r = 59; c.c[0].g = 0; c.c[0].b = 168; c.c[0].a = 255;
            c.c[1].r = 0; c.c[1].g = 54; c.c[1].b = 164; c.c[1].a = 255;
            c.c[2].r = 0; c.c[2].g = 115; c.c[2].b = 144; c.c[2].a = 255;
            c.c[3].r = 0; c.c[3].g = 138; c.c[3].b = 104; c.c[3].a = 255;
            t->mat->cols = c;
            lbl_8035A088 = 1;
        } else {
            c.c[0].r = 59; c.c[0].g = 0; c.c[0].b = 168; c.c[0].a = 255;
            c.c[1].r = 0; c.c[1].g = 54; c.c[1].b = 164; c.c[1].a = 255;
            c.c[2].r = 130; c.c[2].g = 96; c.c[2].b = 133; c.c[2].a = 255;
            c.c[3].r = 140; c.c[3].g = 96; c.c[3].b = 119; c.c[3].a = 255;
            t->mat->cols = c;
            lbl_8035A088 = 0;
        }
    }
    if (fn_800FBB9C() - t->last < 500) {
        t->max--;
        if (t->max == 0) t->max = 1;
    } else {
        t->cur++;
        if (t->cur > (s32)t->max) t->cur = t->max;
    }
    fn_8003B3E8(t, p);
}
}

}
namespace N8003B87C {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct G8003B87C {
    u8 pad[6448];
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(u32 a, s32 b, s32 c);
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61();
    virtual void v62();
    virtual void v63(u8 *color);
};
struct R8003B87C {
    u8 pad[80];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(G8003B87C *g);
};
struct S8003B87C {
    u8 pad[48];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(s32 a);
};
struct T8003B87C {
    u8 pad[56];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11();
};
extern "C" {
extern u8 *lbl_8035A02C;
extern u8 *lbl_8035A1DC;
extern const f32 lbl_8035C178;
extern const f32 lbl_8035C170;
void fn_80039E80(u8 *p, s32 a, f32 f);
s32 fn_800FBB9C(void);
void fn_80039EA4(u8 *p, f32 f);
void fn_80039F78(u8 *p, G8003B87C *g);

void fn_8003B87C(u8 *self, s32 flag) {
    u8 *g;
    s32 start;
    u8 color[4];
    if (flag != 0) {
        fn_80039E80(lbl_8035A02C, 1, lbl_8035C178);
        start = fn_800FBB9C();
        while (*(s32 *)(lbl_8035A02C + 32) != 0) {
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;
            color[3] = 255;
            (*(G8003B87C **)(self + 24))->v63(color);
            (*(G8003B87C **)(self + 24))->v3(*(u32 *)(self + 4), 7, 0);
            (*(R8003B87C **)(self + 32))->v4(*(G8003B87C **)(self + 24));
            (*(G8003B87C **)(self + 24))->v62();
            g = lbl_8035A02C;
            fn_80039EA4(g, (f32)(fn_800FBB9C() - start) / lbl_8035C170);
            start = fn_800FBB9C();
            fn_80039F78(lbl_8035A02C, *(G8003B87C **)(self + 24));
            (*(S8003B87C **)(lbl_8035A1DC + 11340))->v8(1);
        }
    }
    if (*(T8003B87C **)(self + 40) != 0) {
        (*(T8003B87C **)(self + 40))->v11();
        *(T8003B87C **)(self + 40) = 0;
    }
    if (*(T8003B87C **)(self + 36) != 0) {
        (*(T8003B87C **)(self + 36))->v11();
        *(T8003B87C **)(self + 36) = 0;
    }
}

} /* extern "C" */

}
namespace N8003BA20 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

extern "C" void *memset(void *, int, unsigned long);
struct E52 { u8 pad[52]; };
struct G5E4 { u8 pad[112]; E52 *f112; u32 f116; };
extern G5E4 *lbl_8035B5E4;
struct Z { u8 pad[8]; u32 f8; u8 pad12[44]; virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3(); virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7(); virtual void z8(); virtual void z9(); virtual void set(void *); };
struct Y { u8 pad[16]; virtual void y0(); virtual void y1(); virtual void y2(); virtual void y3(); virtual Z *make(int); };
struct X { u8 pad[164]; virtual void x0(); virtual void x1(); virtual void x2(); virtual void x3(); virtual void x4(); virtual void x5(); virtual void x6(); virtual void x7(); virtual void x8(); virtual void x9(); virtual void x10(); virtual void x11(); virtual void x12(); virtual void x13(); virtual void x14(); virtual void x15(); virtual void x16(); virtual void x17(); virtual void x18(); virtual Y *get(int); };
struct H { u8 pad[84]; Z *f84; };
struct B { u8 pad[8]; u32 f8; u8 pad12[200]; };
struct M { u8 pad[48]; virtual void m0(); virtual void m1(); virtual void m2(); virtual void send(B *); };
struct G1DC { u8 pad[11316]; M m; u8 pad2[11340 - 11316 - sizeof(M)]; void *f11340; };
extern G1DC *lbl_8035A1DC;
extern u32 lbl_8035A070;
extern u32 lbl_8035C17C;
extern f32 lbl_8035C158;
extern char lbl_80294DC8[];
struct T { void *f0; u8 pad4[4]; X *f8; u8 pad12[16]; H *f28; H *h32; Z *f36; Z *f40; u8 pad44[8]; u32 f52; u8 pad56[8]; int f64; u8 pad68[12]; int f80; f32 f84; int f88; int f92; int f96; int f100; u32 f104; int f108; int f112; u32 f116; };
int fn_800FBB9C();
void fn_80253250(E52 *);
void fn_802516A4(G5E4 *, int);
void fn_80216044(void *, const char *);
void fn_80215FDC(void *);
static inline void clr(G5E4 *g) { for (u32 i = 0; i < g->f116; i++) fn_80253250(&g->f112[i]); fn_802516A4(g, 0); }
void fn_8003BA20(T *t, int arg) {
    B b;
    t->f112 = fn_800FBB9C();
    t->f100 = 0;
    t->f108 = 18;
    clr(lbl_8035B5E4);
    t->f36 = t->f8->get(0)->make(t->f116 * 2 + 1);
    t->f28->f84 = t->f36;
    t->f36->f8 |= lbl_8035C17C;
    t->f40 = t->f8->get(0)->make(t->f116 * 2);
    t->h32->f84 = t->f40;
    t->f116++;
    if (t->f116 >= t->f104) t->f116 = 0;
    fn_80216044(t->f0, lbl_80294DC8);
    memset(&b, 0, sizeof(B));
    *(volatile u32 *)&b.f8 = lbl_8035A070;
    (*(G1DC *volatile *)&lbl_8035A1DC)->m.send(&b);
    t->f40->set(lbl_8035A1DC->f11340);
    t->f36->set(lbl_8035A1DC->f11340);
    *(volatile u32 *)&b.f8 = t->f52;
    (*(G1DC *volatile *)&lbl_8035A1DC)->m.send(&b);
    fn_80215FDC(t->f0);
    t->f88 = fn_800FBB9C();
    t->f92 = t->f88;
    t->f80 = fn_800FBB9C();
    t->f84 = lbl_8035C158;
    t->f64 = 0;
    t->f96 = arg;
}

} /* extern "C" */

}
namespace N8003BC2C {

struct V3s { f32 x, y, z; };
static inline void ScaleP(V3s *v, f32 k) { v->x *= k; v->y *= k; v->z *= k; }
static inline void ScaleL(V3s *v, f32 k) { f32 x = v->x; f32 y = v->y; f32 z = v->z; v->x = x * k; v->y = y * k; v->z = z * k; }
static inline void ScaleA(f32 *v, f32 k) { v[0] *= k; v[1] *= k; v[2] *= k; }
extern "C" {
struct Vec3 { f32 x, y, z; };
struct Col { u8 r, g, b, a; };
struct Msg { u32 a, b, c; u8 rest[200]; };
struct R1 { u8 pad[28]; u32 f28; };
struct O8 {
    u8 pad[164];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual R1 *get(int);
};
struct D24 {
    u8 pad[6448];
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void set(u32, int, int);
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
    virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
    virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
    virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60(); virtual void v61();
    virtual void end();
    virtual void col(Col *);
};
struct D28 {
    u8 pad[80];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void draw(D24 *);
};
struct D44 { u8 pad0[16]; f32 f16; u8 pad1[60]; virtual void v0(); u8 pad2[4]; u32 f88; };
struct X40 {
    u8 pad[48];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual void en(int);
};
struct X0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual u32 m25(); virtual void v26();
    virtual O8 *m27();
};
struct M {
    u8 pad0[16];
    X0 *f16;
    u8 pad1[4];
    X40 *f24;
    D24 *f28;
    u8 pad2[16];
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void send(Msg *);
};
struct G { u8 pad[11316]; M m; u8 pad2[12352 - 11316 - sizeof(M)]; u8 f12352[4]; };
struct P {
    u32 f0;
    u32 f4;
    O8 *f8;
    C801829F8 *f12;
    u8 *f16;
    u8 pad20[4];
    D24 *f24;
    D28 *f28;
    void *x32;
    u8 pad36[8];
    D44 *f44;
    u32 f48;
    u32 f52;
    s32 f56;
    u8 pad60[12];
    u32 f72;
    u8 pad76[4];
    u32 x80;
    f32 x84;
    u8 pad88[16];
    u32 f104;
    u8 pad108[12];
    C80215B8C *f120;
};
struct E { u8 pad[20]; u8 *f20; };
extern G *lbl_8035A1DC;
extern u32 lbl_8035A070;
extern u32 *lbl_8035B418;
extern f32 lbl_8035C158, lbl_8035C170, lbl_8035C174, lbl_8035C180, lbl_8035C184, lbl_8035C188, lbl_8035C18C;
extern f32 lbl_8035C190, lbl_8035C194, lbl_8035C198, lbl_8035C19C, lbl_8035C1A8;
extern char lbl_8035C1A0[6];
extern char lbl_80294DC8[], lbl_80294DE4[];
u32 fn_800FBB9C(void);
void fn_80129938(u32, X40 *);
void fn_8012962C(u32, f32, f32, f32, f32);
void fn_80101820(Vec3 *);
void fn_80129710(u32, Vec3 *, Vec3 *, Vec3 *);
void *memset(void *, int, u32);
void fn_80216044(u32, char *);
void fn_8012ACAC(O8 *, X40 *, char *, s32, s32);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(u32);
void fn_800F7E98(void);
void fn_8018182C(C801829F8 *, u8 *, char *, s32);
void fn_80215FDC(u32);
E *fn_80180EBC(C801829F8 *, int);
E *fn_80180EAC(C801829F8 *, int);
char *fn_8023C824(u32 *, u32);
int fn_800E8F6C(char *, char *, ...);
void fn_80215534(C80215B8C *, u32, char *, int);
u32 fn_800F8274(C80215B8C *, char *);

void fn_8003BC2C(P *p)
{
    Msg msg;
    char name[128];
    Vec3 b;
    Vec3 c;
    Vec3 a;
    u8 col[3];
    G *g = lbl_8035A1DC;
    u8 *q;
    if (p->f56 && p->f56) {
        u32 dt = fn_800FBB9C() - p->x80;
        if (dt >= 50) {
            p->x80 = fn_800FBB9C();
            p->x84 += (f32)dt / lbl_8035C170;
            col[0] = 0;
            col[1] = 0;
            col[2] = 0;
            col[3] = 255;
            p->f24->col((Col *)col);
            p->f24->set(p->f4, 7, 0);
            p->f28->draw(p->f24);
            if ((s32)(lbl_8035C174 * p->x84) % 2)
                ((D28 *)p->f44)->draw(p->f24);
            p->f24->end();
            lbl_8035A1DC->m.f24->en(1);
        }
    }
    p->f4 = g->m.f16->m25();
    fn_80129938(p->f4, g->m.f24);
    fn_8012962C(p->f4, lbl_8035C180, lbl_8035C184, lbl_8035C188, lbl_8035C18C);
    {
        f32 z0 = lbl_8035C158;
        f32 k;
        ((f32 *)col)[1] = z0;
        ((f32 *)col)[2] = lbl_8035C190;
        ((f32 *)col)[3] = lbl_8035C194;
        ((f32 *)col)[7] = z0;
        ((f32 *)col)[8] = z0;
        ((f32 *)col)[9] = z0;
        ((f32 *)col)[7] = lbl_8035C198;
        k = lbl_8035C174;
        ((f32 *)col)[8] = k;
        ((f32 *)col)[9] = k;
    }
    fn_80101820(&b);
    {
        f32 z, y, x, k;
        x = b.x; k = *(volatile f32 *)&lbl_8035C19C; y = b.y; z = b.z;
        x *= k; y *= k; z *= k;
        ((f32 *)col)[7] = x; ((f32 *)col)[8] = y; ((f32 *)col)[9] = z;
    }
    c.x = lbl_8035C158;
    c.y = lbl_8035C158;
    c.z = lbl_8035C158;
    fn_80129710(p->f4, &b, &c, &a);
    p->f8 = g->m.f16->m27();
    memset(&msg, 0, sizeof(msg));
    msg.c = lbl_8035A070;
    g->m.send(&msg);
    fn_80216044(p->f0, lbl_80294DC8);
    fn_8012ACAC(p->f8, g->m.f24, lbl_8035C1A0, 1, 0);
    p->f104 = p->f8->get(0)->f28 >> 1;
    if (lbl_8035A070 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035A070);
    p->f12 = new C801829F8();
    fn_800F7E98();
    if (p->f12 == 0) fn_800604C4(-4, 0, 0, 0);
    q = g->f12352;
    fn_8018182C(p->f12, q, lbl_8035C1A0, 1);
    fn_80215FDC(p->f0);
    p->f28 = (D28 *)fn_80180EBC(p->f12, 0)->f20;
    p->x32 = fn_80180EBC(p->f12, 0)->f20 + 88;
    p->f44 = (D44 *)fn_80180EAC(p->f12, 0)->f20;
    p->f44->f16 = (f32)p->f72 * lbl_8035C1A8;
    p->f24 = g->m.f28;
    p->f16 = q;
    { char *t = fn_8023C824(lbl_8035B418, *lbl_8035B418); fn_800E8F6C(name, lbl_80294DE4, t); }
    if (lbl_8035A070 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035A070);
    p->f120 = new C80215B8C();
    fn_800F7E98();
    if (p->f120 == 0) fn_800604C4(-4, 0, 0, 0);
    fn_80215534(p->f120, p->f0, name, 1);
    p->f48 = fn_800F8274(p->f120, lbl_8035C1A0);
    if (p->f48) p->f44->f88 = p->f48;
    ((u32 *)name)[34] = p->f52;
    lbl_8035A1DC->m.send(&msg);
}
}

}
