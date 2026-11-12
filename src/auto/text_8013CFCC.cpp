// JPEG marker loop. fn_801F4C84 takes the table precision as a third argument (the temp the original keeps in r5).
// Every "more data?" test is the same inline (one result temp, r30); the DHT case ends in a goto form because
// "if (x) return 1; return 0;" is folded into a branchless x != 0.
#include "common.h"

extern "C" {

struct SB { virtual void v0(); virtual void v1(); virtual void v2(); virtual int v3(); virtual void v4(); };
struct S : SB { u8 *cur; u8 *end; s32 bits; };
struct R { S *s; };
struct QT { u8 b[904]; };
struct HT { u8 b[412]; };
struct D {
    R *r;
    u8 pad4[52];
    s32 err;
    HT ac[4];
    HT dc[4];
    u8 pad1716[1644 - 1640];
    QT qt[4];
    u16 ri;
};
u16 fn_801F359C(S *);
u8 fn_801F36D8(S *);
void fn_801F4C84(QT *, R *, u32);
s32 fn_801F5874(HT *, R *);
void fn_801F5948(D *, s32);
s32 fn_8013CCD0(D *);
s32 fn_8013C63C(D *);

static inline bool more(D *d) {
    return d->r->s->cur < d->r->s->end || d->r->s->v3() == 0;
}

s32 fn_8013CFCC(D *d) {
    while (more(d)) {
        switch (fn_801F36D8(d->r->s)) {
        case 0xD8:
            return 1;
        case 0xDB: {
            u16 len = fn_801F359C(d->r->s) - 2;
            u8 c = fn_801F36D8(d->r->s);
            while (len) {
                u32 id = c & 0xF;
                u32 prec = (c >> 4) & 0xF;
                if (id >= 4) { d->err = 1; return 0; }
                len -= (prec + 1) * 64;
                fn_801F4C84(&d->qt[id], d->r, prec);
                c = fn_801F36D8(d->r->s);
                len--;
            }
            return 1;
        }
        case 0xDE:
            d->err = 1;
            return 0;
        case 0xC0:
        case 0xC1:
        case 0xC2:
            return fn_8013CCD0(d);
        case 0xC3:
        case 0xC5:
        case 0xC6:
        case 0xC7:
            d->err = 1;
            return 0;
        case 0xC9:
        case 0xCA:
        case 0xCB:
        case 0xCD:
        case 0xCE:
        case 0xCF:
            d->err = 1;
            return 0;
        case 0xC4: {
            u16 len = fn_801F359C(d->r->s) - 2;
            u8 c = fn_801F36D8(d->r->s);
            while (len) {
                u32 id = c & 0xF;
                u32 cls = (c >> 4) & 0xF;
                HT *h;
                s32 n;
                if (id > 3) { d->err = 1; return 0; }
                if (cls) h = &d->ac[id]; else h = &d->dc[id];
                n = fn_801F5874(h, d->r);
                len -= n;
                if (n < 0) { d->err = 1; return 0; }
                c = fn_801F36D8(d->r->s);
                len--;
            }
            if (!more(d)) goto z;
            return 1;
            z: return 0;
        }
        case 0xDA:
            return fn_8013C63C(d);
        case 0xDD:
            fn_801F359C(d->r->s);
            d->ri = fn_801F359C(d->r->s);
            return more(d) != 0;
        case 0xD9:
            return 0;
        case 0xE0: case 0xE1: case 0xE2: case 0xE3: case 0xE4: case 0xE5: case 0xE6: case 0xE7:
        case 0xE8: case 0xE9: case 0xEA: case 0xEB: case 0xEC: case 0xED: case 0xEE: case 0xEF:
        case 0xFE:
            {
            u16 len = fn_801F359C(d->r->s);
            fn_801F5948(d, len - 2);
            }
            return more(d) != 0;
        case 0xFF:
            break;
        default:
            d->err = 1;
            return 0;
        }
    }
    d->err = 1;
    return 0;
}

}
