// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_8017EEFC(void *);
void fn_8017B9D8(void *);
void fn_8017EF5C(void *, s32);
void fn_8017BA24(void *, s32);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void *memset(void *, s32, u32);
extern void *lbl_8035B2D0;
} /* extern "C" */

struct E802266B4 {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
};

struct S802266B4 {
    s32 f0;
    E802266B4 arr[662];
    u8 obj10596[20];
    s32 *f10616;
    s32 *f10620;
    u8 obj10624[4];
};

static inline void clr_802266B4(S802266B4 *s) {
    u32 i;
    for (i = 0; i < 662; i++) {
        s->arr[i].a = 0;
    }
}
extern "C" {
s32 fn_802266B4(S802266B4 *self) {
    if (self->f0 != 0) {
        fn_8017EEFC(self->obj10596);
        fn_8017B9D8(self->obj10624);
        if (self->f10616 != 0) {
            delete[] self->f10616;
        }
        if (self->f10620 != 0) {
            delete[] self->f10620;
        }
        self->f0 = 0;
        clr_802266B4(self);
        self->f10616 = 0;
        self->f10620 = 0;
    }
    self->f0 = 1;
    fn_8017EF5C(self->obj10596, 330);
    fn_8017BA24(self->obj10624, 1);
    if (lbl_8035B2D0 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035B2D0);
    self->f10616 = new s32[662];
    fn_800F7E98();
    if (self->f10616 == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    if (lbl_8035B2D0 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035B2D0);
    self->f10620 = new s32[662];
    fn_800F7E98();
    if (self->f10620 == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    memset(self->f10616, 0, 2648);
    return 0;
}

} /* extern "C" */
