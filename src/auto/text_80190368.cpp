// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_803286D0[];
typedef struct Vec80190368 { f32 x, y, z; } Vec80190368;

void fn_80190368(u8 *self, const Vec80190368 *v) {
    u8 *p = *(u8 **)(self + 48);
    if (p != 0) {
        Vec80190368 t;
        (*(void (**)(void *, const Vec80190368 *, Vec80190368 *))(lbl_803286D0 + 404))(*(void **)(p + 16), v, &t);
        Vec80190368 *d = (Vec80190368 *)(*(u8 **)(self + 52) + 24);
        d->x = t.x;
        d->y = t.y;
        d->z = t.z;
    } else {
        Vec80190368 *d = (Vec80190368 *)(*(u8 **)(self + 52) + 24);
        d->x = v->x;
        d->y = v->y;
        d->z = v->z;
    }
}

} /* extern "C" */
