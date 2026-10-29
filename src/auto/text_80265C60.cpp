// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_80366BD0;
extern const f64 lbl_80366BD8;
extern const f64 lbl_80366BE0;
extern f32 lbl_80366BE8;
void fn_802610A0(void *p);
void fn_8026102C(void *p);
f64 fn_800F049C(f64 x);

typedef struct S80265C60 {
    u8 pad0[68];
    f32 f68;
    f32 f72;
    f32 f76;
    f32 f80;
    f32 f84;
    f32 f88;
    u8 pad92[36];
    f32 f128;
    f32 f132;
    f32 f136;
    u8 pad140[36];
    f32 *f176;
} S80265C60;

static inline f32 Sqrtf80265C60(f32 x) {
    volatile f32 y;
    if (x > lbl_80366BD0) {
        f64 half = lbl_80366BD8;
        f64 three = lbl_80366BE0;
        f64 guess = __frsqrte((f64)x);
        guess = half * guess * (three - guess * guess * x);
        guess = half * guess * (three - guess * guess * x);
        guess = half * guess * (three - guess * guess * x);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

void fn_80265C60(S80265C60 *p, f32 dt) {
    f32 dx, dy, dz, k;
    if (p->f176 != 0) {
        if (Sqrtf80265C60(p->f68 * p->f68 + p->f72 * p->f72 + p->f76 * p->f76) > lbl_80366BD0) {
            fn_802610A0(p);
            dx = lbl_80366BD0 - p->f128;
            dy = lbl_80366BD0 - p->f132;
            dz = lbl_80366BD0 - p->f136;
            k = lbl_80366BE8 - (f32)fn_800F049C(-*p->f176 * dt);
            p->f128 += k * dx;
            p->f132 += k * dy;
            p->f136 += k * dz;
            p->f80 += dt * p->f128;
            p->f84 += dt * p->f132;
            p->f88 += dt * p->f136;
            fn_8026102C(p);
        }
    }
}

} /* extern "C" */
