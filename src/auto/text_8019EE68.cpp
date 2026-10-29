// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V8019 {
    u32 f0;
    u8 pad4[4];
    f32 f8;
    f32 f12;
    u8 pad16[4];
    f32 f20;
    u8 pad24[80];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
};
struct S8019EE68 : V8019 {
    u32 f108;
    u8 pad112[108];
    f32 f220;
    u8 pad224[4];
    s32 f228;
    s32 f232;
};
extern "C" {
void fn_801A1444(S8019EE68 *p, void *a, void *b, void *c);
void fn_80186960(void *p, s32 a, s32 b, s32 c);
void fn_80060568(char *s, s32 a, s32 b, s32 c);
extern char lbl_802A25B8[];
extern f32 lbl_803596E0[];
extern f32 lbl_80364D38;
extern f32 lbl_80364D3C;
extern f32 lbl_80364D40;
extern const f64 lbl_80364D48;
extern const f64 lbl_80364D50;

static inline f32 sqrtf_(f32 x)
{
    volatile f32 y;
    if (x > lbl_80364D40) {
        f64 guess = __frsqrte((f64)x);
        guess = lbl_80364D48 * guess * (lbl_80364D50 - guess * guess * x);
        guess = lbl_80364D48 * guess * (lbl_80364D50 - guess * guess * x);
        guess = lbl_80364D48 * guess * (lbl_80364D50 - guess * guess * x);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

void fn_8019EE68(S8019EE68 *p, void *a, void *b, void *c)
{
    f32 sc;
    f32 x, y, d;
    volatile f32 v;
    f64 guess;
    if (p->f0 & 1) {
        p->v10();
    }
    fn_801A1444(p, a, b, c);
    fn_80186960((u8 *)p + 144, p->f228, p->f232, 2);
    fn_80186960((u8 *)p + 164, p->f228, p->f232, 2);
    fn_80186960((u8 *)p + 184, p->f228, p->f232, 2);
    if (p->f108 == 0) {
        fn_80060568(lbl_802A25B8, 0, 0, 0);
    }
    if (p->f20 == lbl_803596E0[0]) {
        sc = p->f220;
        x = lbl_80364D38 * ((f32)p->f228 * sc);
        y = lbl_80364D38 * ((f32)p->f232 * sc);
        p->f8 = x;
        p->f12 = y;
        d = lbl_80364D3C + (x * x + y * y);
        if (d > lbl_80364D40) {
            guess = __frsqrte((f64)d);
            guess = lbl_80364D48 * guess * (lbl_80364D50 - guess * guess * d);
            guess = lbl_80364D48 * guess * (lbl_80364D50 - guess * guess * d);
            guess = lbl_80364D48 * guess * (lbl_80364D50 - guess * guess * d);
            v = (f32)(d * guess);
            d = v;
        }
        p->f20 = d;
    }
}

} /* extern "C" */
