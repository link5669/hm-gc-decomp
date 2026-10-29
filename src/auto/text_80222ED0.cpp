// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_80365A90;
extern f32 lbl_80365A94;
extern f32 lbl_80365A70;

#pragma opt_propagation off
void fn_80222ED0(u8 *p, s32 n) {
    if (*(s32 *)(p + 644) != 0 && n != 0) {
        f32 a = lbl_80365A90;
        s32 t = (s32)(a * (f32)n);
        *(f32 *)(p + 660) = lbl_80365A94 * (f32)t;
        *(f32 *)(p + 656) = *(f32 *)(p + 660);
        *(s32 *)(p + 672) = *(s32 *)(p + 664);
        *(s32 *)(p + 668) = *(s32 *)(p + 664);
        *(s32 *)(p + 664) = 0;
    } else {
        *(f32 *)(p + 660) = lbl_80365A70;
        *(f32 *)(p + 656) = lbl_80365A70;
        *(s32 *)(p + 668) = 0;
        *(s32 *)(p + 672) = 0;
        *(s32 *)(p + 664) = 0;
    }
    *(s32 *)(p + 644) = 0;
}

} /* extern "C" */
