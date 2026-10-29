// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void *memset(void *, int, u32);
void fn_8016B564(void);
void fn_8012163C(void *);
extern f32 lbl_803646D8;
extern f32 lbl_803646F8;
extern f32 lbl_80364704;

#pragma opt_common_subs off
void fn_8016CC50(u8 *p) {
    M2C_FIELD(p, s32 *, 832) = 0;
    M2C_FIELD(p, s32 *, 7952) = 0;
    M2C_FIELD(p, s32 *, 7956) = 0;
    M2C_FIELD(p, s32 *, 836) = 0;
    memset(p + 7960, 0, 8);
    M2C_FIELD(p, s32 *, 7968) = 0;
    M2C_FIELD(p, s32 *, 7972) = 0;
    M2C_FIELD(p, s32 *, 7976) = 0;
    M2C_FIELD(p, s32 *, 7980) = 0;
    M2C_FIELD(p, s32 *, 7984) = 0;
    M2C_FIELD(p, s32 *, 7988) = 0;
    M2C_FIELD(p, s32 *, 7992) = 0;
    M2C_FIELD(p, s32 *, 7996) = 0;
    M2C_FIELD(p, s32 *, 8000) = 0;
    M2C_FIELD(p, s32 *, 10872) = 0;
    M2C_FIELD(p, s32 *, 10892) = 0;
    M2C_FIELD(p, s32 *, 10876) = 0;
    M2C_FIELD(p, s32 *, 10880) = 0;
    M2C_FIELD(p, s32 *, 10884) = 0;
    M2C_FIELD(p, s32 *, 10888) = 0;
    M2C_FIELD(p, s32 *, 10896) = 0;
    M2C_FIELD(p, s32 *, 10900) = 0;
    M2C_FIELD(p, s32 *, 10904) = 0;
    M2C_FIELD(p, s32 *, 10908) = 0;
    M2C_FIELD(p, u8 **, 10912) = p + 10916;
    memset(p + 10916, 0, 1024);
    memset(p + 11940, 0, 1024);
    memset(p + 14012, 0, 1024);
    memset(p + 15036, 0, 1024);
    memset(p + 16060, 0, 80);
    M2C_FIELD(p, s32 *, 16140) = 0;
    memset(p + 16144, 0, 0x8000);
    M2C_FIELD(p, s32 *, 147396) = 0;
    memset(p + 128956, 0, 18432);
    M2C_FIELD(p, s32 *, 147388) = 0;
    M2C_FIELD(p, s32 *, 147392) = 0;
    M2C_FIELD(p, s32 *, 147396) = 0;
    M2C_FIELD(p, s32 *, 162248) = 0;
    M2C_FIELD(p, void **, 162256) = (void *)fn_8016B564;
    M2C_FIELD(p, s32 *, 162260) = 0;
    M2C_FIELD(p, s32 *, 162264) = 0;
    M2C_FIELD(p, s32 *, 812) = 2;
    M2C_FIELD(p, s32 *, 10144) = 0;
    M2C_FIELD(p, s32 *, 10148) = 1;
    M2C_FIELD(p, s32 *, 10152) = 1;
    M2C_FIELD(p, s32 *, 10156) = 0;
    M2C_FIELD(p, s32 *, 10160) = 0;
    M2C_FIELD(p, s32 *, 10164) = 0;
    fn_8012163C(p + 162268);
    M2C_FIELD(p, s32 *, 162272) = 2;
    M2C_FIELD(p, f32 *, 162276) = lbl_803646D8;
    M2C_FIELD(p, f32 *, 162280) = lbl_803646F8;
    M2C_FIELD(p, f32 *, 162284) = lbl_803646F8;
    M2C_FIELD(p, f32 *, 162288) = lbl_80364704;
    memset(p + 820, 0, 7);
    M2C_FIELD(p, s32 *, 162292) = 0;
    M2C_FIELD(p, s32 *, 162296) = 2;
}
#pragma opt_common_subs reset

} /* extern "C" */
