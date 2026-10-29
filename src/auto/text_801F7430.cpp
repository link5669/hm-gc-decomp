// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_803654D0;
void fn_80100D3C(f32 *, f32 *, f32 *, f32);
void fn_801EF640(void *, f32);

typedef struct S_801F7430 {
    u8 pad0[88];
    f32 a[2];
    f32 b[2];
    u8 pad104[4];
    f32 total;
    f32 rem;
    u8 *obj;
} S_801F7430;


void fn_801F7430(S_801F7430 *self, f32 dt) {
    f32 v[2];
    u8 *o;
    f32 z = lbl_803654D0;
    if (self->rem != z) {
        if (self->rem <= dt) self->rem = z;
        else self->rem = self->rem - dt;
        fn_80100D3C(v, self->a, self->b, (self->total - self->rem) / self->total);
        o = self->obj;
        *(f32 *)(o + 12) = v[0];
        *(f32 *)(o + 16) = v[1];
        fn_801EF640(self, dt);
    }
}

} /* extern "C" */
