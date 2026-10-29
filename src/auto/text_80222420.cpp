/* Functions from 0x80222420 to 0x80222514, found by decomp-toolkit. */
#include "common.h"

extern "C" {

typedef struct {
    u8 pad0[0x8];
    f32 unk8;
    u8 padC[0x4];
    f32* unk10;
    u8 pad14[0x24 - 0x14];
    f32 unk24;
    f32 unk28;
    u8 pad2C[0x3C - 0x2C];
} UnkEntry_80222420;

typedef struct {
    u8 pad0[0xB0];
    UnkEntry_80222420* unkB0;
} UnkB0Owner_80222420;

typedef struct {
    u8 pad0[0xA0];
    UnkB0Owner_80222420* unkA0;
} UnkA0Owner_80222420;

typedef struct {
    f32 unk0;
    f32 unk4;
    s32 unk8;
    UnkA0Owner_80222420* unkC;
} Unk_80222420;

extern f32 lbl_80365A30;
extern f32 lbl_80365A34;


typedef struct {
    u8 pad0[0x8];
    f32 unk8;
    u8 padC[0x4];
    f32* unk10;
    u8 pad14[0x24 - 0x14];
    f32 unk24;
    f32 unk28;
    u8 pad2C[0x3C - 0x2C];
} E_80222420w;

typedef struct {
    u8 pad0[0xB0];
    E_80222420w* unkB0;
} B_80222420w;

typedef struct {
    u8 pad0[0xA0];
    B_80222420w* unkA0;
} A_80222420w;

typedef struct {
    f32 unk0;
    f32 unk4;
    s32 unk8;
    A_80222420w* unkC;
} S_80222420w;


#pragma opt_common_subs off
void fn_80222420(S_80222420w* arg0, f32 farg0) {
    A_80222420w* temp_r4;
    B_80222420w* temp_r6;
    s32 other;

    temp_r4 = arg0->unkC;
    if (temp_r4 == 0) {
        return;
    }
    temp_r6 = temp_r4->unkA0;
    if (temp_r6 == 0) {
        return;
    }
    other = arg0->unk8 != 1;
    if (lbl_80365A30 == arg0->unk0) {
        arg0->unk4 = lbl_80365A34;
    } else {
        arg0->unk4 += (f32)__fabs(farg0) / arg0->unk0;
        if (arg0->unk4 >= lbl_80365A34) {
            arg0->unk4 = lbl_80365A34;
        }
    }
    ((f32(*)[15])temp_r6->unkB0)[other][10] = lbl_80365A34 - arg0->unk4;
    ((f32(*)[15])temp_r6->unkB0)[arg0->unk8][10] = arg0->unk4;
}
void fn_802224D0(Unk_80222420* arg0, f32 farg0) {
    UnkEntry_80222420* e;
    f32* d;

    if (arg0->unkC == NULL) {
        return;
    }
    e = &arg0->unkC->unkA0->unkB0[arg0->unk8];
    e->unk8 = farg0;
    d = e->unk10;
    if (d != NULL) {
        e->unk24 = e->unk8 / d[1];
    }
}

#pragma opt_common_subs reset

} /* extern "C" */
