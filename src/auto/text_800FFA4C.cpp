#include "common.h"
extern "C" {
struct Vec { f32 x, y, z; };
struct Quat { f32 x, y, z, w; };
extern f32 lbl_803637A8;
extern f32 lbl_803637A4;
extern f32 lbl_803637C0;
extern const f64 lbl_803637B0;
extern const f64 lbl_803637B8;

#define SQ(x) if (x > *(volatile f32 *)&lbl_803637A4) { \
        f64 guess; \
        volatile f32 y; \
        guess = __frsqrte((f64)x); \
        guess = lbl_803637B0 * guess * (lbl_803637B8 - guess * guess * x); \
        guess = lbl_803637B0 * guess * (lbl_803637B8 - guess * guess * x); \
        guess = lbl_803637B0 * guess * (lbl_803637B8 - guess * guess * x); \
        y = (f32)(x * guess); \
        x = y; \
    }

#define SQ1(x) if (x > lbl_803637A4) { \
        f64 guess; \
        volatile f32 y; \
        guess = __frsqrte((f64)x); \
        guess = lbl_803637B0 * guess * (lbl_803637B8 - guess * guess * x); \
        guess = lbl_803637B0 * guess * (lbl_803637B8 - guess * guess * x); \
        guess = lbl_803637B0 * guess * (lbl_803637B8 - guess * guess * x); \
        y = (f32)(x * guess); \
        x = y; \
    }

void fn_800FFA4C(Quat *q, Vec *a, Vec *b, Vec *c) {
    f32 xx = a->x;
    f32 yy = b->y;
    f32 zz = c->z;
    f32 s = xx + yy + zz;
    int i;
    if (s > lbl_803637A4) {
        s = lbl_803637A8 + s;
        SQ1(s);
        {
            f32 d0 = c->y - b->z;
            f32 d1 = a->z - c->x;
            f32 d2;
            q->w = lbl_803637C0 * s;
            d2 = *(volatile f32 *)&b->x - a->y;
            s = *(volatile f32 *)&lbl_803637C0 / s;
            q->x = s * d0;
            q->y = s * d1;
            q->z = s * d2;
        }
        return;
    }
    i = 0;
    if (yy > xx) {
        i = 1;
        if (zz > yy) i = 2;
    } else if (zz > xx) i = 2;
    switch (i) {
    case 0:
        s = lbl_803637A8 + (xx - (yy + zz));
        SQ(s);
        {
            f32 d0 = c->y - b->z;
            f32 d1 = b->x + a->y;
            f32 d2;
            q->x = lbl_803637C0 * s;
            d2 = *(volatile f32 *)&c->x + a->z;
            s = *(volatile f32 *)&lbl_803637C0 / s;
            q->w = s * d0;
            q->y = s * d1;
            q->z = s * d2;
        }
        break;
    case 1:
        s = lbl_803637A8 + (yy - (zz + xx));
        SQ(s);
        {
            f32 d0 = a->z - c->x;
            f32 d1 = c->y + b->z;
            f32 d2;
            q->y = lbl_803637C0 * s;
            d2 = *(volatile f32 *)&a->y + b->x;
            s = *(volatile f32 *)&lbl_803637C0 / s;
            q->w = s * d0;
            q->z = s * d1;
            q->x = s * d2;
        }
        break;
    case 2:
        s = lbl_803637A8 + (zz - (xx + yy));
        SQ(s);
        {
            f32 d0 = b->x - a->y;
            f32 d1 = a->z + c->x;
            f32 d2;
            q->z = lbl_803637C0 * s;
            d2 = *(volatile f32 *)&b->z + c->y;
            s = *(volatile f32 *)&lbl_803637C0 / s;
            q->w = s * d0;
            q->x = s * d1;
            q->y = s * d2;
        }
        break;
    }
}
}
