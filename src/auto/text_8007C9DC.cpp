// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct S16_7C { u8 pad[4]; f32 f4; u8 pad2[44]; u16 f52; };
struct S176_7C { u8 pad[4]; f32 f4; u8 pad2[8]; S16_7C *f16; };
struct S340_7C { u8 pad[176]; S176_7C *f176; };
struct P7C { u8 pad[340]; S340_7C *f340; u8 pad2[28]; s32 f372; u8 pad3[4]; s32 f380; u8 pad4[12]; u32 f396; };
extern f32 lbl_8035F910;
void fn_802494A4(P7C *, s32);
void fn_802490E0(P7C *, s32, f32);
void fn_8007C9DC(P7C *p) {
    p->f396--;
    if (p->f396 == 0) {
        p->f372 = 0;
        fn_802494A4(p, 2);
    }
    p->f380 = 1;
    p->f340->f176->f4 = lbl_8035F910;
    fn_802490E0(p, 1, (f32)p->f340->f176->f16->f52 / p->f340->f176->f16->f4);
}

} /* extern "C" */
