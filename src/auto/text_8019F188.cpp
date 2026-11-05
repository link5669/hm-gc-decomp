/* Functions from 0x8019F188 to 0x8019F1B0, found by decomp-toolkit. */
#include "common.h"

extern "C" {

extern f32 lbl_80364D70;
extern f32 lbl_80364D74;

typedef struct Unk8019F188 {
    u8 pad0[0x14];
    f32 unk14;
} Unk8019F188;
typedef struct Plane8019F188 {
    f32 x, y, z, w;
} Plane8019F188;

static inline void setPlane(f32 *v, f32 x, f32 y, f32 z, f32 w) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

/* QV=2.0p1 */
typedef struct Unk8019F188b { u8 pad0[0x14]; f32 unk14; } Unk8019F188b;
void fn_8019F188(const Unk8019F188b *p, f32 *out) {
    out[0] = lbl_80364D74;
    out[1] = lbl_80364D70;
    out[2] = lbl_80364D70;
    out[3] = -p->unk14;
}

} /* extern "C" */
