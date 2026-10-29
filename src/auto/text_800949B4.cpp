// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
static u8 d000_800949B4[760] = { 1 };
static s32 tabA_800949B4[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
static s32 tabB_800949B4[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
static s32 tabC_800949B4[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
typedef struct S800949B4 {
    u8 pad0[96];
    s32 f96;
    u8 pad100[188];
    s32 f288;
    u8 pad292[4];
    f32 f296;
    u8 pad300[16];
    s32 *f316;
    u8 pad320[12];
    s32 f332;
    s32 f336;
} S800949B4;
extern f32 lbl_80360F80;
extern f32 lbl_80360F84;
void fn_802491DC(S800949B4 *, s32);
void fn_8024125C(S800949B4 *, s32);

void fn_800949B4(S800949B4 *self, s32 n) {
    s32 *q;
    s32 idx;
    s32 t;
    idx = tabA_800949B4[n];
    t = self->f96;
    for (q = tabB_800949B4 + idx; t > 0; q++) {
        if (*q > t) break;
        t -= tabB_800949B4[idx++];
    }
    switch (tabC_800949B4[idx]) {
    case 0:
        self->f288 = 1;
        if (self->f316 != 0) {
            self->f288 = *self->f316;
        }
        if (self->f288 != 0) {
            self->f296 = lbl_80360F80;
        } else {
            self->f296 = lbl_80360F84;
        }
        fn_802491DC(self, 0);
        break;
    case 1:
        return;
    case 2:
        if (self->f288 == 0 && self->f336 != 0) {
            fn_8024125C(self, 0);
        }
        self->f288 = 1;
        break;
    case 3:
        if (self->f288 != 0 && self->f336 != 0) {
            fn_8024125C(self, 1);
        }
        self->f288 = 0;
        break;
    case 4:
        self->f288 = 1;
        self->f296 = lbl_80360F80;
        break;
    case 5:
        self->f288 = 0;
        self->f296 = lbl_80360F84;
        break;
    case 6:
        self->f332 = 1;
        break;
    case 7:
        self->f332 = 0;
        break;
    case 8:
        self->f336 = 1;
        break;
    case 9:
        break;
    }
}

} /* extern "C" */
