// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct V3 { f32 x, y, z; };
extern "C" {
extern f32 lbl_803600A4;
extern f64 lbl_803600A8;
extern f64 lbl_803600B0;
extern f32 lbl_803600B8;
}
inline f32 Sq(f32 x) {
    volatile f32 y;
    f64 g = __frsqrte(x);
    g = lbl_803600A8 * g * (lbl_803600B0 - g * g * x);
    g = lbl_803600A8 * g * (lbl_803600B0 - g * g * x);
    g = lbl_803600A8 * g * (lbl_803600B0 - g * g * x);
    y = x * g;
    return y;
}
struct Ob { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void get(V3 *a, V3 *b, s32, s32, s32); };
struct G { u8 pad[72]; Ob *o; };
struct T { u8 pad[224]; Ob *f224; u8 pad2[280 - 228]; Ob *f280; f32 *f284; f32 *f288; f32 *f292; s32 f296; s32 f300; u8 f304[1]; };
extern "C" {
extern G *lbl_8035B308;
f32 fn_8023C1BC(void *o, f32 dt);
void fn_80071E34(Ob *o, V3 *v);
void fn_8023FE08(T *t, f32 dt);

static inline f32 dist(V3 *b, V3 *a) {
    f32 dx = b->x - a->x, dy = b->y - a->y, dz = b->z - a->z;
    f32 d = dx * dx + dy * dy + dz * dz;
    if (d > lbl_803600A4) d = Sq(d);
    return d;
}
void fn_8008AB20(T *t, f32 dt) {
    if (t->f296 && t->f300) {
        V3 a, c, b;
        f32 d;
        f32 r0;
        if (!t->f280) t->f280 = lbl_8035B308->o;
        t->f280->get(&a, 0, 0, 0, 0);
        t->f224->get(&b, &c, 0, 0, 0);
        d = dist(&b, &a);
        r0 = *t->f288;
        if (d < r0) {
            V3 v; v.x = c.x; v.y = c.y; v.z = c.z;
            f32 s = dt * (*t->f284 + fn_8023C1BC(t->f304, dt));
            v.x *= s; v.y *= s; v.z *= s;
            fn_80071E34(t->f280, &v);
        } else {
            f32 r1 = *t->f292;
            if (d < r0 + r1) {
                V3 v; v.x = c.x; v.y = c.y; v.z = c.z;
                f32 s = dt * ((lbl_803600B8 - (d - r0) / r1) * (*t->f284 + fn_8023C1BC(t->f304, dt)));
                v.x *= s; v.y *= s; v.z *= s;
                fn_80071E34(t->f280, &v);
            }
        }
    }
    fn_8023FE08(t, dt);
}

} /* extern "C" */
