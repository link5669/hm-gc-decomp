// fn_800515C4: schedule- and register-equivalent (schedequiv.txt). Saved wave-42 draft under
// `#pragma scheduling 7400`; 13 instructions of the Scale(d, k) block are in another order and three FP
// temporaries are renamed. 0.0f/1.0f are the shared pool constants lbl_8035DCA0/lbl_8035DCB0, read through
// *(f32 *)& casts where the draft had literals (plain extern reads there change the code).
#include "common.h"

extern "C" {

struct Vec3 { f32 x, y, z; };
struct M { u8 pad[120]; void *f120; };
struct R {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void s13(Vec3 *, Vec3 *, int, int, int);
    virtual void s14(Vec3 *, Vec3 *, Vec3 *, Vec3 *, int);
    u8 pad[152];
    M *f156;
};
struct GL { u8 pad[72]; R *f72; };
struct P {
    u8 pad[224];
    R *f224;
    u8 pad228[308];
    f32 *f536;
    f32 *f540;
    f32 *f544;
    f32 *f548;
    f32 *f552;
    f32 *f556;
    u8 pad560[24];
    f32 *f584;
    u8 pad588[36];
    f32 f624;
    f32 f628;
    s32 f632;
};
extern GL *lbl_8035B308;
extern f32 lbl_8035DCA0, lbl_8035DCB0, lbl_8035DD30, lbl_8035DD34;
extern f64 lbl_8035DD28;
extern char lbl_8035DCD0[8];
void fn_80072AC8(R *, Vec3 *);
f32 fn_80101590(const Vec3 *, const Vec3 *);
void fn_80101820(Vec3 *);
void fn_802402E0(P *);
P *fn_80242144(P *, int);
void fn_80242BC0(P *, void *, void *, int, f32 *, int);
double fn_800F045C(double);
void fn_80107F3C(void *, Vec3 *);

static inline f32 Dot(const Vec3 *a, const Vec3 *b) { return a->x * b->x + a->y * b->y + a->z * b->z; }

static inline void Cross(Vec3 *o, const Vec3 *a, const Vec3 *b)
{
    o->x = a->y * b->z - a->z * b->y;
    o->y = a->z * b->x - a->x * b->z;
    o->z = a->x * b->y - a->y * b->x;
}

static inline void Scale(Vec3 *v, f32 k) { f32 x = v->x, y = v->y, z = v->z; v->x = x * k; v->y = y * k; v->z = z * k; }


static inline f32 Acos(f32 x)
{
    if ((f32)__fabs(x) <= lbl_8035DD28) return fn_800F045C(x);
    if (x > (*(f32 *)&lbl_8035DCA0)) return (*(f32 *)&lbl_8035DCA0);
    return lbl_8035DD30;
}

#pragma push
#pragma scheduling 7400
void fn_800515C4(P *p, int a, int b, f32 dt)
{
    Vec3 cam;
    Vec3 pos;
    Vec3 d;
    Vec3 dn;
    Vec3 up;
    Vec3 side;
    Vec3 fw;
    Vec3 np;
    Vec3 v20;
    Vec3 sc;
    f32 sp;
    Vec3 h;
    fn_80072AC8(lbl_8035B308->f72, &cam);
    cam.z -= *p->f556;
    p->f224->s13(&pos, 0, 0, 0, 0);
    if (a) {
        p->f632 = 0;
        p->f624 = fn_80101590(&pos, &cam);
        p->f628 = p->f624;
    }
    {
        if (p->f628 <= lbl_8035DCA0) {
            p->f632 = 1;
            if (b) {
                fn_802402E0(p);
                return;
            }
            fn_80242BC0(fn_80242144(p, 0), lbl_8035DCD0, p->f224, 0, p->f552, 0);
            return;
        }
    }
    d.x = pos.x - cam.x;
    d.y = pos.y - cam.y;
    d.z = pos.z - cam.z;
    fn_80101820(&d);
    dn = d;
    fn_80101820(&dn);
    lbl_8035B308->f72->s13(0, &fw, 0, 0, 0);
    fw.z = lbl_8035DCA0;
    fn_80101820(&fw);
    h = d;
    if (b) {
        sp = *p->f584;
    } else {
        f32 t;
        h.z = (*(f32 *)&lbl_8035DCA0);
        f32 g = lbl_8035DD34 * Acos(Dot(&h, &fw));
        t = (g - *p->f544) / (*p->f548 - *p->f544);
        if (t < (*(f32 *)&lbl_8035DCA0)) t = (*(f32 *)&lbl_8035DCA0);
        if (t > (*(f32 *)&lbl_8035DCB0)) t = (*(f32 *)&lbl_8035DCB0);
        sp = t * (*p->f540 - *p->f536) + *p->f536;
    }
    p->f628 -= sp * dt;
    Scale(&d, p->f628);
    f32 o, ux, uy, dz, dy, dx; dy = dn.y; dz = dn.z; dx = dn.x;
    np.x = cam.x + d.x;
    np.y = cam.y + d.y;
    ((f32 *)&v20)[5] = cam.z + d.z;
    ux = *(f32 *)&lbl_8035DCA0; uy = lbl_8035DCA0; up.x = ux; ((f32 *)&side)[4] = uy; o = lbl_8035DCB0; up.z = o;
    side.x = dy * o - dz * uy; side.y = dz * ux - dx * o; side.z = dx * uy - dy * ux;
    fn_80101820(&side);
    Cross(&up, &side, &dn);
    fn_80101820(&up);
    if (b && a) p->f224->s14(0, &dn, &up, &side, 0);
    p->f224->s14(&np, 0, 0, 0, 0);
    if (!b) {
        f32 s = lbl_8035DCB0 - (p->f624 - p->f628) / p->f624;
        sc.z = sc.y = sc.x = s;
        { void *m = p->f224->f156->f120; if (m) fn_80107F3C(m, &sc); }
        p->f224->s13(&v20, 0, 0, 0, 0);
        v20.z = *p->f556 * (lbl_8035DCB0 - sc.z) + v20.z;
        p->f224->s14(&v20, 0, 0, 0, 0);
    }
}

#pragma pop

}
