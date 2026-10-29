// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct Q { f32 x, y, z, w; };
struct V { f32 x, y, z; };
struct S156 { u8 pad[156]; void *f156; u8 pad160[392]; u32 f552; };
struct T { u8 pad[80]; f32 f80; f32 f84; f32 f88; V f92; V f104; f32 f116; f32 f120; f32 f124; f32 f128; f32 f132; f32 f136; u8 pad140[8]; f32 f148; u8 pad152[4]; S156 *f156; u8 pad160[16]; S156 *f176; f32 *f180; f32 *f184; f32 *f188; f32 *f192; f32 *f196; f32 *f200; void *f204; u32 f208; u32 f212; };
extern f32 lbl_8036668C, lbl_80366690, lbl_80366694;
void fn_80261AA8(T *);
void fn_80190888(void *, void *, void *);
void fn_80190940(void *, void *, void *);
void fn_802610A0(T *);
void fn_8026102C(T *);
void fn_800FFE84(Q *, V *, f32);
void fn_801003A8(Q *, Q *, Q *);
void fn_80100490(Q *, Q *);
void fn_800FFF8C(Q *, V *);
void fn_80256A6C(T *t) {
    fn_80261AA8(t);
    t->f208 = (t->f156->f552 >> 4) & 1;
    t->f212 = (t->f156->f552 >> 6) & 1;
    t->f156->f552 |= 16;
    t->f156->f552 &= ~64;
    if (t->f204) fn_80190888(t->f156->f156, t->f176->f156, t->f204);
    else fn_80190940(t->f156->f156, t->f176->f156, t->f204);
    fn_802610A0(t);
    t->f116 = lbl_80366690;
    t->f120 = lbl_8036668C;
    t->f124 = lbl_8036668C;
    t->f92.x = lbl_8036668C;
    t->f92.y = lbl_80366690;
    t->f92.z = lbl_8036668C;
    t->f104.x = lbl_8036668C;
    t->f104.y = lbl_8036668C;
    t->f104.z = lbl_80366694;
    t->f128 = lbl_8036668C;
    t->f132 = lbl_8036668C;
    t->f136 = lbl_8036668C;
    t->f148 = lbl_8036668C;
    if (t->f192 && t->f196 && t->f200) {
        Q a;
        Q b;
        Q c;
        Q r;
        fn_800FFE84(&a, &t->f92, *t->f192);
        fn_800FFE84(&b, (V *)&t->f116, *t->f196);
        fn_800FFE84(&c, &t->f104, *t->f200);
        fn_801003A8(&r, &a, &b);
        fn_80100490(&r, &c);
        fn_800FFF8C(&r, &t->f92);
        fn_800FFF8C(&r, (V *)&t->f116);
        fn_800FFF8C(&r, &t->f104);
    }
    if (t->f180 && t->f184 && t->f188) {
        f32 x = *t->f184;
        f32 z = *t->f188;
        f32 y = -*t->f180;
        t->f80 = x;
        t->f84 = y;
        t->f88 = z;
    } else {
        t->f80 = lbl_8036668C;
        t->f84 = lbl_8036668C;
        t->f88 = lbl_8036668C;
    }
    fn_8026102C(t);
}

} /* extern "C" */
