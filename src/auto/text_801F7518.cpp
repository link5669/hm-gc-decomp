// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
f32 fn_800FB2E0(void *);
void fn_801EF720(void *, void *, s32);
void fn_80121CE8(void *);

void fn_801F77F8(void);
void fn_801F7518(u8 *p, void *q, s32 c);
void fn_801EF9A0(void);
void fn_801F7634(void);
void fn_801F7750(void);
void fn_801F7430(void);
void fn_801EF6AC(void);
void fn_801EF648(void);
void fn_801EF644(void);
void fn_801F7694(void);
void *__vt__9C801F786C[13] = { 0, 0, (void *)fn_801F77F8, (void *)fn_801F7518, (void *)fn_801EF9A0, (void *)fn_801F7634, (void *)fn_801F7750, (void *)fn_801F7430, (void *)fn_801EF6AC, (void *)fn_801EF648, (void *)fn_801EF644, 0, (void *)fn_801F7694 };

void fn_801F7518(u8 *p, void *q, s32 c) {
    switch (c) {
    case 151:
        *(f32 *)(p + 72) = fn_800FB2E0(q);
        *(f32 *)(p + 76) = fn_800FB2E0(q);
        break;
    case 146:
        fn_80121CE8(p + 56);
        break;
    case 147:
        *(f32 *)(p + 80) = fn_800FB2E0(q);
        break;
    case 152:
        *(f32 *)(p + 88) = fn_800FB2E0(q);
        *(f32 *)(p + 92) = fn_800FB2E0(q);
        *(s32 *)(p + 104) = 1;
        break;
    case 153:
        *(f32 *)(p + 96) = fn_800FB2E0(q);
        *(f32 *)(p + 100) = fn_800FB2E0(q);
        break;
    case 154:
        *(f32 *)(p + 108) = fn_800FB2E0(q);
        break;
    case 159:
        *(s32 *)(p + 12) = 33;
        break;
    case 160:
        *(s32 *)(p + 12) = 35;
        break;
    case 161:
        *(s32 *)(p + 12) = 34;
        break;
    case 162:
        *(s32 *)(p + 12) = 36;
        break;
    default:
        fn_801EF720(p, q, c);
        break;
    }
}

} /* extern "C" */
