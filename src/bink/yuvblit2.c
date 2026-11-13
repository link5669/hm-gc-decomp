/* RAD Bink: 0x802878C0-0x8028B134 */
#include "bink_common.h"





extern u32 lbl_803008C0[];
extern u32 *lbl_802F7AE0[];
#define CT(t, x) (*(u32 *)((u8 *)(t) + ((x) & 0x3FC)))
#define YT(x) (*(u32 **)((u8 *)yt + ((x) & 0x3FC)))
void fn_802878C0(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u32 *src1;
    u16 *pv;
    u16 *pu;
    u32 *src0;
    u32 **yt;
    u32 *ct, *t1, *t2, *t3;
    p0 = lbl_80300860[0];
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[0] = p0 + count * 16;
    lbl_80300860[1] = p1 + count * 16;
    stride = (w * 4 + 63) & ~63;
    pv = (u16 *)lbl_80300860[4];
    pu = (u16 *)lbl_80300860[5];
    src0 = (u32 *)lbl_80300860[2];
    src1 = (u32 *)lbl_80300860[3];
    ct = lbl_803008C0;
    t3 = ct + 768;
    t2 = ct + 512;
    t1 = ct + 256;
    yt = lbl_802F7AE0;
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        u32 u;
        u32 v;
        u32 a;
        u32 b;
        u32 r, g, bl;
        u32 *q0, *q1;
        u = *pu++;
        v = *pv++;
        a = *src0++;
        b = *src1++;
        r = CT(t3, u >> 6);
        bl = CT(ct, v >> 6);
        g = CT(t2, v >> 6) + CT(t1, u >> 6);
        q0 = YT(a >> 22); q1 = YT(a >> 14);
        d0[0] = (q0[r] << 16) | q1[r];
        d0[8] = (q0[g] << 24) | (q0[bl] << 16) | (q1[g] << 8) | q1[bl];
        q0 = YT(b >> 22); q1 = YT(b >> 14);
        d1[0] = (q0[r] << 16) | q1[r];
        d1[8] = (q0[g] << 24) | (q0[bl] << 16) | (q1[g] << 8) | q1[bl];
        r = CT(t3, u << 2);
        bl = CT(ct, v << 2);
        g = CT(t2, v << 2) + CT(t1, u << 2);
        q0 = YT(a >> 6); q1 = YT(a << 2);
        d0[1] = (q0[r] << 16) | q1[r];
        d0[9] = (q0[g] << 24) | (q0[bl] << 16) | (q1[g] << 8) | q1[bl];
        d0 += 16;
        q0 = YT(b >> 6); q1 = YT(b << 2);
        d1[1] = (q0[r] << 16) | q1[r];
        d1[9] = (q0[g] << 24) | (q0[bl] << 16) | (q1[g] << 8) | q1[bl];
        d1 += 16;
    } while (--count);
    lbl_80300860[4] = (u8 *)pv;
    lbl_80300860[5] = (u8 *)pu;
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
}
#undef CT
#undef YT

extern u32 lbl_803008C0[];
extern u32 *lbl_802F7AE0[];
#define CT(t, x) (*(u32 *)((u8 *)(t) + ((x) & 0x3FC)))
#define DR(q) ((q[r] << 16) | q[r])
#define GB(q) ((q[g] << 24) | (q[bl] << 16) | (q[g] << 8) | q[bl])
#define YT(x) (*(u32 **)((u8 *)yt + ((x) & 0x3FC)))
void fn_80287B70(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u32 *src1;
    u16 *pv;
    u16 *pu;
    u32 *src0;
    u32 **yt;
    u32 *ct, *t1, *t2, *t3;
    p0 = lbl_80300860[0];
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[0] = p0 + count * 32;
    lbl_80300860[1] = p1 + count * 32;
    stride = (w * 4 + 63) & ~63;
    pv = (u16 *)lbl_80300860[4];
    pu = (u16 *)lbl_80300860[5];
    src0 = (u32 *)lbl_80300860[2];
    src1 = (u32 *)lbl_80300860[3];
    ct = lbl_803008C0;
    t3 = ct + 768;
    t2 = ct + 512;
    t1 = ct + 256;
    yt = lbl_802F7AE0;
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        u32 u;
        u32 v;
        u32 a;
        u32 b;
        u32 r, g, bl;
        u32 *q0, *q1;
        u = *pu++;
        v = *pv++;
        a = *src0++;
        b = *src1++;
        r = CT(t3, u >> 6);
        bl = CT(ct, v >> 6);
        g = CT(t2, v >> 6) + CT(t1, u >> 6);
        q0 = YT(a >> 22); q1 = YT(a >> 14);
        d0[0] = DR(q0); d0[1] = DR(q1); d0[8] = GB(q0); d0[9] = GB(q1);
        q0 = YT(b >> 22); q1 = YT(b >> 14);
        d1[0] = DR(q0); d1[1] = DR(q1); d1[8] = GB(q0); d1[9] = GB(q1);
        r = CT(t3, u << 2);
        bl = CT(ct, v << 2);
        g = CT(t2, v << 2) + CT(t1, u << 2);
        q0 = YT(a >> 6); q1 = YT(a << 2);
        d0[16] = DR(q0); d0[17] = DR(q1); d0[24] = GB(q0); d0[25] = GB(q1);
        d0 += 32;
        q0 = YT(b >> 6); q1 = YT(b << 2);
        d1[16] = DR(q0); d1[17] = DR(q1); d1[24] = GB(q0); d1[25] = GB(q1);
        d1 += 32;
    } while (--count);
    lbl_80300860[4] = (u8 *)pv;
    lbl_80300860[5] = (u8 *)pu;
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
}
#undef CT
#undef DR
#undef GB
#undef YT

