// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { f32 x, y, z; } Vec3;
typedef struct {
    u8 pad0[16];
    void (*f16)(void *, Vec3 *);
} X8;

extern void fn_802610A0(void *self);
extern void fn_8026102C(void *self);
extern void fn_80107244(void *p, Vec3 *v);
extern void fn_80190604(void *a, void *b, void *c);
extern void fn_801906E0(void *a, void *b);
extern void fn_80190C98(void *a);
extern f32 lbl_8036668C;
extern u32 lbl_80366688;
extern void *lbl_803286D0[];

typedef struct {
    u8 pad0[16];
    void *f16;
    u8 pad20[12];
    u32 f32;
} Obj;

typedef struct {
    u8 pad0[48];
    Obj *f48;
    u8 pad52[104];
    void *f156;
} Ctx;

typedef struct {
    u8 pad0[156];
    Ctx *f156;
    u8 pad160[392];
    u32 f552;
} Holder;

typedef struct {
    u8 pad0[20];
    f32 a[15];
    f32 b[15];
    u8 pad140[4];
    f32 f144;
    f32 f148;
    u8 pad152[4];
    Holder *f156;
    u8 pad160[16];
    Holder *f176;
    u8 pad180[24];
    void *f204;
    s32 f208;
    s32 f212;
} Self;

static inline void SetFlag(Holder *h, u32 bit, s32 on) {
    if (on) {
        h->f552 |= bit;
    } else {
        h->f552 &= ~bit;
    }
}

void fn_80256898(Self *self) {
    Ctx *ctx = self->f156->f156;
    Vec3 v;
    Obj *o;
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
    self->b[12] = self->a[12];
    self->b[13] = self->a[13];
    self->b[14] = self->a[14];
    self->f148 = self->f144;
    if (ctx->f48 != 0) {
        fn_80107244(ctx->f48, &v);
    } else {
        v.z = v.y = v.x = lbl_8036668C;
    }
    if (self->f204 != 0) {
        fn_80190604(ctx, self->f176->f156, self->f204);
    } else {
        fn_801906E0(ctx, self->f176->f156);
    }
    o = ctx->f48;
    if (o != 0) {
        ((void (*)(void *, Vec3 *))lbl_803286D0[3])(o->f16, &v);
        o->f32 |= lbl_80366688;
        fn_80190C98(ctx);
    }
    self->b[0] = v.x;
    self->b[1] = v.y;
    self->b[2] = v.z;
    fn_8026102C(self);
    SetFlag(self->f156, 0x10, self->f208);
    SetFlag(self->f156, 0x40, self->f212);
}

} /* extern "C" */
