// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
#pragma readonly_strings on
extern volatile u32 lbl_80359FB0;
extern s8 lbl_80359FB4;
extern f32 lbl_8035BD48;
extern f32 lbl_8035BD4C;
extern void *volatile lbl_8035B7BC;
extern u8 *lbl_8035A1DC;
u32 fn_801AA960(void *, const char *, const char *);
void fn_8026BBF8(void *);
void fn_8026BD38(void *);
void fn_8003AD38(void *, const char *, s32, s32, s32);

struct S120_800316C8 { u32 f0; u32 f4; u32 f8; u32 f12; };
struct S36_800316C8 { u8 pad[13232]; void *f13232; };
struct S_800316C8 {
    u8 pad[36];
    S36_800316C8 *f36;
    u8 pad40[80];
    S120_800316C8 *f120;
    u8 pad124[2980];
    f32 f3104;
    s32 f3108;
    u32 f3112;
    u32 f3116;
};

void fn_800316C8(S_800316C8 *self, f32 dt) {
    u32 x;
    u32 y;
    u32 r;
    if (!lbl_80359FB4) {
        lbl_80359FB0 = 0;
        lbl_80359FB4 = 1;
    }
    x = self->f120->f4;
    r = fn_801AA960(self->f36->f13232, "MAINMENU", "MainMenu");
    y = self->f120->f12;
    if (x != self->f3112) {
        if (x != r) {
            self->f3104 = lbl_8035BD48;
            self->f3108 = 0;
        } else {
            self->f3104 = lbl_8035BD48;
            self->f3108 = 1;
        }
        self->f3112 = x;
    }
    if (self->f3108 == 0) return;
    if (y != self->f3116) {
        self->f3104 = lbl_8035BD48;
        self->f3116 = y;
        return;
    }
    self->f3104 -= dt;
    if (self->f3104 <= lbl_8035BD4C) {
        fn_8026BBF8(lbl_8035B7BC);
        {
            u32 idx = lbl_80359FB0;
            if (idx == 0) {
                fn_8003AD38(lbl_8035A1DC + 13616, "HMDem130", 1, 0, 1);
            } else if (idx == 1) {
                fn_8003AD38(lbl_8035A1DC + 13616, "HMDem230", 1, 0, 1);
            } else {
                fn_8003AD38(lbl_8035A1DC + 13616, "HM_Intro", 1, 0, 1);
            }
        }
        lbl_80359FB0++;
        lbl_80359FB0 %= 3;
        fn_8026BD38(lbl_8035B7BC);
        self->f3104 = lbl_8035BD48;
        self->f3108 = 1;
    }
}
#pragma readonly_strings reset

} /* extern "C" */
