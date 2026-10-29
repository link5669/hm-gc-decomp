// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct Q { u8 pad[360]; s32 a360; u8 pad364[20]; s32 a384; u8 pad388[20]; s32 *p408; };
struct P { u8 pad[356]; void *w356; void *w360; Q *q364; };
extern f32 lbl_80364FFC;
void fn_801DB744(P *);
void fn_801BD8A0(void *, int, int, void *, f32);
void fn_801DD54C(P *, Q *);

s32 fn_801C4ED4(P *p) {
    fn_801DB744(p);
    {
        Q *q = p->q364;
        s32 v;
        if (!q) return 0;
        v = q->a360;
        if (v == 0 && q->a384 == 0) return 0;
        if (v) q->p408 = &q->a360;
        else q->p408 = &q->a384;
    }
    if (p->w360) {
        if (p->q364->a360) {
            fn_801BD8A0(p->w360, 0, 64, p, lbl_80364FFC);
            fn_801BD8A0(p->w356, 0, 2048, p, lbl_80364FFC);
            fn_801BD8A0(p->q364, 0, 256, p->w360, lbl_80364FFC);
            fn_801BD8A0(p->q364, 1, 512, p->w356, lbl_80364FFC);
            fn_801BD8A0(p->q364, 2, 1, p, lbl_80364FFC);
            fn_801BD8A0(p->q364, 3, 32, p, lbl_80364FFC);
        } else {
            fn_801BD8A0(p->w360, 0, 1, p, lbl_80364FFC);
            fn_801BD8A0(p->w356, 0, 32, p, lbl_80364FFC);
            fn_801BD8A0(p->q364, 0, 8, p->w356, lbl_80364FFC);
            fn_801BD8A0(p->q364, 1, 4, p->w360, lbl_80364FFC);
            fn_801BD8A0(p->q364, 2, 64, p, lbl_80364FFC);
            fn_801BD8A0(p->q364, 3, 2048, p, lbl_80364FFC);
        }
        fn_801DD54C(p, p->q364);
    } else {
        if (p->q364->a360) {
            fn_801BD8A0(p->q364, 0, 2048, p, lbl_80364FFC);
            fn_801BD8A0(p->q364, 1, 64, p, lbl_80364FFC);
            fn_801BD8A0(p->q364, 2, 1, p, lbl_80364FFC);
            fn_801BD8A0(p->q364, 3, 32, p, lbl_80364FFC);
        } else {
            fn_801BD8A0(p->q364, 0, 8, p, lbl_80364FFC);
            fn_801BD8A0(p->q364, 1, 4, p, lbl_80364FFC);
            fn_801BD8A0(p->q364, 2, 64, p, lbl_80364FFC);
            fn_801BD8A0(p->q364, 3, 2048, p, lbl_80364FFC);
        }
    }
    return 0;
}

} /* extern "C" */
