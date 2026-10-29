// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern volatile f32 lbl_80366B20;
extern volatile f32 lbl_80366B18;
extern u8 lbl_802F2C2C[];
void __ct__9C80261CB0Fv(void *);

void *__ct__9C80264998Fv(u8 *p) {
    __ct__9C80261CB0Fv(p);
    *(void **)p = lbl_802F2C2C;
    *(s32 *)(p + 176) = 2;
    *(s32 *)(p + 180) = 0;
    *(s32 *)(p + 184) = 2;
    *(s32 *)(p + 188) = 0;
    *(s32 *)(p + 192) = 1;
    *(s32 *)(p + 196) = 1;
    *(s32 *)(p + 200) = 0;
    *(f32 *)(p + 204) = lbl_80366B20;
    *(f32 *)(p + 208) = lbl_80366B18;
    *(f32 *)(p + 236) = lbl_80366B18;
    *(s32 *)(p + 220) = 0;
    *(f32 *)(p + 224) = lbl_80366B18;
    *(f32 *)(p + 228) = lbl_80366B18;
    *(f32 *)(p + 212) = lbl_80366B18;
    *(f32 *)(p + 216) = lbl_80366B20;
    *(s32 *)(p + 240) = -1;
    *(s32 *)(p + 244) = 0;
    *(s32 *)(p + 248) = 0;
    *(f32 *)(p + 232) = lbl_80366B18;
    *(s32 *)(p + 256) = 0;
    return p;
}

} /* extern "C" */
