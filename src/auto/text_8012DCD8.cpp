/* Functions from 0x8012DCD8 to 0x8012DD1C, found by decomp-toolkit. */
#include "common.h"

extern "C" {

typedef struct {
    u8 r, g, b, a;
} Color_8012DCE8;

extern s32 lbl_80363EE8;

void fn_8012DCD8(u8* arg0) {
    *(s32*)(arg0 + 8) &= 0xFFFFFFFB;
}

/* QV=2.0p1 */
typedef struct { u8 r, g, b, a; } Col8012DCE8;
void fn_8012DCE8(u8 *p, const Col8012DCE8 *c) {
    p[52] = c->r;
    p[53] = c->g;
    p[54] = c->b;
    p[55] = c->a;
    *(s32 *)(p + 8) |= lbl_80363EE8;
}

} /* extern "C" */
