// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { u32 v[3]; } T12_801090D4;
T12_801090D4 *fn_800F8274(void *, void *);
void fn_80108EFC(void *, void *, T12_801090D4 *, void *, s32);

void fn_801090D4(u8 *p, void *b, const T12_801090D4 *c, void *d, void *e) {
    T12_801090D4 *base = *(T12_801090D4 **)(p + 20);
    T12_801090D4 t;
    s32 idx = fn_800F8274(p, e) - base;
    t = *c;
    fn_80108EFC(p + 20, b, &t, d, idx);
}

} /* extern "C" */
