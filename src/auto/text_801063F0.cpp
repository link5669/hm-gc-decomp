/* Functions from 0x801063F0 to 0x801064C4, found by decomp-toolkit. */
#include "common.h"

extern "C" {

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 unk18;
    u8 pad19[7];
    f32 unk20[3][4];
} Unk801063F0;

extern f32 lbl_803638A8;
extern f32 lbl_803638AC;
extern f32 lbl_803638C0;

void __ct__9C801063F0Fv(Unk801063F0* arg0) {
    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    arg0->unk14 = 0;
    arg0->unk18 = 0;
    arg0->unk20[0][0] = lbl_803638A8;
    arg0->unk20[0][1] = lbl_803638A8;
    arg0->unk20[0][2] = lbl_803638A8;
    arg0->unk20[0][3] = lbl_803638AC;
    arg0->unk20[1][0] = lbl_803638A8;
    arg0->unk20[1][1] = lbl_803638A8;
    arg0->unk20[1][2] = lbl_803638A8;
    arg0->unk20[1][3] = lbl_803638AC;
    arg0->unk20[2][0] = lbl_803638A8;
    arg0->unk20[2][1] = lbl_803638A8;
    arg0->unk20[2][2] = lbl_803638A8;
    arg0->unk20[2][3] = lbl_803638AC;
}

extern f32 lbl_803638A8;
extern f32 lbl_803638AC;
extern f32 lbl_803638C0;

/* QV=2.0p1 */
typedef struct V80106474 { f32 x, y, z; } V80106474;
typedef struct S80106474 { u8 pad[20]; V80106474 n; u8 pad2[12]; V80106474 r; } S80106474;
void fn_80106474(S80106474* p, const V80106474* v) {
    f32 d = lbl_803638C0 * (p->n.x * v->x + p->n.y * v->y + p->n.z * v->z);
    p->r.x = v->x - d * p->n.x;
    p->r.y = v->y - d * p->n.y;
    p->r.z = v->z - d * p->n.z;
}

} /* extern "C" */
