// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_80366780;
extern const f64 lbl_80366788;
extern const f64 lbl_80366790;
typedef struct {
    u8 pad[304];
    void (*f304)(void *h, f32 *out);
    void (*f308)(void *h, f32 *a, f32 *b, f32 *c);
} T80258B98;
extern T80258B98 lbl_803286D0;
void fn_8026102C(u8 *self);
void fn_80261978(u8 *self, f32 t);

void fn_80258B98(u8 *self, f32 t) {
    u8 *o;
    f32 *v;
    f32 len2;
    volatile f32 y;
    o = *(u8 **)(*(u8 **)(self + 156) + 156);
    v = *(f32 **)(o + 52);
    if (v != 0) {
        *(f32 *)(self + 128) = v[0];
        *(f32 *)(self + 132) = v[1];
        *(f32 *)(self + 136) = v[2];
    } else {
        *(f32 *)(self + 128) = lbl_80366780;
        *(f32 *)(self + 132) = lbl_80366780;
        *(f32 *)(self + 136) = lbl_80366780;
    }
    len2 = *(f32 *)(self + 128) * *(f32 *)(self + 128) +
           *(f32 *)(self + 132) * *(f32 *)(self + 132) +
           *(f32 *)(self + 136) * *(f32 *)(self + 136);
    if (len2 > lbl_80366780) {
        f64 guess = __frsqrte((f64)len2);
        guess = lbl_80366788 * guess * (lbl_80366790 - guess * guess * len2);
        guess = lbl_80366788 * guess * (lbl_80366790 - guess * guess * len2);
        guess = lbl_80366788 * guess * (lbl_80366790 - guess * guess * len2);
        y = (f32)(len2 * guess);
        len2 = y;
    }
    *(f32 *)(self + 148) = len2;
    if (*(u8 **)(o + 48) != 0) {
        lbl_803286D0.f304(*(void **)(*(u8 **)(o + 48) + 16), (f32 *)(self + 80));
    } else {
        *(f32 *)(self + 80) = lbl_80366780;
        *(f32 *)(self + 84) = lbl_80366780;
        *(f32 *)(self + 88) = lbl_80366780;
    }
    if (*(u8 **)(o + 48) != 0) {
        lbl_803286D0.f308(*(void **)(*(u8 **)(o + 48) + 16), (f32 *)(self + 116), (f32 *)(self + 92), (f32 *)(self + 104));
    }
    *(f32 *)(self + 116) = -*(f32 *)(self + 116);
    *(f32 *)(self + 120) = -*(f32 *)(self + 120);
    *(f32 *)(self + 124) = -*(f32 *)(self + 124);
    *(f32 *)(self + 92) = -*(f32 *)(self + 92);
    *(f32 *)(self + 96) = -*(f32 *)(self + 96);
    *(f32 *)(self + 100) = -*(f32 *)(self + 100);
    fn_8026102C(self);
    fn_80261978(self, t);
}

} /* extern "C" */
