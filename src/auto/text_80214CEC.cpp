// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */

struct X80214CEC {
    u32 f0;
    u32 f4;
    u32 f8;
    u32 f12;
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void Flush();
};

struct S80214CEC {
    u32 f0;
    X80214CEC *f4;
};

struct T80214CEC {
    u32 f0;
    u32 f4;
    u32 f8;
    u32 f12;
    u32 f16;
    u32 f20;
    u32 f24;
    S80214CEC *f28;
    u32 f32;
};

static inline s32 IsActive(S80214CEC *s) {
    if (s->f4 == 0) return 0;
    return (s->f4->f8 & 4) || (s->f4->f8 & 8);
}

static inline s32 IsReadable(S80214CEC *s) {
    if (s->f4 == 0) return 0;
    return s->f4->f8 & 2;
}

extern "C" {

void fn_80210830(S80214CEC *s, u32 a, u32 n);
s32 fn_802108B4(S80214CEC *s, u32 a, u32 b, u32 *out);

s32 fn_80214CEC(T80214CEC *self) {
    u32 n = 0;

    if (IsActive(self->f28)) {
        if (self->f32 != self->f28->f4->f0) {
            self->f28->f4->Flush();
        }
        fn_80210830(self->f28, self->f4, self->f12 - self->f4);
        self->f32 += self->f12 - self->f4;
    }
    if (IsReadable(self->f28)) {
        if (fn_802108B4(self->f28, self->f4, self->f8, &n) != 0) {
            return 0;
        }
        self->f32 = self->f28->f4->f0;
    }
    if (IsActive(self->f28)) {
        n = self->f8;
    }
    self->f12 = self->f4;
    self->f16 = self->f12 + n;
    if (self->f8 != n && n == 0) {
        return 0;
    }
    return 1;
}

} /* extern "C" */
