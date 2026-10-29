// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V4_801E1DF0 {
    u8 pad[4];
    virtual void v0();
    virtual void v1();
};
struct V0_801E1DF0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
};
struct V20_801E1DF0 {
    u8 pad[20];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
};
extern "C" {
typedef struct Tex801E1DF0 { u8 pad[28]; u16 w; u16 h; } Tex801E1DF0;
typedef struct Img801E1DF0 { u8 pad[4]; Tex801E1DF0 *tex; } Img801E1DF0;
typedef struct Cam801E1DF0 { u8 pad[52]; f32 fov; u8 pad2[20]; f32 znear; f32 zfar; } Cam801E1DF0;
typedef struct Rect801E1DF0 { s32 x, y, w, h; } Rect801E1DF0;
typedef struct A801E1DF0 { u8 pad[192]; Cam801E1DF0 *cam; Rect801E1DF0 *rect; u8 pad2[8]; Img801E1DF0 *img; } A801E1DF0;
typedef struct B801E1DF0 { u32 f0; u8 pad[8]; V4_801E1DF0 *f12; u8 pad2[32]; u32 f48; } B801E1DF0;
typedef struct C801E1DF0 { u8 pad[176]; B801E1DF0 *f176; } C801E1DF0;
typedef struct N1_801E1DF0 { struct N1_801E1DF0 *next; u8 pad[4]; V0_801E1DF0 *obj; } N1_801E1DF0;
typedef struct N2_801E1DF0 { struct N2_801E1DF0 *next; u8 pad[4]; V20_801E1DF0 *obj; } N2_801E1DF0;
typedef struct S801E1DF0 {
    A801E1DF0 *f0;
    u8 pad4[12];
    f32 f16;
    C801E1DF0 *f20;
    u8 pad18[8];
    N2_801E1DF0 *f32;
    u8 pad24[36];
    N1_801E1DF0 *f72;
    u8 pad4c[40];
    s32 f116;
} S801E1DF0;
/* 1.0f and 2.0f are literals: the original TU owns .sdata2 0x803652B8 (1.0f), 0x803652BC (0.5f) and
   0x803652C0 (int-to-float magic), shared with text_801E20BC; externs colour the float registers differently */
extern u32 lbl_803652C8;
void fn_8012962C(Cam801E1DF0 *cam, f32 fov, f32 aspect, f32 znear, f32 zfar);

void fn_801E1DF0(S801E1DF0 *self) {
    N2_801E1DF0 *n2 = self->f32;
    N1_801E1DF0 *n1 = self->f72;
    if (self->f116 == 0) {
        A801E1DF0 *a;
        Rect801E1DF0 *r;
        self->f116 = 1;
        a = self->f0;
        r = a->rect;
        if (r != 0) {
            Tex801E1DF0 *t = a->img->tex;
            f32 w = (f32)(s32)t->w;
            f32 h = (f32)(s32)t->h;
            f32 y = (h - w / self->f16 + 1.0f) / 2.0f;
            Cam801E1DF0 *cam = a->cam;
            r->x = 0;
            r->w = w;
            r->y = y;
            r->h = h - y;
            fn_8012962C(cam, cam->fov, self->f16, cam->znear, cam->zfar);
        }
        if (self->f20 != 0) {
            B801E1DF0 *b = self->f20->f176;
            if (b->f48 & 1) {
                b->f0 |= lbl_803652C8;
                if (b->f12 != 0) b->f12->v1();
            }
        }
        for (; n1 != 0; n1 = n1->next) n1->obj->v6();
        for (; n2 != 0; n2 = n2->next) n2->obj->v6();
    }
}

} /* extern "C" */
