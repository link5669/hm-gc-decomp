// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern volatile f32 lbl_80328870[8];
extern volatile f32 lbl_80363A68;
extern volatile f32 lbl_80363A74;
void fn_800E1E88(void *, void *);
void __dt__9C80118D20Fv(void *, s32);
void *memset(void *, s32, u32);
s32 fn_8011F36C(void *);

s32 fn_80117358(u8 *self) {
    f32 v;
    f32 st;
    if (*(s32 *)(self + 188) == 0) {
        return 0;
    }
    if (*(void **)(self + 212) != 0) {
        fn_800E1E88(*(void **)(self + 212), (void *)__dt__9C80118D20Fv);
    }
    v = lbl_80363A68;
    *(s32 *)(self + 0x10) = 5;
    lbl_80328870[0] = lbl_80363A68;
    st = lbl_80363A74;
    v += st;
    lbl_80328870[1] = v;
    v += st;
    lbl_80328870[2] = v;
    v += st;
    lbl_80328870[3] = v;
    v += st;
    lbl_80328870[4] = v;
    v += st;
    lbl_80328870[5] = v;
    v += st;
    lbl_80328870[6] = v;
    v += st;
    lbl_80328870[7] = v;
    memset(self + 256, 0, 16);
    memset(self + 272, 0, 16);
    *(s32 *)(self + 212) = 0;
    return fn_8011F36C(self);
}

} /* extern "C" */
