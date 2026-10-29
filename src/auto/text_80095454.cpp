// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
static u8 d000_80095454[688] = { 1 };
static s32 tabA_80095454[6] = { 0, 1, 2, 3, 4, 5 };
static s32 tabB_80095454[6] = { 1, 1, 1, 1, 1, 1 };
static s32 tabC_80095454[6] = { 0, 1, 2, 3, 4, 0 };
typedef struct S80095454 {
    u8 pad0[96];
    s32 f96;
    u8 pad100[124];
    void *f224;
    u8 pad228[64];
    s32 f292;
} S80095454;
extern f32 lbl_80360FFC;
void fn_8022C128(void *o, s32 a, s32 b, s32 c, s32 d, f32 f);

void fn_80095454(S80095454 *self, s32 n) {
    s32 *q;
    s32 idx;
    s32 t;
    idx = tabA_80095454[n];
    t = self->f96;
    for (q = tabB_80095454 + idx; t > 0; q++) {
        if (*q > t) break;
        t -= tabB_80095454[idx++];
    }
    switch (tabC_80095454[idx]) {
    case 0: return;
    case 1: self->f292 = 1; break;
    case 2: self->f292 = 0; break;
    case 3: fn_8022C128(self->f224, 64, 64, 64, 1, lbl_80360FFC); break;
    case 4: fn_8022C128(self->f224, 255, 255, 255, 1, lbl_80360FFC); break;
    case 5: break;
    }
}

} /* extern "C" */
