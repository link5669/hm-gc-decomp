// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct O_8022992C {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8(void *, void *, void *);
};
void *fn_8023CA4C(void *, void *);

O_8022992C *fn_8022992C(u8 *a, void *b, void *c, void *d) {
    O_8022992C *o;
    void *v = fn_8023CA4C(a, b);
    if (v == 0) return 0;
    o = (O_8022992C *)v;
    o->v8(a, d, c);
    (*(s32 *)(a + 84))++;
    return o;
}

} /* extern "C" */
