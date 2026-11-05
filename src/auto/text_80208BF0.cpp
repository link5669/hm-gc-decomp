// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

} /* extern "C" */

extern "C" {
extern u8 lbl_802EF968[];
void __dl__FPv(int);
void __dt__9C80208C80Fv(int, int);
void fn_800BD474(int);
struct VCall_dtor_80208BF0_0 { virtual void p0(); virtual void p1(); virtual void m(); };

s32 * __dt__9C80208BF0Fv(s32 *param_1, s16 param_2) {
    if (param_1 != (s32 *)0x0) {
        *param_1 = (s32)lbl_802EF968;
        if (param_1[0x10] != 0) {
            ((VCall_dtor_80208BF0_0 *)(param_1))->m();
        }
        fn_800BD474((int)(param_1 + 1));
        param_1[0x10] = 0;
        __dt__9C80208C80Fv((int)(param_1), (int)(0));
        if (0 < param_2) {
            __dl__FPv((int)(param_1));
        }
    }
    return param_1;
}
}