#define TB(x) (*(u32 *)((u8 *)tbl + ((x) & 0x3FC)))
void fn_80287EC0(s32 count) {
    extern u32 lbl_80300460[];
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u32 *s0;
    u32 *s1;
    u32 *tbl;
    p0 = lbl_80300860[0];
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[0] = p0 + count * 16;
    lbl_80300860[1] = p1 + count * 16;
    stride = (w * 4 + 63) & ~63;
    s0 = (u32 *)lbl_80300860[2];
    s1 = (u32 *)lbl_80300860[3];
    tbl = lbl_80300460;
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        u32 a = *s0++;
        u32 b = *s1++;
        u32 c0, c1, c2, c3;
        c0 = TB(a >> 22);
        c1 = TB(a >> 14);
        c2 = TB(a >> 6);
        c3 = TB(a << 2);
        d0[0] = (c0 & 0xFFFF0000) | (c1 >> 16);
        d0[1] = (c2 & 0xFFFF0000) | (c3 >> 16);
        d0[8] = (c0 << 16) | (c1 & 0xFFFF);
        d0[9] = (c2 << 16) | (c3 & 0xFFFF);
        d0 += 16;
        c0 = TB(b >> 22);
        c1 = TB(b >> 14);
        c2 = TB(b >> 6);
        c3 = TB(b << 2);
        d1[0] = (c0 & 0xFFFF0000) | (c1 >> 16);
        d1[1] = (c2 & 0xFFFF0000) | (c3 >> 16);
        d1[8] = (c0 << 16) | (c1 & 0xFFFF);
        d1[9] = (c2 << 16) | (c3 & 0xFFFF);
        d1 += 16;
    } while (--count);
    lbl_80300860[2] = (u8 *)s0;
    lbl_80300860[3] = (u8 *)s1;
}
#undef TB

extern u32 lbl_80300460[];
static inline u32 dup(u32 v) { return (v << 16) | v; }
extern u32 lbl_802F9340[], lbl_802F9F60[], lbl_802FAB80[];
extern s32 lbl_802F72A0[];
#define CT(t, x) (*(u32 *)((u8 *)(t) + ((x) & 0x3FC)))
#define YT(x) (*(s32 *)((u8 *)lbl_802F72A0 + ((x) << 2)))
#define PX(l) ((u16)R[l] | (u16)G[l] | (u16)B[l])
void fn_80288294(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u32 *src1;
    u16 *pv;
    u16 *pu;
    u32 *src0;
    u32 *ct, *t1, *t2, *t3;
    s32 *yt; u32 *Rt, *Gt, *Bt;
    p0 = lbl_80300860[0];
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[0] = p0 + count * 8;
    lbl_80300860[1] = p1 + count * 8;
    stride = (w * 4 + 31) & ~31;
    src1 = (u32 *)lbl_80300860[3];
    src0 = (u32 *)lbl_80300860[2];
    pu = (u16 *)lbl_80300860[5];
    pv = (u16 *)lbl_80300860[4];
    ct = lbl_803008C0;
    t3 = ct + 768;
    t2 = ct + 512;
    t1 = ct + 256;
    Rt = lbl_802F9340;
    Bt = lbl_802FAB80;
    Gt = lbl_802F9F60;
    yt = lbl_802F72A0;
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        u32 u;
        u32 v;
        u32 a;
        u32 b;
        u16 h;
        u = *pv++;
        v = *pu++;
        a = *src0++;
        b = *src1++;
        { 
        u32 *R = (u32 *)((CT(ct, u >> 6)) * 4 + (u32)Rt);
        u32 *G = (u32 *)(((CT(t2, u >> 6) + CT(t1, v >> 6))) * 4 + (u32)Gt);
        u32 *B = (u32 *)((CT(t3, v >> 6)) * 4 + (u32)Bt);
        h = a >> 16;
        d0[0] = (((u16)R[CT(yt, h >> 6)] | (u16)G[CT(yt, h >> 6)] | (u16)B[CT(yt, h >> 6)]) << 16) | ((u16)R[CT(yt, h << 2)] | (u16)G[CT(yt, h << 2)] | (u16)B[CT(yt, h << 2)]);
        h = b >> 16;
        d1[0] = (((u16)R[CT(yt, h >> 6)] | (u16)G[CT(yt, h >> 6)] | (u16)B[CT(yt, h >> 6)]) << 16) | ((u16)R[CT(yt, h << 2)] | (u16)G[CT(yt, h << 2)] | (u16)B[CT(yt, h << 2)]); }
        { 
        u32 *R = (u32 *)((CT(ct, u << 2)) * 4 + (u32)Rt);
        u32 *G = (u32 *)(((CT(t2, u << 2) + CT(t1, v << 2))) * 4 + (u32)Gt);
        u32 *B = (u32 *)((CT(t3, v << 2)) * 4 + (u32)Bt);
        h = a & 0xFFFF;
        d0[1] = (((u16)R[CT(yt, h >> 6)] | (u16)G[CT(yt, h >> 6)] | (u16)B[CT(yt, h >> 6)]) << 16) | ((u16)R[CT(yt, h << 2)] | (u16)G[CT(yt, h << 2)] | (u16)B[CT(yt, h << 2)]);
        d0 += 8;
        h = b & 0xFFFF;
        d1[1] = (((u16)R[CT(yt, h >> 6)] | (u16)G[CT(yt, h >> 6)] | (u16)B[CT(yt, h >> 6)]) << 16) | ({ u32 _l = CT(yt, h << 2) * 4; *(u16 *)((u8 *)R + _l + 2) | *(u16 *)((u8 *)G + _l + 2) | *(u16 *)((u8 *)B + _l + 2); }); }
        d1 += 8;
    } while (--count);
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
    lbl_80300860[4] = (u8 *)pv;
    lbl_80300860[5] = (u8 *)pu;
}
void fn_802885F4(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u32 *src1;
    u16 *pv;
    u16 *pu;
    u32 *src0;
    u32 *ct, *t1, *t2, *t3;
    s32 *yt; u32 *Rt, *Gt, *Bt;
    p0 = lbl_80300860[0];
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[0] = p0 + count * 16;
    lbl_80300860[1] = p1 + count * 16;
    stride = (w * 4 + 31) & ~31;
    src1 = (u32 *)lbl_80300860[3];
    src0 = (u32 *)lbl_80300860[2];
    pu = (u16 *)lbl_80300860[5];
    pv = (u16 *)lbl_80300860[4];
    ct = lbl_803008C0;
    t3 = ct + 768;
    t1 = ct + 256;
    t2 = ct + 512;
    Rt = lbl_802F9340;
    Bt = lbl_802FAB80;
    Gt = lbl_802F9F60;
    yt = lbl_802F72A0;
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        u32 u;
        u32 v;
        u32 a;
        u32 b;
        u16 h;
        u = *pv++;
        v = *pu++;
        a = *src0++;
        b = *src1++;
        {
        u32 *R = (u32 *)((CT(ct, u >> 6)) * 4 + (u32)Rt);
        u32 *G = (u32 *)(((CT(t2, u >> 6) + CT(t1, v >> 6))) * 4 + (u32)Gt);
        u32 *B = (u32 *)((CT(t3, v >> 6)) * 4 + (u32)Bt);
        h = a >> 16;
        { u32 v0 = PX(CT(yt, h >> 6)), v1 = PX(CT(yt, h << 2));
        d0[0] = dup(v0); d0[1] = dup(v1); }
        h = b >> 16;
        { u32 v0 = PX(CT(yt, h >> 6)), v1 = PX(CT(yt, h << 2));
        d1[0] = dup(v0); d1[1] = dup(v1); } }
        {
        u32 *R = (u32 *)((CT(ct, u << 2)) * 4 + (u32)Rt);
        u32 *G = (u32 *)(((CT(t2, u << 2) + CT(t1, v << 2))) * 4 + (u32)Gt);
        u32 *B = (u32 *)((CT(t3, v << 2)) * 4 + (u32)Bt);
        h = a & 0xFFFF;
        { u32 v0 = PX(CT(yt, h >> 6)), v1 = PX(CT(yt, h << 2));
        d0[8] = dup(v0); d0[9] = dup(v1); }
        d0 += 16;
        h = b & 0xFFFF;
        { u32 v0 = PX(CT(yt, h >> 6)), v1 = PX(CT(yt, h << 2));
        d1[8] = dup(v0); d1[9] = dup(v1); } }
        d1 += 16;
    } while (--count);
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
    lbl_80300860[4] = (u8 *)pv;
    lbl_80300860[5] = (u8 *)pu;
}
#undef CT
#undef YT
#undef PX

