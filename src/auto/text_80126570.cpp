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
struct T { u8 pad[16]; u32 f16; u32 f20; void *f24; u8 f28[20]; u8 f48[4]; S52 *f52; void *f56; u8 f60[1284]; u8 *f1344; u32 *f1348; };
void fn_801485B4(T *, int);
int fn_802108B4(void *, u8 *, u32, u32 *);
void fn_80126268(T *, u8 *);
void fn_80129168(Img *, void *, void *, void *);
void fn_80148330(T *, void *, Img *, void *);
void fn_80128F98(Img *, R *, u32 *, void *, R *);
void fn_80128F54(Img *);
void fn_80126570(T *t, void *a, Img *img, void *c) {
    u8 *data;
    u32 got;
    R r2;
    R r;
    if (t->f1344 == 0) {
        if (lbl_8035A9F4 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035A9F4);
        data = new u8[(t->f16 >> 3) * (t->f20 >> 2) * 16];
        fn_800F7E98();
        if (data == 0) fn_800604C4(-4, 0, 0, 0);
        int e = t->f52->seek(16);
        if (e) fn_801485B4(t, e);
        e = fn_802108B4(t->f48, data, (t->f16 >> 3) * (t->f20 >> 2) * 16, &got);
        if (e) fn_801485B4(t, e);
    } else {
        data = t->f1344;
    }
    if (lbl_8035A9F4 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035A9F4);
    t->f1348 = new u32[t->f16 * t->f20];
    fn_800F7E98();
    if (t->f1348 == 0) fn_800604C4(-4, 0, 0, 0);
    fn_80126268(t, data);
    fn_80129168(img, t->f28, t->f60, t->f56);
    fn_80148330(t, a, img, c);
    r2.x = r2.y = 0;
    r2.w = t->f16;
    r2.h = t->f20;
    r.x = r.y = 0;
    r.w = img->f28;
    r.h = img->f30;
    fn_80128F98(img, &r, t->f1348, t->f24, &r2);
    fn_80128F54(img);
    delete[] t->f1348;
    if (t->f1344 == 0) delete[] data;
}

} /* extern "C" */
