// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {



} /* extern "C" */

extern "C" {
extern u8 lbl_802AFA70[];
void __dt__9C8002F9F4Fv(int, int);
void __dt__9C80037904Fv(int, int);
void __dt__9C80037F20Fv(int, int);
void __dt__9C800390F8Fv(int, int);
void __dl__FPv(int);
void __dt__9C8010B8F8Fv(int, int);
void __dt__9C80111028Fv(int, int);
void __dt__9C801AD710Fv(int, int);
void __dt__9C8025577CFv(int, int);
struct VCall_dtor_8003493C_0 { char vptr_pad[0x2f0]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void m(); };

s32 __dt__9C80034A10Fv(s32 param_1, s16 param_2) {
    if (param_1 != 0) {
        *(u8 **)(param_1 + 0x2f0) = lbl_802AFA70;
        ((VCall_dtor_8003493C_0 *)(param_1))->m();
        __dt__9C8002F9F4Fv((int)(param_1 + 0x818), (int)(0xffffffff));
        __dt__9C80037904Fv((int)(param_1 + 0x804), (int)(0xffffffff));
        __dt__9C800390F8Fv((int)(param_1 + 0x7cc), (int)(0xffffffff));
        __dt__9C80037F20Fv((int)(param_1 + 0x770), (int)(0xffffffff));
        __dt__9C801AD710Fv((int)(param_1 + 0x6f8), (int)(0xffffffff));
        __dt__9C8010B8F8Fv((int)(param_1 + 0x6e4), (int)(0xffffffff));
        __dt__9C80111028Fv((int)(param_1 + 0x4f4), (int)(0xffffffff));
        __dt__9C80111028Fv((int)(param_1 + 0x304), (int)(0xffffffff));
        __dt__9C8025577CFv((int)(param_1), (int)(0));
        if (0 < param_2) {
            __dl__FPv((int)(param_1));
        }
    }
    return param_1;
}
}
