// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V801D0B30 { virtual void v0(); virtual void v1(); virtual s32 v2(void *self, void *arg, f32 x, f32 y); };
struct N801D0B30 { V801D0B30 *obj; s32 f4; N801D0B30 *next; };
struct S801D0B30 {
    u8 pad0[136];
    N801D0B30 *f136;
    u8 pad140[324 - 140];
    s32 f324;
    u8 pad328[412 - 328];
    f32 f412;
    f32 f416;
    f32 f420;
    f32 f424;
    u8 pad428[468 - 428];
    f32 f468;
    f32 f472;
};
extern "C" {
extern f32 lbl_80365178;
extern f32 lbl_8036517C;
extern f32 lbl_80365180;
void fn_801D0D78(S801D0B30 *self, f32 dx, f32 dy);
s32 fn_801D0B30(S801D0B30 *self, void *arg, f32 x, f32 y) {
    N801D0B30 *n = self->f136;
    s32 found = 0;
    f32 dx, dy;
    f32 hi, lo;
    while (n != 0) {
        if (n->f4 != 0) {
            if (n->obj->v2(self, arg, x, y) == 0) found = 1;
        }
        n = n->next;
    }
    if (found) return 0;
    switch (self->f324) {
    case 64:
        dx = x - self->f468;
        dy = y - self->f472;
        self->f468 = x;
        self->f472 = y;
        if (dx >= (lo = lbl_80365178) && dx <= (hi = lbl_8036517C) && dy >= lo && dy <= hi) break;
        if (x > self->f420 || x < self->f412) dx = lbl_80365180;
        if (y > self->f424 || y < self->f416) dy = lbl_80365180;
        fn_801D0D78(self, dx, dy);
        break;
    }
    return 0;
}

} /* extern "C" */
