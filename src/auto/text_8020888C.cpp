// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

} /* extern "C" */

extern "C" {
extern u8 lbl_802EF920[];
void __dl__FPv(int);
void __dt__9C8020EA30Fv(int, int);
struct VCall_fn_8020888C_0 { virtual void p0(); virtual void p1(); virtual void m(); };

u32 * fn_8020888C(u32 *param_1, s16 param_2) {
    if (param_1 != (u32 *)0x0) {
        *param_1 = (u32)lbl_802EF920;
        if (param_1[4] != 0) {
            ((VCall_fn_8020888C_0 *)(param_1))->m();
        }
        param_1[1] = 0;
        param_1[2] = 0;
        param_1[3] = 0;
        param_1[4] = 0;
        param_1[5] = 0;
        __dt__9C8020EA30Fv((int)(param_1), (int)(0));
        if (0 < param_2) {
            __dl__FPv((int)(param_1));
        }
    }
    return param_1;
}
}
