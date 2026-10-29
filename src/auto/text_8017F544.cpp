// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V8017F544 {
    u8 pad[12];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4(u8 *);
};
struct E8017F544 {
    u32 f0;
    V8017F544 *f4;
    u8 pad[56];
};
extern "C" {

static inline void h8017F544(E8017F544 *e, u8 *p) {
    if (e->f0 != 0) {
        e->f4->v4(p);
        e->f0 = 0;
    }
}

void fn_8017F544(u8 *p) {
    u32 i;
    if (*(s32 *)(p + 556) == 0) {
        for (i = 0; i < *(u32 *)(p + 548); i++) {
            h8017F544(&(*(E8017F544 **)(p + 552))[i], p);
        }
        *(s32 *)(p + 556) = 1;
    }
}

} /* extern "C" */
