// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct C802538C0 {
    u8 pad[24];
    C802538C0();
};
extern "C" {
typedef struct A80251A44 {
    u8 pad0[188];
    s32 f188;
} A80251A44;
typedef struct T80251A44 {
    u8 pad0[28];
    void *f28;
    void *f32;
    u8 pad24[4];
    void **f40;
    u32 f44;
    C802538C0 **f48;
    u32 f52;
    u8 pad38[40];
    u32 f96;
    u32 f100;
} T80251A44;
extern u32 lbl_8035B5E0;
extern u32 lbl_8035B1C0[2];
void *fn_800F8274(void *map, u32 key);
void fn_8011B718(void *o, A80251A44 *a, void *r);
void fn_800604C4(s32 a, s32 b, s32 c, s32 d);
void fn_800F7EC0(u32 heap);
void fn_800F7E98(void);
void *fn_8021616C(u32 x);
void fn_80207BF4(void *x, u32 d);
void fn_8025370C(C802538C0 *o, void *r, u32 b, u32 e, u32 f);
void fn_802079F0(void *x, s32 v);
void fn_800F87F0(T80251A44 *self, u32 b, C802538C0 *o);

void fn_80251A44(T80251A44 *self, A80251A44 *a, u32 b, u32 c, u32 d, u32 e, u32 f) {
    void *r;
    void *x;
    r = fn_800F8274(self->f28, b);
    if (a != 0 && a->f188 != 0 && self->f100 < self->f44) {
        self->f40[self->f100] = fn_800F8274(self->f32, c);
        fn_8011B718(self->f40[self->f100], a, r);
        self->f100++;
    }
    if (fn_800F8274(self, b) == 0 && self->f96 < self->f52) {
        if (lbl_8035B5E0 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B5E0);
        self->f48[self->f96] = new C802538C0;
        fn_800F7E98();
        if (self->f48[self->f96] == 0) fn_800604C4(-4, 0, 0, 0);
        x = fn_8021616C(lbl_8035B1C0[0]);
        fn_80207BF4(x, d);
        fn_8025370C(self->f48[self->f96], r, b, e, f);
        fn_802079F0(x, 0);
        fn_800F87F0(self, b, self->f48[self->f96]);
        self->f96++;
    }
}

} /* extern "C" */
