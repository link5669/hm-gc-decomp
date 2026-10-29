// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct C80152B64 { u8 data[64]; C80152B64(); };
extern "C" {
typedef void (*FP80163BE4)(void *);
extern FP80163BE4 lbl_803286D0[];
void fn_800D9E98(u32);
void fn_800BC02C(void *p, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void fn_800D9CC8(void *p, s32 v);
extern f32 lbl_80364684;
extern f32 lbl_80364688;
struct S80163BE4 { u8 pad[28]; u16 w; u16 h; };
#pragma opt_propagation off
#pragma opt_common_subs off
void fn_80163BE4(u8 *self) {
    C80152B64 m;
    u8 *g = *(u8 **)(self + 6456);
    S80163BE4 *s;
    s32 w, h;
    if (*(u32 *)(g + 2072) != 3) {
        *(u32 *)(g + 2072) = 3;
        fn_800D9E98(*(u32 *)(g + 2072));
    }
    s = *(S80163BE4 **)(self + 4);
    w = s->w - 1;
    h = s->h - 1;
    fn_800BC02C(&m, lbl_80364684, (f32)h, lbl_80364684, (f32)w, lbl_80364684, lbl_80364688);
    lbl_803286D0[94](&m);
    fn_800D9CC8(&m, 1);
}
#pragma opt_common_subs reset
#pragma opt_propagation reset

} /* extern "C" */
