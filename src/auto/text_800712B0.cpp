// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Vec { f32 x, y, z; };
struct T {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void get(void *, Vec *, Vec *, void *, void *);
    u8 pad[316 - 4];
    Vec pos;
};
struct Obj { u8 pad[224]; T *f224; T *f228; };
extern "C" {
void fn_80100F24(Vec *, Vec *);
void fn_80101820(Vec *);

extern f32 lbl_8035F340;
extern f32 lbl_8035F344;
static inline void VecScale(Vec *v, f32 s) { v->x *= s; v->y *= s; v->z *= s; }
static inline void VecAddScaled(Vec *d, f32 s, const Vec *a) { d->x += s * a->x; d->y += s * a->y; d->z += s * a->z; }
static inline void VecCopy(Vec *d, const Vec *s) { d->x = s->x; d->y = s->y; d->z = s->z; }
void fn_800712B0(Obj *o) {
    Vec v20;
    Vec v8;
    if (o->f228 != 0) {
        o->f228->get(0, &v20, 0, 0, 0);
        o->f224->get(0, 0, &v8, 0, 0);
        fn_80100F24(&v20, &v8);
        fn_80101820(&v20);
        { f32 az, ay, ax, k, z, y, x, s; s = lbl_8035F340; x = v20.x * s; y = v20.y * s; z = v20.z * s; ax = v8.x; ay = v8.y; az = v8.z; *(volatile f32 *)&v20.x = x; *(volatile f32 *)&v20.y = y; *(volatile f32 *)&v20.z = z; k = *(volatile f32 *)&lbl_8035F344; v20.x = k * ax + x; v20.y = k * ay + y; v20.z = k * az + z; }
        
        VecCopy(&o->f224->pos, &v20);
    }
}

} /* extern "C" */
