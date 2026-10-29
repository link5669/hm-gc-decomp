// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_80365270;
extern f32 lbl_80365274;
u8 *fn_801DFE74(void *);

void fn_801DEFB4(u8 *p, f32 dt) {
    u8 *r;
    f32 t;
    f32 cur = *(f32 *)(p + 52);
    if (cur != lbl_80365274) {
        if (cur <= dt) {
            *(f32 *)(p + 52) = lbl_80365274;
            r = fn_801DFE74(*(void **)(p + 40));
            *(f32 *)(r + 40) = lbl_80365274;
            r = fn_801DFE74(*(void **)(p + 40));
            *(u32 *)(r + 48) &= ~1;
            r = fn_801DFE74(*(void **)(p + 44));
            *(f32 *)(r + 40) = lbl_80365270;
        } else {
            *(f32 *)(p + 52) = cur - dt;
            t = *(f32 *)(p + 52) / *(f32 *)(p + 48);
            r = fn_801DFE74(*(void **)(p + 40));
            *(f32 *)(r + 40) = t;
            r = fn_801DFE74(*(void **)(p + 44));
            *(f32 *)(r + 40) = lbl_80365270 - t;
        }
    }
}

} /* extern "C" */
