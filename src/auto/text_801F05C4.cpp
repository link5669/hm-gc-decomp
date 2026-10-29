// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct C801F05C4 {
    u8 pad[20];
    virtual void v0();
    virtual void v1();
    f32 f24;
    f32 f28;
    f32 f32_;
    u32 f36;
    u32 f40;
};
extern "C" {
void fn_801F05C4(C801F05C4 *p, f32 dt) {
    u32 i;
    p->f28 += dt;
    if (p->f40 != p->f36) {
        if (p->f36 != 0) {
            for (i = p->f40; i < p->f36; i++) {
                if (!(p->f28 >= p->f24 + (f32)i * p->f32_)) break;
                p->v1();
            }
            p->f40 = i;
        } else if (p->f28 >= p->f24) {
            p->v1();
            p->f40++;
        }
    }
}

} /* extern "C" */
