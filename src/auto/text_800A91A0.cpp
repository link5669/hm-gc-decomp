// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_802D1B48[];
extern u8 lbl_80359470[8];
extern f32 lbl_803620E8;


void fn_800A91A0(u8 *p) {
    u8 *base = lbl_802D1B48;
    M2C_FIELD(p, s32 *, 84) = 6;
    M2C_FIELD(p, s32 *, 44) = 6;
    M2C_FIELD(p, s32 *, 104) = 3;
    M2C_FIELD(p, s32 *, 92) = 2;
    M2C_FIELD(p, s32 *, 128) = 2;
    M2C_FIELD(p, s32 *, 124) = 0;
    M2C_FIELD(p, s32 *, 132) = 2;
    M2C_FIELD(p, s32 *, 136) = 3;
    M2C_FIELD(p, s32 *, 140) = 0;
    M2C_FIELD(p, s32 *, 148) = 0;
    M2C_FIELD(p, u8 **, 88) = base + 652;
    M2C_FIELD(p, u8 **, 40) = base + 676;
    M2C_FIELD(p, u8 **, 48) = base + 748;
    M2C_FIELD(p, u8 **, 108) = base + 640;
    M2C_FIELD(p, u8 **, 120) = base + 608;
    M2C_FIELD(p, u8 **, 196) = lbl_80359470;
    M2C_FIELD(p, s32 *, 200) = 0;
    M2C_FIELD(p, u8 **, 204) = base + 540;
    M2C_FIELD(p, u8 **, 244) = base + 564;
    M2C_FIELD(p, s32 *, 252) = 0;
    M2C_FIELD(p, s32 *, 268) = 0;
    M2C_FIELD(p, s32 *, 280) = 0;
    M2C_FIELD(p, s32 *, 284) = 0;
    M2C_FIELD(p, s32 *, 288) = 0;
    M2C_FIELD(p, s32 *, 292) = 0;
    M2C_FIELD(p, s32 *, 296) = 0;
    M2C_FIELD(p, s32 *, 300) = 0;
    M2C_FIELD(p, s32 *, 304) = 0;
    M2C_FIELD(p, s32 *, 308) = 0;
    M2C_FIELD(p, s32 *, 312) = 0;
    M2C_FIELD(p, s32 *, 316) = 0;
    M2C_FIELD(p, s32 *, 320) = 0;
    M2C_FIELD(p, s32 *, 324) = 0;
    M2C_FIELD(p, s32 *, 328) = 0;
    M2C_FIELD(p, s32 *, 332) = 0;
    M2C_FIELD(p, s32 *, 336) = 0;
    M2C_FIELD(p, s32 *, 340) = 0;
    M2C_FIELD(p, s32 *, 344) = 0;
    M2C_FIELD(p, s32 *, 348) = 0;
    M2C_FIELD(p, s32 *, 352) = 0;
    M2C_FIELD(p, s32 *, 496) = 1;
    M2C_FIELD(p, f32 *, 500) = lbl_803620E8;
    M2C_FIELD(p, s32 *, 504) = 0;
}

} /* extern "C" */
