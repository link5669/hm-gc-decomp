// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u32 lbl_80365828;
} /* extern "C" */
struct V8020E7D0 { u8 pad[0x60]; virtual void p0(); virtual void p1(); virtual void m(); };
struct EB8020E7D0 {
    u8 pad0[8];
    u32 f8;
    u8 pad12[96 - 12];
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct E8020E7D0 : EB8020E7D0 {
    u8 rest[43332 - 100];
};
struct S8020E7D0 {
    u32 f0;
    E8020E7D0 e[2];
    s32 f86668;
};
extern "C" {
void fn_8020BB10(void *, void *, void *, s32, u32);
s32 fn_800D0B94(u32, s32 *, s32 *);

#pragma opt_propagation off
void fn_8020E7D0(S8020E7D0 *s0, void *a, void *b) {
    s32 r;
    S8020E7D0 *s;
    u32 i;
    u32 k;
    u8 *q;
    u8 *t;
    u8 *p;
    u32 j;
    s = s0;
    if (s->f86668 != 0) {
    for (k = 0, t = (u8 *)s; k < 2; k++, t += 43332) {
        ((E8020E7D0 *)(t + 4))->v2();
    }
        s->f86668 = 0;
    }
    for (i = 0, p = (u8 *)s; i < 2; i++, p += 43332) {
        fn_8020BB10(p + 4, a, b, 0, i);
    }
    for (j = 0, q = (u8 *)s; j < 2; j++, q += 43332) {
        do {
            r = fn_800D0B94(j, 0, 0);
        } while (r == -1);
        if (r == 0 || r == -2) *(u32 *)(q + 12) |= lbl_80365828;
        else *(u32 *)(q + 12) &= ~0x20;
    }
    s->f86668 = 1;
}
#pragma opt_propagation reset

} /* extern "C" */
