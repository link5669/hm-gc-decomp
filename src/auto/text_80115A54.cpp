// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_80115B6C(int, int, int, void *);
void fn_80116520(int, f32, void *);
void fn_80116A70(int, void *);
void fn_80116B10(int, int, void *);

u32 fn_80115A54(s32 param_1, u32 param_2, s32 param_3) {
    u8 auStack_20[16];
    u32 local_24;
    u8 auStack_28[4];
    u32 v;
    f32 f;

    v = *(u32 *)(param_3 + 4);
    f = *(f32 *)&v;
    fn_80116B10((int)(param_2), (int)(*(u32 *)(param_3 + 8)), &local_24);
    fn_80116A70((int)(local_24), auStack_28);
    fn_80115B6C((int)(local_24), (int)(0), (int)(0), auStack_20);
    fn_80116520((int)(*(u32 *)(param_1 + 0x27a8)), f, auStack_20);
    return 0;
}

} /* extern "C" */
