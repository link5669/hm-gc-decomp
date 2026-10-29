// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_8014AAE4(void *);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
extern void *lbl_8035AE70;
extern volatile f32 lbl_80364C14;
} /* extern "C" */

struct P8019628C;
struct O8019628C {
    virtual void v0();
    virtual void v1(P8019628C *);
};
struct Q8019628C {
    O8019628C *o;
};
struct A8019628C;
struct B8019628C {
    u8 pad[440];
    s32 f440;
};
struct P8019628C {
    Q8019628C *q;
    u32 f4;
    virtual void v0();
    virtual void v1(A8019628C *, B8019628C *);
};
struct AO8019628C {
    virtual P8019628C *v0();
};
struct A8019628C {
    AO8019628C *ao;
};

struct C8019590C {
    u8 pad[64];
    C8019590C();
};

struct S8019628C {
    P8019628C *f0;
    B8019628C *f4;
    C8019590C *f8;
    s32 f12;
    s32 f16;
    s32 f20;
    s32 f24;
    f32 f28;
    f32 f32_;
    f32 f36;
    f32 f40;
    u32 f44;
    u32 f48;
};

extern "C" {
void fn_8019628C(S8019628C *self, A8019628C *a, B8019628C *b, f32 *c) {
    if (self->f4 != 0) {
        if (self->f0 != 0) {
            self->f0->q->o->v1(self->f0);
        }
        if (self->f8 != 0) {
            delete[] self->f8;
        }
        self->f0 = 0;
        self->f4 = 0;
        self->f8 = 0;
        self->f12 = 0;
        self->f16 = 0;
        self->f20 = 0;
        self->f24 = 0;
        fn_8014AAE4(&self->f28);
        self->f44 = 0;
        self->f48 = 0;
    }
    self->f4 = b;
    if (c != 0) {
        self->f28 = c[0];
        self->f32_ = c[1];
        self->f36 = c[2];
        self->f40 = c[3];
    } else {
        self->f28 = lbl_80364C14;
        self->f32_ = lbl_80364C14;
        self->f36 = lbl_80364C14;
        self->f40 = lbl_80364C14;
    }
    self->f20 = b->f440 + 1;
    if (lbl_8035AE70 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035AE70);
    self->f8 = new C8019590C[self->f20];
    fn_800F7E98();
    if (self->f8 == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    self->f0 = a->ao->v0();
    self->f0->v1(a, b);
    self->f12 = self->f20 - 1;
    self->f16 = self->f12;
    self->f24 = 0;
}

} /* extern "C" */
