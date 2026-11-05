// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct S1E66FC {
    u8 pad[20];
    virtual void v0();
    virtual void Fire();
};
extern "C" {

void fn_80107018(void *, u32, u32);

void fn_801E66FC(S1E66FC *s) {
    u8 *p = (u8 *)s;
    u32 flags;
    f32 t;
    u32 i;
    f32 prev;
    f32 v;
    flags = *(u32 *)(p + 4);
    if ((flags & 1) || (flags & 2)) {
        fn_80107018(p + 52, *(u32 *)(p + 40), *(u32 *)(p + 48));
        t = *(f32 *)(p + 56);
        for (i = 0; i < *(u32 *)(p + 28); i++) {
            prev = *(f32 *)(p + 32);
            v = (f32)(*(u32 **)(p + 24))[i];
            if (t >= prev) {
                if (t > v && v >= prev) {
                    *(u32 *)(p + 36) = i;
                    s->Fire();
                }
            } else {
                if (t > v || v > prev) {
                    *(u32 *)(p + 36) = i;
                    s->Fire();
                }
            }
        }
        *(f32 *)(p + 32) = t;
    }
}

} /* extern "C" */
