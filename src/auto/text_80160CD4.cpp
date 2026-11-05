// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct S80160CD4 { u16 count; u8 pad[18]; void *f20; u16 *arr; };
s16 fn_80147CD8(void *a, void *b);
static inline s32 find_80160CD4(u16 *arr, u32 n, u16 v, u32 *out) {
    u32 i;
    for (i = 0; i < n; i++) {
        if (v == arr[i]) { *out = i; return 1; }
    }
    return 0;
}
s32 fn_80160CD4(S80160CD4 *p, void *key, u32 *out) {
    u16 v = fn_80147CD8(p->f20, key);
    return find_80160CD4(p->arr, p->count, v, out);
}

} /* extern "C" */
