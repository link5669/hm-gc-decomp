// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern char lbl_80299400[];
extern char lbl_80360630[4];
extern char lbl_803606B4[5];
extern char lbl_803606BC[8];
u32 fn_8023F52C(void *self, const char *a, const char *b, const char *c, s32 d, s32 e);
s32 fn_8023F214(void *self);
#define F(o) (*(u32 *)((u8 *)self + (o)))
#pragma opt_propagation off
s32 fn_8008ED7C(void *self) {
    char *str = lbl_80299400;
    F(280) = fn_8023F52C(self, lbl_80360630, lbl_80360630, str + 264, 1, 0);
    F(284) = fn_8023F52C(self, lbl_80360630, lbl_80360630, str + 280, 1, 0);
    F(288) = fn_8023F52C(self, lbl_80360630, lbl_80360630, str + 292, 1, 0);
    F(292) = fn_8023F52C(self, lbl_80360630, lbl_80360630, str + 304, 0, 0);
    F(296) = fn_8023F52C(self, lbl_80360630, lbl_80360630, str + 320, 0, 0);
    F(300) = fn_8023F52C(self, lbl_80360630, lbl_80360630, str + 340, 1, 0);
    F(368) = fn_8023F52C(self, lbl_80360630, lbl_80360630, lbl_803606B4, 1, 0);
    F(372) = fn_8023F52C(self, lbl_80360630, str + 12, lbl_803606BC, 1, 0);
    F(380) = fn_8023F52C(self, lbl_80360630, lbl_80360630, str + 352, 0, 0);
    F(384) = fn_8023F52C(self, lbl_80360630, lbl_80360630, str + 364, 0, 0);
    F(388) = fn_8023F52C(self, lbl_80360630, lbl_80360630, str + 380, 0, 0);
    return fn_8023F214(self);
}
#pragma opt_propagation reset

} /* extern "C" */
