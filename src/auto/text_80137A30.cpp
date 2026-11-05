/* Functions from 0x80137A30 to 0x80137A9C, found by decomp-toolkit. */
#include "common.h"

extern "C" {

typedef struct { u8 r, g, b, a; } GXColor;

static inline void CopyColor(GXColor *__restrict d, const GXColor *__restrict s) {
    d->r = s->r;
    d->g = s->g;
    d->b = s->b;
    d->a = s->a;
}

extern u16 lbl_80364188;

void fn_80137A30(u8 *arg0) {
    *(s32 *)(arg0 + 0x8) &= ~0x61;
}

s32 fn_80137A44(void) {
    return 0;
}

void fn_80137A4C(u8 *arg0) {
    *(u16 *)(arg0 + 0xC) &= ~0x8;
}

/* QV=2.0p1 */

void fn_80137A5C(u8 *p, const u8 *c) {
    p[0] = c[0];
    p[1] = c[1];
    p[2] = c[2];
    p[3] = c[3];
    *(u16 *)(p + 12) |= lbl_80364188;
}


int fn_80137A90(int a) { return a; }

s32 fn_80137A94(void) {
    return 0;
}

} /* extern "C" */
