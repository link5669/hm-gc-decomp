// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct El80222514;
struct Cb80222514 {
    u32 pad;
    virtual void f0();
    virtual void f1(El80222514 *);
};
struct El80222514 {
    u32 flags;
    f32 f4;
    u8 pad8[4];
    Cb80222514 *cb;
    u32 f10;
    u8 pad14[20];
    f32 f28;
    u8 pad2c[4];
    u32 f30;
    u8 pad34[8];
};
struct Res80222514 { u8 pad[176]; El80222514 *els; };
struct Own80222514 { u8 pad[160]; Res80222514 *res; };
struct S80222514 {
    f32 unk0;
    f32 unk4;
    u32 unk8;
    Own80222514 *unkC;
};

extern const u32 lbl_80365A38;
extern const u32 lbl_80365A3C;
extern const u32 lbl_80365A40;
extern f32 lbl_80365A30;
extern f32 lbl_80365A34;
extern f32 lbl_80365A44;
extern f32 lbl_80365A48;
void fn_80103BB4(El80222514 *, u32);

void fn_80222514(S80222514 *self, u32 key, s32 flag, f32 val) {
    Res80222514 *res;
    El80222514 *e;
    u32 old;

    if (self->unkC == 0) return;
    res = self->unkC->res;
    if (res == 0) return;
    e = &res->els[self->unk8];
    if (e->f10 == key && !(e->flags & 0x10)) return;
    self->unk0 = val;
    old = self->unk8;
    if (old == 0) {
        self->unk8 = 1;
    } else {
        self->unk8 = 0;
    }
    if (val >= lbl_80365A44 && val <= lbl_80365A48) {
        ((f32(*)[15])res->els)[old][10] = lbl_80365A30;
        ((f32(*)[15])res->els)[self->unk8][10] = lbl_80365A34;
    } else {
        ((f32(*)[15])res->els)[old][10] = lbl_80365A34;
        ((f32(*)[15])res->els)[self->unk8][10] = lbl_80365A30;
    }
    e = &res->els[old];
    if (e->f30 & 1) e->flags &= ~2;
    e = &res->els[self->unk8];
    fn_80103BB4(e, key);
    e->flags |= lbl_80365A38;
    if (e->cb != 0) e->cb->f1(e);
    e->f30 |= lbl_80365A3C;
    e = &res->els[self->unk8];
    if (flag) {
        e->flags |= lbl_80365A40;
    } else {
        e->flags &= ~4;
    }
    self->unk4 = lbl_80365A30;
}

} /* extern "C" */
