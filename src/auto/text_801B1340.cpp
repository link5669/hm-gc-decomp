// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
int fn_801D99B4(void *p, int a, int b);
int fn_801B1340(u8 *p, int a, int b) {
    fn_801D99B4(p, a, b);
    switch (M2C_FIELD(p, s32 *, 324)) {
    default:
        return -6;
    case 16:
        return 1;
    }
}

} /* extern "C" */
