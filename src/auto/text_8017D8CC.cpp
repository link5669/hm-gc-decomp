// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct Vec { f32 x, y, z; };
struct Q { f32 x, y, z, w; };
struct A { u8 pad[4]; u32 idx; u8 pad2[20]; Vec pos; };
struct C { u32 type; u8 pad[24]; Vec pos; f32 w; };
struct M33 { f32 m[3][3]; };
extern M33 lbl_80330228;
extern Vec lbl_8033024C;
extern void *lbl_8035AD88;
extern u32 lbl_8035AD80;
extern u32 lbl_8035AD84;
void fn_8017BCCC(A *a, C *c);
s32 fn_800FF140(Vec *a, Vec *b, M33 *m, Vec *l);
s32 fn_800FEFC8(Vec *a, Q *q);
void fn_8017B938(void *p, A *a, C *c, u32 x, u32 y);
void fn_80100CF4(Q *q);

static inline void mulv(M33 *m, Vec *v, Vec *o) {
    f32 z, y, x;
    x = v->x * m->m[0][0]; y = v->x * m->m[0][1]; z = v->x * m->m[0][2];
    x += v->y * m->m[1][0]; y += v->y * m->m[1][1]; z += v->y * m->m[1][2];
    x += v->z * m->m[2][0]; y += v->z * m->m[2][1]; z += v->z * m->m[2][2];
    o->x = x; o->y = y; o->z = z;
}

s32 fn_8017D8CC(A *a, C *c) {
    if (c->type == 0) {
        fn_8017BCCC(a, c);
        if (fn_800FF140(&a->pos, &c->pos, &lbl_80330228, &lbl_8033024C)) {
            if (lbl_8035AD88) fn_8017B938(lbl_8035AD88, a, c, lbl_8035AD80, lbl_8035AD84);
            return 1;
        }
        return 0;
    } else if (c->type == 1) {
        Q q;
        fn_80100CF4(&q);
        fn_8017BCCC(a, c);
        Vec d;
        d.x = lbl_8033024C.x - a->pos.x;
        d.y = lbl_8033024C.y - a->pos.y;
        d.z = lbl_8033024C.z - a->pos.z;
        Vec rv;
        mulv(&lbl_80330228, &c->pos, &rv);
        q.x = d.x + rv.x;
        q.y = d.y + rv.y;
        q.z = d.z + rv.z;
        q.w = c->w;
        if (fn_800FEFC8(&a->pos, &q)) {
            if (lbl_8035AD88) fn_8017B938(lbl_8035AD88, a, c, lbl_8035AD80, lbl_8035AD84);
            return 1;
        }
        return 0;
    }
    return c->type == 4 ? 1 : 0;
}

} /* extern "C" */
