// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern char lbl_802B4390[];
extern f32 lbl_8035CE28;

#pragma opt_propagation off
void fn_80046AB0(u8 *p) {
    char *s = lbl_802B4390;
    M2C_FIELD(p, s32 *, 84) = 39;
    M2C_FIELD(p, s32 *, 44) = 38;
    M2C_FIELD(p, s32 *, 104) = 10;
    M2C_FIELD(p, s32 *, 92) = 6;
    M2C_FIELD(p, s32 *, 128) = 7;
    M2C_FIELD(p, s32 *, 124) = 9;
    M2C_FIELD(p, s32 *, 132) = 0;
    M2C_FIELD(p, s32 *, 136) = 8;
    M2C_FIELD(p, s32 *, 140) = 0;
    M2C_FIELD(p, s32 *, 148) = 1;
    M2C_FIELD(p, char **, 88) = s + 964;
    M2C_FIELD(p, char **, 40) = s + 1120;
    M2C_FIELD(p, char **, 48) = s + 1576;
    M2C_FIELD(p, char **, 108) = s + 924;
    M2C_FIELD(p, char **, 120) = s + 808;
    M2C_FIELD(p, char **, 196) = s + 540;
    M2C_FIELD(p, char **, 200) = s + 568;
    M2C_FIELD(p, s32 *, 204) = 0;
    M2C_FIELD(p, char **, 244) = s + 676;
    M2C_FIELD(p, s32 *, 252) = 0;
    M2C_FIELD(p, char **, 268) = s + 904;
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
    M2C_FIELD(p, f32 *, 320) = lbl_8035CE28;
    M2C_FIELD(p, f32 *, 324) = lbl_8035CE28;
    M2C_FIELD(p, s32 *, 328) = 0;
    M2C_FIELD(p, s32 *, 332) = 0;
}
#pragma opt_propagation reset

} /* extern "C" */
