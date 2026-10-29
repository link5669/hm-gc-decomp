// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_80365258;
} /* extern "C" */
struct S801DA954;
struct O801DA954 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual s32 v5(S801DA954 *self, void *arg, f32 x, f32 y);
};
struct N801DA954 { O801DA954 *obj; s32 f4; N801DA954 *next; };
struct T801DA954 { u8 pad[28]; s32 f28; s32 x32; u8 pad2[280 - 36]; f32 f280; f32 f284; };
struct S801DA954 { u8 pad[116]; T801DA954 *f116; u8 pad2[136 - 120]; N801DA954 *f136; };
extern "C" {
s32 fn_801DA954(S801DA954 *self, void *arg, f32 x, f32 y) {
    N801DA954 *n1;
    s32 found1;
    N801DA954 *n2;
    s32 found2;
    T801DA954 *t;
    found1 = 0;
    for (n1 = self->f136; n1 != 0; n1 = n1->next) {
        if (n1->f4 != 0) {
            if (n1->obj->v5(self, arg, x, y) == 0) found1 = 1;
        }
    }
    if (found1) return 0;
    t = self->f116;
    if (y > t->f284 * lbl_80365258) t->f28 = 1; else t->f28 = 2;
    t = self->f116;
    if (x > t->f280 * lbl_80365258) t->x32 = 1; else t->x32 = 2;
    found2 = 0;
    for (n2 = self->f136; n2 != 0; n2 = n2->next) {
        if (n2->f4 == 0) {
            if (n2->obj->v5(self, arg, x, y) == 0) found2 = 1;
        }
    }
    return found2 ? 0 : 0;
}

} /* extern "C" */