#define TB(x) (*(u32 *)((u8 *)tbl + ((x) & 0x3FC)))
#define HI(c) (((c) & 0xFFFF0000) | ((c) >> 16))
#define LO(c) (((c) << 16) | ((c) & 0xFFFF))
void fn_8028806C(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u32 *src0;
    u32 *src1;
    u32 a, b;
    u32 *tbl;
    u32 c0, c1;
    p0 = lbl_80300860[0];
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[0] = p0 + count * 32;
    lbl_80300860[1] = p1 + count * 32;
    stride = (w * 4 + 63) & ~63;
    tbl = lbl_80300460;
    src0 = (u32 *)lbl_80300860[2];
    src1 = (u32 *)lbl_80300860[3];
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        a = *src0++;
        b = *src1++;
        { c0 = TB(a >> 22); c1 = TB(a >> 14);
        d0[0] = HI(c0); d0[1] = HI(c1); d0[8] = LO(c0); d0[9] = LO(c1); }
        { c0 = TB(a >> 6); c1 = TB(a << 2);
        d0[16] = HI(c0); d0[17] = HI(c1); d0[24] = LO(c0); d0[25] = LO(c1); }
        d0 += 32;
        { c0 = TB(b >> 14); c1 = TB(b >> 6);
        d1[0] = HI(c0); d1[1] = HI(c1); d1[8] = LO(c0); d1[9] = LO(c1); }
        { c0 = TB(b >> 6); c1 = TB(b << 2);
        d1[16] = HI(c0); d1[17] = HI(c1); d1[24] = LO(c0); d1[25] = LO(c1); }
        d1 += 32;
    } while (--count);
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
}
#undef TB
#undef HI
#undef LO

#define T16(i) ((u16)((u32 *)lbl_802FFC60)[i])
void fn_80288990(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u32 *src0;
    u32 *src1;
    u32 a, b;
    p0 = lbl_80300860[0];
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[0] = p0 + count * 8;
    lbl_80300860[1] = p1 + count * 8;
    stride = (w * 4 + 31) & ~31;
    src1 = (u32 *)lbl_80300860[3];
    src0 = (u32 *)lbl_80300860[2];
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        u16 h, l;
        a = *src0++;
        b = *src1++;
        h = a >> 16;
        d0[0] = (T16(h >> 8) << 16) | T16(h & 0xFF);
        h = b >> 16;
        d1[0] = (T16(h >> 8) << 16) | T16(h & 0xFF);
        l = a & 0xFFFF;
        d0[1] = (T16(l >> 8) << 16) | T16(l & 0xFF);
        d0 += 8;
        l = b & 0xFFFF;
        d1[1] = (T16(l >> 8) << 16) | T16(l & 0xFF);
        d1 += 8;
    } while (--count);
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
}
#undef T16

#define T16(i) ((u16)((u32 *)lbl_802FFC60)[i])
void fn_80288B1C(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u32 *src0;
    u32 *src1;
    u32 a, b;
    p0 = lbl_80300860[0];
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[0] = p0 + count * 16;
    lbl_80300860[1] = p1 + count * 16;
    stride = (w * 4 + 31) & ~31;
    src1 = (u32 *)lbl_80300860[3];
    src0 = (u32 *)lbl_80300860[2];
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        u16 h, l;
        a = *src0++;
        b = *src1++;
        h = a >> 16;
        { u32 x, y; y = T16(h >> 8); x = T16(h & 0xFF);
        d0[1] = dup(x); d0[0] = dup(y); }
        h = b >> 16;
        { u32 x, y; x = T16(h >> 8); y = T16(h & 0xFF);
        d1[0] = dup(x); d1[1] = dup(y); }
        l = a & 0xFFFF;
        { u32 x, y; x = T16(l >> 8); y = T16(l & 0xFF);
        d0[8] = dup(x); d0[9] = dup(y); }
        d0 += 16;
        l = b & 0xFFFF;
        { u32 x, y; x = T16(l >> 8); y = T16(l & 0xFF);
        d1[8] = dup(x); d1[9] = dup(y); }
        d1 += 16;
    } while (--count);
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
}
#undef T16

