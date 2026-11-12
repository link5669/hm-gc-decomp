// Code of main that had no source file yet: decomp.wtf gave it this one.
// fn_8007AC1C NonMatching draft (wMY, wOX): DIFF 16 / SDIFF 2. Volatile ax-neg stores + volatile K read pin the K load; volatile ay.x/ay.y/ay.z/c.z stores in target order (wOX). wRR: k,nz,ny,nx declared then assigned (nx,ny,nz) before the k read fixed FPR colouring (DIFF 16). Left: ay.x stfs scheduled before first fmuls, f1/f2 temp swap.
#include "common.h"

extern "C" {

struct V3 { f32 x, y, z; };

struct Q {
    u8 pad[0x98];
    u32 f98;
    f32 f9c;
    u8 pada0[0xac - 0xa0];
    f32 fac;
};

struct VE {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12();
    virtual void getPos(V3 *p, s32 a, s32 b, s32 c, s32 d);
    virtual void setPos(V3 *p, V3 *a, V3 *b, V3 *c, s32 d);
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
    virtual void s21(); virtual void s22();
    virtual void off();
    virtual void on();
    u8 pad4[0x9c - 4];
    Q *f9c;
};

struct T30 { u8 pad[0x30]; void *f30; };
struct T9C { u8 pad[0x9c]; T30 *f9c; };

struct Obj {
    u8 pad0[0x60];
    s32 f60;
    u8 pad64[0xe0 - 0x64];
    VE *fe0;
    u8 pade4[0x11c - 0xe4];
    s32 *f11c;
    u8 pad120[0x128 - 0x120];
    f32 *f128;
    f32 *f12c;
    f32 *f130;
    f32 *f134;
    u8 pad138[0x140 - 0x138];
    f32 *f140;
    u8 pad144[0x158 - 0x144];
    s32 *f158;
    s32 *f15c;
    char *f160;
    char *f164;
    char *f168;
    u8 pad16c[0x174 - 0x16c];
    s32 *f174;
    u8 pad178[0x180 - 0x178];
    T9C *f180;
    s32 f184;
    s32 f188;
    s32 f18c;
    s32 f190;
    s32 f194;
    u8 pad198[0x1ac - 0x198];
    s32 f1ac;
};

extern f32 lbl_8035F76C;
extern f32 lbl_8035F780;
extern f32 lbl_8035F790;
extern u32 lbl_8035F760;
extern char lbl_8035F720[4], lbl_8035F770[4], lbl_8035F778[4];
extern char lbl_80357740[];
extern void **lbl_8035B334;

int fn_800F6CD0(char *, char *);
f32 fn_80101590(V3 *, V3 *);
void fn_80101820(V3 *);
void fn_80107244(void *, V3 *);
void fn_80196688(Q *);
void fn_8022345C(void *p, f32 f);
void *fn_802288FC(void *, char *);
void fn_8022A7A8(VE *);
void fn_8022AD0C(VE *);
void fn_8022B618(VE *);
void fn_80240B50(Obj *, char *, s32);
void fn_8024118C(Obj *, char *, s32);
void fn_80249008(Obj *, s32);
void fn_802490E0(Obj *, s32, f32);
int strcmp(const char *, const char *);

static inline void Chk(Obj *o, char *s, s32 v) {
    if (fn_800F6CD0(s, lbl_8035F720) == 0) {
        if (o->f1ac) fn_80240B50(o, s, v);
        else fn_8024118C(o, s, v);
        o->f1ac = v;
    }
}

static inline void Cross2(V3 *r, V3 *a, V3 *b) {
    r->z = a->x * b->y - a->y * b->x;
    r->x = a->y * b->z - a->z * b->y;
    r->y = a->z * b->x - a->x * b->z;
}
static inline void Cross(V3 *r, V3 *a, V3 *b) {
    r->x = a->y * b->z - a->z * b->y;
    r->y = a->z * b->x - a->x * b->z;
    r->z = a->x * b->y - a->y * b->x;
}

#define VS(a) (*(volatile f32 *)&(a))

void fn_8007AC1C(Obj *o, f32 dt) {
    V3 cp;
    V3 tp;
    V3 dir;
    V3 ax;
    V3 ay;
    V3 c;
    f32 d;
    void *x;

    if (o->f180 == 0) return;
    if (o->f60 != 1) return;
    if (o->f184 == 0 || (o->f184 != 0 && o->f188 != 0)) {
        o->fe0->getPos(&cp, 0, 0, 0, 0);
        x = o->f180->f9c->f30;
        if (x) {
            fn_80107244(x, &tp);
        } else {
            f32 k = *(volatile f32 *)&lbl_8035F76C;
            tp.x = k;
            tp.y = k;
            tp.z = k;
        }
        if (*o->f11c == 0) tp.z = cp.z;
        d = fn_80101590(&cp, &tp);
        if (d > *o->f128) {
            dir.x = tp.x - cp.x;
            dir.y = tp.y - cp.y;
            dir.z = tp.z - cp.z;
            fn_80101820(&dir);
            if (d > *o->f128 + *o->f12c) {
                o->f18c = 1;
                fn_80249008(o, 0);
                fn_802490E0(o, 1, *o->f140);
            }
            if (o->f18c == 0) return;
            {
                f32 a = *o->f128;
                f32 b = *o->f12c;
                f32 ab = a + b;
                f32 lim = *o->f134 * dt;
                f32 s;
                if (d < ab) s = *o->f130 * (d - a);
                else s = b * *o->f130 + (d - ab);
                if (s < lim) s = lim;
                dir.x *= s;
                dir.y *= s;
                dir.z *= s;
            }
            if (*o->f174 != 0) {
                ax.x = dir.x;
                ax.y = dir.y;
                ((f32 *)&ay)[5] = dir.z;
                ax.z = lbl_8035F76C;
                fn_80101820(&ax);
                {
                    *(volatile f32 *)&ax.x = -ax.x;
                    *(volatile f32 *)&ax.y = -ax.y;
                    *(volatile f32 *)&ax.z = -ax.z;
                    f32 k, nz, ny, nx;
                    nx = ax.x; ny = ax.y; nz = ax.z;
                    {
                        k = *(volatile f32 *)&lbl_8035F76C;
                        VS(ay.x) = k;
                        VS(((f32 *)&c)[4]) = k;
                        {
                            VS(ay.z) = lbl_8035F790;
                            c.x = ny * lbl_8035F790 - k * nz;
                            c.y = nz * k - nx * lbl_8035F790;
                            c.z = nx * k - ny * k;
                        }
                    }
                }
                fn_80101820(&c);
                Cross(&ay, &c, &ax);
                fn_80101820(&ay);
                o->fe0->setPos(0, &ax, &ay, &c, 0);
            }
            cp.x += dir.x;
            cp.y += dir.y;
            cp.z += dir.z;
            o->fe0->setPos(&cp, 0, 0, 0, 0);
            if (o->f190 != 0) return;
            Chk(o, o->f160, 0);
            Chk(o, o->f164, 1);
            if (*o->f158 != 0) {
                if (*o->f15c != 0) {
                    if (*o->f15c != 0) {
                        Q *q = o->fe0->f9c;
                        q->f9c = lbl_8035F76C;
                        q->f98 &= ~6;
                        q->fac = lbl_8035F76C;
                        fn_80196688(q);
                        q->f98 &= ~8;
                    }
                } else {
                    o->fe0->off();
                    fn_8022AD0C(o->fe0);
                    o->f194 = 1;
                }
            }
            if (strcmp(lbl_80357740, lbl_8035F770) == 0) {
                fn_8022345C(fn_802288FC(*lbl_8035B334, lbl_8035F778), lbl_8035F780);
            }
        } else {
            if (o->f18c == 0) return;
            o->f18c = 0;
            if (o->f190 == 0) return;
            Chk(o, o->f168, 0);
            if (*o->f158 == 0) return;
            if (*o->f15c != 0) {
                if (*o->f15c != 0) {
                    Q *q = o->fe0->f9c;
                    q->f98 |= lbl_8035F760;
                    q->f9c = lbl_8035F76C;
                    q->f98 &= ~6;
                    q->fac = lbl_8035F76C;
                    fn_80196688(q);
                }
            } else {
                o->fe0->on();
                fn_8022A7A8(o->fe0);
                fn_8022B618(o->fe0);
            }
        }
    }
}

}
