// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

typedef struct P801FE48C { u8 pad[16]; s32 f16; } P801FE48C;
typedef struct O801FE48C { u8 pad[24]; s32 f24; } O801FE48C;
O801FE48C *fn_800C72C0(void *a, void *b, void *c);
extern u32 lbl_8035B158;
extern u32 lbl_8035B15C;
#pragma opt_propagation off
O801FE48C *fn_801FE48C(P801FE48C *p, void *a, void *b, void *c) {
    O801FE48C *o = fn_800C72C0(a, b, c);
    if (o != 0) {
        s32 m; u32 hi; u32 lo;
        m = 1 << o->f24;
        lo = lbl_8035B15C;
        hi = lbl_8035B158;
        lbl_8035B15C = lo | m;
        m >>= 31;
        lbl_8035B158 = hi | m;
        p->f16++;
    }
    return o;
}
#pragma opt_propagation reset

} /* extern "C" */
