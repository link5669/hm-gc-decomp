// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct S80234C94 {
    u8 pad0[596];
    s32 arr[100];
    s32 f996;
    s32 f1000;
    s32 f1004;
    s32 f1008;
    s32 f1012;
    s32 f1016;
    u8 pad1020[4];
    s32 f1024;
    s32 f1028;
    s32 f1032;
    u8 f1036;
    u8 pad1037[7];
    u8 f1044;
    u8 pad1045[7];
    s32 f1052;
    s32 f1056;
    f32 f1060;
    s32 f1064;
    s32 f1068;
    s32 f1072;
    u8 pad1076[4];
    s32 f1080;
    s32 f1084;
    f32 f1088;
    f32 f1092;
    f32 f1096;
    s32 f1100;
} S80234C94;
extern f32 lbl_80365E88;
void fn_80238BF4(S80234C94 *);

static inline void fill80234C94(s32 *p, s32 v, u32 n) { u32 i; for (i = 0; i < n; i++) p[i] = v; }
void fn_80234C94(S80234C94 *self) {
    fill80234C94(self->arr, 0, 100);
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
    fn_80238BF4(self);
}

} /* extern "C" */
