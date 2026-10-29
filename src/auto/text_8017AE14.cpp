// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern "C" {
typedef struct P8017AE14 {
    u32 f0;
    f32 f4;
    u8 pad8[8];
    void *f16;
    u8 pad20[4];
    u8 f24[16];
    f32 f40;
    u32 f44;
    u32 f48;
    void *f52;
    void *f56;
} P8017AE14;

void fn_80102864(void *a, void *b, f32 f, u32 c);
void fn_80101E38(void *a, void *b, f32 f, void *c);
void fn_801064C4(void *x, void *a, u32 c, f32 f);
void fn_80101C20(void *a, void *b, u32 c, f32 f, f32 g, void *d);
void fn_8017AE14(P8017AE14 *p, void *a) {
    void *x;
    void *c;
    u32 e;
    f32 t;
    if (p->f48 & 1) {
        if (p->f56 != 0) {
            fn_80102864(a, p->f56, p->f40, p->f44);
        } else if (p->f48 & 8) {
            c = 0;
            e = p->f44;
            t = p->f40;
            x = p->f52;
            if (p->f0 & 0x400) {
                c = p->f24;
            }
            fn_80101E38(p->f16, x, p->f4, c);
            fn_801064C4(x, a, e, t);
        } else {
            c = 0;
            e = p->f44;
            t = p->f40;
            if (p->f0 & 0x400) {
                c = p->f24;
            }
            fn_80101C20(p->f16, a, e, p->f4, t, c);
        }
    }
}
}

} /* extern "C" */
