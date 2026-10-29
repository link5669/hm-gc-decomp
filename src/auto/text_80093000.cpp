// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
static u8 tab_80093000_000[1048] = { 1 };
static s32 tabA_80093000[17] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
static s32 tabB_80093000[17] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
static s32 tabC_80093000[17] = { 0, 1, 2, 3, 4, 5, 6, 1, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
extern char lbl_802999A0[];
extern void *lbl_8035B65C;
extern f32 lbl_80360D48;
typedef struct S80093000 { u8 pad[96]; s32 f96; } S80093000;
void fn_80241628(S80093000 *, s32, s32);
void fn_80240DBC(S80093000 *, f32);
void fn_8024125C(S80093000 *, s32);
void fn_80240C2C(S80093000 *, s32);
void __ct__9C80253F24Fiiii(void *, char *, s32, s32, s32);

void fn_80093000(S80093000 *self, s32 n) {
    char *str = lbl_802999A0;
    s32 *q;
    s32 idx;
    s32 t;
    idx = tabA_80093000[n];
    t = self->f96;
    for (q = tabB_80093000 + idx; t > 0; q++) {
        if (*q > t) break;
        t -= tabB_80093000[idx++];
    }
    switch (tabC_80093000[idx]) {
    case 0: fn_80241628(self, 0, 0); break;
    case 1: fn_80240DBC(self, lbl_80360D48); break;
    case 2: fn_8024125C(self, 6); break;
    case 3: fn_80240C2C(self, 7); break;
    case 4: fn_8024125C(self, 8); break;
    case 5: fn_80240C2C(self, 9); break;
    case 6: fn_80240C2C(self, 12); break;
    case 7: fn_8024125C(self, 0); break;
    case 8: fn_80240C2C(self, 1); break;
    case 9: fn_80240C2C(self, 2); __ct__9C80253F24Fiiii(lbl_8035B65C, str + 84, 0, 0, 0); break;
    case 10: fn_80240C2C(self, 3); break;
    case 11: fn_80240C2C(self, 4); break;
    case 12: fn_80240C2C(self, 5); __ct__9C80253F24Fiiii(lbl_8035B65C, str + 96, 0, 0, 0); break;
    case 13: fn_80240C2C(self, 10); break;
    case 14: fn_80240C2C(self, 11); __ct__9C80253F24Fiiii(lbl_8035B65C, str + 108, 0, 0, 0); break;
    case 15: fn_8024125C(self, 13); break;
    case 16: break;
    }
}

} /* extern "C" */
