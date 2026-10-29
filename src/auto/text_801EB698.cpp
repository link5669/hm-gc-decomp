// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_801089F0(int, void *);
struct C800322B0 { u32 a; s32 b; u32 c; C800322B0() { a = 0; c = 0; b = 0; } ~C800322B0() {} };
struct T { u32 f0; u32 flags; u32 *arr; u32 count; };

void fn_801EB698(T *p) {
    C800322B0 h;
    u32 i;
    if (p->flags & 1) {
        h.b = -1;
        for (i = 0; i < p->count; i++) {
            h.a = p->arr[i];
            fn_801089F0((int)h.a, &h);
        }
    }
}

} /* extern "C" */
