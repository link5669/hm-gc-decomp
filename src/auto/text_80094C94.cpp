// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct {
    u8 pad[8];
    u8 r, g, b, a;
} Col_80094C94;
typedef struct {
    u8 pad0[280];
    Col_80094C94 *c1;
    Col_80094C94 *c2;
    s32 dir;
    f32 rate;
    f32 val;
    u8 pad12c[20];
    s32 *f140;
    f32 f144;
    f32 f148;
    s32 f14c;
} Obj_80094C94;
extern f64 lbl_80360F88;
extern f64 lbl_80360F90;
extern f32 lbl_80360F80;
extern f32 lbl_80360F84;
extern f32 lbl_80360F98;
extern f32 lbl_80360F9C;
extern f32 lbl_80360FA0;
extern f32 lbl_80360FA4;
extern f32 lbl_80360FA8;
extern f32 lbl_80360FAC;
f64 fn_800F030C(f64);
void fn_80240200(Obj_80094C94 *, f32);
void fn_8023FE08(Obj_80094C94 *, f32);

void fn_80094C94(Obj_80094C94 *p, f32 dt)
{
    Col_80094C94 *col;
    s32 c;
    u8 inv;
    if (p->dir != 0) {
        p->val += dt * p->rate;
        if (p->val > lbl_80360F88) {
            p->val = lbl_80360F80;
        }
    } else {
        p->val -= dt * p->rate;
        if (p->val < lbl_80360F90) {
            p->val = lbl_80360F84;
        }
    }
    c = (s32)p->val;
    col = p->c1;
    col->r = c;
    col->g = c;
    col->b = c;
    col->a = 255;
    inv = 255 - c;
    col = p->c2;
    col->r = inv;
    col->g = inv;
    col->b = inv;
    col->a = 255;
    if (p->f140 != 0 && *p->f140 != 0 && p->f14c == 0) {
        p->f148 += lbl_80360F98 * dt;
        while (p->f148 > lbl_80360FA0) {
            p->f148 -= lbl_80360F9C;
        }
        while (p->f148 < lbl_80360FA4) {
            p->f148 += lbl_80360F9C;
        }
        p->f144 = fn_800F030C(p->f148);
        p->f144 = lbl_80360FAC * p->f144 + lbl_80360FA8;
        fn_80240200(p, p->f144);
    }
    fn_8023FE08(p, dt);
}
/* inv=0 al=0 s32 col c */
/* pos=5 u8 col c inv */

} /* extern "C" */
