#include "common.h"

extern "C" {
struct V3 {
    f32 x, y, z;
    V3() {}
    V3(f32 a, f32 b, f32 c) { x = a; y = b; z = c; }
};
static inline V3 operator-(const V3 &a, const V3 &b) { return V3(a.x - b.x, a.y - b.y, a.z - b.z); }
static inline V3 operator+(const V3 &a, const V3 &b) { return V3(a.x + b.x, a.y + b.y, a.z + b.z); }
struct O {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void s11(O *);
    virtual void v12(); virtual void s13(); virtual void s14(f32);
    virtual void s15(V3 *, int, int, int, int);
    u8 pad4[64];
    V3 pos44;
    u8 pad50[200];
    V3 v118;
    u8 pad124[12];
    V3 v130;
    V3 v13C;
    u8 pad148[68];
    O *p18C;
    u8 pad190[228];
    f32 *p274;
    u8 pad278[256];
    O *p378;
    s32 i37C;
};
extern f32 lbl_8035FEB8, lbl_8035FED4, lbl_8035FED8, lbl_8035FEE8, lbl_8035FEEC, lbl_8035FEF0, lbl_8035FEF4;
extern f64 lbl_8035FEC0, lbl_8035FEE0;
extern u8 lbl_8035FECC[8];
extern char lbl_80298EC8[];
void fn_8005D9EC(O *, int, int, int, int, int, f32, f32);
void *fn_8023BC90(void *);
O *fn_8023B8FC(void *, const char *, s32);
void fn_80101744(V3 *, V3 *);
void fn_80101414(V3 *, V3 *, f32);
void fn_80101820(V3 *);
f32 fn_80101590(V3 *, V3 *);
double fn_800F030C(double);
double fn_800EFDA4(double);

static inline f32 Sq(f32 x) {
    if (x > lbl_8035FEB8) {
        const f64 _half = lbl_8035FEC0;
        const f64 _three = lbl_8035FEE0;
        volatile f32 y;
        f64 g = __frsqrte((f64)x);
        g = _half * g * (_three - g * g * x);
        g = _half * g * (_three - g * g * x);
        g = _half * g * (_three - g * g * x);
        y = x * g;
        return y;
    }
    return x;
}
static inline void Cross(V3 *o, const V3 *a, const V3 *b) {
    f32 x = a->y * b->z - a->z * b->y;
    f32 y = a->z * b->x - a->x * b->z;
    f32 z = a->x * b->y - a->y * b->x;
    o->x = x; o->y = y; o->z = z;
}
static inline f32 Mul(f32 a, f32 b) { return a * b; }
static inline void Scale(V3 *v, f32 k) { v->x *= k; v->y *= k; v->z *= k; }
static inline void Sub(V3 *o, const V3 *a, const V3 *b) { o->x = a->x - b->x; o->y = a->y - b->y; o->z = a->z - b->z; }
static inline void Sub2(V3 *o, const V3 *a, const V3 *b) { f32 x = a->x - b->x, y = a->y - b->y, z = a->z - b->z; o->x = x; o->y = y; o->z = z; }
static inline V3 *Pos(O *q) { return &q->v130; }
static inline V3 CrossV(const V3 &a, const V3 &b) { return V3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
static inline V3 CrossW(const V3 &a, const V3 &b) { V3 r; r.x = a.y * b.z - b.y * a.z; r.y = b.x * a.z - a.x * b.z; r.z = a.x * b.y - a.y * b.x; return r; }
static inline f32 Lim(O *p) { return p->p274 ? *p->p274 : lbl_8035FEE8; }

static inline f32 Clamp(f32 s, O *p) {
    if (s > Lim(p)) return Lim(p);
    return s;
}
void fn_80087E20(O *p, int a, int b, int c, int d, int e, f32 x, f32 y) {
    fn_8005D9EC(p, a, 0, c, d, e, x, y);
    p->i37C = 0;
    if (p->p378 == 0) {
        p->p378 = fn_8023B8FC(fn_8023BC90(lbl_8035FECC), lbl_80298EC8, -1);
        p->p378->s11(p);
    }
    {
        V3 ax, t;
        fn_80101744(&t, &p->v118);
        {
            f32 t1;
            f32 ty = t.y;
            f32 tx = t.x;
            f32 tz = t.z;
            *(volatile f32 *)&ax.x = ty * lbl_8035FED4 - (t1 = tz * lbl_8035FEB8);
            *(volatile f32 *)&ax.y = t1 - tx * lbl_8035FED4;
            ax.z = tx * lbl_8035FEB8 - ty * lbl_8035FEB8;
        }
        fn_80101414(&p->v118, &ax, *(volatile f32 *)&lbl_8035FED8);
    }
    if (p->p18C) {
        f32 cs, sn, dist, len, r, s;
        V3 dv, ps, tg;
        fn_80101820(&p->v118);
        cs = fn_800F030C(lbl_8035FED8);
        sn = fn_800EFDA4(lbl_8035FED8);
        p->p18C->s15(&tg, 0, 0, 0, 0);
        ps = p->pos44;
        dist = fn_80101590(&ps, &tg);
        dv = p->p18C->v130; dv.x -= p->v118.x; dv.y -= p->v118.y; dv.z -= p->v118.z;
        {
            f32 ex = tg.x + dv.x - ps.x;
            f32 ey = tg.y + dv.y - ps.y;
            f32 ez = tg.z + dv.z - ps.z;
            len = Sq(ex * ex + ey * ey + ez * ez);
        }
        {
            f32 over = len - dist;
            Scale(&dv, dist / (Lim(p) - over));
        }
        tg.x += dv.x;
        tg.y += dv.y;
        tg.z += dv.z;
        {
            f32 d2 = fn_80101590(&ps, &tg);
            f32 q = (lbl_8035FEEC * d2) / Mul(lbl_8035FEF0 * sn, cs);
            if (q > lbl_8035FEB8) {
                volatile f32 y;
                f64 g = __frsqrte((f64)q);
                g = lbl_8035FEC0 * g * (lbl_8035FEE0 - g * g * q);
                g = lbl_8035FEC0 * g * (lbl_8035FEE0 - g * g * q);
                g = lbl_8035FEC0 * g * (lbl_8035FEE0 - g * g * q);
                y = q * g;
                s = y;
            } else {
                s = q;
            }
            if (s > Lim(p)) s = Lim(p);
        }
        p->v118.x *= s;
        p->v118.y *= s;
        p->v118.z *= s;
    }
    p->v13C = p->v118;
    p->p378->s13();
    p->s14(lbl_8035FEF4);
}
}
