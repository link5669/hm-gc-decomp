// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_80363828;
extern const f64 lbl_80363830;
extern const f64 lbl_80363838;
extern f32 lbl_80363840;
extern f32 lbl_80363844;

typedef struct { f32 x, y, z; } V3_80100E24;

static inline f32 sqrtf_80100E24(f32 x) {
    volatile f32 y;
    if (x > lbl_80363828) {
        f64 _half = lbl_80363830;
        f64 _three = lbl_80363838;
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

static inline void Norm_80100E24(V3_80100E24 *out, const V3_80100E24 *in) {
    f32 len = sqrtf_80100E24(in->x * in->x + in->y * in->y + in->z * in->z);
    if (len <= lbl_80363840) {
        out->x = lbl_80363844;
        out->z = out->y = lbl_80363828;
    } else {
        f32 inv = lbl_80363844 / len;
        out->x = in->x * inv;
        out->y = in->y * inv;
        out->z = in->z * inv;
    }
}

void fn_80100E24(V3_80100E24 *out, const V3_80100E24 *a, const V3_80100E24 *b) {
    V3_80100E24 n;
    f32 d;
    Norm_80100E24(&n, b);
    d = a->x * n.x + a->y * n.y + a->z * n.z;
    n.x *= d;
    n.y *= d;
    n.z *= d;
    out->x = a->x - n.x;
    out->y = a->y - n.y;
    out->z = a->z - n.z;
}

} /* extern "C" */
