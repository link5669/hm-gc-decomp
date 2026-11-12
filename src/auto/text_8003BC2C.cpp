#include "common.h"
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
struct C801829F8 { char pad[0x78]; C801829F8(void); };
struct C80215B8C { char pad[52]; C80215B8C(void); };
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
    p->f44->f16 = lbl_8035C1A8 * (f32)p->f72;
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
