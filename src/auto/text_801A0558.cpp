// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct P801A0558 {
    void *f0;
    u8 pad4[8];
    f32 f12;
    f32 f16;
};
struct Q801A0558;
struct V801A0558 {
    u8 pad0[8];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void f8(f32 r, P801A0558 *p, Q801A0558 *q);
};
struct S801A0558 {
    u8 pad0[12];
    V801A0558 *f12;
    V801A0558 *f16;
    f32 f20;
};
extern "C" {
extern f32 lbl_80364D80;
Q801A0558 *fn_8019BAB8(void *);
void fn_80195208(Q801A0558 *, Q801A0558 *);

void fn_801A0558(S801A0558 *self, P801A0558 *p, Q801A0558 *q, f32 range) {
    f32 d;
    Q801A0558 *r;
    d = p->f12 - self->f20;
    if (d < -range) {
        d = -d - range;
        self->f16->f8(range, p, q);
    } else if (d >= range) {
        d = d - range;
        self->f12->f8(range, p, q);
    } else {
        r = fn_8019BAB8(p->f0);
        if (r == 0) {
            self->f12->f8(range, p, q);
            return;
        }
        fn_80195208(q, r);
        if (d < lbl_80364D80) {
            d = -d;
            self->f16->f8(range, p, q);
            self->f12->f8(range, p, r);
        } else {
            self->f16->f8(range, p, r);
            self->f12->f8(range, p, q);
        }
    }
    if (d < p->f16) {
        p->f16 = d;
    }
}

} /* extern "C" */
