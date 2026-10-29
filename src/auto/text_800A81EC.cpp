// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
static u8 tab_000[776] = { 1 };
static s32 tabA[7] = { 0, 5, 8, 12, 15, 18, 21 };
static s32 tabB[24] = { 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 3, 3, 1, 1, 3, 1, 1, 3, 1, 1 };
static s32 tabC[24] = { 0, 1, 2, 3, 4, 5, 6, 5, 5, 7, 5, 8, 5, 9, 5, 5, 10, 5, 5, 11, 5, 5, 12, 5 };
extern u8 *lbl_8035B308;
extern f32 lbl_80362014;
void fn_80241628(void *, s32, s32);
void fn_802494A4(void *, s32);
void fn_802402E0(void *);
void fn_80240274(void *, s32);
void fn_802401A0(void *);
void fn_802401D0(void *);
void fn_80241588(void *, s32, s32, f32);
void fn_8023F9C8(void *, s32);

void fn_800A81EC(u8 *p, s32 idx) {
    s32 *q;
    s32 j;
    s32 t;

    j = tabA[idx];
    t = *(s32 *)(p + 96);

    for (q = tabB + j; t > 0; q++) {
        if (*q > t) break;
        t -= tabB[j++];
    }
    switch (tabC[j]) {
    case 0:
        fn_80241628(p, 0, 0);
        *(s32 *)(p + 280) = *(s32 *)(lbl_8035B308 + 72);
        fn_802494A4(p, 1);
        break;
    case 1:
        fn_802402E0(p);
        break;
    case 2:
        fn_80240274(p, 0);
        fn_802401A0(p);
        fn_80241588(p, 0, 0, lbl_80362014);
        fn_8023F9C8(p, 0);
        break;
    case 3:
        fn_802401D0(p);
        fn_80241588(p, 1, 0, lbl_80362014);
        *(s32 *)(p + 284) = 0;
        break;
    case 4:
        fn_802401A0(p);
        fn_80241588(p, 2, 0, lbl_80362014);
        break;
    case 5:
        return;
    case 6:
        fn_802401A0(p);
        *(s32 *)(p + 284) = 0;
        break;
    case 7:
        fn_802494A4(p, 3);
        break;
    case 8:
        fn_802494A4(p, 1);
        break;
    case 9:
        fn_802494A4(p, 2);
        break;
    case 10:
        fn_802494A4(p, 4);
        break;
    case 11:
        *(s32 *)(p + 284) = 1;
        *(s32 *)(p + 288) = 1;
        break;
    case 12:
        *(s32 *)(p + 284) = 0;
        *(s32 *)(p + 288) = 0;
        break;
    case 13:
        break;
    }
}

} /* extern "C" */
