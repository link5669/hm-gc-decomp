// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct P8019F670 { void *f0; f32 f4; u8 pad[8]; f32 f16; };
struct V8019F670 {
    u8 pad[8];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void m(f32 dt, P8019F670 *p, void *x);
};
extern "C" {
typedef struct { u8 pad[12]; V8019F670 *f12; V8019F670 *f16; f32 f20; } T8019F670;
extern f32 lbl_80364D70;
void *fn_8019BAB8(void *);
void fn_80195208(void *, void *);

void fn_8019F670(T8019F670 *t, P8019F670 *p, void *x, f32 dt) {
    f32 d;
    void *k;
    d = p->f4 - t->f20;
    if (d < -dt) {
        d = -d - dt;
        t->f16->m(dt, p, x);
    } else if (d >= dt) {
        d = d - dt;
        t->f12->m(dt, p, x);
    } else {
        k = fn_8019BAB8(p->f0);
        if (k == 0) {
            t->f12->m(dt, p, x);
            return;
        }
        fn_80195208(x, k);
        if (d < lbl_80364D70) {
            d = -d;
            t->f16->m(dt, p, x);
            t->f12->m(dt, p, k);
        } else {
            t->f16->m(dt, p, k);
            t->f12->m(dt, p, x);
        }
    }
    if (d < p->f16) p->f16 = d;
}

} /* extern "C" */
