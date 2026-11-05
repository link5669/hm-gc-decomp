// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { u32 a, b, c; } T12;
extern u8 *volatile lbl_8035B684;
void fn_8010904C(void *, void *, T12 *, s32, void *);
void fn_80253AD8(void *p, void *a, T12 *__restrict t, void *d) {
    volatile T12 c; c.a = t->a; c.b = t->b; c.c = t->c; fn_8010904C(lbl_8035B684 + 136, a, (T12 *)&c, -1, d);
}

} /* extern "C" */
