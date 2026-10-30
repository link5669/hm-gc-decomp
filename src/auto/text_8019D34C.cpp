// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct Vec { f32 x, y, z; };
struct Arr { u8 pad[36]; u8 *items; };
struct B { u8 pad[104]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void *v4(); u8 pad2[168 - 108]; Arr *arr; };
struct A { u8 pad[4]; u32 idx; u8 pad2[20]; Vec pos; f32 w; };
struct C { u32 type; u8 pad[20]; virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual f32 c4(s32, A *, B *, Vec *, f32 *, f32 *); Vec pos; f32 w; };
struct M33 { f32 m[3][3]; };
extern M33 lbl_80330228;
extern Vec lbl_8033024C;
extern f32 lbl_80364CE0;
extern const f32 lbl_80364CE4;
void fn_8017BCCC(A *a, C *c);
f32 fn_80101664(Vec *v);
void fn_80103F78(void *m, Vec *in, Vec *out, s32 n);
void fn_80101820(Vec *v);

static inline void mulv(M33 *m, Vec *v, Vec *o) {
    f32 z, y, x;
    x = v->x * m->m[0][0]; y = v->x * m->m[0][1]; z = v->x * m->m[0][2];
    x += v->y * m->m[1][0]; y += v->y * m->m[1][1]; z += v->y * m->m[1][2];
    x += v->z * m->m[2][0]; y += v->z * m->m[2][1]; z += v->z * m->m[2][2];
    o->x = x; o->y = y; o->z = z;
}
static inline void post(A *a, B *b, Vec *tmp, Vec *out) {
    if (a->idx == 0) {
        void *m = b->v4();
        if (m) fn_80103F78(m, tmp, out, 1);
        else *out = *tmp;
    } else {
        fn_80103F78(b->arr->items + (a->idx - 1) * 40, tmp, out, 1);
    }
    fn_80101820(out);
}

f32 fn_8019D34C(A *a, B *b, C *c, s32 p4, Vec *out, f32 *p8, f32 *p9) {
    if (c->type == 1) {
        f32 r;
        fn_8017BCCC(a, c);
        Vec d;
        d.x = lbl_8033024C.x - a->pos.x;
        d.y = lbl_8033024C.y - a->pos.y;
        d.z = lbl_8033024C.z - a->pos.z;
        Vec rv;
        mulv(&lbl_80330228, &c->pos, &rv);
        d.x = d.x + rv.x;
        d.y = d.y + rv.y;
        d.z = d.z + rv.z;
        r = fn_80101664(&d) - a->w - c->w;
        *p8 = lbl_80364CE0 * a->w;
        *p9 = lbl_80364CE0 * c->w;
        post(a, b, &d, out);
        if (lbl_8033024C.x * d.x + lbl_8033024C.y * d.y + lbl_8033024C.z * d.z < lbl_80364CE4) {
            out->x = -out->x; out->y = -out->y; out->z = -out->z;
        }
        return r;
    } else if (c->type == 0) {
        f32 r = c->c4(p4, a, b, out, p9, p8);
        out->x = -out->x; out->y = -out->y; out->z = -out->z;
        return r;
    }
    return lbl_80364CE4;
}

} /* extern "C" */
