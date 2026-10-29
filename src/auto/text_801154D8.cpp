// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Obj801154D8 {
    u8 pad0[2080];
    char *arr[2000];
    s32 f10080;
    s32 f10084;
    s32 f10088;
    s32 f10092;
    s32 f10096;
    void *f10100;
    s32 f10104;
    u8 sub[20];
};
extern "C" {
void fn_80115090(void *a, void *b);
void fn_800F8410(void *t, const char *s);
void fn_801154D8(Obj801154D8 *p) {
    u32 i;
    for (i = 0; i < 2000; i++) {
        if (p->arr[i] != 0) {
            fn_800F8410(p->sub, p->arr[i] + 100);
            fn_80115090(p->f10100, p->arr[i]);
            p->arr[i] = 0;
            p->f10088--;
        }
    }
}

} /* extern "C" */
