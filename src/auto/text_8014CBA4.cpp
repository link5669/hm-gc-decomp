/* Functions from 0x8014CBA4 to 0x8014CC80, found by decomp-toolkit. */
#include "common.h"

extern "C" {

typedef struct {
    s32 v[4];
} Quad;

typedef struct {
    Quad q;
    f32 x;
    f32 y;
} QuadXY;

typedef struct {
    f32 x, y, z, w;
} Plane;

extern f32 lbl_803644E0;
extern f32 lbl_803644E4;

void fn_8014CBA4(QuadXY *__restrict dst, QuadXY *__restrict src) {
    dst->q.v[0] = src->q.v[0];
    dst->q.v[2] = src->q.v[2];
    dst->q.v[1] = src->q.v[1];
    dst->q.v[3] = src->q.v[3];
    dst->x = src->x;
    dst->y = src->y;
}

void fn_8014CBD8(QuadXY *p) {
    p->x = lbl_803644E0;
    p->y = lbl_803644E4;
}

/* QV=2.0p1 */
typedef struct {
    f32 x, y, z, w;
} Plane8014CBEC;

#pragma opt_propagation off
s32 fn_8014CBEC(Plane8014CBEC *planes, Plane8014CBEC *s) {
    Plane8014CBEC *end = planes + 6;
    f32 d;
    f32 py;
    f32 y;
    f32 px;
    f32 x;
    f32 pz;
    f32 z;
    f32 pw;
    f32 r;
    s32 mask = 0;
    s32 bit = 1;
    r = s->w;
    z = s->z;
    x = s->x;
    y = s->y;
    for (; planes < end; planes++) {
        py = planes->y;
        px = planes->x;
        pz = planes->z;
        pw = planes->w;
        d = y * py;
        d = x * px + d;
        d = z * pz + d;
        d = pw + d;
        if (d < -r) {
            return 0x40;
        }
        if (d < r) {
            mask |= bit;
        }
        bit <<= 1;
    }
    return mask ? mask : 0;
}
#pragma opt_propagation reset

} /* extern "C" */
