// TU: fn_8014BDD4 + fn_8014C150 + fn_8014C1A4 (merged: they share the .rodata string pool 0x802A01C8).
// fn_8014BDD4 is schedule-equivalent (schedequiv.txt, 3 instructions in another order); the other two are exact.
#include "common.h"
extern "C" {
#pragma push
#pragma use_lmw_stmw on
struct Rd { u8 d[4]; };
struct SkV { u8 pad[16]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual s32 seek(u32); };
struct T {
    u8 pad[16]; u32 w; u32 h; u32 pitch; u8 fmt[20]; Rd rd; SkV *sk; u32 ncmap;
    u8 pad2[1344 - 60]; u32 dataOff; u32 size; u8 pad3[4]; s32 f1356; u8 type; u8 cdepth; u8 desc; u8 pad4; u32 cfirst;
};
extern char lbl_802A01C8[];
extern void *lbl_8035A9F4;
s32 fn_802108B4(Rd *, void *, u32, u32 *);
void fn_801485B4(T *, s32);
void fn_801486B4(T *, char *);
void fn_8014BC1C(T *, u8 *);
void fn_8014824C(u8 *, u32, u32, s32, s32);
void fn_80148210(u8 *, u32, u32, s32, s32);
void fn_80148288(u8 *, u32, u32, u32, u32, u32, u32);
void fn_80060568(char *, s32, s32, s32);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);

static void strs(char **o) {
    o[0] = "Unsupported image type encountered"; o[1] = "Unsupported color depth."; o[2] = "Invalid palette size"; o[3] = "Unsupported file format.";
    //("Unsupported image type encountered", "Unsupported color depth.", "Invalid palette size", "Unsupported file format.");
}
void fn_8014BDD4(T *t) {
    u32 n;
    u8 h[18];
    s32 e;
    u32 off;
    u32 bpp;
    u8 *buf;
    u32 sz;
    e = fn_802108B4(&t->rd, h, 18, &n);
    if (e) fn_801485B4(t, e);
    off = h[0] + 18;
    t->type = h[2];
    t->cfirst = h[3] + (h[4] << 8);
    t->ncmap = h[5] + (h[6] << 8);
    t->cdepth = h[7];
    t->w = h[12] + (h[13] << 8);
    t->h = h[14] + (h[15] << 8);
    bpp = h[16];
    t->desc = h[17];
    e = t->sk->seek(off);
    t->dataOff = off + t->ncmap * ((t->cdepth + 7) >> 3);
    if (e) fn_801485B4(t, e);
    t->pitch = (t->w * bpp + 7) >> 3;
    t->size = t->pitch * t->h;
    switch (t->type) {
    case 1: {
        if (t->ncmap > 256) fn_801486B4(t, "Invalid palette size");
        sz = ((t->cdepth + 7) >> 3) * t->ncmap;
        if (lbl_8035A9F4 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035A9F4);
        buf = new u8[sz];
        fn_800F7E98();
        if (buf == 0) fn_800604C4(-4, 0, 0, 0);
        e = fn_802108B4(&t->rd, buf, sz, &n);
        if (e) fn_801485B4(t, e);
        fn_8014BC1C(t, buf);
        delete[] buf;
        break;
    }
    case 2:
    case 3:
        t->ncmap = 0;
        break;
    default:
        fn_801486B4(t, "Unsupported file format.");
        break;
    }
    switch (t->type) {
    case 0:
        fn_801486B4(t, "Unsupported image type encountered");
        break;
    case 1:
        fn_8014824C(t->fmt, bpp, (1 << bpp) - 1, 0, 0);
        t->f1356 = 0;
        break;
    case 2:
        switch (bpp) {
        case 16:
            fn_80148288(t->fmt, bpp, 0x7C00, 0x3E0, 0x1F, 0x8000, 0);
            break;
        case 24:
            fn_80148288(t->fmt, bpp, 0xFF0000, 0xFF00, 0xFF, 0, 0);
            break;
        case 32:
            fn_80148288(t->fmt, bpp, 0xFF00, 0xFF0000, 0xFF000000, 0xFF, 0);
            break;
        default:
            fn_80060568("Unsupported color depth.", 0, 0, 0);
            break;
        }
        t->f1356 = 0;
        break;
    case 3:
        fn_80148210(t->fmt, bpp, (1 << bpp) - 1, 0, 0);
        t->f1356 = 0;
        break;
    default:
        fn_801486B4(t, "Unsupported image type encountered");
        break;
    }
}
#pragma pop

void fn_801487AC(int);
void fn_801487C8(void);

void fn_8014C150(s32 param_1) {
    fn_801487C8();
    *(u32 *)(param_1 + 0x540) = 0;
    *(u32 *)(param_1 + 0x544) = 0;
    *(u32 *)(param_1 + 0x548) = 0;
    *(u32 *)(param_1 + 0x54c) = 0;
    *(u8 *)(param_1 + 0x550) = 0;
    *(u8 *)(param_1 + 0x551) = 0;
    *(u8 *)(param_1 + 0x552) = 0;
    fn_801487AC((int)(param_1));
}


struct P {
    u8 pad0[16];
    u32 w16;
    u32 h20;
    u32 a24;
    u16 a28;
    u8 fmt30[26];
    u32 a56;
    u8 pad60[1280];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void s4();
    u8 pad1344[4];
    u32 a1348;
    u8 *a1352;
    s32 a1356;
    u8 t1360;
    u8 b1361;
    u8 c1362;
    u8 pad1363;
    u32 a1364;
};

static inline u32 rd32(u8 *b) { return b[0] + (b[1] << 8) + (b[2] << 16) + (b[3] << 24); }
void fn_8014C1A4(P *p, u8 *h) {
    u8 *data;
    u32 bpp;
    if (p->a28) p->s4();
    data = h + 21;
    p->w16 = h[0] + (h[1] << 8);
    p->h20 = h[2] + (h[3] << 8);
    bpp = (u8)(h[4] + (h[5] << 8));
    p->a56 = h[6] + (h[7] << 8);
    p->a24 = rd32(h + 8);
    p->a1348 = rd32(h + 12);
    p->t1360 = h[16];
    p->b1361 = h[17];
    p->c1362 = h[18];
    p->a1364 = h[19] + (h[20] << 8);
    switch (p->t1360) {
    case 0:
        fn_801486B4((T *)p, "Unsupported image type encountered");
        break;
    case 1:
        fn_8014824C((u8 *)&p->a28, bpp, (1 << bpp) - 1, 0, 0);
        p->a1356 = 0;
        break;
    case 2:
        switch (bpp) {
        case 16:
            fn_80148288((u8 *)&p->a28, bpp, 0x7C00, 0x3E0, 0x1F, 0x8000, 0);
            break;
        case 24:
            fn_80148288((u8 *)&p->a28, bpp, 0xFF0000, 0xFF00, 0xFF, 0, 0);
            break;
        case 32:
            fn_80148288((u8 *)&p->a28, bpp, 0xFF00, 0xFF0000, 0xFF000000, 0xFF, 0);
            break;
        default:
            fn_80060568("Unsupported color depth.", 0, 0, 0);
            break;
        }
        p->a1356 = 0;
        break;
    case 3:
        fn_80148210((u8 *)&p->a28, bpp, (1 << bpp) - 1, 0, 0);
        p->a1356 = 0;
        break;
    default:
        fn_801486B4((T *)p, "Unsupported image type encountered");
        break;
    }
    fn_8014BC1C((T *)p, data);
    data += ((p->b1361 + 7) >> 3) * p->a56;
    p->a1352 = data;
}

} /* extern "C" */
