// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
/* The statics stand for lbl_802D0990 (0x350 bytes, in jt_802D098C; also used by text_800A585C): fn_800A51D8
   addresses it through the section base at offsets 736 (tabA), 760 (tabB) and 804 (tabC). d000 is filler;
   tabA/tabB/tabC hold the real values. */
static u8 d000_800A51D8[736] = { 1 };
static s32 tabA_800A51D8[6] = { 0, 2, 4, 6, 8, 10 };
static s32 tabB_800A51D8[11] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 };
static s32 tabC_800A51D8[11] = { 0, 1, 1, 2, 3, 4, 1, 5, 6, 7, 1 };
void fn_802494A4(void *, s32);
void fn_800A5494(void *);
s32 fn_800F6CD0(const char *, const char *);
void *fn_80242144(void *, s32);
void fn_80242BC0(void *, const char *, s32, s32, s32, s32);
extern const char lbl_80361E14[5];
extern const char lbl_80361DC0[4];

void fn_800A51D8(u8 *self, s32 n) {
    s32 *q;
    s32 idx;
    s32 t;
    idx = tabA_800A51D8[n];
    t = M2C_FIELD(self, s32 *, 96);
    for (q = tabB_800A51D8 + idx; t > 0; q++) {
        if (*q > t) break;
        t -= tabB_800A51D8[idx++];
    }
    switch (tabC_800A51D8[idx]) {
    case 0:
        M2C_FIELD(self, s32 *, 320) = 0;
        M2C_FIELD(self, s32 *, 328) = 0;
        M2C_FIELD(self, s32 *, 332) = 0;
        M2C_FIELD(self, s32 *, 336) = 0;
        fn_802494A4(self, 1);
        break;
    case 1:
        return;
    case 2:
        fn_800A5494(self);
        break;
    case 3:
        M2C_FIELD(self, s32 *, 340) = 1;
        break;
    case 4:
        M2C_FIELD(self, s32 *, 340) = 1;
        M2C_FIELD(self, s32 *, 328) = 1;
        M2C_FIELD(self, s32 *, 332) = 1;
        M2C_FIELD(self, s32 *, 320) = 0;
        if (M2C_FIELD(self, s32 *, 336) != 0) {
            if (fn_800F6CD0(lbl_80361E14, lbl_80361DC0) == 0) {
                fn_80242BC0(fn_80242144(self, 1), lbl_80361E14, 0, 0, 0, 0);
            }
        }
        break;
    case 5:
        M2C_FIELD(self, s32 *, 336) = 1;
        if (fn_800F6CD0(lbl_80361E14, lbl_80361DC0) == 0) {
            fn_80242BC0(fn_80242144(self, 1), lbl_80361E14, 0, 0, 0, 0);
        }
        break;
    case 6:
        M2C_FIELD(self, s32 *, 340) = 0;
        break;
    case 7:
        M2C_FIELD(self, s32 *, 340) = 0;
        fn_802494A4(self, 0);
        break;
    case 8:
        break;
    }
}

} /* extern "C" */
