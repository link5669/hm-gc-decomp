// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u8 lbl_802C57F0[];
extern volatile f32 lbl_8035FEB8;
void __ct__9C8005F938Fv(void *);

void *__ct__9C800899FCFv(u8 *p) {
    __ct__9C8005F938Fv(p);
    *(void * *)(p + 0) = lbl_802C57F0;
    *(s32 *)(p + 896) = 0;
    *(f32 *)(p + 900) = lbl_8035FEB8;
    *(s32 *)(p + 908) = 0;
    *(s32 *)(p + 888) = 0;
    *(f32 *)(p + 912) = lbl_8035FEB8;
    *(f32 *)(p + 916) = lbl_8035FEB8;
    *(f32 *)(p + 920) = lbl_8035FEB8;
    *(s32 *)(p + 1000) = 0;
    *(s32 *)(p + 1024) = 0;
    *(s32 *)(p + 1004) = 0;
    *(s32 *)(p + 1028) = 0;
    *(s32 *)(p + 1008) = 0;
    *(s32 *)(p + 1032) = 0;
    *(s32 *)(p + 1012) = 0;
    *(s32 *)(p + 1036) = 0;
    *(s32 *)(p + 1016) = 0;
    *(s32 *)(p + 1040) = 0;
    *(s32 *)(p + 1020) = 0;
    *(s32 *)(p + 1044) = 0;
    *(s32 *)(p + 608) = 32;
    *(s32 *)(p + 948) = 0;
    return p;
}

} /* extern "C" */
