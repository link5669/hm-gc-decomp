// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u8 lbl_802BCC00[];
extern f32 lbl_8035E438;
void __ct__9C80233124Fv(void *);

void *__ct__9C8005D3E0Fv(u8 *p) {
    __ct__9C80233124Fv(p);
    *(void * *)(p + 0) = lbl_802BCC00;
    *(s32 *)(p + 772) = 0;
    *(s32 *)(p + 776) = 0;
    *(f32 *)(p + 780) = lbl_8035E438;
    *(s32 *)(p + 768) = 0;
    *(s32 *)(p + 728) = 0;
    *(s32 *)(p + 732) = 0;
    *(s32 *)(p + 736) = 0;
    *(s32 *)(p + 740) = 0;
    *(s32 *)(p + 744) = 0;
    *(s32 *)(p + 748) = 0;
    *(s32 *)(p + 752) = 0;
    *(s32 *)(p + 756) = 0;
    *(s32 *)(p + 760) = 0;
    *(s32 *)(p + 764) = 0;
    *(s32 *)(p + 820) = 0;
    *(s32 *)(p + 824) = 0;
    *(s32 *)(p + 828) = 0;
    *(s32 *)(p + 832) = 0;
    *(s32 *)(p + 816) = 0;
    return p;
}

} /* extern "C" */
