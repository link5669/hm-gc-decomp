// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern char lbl_803666D4[4];
extern char lbl_803666D8[7];
extern u8 *lbl_8035B65C;
extern f32 lbl_803666B0;
extern f32 lbl_803666B8;
extern f32 lbl_803666BC;
extern f32 lbl_803666C0;
extern f32 lbl_803666C4;
extern f32 lbl_803666C8;
extern f32 lbl_803666CC;
f64 fn_800F049C(f64);
f32 *fn_80261114(void *, char *, s32);
void fn_80261AA8(void *);
void fn_8012962C(void *, f32, f32, f32, f32);
typedef struct P8025732C { u8 pad[596]; f32 f596; f32 f600; f32 f604; f32 f608; } P8025732C;
typedef struct S8025732C { u8 pad[156]; P8025732C *f156; u8 pad2[176 - 160]; void *f176; f32 *f180; f32 *f184; f32 *f188; } S8025732C;
static inline f32 Approach8025732C(f32 cur, f32 target, f32 rate) {
    f32 d = target - cur;
    if ((f32)__fabs(d) > lbl_803666B8) { f32 k = lbl_803666BC - (f32)fn_800F049C(-rate * lbl_803666B0); cur += k * d; }
    return cur;
}

void fn_8025732C(S8025732C *s) {
    P8025732C *p;
    f32 v;
    s->f180 = fn_80261114(s, lbl_803666D4, 1);
    s->f188 = fn_80261114(s, lbl_803666D8, 1);
    fn_80261AA8(s);
    s->f176 = *(void **)(lbl_8035B65C + 40);
    p = s->f156;
    if ((f32)__fabs(*s->f180 - p->f596) > lbl_803666B8) {
        v = Approach8025732C(p->f596, *s->f180, *s->f184);
        p->f596 = v;
        p->f600 = v;
        p->f604 = v;
        p->f608 = lbl_803666B0;
        fn_8012962C(s->f176, lbl_803666C0 * v, lbl_803666C4, lbl_803666C8, lbl_803666CC);
    }
}

} /* extern "C" */
