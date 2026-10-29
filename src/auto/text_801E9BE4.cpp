// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef void (*Fn801E9BE4b)(void *, void *);
extern void *lbl_803286D0[104];
extern f32 lbl_80365364;
extern u32 lbl_80365360;
typedef struct O801E9BE4 {
    u8 pad0[16];
    void *f16;
    u8 pad14[12];
    u32 f32;
    u8 pad24[12];
    struct O801E9BE4 *f48;
} O801E9BE4;
typedef struct T801E9BE4 {
    u8 pad0[40];
    O801E9BE4 *f40;
    O801E9BE4 *f44;
    O801E9BE4 *f48;
    O801E9BE4 *f52;
    f32 f56[4];
    f32 f72[3];
} T801E9BE4;
void fn_80190C98(O801E9BE4 *o);

void fn_801E9BE4(T801E9BE4 *self) {
    O801E9BE4 *o;
    O801E9BE4 *h;
    O801E9BE4 *p;

    o = self->f44 ? self->f44 : self->f40;
    if (self->f48 != 0) {
        p = self->f52 ? self->f52 : self->f48;
        if (p->f48 != 0) {
            ((Fn801E9BE4b)lbl_803286D0[76])(p->f48->f16, self->f72);
        } else {
            self->f72[0] = lbl_80365364;
            self->f72[1] = lbl_80365364;
            self->f72[2] = lbl_80365364;
        }
    }
    h = o->f48;
    if (h != 0) {
        ((Fn801E9BE4b)lbl_803286D0[3])(h->f16, self->f72);
        h->f32 |= lbl_80365360;
        fn_80190C98(o);
    }
}

} /* extern "C" */
