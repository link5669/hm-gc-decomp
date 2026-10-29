// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct T_80241588 { u8 pad[416]; f32 f416; };
struct S_80241588 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual bool v16(s32);
    u8 pad4[204];
    void **f208;
    u8 pad212[8];
    s32 f220;
    T_80241588 *f224;
};
extern f32 lbl_8036613C;
void fn_8022CC44(void *, void *, s32, f32, bool, s32, s32, f32);

void fn_80241588(S_80241588 *self, s32 idx, s32 x, f32 f) {
    void *e;
    self->f220 = idx;
    self->f224->f416 = lbl_8036613C;
    e = self->f208[idx];
    fn_8022CC44(self->f224, e, 1, f, self->v16(idx), x, 0, lbl_8036613C);
}

} /* extern "C" */
