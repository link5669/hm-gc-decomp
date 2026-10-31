// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct R { u8 pad_[292]; virtual void s0(); virtual void s1(); virtual void s2(void *, int, int); virtual void s3(); virtual void v4(int); virtual u32 v5(); };
struct B { u8 pad[44]; u32 f44; u8 pad2[132]; u8 f180[24]; u8 f204[4]; };
struct A { u8 pad[24]; u32 f24; u32 f28; u32 *a32; u32 f36; u32 f40; u32 *f44; };
struct T {
    u8 c0, c1, c2, c3;
    u8 f4[4];
    u8 f8, f9, f10, f11;
    u8 f12[4];
    f32 f16;
    void *f20;
    u32 *f24;
    u32 *f28;
    u32 g32;
    u32 f36;
    f32 f40;
    u32 f44;
    u8 f48, f49, f50, f51;
    u8 f52, f53, f54, f55;
    u8 f56, f57, f58, f59;
    f32 f60;
    A *f64;
    virtual void v0(B *); virtual void v1(); virtual void v2();
};
extern u32 lbl_80363F80, lbl_80363F88, lbl_80363F8C, lbl_80363F90, lbl_80363F94, lbl_80363F98, lbl_80363F9C, lbl_80363FA0;
extern u32 lbl_80363FA4, lbl_80363FA8, lbl_80363FAC, lbl_80363FB0, lbl_80363FB4, lbl_80363FB8, lbl_80363FBC, lbl_80363FC0;
extern u32 lbl_80363FC4, lbl_80363FC8, lbl_80363FCC, lbl_80363FD0, lbl_80363FD4, lbl_80363FD8;
u32 fn_800FB33C(R *);
f32 fn_800FB2E0(R *);
void fn_800FAEF8(R *);
void fn_800FB064(R *, void *);
void fn_80121670(void *, R *);
void *fn_800F9398(void *, void *);
void *fn_800F9788(void *, char *, void *);
static inline void *look(B *b, char *nm, void *id) {
    if (nm == 0 || *nm == 0) return fn_800F9398(b->f180, id);
    return fn_800F9788(b->f204, nm, id);
}
static inline u8 mA(R *r) {
    u8 v;
    switch (r->v5()) {
    case 107: v = 0; break;
    case 108: v = 5; break;
    case 109: v = 3; break;
    case 110: v = 4; break;
    case 111: v = 1; break;
    case 112: v = 2; break;
    case 113: v = 7; break;
    case 114: v = 6; break;
    default: r->v4(30); v = 0; break;
    }
    return v;
}
static inline u8 mB(R *r) {
    u8 v;
    switch (r->v5()) {
    case 115: v = 0; break;
    case 116: v = 1; break;
    case 117: v = 2; break;
    case 118: v = 3; break;
    case 119: v = 4; break;
    case 120: v = 5; break;
    case 121: v = 6; break;
    case 122: v = 7; break;
    default: r->v4(30); v = 0; break;
    }
    return v;
}
static inline u8 mC(R *r) {
    u8 v;
    switch (r->v5()) {
    case 97: v = 1; break;
    case 98: v = 2; break;
    case 99: v = 3; break;
    case 100: v = 4; break;
    case 101: v = 5; break;
    case 102: v = 6; break;
    case 103: v = 7; break;
    case 104: v = 8; break;
    case 105: v = 9; break;
    case 106: v = 10; break;
    default: r->v4(30); v = 0; break;
    }
    return v;
}
void fn_801300B8(T *t, B *b, A *a, R *r, char *name) {
    u32 n;
    u32 tok;
    u8 id[8];
    char nm[8];
    if (t->f44 & 1) t->v2();
    t->f64 = a;
    fn_800FAEF8(r);
    while ((tok = r->v5()) != 6) {
        switch (tok) {
        case 64:
            t->c0 = fn_800FB33C(r);
            t->c1 = fn_800FB33C(r);
            t->c2 = fn_800FB33C(r);
            t->c3 = fn_800FB33C(r);
            t->c0 = 255;
            t->c1 = 255;
            t->c2 = 255;
            t->c3 = 255;
            break;
        case 65: fn_80121670(t->f4, r); break;
        case 66: fn_80121670(t->f12, r); break;
        case 67:
            t->f8 = fn_800FB33C(r);
            t->f9 = fn_800FB33C(r);
            t->f10 = fn_800FB33C(r);
            t->f44 |= lbl_80363F8C;
            break;
        case 68: t->f44 |= lbl_80363F90; break;
        case 69: t->f44 &= ~4; break;
        case 70: t->f44 |= lbl_80363F94; break;
        case 71: t->f44 &= ~8; break;
        case 72: t->f44 |= lbl_80363F98; break;
        case 73: t->f44 &= ~2; break;
        case 74:
            t->f54 = mA(r);
            if (t->f54 != 0 && t->f54 != 7) t->f55 = fn_800FB33C(r);
            t->f44 |= lbl_80363F80;
            break;
        case 96:
            t->f49 = mA(r);
            t->f44 |= lbl_80363F9C;
            break;
        case 75:
            t->f53 = mC(r);
            t->f44 |= lbl_80363FA0;
            break;
        case 76: t->f44 &= ~0x20; break;
        case 77:
            t->f11 = fn_800FB33C(r);
            t->f44 |= lbl_80363FA4;
            break;
        case 78:
            t->f20 = 0;
            n = fn_800FB33C(r);
            if (n + 1 > a->f36) r->v4(35);
            t->f48 = 1;
            t->f28 = a->f44 + n;
            break;
        case 79: {
            fn_800FB064(r, id);
            t->f20 = look(b, name, id);
            if (t->f20 == 0) r->v4(37);
            n = fn_800FB33C(r);
            t->f52 = fn_800FB33C(r);
            if (n + t->f52 > a->f24) r->v4(35);
            if (t->f52) t->f24 = a->a32 + n;
            n = fn_800FB33C(r);
            t->f48 = fn_800FB33C(r);
            if (n + t->f48 > a->f36) r->v4(35);
            if (t->f48) t->f28 = a->f44 + n;
            break;
        }
        case 80: {
            fn_800FB064(r, id);
            fn_800FB064(r, nm);
            t->f20 = look(b, nm, id);
            if (t->f20 == 0) r->v4(37);
            n = fn_800FB33C(r);
            t->f52 = fn_800FB33C(r);
            if (n + t->f52 > a->f24) r->v4(35);
            if (t->f52) t->f24 = a->a32 + n;
            n = fn_800FB33C(r);
            t->f48 = fn_800FB33C(r);
            if (n + t->f48 > a->f36) r->v4(35);
            if (t->f48) t->f28 = a->f44 + n;
            break;
        }
        case 83: t->g32 = fn_800FB33C(r); break;
        case 81: t->f44 |= lbl_80363FA8; break;
        case 82:
            t->f44 |= lbl_80363FAC;
            t->f40 = fn_800FB2E0(r);
            break;
        case 84:
            t->f56 = mB(r);
            t->f57 = mB(r);
            t->f58 = mA(r);
            t->f59 = fn_800FB33C(r);
            t->f44 |= lbl_80363FB0;
            break;
        case 85: t->f44 |= lbl_80363FB4; break;
        case 86: t->f44 |= lbl_80363FB8; t->f44 &= ~0x2000; break;
        case 87: t->f44 |= lbl_80363FBC; t->f44 &= ~0x1000; break;
        case 88: t->f44 |= lbl_80363FC0; break;
        case 89:
            t->f16 = fn_800FB2E0(r);
            t->f44 |= lbl_80363FC4;
            break;
        case 90: t->f44 |= lbl_80363FC8; break;
        case 91: t->f60 = fn_800FB2E0(r); break;
        case 92: t->f44 |= lbl_80363FCC; break;
        case 95: t->f44 |= lbl_80363FD0; break;
        case 93: t->f44 |= lbl_80363FD4; break;
        case 94: t->f44 |= lbl_80363FD8; break;
        default: r->v4(30); break;
        }
    }
    if (b->f44 & 0x80) {
        t->f20 = 0;
        t->f48 = 0;
        t->f52 = 0;
        t->f28 = 0;
        t->f24 = 0;
    }
    if (!(t->f44 & 0x20000) && (t->f44 & 0x80) && ((int)t->f53 == 1 || (int)t->f53 == 9)) t->f44 |= lbl_80363FCC;
    t->v0(b);
    t->f44 |= lbl_80363F88;
}

} /* extern "C" */
