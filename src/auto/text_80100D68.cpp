// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct Vec2_80100D68 { f32 x, y; };
extern f32 lbl_80363808;
extern f64 lbl_80363810;
extern f64 lbl_80363818;
extern f32 lbl_80363820;
extern f32 lbl_80363824;

void fn_80100D68(Vec2_80100D68 *v) {
    f32 len;
    len = v->x * v->x + v->y * v->y;
    if (len > lbl_80363808) {
        f64 guess;
        volatile f32 y;
        guess = __frsqrte((f64)len);
        guess = lbl_80363810 * guess * (lbl_80363818 - guess * guess * len);
        guess = lbl_80363810 * guess * (lbl_80363818 - guess * guess * len);
        guess = lbl_80363810 * guess * (lbl_80363818 - guess * guess * len);
        y = (f32)(len * guess);
        len = y;
    }
    if (len <= lbl_80363820) {
        v->x = lbl_80363824;
        v->y = lbl_80363808;
    } else {
        f32 inv = lbl_80363824 / len;
        v->x *= inv;
        v->y *= inv;
    }
}

} /* extern "C" */
