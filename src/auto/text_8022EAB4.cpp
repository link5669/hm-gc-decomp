/* Functions from 0x8022EAB4 to 0x8022EB48, found by decomp-toolkit. */
#include "common.h"

extern "C" {

typedef struct {
    u32 flags;
    u8 pad4[0x94];
    union {
        u32 flags98;
        struct {
            u32 unk98_pad : 28;
            u32 unk98_b3 : 1;
            u32 unk98_b2 : 1;
            u32 unk98_b1 : 1;
            u32 unk98_b0 : 1;
        };
    };
    u8 pad9C[0x48];
} UnkElem8022EAB4;

typedef struct {
    u8 pad0[4];
    u32 *counts;
    u8 pad8[4];
    u32 num;
    UnkElem8022EAB4 **elems;
} UnkObj8022EAB4;

/* QV=2.0p1 */
} /* extern "C" */
struct E8022EAB4 { u32 f0; u8 pad[148]; volatile u32 f152; u8 pad2[72]; };
struct P8022EAB4 { u8 pad0[4]; u32 *f4; u8 pad8[4]; u32 f12; E8022EAB4 **f16; };
extern "C" {
void fn_8022EAB4(P8022EAB4 *p) {
    u32 i, j;
    for (i = 0; i < p->f12; i++) {
        for (j = 0; j < p->f4[i]; j++) {
            p->f16[i][j].f152 &= ~1;
            p->f16[i][j].f0 &= ~0x800;
            if (p->f16[i][j].f152 & 8) p->f16[i][j].f152 &= ~8;
        }
    }
}

} /* extern "C" */
