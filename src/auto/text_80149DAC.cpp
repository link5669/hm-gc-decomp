// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern void *lbl_8035A9F4;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
struct R { u32 x, y, w, h; };
struct Img { u8 pad[28]; u16 f28; u16 f30; };
struct S52 { u8 pad[16]; virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual int seek(int); };
struct T { u8 pad[16]; u32 f16; u32 f20; void *f24; u8 f28[20]; u8 f48[4]; S52 *f52; void *f56; u8 f60[1284]; u32 f1344; u8 *f1348; int f1352; u8 b1356, b1357, b1358, b1359, b1360, b1361; };
struct C80149BF4 { C80149BF4(); u32 *f0; u8 pad[37844]; void *f37848; u8 pad2[4]; };
void fn_801485B4(T *, int);
int fn_802108B4(void *, u8 *, u32, u32 *);
void fn_80149A40(C80149BF4 *, u8 *, u32, u32, u32, u8, u8, u8, u8, u8, u8, void *);
void fn_801499CC(C80149BF4 *);
void fn_80129168(Img *, void *, void *, void *);
void fn_80148330(T *, void *, Img *, void *);
void fn_80128F98(Img *, R *, u32 *, void *, R *);
void fn_80128F54(Img *);
void fn_80149B34(C80149BF4 *, int);
void fn_80149DAC(T *t, void *a, Img *img, void *c) {
    u8 *data;
    u32 got;
    R r2;
    R r;
    if (t->f1348 == 0) {
        if (lbl_8035A9F4 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035A9F4);
        data = new u8[t->f1344];
        fn_800F7E98();
        if (data == 0) fn_800604C4(-4, 0, 0, 0);
        int e = t->f52->seek(t->f1352);
        if (e) fn_801485B4(t, e);
        e = fn_802108B4(t->f48, data, t->f1344, &got);
        if (e) fn_801485B4(t, e);
    } else {
        data = t->f1348;
    }
    if (lbl_8035A9F4 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035A9F4);
    C80149BF4 *o = new C80149BF4;
    fn_800F7E98();
    if (o == 0) fn_800604C4(-4, 0, 0, 0);
    fn_80149A40(o, data, t->f1344, t->f20, t->f16, t->b1356, t->b1358, t->b1359, t->b1360, t->b1361, t->b1357, t->f60);
    fn_801499CC(o);
    t->f56 = o->f37848;
    fn_80129168(img, t->f28, t->f60, t->f56);
    fn_80148330(t, a, img, c);
    r2.x = r2.y = 0;
    r2.w = t->f16;
    r2.h = t->f20;
    r.x = r.y = 0;
    r.w = img->f28;
    r.h = img->f30;
    fn_80128F98(img, &r, o->f0, t->f24, &r2);
    fn_80128F54(img);
    if (t->f1348 == 0) delete[] data;
    fn_80149B34(o, 1);
}

} /* extern "C" */