#define CT(t, x) (*(u32 *)((u8 *)(t) + ((x) & 0x3FC)))
#define YT(x) (*(u32 **)((u8 *)yt + ((x) & 0x3FC)))
void fn_80288CD8(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u32 *src1;
    u16 *pv;
    u16 *pu;
    u32 *src0;
    u32 *m0;
    u32 *m1;
    u32 **yt;
    u32 *ct, *t1, *t2, *t3;
    p0 = lbl_80300860[0];
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[0] = p0 + count * 16;
    lbl_80300860[1] = p1 + count * 16;
    stride = (w * 4 + 63) & ~63;
    m0 = (u32 *)lbl_80300860[6];
    m1 = (u32 *)lbl_80300860[7];
    pv = (u16 *)lbl_80300860[4];
    pu = (u16 *)lbl_80300860[5];
    src0 = (u32 *)lbl_80300860[2];
    src1 = (u32 *)lbl_80300860[3];
    ct = lbl_803008C0;
    t3 = ct + 768;
    t2 = ct + 512;
    t1 = ct + 256;
    yt = lbl_802F7AE0;
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        u32 u;
        u32 v;
        u32 a;
        u32 b;
        u32 ma, mb;
        u32 r, g, bl;
        u32 *q0, *q1;
        u = *pu++; 
        v = *pv++; 
        a = *src0++; 
        b = *src1++; 
        ma = *m0++; 
        mb = *m1++; 
        r = CT(t3, u >> 6);
        bl = CT(ct, v >> 6);
        g = CT(t2, v >> 6) + CT(t1, u >> 6);
        q0 = YT(a >> 22); q1 = YT(a >> 14);
        d0[0] = (ma & 0xFF000000) | (q0[r] << 16) | ((ma >> 8) & 0xFF00) | q1[r];
        d0[8] = (q0[g] << 24) | (q0[bl] << 16) | (q1[g] << 8) | q1[bl];
        q0 = YT(b >> 22); q1 = YT(b >> 14);
        d1[0] = (mb & 0xFF000000) | (q0[r] << 16) | ((mb >> 8) & 0xFF00) | q1[r];
        d1[8] = (q0[g] << 24) | (q0[bl] << 16) | (q1[g] << 8) | q1[bl];
        r = CT(t3, u << 2);
        bl = CT(ct, v << 2);
        g = CT(t2, v << 2) + CT(t1, u << 2);
        q0 = YT(a >> 6); q1 = YT(a << 2);
        d0[1] = ((ma << 16) & 0xFF000000) | (q0[r] << 16) | ((ma << 8) & 0xFF00) | q1[r];
        d0[9] = (q0[g] << 24) | (q0[bl] << 16) | (q1[g] << 8) | q1[bl];
        d0 += 16;
        q0 = YT(b >> 6); q1 = YT(b << 2);
        d1[1] = ((mb << 16) & 0xFF000000) | (q0[r] << 16) | ((mb << 8) & 0xFF00) | q1[r];
        d1[9] = (q0[g] << 24) | (q0[bl] << 16) | (q1[g] << 8) | q1[bl];
        d1 += 16;
    } while (--count);
    lbl_80300860[4] = (u8 *)pv;
    lbl_80300860[5] = (u8 *)pu;
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
    lbl_80300860[6] = (u8 *)m0;
    lbl_80300860[7] = (u8 *)m1;
}
#undef CT
#undef YT

#define CT(t, x) (*(u32 *)((u8 *)(t) + ((x) & 0x3FC)))
#define GB(q) ((q[g] << 24) | (q[bl] << 16) | (q[g] << 8) | q[bl])
#define DA(q, A) ({ u32 _a = (A); (_a << 24) | (q[r] << 16) | (_a << 8) | q[r]; })
#define YT(x) (*(u32 **)((u8 *)yt + ((x) & 0x3FC)))
void fn_80289048(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u16 *pu;
    u32 *src0;
    u32 *src1;
    u32 *m0;
    u32 *m1;
    u16 *pv;
    u32 **yt;
    u32 *ct, *t1, *t2, *t3;
    p0 = lbl_80300860[0];
    lbl_80300860[0] = p0 + count * 32;
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[1] = p1 + count * 32;
    stride = (w * 4 + 63) & ~63;
    m0 = (u32 *)lbl_80300860[6];
    m1 = (u32 *)lbl_80300860[7];
    pu = (u16 *)lbl_80300860[5];
    pv = (u16 *)lbl_80300860[4];
    src0 = (u32 *)lbl_80300860[2];
    src1 = (u32 *)lbl_80300860[3];
    ct = lbl_803008C0;
    t3 = ct + 768;
    t2 = ct + 512;
    t1 = ct + 256;
    yt = lbl_802F7AE0;
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        u32 u;
        u32 v;
        u32 a;
        u32 b;
        u32 ma, mb;
        u32 r, g, bl;
        u32 *q0, *q1;
        u = *pu;
        pu++;
        v = *pv;
        a = *src0;
        src0++;
        b = *src1;
        mb = *m1;
        pv++;
        ma = *m0;
        m0++;
        src1++;
        m1++;
        bl = CT(ct, v >> 6);
        r = CT(t3, u >> 6);
        g = CT(t2, v >> 6) + CT(t1, u >> 6);
        q0 = YT(a >> 22); q1 = YT(a >> 14);
        d0[0] = DA(q0, ma >> 24); d0[1] = DA(q1, (ma >> 16) & 0xFF); d0[8] = GB(q0); d0[9] = GB(q1);
        q0 = YT(b >> 22); q1 = YT(b >> 14);
        d1[0] = DA(q0, mb >> 24); d1[1] = DA(q1, (mb >> 16) & 0xFF); d1[8] = GB(q0); d1[9] = GB(q1);
        d1 += 32;
        r = CT(t3, u << 2);
        bl = CT(ct, v << 2);
        g = CT(t2, v << 2) + CT(t1, u << 2);
        q0 = YT(a >> 6); q1 = YT(a << 2);
        d0[16] = DA(q0, (ma >> 8) & 0xFF); d0[17] = DA(q1, ma & 0xFF); d0[24] = GB(q0); d0[25] = GB(q1);
        d0 += 32;
        q0 = YT(b >> 6); q1 = YT(b << 2);
        d1[16] = DA(q0, (mb >> 8) & 0xFF); d1[17] = DA(q1, mb & 0xFF); d1[24] = GB(q0); d1[25] = GB(q1);
    } while (--count);
    lbl_80300860[4] = (u8 *)pv;
    lbl_80300860[5] = (u8 *)pu;
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
    lbl_80300860[6] = (u8 *)m0;
    lbl_80300860[7] = (u8 *)m1;
}
#undef CT
#undef GB
#undef DA
#undef YT

