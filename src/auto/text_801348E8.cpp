/* Functions from 0x801348E8 to 0x8013494C, found by decomp-toolkit. */
#include "common.h"

extern "C" {

extern s32 lbl_8035AC38;
s32 fn_801348E8(void) {
    return lbl_8035AC38;
}

extern u8 lbl_8032C2D0[];
u8 *fn_801348F0(void) {
    return lbl_8032C2D0;
}

s32 fn_801348FC(void) {
    return 0;
}

int fn_80134904(int a) { return a; }

extern u16 lbl_803640E0;
void fn_80134908(void* arg0) {
    *(u16*)((u8*)arg0 + 0x1A) &= ~2;
}

/* QV=2.0p1 */
typedef struct { u8 r, g, b, a; } Col4;
typedef struct { u8 pad[20]; Col4 c; u16 f24; u16 f26; } S134;
void fn_80134918(S134 *p, const Col4 *c) {
    p->c = *c;
    p->f26 |= lbl_803640E0;
}

} /* extern "C" */
