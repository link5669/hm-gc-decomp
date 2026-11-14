#include "common.h"

extern "C" {

struct Vec3 { f32 x, y, z; };
struct V3 { u32 v[3]; };
struct F { u32 a, b, c; F(const F &o) { u32 x = o.a, y = o.b, z = o.c; *(volatile u32 *)&a = x; *(volatile u32 *)&b = y; *(volatile u32 *)&c = z; } };
struct R {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void s13(Vec3 *, Vec3 *, int, int, int);
    virtual void s14(Vec3 *, Vec3 *, Vec3 *, Vec3 *, int);
    u8 pad[1244];
    s32 f4E0;
    u8 pad2[1804 - 1252];
    s32 f70C;
    u8 pad3[4];
    f32 f714;
};
struct P {
    u8 pad0[224];
    R *fE0;
    u8 padE4[52];
    R *f118;
    u8 pad11C[4];
    s32 f120;
    s32 f124;
    u8 pad128[4];
    s32 f12C;
    u8 pad130[8];
    f32 *f138;
    u8 pad13C[4];
    f32 f140;
    f32 *f144;
    f32 *f148;
    f32 *f14C;
    f32 *f150;
    f32 *f154;
    u32 *f158;
    void *f15C;
    void *f160;
    u8 pad164[4];
    f32 *f168;
    u8 pad16C[12];
    Vec3 f178;
    u8 f184[16];
    s32 *f194;
    u8 pad198[12];
    s32 *f1A4;
    u8 pad1A8[4];
    f32 f1AC;
    u8 pad1B0[12];
    s32 f1BC;
    s32 f1C0;
    s32 f1C4;
};

extern volatile f32 lbl_8035DF6C;
extern f32 lbl_8035DFE4, lbl_8035DFE8;
extern volatile f32 lbl_8035DFEC;
extern f64 lbl_8035DFF0;
extern u32 lbl_8035DF58;
extern char lbl_8035DEC8[7];
int rand(void);
void fn_802494A4(P *, int);
void fn_80107244(void *, Vec3 *);
int fn_80264E0C(Vec3 *, Vec3 *, int, int, int, int, int, int, int, int, int, int, int, int, int);
void fn_8023F5E8(P *, R *);
f32 fn_80101664(Vec3 *);
void fn_80101820(Vec3 *);
f32 fn_8023C1BC(void *, f32);
void fn_80241DD0(P *, char *, int, int, int, int);
void fn_80071E34(R *, Vec3 *);
void fn_80053D9C(P *, F, f32);
double fn_800EFDA4(double);
void fn_8023FE08(P *, f32);

static inline void Sub(Vec3 *o, const Vec3 *a, const Vec3 *b)
{
    o->x = a->x - b->x;
    o->y = a->y - b->y;
    o->z = a->z - b->z;
}

static inline void SubV(Vec3 *o, const Vec3 *a, const Vec3 *b)
{
    *(volatile f32 *)&o->x = a->x - b->x;
    *(volatile f32 *)&o->y = a->y - b->y;
    *(volatile f32 *)&o->z = a->z - b->z;
}

static inline int Has(s32 *q)
{
    int r = 0;
    if (q && *q) r = 1;
    return r;
}

static inline void Fail(P *p, int st)
{
    if (p->f1BC == 0) {
        fn_802494A4(p, st);
        return;
    }
    if (p->f158) *p->f158 &= ~0x800;
    p->f12C = 0;
    if (p->f158) *p->f158 |= lbl_8035DF58;
    p->f140 = lbl_8035DF6C;
    p->f120 = 1;
    p->f1C0 = 0;
}

void fn_80053430(P *p, f32 dt)
{
    Vec3 a, b, d, e, g, h, k, q, s, r, w, x;
    if (p->f120) {
        f32 len;
        if (p->f1C0 == 0 && p->f118->f4E0 == 1 && *p->f1A4 > (s32)((u32)rand() % 100)) {
            fn_802494A4(p, 11);
            return;
        }
        p->f1C0 = p->f118->f4E0;
        fn_80107244(p->f15C, &a);
        fn_80107244(p->f160, &b);
        d.x = b.x - a.x;
        d.y = b.y - a.y;
        d.z = b.z - a.z;
        if (fn_80264E0C(&b, &a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)) {
            fn_8023F5E8(p, p->f118);
            p->f118->s13(&p->f178, 0, 0, 0, 0);
            p->f120 = 0;
            fn_802494A4(p, 11);
            return;
        }
        len = fn_80101664(&d);
        d.z = lbl_8035DF6C;
        if (Has(p->f194) && p->f168) {
            f32 l2, mx;
            p->f118->s13(&a, 0, 0, 0, 0);
            SubV(&e, &a, &b);
            ((f32 *)&k)[11] = lbl_8035DF6C;
            l2 = fn_80101664(&e);
            mx = *p->f168;
            if (l2 > mx) {
                a.x = -l2 * e.x + a.x;
                a.y = -l2 * e.y + a.y;
                a.z = -l2 * e.z + a.z;
                a.x = mx * e.x + a.x;
                a.y = mx * e.y + a.y;
                a.z = mx * e.z + a.z;
            }
            p->f118->s14(&a, 0, 0, 0, 0);
        } else if (p->f168 && len > *p->f168) {
            fn_802494A4(p, 10);
            if (p->f158) *p->f158 &= ~0x800;
            p->f120 = 0;
            return;
        }
        p->f140 += *p->f144 * dt / *p->f14C;
        if (p->f140 > *p->f144) p->f140 = *p->f144;
        {
            f32 s = dt * (p->f140 + fn_8023C1BC(p->f184, dt));
            d.x *= s;
            d.y *= s;
            d.z *= s;
        }
        p->f118->s13(&a, 0, 0, 0, 0);
        a.x += d.x;
        a.y += d.y;
        a.z += d.z;
        p->f118->f70C++;
        p->f118->f714 = *p->f148;
        if (len > *p->f138) {
            p->f118->s14(&a, 0, 0, 0, 0);
        } else {
            fn_80241DD0(p, lbl_8035DEC8, 0, 0, 0, 0);
        }
    } else if (p->f124 && (f32)p->f1C4 < *p->f150) {
        {
            f32 s;
            p->fE0->s13(&g, 0, 0, 0, 0);
            p->f118->s13(&h, 0, 0, 0, 0);
            SubV(&k, &h, &g);
            ((f32 *)&q)[5] = lbl_8035DF6C;
            fn_80101820(&k);
            s = *p->f154 * dt;
            k.x *= s;
            k.y *= s;
            k.z *= s;
            fn_80071E34(p->f118, &k);
            p->f1C4 = *p->f154 * dt + (f32)p->f1C4;
        }
    } else if (p->f12C) {
        f32 l, t;
        p->f140 = lbl_8035DF6C;
        fn_80107244(p->f160, &q);
        r.x = p->f178.x - q.x;
        r.y = p->f178.y - q.y;
        r.z = p->f178.z - q.z;
        l = lbl_8035DFE4 + fn_80101664(&r);
        p->f1AC += dt;
        t = lbl_8035DFE8 * p->f1AC;
        if (t > l) {
            Fail(p, 11);
        } else {
                        f32 l3;
            f32 cs;
            r.x *= t;
            r.y *= t;
            r.z *= t;
            s.x = q.x + r.x;
            s.y = q.y + r.y;
            s.z = q.z + r.z;
            fn_80053D9C(p, *(F *)&s, lbl_8035DFEC);
            if (fn_80264E0C(&q, &s, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)) {
                Fail(p, 11);
            } else {
                fn_80107244(p->f15C, &w);
                x.x = w.x - q.x;
                x.y = w.y - q.y;
                x.z = w.z - q.z;
                l3 = fn_80101664(&x);
                fn_80101820(&r);
                cs = fn_800EFDA4(lbl_8035DFF0);
                if (x.x * r.x + x.y * r.y + x.z * r.z > cs && l3 < t) {
                    Fail(p, 5);
                }
            }
        }
    } else {
        p->f140 = lbl_8035DF6C;
    }
    fn_8023FE08(p, dt);
}

} /* extern "C" */