extern u32 lbl_80300460[];
#define TB(x) (*(u32 *)((u8 *)tbl + ((x) & 0x3FC)))
#define HI(c) (((c) & 0xFFFF0000) | ((c) >> 16))
#define LO(c) (((c) << 16) | ((c) & 0xFFFF))
void fn_80289528(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u32 *src0;
    u32 *src1;
    u32 *m1;
    u32 *m0;
    u32 a, b;
    u32 *tbl;
    u32 c0, c1, c2, c3;
    p0 = lbl_80300860[0];
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[0] = p0 + count * 16;
    lbl_80300860[1] = p1 + count * 16;
    stride = (w * 4 + 63) & ~63;
    tbl = lbl_80300460;
    m0 = (u32 *)lbl_80300860[6];
    m1 = (u32 *)lbl_80300860[7];
    src0 = (u32 *)lbl_80300860[2];
    src1 = (u32 *)lbl_80300860[3];
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        u32 a2, b2;
        a = *src0++;
        b = *m0++;
        a2 = *src1++;
        b2 = *m1++;
        c0 = TB(a >> 22); c1 = TB(a >> 6); c2 = TB(a >> 14); c3 = TB(a << 2);
        d0[0] = (b & 0xFF000000) | (c0 & 0xFFFF0000) | (c2 >> 16) | ((b >> 8) & 0xFF00);
        d0[1] = ((b << 16) & 0xFF000000) | (c1 & 0xFFFF0000) | (c3 >> 16) | ((b << 8) & 0xFF00);
        d0[8] = (c0 << 16) | (c2 & 0xFFFF);
        d0[9] = (c1 << 16) | (c3 & 0xFFFF);
        a = a2;
        b = b2;
        c0 = TB(a >> 22); c1 = TB(a >> 6); c2 = TB(a >> 14); c3 = TB(a << 2);
        d1[0] = (b & 0xFF000000) | (c0 & 0xFFFF0000) | (c2 >> 16) | ((b >> 8) & 0xFF00);
        d1[1] = ((b << 16) & 0xFF000000) | (c1 & 0xFFFF0000) | (c3 >> 16) | ((b << 8) & 0xFF00);
        d1[8] = (c0 << 16) | (c2 & 0xFFFF);
        d1[9] = (c1 << 16) | (c3 & 0xFFFF);
        d0 += 16;
        d1 += 16;
    } while (--count);
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
    lbl_80300860[6] = (u8 *)m0;
    lbl_80300860[7] = (u8 *)m1;
}
#undef TB
#undef HI
#undef LO

extern u32 lbl_80300460[];
#define TB(x) (*(u32 *)((u8 *)tbl + ((x) & 0x3FC)))
#define HI(c) (((c) & 0xFFFF0000) | ((c) >> 16))
#define LO(c) (((c) << 16) | ((c) & 0xFFFF))
void fn_80289734(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u32 *src0;
    u32 *src1;
    u32 *m1;
    u32 *m0;
    u32 a, b;
    u32 *tbl;
    u32 c0, c1, c2, c3;
    p0 = lbl_80300860[0];
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[0] = p0 + count * 32;
    lbl_80300860[1] = p1 + count * 32;
    stride = (w * 4 + 63) & ~63;
    tbl = lbl_80300460;
    m0 = (u32 *)lbl_80300860[6];
    m1 = (u32 *)lbl_80300860[7];
    src0 = (u32 *)lbl_80300860[2];
    src1 = (u32 *)lbl_80300860[3];
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        u32 a2, b2;
        a = *src0++;
        a2 = *src1++;
        b = *m0++;
        b2 = *m1++;
        { u32 A0 = b >> 24, A1 = (b >> 16) & 0xFF;
        c0 = TB(a >> 22); c1 = TB(a >> 14);
        d0[0] = (A0 << 24) | (c0 & 0xFFFF0000) | (c0 >> 16) | (A0 << 8); d0[1] = (A1 << 24) | (c1 & 0xFFFF0000) | (c1 >> 16) | (A1 << 8); d0[8] = LO(c0); d0[9] = LO(c1);
        c0 = TB(a >> 6); c1 = TB(a << 2);
        d0[16] = (A0 << 24) | (c0 & 0xFFFF0000) | (c0 >> 16) | (A0 << 8); d0[17] = (A1 << 24) | (c1 & 0xFFFF0000) | (c1 >> 16) | (A1 << 8); d0[24] = LO(c0); d0[25] = LO(c1); }
        d0 += 32;
        { u32 A0 = b2 >> 24, A1 = (b2 >> 16) & 0xFF;
        c0 = TB(a2 >> 14); c1 = TB(a2 >> 6);
        d1[0] = (A0 << 24) | (c0 & 0xFFFF0000) | (c0 >> 16) | (A0 << 8); d1[1] = (A1 << 24) | (c1 & 0xFFFF0000) | (c1 >> 16) | (A1 << 8); d1[8] = LO(c0); d1[9] = LO(c1);
        c0 = TB(a2 >> 6); c1 = TB(a2 << 2);
        d1[16] = (A0 << 24) | (c0 & 0xFFFF0000) | (c0 >> 16) | (A0 << 8); d1[17] = (A1 << 24) | (c1 & 0xFFFF0000) | (c1 >> 16) | (A1 << 8); d1[24] = LO(c0); d1[25] = LO(c1); }
        d1 += 32;
    } while (--count);
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
    lbl_80300860[6] = (u8 *)m0;
    lbl_80300860[7] = (u8 *)m1;
}
#undef TB
#undef HI
#undef LO

