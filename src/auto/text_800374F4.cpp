// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u8 lbl_802AFB98[];
extern u8 lbl_802AFAF0[];
extern volatile f32 lbl_8035BE98;
void __ct__9C800665E0Fv(void *);

void *__ct__9C800374F4Fv(u8 *p) {
    __ct__9C800665E0Fv(p);
    *(void * *)(p + 0) = lbl_802AFB98;
    *(f32 *)(p + 364) = lbl_8035BE98;
    *(f32 *)(p + 368) = lbl_8035BE98;
    *(f32 *)(p + 372) = lbl_8035BE98;
    *(f32 *)(p + 376) = lbl_8035BE98;
    *(f32 *)(p + 380) = lbl_8035BE98;
    *(s32 *)(p + 384) = -1;
    *(s32 *)(p + 392) = 0;
    *(void * *)(p + 396) = lbl_802AFAF0;
    return p;
}

} /* extern "C" */
