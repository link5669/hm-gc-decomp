// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern "C" {
extern u32 lbl_8035E498;
} /* extern "C" */
struct O8005 { u32 f0; u8 pad[100]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(f32); u8 pad2[44]; u32 f152; };
struct H8005 { u8 pad[760]; O8005 *objs[6]; };
extern "C" {
s32 fn_8005E6BC(H8005 *h, f32 t) {
    s32 r = 0;
    u32 i;
    for (i = 0; i < 6; i++) {
        O8005 *o = h->objs[i];
        u32 fl;
        if (o != 0 && ((fl = o->f152) & 1)) {
            if (fl & 4) {
                *(volatile u32 *)&o->f152 &= ~1;
                h->objs[i]->f0 &= ~0x800;
                h->objs[i]->f152 |= lbl_8035E498;
            }
            h->objs[i]->v11(t);
            r = 1;
        }
    }
    return r;
}
}

} /* extern "C" */
