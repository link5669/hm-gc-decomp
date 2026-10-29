// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
#pragma opt_propagation off
extern char lbl_80360DC8[4];
extern char lbl_80360F1C[8];
extern char lbl_80360F24[6];
extern char lbl_80299A90[];
u32 fn_8023F52C(void *, char *, char *, char *, s32, s32);
void fn_8023F214(void *);

void fn_800945E0(u8 *p) {
    char *s = lbl_80299A90;
    *(u32 *)(p + 280) = fn_8023F52C(p, lbl_80360DC8, lbl_80360DC8, lbl_80360F1C, 1, 0);
    *(u32 *)(p + 284) = fn_8023F52C(p, lbl_80360DC8, lbl_80360DC8, lbl_80360F24, 1, 0);
    *(u32 *)(p + 288) = fn_8023F52C(p, lbl_80360DC8, lbl_80360DC8, s + 144, 1, 0);
    *(u32 *)(p + 292) = fn_8023F52C(p, lbl_80360DC8, lbl_80360DC8, s + 156, 1, 0);
    *(u32 *)(p + 296) = fn_8023F52C(p, lbl_80360DC8, lbl_80360DC8, s + 172, 0, 0);
    *(u32 *)(p + 300) = fn_8023F52C(p, lbl_80360DC8, lbl_80360DC8, s + 184, 0, 0);
    *(u32 *)(p + 304) = fn_8023F52C(p, lbl_80360DC8, lbl_80360DC8, s + 196, 0, 0);
    *(u32 *)(p + 328) = fn_8023F52C(p, lbl_80360DC8, lbl_80360DC8, s + 208, 1, 0);
    *(u32 *)(p + 332) = fn_8023F52C(p, lbl_80360DC8, lbl_80360DC8, s + 220, 1, 0);
    *(u32 *)(p + 336) = fn_8023F52C(p, lbl_80360DC8, lbl_80360DC8, s + 232, 1, 0);
    *(u32 *)(p + 340) = fn_8023F52C(p, lbl_80360DC8, lbl_80360DC8, s + 248, 1, 0);
    *(u32 *)(p + 344) = fn_8023F52C(p, lbl_80360DC8, lbl_80360DC8, s + 268, 1, 0);
    fn_8023F214(p);
}
#pragma opt_propagation reset

} /* extern "C" */
