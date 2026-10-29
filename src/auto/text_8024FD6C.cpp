// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { u32 v[3]; } T12_8024FD6C;
typedef struct { u32 a, b; } ID_8024FD6C;
typedef struct {
    u8 pad0[8];
    ID_8024FD6C id;
    u8 pad16[16];
    s32 f32;
    u8 pad36[4];
} E8024FD6C;
typedef struct {
    u8 pad0[4];
    s32 f4;
    u32 f8;
    u32 f12;
    E8024FD6C *f16;
} S8024FD6C;
extern void *lbl_8035B5A0;
extern void *lbl_8035B65C;
extern T12_8024FD6C lbl_802F20D0;
extern T12_8024FD6C lbl_802F20DC;
extern ID_8024FD6C lbl_80366498;
void fn_800604C4(s32 a, s32 b, s32 c, s32 d);
void fn_800F7EC0(void *heap);
void fn_800F7E98(void);
void *memcpy(void *d, const void *s, u32 n);
s32 fn_800F6CD0(ID_8024FD6C *a, ID_8024FD6C *b);
void fn_80253A90(void *mgr, S8024FD6C *self, T12_8024FD6C *f, ID_8024FD6C *id);
void fn_80253B24(void *mgr, S8024FD6C *self, T12_8024FD6C *f, ID_8024FD6C *id);
void fn_8024FD6C(S8024FD6C *self, u32 n, E8024FD6C *src, s32 flag) {
    void *mgr;
    u32 off;
    u32 i;
    if (self->f16 == 0) {
        if (lbl_8035B5A0 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B5A0);
        self->f16 = new E8024FD6C[100];
        fn_800F7E98();
        if (self->f16 == 0) fn_800604C4(-4, 0, 0, 0);
    }
    memcpy(&self->f16[self->f8], src, n * sizeof(E8024FD6C));
    mgr = lbl_8035B65C;
    for (i = self->f8, off = i * sizeof(E8024FD6C); i < self->f8 + n; off += sizeof(E8024FD6C), i++) {
        if (fn_800F6CD0(&((E8024FD6C *)((u8 *)self->f16 + off))->id, &lbl_80366498) == 0) {
            if (((E8024FD6C *)((u8 *)self->f16 + off))->f32 != 0) {
                T12_8024FD6C v = lbl_802F20D0;
                fn_80253A90(mgr, self, &v, &((E8024FD6C *)((u8 *)self->f16 + off))->id);
            } else {
                T12_8024FD6C v = lbl_802F20DC;
                fn_80253B24(mgr, self, &v, &((E8024FD6C *)((u8 *)self->f16 + off))->id);
            }
        }
    }
    self->f8 += n;
    if (flag) self->f12 = n;
    self->f4 = 1;
}

} /* extern "C" */
