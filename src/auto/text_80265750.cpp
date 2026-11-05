// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct Vec80265750 { f32 x, y, z; } Vec80265750;
typedef struct S80265750 {
    u8 pad0[20];
    Vec80265750 p20;      /* 20 */
    Vec80265750 p32;      /* 32 */
    Vec80265750 p44;      /* 44 */
    Vec80265750 p56;      /* 56 */
    u8 pad68[12];
    Vec80265750 p80;      /* 80 */
    u8 q92[12];   /* 92 */
    u8 q104[12];  /* 104 */
    u8 q116[12];  /* 116 */
    f32 f128;
    f32 f132;
    f32 f136;
    u8 pad140[8];
    f32 f148;
    u8 pad152[24];
    f32 * volatile f176;
    f32 *f180;
    f32 *f184;
    f32 *f188;
} S80265750;

extern volatile f32 lbl_80366BA8;
extern f32 lbl_80366BAC;
void fn_802610A0(S80265750 *);
void fn_8026102C(S80265750 *);
void fn_801012C0(void *, Vec80265750 *, Vec80265750 *, f32);
void fn_80101820(void *);

void fn_80265750(S80265750 *self, f32 t) {
    volatile Vec80265750 v;
    f32 *p;
    fn_802610A0(self);
    v.x = *self->f180;
    v.y = *self->f184;
    v.z = *self->f188;
    p = self->f176;
    fn_801012C0(self->q92, (Vec80265750 *)&v, &self->p32, t * (lbl_80366BA8 * *p));
    fn_80101820(self->q92);
    p = self->f176;
    fn_801012C0(self->q116, (Vec80265750 *)&v, &self->p56, t * (lbl_80366BA8 * *p));
    fn_80101820(self->q116);
    p = self->f176;
    fn_801012C0(self->q104, (Vec80265750 *)&v, &self->p44, t * (lbl_80366BA8 * *p));
    fn_80101820(self->q104);
    self->p80.x = self->p20.x;
    self->p80.y = self->p20.y;
    self->p80.z = self->p20.z;
    self->f128 = lbl_80366BAC;
    self->f132 = lbl_80366BAC;
    self->f136 = lbl_80366BAC;
    self->f148 = lbl_80366BAC;
    fn_8026102C(self);
}

} /* extern "C" */
