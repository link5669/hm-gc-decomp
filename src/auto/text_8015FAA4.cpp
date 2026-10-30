// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct T12 { u32 v[3]; };
struct Q { u8 pad[20]; u32 a20; };
struct R16 { u8 pad[24]; u16 *a24; };
struct P {
    Q *q;
    u8 pad4[12];
    R16 *r16;
    u32 a20;
    u32 a24;
    u32 a28;
    u8 pad32[2];
    u16 a34;
    u16 fl36;
    u8 pad38[4];
    u16 a42;
    u8 pad44[16];
    u8 s60[16];
    u16 a76;
    u8 pad78[2];
    char *s80;
    u8 pad84[4];
    T12 pmf;
};
static T12 sTbl[6] = {1};
extern char lbl_802A04DC[], lbl_802A04E8[];
void fn_80217D7C(u8 *, void *, Q *, int, u16, u32);
void fn_80217954(u8 *, void *, Q *, int, u16 *, u16, u32);

void fn_8015FAA4(P *p, void *x) {
    T12 *t = sTbl;
    u16 fl = p->fl36;
    Q *q;
    if (fl & 0x80) {
        p->pmf = t[0];
        return;
    }
    if (fl & 0x100) {
        if (fl & 4) p->s80 = lbl_802A04DC;
        else p->s80 = lbl_802A04E8;
        if (p->a42 < 2) p->pmf = t[1];
        else p->pmf = t[2];
        return;
    }
    q = p->q;
    if (fl & 4) {
        fn_80217D7C(p->s60, x, q, 144, p->a34, p->a20);
        p->a76 = p->a20;
    } else if (fl & 8) {
        fn_80217D7C(p->s60, x, q, 152, p->a34, p->a20);
        p->a76 = p->a20;
    } else if (fl & 0x10) {
        fn_80217954(p->s60, x, q, 144, p->r16->a24 + p->a24, p->a28, p->a20);
        p->a76 = p->a20;
        p->r16 = 0;
    } else if (fl & 0x40) {
        fn_80217954(p->s60, x, q, 144, p->r16->a24 + p->a24, p->a28, 0);
        p->a76 = 0;
        p->r16 = 0;
    } else if (fl & 0x20) {
        fn_80217954(p->s60, x, q, 152, p->r16->a24 + p->a24, p->a28, p->a20);
        p->a76 = p->a20;
        p->r16 = 0;
    }
    if (q->a20 == 0) p->pmf = t[3];
    else if (q->a20 == 1) p->pmf = t[4];
    else p->pmf = t[5];
}

} /* extern "C" */
