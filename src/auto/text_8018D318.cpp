// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Vec3_8018D318 {
    f32 x;
    f32 y;
    f32 z;
};
struct Sph_8018D318 {
    Vec3_8018D318 c;
    f32 r;
};
struct V144_8018D318 {
    u8 pad[20];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void *v5();
};
struct O48_8018D318 {
    u8 pad[20];
    void *f20;
};
struct O120_8018D318 {
    u8 pad[40];
    Vec3_8018D318 scale;
};
struct S8018D318 {
    u8 pad[48];
    O48_8018D318 *f48;
    u8 pad2[120 - 52];
    O120_8018D318 *f120;
    u8 pad3[144 - 124];
    V144_8018D318 *f144;
};
struct FT_8018D318 {
    u8 pad[400];
    void (*fn400)(void *, Sph_8018D318 *, Sph_8018D318 *);
};
extern "C" {
void fn_80100CF4(Sph_8018D318 *);
void fn_801909F4(S8018D318 *, void *, Sph_8018D318 *, void *);
void fn_80104870(O48_8018D318 *);
void fn_8018BB70(void *, void *);
void fn_8018BAA8(void *);
void fn_8018B9C8(void *, Vec3_8018D318 *);
void fn_800FBBE4(void *, void *, Sph_8018D318 *);
extern FT_8018D318 lbl_803286D0;
extern volatile f32 lbl_80364AA8;
extern S8018D318 *lbl_8035AE40;

void fn_8018D318(S8018D318 *self, void *a, Sph_8018D318 *b, void *c) {
    Sph_8018D318 local;
    volatile Vec3_8018D318 inv;
    void *o;
    f32 iz;
    f32 iy;
    f32 ix;
    f32 one;
    f32 sy;
    f32 sx;
    f32 sz;
    f32 tx;
    f32 ty;
    f32 one2;
    f32 tz;
    fn_80100CF4(&local);
    o = self->f144->v5();
    if (o == 0) {
        fn_801909F4(self, a, b, c);
        return;
    }
    if (self->f48 != 0) {
        fn_80104870(self->f48);
        fn_8018BB70(a, self->f48->f20);
        if (b != 0) {
            lbl_803286D0.fn400(self->f48->f20, b, &local);
            if (self->f120 != 0) {
                sx = self->f120->scale.x;
                inv.x = sx;
                sy = self->f120->scale.y;
                inv.y = sy;
                sz = self->f120->scale.z;
                inv.z = sz;
                one = lbl_80364AA8;
                ix = one / sx;
                inv.x = ix;
                iy = one / sy;
                inv.y = iy;
                iz = one / sz;
                inv.z = iz;
                local.c.x *= ix;
                local.c.y *= iy;
                local.c.z *= iz;
                if (ix > iy) {
                    if (iz > ix) {
                        local.r = iz * b->r;
                    } else {
                        local.r = ix * b->r;
                    }
                } else {
                    if (iz > iy) {
                        local.r = iz * b->r;
                    } else {
                        local.r = iy * b->r;
                    }
                }
            } else {
                local.r = b->r;
            }
            b = &local;
        }
    } else {
        fn_8018BAA8(a);
    }
    if (self->f120 != 0) {
        tx = self->f120->scale.x;
        inv.x = tx;
        ty = self->f120->scale.y;
        inv.y = ty;
        tz = self->f120->scale.z;
        inv.z = tz;
        one2 = lbl_80364AA8;
        inv.x = one2 / tx;
        inv.y = one2 / ty;
        inv.z = one2 / tz;
        fn_8018B9C8(a, (Vec3_8018D318 *)&inv);
    }
    lbl_8035AE40 = self;
    fn_800FBBE4(o, a, b);
}

} /* extern "C" */