extern u8 lbl_802F8B20[];
#define AL(x) ((u16)*(u32 *)((u8 *)lbl_802F8B20 + ((x) & 0x3FC)))
#define PXA(l, x) (AL(x) | (u16)B[l] | (u16)G[l] | (u16)R[l])
#define CT(t, x) (*(u32 *)((u8 *)(t) + ((x) & 0x3FC)))
void fn_802899EC(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u16 *pu;
    u32 *src0;
    u32 *src1;
    u16 *pv;
    u32 *m0;
    u32 *m1;
    u32 *ct, *t1, *t2, *t3;
    s32 *yt; u32 *Rt, *Gt, *Bt;
    p0 = lbl_80300860[0];
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[0] = p0 + count * 8;
    lbl_80300860[1] = p1 + count * 8;
    stride = (w * 4 + 31) & ~31;
    src0 = (u32 *)lbl_80300860[2];
    src1 = (u32 *)lbl_80300860[3];
    pv = (u16 *)lbl_80300860[4];
    m0 = (u32 *)lbl_80300860[6];
    pu = (u16 *)lbl_80300860[5];
    m1 = (u32 *)lbl_80300860[7];
    ct = lbl_803008C0;
    t3 = ct + 768;
    t2 = ct + 512;
    t1 = ct + 256;
    Rt = lbl_802F9340;
    Bt = lbl_802FAB80;
    Gt = lbl_802F9F60;
    yt = lbl_802F72A0;
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        u32 u;
        u32 v;
        u32 a;
        u32 b;
        u32 ma;
        u32 mb;
        u16 h;
        u16 k;
        u = *pv++;
        v = *pu++;
        a = *src0++;
        b = *src1++;
        ma = *m0++;
        mb = *m1++;
        { 
        u32 *G = (u32 *)(((CT(t2, u >> 6) + CT(t1, v >> 6))) * 4 + (u32)Gt);
        u32 *B = (u32 *)((CT(t3, v >> 6)) * 4 + (u32)Bt);
        u32 *R = (u32 *)((CT(ct, u >> 6)) * 4 + (u32)Rt);
        h = a >> 16;
        k = ma >> 16;
        d0[0] = (PXA(CT(yt, h >> 6), k >> 6) << 16) | PXA(CT(yt, h << 2), k << 2);
        h = b >> 16;
        k = mb >> 16;
        d1[0] = (PXA(CT(yt, h >> 6), k >> 6) << 16) | PXA(CT(yt, h << 2), k << 2); }
        { 
        u32 *R = (u32 *)((CT(ct, u << 2)) * 4 + (u32)Rt);
        u32 *B = (u32 *)((CT(t3, v << 2)) * 4 + (u32)Bt);
        u32 *G = (u32 *)(((CT(t2, u << 2) + CT(t1, v << 2))) * 4 + (u32)Gt);
        h = a & 0xFFFF;
        k = ma & 0xFFFF;
        d0[1] = (PXA(CT(yt, h >> 6), k >> 6) << 16) | PXA(CT(yt, h << 2), k << 2);
        d0 += 8;
        h = b & 0xFFFF;
        k = mb & 0xFFFF;
        d1[1] = (PXA(CT(yt, h >> 6), k >> 6) << 16) | PXA(CT(yt, h << 2), k << 2); }
        d1 += 8;
    } while (--count);
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
    lbl_80300860[4] = (u8 *)pv;
    lbl_80300860[5] = (u8 *)pu;
    lbl_80300860[6] = (u8 *)m0;
    lbl_80300860[7] = (u8 *)m1;
}
void fn_80289E40(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u16 *pu;
    u32 *src0;
    u32 *src1;
    u16 *pv;
    u32 *m0;
    u32 *m1;
    u32 *ct, *t1, *t2, *t3;
    s32 *yt;
    p0 = lbl_80300860[0];
    base = lbl_80300860[18];
    p1 = lbl_80300860[1];
    w = (s32)lbl_80300860[17];
    y0 = (s32)(p0 - base) / w;
    y1 = (s32)(p1 - base) / w;
    lbl_80300860[0] = p0 + count * 16;
    lbl_80300860[1] = p1 + count * 16;
    stride = (w * 4 + 31) & ~31;
    m0 = (u32 *)lbl_80300860[6];
    pv = (u16 *)lbl_80300860[4];
    pu = (u16 *)lbl_80300860[5];
    src0 = (u32 *)lbl_80300860[2];
    src1 = (u32 *)lbl_80300860[3];
    ct = lbl_803008C0;
    t3 = ct + 768;
    t2 = ct + 512;
    t1 = ct + 256;
    yt = lbl_802F72A0;
    m1 = (u32 *)lbl_80300860[7];
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4);
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4);
    do {
        u32 u;
        u32 v;
        u32 a;
        u32 b;
        u32 ma;
        u32 mb;
        u16 h;
        u16 k;
        u = *pv++;
        v = *pu++;
        a = *src0++;
        b = *src1++;
        ma = *m0++;
        mb = *m1++;
        { u32 *R = lbl_802F9340 + CT(ct, u >> 6);
        u32 *G = lbl_802F9F60 + (CT(t2, u >> 6) + CT(t1, v >> 6));
        u32 *B = lbl_802FAB80 + CT(t3, v >> 6);
        h = a >> 16;
        k = ma >> 16;
        { u32 v0 = PXA(CT(yt, h >> 6), k >> 6), v1 = PXA(CT(yt, h << 2), k << 2);
        d0[0] = dup(v0); d0[1] = dup(v1); }
        h = b >> 16;
        k = mb >> 16;
        { u32 v0 = PXA(CT(yt, h >> 6), k >> 6), v1 = PXA(CT(yt, h << 2), k << 2);
        d1[0] = dup(v0); d1[1] = dup(v1); } }
        { u32 *B = lbl_802FAB80 + CT(t3, v << 2);
        u32 *G = lbl_802F9F60 + (CT(t2, u << 2) + CT(t1, v << 2));
        u32 *R = lbl_802F9340 + CT(ct, u << 2);
        h = a & 0xFFFF;
        k = ma & 0xFFFF;
        { u32 v0 = PXA(CT(yt, h >> 6), k >> 6), v1 = PXA(CT(yt, h << 2), k << 2);
        d0[8] = dup(v0); d0[9] = dup(v1); }
        d0 += 16;
        h = b & 0xFFFF;
        k = mb & 0xFFFF;
        { u32 v0 = PXA(CT(yt, h >> 6), k >> 6), v1 = PXA(CT(yt, h << 2), k << 2);
        d1[8] = dup(v0); d1[9] = dup(v1); } }
        d1 += 16;
    } while (--count);
    lbl_80300860[5] = (u8 *)pu;
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
    lbl_80300860[6] = (u8 *)m0;
    lbl_80300860[4] = (u8 *)pv;
    lbl_80300860[7] = (u8 *)m1;
}
#undef CT
#undef AL
#undef PXA

