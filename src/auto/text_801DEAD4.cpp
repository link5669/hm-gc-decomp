// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
u8 *fn_8019565C(void *);
void fn_8019B7E8(void *, u8 *);
void fn_801DEAD4(u8 *p) {
    void *obj;
    u8 *r;
    u32 *q;
    obj = *(void **)(*(u8 **)(p + 8) + 216);
    r = fn_8019565C(*(void **)(p + 44) ? *(void **)(p + 44) : *(void **)(p + 40));
    if (*(u32 *)(p + 36) & 2) {
        for (q = *(u32 **)(r + 72); q != 0; q = (u32 *)q[5]) {
            if ((void *)*q == obj) return;
        }
        fn_8019B7E8(obj, r);
    }
}

} /* extern "C" */
