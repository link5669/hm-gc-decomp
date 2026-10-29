// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_803596E0[];
extern volatile f32 lbl_8035B3A4;
extern volatile f32 lbl_8035B3A0;
extern volatile f64 lbl_80365FD0;
double fn_800EFDA4(double);
void *fn_8023DC5C(void *, void *, void *, void *, s32);
void __register_global_object(void *, void *, void *);
static u8 lbl_80357058[12];
static u8 lbl_80357064[36];
static u8 lbl_80357088[12];
static u8 lbl_80357094[36];
extern u8 lbl_802A8A70[];
extern char lbl_80365FD8[6];
extern char lbl_80365FE0[8];
void fn_80239BAC(void);
void fn_800375E4(void);

void fn_80239D0C(void) {
    lbl_8035B3A4 = lbl_803596E0[0];
    lbl_8035B3A0 = fn_800EFDA4(lbl_80365FD0);
    __register_global_object(fn_8023DC5C(lbl_80357064, lbl_802A8A70, lbl_80365FD8, (void *)fn_80239BAC, 596), (void *)fn_800375E4, lbl_80357058);
    __register_global_object(fn_8023DC5C(lbl_80357094, lbl_802A8A70, lbl_80365FE0, (void *)fn_80239BAC, 596), (void *)fn_800375E4, lbl_80357088);
}

__declspec(section ".ctors") static void (*const ctor_80239D0C)(void) = fn_80239D0C;

} /* extern "C" */
