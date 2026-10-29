// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_80365EFC;
extern f64 lbl_80365F28;
extern f64 lbl_80365F30;
extern char lbl_80365F6C[5];
extern char lbl_80365F74[5];
extern char lbl_802A8A94[];
void fn_800F6E88(void *, void *);
void fn_80241DD0(void *, void *, void *, void *, void *, void *);

void fn_80238404(u8 *self, u8 *other, u8 *c) {
    f32 ax, ay, az;
    f32 s;
    f32 bx, by, bz;
    f32 dx, dy, dz;
    f32 d;
    f64 guess;
    volatile f32 v;
    char buf[8];
    if (other != 0 && *(void **)(self + 524) != 0 && *(u8 **)(self + 564) != other) {
        ax = *(f32 *)(other + 280);
        ay = *(f32 *)(other + 284);
        az = *(f32 *)(other + 288);
        s = *(f32 **)(other + 444) != 0 ? **(f32 **)(other + 444) : lbl_80365EFC;
        ax *= s;
        ay *= s;
        az *= s;
        s = *(f32 **)(self + 444) != 0 ? **(f32 **)(self + 444) : lbl_80365EFC;
        bx = *(f32 *)(self + 280) * s;
        by = *(f32 *)(self + 284) * s;
        bz = *(f32 *)(self + 288) * s;
        dx = ax - bx;
        dy = ay - by;
        dz = az - bz;
        d = dx * dx + dy * dy + dz * dz;
        if (d > lbl_80365EFC) {
            guess = __frsqrte((f64)d);
            guess = lbl_80365F28 * guess * (lbl_80365F30 - guess * guess * d);
            guess = lbl_80365F28 * guess * (lbl_80365F30 - guess * guess * d);
            guess = lbl_80365F28 * guess * (lbl_80365F30 - guess * guess * d);
            v = (f32)(d * guess);
            d = v;
        }
        if (d > **(f32 **)(self + 540)) {
            fn_800F6E88(buf, lbl_80365F6C);
        } else {
            fn_800F6E88(buf, lbl_80365F74);
        }
        fn_80241DD0(*(void **)(self + 524), buf, other, 0, 0, 0);
        fn_80241DD0(*(void **)(self + 524), lbl_802A8A94, other, 0, c + 10624, 0);
        *(u32 *)(self + 568) = 0;
    }
}

} /* extern "C" */
