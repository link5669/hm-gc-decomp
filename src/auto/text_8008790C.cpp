// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u8 lbl_802C5740[];
extern volatile f32 lbl_8035FE7C;
void __ct__9C8005F938Fv(void *);

void *__ct__9C8008790CFv(u8 *p) {
    __ct__9C8005F938Fv(p);
    *(void * *)(p + 0) = lbl_802C5740;
    *(s32 *)(p + 888) = 0;
    *(f32 *)(p + 892) = lbl_8035FE7C;
    *(f32 *)(p + 896) = lbl_8035FE7C;
    *(f32 *)(p + 900) = lbl_8035FE7C;
    *(f32 *)(p + 904) = lbl_8035FE7C;
    *(s32 *)(p + 608) = 16;
    *(s32 *)(p + 908) = 255;
    *(s32 *)(p + 912) = 0;
    return p;
}

} /* extern "C" */
