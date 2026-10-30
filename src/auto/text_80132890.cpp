// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct X4 { u8 pad[4]; u16 f; };
struct G { u8 pad[12]; X4 *x; u8 sub[112]; u32 f128; };
struct W {
    u8 pad[220]; u32 f220; u8 pad2[12]; u32 f236; u8 pad3[4];
    virtual void a0(void *, u32, u16); virtual void a1(void *, u32, u16); virtual void a2(void *, u32, int, u32, u32, u16);
    virtual void b0(void *, u32, u16); virtual void b1(void *, u32, u16); virtual void b2(void *, u32, int, u32, u32, u16);
};
struct T { u32 f0; u8 pad[12]; u32 f16; u32 f20; u32 f24; u8 pad2[8]; u16 f36; u8 pad3[2]; u16 f40; u16 cnt; u8 b[1]; };
extern "C" {
extern G *lbl_8035AC5C;
void fn_80138D8C(W *);
void fn_80138D34(W *, u8, u32);
void fn_80138CBC(W *, u32);
void fn_80138C44(W *, u32);
void fn_80132890(T *t, W *w, int c) {
    u32 i;
    if (t->f0 == 0) return;
    if (t->cnt == 0) {
        fn_80138D8C(w);
    } else {
        for (i = 0; i < t->cnt; i++) {
            u8 v = t->b[i];
            if (v != 0 && (w->f236 & 1)) return;
            fn_80138D34(w, v, i);
        }
        w->f220 = t->cnt;
    }
    fn_80138CBC(w, t->f0);
    if (c) {
        if (t->f36 & 4) w->b0(lbl_8035AC5C->sub, t->f20, t->f40);
        else if (t->f36 & 8) w->b1(lbl_8035AC5C->sub, t->f20, t->f40);
        else if (t->f36 & 0x10) { fn_80138C44(w, t->f16); w->b2(lbl_8035AC5C->sub, lbl_8035AC5C->f128, (lbl_8035AC5C->x->f >> 5) & 1, t->f20, t->f24, t->f40); }
        else if (t->f36 & 0x40) { fn_80138C44(w, t->f16); w->b2(lbl_8035AC5C->sub, lbl_8035AC5C->f128, (lbl_8035AC5C->x->f >> 5) & 1, 0, t->f24, t->f40); }
    } else {
        if (t->f36 & 4) w->a0(lbl_8035AC5C->sub, t->f20, t->f40);
        else if (t->f36 & 8) w->a1(lbl_8035AC5C->sub, t->f20, t->f40);
        else if (t->f36 & 0x10) { fn_80138C44(w, t->f16); w->a2(lbl_8035AC5C->sub, lbl_8035AC5C->f128, (lbl_8035AC5C->x->f >> 5) & 1, t->f20, t->f24, t->f40); }
        else if (t->f36 & 0x40) { fn_80138C44(w, t->f16); w->a2(lbl_8035AC5C->sub, lbl_8035AC5C->f128, (lbl_8035AC5C->x->f >> 5) & 1, 0, t->f24, t->f40); }
    }
}

} /* extern "C" */
