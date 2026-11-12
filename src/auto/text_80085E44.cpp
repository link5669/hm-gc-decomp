// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct Vec3 { f32 x, y, z; };
struct Q4 { f32 x, y, z, w; };
struct B { u8 pad[16]; void *h; u8 pad2[12]; u32 flags; };
struct C { u8 pad[48]; B *b; };
struct FT {
    u8 pad0[24]; void (*set24)(void *, Vec3 *);
    u8 pad1[272]; void (*get300)(void *, Vec3 *);
};
struct R {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual void s11(void *);
    virtual void v10();
    virtual void s13();
};
struct G {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void s15(Vec3 *, int, int, int, int);
    u8 pad[300];
    Vec3 v304;
};
struct H0 { u8 pad_[104]; virtual void v0(); };
struct H : H0 {
    virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void s18(Q4 *);
};
struct O {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void s14(f32);
    u8 pad4[64];
    Vec3 v68;
    u8 pad80[76];
    C *f156;
    u8 pad160[120];
    Vec3 v280;
    u8 pad292[24];
    Vec3 v316;
    u8 pad328[68];
    G *f396;
    u8 pad400[228];
    f32 *f628;
    u8 pad632[124];
    C *f756;
    u8 pad760[128];
    R *f888;
    u8 pad892[20];
    f32 f912;
};
extern FT lbl_803286D0;
extern u32 lbl_8035FDF0;
extern f32 lbl_8035FDF8, lbl_8035FE10, lbl_8035FE14, lbl_8035FE28, lbl_8035FE2C, lbl_8035FE30, lbl_8035FE34;
extern f64 lbl_8035FE18, lbl_8035FE20;
extern char lbl_8035FE08[8];
extern char lbl_80298E18[];
void fn_8005D9EC(O *, void *, int);
void *fn_8023BC90(char *);
R *fn_8023B8FC(void *, char *, int);
void fn_80190C98(C *);
void fn_80100CF4(Q4 *);
void fn_80101744(Vec3 *, Vec3 *);
void fn_80101414(Vec3 *, Vec3 *, f32);
void fn_80101820(Vec3 *);
f32 fn_80101590(const Vec3 *, const Vec3 *);
double fn_800F030C(double);
double fn_800EFDA4(double);

static inline f32 Sqrt(f32 d)
{
    volatile f32 y;
    f64 guess;
    if (d > lbl_8035FDF8) {
        guess = __frsqrte((f64)d);
        guess = lbl_8035FE18 * guess * (lbl_8035FE20 - guess * guess * d);
        guess = lbl_8035FE18 * guess * (lbl_8035FE20 - guess * guess * d);
        guess = lbl_8035FE18 * guess * (lbl_8035FE20 - guess * guess * d);
        y = (f32)(d * guess);
        return y;
    }
    return d;
}

static inline void Put(O *p, Vec3 *v)
{
    B *b;
    C *c = p->f756;
    b = c->b;
    if (b) {
        lbl_803286D0.set24(b->h, v);
        b->flags |= lbl_8035FDF0;
        fn_80190C98(c);
    }
}

static inline f32 Dist(const Vec3 *a, const Vec3 *b)
{
    f32 dx = b->x - a->x;
    f32 dy = b->y - a->y;
    f32 dz = b->z - a->z;
    dx = dx * dx + dy * dy + dz * dz;
    return Sqrt(dx);
}

static inline f32 Max(O *p) { return p->f628 ? *p->f628 : lbl_8035FE28; }

void fn_80085E44(O *p, void *a)
{
    Vec3 v80;
    Q4 q;
    Vec3 n;
    Vec3 v;
    Vec3 t;
    Vec3 s;
    volatile f32 y;
    fn_8005D9EC(p, a, 0);
    if (p->f888 == 0) {
        p->f888 = fn_8023B8FC(fn_8023BC90(lbl_8035FE08), lbl_80298E18, -1);
        p->f888->s11(p);
    }
    if (p->f756) {
        B *b = p->f156->b;
        if (b) lbl_803286D0.get300(b->h, &v80);
        Put(p, &v80);
    }
    fn_80100CF4(&q);
    {
        H *h = (H *)p->f156;
        q = *(Q4 *)((u8 *)h + 8);
        q.w = p->f912;
        h->s18(&q);
    }
    fn_80101744(&v, &p->v280);
    {
    f32 t1;
    f32 vy = v.y;
    f32 vx = v.x;
    f32 vz = v.z;
    *(volatile f32 *)&n.x = vy * lbl_8035FE10 - (t1 = vz * lbl_8035FDF8);
    *(volatile f32 *)&n.y = -(vx * lbl_8035FE10 - t1);
    n.z = vx * lbl_8035FDF8 - vy * lbl_8035FDF8;
    }
    fn_80101414(&p->v280, &n, *(volatile f32 *)&lbl_8035FE14);
    if (p->f396) {
        f32 c0, s0, d, len, r;
        fn_80101820(&p->v280);
        c0 = fn_800F030C(lbl_8035FE14);
        s0 = fn_800EFDA4(lbl_8035FE14);
        p->f396->s15(&s, 0, 0, 0, 0);
        t = p->v68;
        d = fn_80101590(&t, &s);
        {
            G *g = p->f396;
            f32 ex = g->v304.x;
            f32 ey = g->v304.y;
            f32 ez = g->v304.z;
            ex -= p->v280.x;
            ey -= p->v280.y;
            ez -= p->v280.z;
            Vec3 w;
            w.x = s.x + ex;
            w.y = s.y + ey;
            w.z = s.z + ez;
            len = Dist(&t, &w);
            {
                f32 e = len - d;
                f32 k = d / (Max(p) - e);
                ex *= k;
                ey *= k;
                ez *= k;
                s.x += ex;
                s.y += ey;
                s.z += ez;
            }
        }
        d = fn_80101590(&t, &s);
        {
            f32 m = lbl_8035FE30 * s0;
            f32 q = (lbl_8035FE2C * d) / (m * c0);
            if (q > lbl_8035FDF8) {
                f64 guess = __frsqrte((f64)q);
                guess = lbl_8035FE18 * guess * (lbl_8035FE20 - guess * guess * q);
                guess = lbl_8035FE18 * guess * (lbl_8035FE20 - guess * guess * q);
                guess = lbl_8035FE18 * guess * (lbl_8035FE20 - guess * guess * q);
                y = (f32)(q * guess);
                r = y;
            } else {
                r = q;
            }
        }
        if (r > Max(p)) r = Max(p);
        p->v280.x *= r;
        p->v280.y *= r;
        p->v280.z *= r;
    }
    p->v316 = p->v280;
    p->f888->s13();
    p->s14(lbl_8035FE34);
}

} /* extern "C" */
