/* Functions from 0x800FEEA0 to 0x800FF140, found by decomp-toolkit. */
#include "common.h"
extern "C" {
// the 0.0f of this function is the TU pool constant lbl_80363740; the first read goes through a cast, which keeps
// the literal-like code (all-plain or all-cast reads change it)
extern f32 lbl_80363740;
}

extern "C" {

static inline f64 fabs(f64 x) {
    return __fabs(x);
}

static inline f32 fabsf(f32 x) {
    return (f32)fabs((f64)x);
}


/* QV=1.3.2 */


/* QV=2.0p1 */
static inline f64 fabs_FEEA0(f64 x) { return __fabs(x); }
#define FABSF_FEEA0(x) ((f32)fabs_FEEA0(x))
s32 fn_800FEEA0(f32 *box, f32 *dir, f32 *pos, f32 t) {
    f32 d[3];
    f32 a[3];
    f32 r;
    f32 l;
    f32 ad[3];
    d[0] = pos[0] - box[0];
    d[1] = pos[1] - box[1];
    d[2] = pos[2] - box[2];
    a[0] = FABSF_FEEA0(dir[0]);
    if (FABSF_FEEA0(d[0]) > t * a[0] + box[3]) {
        return 0;
    }
    a[1] = FABSF_FEEA0(dir[1]);
    if (FABSF_FEEA0(d[1]) > t * a[1] + box[4]) {
        return 0;
    }
    a[2] = FABSF_FEEA0(dir[2]);
    if (FABSF_FEEA0(d[2]) > t * a[2] + box[5]) {
        return 0;
    }
    r = box[4] * a[2] + box[5] * a[1];
    if (FABSF_FEEA0(d[1] * dir[2] - d[2] * dir[1]) > r) {
        return 0;
    }
    r = box[3] * a[2] + box[5] * a[0];
    if (FABSF_FEEA0(d[2] * dir[0] - d[0] * dir[2]) > r) {
        return 0;
    }
    r = box[3] * a[1] + box[4] * a[0];
    if (FABSF_FEEA0(d[0] * dir[1] - d[1] * dir[0]) > r) {
        return 0;
    }
    return 1;
}
s32 fn_800FEFC8(f32 *box, f32 *sphere) {
    f32 dx, dy, dz;
    f32 z = sphere[2];

    dx = (f32)__fabs(sphere[0]) - box[3];
    dy = (f32)__fabs(sphere[1]) - box[4];
    dz = (f32)__fabs(z) - box[5];
    if (dx <= (*(f32 *)&lbl_80363740)) {
        if (dy <= lbl_80363740) {
            if (dz <= lbl_80363740) {
                return 1;
            }
            return dz <= sphere[3];
        }
        if (dz <= lbl_80363740) {
            return dy <= sphere[3];
        }
        return dy * dy + dz * dz <= sphere[3] * sphere[3];
    }
    if (dy <= lbl_80363740) {
        if (dz <= lbl_80363740) {
            return dx <= sphere[3];
        }
        return dx * dx + dz * dz <= sphere[3] * sphere[3];
    }
    if (dz <= lbl_80363740) {
        return dx * dx + dy * dy <= sphere[3] * sphere[3];
    }
    return dx * dx + dy * dy + dz * dz <= sphere[3] * sphere[3];
}

} /* extern "C" */
