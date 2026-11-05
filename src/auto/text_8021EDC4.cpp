// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern f32 lbl_803659A0;
extern u32 lbl_8035B25C;
void fn_80101624(f32 *dst, f32 *a, f32 *b, f32 t);

struct N_8021EDC4 { f32 x, y, z, w; u8 pad[8]; N_8021EDC4 *front; N_8021EDC4 *back; };
struct Q_8021EDC4 { u8 pad[84]; f32 *a; f32 *b; u8 pad2[116 - 92]; u32 lim; };
void fn_8021E508(N_8021EDC4 *p, Q_8021EDC4 *q, f32 *v);

#pragma opt_common_subs off
void fn_8021EDC4(N_8021EDC4 *p, Q_8021EDC4 *q) {
    f32 tmp[3];
    f32 *saved;
    f32 *va = q->a;
    f32 *vb = q->b;
    f32 a1, b0, b1, a0, y, x;
    a1 = *(volatile f32 *)&va[1];
    y = *(volatile f32 *)&p->y;
    b1 = vb[1];
    a0 = *(volatile f32 *)&va[0];
    x = p->x;
    b0 = vb[0];
    f32 da = a0 * x + a1 * y + va[2] * p->z + p->w;
    f32 db = b0 * x + b1 * y + vb[2] * p->z + p->w;
    if (da >= lbl_803659A0) {
        if (db < lbl_803659A0) {
            fn_80101624(tmp, va, vb, da / (da - db));
            if (p->front) {
                saved = q->b;
                q->b = tmp;
                fn_8021EDC4(p->front, q);
                q->b = saved;
            }
            fn_8021E508(p, q, tmp);
            if (lbl_8035B25C < q->lim && p->back) {
                saved = q->a;
                q->a = tmp;
                fn_8021EDC4(p->back, q);
                q->a = saved;
            }
        } else {
            if (p->front) fn_8021EDC4(p->front, q);
        }
    } else {
        if (db >= lbl_803659A0) {
            fn_80101624(tmp, va, vb, da / (da - db));
            if (p->back) {
                saved = q->b;
                q->b = tmp;
                fn_8021EDC4(p->back, q);
                q->b = saved;
            }
            fn_8021E508(p, q, tmp);
            if (lbl_8035B25C < q->lim && p->front) {
                saved = q->a;
                q->a = tmp;
                fn_8021EDC4(p->front, q);
                q->a = saved;
            }
        } else {
            if (p->back) fn_8021EDC4(p->back, q);
        }
    }
}

#pragma opt_common_subs reset

} /* extern "C" */
