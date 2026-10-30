// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

void fn_800604C4(s32, s32, s32, s32); void fn_800F7EC0(void *); void fn_800F7E98(void);
}
struct Fmt { u16 f0; u16 bpp; };
struct G { u8 pad[24]; u32 f24; u32 f28; };
struct Tx { u8 pad[8]; void *f8; u16 f12; u8 pad14; u8 mips; u8 f16[8]; u8 f24[32]; u8 *data; u8 pad60[4]; void *f64; };
extern "C" {
extern G *lbl_8035ACC8;
extern u16 lbl_80364598;
extern f32 lbl_8036459C;
void fn_8015689C(void *, void *, s32, Fmt *);
void fn_8015659C(void *, void *, u32 *, u32 *, Fmt *);
void fn_80156514(void *, void *, Fmt *, u32, u32 *);
void *fn_801562D8(Fmt *);
void fn_800D8070(void *, u8 *, u16, u16, void *, s32, s32, s32, s32);
void fn_800D7E24(void *, u8 *, u16, u16, void *, s32, s32, s32);
void fn_800D80B8(void *, s32, s32, s32, s32, s32, f32, f32, f32);

void fn_8015569C(Tx *t, void *a, u32 *w, u32 *h, Fmt *fmt, u32 mips, u32 *offs) {
    u32 total;
    u32 sz;
    u32 i;
    s32 p2;
    fn_8015689C(a, t->f8, 0, fmt);
    if (!(fmt->f0 & 0x3E0)) {
        fn_8015659C(a, t->f8, w, h, fmt);
        fn_80156514(a, t->f8, fmt, *w, &mips);
    }
    total = 0;
    if (fmt->f0 & 0x3E0) sz = (*w * *h) >> 1;
    else { u32 wh = *w * *h; sz = (wh * fmt->bpp + 7) >> 3; }
    for (i = 0; i < mips; i++) {
        offs[i] = total;
        total += sz;
        sz >>= 2;
    }
    if (lbl_8035ACC8->f24 >= 5) lbl_8035ACC8->f28 = lbl_8035ACC8->f24;
    else lbl_8035ACC8->f28 = 5;
    if (!lbl_8035ACC8) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035ACC8);
    t->data = new u8[total];
    fn_800F7E98();
    if (!t->data) fn_800604C4(-4, 0, 0, 0);
    lbl_8035ACC8->f28 = lbl_8035ACC8->f24;
    {
        u32 x = *w, y;
        while (!(x & 1)) x >>= 1;
        y = *h;
        while (!(y & 1)) y >>= 1;
        if (x == 1 && y == 1) { t->f12 |= lbl_80364598; p2 = 1; }
        else p2 = 0;
    }
    t->f64 = fn_801562D8(fmt);
    if (fmt->f0 & 4) fn_800D8070(t->f24, t->data, *w, *h, t->f64, p2, p2, mips > 1, 0);
    else fn_800D7E24(t->f24, t->data, *w, *h, t->f64, p2, p2, mips > 1);
    if (mips > 1) fn_800D80B8(t->f24, 5, 1, 1, 1, 0, lbl_8036459C, mips - 1, lbl_8036459C);
    t->mips = mips;
}

} /* extern "C" */
