// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct Pool {
    u8 *(*alloc)(s32 n);
    u8 pad[24];
    s32 stride;
} Pool;

typedef struct Obj {
    u32 f0;
    Pool *owner;
} Obj;

Pool *fn_800F85F0(void *a, void *b, s32 n);

u8 *fn_8023B7DC(void *a, void *b, s32 n) {
    Pool *pool;
    u8 *mem;
    s32 i;
    u8 *p;
    pool = fn_800F85F0(a, b, n);
    if (pool->alloc != 0) {
        mem = pool->alloc(n);
        if (n <= 1) {
            ((Obj *)mem)->owner = pool;
        } else {
            p = mem;
            for (i = 0; i < n; i++) {
                ((Obj *)p)->owner = pool;
                p += pool->stride;
            }
        }
        return mem;
    }
    return 0;
}

} /* extern "C" */
