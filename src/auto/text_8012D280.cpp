// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct R8012D280 { u8 pad[0x124]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void err(s32); };
struct P8012D280 { u8 pad[8]; u32 f8; u8 pad2[16]; f32 f28; f32 f32_; u8 sub[8]; };
extern "C" {
f32 fn_800FB2E0(R8012D280 *);
void fn_80121CE8(void *, R8012D280 *);
extern u32 lbl_80363E9C, lbl_80363EA0, lbl_80363EA4, lbl_80363EA8;
void fn_8012D280(P8012D280 *p, void *x, R8012D280 *r, u32 k) {
    switch (k) {
    case 62: p->f28 = fn_800FB2E0(r); break;
    case 76: p->f32_ = fn_800FB2E0(r); break;
    case 65: p->f8 |= lbl_80363E9C; fn_80121CE8(p->sub, r); break;
    case 70: p->f8 |= lbl_80363EA0; break;
    case 71: p->f8 |= lbl_80363EA4; break;
    case 75: p->f8 |= lbl_80363EA8; break;
    default: r->err(30); break;
    }
}

} /* extern "C" */
