// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

typedef struct S801FE3F0 { u8 pad[20]; void *f20; s32 f24; } S801FE3F0;
void fn_802022C8(void *p);
extern u32 lbl_8035B158;
extern u32 lbl_8035B15C;
#pragma opt_propagation off
void fn_801FE3F0(S801FE3F0 *p) {
    void *t = p->f20;
    s32 m; u32 hi; u32 lo;
    p->f20 = 0;
    fn_802022C8(t);
    m = ~(1 << p->f24);
    lo = lbl_8035B15C;
    hi = lbl_8035B158;
    lbl_8035B15C = lo & m;
    m >>= 31;
    lbl_8035B158 = hi & m;
}
#pragma opt_propagation reset

} /* extern "C" */
