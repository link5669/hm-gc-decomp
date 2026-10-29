// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct V800FF778 { f32 x, y, z; } V800FF778;
typedef struct P800FF778 { f32 x, y, z, d; } P800FF778;

void fn_80101624(V800FF778 *, const V800FF778 *, const V800FF778 *, f32);

static inline f32 dist800FF778(const P800FF778 *p, const V800FF778 *v) {
    return p->d + (v->x * p->x + v->y * p->y + v->z * p->z);
}

s32 fn_800FF778(const P800FF778 *pl, const V800FF778 *b, const V800FF778 *c, V800FF778 *out, f32 *tOut) {
    f32 d1 = dist800FF778(pl, b);
    f32 d2 = dist800FF778(pl, c);
    f32 t;
    if (d1 >= 0.0f) {
        if (d2 >= 0.0f) return 0;
        d2 = -d2;
    } else {
        if (d2 < 0.0f) return 0;
        d1 = -d1;
    }
    t = d1 / (d1 + d2);
    fn_80101624(out, b, c, t);
    *tOut = t;
    return 1;
}

} /* extern "C" */
