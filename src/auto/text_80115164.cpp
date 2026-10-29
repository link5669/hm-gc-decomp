// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { u32 f0; u32 f4; s32 f8; } A80115164;
double fn_800EFE78(double x);
extern f32 lbl_80363A28;
extern f32 lbl_80363A2C;
extern f64 lbl_80363A30;

static inline f32 up80115164(f32 v) {
    f32 r = (f32)fn_800EFE78(v);
    if (v >= lbl_80363A28 && lbl_80363A28 != v - r) r += lbl_80363A2C;
    return r;
}
#pragma opt_propagation off
s32 fn_80115164(void *a, void *b, A80115164 *p) {
    union { u32 i; f32 f; } u;
    f32 v, r;
    u.i = p->f4;
    v = u.f;
    switch (p->f8) {
    case 1:
        r = (f32)fn_800EFE78(v);
        break;
    case 2:
        r = up80115164(v);
        break;
    default:
        r = (f32)fn_800EFE78(lbl_80363A30 + v);
        break;
    }
    return (s32)r;
}
#pragma opt_propagation reset

} /* extern "C" */
