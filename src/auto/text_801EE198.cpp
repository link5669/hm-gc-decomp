// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct V801EE198 {
    u8 pad0[24];
    f32 f24;
    u8 pad1[60];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void m16(void *, s32, void *);
    virtual void v17(); virtual void v18();
    virtual void m19(void *, s32);
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void m24(f32);
};
struct S801EE198 {
    u8 pad0[36];
    u32 f36;
    void *f40;
    void *f44;
    void *f48;
    V801EE198 *f52;
};

void fn_801EE198(S801EE198 *self) {
    void *x;
    if (self->f36 & 2) {
        x = self->f48 ? self->f48 : self->f44;
        if (self->f40 != 0) {
            self->f52->m19(self->f40, 0);
        }
        self->f52->m16(x, 0, self->f40);
        self->f52->m24(self->f52->f24);
    }
}

} /* extern "C" */
