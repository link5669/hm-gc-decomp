// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct E8025EE5C { u8 data[28]; } E8025EE5C;
typedef struct P8025EE5C { u8 pad[108]; s32 count; E8025EE5C *arr; } P8025EE5C;
s32 fn_800F6CD0(void *a, void *b);

E8025EE5C *fn_8025EE5C(const P8025EE5C *p, void *key) {
    s32 n;
    u8 *arr;
    s32 off;
    s32 i;
    arr = (u8 *)p->arr;
    n = p->count;
    for (i = 0, off = 0; i < n; off += 28, i++) {
        if (fn_800F6CD0(arr + off, key) != 0) return &p->arr[i];
    }
    return 0;
}

} /* extern "C" */
