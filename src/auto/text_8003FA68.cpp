// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
s32 fn_802421C0(void *, s32);

s32 fn_8003FA68(void *p, s32 a) {
    switch (a) {
    case 3:
        return fn_802421C0(p, 0);
    case 4:
        return fn_802421C0(p, 1) || fn_802421C0(p, 2);
    }
    return 1;
}

} /* extern "C" */
