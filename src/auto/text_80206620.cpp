// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u8 lbl_802D8F60[], lbl_802D9060[], lbl_802D9160[], lbl_802D9260[], lbl_802D9360[], lbl_802D9460[];
extern f32 lbl_80365798, lbl_8036579C;
struct P { u8 pad[32]; f32 f32_; int f36; int f40; f32 f44; int f48; int f52; u8 pad56[36]; u32 f92; };
struct T { u8 pad[24]; u8 f24[8]; u8 f32[32]; int f64; u8 f68[8]; u8 f76[32]; int f108; };
void fn_800BB79C(void *);
void fn_800BB678(void *, u8 *, int, f32);
void fn_800BB744(void *);
void fn_800BBAC8(void *, void *);
void fn_80206620(T *t, P *p, void *x) {
    u8 *tbl;
    int n;
    if (p->f92 & 4) {
        f32 v = lbl_80365798 * p->f32_;
        switch (p->f36) {
        case 0: n = 64; tbl = lbl_802D8F60; break;
        case 1: n = 64; tbl = lbl_802D9060; break;
        case 2: n = 64; tbl = lbl_802D9160; break;
        case 3: n = 64; tbl = lbl_802D9260; break;
        case 4: n = 64; tbl = lbl_802D9360; break;
        case 5: n = 64; tbl = lbl_802D9460; break;
        }
        fn_800BB79C(t->f24);
        fn_800BB678(t->f32, tbl, n, v / lbl_8036579C);
        t->f64 = (p->f40 * 10) << 16;
        fn_800BBAC8(x, t->f24);
    }
    if (p->f92 & 8) {
        f32 v = lbl_80365798 * p->f44;
        switch (p->f48) {
        case 0: n = 64; tbl = lbl_802D8F60; break;
        case 1: n = 64; tbl = lbl_802D9060; break;
        case 2: n = 64; tbl = lbl_802D9160; break;
        case 3: n = 64; tbl = lbl_802D9260; break;
        case 4: n = 64; tbl = lbl_802D9360; break;
        case 5: n = 64; tbl = lbl_802D9460; break;
        }
        fn_800BB678(t->f76, tbl, n, v / lbl_8036579C);
        fn_800BB744(t->f68);
        t->f108 = p->f52 << 16;
        fn_800BBAC8(x, t->f68);
    }
}

} /* extern "C" */
