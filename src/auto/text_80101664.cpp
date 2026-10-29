// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct V_80101664 { f32 x, y, z; };
extern f32 lbl_80363828;
extern f64 lbl_80363830;
extern f64 lbl_80363838;
extern f32 lbl_80363840;
extern f32 lbl_80363844;
f32 fn_80101664(V_80101664 *v) {
    f32 d;
    f32 inv;
    volatile f32 y;
    f64 guess;
    d = v->x * v->x + v->y * v->y + v->z * v->z;
    if (d > lbl_80363828) {
        guess = __frsqrte((f64)d);
        guess = lbl_80363830 * guess * (lbl_80363838 - guess * guess * d);
        guess = lbl_80363830 * guess * (lbl_80363838 - guess * guess * d);
        guess = lbl_80363830 * guess * (lbl_80363838 - guess * guess * d);
        y = (f32)(d * guess);
        d = y;
    }
    if (d <= lbl_80363840) {
        v->x = lbl_80363844;
        v->y = lbl_80363828;
        v->z = lbl_80363828;
        return lbl_80363828;
    }
    inv = lbl_80363844 / d;
    v->x *= inv;
    v->y *= inv;
    v->z *= inv;
    return d;
}

} /* extern "C" */
