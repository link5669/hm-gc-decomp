// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
}
struct C8018F358 { C8018F358(); ~C8018F358(); s32 a, b; };
extern "C" {
struct S8018F424 { u32 count; u32 f4; C8018F358 *arr; };
extern void *lbl_8035AE58;
extern void *lbl_8035A9F4;
void fn_800E1E88(void *, void *);
void __dt__9C8018F358Fv(void);
void fn_800604C4(int, int, int, int);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_8018F124(C8018F358 *, u32, s32);
void fn_8018EEF8(C8018F358 *);

static inline void clear(S8018F424 *p) {
    if (p->arr) fn_800E1E88(p->arr, (void *)__dt__9C8018F358Fv);
    p->count = 0;
    p->f4 = 0;
    p->arr = 0;
}

void fn_8018F424(S8018F424 *p, u32 n, u32 c, s32 mode) {
    u32 i;
    if (p->arr) clear(p);
    p->count = n;
    if (mode == 0) {
        if (lbl_8035AE58 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035AE58);
        p->arr = new C8018F358[p->count];
        fn_800F7E98();
        if (p->arr == 0) fn_800604C4(-4, 0, 0, 0);
    } else {
        if (lbl_8035A9F4 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035A9F4);
        p->arr = new C8018F358[p->count];
        fn_800F7E98();
        if (p->arr == 0) fn_800604C4(-4, 0, 0, 0);
    }
    for (i = 0; i < n; i++) fn_8018F124(&p->arr[i], c, mode);
    p->f4 = 1;
    fn_8018EEF8(&p->arr[i]);
}

} /* extern "C" */
