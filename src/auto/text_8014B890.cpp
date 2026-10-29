// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V52_8014B890 {
    u8 pad[16];
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void *m(u32);
};
extern "C" {

typedef struct Rect_8014B890 { s32 x, y, w, h; } Rect_8014B890;
typedef struct B_8014B890 { u8 pad[28]; u16 f28; u16 f30; } B_8014B890;
typedef struct Self_8014B890 {
    u8 pad0[16]; u32 f16; u32 f20; u32 f24; u8 f28[20]; u8 f48[4]; V52_8014B890 *f52; u32 f56; u8 f60[1284];
    u32 f1344; u32 f1348; u8 *f1352; u8 pad1356[6]; u8 f1362; u8 pad1363; u32 f1364;
} Self_8014B890;

extern void *lbl_8035A9F4;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_801485B4(Self_8014B890 *, void *);
void *fn_802108B4(void *, void *, u32, void *);
void fn_80129168(B_8014B890 *, void *, void *, u32);
void fn_80148330(Self_8014B890 *, void *, B_8014B890 *, s32);
void fn_80128F98(B_8014B890 *, Rect_8014B890 *, u8 *, u32, Rect_8014B890 *);
void fn_80128F54(B_8014B890 *);

void fn_8014B890(Self_8014B890 *self, void *a, B_8014B890 *b, s32 c) {
    u8 *buf;
    void *r;
    Rect_8014B890 r2;
    Rect_8014B890 r1;
    u32 tmp;
    if (self->f1352 == 0) {
        if (lbl_8035A9F4 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035A9F4);
        buf = new u8[self->f1348];
        fn_800F7E98();
        if (buf == 0) fn_800604C4(-4, 0, 0, 0);
        r = self->f52->m(self->f1344);
        if (r) fn_801485B4(self, r);
        r = fn_802108B4(self->f48, buf, self->f1348, &tmp);
        if (r) fn_801485B4(self, r);
    } else {
        buf = self->f1352;
    }
    fn_80129168(b, self->f28, self->f60, self->f56 + self->f1364);
    if (!(self->f1362 & 0x10)) c = (bool)(c == 0);
    fn_80148330(self, a, b, c);
    r2.x = r2.y = 0;
    r2.w = self->f16;
    r2.h = self->f20;
    r1.x = r1.y = 0;
    r1.w = b->f28;
    r1.h = b->f30;
    fn_80128F98(b, &r1, buf, self->f24, &r2);
    fn_80128F54(b);
    if (self->f1352 == 0) delete[] buf;
}

} /* extern "C" */
