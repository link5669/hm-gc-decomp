// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct S801DF640 {
    u8 pad[16];
    u32 f16;
    u8 pad2[40];
};
extern "C" {
u8 *fn_8019556C(void *);
void fn_801EB698(u8 *);

static inline s32 h801DF640(u8 *o, u8 *p) {
    u32 lo;
    u32 hi;
    u32 i;
    s32 idx;
    if (o == 0) {
        return 0;
    }
    idx = *(s32 *)(p + 40);
    if (idx >= 0) {
        lo = idx;
        hi = idx;
    } else {
        hi = *(s32 *)(o + 172) - 1;
        lo = 0;
    }
    for (i = lo; i <= hi; i++) {
        u32 v = (*(S801DF640 **)(o + 176))[i].f16;
        if (v == *(u32 *)(p + 44)) {
            return 1;
        }
    }
    return 0;
}

void fn_801DF640(u8 *p) {
    if ((*(u32 *)(p + 4) & 1) && *(s32 *)(p + 80) == 2) {
        if (h801DF640(fn_8019556C(*(void **)(p + 32)), p)) {
            fn_801EB698(p);
            *(s32 *)(p + 24) = 0;
        }
    }
}

} /* extern "C" */
