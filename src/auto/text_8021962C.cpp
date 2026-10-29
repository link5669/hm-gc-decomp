// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct E8021962C { s32 f0; char *str; s32 f8; f32 x; f32 y; };
struct L8021962C { u32 f0; E8021962C *arr; u32 count; };
extern char lbl_80356DC8[];
void fn_802194B8(void *, s32);
void fn_80219DE8(void *, const char *, ...);
void fn_8021962C(L8021962C *p) {
    u32 i;
    for (i = 0; i < p->count; i++) {
        *(s32 *)(lbl_80356DC8 + 0x14) = (s32)p->arr[i].x;
        fn_802194B8(lbl_80356DC8, (s32)p->arr[i].y);
        fn_80219DE8(lbl_80356DC8, p->arr[i].str, p->arr[i].f8, p->arr[i].f0);
    }
    p->count = 0;
}

} /* extern "C" */