extern u8 lbl_802F8B20[];
#define TA(i) ((u16)((u32 *)lbl_802F8B20)[i])
#define TB2(i) ((u16)((u32 *)lbl_802FFC60)[i])
void fn_8028A2E0(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u32 *src0;
    u32 *src1;
    u32 *m1;
    u32 *m0;
    u32 n = count;
    m0 = (u32 *)lbl_80300860[6]; /*P*/
    p0 = lbl_80300860[0]; /*P*/
    base = lbl_80300860[18]; /*P*/
    p1 = lbl_80300860[1]; /*P*/
    w = (s32)lbl_80300860[17]; /*P*/
    y0 = (s32)(p0 - base) / w; /*P*/
    y1 = (s32)(p1 - base) / w; /*P*/
    lbl_80300860[0] = p0 + count * 8; /*P*/
    stride = (w * 4 + 31) & ~31; /*P*/
    m1 = (u32 *)lbl_80300860[7]; /*P*/
    src0 = (u32 *)lbl_80300860[2]; /*P*/
    src1 = (u32 *)lbl_80300860[3]; /*P*/
    lbl_80300860[1] = p1 + count * 8; /*P*/
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4); /*P*/
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4); /*P*/
    do {
        u32 a0, b0, a1, b1;
        u16 x, y;
        a0 = *m0++;
        b0 = *src0++;
        a1 = *m1;
        b1 = *src1++; m1++;
        x = a0 >> 16; y = b0 >> 16;
        d0[0] = ((TA(x >> 8) | TB2(y >> 8)) << 16) | (TA(x & 0xFF) | TB2(y & 0xFF));
        x = a1 >> 16; y = b1 >> 16;
        d1[0] = ((TA(x >> 8) | TB2(y >> 8)) << 16) | (TA(x & 0xFF) | TB2(y & 0xFF));
        y = b0 & 0xFFFF; x = a0 & 0xFFFF;
        d0[1] = ((TA(x >> 8) | TB2(y >> 8)) << 16) | (TA(x & 0xFF) | TB2(y & 0xFF));
        y = b1 & 0xFFFF; x = a1 & 0xFFFF;
        d1[1] = ((TA(x >> 8) | TB2(y >> 8)) << 16) | (TA(x & 0xFF) | TB2(y & 0xFF));
        d0 += 8;
        d1 += 8;
    } while (--n);
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
    lbl_80300860[6] = (u8 *)m0;
    lbl_80300860[7] = (u8 *)m1;
}
void fn_8028A528(s32 count) {
    u8 *p0;
    u8 *base;
    u8 *p1;
    s32 w;
    u32 y0;
    u32 y1;
    u32 stride;
    u32 *d0;
    u32 *d1;
    u32 *src0;
    u32 *src1;
    u32 *m1;
    u32 *m0;
    u32 n = count;
    m0 = (u32 *)lbl_80300860[6]; /*P*/
    p0 = lbl_80300860[0]; /*P*/
    base = lbl_80300860[18]; /*P*/
    p1 = lbl_80300860[1]; /*P*/
    w = (s32)lbl_80300860[17]; /*P*/
    y0 = (s32)(p0 - base) / w; /*P*/
    y1 = (s32)(p1 - base) / w; /*P*/
    lbl_80300860[0] = p0 + count * 16; /*P*/
    stride = (w * 4 + 31) & ~31; /*P*/
    m1 = (u32 *)lbl_80300860[7]; /*P*/
    src0 = (u32 *)lbl_80300860[2]; /*P*/
    src1 = (u32 *)lbl_80300860[3]; /*P*/
    lbl_80300860[1] = p1 + count * 16; /*P*/
    d0 = (u32 *)(base + stride * (y0 >> 2) + (y0 & 3) * 8 + (p0 - (base + y0 * w)) * 4); /*P*/
    d1 = (u32 *)(base + stride * (y1 >> 2) + (y1 & 3) * 8 + (p1 - (base + y1 * w)) * 4); /*P*/
    do {
        u32 a0, b0, a1, b1;
        u16 x, y;
        a0 = *m0++;
        b0 = *src0++;
        a1 = *m1;
        b1 = *src1++; m1++;
        x = a0 >> 16; y = b0 >> 16;
        { u32 v0 = TA(x >> 8) | TB2(y >> 8); u32 v1 = TA(x & 0xFF) | TB2(y & 0xFF);
        d0[0] = dup(v0); d0[1] = dup(v1); }
        y = b1 >> 16; x = a1 >> 16;
        { u32 v0 = TA(x >> 8) | TB2(y >> 8); u32 v1 = TA(x & 0xFF) | TB2(y & 0xFF);
        d1[0] = dup(v0); d1[1] = dup(v1); }
        y = b0 & 0xFFFF; x = a0 & 0xFFFF;
        { u32 v0 = TA(x >> 8) | TB2(y >> 8); u32 v1 = TA(x & 0xFF) | TB2(y & 0xFF);
        d0[8] = dup(v0); d0[9] = dup(v1); }
        y = b1 & 0xFFFF; x = a1 & 0xFFFF;
        { u32 v0 = TA(x >> 8) | TB2(y >> 8); u32 v1 = TA(x & 0xFF) | TB2(y & 0xFF);
        d1[8] = dup(v0); d1[9] = dup(v1); }
        d0 += 16;
        d1 += 16;
    } while (--n);
    lbl_80300860[2] = (u8 *)src0;
    lbl_80300860[3] = (u8 *)src1;
    lbl_80300860[6] = (u8 *)m0;
    lbl_80300860[7] = (u8 *)m1;
}
#undef TA
#undef TB2

void fn_8028A7A0(void) {

}

void fn_8028A7A4(void) {

}

void fn_8028A7A8(void) {

}

void fn_8028A7AC(void) {

}

void fn_8028A7B0(void) {
}

void fn_8028A7B4(void) {
}

void fn_8028A7B8(void) {
}

void fn_8028A7BC(void) {
}

u8 *fn_8028A7C0(u8 *addr, s32 pitch) {
    u8 *base = lbl_80300860[18];
    s32 row = (addr - base) / (s32)lbl_80300860[17];
    return base + pitch * ((u32)row >> 2) + ((row & 3) << 3) + ((addr - (base + row * (s32)lbl_80300860[17])) << 2);
}

