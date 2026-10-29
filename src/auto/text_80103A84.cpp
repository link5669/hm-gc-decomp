// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { s32 x0; } L80103A84;
typedef struct { u8 pad[52]; u16 f52; u16 f54; } Q80103A84;
typedef struct { u32 flags; f32 t; f32 speed; L80103A84 *l; Q80103A84 *q; void *f20; } S80103A84;
f32 fn_80106E84(S80103A84 *p, f32 dt, s32 lo, s32 hi);
void fn_80107018(S80103A84 *p, f32 dt, s32 lo, s32 hi);
void fn_80101B0C(Q80103A84 *q, void *b, L80103A84 *l, f32 old, f32 res);

#pragma opt_propagation off
void fn_80103A84(S80103A84 *p, f32 dt) {
    if (p->f20 != 0 || p->l != 0) {
        if (p->flags & 2) {
            Q80103A84 *q = p->q;
            f32 old = p->t;
            f32 res = fn_80106E84(p, dt, q->f52, q->f54);
            if (q == p->q) {
                if (p->l != 0 && p->l->x0 != 0) {
                    fn_80101B0C(p->q, p->f20, p->l, old, res);
                } else if (p->f20 != 0) {
                    fn_80101B0C(p->q, p->f20, 0, old, res);
                }
            }
        }
    } else {
        Q80103A84 *q = p->q;
        u16 hi = q->f54;
        u16 lo = q->f52;
        fn_80107018(p, dt, lo, hi);
    }
}
#pragma opt_propagation reset

} /* extern "C" */
