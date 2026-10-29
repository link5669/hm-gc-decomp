// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct Out_8016F10C { u32 a, b, c, d, e; };
struct Q_8016F10C { u16 h0; u16 h2; u8 pad[12]; u16 h10; u16 h12; u16 h14; u16 h16; u16 h18; };
struct P_8016F10C { u32 type; };
extern Out_8016F10C lbl_8032ED08;
extern u32 lbl_8035AD34;
void fn_80156110(s32, Out_8016F10C *);
void fn_8016E750(Q_8016F10C *, P_8016F10C *, u32);
void fn_8016F10C(Q_8016F10C *q, P_8016F10C *p, s32 n, u32 f) {
    if (n == 0) n = p->type;
    lbl_8035AD34 = 0;
    q->h2 = 0;
    q->h10 = n;
    lbl_8032ED08.d = 0;
    if (n != 0) {
        fn_80156110(n, &lbl_8032ED08);
        q->h14 = lbl_8032ED08.a;
        q->h16 = lbl_8032ED08.b;
        q->h18 = lbl_8032ED08.c;
    }
    fn_8016E750(q, p, f);
}

} /* extern "C" */
