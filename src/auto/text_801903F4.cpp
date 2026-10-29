// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct V3 { f32 x, y, z; } V3;
typedef struct Q { u8 pad[16]; void *f16; } Q;
typedef struct P { u8 pad[48]; Q *f48; V3 *f52; } P;
extern u8 lbl_803286D0[];
void fn_801903F4(P *self, const V3 *v) {
    Q *q = self->f48;
    if (q != 0) {
        V3 t;
        (*(void (**)(void *, const V3 *, V3 *))(lbl_803286D0 + 0x194))(q->f16, v, &t);
        *self->f52 = t;
    } else {
        *self->f52 = *v;
    }
}

} /* extern "C" */
