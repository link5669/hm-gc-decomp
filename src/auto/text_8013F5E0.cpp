// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct B { u8 pad[8]; u32 a8; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void s6(); };
struct S8 {
    u32 a0;
    u8 pad4[4];
    u32 a8;
    u8 pad12[8];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual B *s13(u32);
};
struct P {
    u8 pad0[8];
    S8 *s8;
    s32 a12;
    u8 pad16[112];
    u32 fl128;
    u32 a132;
    B *b136;
    u32 a140;
    u32 a144;
    u32 a148;
    u32 a152;
    u32 v156[4];
    u32 a172;
    u32 a176;
};
extern u32 lbl_80364354;

s32 fn_8013F5E0(P *p, u32 a, u32 n, u32 *v) {
    B *b = p->b136;
    u32 i;
    if (!b || p->a140 + 3 > b->a8) {
        if (p->fl128 & 4) {
            b->s6();
            p->fl128 &= ~4;
        }
        if (p->a132 >= p->s8->a0) return 0;
        p->b136 = p->s8->s13(p->a132++);
        p->a140 = 0;
    } else if (p->a12 == 0 && p->a148 == a && p->a152 == n) {
        for (i = 0; i < n; i++) {
            if (p->v156[i] != v[i]) break;
        }
        if (i >= n) {
            p->fl128 |= lbl_80364354;
            return 1;
        }
    }
    p->a148 = a;
    p->a152 = n;
    for (i = 0; i < n; i++) p->v156[i] = v[i];
    if (p->a144 >= p->s8->a8) return 0;
    p->a144++;
    p->a172 = p->a140;
    p->a176 = 0;
    p->fl128 |= lbl_80364354;
    return 1;
}

} /* extern "C" */
