// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern void *lbl_8035A9F0;
extern void *volatile lbl_8035A9F4;
void fn_800F7EC0(void *);
} /* extern "C" */
struct C80119398 {
    s32 f0;
    u8 pad[656];
    void *f660;
    virtual void v0(void *);
    virtual void v1();
    virtual void v2();
    virtual void v3();
};
extern "C" {
void fn_80119398(C80119398 *p, void *a) {
    void *t;
    if (p->f0 != 0) p->v3();
    p->v0(a);
    lbl_8035A9F0 = (u8 *)p + 4;
    lbl_8035A9F4 = p->f660;
    t = lbl_8035A9F4;
    if (t) fn_800F7EC0(t);
    p->f0 = 1;
}

} /* extern "C" */
