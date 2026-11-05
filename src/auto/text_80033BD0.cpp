// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u8 lbl_802F069C[];
void __dl__FPv(void *);
void __dt__9C80031B94Fv(void *, s32);
void fn_80222BE8(void *);

u32 *__dt__9C80033BD0Fv(u32 *param_1, s16 param_2) {
    if (param_1 != (u32 *)0x0) {
        param_1[1] = (u32)lbl_802F069C;
        fn_80222BE8(param_1);
        __dt__9C80031B94Fv(param_1, 0);
        if (0 < param_2) {
            __dl__FPv(param_1);
        }
    }
    return param_1;
}

} /* extern "C" */
