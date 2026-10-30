// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct P { u8 pad[16]; virtual void p0(); virtual void clear(); };
struct T { u32 f0; void *f4; u8 pad[8]; s32 f16; u32 pad20; u32 fl[12]; void *arr[12]; P pool[12]; };
extern "C" {
void fn_801A68D0(void *, T *);
void fn_801A69EC(void *);
void __dl__FPv(void *);
void fn_800E1E88(void *, void *);
void fn_801A6380(T *);
void __dt__9C801A460CFv(void *, s16);
void __dt__9C801A4C14Fv(void *, s16);
void __dt__9C801A4F00Fv(void *, s16);
void __dt__9C801AE6F4Fv(void *, s16);
void __dt__9C801B307CFv(void *, s16);
void __dt__9C801B369CFv(void *, s16);
void __dt__9C801B3E18Fv(void *, s16);
void __dt__9C801BD4C8Fv(void *, s16);
void __dt__9C801BD818Fv(void *, s16);
void __dt__9C801C6614Fv(void *, s16);
void __dt__9C801CCA28Fv(void *, s16);
void __dt__9C801DE4E0Fv(void *, s16);

void fn_801A6400(T *t) {
    if (t->f4) fn_801A68D0(t->f4, t);
    if (t->f4 && t->f16) {
        fn_801A69EC(t->f4);
        __dl__FPv(t->f4);
        t->f4 = 0;
    }
    if (t->fl[0]) { t->pool[0].clear(); fn_800E1E88(t->arr[0], (void *)__dt__9C801BD4C8Fv); }
    if (t->fl[1]) { t->pool[1].clear(); fn_800E1E88(t->arr[1], (void *)__dt__9C801B369CFv); }
    if (t->fl[2]) { t->pool[2].clear(); fn_800E1E88(t->arr[2], (void *)__dt__9C801CCA28Fv); }
    if (t->fl[3]) { t->pool[3].clear(); fn_800E1E88(t->arr[3], (void *)__dt__9C801AE6F4Fv); }
    if (t->fl[4]) { t->pool[4].clear(); fn_800E1E88(t->arr[4], (void *)__dt__9C801A4F00Fv); }
    if (t->fl[5]) { t->pool[5].clear(); fn_800E1E88(t->arr[5], (void *)__dt__9C801A4C14Fv); }
    if (t->fl[6]) { t->pool[6].clear(); fn_800E1E88(t->arr[6], (void *)__dt__9C801B3E18Fv); }
    if (t->fl[7]) { t->pool[7].clear(); fn_800E1E88(t->arr[7], (void *)__dt__9C801B307CFv); }
    if (t->fl[8]) { t->pool[8].clear(); fn_800E1E88(t->arr[8], (void *)__dt__9C801DE4E0Fv); }
    if (t->fl[9]) { t->pool[9].clear(); fn_800E1E88(t->arr[9], (void *)__dt__9C801A460CFv); }
    if (t->fl[11]) { t->pool[11].clear(); fn_800E1E88(t->arr[11], (void *)__dt__9C801C6614Fv); }
    if (t->fl[10]) { t->pool[10].clear(); fn_800E1E88(t->arr[10], (void *)__dt__9C801BD818Fv); }
    fn_801A6380(t);
}

} /* extern "C" */
