// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
s32 fn_802421C0(void *a, s32 b);

s32 fn_80084588(void *a, s32 b) {
    switch (b) {
    case 5: return fn_802421C0(a, 0);
    case 6: return fn_802421C0(a, 1);
    case 7: return fn_802421C0(a, 2);
    case 8: return fn_802421C0(a, 3);
    case 9: return fn_802421C0(a, 4);
    case 10: return fn_802421C0(a, 5);
    case 11: return fn_802421C0(a, 6);
    case 12: return fn_802421C0(a, 7);
    case 13: return fn_802421C0(a, 8);
    case 14: return fn_802421C0(a, 9);
    case 15: return fn_802421C0(a, 10);
    case 16: return fn_802421C0(a, 11);
    case 17: return fn_802421C0(a, 12);
    }
    return 1;
}

} /* extern "C" */
