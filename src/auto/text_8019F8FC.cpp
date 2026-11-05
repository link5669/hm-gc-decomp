/* Functions from 0x8019F8FC to 0x8019F924, found by decomp-toolkit. */
#include "common.h"

extern "C" {

extern f32 lbl_80364D78;
extern f32 lbl_80364D7C;

static inline void fn_8019F8FC_set(f32 *v, f32 x, f32 y, f32 z, f32 w) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

/* QV=2.0p1 */
void fn_8019F8FC(const u8 *p, f32 *out) {
    out[0] = lbl_80364D78;
    out[1] = lbl_80364D7C;
    out[2] = lbl_80364D78;
    out[3] = -*(const f32 *)(p + 20);
}

} /* extern "C" */
