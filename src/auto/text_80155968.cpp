// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct E80155968B {
    u8 pad[32];
    virtual void v0();
    virtual void v1();
    virtual void *v2();
};
struct E80155968 : E80155968B {
    u8 pad2[44];
};
struct S80155968 {
    u8 pad0[8];
    u32 f8;
    u16 f12;
    u8 b14;
    u8 b15;
    u8 b16;
    u8 pad17[39];
    u32 f56;
    E80155968 *f60;
};
extern "C" {

void fn_80148310(void *buf);
E80155968 *fn_80171438(u32 a, u8 n);
void fn_801482DC(void *buf, u32 a);
void fn_8015569C(S80155968 *p, u32 a, u32 *w, u32 *h, void *buf, u8 b, u32 *offs);
void fn_801551F8(E80155968 *q, u32 off, u32 w, u32 h, void *buf, u32 f8, E80155968 *prev);
extern u16 lbl_80364590;

void fn_80155968(S80155968 *p, u32 a1, u32 a2, u32 w, u32 h, u32 a5) {
    u8 buf[20];
    u32 offs[11];
    s32 i;
    E80155968 *q;
    u32 *o;
    E80155968 *prev;
    fn_80148310(buf);
    p->f60 = fn_80171438(a2, p->b15);
    fn_801482DC(buf, a5);
    fn_8015569C(p, a1, &w, &h, buf, p->b16, offs);
    o = offs;
    prev = 0;
    w >>= p->b15 - 1;
    h >>= p->b15 - 1;
    q = p->f60 + p->b15 - 1;
    i = p->b15 - 1;
    o += i;
    for (; i >= 0; q--, o--, i--) {
        fn_801551F8(q, p->f56 + *o, w, h, buf, p->f8, prev);
        prev = q;
        w <<= 1;
        h <<= 1;
    }
    if (p->f60->v2()) p->f12 |= lbl_80364590;
    else p->f12 &= ~0x20;
}

} /* extern "C" */
