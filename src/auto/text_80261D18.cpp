// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_803596E0[];
extern volatile f32 lbl_8035B734;
extern volatile f32 lbl_8035B730;
extern volatile f64 lbl_80366A98;
double fn_800EFDA4(double);
void __ct__9C8002FAE0Fv(void);
void __construct_array(void *, void *, void *, u32, u32);
static u8 s0[96];
static u8 s1[96];
static u8 s2[96];
static u8 s3[96];
static u8 s4[192];
static u8 s5[96];
static u8 s6[64];

void fn_80261D18(void) {
    lbl_8035B734 = lbl_803596E0[0];
    lbl_8035B730 = fn_800EFDA4(lbl_80366A98);
    __construct_array(s0, (void *)__ct__9C8002FAE0Fv, 0, 12, 8);
    __construct_array(s1, (void *)__ct__9C8002FAE0Fv, 0, 12, 8);
    __construct_array(s2, (void *)__ct__9C8002FAE0Fv, 0, 12, 8);
    __construct_array(s3, (void *)__ct__9C8002FAE0Fv, 0, 12, 8);
    __construct_array(s5, (void *)__ct__9C8002FAE0Fv, 0, 12, 8);
}

__declspec(section ".ctors") static void (*const ctor_80261D18)(void) = fn_80261D18;

} /* extern "C" */
