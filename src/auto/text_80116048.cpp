// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct M80116048 {
    u8 pad[16];
    virtual void v0();
    virtual void v1();
};
struct O80116048 {
    u8 pad0[2080];
    u32 arr[2000];
    u32 f10080;
    u32 f10084;
    u32 f10088;
    u32 f10092;
    u32 f10096;
    u32 f10100;
    u32 f10104;
    M80116048 m;
    u32 f10128;
    u32 f10132;
    u32 f10136;
    u32 f10140;
    u32 f10144;
    s32 f10148;
    u32 f10152;
};
extern "C" {
extern u32 lbl_8035AB00;
void fn_80115090(u32 a, u32 b);
void *memset(void *p, int c, unsigned long n);
void __dt__9C800F92E8Fv(void *p, s16 f);
void __dl__FPv(void *p);

static inline void rel80116048(O80116048 *self) {
    u32 i;
    for (i = 0; i < 2000; i++) {
        if (self->arr[i] != 0) fn_80115090(self->f10100, self->arr[i]);
    }
}
static inline void clr80116048(O80116048 *self) {
    u32 i;
    for (i = 0; i < 2000; i++) self->arr[i] = 0;
}
O80116048 *fn_80116048(O80116048 *self, s16 f) {
    if (self) {
        if (self->f10148 != 0) {
            self->m.v1();
            rel80116048(self);
            self->f10148 = 0;
            lbl_8035AB00 = 0;
            self->f10096 = 0;
            self->f10128 = 0;
            self->f10100 = 0;
            self->f10080 = 0;
            self->f10088 = 0;
            self->f10092 = 0;
            self->f10136 = 0;
            self->f10140 = 4;
            self->f10104 = 0;
            self->f10152 = 0;
            self->f10132 = 0;
            memset(self, 0, 1120);
            clr80116048(self);
        }
        __dt__9C800F92E8Fv(&self->m, -1);
        if (f > 0) __dl__FPv(self);
    }
    return self;
}

} /* extern "C" */
