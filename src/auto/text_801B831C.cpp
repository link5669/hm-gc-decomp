// Code of main that had no source file yet: decomp.wtf gave it this one.
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void *fn_801C05EC(u8 *, void *, void *);
void fn_801DBE0C(u8 *, void *);
u32 fn_801B831C(u8 *p, void *q) {
    u32 i;
    fn_801DBE0C(p, q);
    if (*(void ***)(p + 440) != 0) {
        for (i = 0; i < *(u32 *)(p + 392); i++) {
            (*(void ***)(p + 440))[i] = fn_801C05EC(p, q, (*(void ***)(p + 440))[i]);
        }
    }
    if (*(void **)(p + 452) != 0) {
        *(void **)(p + 452) = fn_801C05EC(p, q, *(void **)(p + 452));
    }
    if (p[400] & 3) {
        *(void **)(p + 432) = fn_801C05EC(p, q, *(void **)(p + 432));
    }
    if (p[400] & 0xC) {
        *(void **)(p + 436) = fn_801C05EC(p, q, *(void **)(p + 436));
    }
    return 0;
}

} /* extern "C" */
