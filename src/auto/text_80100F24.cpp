// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_80363828;
extern f64 lbl_80363830;
extern f64 lbl_80363838;
extern f32 lbl_80363840;
extern f32 lbl_80363844;

typedef struct V80100F24 { f32 x, y, z; } V80100F24;

void fn_80100F24(V80100F24 *a, const V80100F24 *n) {
    const V80100F24 *ca = a;
    f32 len;
    f32 x, y, z;
    f32 d;
    f32 inv;
    volatile f32 vy;
    f64 guess;
    len = n->x * n->x + n->y * n->y + n->z * n->z;
    if (len > lbl_80363828) {
        guess = __frsqrte((f64)len);
        guess = lbl_80363830 * guess * (lbl_80363838 - guess * guess * len);
        guess = lbl_80363830 * guess * (lbl_80363838 - guess * guess * len);
        guess = lbl_80363830 * guess * (lbl_80363838 - guess * guess * len);
        vy = (f32)(len * guess);
        len = vy;
    }
    if (len <= lbl_80363840) {
        z = y = lbl_80363828;
        x = lbl_80363844;
    } else {
        inv = lbl_80363844 / len;
        x = n->x * inv;
        y = n->y * inv;
        z = n->z * inv;
    }
    d = ca->x * x + ca->y * y + ca->z * z;
    x *= d;
    y *= d;
    z *= d;
    a->x -= x;
    a->y -= y;
    a->z -= z;
}

} /* extern "C" */
