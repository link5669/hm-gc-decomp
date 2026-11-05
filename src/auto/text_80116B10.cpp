/* Functions from 0x80116B10 to 0x80116B64, found by decomp-toolkit. */
#include "common.h"

extern "C" {


/* QV=2.0p1 */
struct H80116B10 { u8 pad[16]; s32 f16; };
struct S80116B10 { H80116B10 *f0; u8 pad4[16]; s32 f20; s32 f24; s32 f28; };
s32 fn_80116B10(S80116B10 *p, s32 i, u8 **out) {
    H80116B10 *h = p->f0;
    if ((i >= p->f20 && i < p->f24) || i >= p->f28) return 5;
    *out = (u8 *)(h->f16 + i + (s32)h);
    return 0;
}
s32 fn_80116B58(u8* arg0, s32 arg1) {
    *(s32*)(arg0 + 0x5C) = arg1;
    return 0;
}

} /* extern "C" */
