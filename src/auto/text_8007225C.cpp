// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct S7225C {
    u8 pad0[424];
    f32 f424;
    f32 f428;
    u8 pad1[1348 - 432];
    s32 *f1348;
    u8 pad2[1668 - 1352];
    s32 f1668;
} S7225C;

extern char lbl_80298060[];
extern void *lbl_8035B65C;
extern f32 lbl_8035F3EC;
extern f32 lbl_8035F3F8;
extern f32 lbl_8035F3FC;
f32 fn_802539FC(void *p);
double fn_800EFC38(double x);
void __ct__9C80253F24Fiiii(void *p, const char *s, s32 a, s32 b, s32 c);

void fn_8007225C(S7225C *s, f32 dt) {
    f32 scale;
    if (s->f1668 != 0) {
        scale = fn_802539FC(lbl_8035B65C);
        if (dt < lbl_8035F3EC) {
            dt *= scale;
        }
        s->f428 += dt;
        if (s->f428 > s->f424) {
            s->f428 = s->f424;
        }
        *s->f1348 = (s32)(f32)fn_800EFC38(s->f428);
        if (dt <= lbl_8035F3F8) {
            __ct__9C80253F24Fiiii(lbl_8035B65C, "RUMBLE_H", 0, 0, 0);
        } else if (dt <= lbl_8035F3FC) {
            __ct__9C80253F24Fiiii(lbl_8035B65C, "RUMBLE_M", 0, 0, 0);
        } else if (dt < lbl_8035F3EC) {
            __ct__9C80253F24Fiiii(lbl_8035B65C, "RUMBLE_L", 0, 0, 0);
        }
    }
}

} /* extern "C" */
