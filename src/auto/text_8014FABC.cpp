#include "common.h"
extern "C" {
struct Vec { f32 x, y, z; };
struct Quat { f32 x, y, z, w; };
extern f32 lbl_8036453C;
extern f32 lbl_80364544;
extern f32 lbl_80364558;
extern const f64 lbl_80364548;
extern const f64 lbl_80364550;

#define SQ(x) if (x > *(volatile f32 *)&lbl_80364544) { \
        f64 guess; \
        volatile f32 y; \
        guess = __frsqrte((f64)x); \
        guess = lbl_80364548 * guess * (lbl_80364550 - guess * guess * x); \
        guess = lbl_80364548 * guess * (lbl_80364550 - guess * guess * x); \
        guess = lbl_80364548 * guess * (lbl_80364550 - guess * guess * x); \
        y = (f32)(x * guess); \
        x = y; \
    }

#define SQ1(x) if (x > lbl_80364544) { \
        f64 guess; \
        volatile f32 y; \
        guess = __frsqrte((f64)x); \
        guess = lbl_80364548 * guess * (lbl_80364550 - guess * guess * x); \
        guess = lbl_80364548 * guess * (lbl_80364550 - guess * guess * x); \
        guess = lbl_80364548 * guess * (lbl_80364550 - guess * guess * x); \
        y = (f32)(x * guess); \
        x = y; \
    }

void fn_8014FABC(f32 m[3][4], Quat *q) {
    f32 s = m[0][0] + m[1][1] + m[2][2];
    int i;
    if (s > lbl_80364544) {
        s = lbl_8036453C + s;
        SQ1(s);
        {
            f32 d0 = m[1][2] - m[2][1];
            f32 d1 = m[2][0] - m[0][2];
            f32 d2;
            q->w = lbl_80364558 * s;
            d2 = *(volatile f32 *)&m[0][1] - m[1][0];
            s = *(volatile f32 *)&lbl_80364558 / s;
            q->x = s * d0;
            q->y = s * d1;
            q->z = s * d2;
        }
        return;
    }
    i = 0;
    if (m[1][1] > m[0][0]) i = 1;
    if (m[2][2] > m[i][i]) i = 2;
    switch (i) {
    case 0:
        s = lbl_8036453C + (m[0][0] - (m[1][1] + m[2][2]));
        SQ(s);
        {
            f32 d0 = m[1][2] - m[2][1];
            f32 d1 = m[0][1] + m[1][0];
            f32 d2;
            q->x = lbl_80364558 * s;
            d2 = *(volatile f32 *)&m[0][2] + m[2][0];
            s = *(volatile f32 *)&lbl_80364558 / s;
            q->w = s * d0;
            q->y = s * d1;
            q->z = s * d2;
        }
        break;
    case 1:
        s = lbl_8036453C + (m[1][1] - (m[2][2] + m[0][0]));
        SQ(s);
        {
            f32 d0 = m[2][0] - m[0][2];
            f32 d1 = m[1][2] + m[2][1];
            f32 d2;
            q->y = lbl_80364558 * s;
            d2 = *(volatile f32 *)&m[1][0] + m[0][1];
            s = *(volatile f32 *)&lbl_80364558 / s;
            q->w = s * d0;
            q->z = s * d1;
            q->x = s * d2;
        }
        break;
    case 2:
        s = lbl_8036453C + (m[2][2] - (m[0][0] + m[1][1]));
        SQ(s);
        {
            f32 d0 = m[0][1] - m[1][0];
            f32 d1 = m[2][0] + m[0][2];
            f32 d2;
            q->z = lbl_80364558 * s;
            d2 = *(volatile f32 *)&m[2][1] + m[1][2];
            s = *(volatile f32 *)&lbl_80364558 / s;
            q->w = s * d0;
            q->x = s * d1;
            q->y = s * d2;
        }
        break;
    }
}
}
