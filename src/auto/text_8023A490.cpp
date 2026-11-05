// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct R8023A490 { u8 pad[28]; s32 f28; } R8023A490;
R8023A490 *fn_800F85F0(void *a, void *b);
typedef struct S8023A490 { u8 pad[8]; void *f8; u8 pad2[8]; u8 *f20; u8 pad3[4]; void *f28; } S8023A490;
u8 *fn_8023A490(S8023A490 *p, s32 i) {
    s32 stride = fn_800F85F0(p->f28, p->f8)->f28;
    u8 *r = p->f20;
    r += i * stride;
    return r;
}

} /* extern "C" */
