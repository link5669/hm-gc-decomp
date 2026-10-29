// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void __dla__FPv(void *);
void fn_800FBF44(void *);
struct S15C { s32 f0; u16 flags; u16 f6; u8 pad[24-8]; union { u8 *a; u16 *b; u32 *c; } u; };

void fn_8015C40C(S15C *p) {
    if (p->flags & 0x10) {
        if (p->u.a) __dla__FPv(p->u.a);
    } else if (p->flags & 0x20) {
        if (p->u.b) __dla__FPv(p->u.b);
    } else {
        if (p->u.c) __dla__FPv(p->u.c);
    }
    fn_800FBF44(p);
    p->u.a = 0;
    p->u.b = 0;
    p->u.c = 0;
}

} /* extern "C" */
