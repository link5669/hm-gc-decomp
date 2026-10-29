// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_80363828;
extern f64 lbl_80363830;
extern f64 lbl_80363838;

f32 fn_80101590(const f32 *a, const f32 *b) {
    f32 dx = b[0] - a[0];
    f32 dy = b[1] - a[1];
    f32 dz = b[2] - a[2];
    f32 d = dx * dx + dy * dy + dz * dz;
    volatile f32 y;
    f64 guess;
    if (d > lbl_80363828) {
        guess = __frsqrte((f64)d);
        guess = lbl_80363830 * guess * (lbl_80363838 - guess * guess * d);
        guess = lbl_80363830 * guess * (lbl_80363838 - guess * guess * d);
        guess = lbl_80363830 * guess * (lbl_80363838 - guess * guess * d);
        y = (f32)(d * guess);
        return y;
    }
    return d;
}

} /* extern "C" */