#define ROW(D, Y) \
    { \
        u32 *d = (u32 *)lbl_80300860[D]; \
        u32 *y = (u32 *)lbl_80300860[Y]; \
        u32 *u = (u32 *)lbl_80300860[4]; \
        u32 *v = (u32 *)lbl_80300860[5]; \
        s32 i = count >> 1; \
        while (--i != -1) { \
            u32 yy = *y++, uu = *u++, vv = *v++; \
            *d++ = (yy & 0xFF000000) + ((uu >> 8) & 0xFF0000) + ((yy >> 8) & 0xFF00) + (vv >> 24); \
            *d++ = ((yy << 16) & 0xFF000000) + (uu & 0xFF0000) + ((yy << 8) & 0xFF00) + ((vv >> 16) & 0xFF); \
            yy = *y++; \
            *d++ = (yy & 0xFF000000) + ((uu << 8) & 0xFF0000) + ((yy >> 8) & 0xFF00) + ((vv >> 8) & 0xFF); \
            *d++ = ((yy << 16) & 0xFF000000) + ((uu << 16) & 0xFF0000) + ((yy << 8) & 0xFF00) + (vv & 0xFF); \
        } \
        if (count & 1) { \
            u32 yy; u16 uu, vv; \
            yy = *y; \
            uu = *(u16 *)u; \
            vv = *(u16 *)v; \
            d[0] = (yy & 0xFF000000) + ((uu << 8) & 0xFF0000) + ((yy >> 8) & 0xFF00) + (vv >> 8); \
            d[1] = ((yy << 16) & 0xFF000000) + ((uu << 16) & 0xFF0000) + ((yy << 8) & 0xFF00) + (vv & 0xFF); \
        } \
    }
void fn_8028A804(s32 count) {
    ROW(0, 2)
    ROW(1, 3)
    lbl_80300860[0] += count * 8;
    lbl_80300860[1] += count * 8;
    lbl_80300860[2] += count * 4;
    lbl_80300860[3] += count * 4;
    lbl_80300860[4] += count * 2;
    lbl_80300860[5] += count * 2;
}
#undef ROW

#define PX(YW, UV) \
    { u32 ya = (YW) & 0xFF000000, yb = (YW) & 0xFF0000; \
      *d++ = ya + (ya >> 16) + (UV); \
      *d++ = (yb << 8) + (yb >> 8) + (UV); } 
#define PX2(YW, UV) \
    { u32 yc = (YW) & 0xFF00, yd = (YW) & 0xFF; \
      *d++ = (yc << 16) + yc + (UV); \
      *d++ = (yd << 24) + (yd << 8) + (UV); }
#define ROW(D, Y) \
    { \
        u32 *d = (u32 *)lbl_80300860[D]; \
        u32 *y = (u32 *)lbl_80300860[Y]; \
        u32 *u = (u32 *)lbl_80300860[4]; \
        u32 *v = (u32 *)lbl_80300860[5]; \
        s32 i = count >> 1; \
        while (--i != -1) { \
            u32 uu = *u++, vv = *v++, yy = *y++, uv; \
            uv = ((uu >> 8) & 0xFF0000) + (vv >> 24); PX(yy, uv) \
            uv = (uu & 0xFF0000) + ((vv >> 16) & 0xFF); PX2(yy, uv) \
            yy = *y++; \
            uv = ((uu << 8) & 0xFF0000) + ((vv >> 8) & 0xFF); PX(yy, uv) \
            uv = ((uu << 16) & 0xFF0000) + (vv & 0xFF); PX2(yy, uv) \
        } \
        if (count & 1) { \
            u16 uu = *(u16 *)u, vv = *(u16 *)v; u32 yy = *y, uv; \
            uv = ((uu << 8) & 0xFF0000) + (vv >> 8); PX(yy, uv) \
            uv = ((uu << 16) & 0xFF0000) + (vv & 0xFF); PX2(yy, uv) \
        } \
    }
void fn_8028AAC8(s32 count) {
    ROW(0, 2)
    ROW(1, 3)
    lbl_80300860[0] += count * 16;
    lbl_80300860[1] += count * 16;
    lbl_80300860[2] += count * 4;
    lbl_80300860[3] += count * 4;
    lbl_80300860[4] += count * 2;
    lbl_80300860[5] += count * 2;
}
#undef PX
#undef PX2
#undef ROW

void fn_8028AEAC(s32 n) {
    u32 *dst = (u32 *)lbl_80300860[0];
    u32 *src = (u32 *)lbl_80300860[2];
    s32 i = n;
    while (--i != -1) {
        u32 v = *src++;
        *dst++ = (v & 0xFF000000) + ((v >> 8) & 0xFF00) + 0x800080;
        *dst++ = ((v << 16) & 0xFF000000) + ((v & 0xFF) << 8) + 0x800080;
    }
    dst = (u32 *)lbl_80300860[1];
    src = (u32 *)lbl_80300860[3];
    i = n;
    while (--i != -1) {
        u32 v = *src++;
        *dst++ = (v & 0xFF000000) + ((v >> 8) & 0xFF00) + 0x800080;
        *dst++ = ((v << 16) & 0xFF000000) + ((v & 0xFF) << 8) + 0x800080;
    }
    lbl_80300860[0] += n * 8;
    lbl_80300860[1] += n * 8;
    lbl_80300860[2] += n * 4;
    lbl_80300860[3] += n * 4;
}

void fn_8028AFB8(s32 n) {
    u32 *dst = (u32 *)lbl_80300860[0];
    u32 *src = (u32 *)lbl_80300860[2];
    s32 i = n;
    while (--i != -1) {
        u32 v = *src++;
        *dst++ = (v & 0xFF000000) + ((v & 0xFF000000) >> 16) + 0x800080;
        *dst++ = ((v & 0xFF0000) << 8) + ((v & 0xFF0000) >> 8) + 0x800080;
        *dst++ = ((v & 0xFF00) << 16) + (v & 0xFF00) + 0x800080;
        *dst++ = ((v & 0xFF) << 24) + ((v & 0xFF) << 8) + 0x800080;
    }
    dst = (u32 *)lbl_80300860[1];
    src = (u32 *)lbl_80300860[3];
    i = n;
    while (--i != -1) {
        u32 v = *src++;
        *dst++ = (v & 0xFF000000) + ((v & 0xFF000000) >> 16) + 0x800080;
        *dst++ = ((v & 0xFF0000) << 8) + ((v & 0xFF0000) >> 8) + 0x800080;
        *dst++ = ((v & 0xFF00) << 16) + (v & 0xFF00) + 0x800080;
        *dst++ = ((v & 0xFF) << 24) + ((v & 0xFF) << 8) + 0x800080;
    }
    lbl_80300860[0] += n * 16;
    lbl_80300860[1] += n * 16;
    lbl_80300860[2] += n * 4;
    lbl_80300860[3] += n * 4;
}
