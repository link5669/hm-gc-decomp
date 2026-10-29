// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_80241628(u8 *, int, int);
void fn_802494A4(u8 *, int);
void fn_8023F864(u8 *, int);
void fn_8023F9C8(u8 *, int);
static u8 sPad[652] = {1};
static s32 tA[4] = {1};
static s32 tB[9] = {1};
static s32 tC[16] = {1};
void fn_800AEA64(u8 *p, s32 n) {
    s32 *q;
    s32 i;
    s32 t;
    i = tA[n];
    t = *(s32 *)(p + 96);
    for (q = tB + i; t > 0; q++) {
        if (*q > t) break;
        t -= tB[i++];
    }
    switch (tC[i]) {
    case 0:
        fn_80241628(p, 0, 0);
        fn_802494A4(p, 1);
        break;
    case 1:
        fn_8023F864(p, 0);
        break;
    case 2:
        fn_8023F9C8(p, 0);
        break;
    case 3:
        return;
    case 4:
        fn_802494A4(p, 2);
        break;
    case 5:
        fn_802494A4(p, 1);
        break;
    case 6:
        break;
    }
}

} /* extern "C" */
