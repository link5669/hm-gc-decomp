// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void __ct__9C80239B40Fv(void *);
extern void *lbl_802F17C8[];
extern volatile f32 lbl_80365E88;
} /* extern "C" */

struct S80234EC8 {
    void **vt;
    u8 pad4[592];
    u32 arr[100];
    u32 f996;
    u32 f1000;
    u32 f1004;
    u32 f1008;
    u32 f1012;
    u32 f1016;
    u32 f1020;
    u32 f1024;
    u32 f1028;
    u32 f1032;
    u8 f1036;
    u8 pad1037[7];
    u8 f1044;
    u8 pad1045[7];
    u32 f1052;
    u32 f1056;
    f32 f1060;
    u32 f1064;
    u32 f1068;
    u32 f1072;
    u32 f1076;
    u32 f1080;
    u32 f1084;
    f32 f1088;
    f32 f1092;
    f32 f1096;
    u32 f1100;
};

static inline void clr_80234EC8(S80234EC8 *s) {
    u32 i;
    for (i = 0; i < 100; i++) {
        s->arr[i] = 0;
    }
}

extern "C" {
S80234EC8 *fn_80234EC8(S80234EC8 *self) {
    __ct__9C80239B40Fv(self);
    self->vt = lbl_802F17C8;
    clr_80234EC8(self);
    self->f996 = 0;
    self->f1000 = 0;
    self->f1004 = 0;
    self->f1008 = 0;
    self->f1024 = 0;
    self->f1028 = 0;
    self->f1012 = 0;
    self->f1016 = 0;
    self->f1032 = 0;
    self->f1068 = 0;
    self->f1072 = 1;
    self->f1036 = 0;
    self->f1044 = 0;
    self->f1056 = 0;
    self->f1060 = lbl_80365E88;
    self->f1052 = 0;
    self->f1064 = 0;
    self->f1080 = 0;
    self->f1084 = 0;
    self->f1088 = lbl_80365E88;
    self->f1092 = lbl_80365E88;
    self->f1096 = lbl_80365E88;
    self->f1100 = 0;
    return self;
}

} /* extern "C" */
