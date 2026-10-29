// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct O8025AB4C {
    u8 pad0[316];
    f32 f316;
    f32 f320;
    f32 f324;
} O8025AB4C;
typedef struct S8025AB4C {
    u8 pad0[20];
    f32 a[15];
    f32 b[12];
    f32 vx;
    f32 vy;
    f32 vz;
    u8 pad140[4];
    f32 f144;
    f32 f148;
    u8 pad152[4];
    O8025AB4C *f156;
    u8 pad160[36];
    f32 f196;
} S8025AB4C;
extern f32 lbl_803667B4;
extern f64 lbl_803667B8;
extern f64 lbl_803667C0;
void fn_80261AA8(S8025AB4C *);
void fn_802610A0(S8025AB4C *);
void fn_8026102C(S8025AB4C *);

void fn_8025AB4C(S8025AB4C *self) {
    f32 d;
    volatile f32 y;
    f64 guess;
    const O8025AB4C *o;
    O8025AB4C *o2;
    f32 ox, oy, oz;
    fn_80261AA8(self);
    fn_802610A0(self);
    self->b[0] = self->a[0];
    self->b[1] = self->a[1];
    self->b[2] = self->a[2];
    self->b[3] = self->a[3];
    self->b[4] = self->a[4];
    self->b[5] = self->a[5];
    self->b[6] = self->a[6];
    self->b[7] = self->a[7];
    self->b[8] = self->a[8];
    self->b[9] = self->a[9];
    self->b[10] = self->a[10];
    self->b[11] = self->a[11];
    self->vx = self->a[12];
    self->vy = self->a[13];
    self->vz = self->a[14];
    self->f148 = self->f144;
    self->f196 = lbl_803667B4;
    self->vx = lbl_803667B4;
    self->vy = lbl_803667B4;
    self->vz = lbl_803667B4;
    o = self->f156;
    ox = o->f316;
    oy = o->f320;
    oz = o->f324;
    self->vx += ox;
    self->vy += oy;
    self->vz += oz;
    d = self->vx * self->vx + self->vy * self->vy + self->vz * self->vz;
    if (d > lbl_803667B4) {
        guess = __frsqrte((f64)d);
        guess = lbl_803667B8 * guess * (lbl_803667C0 - guess * guess * d);
        guess = lbl_803667B8 * guess * (lbl_803667C0 - guess * guess * d);
        guess = lbl_803667B8 * guess * (lbl_803667C0 - guess * guess * d);
        y = (f32)(d * guess);
        d = y;
    }
    self->f148 = d;
    o2 = self->f156;
    o2->f316 = lbl_803667B4;
    o2->f320 = lbl_803667B4;
    o2->f324 = lbl_803667B4;
    fn_8026102C(self);
}

} /* extern "C" */
