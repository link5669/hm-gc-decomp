// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern void *lbl_8035B4F8;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
struct V { f32 x, y, z; };
extern f32 lbl_80366250;
extern f64 lbl_80366280, lbl_80366288;
struct P { u8 pad[12]; u32 n; int closed; u8 pad20[4]; V *pts; u8 pad28[28]; f32 *f56; f32 *f60; };
static inline f32 Sq(f32 x) {
    if (x > lbl_80366250) {
        const f64 _half = lbl_80366280;
        const f64 _three = lbl_80366288;
        volatile f32 y;
        f64 g = __frsqrte((f64)x);
        g = _half * g * (_three - g * g * x);
        g = _half * g * (_three - g * g * x);
        g = _half * g * (_three - g * g * x);
        y = (f32)(x * g);
        return y;
    }
    return x;
}
void fn_80246A30(P *p) {
    u32 j;
    V *a;
    V *b;
    V *pts;
    u32 i;
    f32 total = lbl_80366250;
    if (p->n) {
    if (!p->f56) {
        if (lbl_8035B4F8 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B4F8);
        p->f56 = new f32[p->n];
        fn_800F7E98();
        if (p->f56 == 0) fn_800604C4(-4, 0, 0, 0);
    }
    if (!p->f60) {
        if (lbl_8035B4F8 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B4F8);
        p->f60 = new f32[p->n];
        fn_800F7E98();
        if (p->f60 == 0) fn_800604C4(-4, 0, 0, 0);
    }
    p->f56[0] = lbl_80366250;
    p->f60[0] = lbl_80366250;
    for (i = 1; i < (p->closed ? p->n + 1 : p->n); i++) {
        j = i % p->n;
        pts = p->pts;
        a = &pts[i - 1];
        b = &pts[j];
        f32 dx = a->x - b->x;
        f32 dy = a->y - b->y;
        f32 dz = a->z - b->z;
        f32 d = Sq(dx * dx + dy * dy + dz * dz);
        total += d;
        p->f56[j] = d;
        p->f60[j] = total;
    }
    } else {
        p->f56 = 0;
        p->f60 = 0;
    }
}

} /* extern "C" */
