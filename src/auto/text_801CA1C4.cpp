// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_80365010;
struct S801CA1C4 {
    u8 pad0[428];
    u32 n1;       /* 428 */
    u8 pad1[4];
    u32 v436;     /* 436 */
    u8 pad2[16];
    f32 *arr;     /* 456 */
    f32 f460;     /* 460 */
    u8 pad3[8];
    f32 sum1;     /* 472 */
    f32 f476;     /* 476 */
    u8 pad4[8];
    u32 n2;       /* 488 */
    f32 sum2;     /* 492 */
};

void fn_801CA1C4(S801CA1C4 *p) {
    u32 i;
    p->f476 = p->f460 * (f32)p->v436;
    p->sum1 = lbl_80365010;
    for (i = 0; i < p->n1; i++) {
        p->sum1 += p->arr[i];
    }
    p->sum2 = lbl_80365010;
    for (i = 0; i < p->n2; i++) {
        p->sum2 += p->arr[i];
    }
}

} /* extern "C" */
