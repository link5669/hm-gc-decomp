// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_802B61A0[0x790];
extern char lbl_80359230[8];
extern f32 lbl_8035D34C;
extern f32 lbl_8035D368;

#pragma opt_propagation off
void fn_8004BAE0(u8 *p) {
    u8 *base = lbl_802B61A0;
    M2C_FIELD(p, s32 *, 84) = 26;
    M2C_FIELD(p, s32 *, 44) = 26;
    M2C_FIELD(p, s32 *, 104) = 7;
    M2C_FIELD(p, s32 *, 92) = 3;
    M2C_FIELD(p, s32 *, 128) = 3;
    M2C_FIELD(p, s32 *, 124) = 0;
    M2C_FIELD(p, s32 *, 132) = 2;
    M2C_FIELD(p, s32 *, 136) = 3;
    M2C_FIELD(p, s32 *, 140) = 1;
    M2C_FIELD(p, s32 *, 148) = 0;
    M2C_FIELD(p, u8 **, 88) = base + 696;
    M2C_FIELD(p, u8 **, 40) = base + 800;
    M2C_FIELD(p, u8 **, 48) = base + 1112;
    M2C_FIELD(p, u8 **, 108) = base + 668;
    M2C_FIELD(p, u8 **, 120) = base + 620;
    M2C_FIELD(p, u8 **, 196) = base + 540;
    M2C_FIELD(p, s32 *, 200) = 0;
    M2C_FIELD(p, u8 **, 204) = base + 552;
    M2C_FIELD(p, u8 **, 244) = base + 576;
    M2C_FIELD(p, char **, 252) = lbl_80359230;
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
    M2C_FIELD(p, s32 *, 356) = 0;
    M2C_FIELD(p, s32 *, 360) = 0;
    M2C_FIELD(p, s32 *, 364) = 0;
    M2C_FIELD(p, s32 *, 368) = 0;
    M2C_FIELD(p, s32 *, 372) = 0;
    M2C_FIELD(p, s32 *, 376) = 0;
    M2C_FIELD(p, s32 *, 380) = 0;
    M2C_FIELD(p, s32 *, 384) = 0;
    M2C_FIELD(p, s32 *, 388) = 0;
    M2C_FIELD(p, s32 *, 392) = 0;
    M2C_FIELD(p, s32 *, 396) = 0;
    M2C_FIELD(p, s32 *, 400) = 0;
    M2C_FIELD(p, f32 *, 404) = lbl_8035D34C;
    M2C_FIELD(p, f32 *, 408) = lbl_8035D34C;
    M2C_FIELD(p, f32 *, 412) = lbl_8035D34C;
    M2C_FIELD(p, s32 *, 416) = 0;
    M2C_FIELD(p, s32 *, 420) = 0;
    M2C_FIELD(p, s32 *, 424) = 0;
    M2C_FIELD(p, s32 *, 428) = 0;
    M2C_FIELD(p, s32 *, 432) = 1;
    M2C_FIELD(p, s32 *, 436) = 1;
    M2C_FIELD(p, s32 *, 440) = 0;
    M2C_FIELD(p, s32 *, 444) = 0;
    M2C_FIELD(p, s32 *, 448) = 0;
    M2C_FIELD(p, s32 *, 452) = 0;
    M2C_FIELD(p, s32 *, 456) = 1;
    M2C_FIELD(p, s32 *, 460) = 2;
    M2C_FIELD(p, s32 *, 464) = 0;
    M2C_FIELD(p, s32 *, 468) = 2;
    M2C_FIELD(p, s32 *, 472) = 1;
    M2C_FIELD(p, s32 *, 476) = 0;
    M2C_FIELD(p, f32 *, 480) = lbl_8035D368;
    M2C_FIELD(p, s32 *, 484) = 0;
    M2C_FIELD(p, s32 *, 488) = 1;
}
#pragma opt_propagation reset

} /* extern "C" */
