/* Functions from 0x801018FC to 0x80101A90, found by decomp-toolkit. */
#include "common.h"

extern "C" {

typedef struct {
    u32 unk0;
    u32 unk4;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} UnkStruct_801018FC;

extern u32 lbl_80363848;

void fn_801018FC(f32 *out, f32 *a, f32 *b, f32 t) {
    f32 x = a[0];
    f32 ry, rz, rw;
    f32 y = a[1], z = a[2], w = a[3];
    x = t * (b[0] - x) + x;
    ry = t * (b[1] - y) + y;
    rz = t * (b[2] - z) + z;
    rw = t * (b[3] - w) + w;
    out[0] = x;
    out[1] = ry;
    out[2] = rz;
    out[3] = rw;
}

void fn_80101950(UnkStruct_801018FC *arg0) {
    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unk9 = 0;
    arg0->unkA = 0;
    arg0->unkB = 0;
}

void fn_801019A4(UnkStruct_801018FC *arg0, u32 arg1, u32 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6);
void fn_80101970(UnkStruct_801018FC *__restrict arg0, UnkStruct_801018FC *__restrict arg1) {
    arg0->unk0 = arg1->unk0;
    arg0->unk4 = arg1->unk4;
    arg0->unk8 = arg1->unk8;
    arg0->unk9 = arg1->unk9;
    arg0->unkA = arg1->unkA;
    arg0->unkB = arg1->unkB;
}

void fn_801019A4(UnkStruct_801018FC *arg0, u32 arg1, u32 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6) {
    if (arg2 < 1) {
        arg1 &= ~0x200;
    } else {
        if (arg2 > 4) {
            arg2 = 4;
        }
        arg1 |= lbl_80363848;
    }
    arg0->unk0 = arg1;
    arg0->unk4 = arg2;
    arg0->unk8 = arg3;
    arg0->unk9 = arg4;
    arg0->unkA = arg5;
    arg0->unkB = arg6;
}

typedef struct { u32 flags; u32 n; u8 f8; u8 f9; u8 f10; u8 f11; } S801019E4;

#pragma opt_propagation off
#pragma optimization_level 1
void fn_801019E4(S801019E4 *s, u32 flags, u32 n) {
    u8 t;
    u8 v;
    if (n < 1) {
        flags &= ~0x200;
        s->f9 = 0;
    } else {
        s->f9 = 31;
        if (n > 4) n = 4;
        flags |= lbl_80363848;
    }
    s->flags = flags;
    v = 31;
    s->n = n;
    s->f8 = v;
    t = 0;
    if (s->flags & 0x800) t = v;
    s->f11 = t;
    t = 0;
    if (s->flags & 0x400) t = 8;
    s->f10 = t;
}
#pragma optimization_level reset
#pragma opt_propagation reset



void fn_80101A5C(UnkStruct_801018FC *arg0) {
    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unk9 = 0;
    arg0->unkA = 0;
    arg0->unkB = 0;
}

extern u32 lbl_802E22B8[];
u32 fn_80101A7C(s32 arg0) {
    return lbl_802E22B8[arg0];
}

} /* extern "C" */
