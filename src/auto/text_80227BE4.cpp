// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u8 lbl_802F0FDC[];
void __ct__9C80233124Fv(void);

u32 * __ct__9C80227BE4Fv(u32 *param_1) {
    __ct__9C80233124Fv();
    *param_1 = (u32)lbl_802F0FDC;
    return param_1;
}

} /* extern "C" */
