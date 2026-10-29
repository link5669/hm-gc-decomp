// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern char lbl_802C5100[];
extern char lbl_80359318[8];
extern f32 lbl_8035FD94;

#pragma opt_propagation off
void fn_80084DC0(u8 *p) {
    char *s = lbl_802C5100;
    *(s32 *)(p + 84) = 10;
    *(s32 *)(p + 44) = 10;
    *(s32 *)(p + 104) = 5;
    *(s32 *)(p + 92) = 3;
    *(s32 *)(p + 128) = 1;
    *(s32 *)(p + 124) = 0;
    *(s32 *)(p + 132) = 0;
    *(s32 *)(p + 136) = 2;
    *(s32 *)(p + 140) = 0;
    *(s32 *)(p + 148) = 0;
    *(char **)(p + 88) = s + 636;
    *(char **)(p + 40) = s + 676;
    *(char **)(p + 48) = s + 796;
    *(char **)(p + 108) = s + 616;
    *(char **)(p + 120) = s + 568;
    *(char **)(p + 196) = lbl_80359318;
    *(s32 *)(p + 200) = 0;
    *(s32 *)(p + 204) = 0;
    *(char **)(p + 244) = s + 540;
    *(s32 *)(p + 252) = 0;
    *(s32 *)(p + 268) = 0;
    *(s32 *)(p + 280) = 0;
    *(s32 *)(p + 284) = 0;
    *(s32 *)(p + 288) = 0;
    *(s32 *)(p + 292) = 0;
    *(s32 *)(p + 296) = 0;
    *(s32 *)(p + 300) = 0;
    *(s32 *)(p + 304) = 0;
    *(s32 *)(p + 308) = 0;
    *(s32 *)(p + 312) = 0;
    *(f32 *)(p + 316) = lbl_8035FD94;
    *(s32 *)(p + 320) = 0;
    *(s32 *)(p + 324) = 1;
    *(f32 *)(p + 328) = lbl_8035FD94;
    *(s32 *)(p + 332) = 0;
    *(s32 *)(p + 336) = 0;
}
#pragma opt_propagation reset

} /* extern "C" */
