// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct G_80039EA4 { u8 pad[11]; u8 b11; u8 pad12[32]; u32 f44; };
struct S_80039EA4 { u8 pad[28]; f32 f28; s32 f32_; f32 f36; G_80039EA4 *f40; };
extern f32 lbl_8035C08C;
extern f32 lbl_8035C090;
extern u32 lbl_8035C088;
void fn_80039EA4(S_80039EA4 *p, f32 f) {
    G_80039EA4 *g;
    f32 d;
    if (p->f32_ != 0) {
        d = (f32)p->f32_ * (lbl_8035C08C * f / p->f36);
        p->f28 += d;
        if (p->f28 >= lbl_8035C08C && p->f32_ > 0) {
            p->f28 = lbl_8035C08C;
            p->f32_ = 0;
        } else if (p->f28 <= lbl_8035C090 && p->f32_ < 0) {
            p->f28 = lbl_8035C090;
            p->f32_ = 0;
        }
        g = p->f40;
        g->b11 = (u8)p->f28;
        g->f44 |= lbl_8035C088;
    }
}

} /* extern "C" */
