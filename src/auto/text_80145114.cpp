// NonMatching draft (wMU: GC/2.6 + __restrict r fixes prologue, SDIFF 18->8; left: entry mullw/srawi schedule)
#include "common.h"

extern "C" {
void *memset(void *, int, u32);
void fn_800604C4(int, int, int, int);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
}
struct Heap { u8 pad[0x18]; u32 f18; u32 f1c; };
extern "C" Heap *lbl_8035AC98;
extern "C" const u32 lbl_80364394;
struct C80121E80 {
    u8 b[4];
    C80121E80();
};
struct Rc { s32 x0, y0, x1, y1; };
struct C80145114;
typedef void (C80145114::*PM)();
struct C80145114 {
    u32 f0;
    u8 pad4[0x16 - 4];
    u16 f16;
    u8 pad18[0x28 - 0x18];
    u16 f28;
    u16 f2a;
    u8 pad2c[0x8c - 0x2c];
    u32 f8c;
    s32 f90;
    u32 f94;
    s32 f98;
    u32 f9c;
    u32 fa0;
    u8 pada4[0xb0 - 0xa4];
    u8 *fb0;
    u8 *fb4;
    u8 bb8[0x80];
    u8 b138[0x20];
    u8 b158[0x20];
    C80121E80 *f178;
    u8 pad17c[0x184 - 0x17c];
    u8 *f184;
    u8 *f188;
    u8 *f18c;
    u8 *f190;
    u8 pad194[0x59c - 0x194];
    u32 n59c;
    PM pm5a0[0x18];
    u8 *f6c0;
    u8 *f6c4;
    u8 pad6c8[0x6dc - 0x6c8];
    PM pm6dc;
    PM pm6e8;
    PM pm6f4;
    PM pm700;
    void runall() { u32 i; u8 *q; for (i = 0, q = (u8 *)this; i < this->n59c; q += 12, i++) (this->*(((C80145114 *)q)->pm5a0[0]))(); }
};
extern "C" {
void fn_80146610(C80145114 *);

void fn_80145114(C80145114 *t, u8 *dst, s32 dpitch, s32 dx, s32 dy, u8 *src, s32 spitch, Rc *__restrict r) {
    u8 *e;
    s32 step;
    u8 *sv;
    u8 *nx;
    s32 y0, y1, x1, x0;
    if ((y1 = r->y1) <= (y0 = r->y0) || (x1 = r->x1) <= (x0 = r->x0)) return;
    if (!(t->f28 & 1)) return;
    t->f8c = x1 - x0;
    dst = dst + (dy * dpitch + ((u32)(dx * t->f2a) >> 3));
    src = src + ((u32)(x0 * t->f16) >> 3);
    e = dst + dpitch * ((y1 - y0) >> 1);
    if (t->f0 & 0x40) {
        step = -spitch;
        src = src + (y1 - 1) * spitch;
    } else {
        step = spitch;
        src = src + y0 * spitch;
    }
    t->f0 |= lbl_80364394;
    t->fb0 = src;
    t->fb4 = dst;
    t->f94 = t->f8c;
    t->f90 = r->x0;
    t->f98 = dx;
    fn_80146610(t);
    if (!(t->f0 & 6)) memset(t->b158, 0xff, 0x20);
    {
        Heap *h = lbl_8035AC98;
        if (h->f18 >= 2) h->f1c = h->f18; else h->f1c = 2;
        if (!lbl_8035AC98) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035AC98);
        t->f178 = new C80121E80[0x20];
        fn_800F7E98();
        if (!t->f178) fn_800604C4(-4, 0, 0, 0);
        h = lbl_8035AC98;
        h->f1c = h->f18;
    }
    t->f188 = t->bb8;
    t->f18c = t->b138;
    t->f190 = t->b158;
    do {
        t->fb0 = src;
        t->fb4 = dst;
        t->fa0 = t->f8c;
        while (t->fa0 >= 0x20) {
            t->f9c = 0x20;
            nx = t->fb0 + step;
            t->f184 = t->bb8;
            (t->*(t->pm6dc))();
            t->runall();
            sv = t->fb0;
            t->fb0 = nx;
            t->f184 = (u8 *)t->f178;
            (t->*(t->pm6dc))();
            t->runall();
            {
                u32 n = t->f9c;
                u8 *o = t->bb8, *p = o, *pe;
                u8 *b;
                if (n & 1) pe = p + n * 4 - 4; else pe = p + n * 4;
                b = (u8 *)t->f178;
                for (; p < pe; p += 8, b += 8, o += 4) {
                    o[0] = (u32)(p[0] + b[0] + p[4] + b[4]) >> 2;
                    o[1] = (u32)(p[1] + b[1] + p[5] + b[5]) >> 2;
                    o[2] = (u32)(p[2] + b[2] + p[6] + b[6]) >> 2;
                    o[3] = (u32)(p[3] + b[3] + p[7] + b[7]) >> 2;
                }
            }
            t->fb0 = sv;
            t->f9c = 0x10;
            (t->*(t->pm700))();
            t->fa0 -= 0x20;
        }
        if (t->fa0 != 0) {
            t->f9c = t->fa0;
            nx = t->fb0 + step;
            t->f184 = t->bb8;
            (t->*(t->pm6f4))();
            t->runall();
            t->fb0 = nx;
            t->f184 = (u8 *)t->f178;
            (t->*(t->pm6f4))();
            t->runall();
            {
                u32 n = t->f9c;
                u8 *o = t->bb8, *p = o, *pe;
                u8 *b;
                if (n & 1) pe = p + n * 4 - 4; else pe = p + n * 4;
                b = (u8 *)t->f178;
                for (; p < pe; p += 8, b += 8, o += 4) {
                    o[0] = (u32)(p[0] + b[0] + p[4] + b[4]) >> 2;
                    o[1] = (u32)(p[1] + b[1] + p[5] + b[5]) >> 2;
                    o[2] = (u32)(p[2] + b[2] + p[6] + b[6]) >> 2;
                    o[3] = (u32)(p[3] + b[3] + p[7] + b[7]) >> 2;
                }
            }
            t->f9c >>= 1;
            (t->*(t->pm700))();
        }
        src += step + step;
        dst += dpitch;
    } while (dst < e);
    delete[] t->f178;
    t->f178 = 0;
    t->f0 &= ~0x400;
}
}
