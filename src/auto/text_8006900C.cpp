// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u8 lbl_802BD3A8[];
extern u8 lbl_802BD300[];
extern volatile f32 lbl_8035E758;
void __ct__9C800665E0Fv(void *);

void *__ct__9C8006900CFv(u8 *p) {
    __ct__9C800665E0Fv(p);
    *(void * *)(p + 0) = lbl_802BD3A8;
    *(s32 *)(p + 388) = 0;
    *(f32 *)(p + 364) = lbl_8035E758;
    *(f32 *)(p + 368) = lbl_8035E758;
    *(s32 *)(p + 372) = 0;
    *(s32 *)(p + 376) = 0;
    *(s32 *)(p + 380) = 0;
    *(s32 *)(p + 416) = 0;
    *(f32 *)(p + 420) = lbl_8035E758;
    *(s32 *)(p + 408) = 0;
    *(s32 *)(p + 428) = 0;
    *(void * *)(p + 432) = lbl_802BD300;
    return p;
}

} /* extern "C" */
