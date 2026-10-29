// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct A_E04C {
    u8 pad[1720];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5();
    virtual s32 s6(void *a, u32 *flags);
    virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual s32 s11();
    virtual void v12(); virtual void v13();
    virtual s32 s14();
};
extern "C" {
bool fn_8020E04C(A_E04C *self, void *a) {
    u32 flags;
    if (self->s11() == 0) return 0;
    if (self->s14() == 0) return 0;
    if (self->s6(a, &flags) == 1) return 1;
    return !(flags & 2);
}

} /* extern "C" */
