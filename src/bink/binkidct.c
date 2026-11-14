/* RAD Bink: 0x80290650-0x80293ED8 */
#include "bink_common.h"

void fn_80290650(s32 *data, u8 *in) {
    s32 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    s32 tmp10, tmp11, tmp12, tmp13;
    s32 z1, z2, z3, z4, z5, z11, z13;
    s32 *p = data;
    int i;

    for (i = 8; i > 0; i--) {
        tmp0 = (in[0] + in[7]) << 8;
        tmp7 = (in[0] - in[7]) << 8;
        tmp1 = (in[1] + in[6]) << 8;
        tmp6 = (in[1] - in[6]) << 8;
        tmp2 = (in[2] + in[5]) << 8;
        tmp5 = (in[2] - in[5]) << 8;
        tmp3 = (in[3] + in[4]) << 8;
        tmp4 = (in[3] - in[4]) << 8;
        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;
        p[0] = tmp10 + tmp11;
        p[4] = tmp10 - tmp11;
        z1 = ((tmp12 + tmp13) * 1448) >> 11;
        p[2] = tmp13 + z1;
        p[6] = tmp13 - z1;
        tmp10 = tmp4 + tmp5;
        tmp11 = tmp5 + tmp6;
        tmp12 = tmp6 + tmp7;
        z5 = ((tmp10 - tmp12) * 784) >> 11;
        z2 = ((tmp10 * 1108) >> 11) + z5;
        z4 = ((tmp12 * 2676) >> 11) + z5;
        z3 = (tmp11 * 1448) >> 11;
        z11 = tmp7 + z3;
        z13 = tmp7 - z3;
        p[5] = z13 + z2;
        p[3] = z13 - z2;
        p[1] = z11 + z4;
        p[7] = z11 - z4;
        p += 8;
        in += 8;
    }
    p = data;
    for (i = 8; i > 0; i--) {
        tmp0 = p[0] + p[56];
        tmp7 = p[0] - p[56];
        tmp1 = p[8] + p[48];
        tmp6 = p[8] - p[48];
        tmp2 = p[16] + p[40];
        tmp5 = p[16] - p[40];
        tmp3 = p[24] + p[32];
        tmp4 = p[24] - p[32];
        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;
        p[0] = tmp10 + tmp11;
        p[32] = tmp10 - tmp11;
        z1 = ((tmp12 + tmp13) * 1448) >> 11;
        p[16] = tmp13 + z1;
        p[48] = tmp13 - z1;
        tmp10 = tmp4 + tmp5;
        tmp11 = tmp5 + tmp6;
        tmp12 = tmp6 + tmp7;
        z5 = ((tmp10 - tmp12) * 784) >> 11;
        z2 = ((tmp10 * 1108) >> 11) + z5;
        z4 = ((tmp12 * 2676) >> 11) + z5;
        z3 = (tmp11 * 1448) >> 11;
        z11 = tmp7 + z3;
        z13 = tmp7 - z3;
        p[40] = z13 + z2;
        p[24] = z13 - z2;
        p[8] = z11 + z4;
        p[56] = z11 - z4;
        p++;
    }
}

void fn_8029086C(s32 *data, s8 *in) {
    s32 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    s32 tmp10, tmp11, tmp12, tmp13;
    s32 z1, z2, z3, z4, z5, z11, z13;
    s32 *p = data;
    int i;

    for (i = 8; i > 0; i--) {
        tmp0 = (in[0] + in[7]) << 8;
        tmp7 = (in[0] - in[7]) << 8;
        tmp1 = (in[1] + in[6]) << 8;
        tmp6 = (in[1] - in[6]) << 8;
        tmp2 = (in[2] + in[5]) << 8;
        tmp5 = (in[2] - in[5]) << 8;
        tmp3 = (in[3] + in[4]) << 8;
        tmp4 = (in[3] - in[4]) << 8;
        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;
        p[0] = tmp10 + tmp11;
        p[4] = tmp10 - tmp11;
        z1 = ((tmp12 + tmp13) * 1448) >> 11;
        p[2] = tmp13 + z1;
        p[6] = tmp13 - z1;
        tmp10 = tmp4 + tmp5;
        tmp11 = tmp5 + tmp6;
        tmp12 = tmp6 + tmp7;
        z5 = ((tmp10 - tmp12) * 784) >> 11;
        z2 = ((tmp10 * 1108) >> 11) + z5;
        z4 = ((tmp12 * 2676) >> 11) + z5;
        z3 = (tmp11 * 1448) >> 11;
        z11 = tmp7 + z3;
        z13 = tmp7 - z3;
        p[5] = z13 + z2;
        p[3] = z13 - z2;
        p[1] = z11 + z4;
        p[7] = z11 - z4;
        p += 8;
        in += 8;
    }
    p = data;
    for (i = 8; i > 0; i--) {
        tmp0 = p[0] + p[56];
        tmp7 = p[0] - p[56];
        tmp1 = p[8] + p[48];
        tmp6 = p[8] - p[48];
        tmp2 = p[16] + p[40];
        tmp5 = p[16] - p[40];
        tmp3 = p[24] + p[32];
        tmp4 = p[24] - p[32];
        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;
        p[0] = tmp10 + tmp11;
        p[32] = tmp10 - tmp11;
        z1 = ((tmp12 + tmp13) * 1448) >> 11;
        p[16] = tmp13 + z1;
        p[48] = tmp13 - z1;
        tmp10 = tmp4 + tmp5;
        tmp11 = tmp5 + tmp6;
        tmp12 = tmp6 + tmp7;
        z5 = ((tmp10 - tmp12) * 784) >> 11;
        z2 = ((tmp10 * 1108) >> 11) + z5;
        z4 = ((tmp12 * 2676) >> 11) + z5;
        z3 = (tmp11 * 1448) >> 11;
        z11 = tmp7 + z3;
        z13 = tmp7 - z3;
        p[40] = z13 + z2;
        p[24] = z13 - z2;
        p[8] = z11 + z4;
        p[56] = z11 - z4;
        p++;
    }
}

void fn_80293258(s8 *out, BitBuf *bs, s32 limit);
int abs(int);
extern const u8 lbl_802AF340[];
#define MX(a, b) ((a) < (b) ? (b) : (a))
#define MXE(q, e) { u8 x_ = (e); if (q < x_) q = x_; }
#define ONE(L, K) \
    { if (K) bp++; \
    if (*bp != (L)) *--head = *bp | ((pos << 10) + 0x300); \
    else cnt += (L); } \
    pos++;
#define PASS(L) \
    { u16 v; for (p = head; p < end;) { \
        v = *p; \
        if (v == 0) { p++; continue; } \
        cnt++; \
        if ((u8)v != (L)) { p++; continue; } \
        switch (v & 0x300) { \
        case 0x000: \
            { u8 *hh_ = h; \
            pos = v >> 10; \
            *p = hh_[pos >> 4] + (((pos + 4) << 10) + 0x100); } \
            goto C##L; \
        case 0x100: { u16 k; \
            pos = v >> 10; \
            k = pos >> 2; \
            *p = g[k - 1] + ((pos << 10) + 0x200); \
            *end++ = g[k] + (((pos + 4) << 10) + 0x200); \
            *end++ = g[k + 1] + (((pos + 8) << 10) + 0x200); \
            *end++ = g[k + 2] + (((pos + 12) << 10) + 0x200); } \
            break; \
        case 0x200: \
            *p = 0; \
            pos = v >> 10; \
            p++; \
        C##L: \
            cnt += 4; \
            bp = bits + pos; ONE(L, 0) ONE(L, 1) ONE(L, 2) ONE(L, 3) \
            break; \
        case 0x300: \
            *p = 0; \
            cnt += (L); \
            p++; \
            break; \
        default: \
            p++; \
        } \
    } }
u32 fn_80290AAC(s16 *in) {
    u16 list[132];
    u8 bits[64];
    u8 g[16];
    u8 h[4];
    u16 *head, *end, *p;
    u8 *bp;
    u32 cnt;
    u8 mx, lvl, q;
#define pos v
    s32 i;
    mx = 0;
    for (i = 1; i < 64; i++) {
        u8 t = 32 - cntlzw_inline((u16)abs(in[lbl_802AF340[i]]));
        if (t > mx) mx = t;
        bits[i] = t;
    }
    for (i = 4; i < 64; i += 4) {
        q = bits[i];
        MXE(q, bits[i + 1]);
        MXE(q, bits[i + 2]);
        MXE(q, bits[i + 3]);
        g[i / 4 - 1] = q;
    }
    q = g[1]; MXE(q, g[2]); MXE(q, g[3]); MXE(q, g[4]); h[0] = q;
    q = g[6]; MXE(q, g[7]); MXE(q, g[8]); MXE(q, g[9]); h[1] = q;
    q = g[11]; MXE(q, g[12]); MXE(q, g[13]); MXE(q, g[14]); h[2] = q;
    cnt = 4;
    head = &list[68];
    head[0] = (h[0] > g[0] ? h[0] : g[0]) | (4 << 10);
    head[1] = (h[1] > g[5] ? h[1] : g[5]) | (24 << 10);
    head[2] = (h[2] > g[10] ? h[2] : g[10]) | (44 << 10);
    head[3] = bits[1] + 0x700;
    head[4] = bits[2] + 0xB00;
    head[5] = bits[3] + 0xF00;
    end = head + 6;
    for (lvl = mx; lvl > 1; lvl--) {
        PASS(lvl)
    }
    if (mx != 0) {
        PASS(1)
    }
    return cnt;
}
#undef MX
#undef MXE
#undef ONE
#undef PASS
#undef pos

static inline void bW(BitBuf *bs, u32 v, u32 n) {
    u32 bits = bs->bits;
    u32 buf;
    u32 nb;
    v &= lbl_802AB0C0[n];
    nb = bits + n;
    buf = bs->buf | (v << bits);
    bs->bits = nb;
    bs->buf = buf;
    if (nb > 31) {
        *bs->ptr = buf;
        bs->ptr++;
        bs->bits -= 32;
        if (bs->bits != 0) {
            bs->buf = v >> (n - bs->bits);
        } else {
            bs->buf = 0;
        }
    }
}
extern u32 lbl_802AB0CC[];
extern u32 lbl_802AB0D0[];
static inline void bWT(BitBuf *bs, u32 v, u32 n, u32 *tab) {
    u32 bits = bs->bits;
    u32 buf;
    u32 nb;
    v &= *tab;
    nb = bits + n;
    buf = bs->buf | (v << bits);
    bs->bits = nb;
    bs->buf = buf;
    if (nb > 31) {
        *bs->ptr = buf;
        bs->ptr++;
        bs->bits -= 32;
        if (bs->bits != 0) {
            bs->buf = v >> (n - bs->bits);
        } else {
            bs->buf = 0;
        }
    }
}
#define BWM(V, N) { \
    u32 n_ = (N); \
    u32 v_; \
    u32 bits_ = bs->bits; \
    u32 buf_; \
    u32 nb_; \
    v_ = (V) & lbl_802AB0C0[n_]; \
    nb_ = bits_ + n_; \
    buf_ = bs->buf | (v_ << bits_); \
    bs->buf = buf_; \
    bs->bits = nb_; \
    if (nb_ > 31) { \
        *bs->ptr = buf_; \
        bs->ptr++; \
        bs->bits -= 32; \
        if (bs->bits != 0) { \
            bs->buf = v_ >> (n_ - bs->bits); \
        } else { \
            bs->buf = 0; \
        } \
    } }
#define MXE(q, e) { u8 x_ = (e); if (q < x_) q = x_; }
#define PUT1(c) \
    { \
        if (c) bs->buf |= 1 << bs->bits; \
        if (++bs->bits == 32) { \
            *bs->ptr = bs->buf; \
            bs->bits = 0; \
            bs->buf = 0; \
            bs->ptr++; \
        } \
    }
#define ONE(K) \
    PUT1(((K) ? *++bp : *bp) != lvl); \
    { \
    u8 t_ = *bp; \
    if (t_ != lvl) { \
        *--head = *bp | ((pos << 10) + 0x300) | (t_ & 0x100); \
    } else { \
        BWM(av[pos], lvl - 1) \
        PUT1(sv[pos] < 0); \
    } \
    } \
    pos++;
void fn_802910C0(BitBuf *bs, s16 *in) {
    u16 list[132];
    u8 bits[64];
    u8 g[16];
    u16 av[64];
    s16 sv[64];
    u8 h[4];
    u16 *head, *end, *p;
    u8 *bp;
    u8 mx, lvl, q;
    u16 v, k;
#define pos v
    s32 i;
    for (i = 0; i < 64; i++) sv[i] = in[lbl_802AF340[i]];
    for (i = 0; i < 64; i++) av[i] = abs(sv[i]);
    mx = 0;
    for (i = 1; i < 64; i++) {
        u8 t = 32 - cntlzw_inline(av[i]);
        if (t > mx) mx = t;
        bits[i] = t;
    }
    for (i = 4; i < 64; i += 4) {
        q = bits[i];
        MXE(q, bits[i + 1]);
        MXE(q, bits[i + 2]);
        MXE(q, bits[i + 3]);
        g[i / 4 - 1] = q;
    }
    q = g[1]; MXE(q, g[2]); MXE(q, g[3]); MXE(q, g[4]); h[0] = q;
    q = g[6]; MXE(q, g[7]); MXE(q, g[8]); MXE(q, g[9]); h[1] = q;
    q = g[11]; MXE(q, g[12]); MXE(q, g[13]); MXE(q, g[14]); h[2] = q;
    bWT(bs, mx, 4, lbl_802AB0D0);
    head = &list[68];
    head[0] = (h[0] > g[0] ? h[0] : g[0]) | (4 << 10);
    head[1] = (h[1] > g[5] ? h[1] : g[5]) | (24 << 10);
    head[2] = (h[2] > g[10] ? h[2] : g[10]) | (44 << 10);
    head[3] = bits[1] + 0x700;
    head[4] = bits[2] + 0xB00;
    head[5] = bits[3] + 0xF00;
    end = head + 6;
    for (lvl = mx; lvl != 0; lvl--) {
        for (p = head; p < end;) {
            v = *p;
            if (v == 0) goto next;
            PUT1((u8)v == lvl);
            if ((u8)v != lvl) goto next;
            switch (v & 0x300) {
            case 0x000:
                pos = v >> 10;
                *p = h[pos >> 4] + (((pos + 4) << 10) + 0x100);
                goto C;
            case 0x100:
                pos = v >> 10;
                k = pos >> 2;
                *p = g[k - 1] + ((pos << 10) + 0x200);
                *end++ = g[k] + (((pos + 4) << 10) + 0x200);
                *end++ = g[k + 1] + (((pos + 8) << 10) + 0x200);
                *end++ = g[k + 2] + (((pos + 12) << 10) + 0x200);
                continue;
            case 0x200:
                *p = 0;
                pos = v >> 10;
                p++;
            C:
                bp = bits + pos;
                ONE(0) ONE(1) ONE(2) ONE(3)
                continue;
            case 0x300:
                pos = v >> 10;
                BWM(av[pos], lvl - 1)
                PUT1(sv[pos] < 0);
                *p = 0;
                break;
            }
        next:
            p++;
        }
    }
}
#undef MXE
#undef PUT1
#undef ONE
#undef BWM
#undef pos

#define GB1(q) (bb.bits != 0 ? ({ u32 w_ = bb.buf; bb.bits--; bb.buf = w_ >> 1; w_ & 1; }) \
                             : ({ u32 w_ = *bb.ptr; bb.ptr++; bb.bits = 31; bb.buf = w_ >> 1; w_ & 1; }))
#define GBN(n, r_) { u32 b_ = bb.bits; \
    if (b_ >= (n)) { \
        r_ = bb.buf & (0xFFFFFFFF >> (32 - (n))); \
        bb.bits = b_ - (n); \
        bb.buf >>= (n); \
    } else { \
        u32 *pp_ = bb.ptr; \
        u32 w_ = *pp_; \
        r_ = (bb.buf | (w_ << b_)) & (0xFFFFFFFF >> (32 - (n))); \
        bb.bits = b_ + 32 - (n); \
        bb.buf = w_ >> ((n) - b_); \
        bb.ptr = pp_ + 1; \
    } }
#define RQV(V) \
    if (GB1(q)) { \
        *--head = (c << 2) + 3; \
    } else { \
        V; \
    }
#define VAL { GBN(lvl, v) v |= mask; ((s16 *)list)[c + 68] = GB1(q) ? -v : v; }
#define VAL1 { ((s16 *)list)[c + 68] = GB1(q) ? -1 : 1; }
#define PASS(V) \
        p = head; \
        while (p < end) { \
            c = *p; \
            if (c != 0 && GB1(q)) { \
                switch (c & 3) { \
                case 0: \
                    c >>= 2; \
                    *p = ((c + 4) << 2) + 1; \
                    goto four##V; \
                case 1: \
                    c >>= 2; \
                    *p = (c << 2) + 2; \
                    *end++ = ((c + 4) << 2) + 2; \
                    *end++ = ((c + 8) << 2) + 2; \
                    *end++ = ((c + 12) << 2) + 2; \
                    continue; \
                case 2: \
                    *p = 0; \
                    c >>= 2; \
                    p++; \
                four##V: \
                    RQV(V) c++; \
                    RQV(V) c++; \
                    RQV(V) c++; \
                    RQV(V) \
                    continue; \
                case 3: \
                    c >>= 2; \
                    V; \
                    *p = 0; \
                    break; \
                } \
            } \
            p++; \
        }
void fn_80291B30(s16 *out, BitBuf *bs) {
    u8 list[136];
    s16 tmp[64];
    BitBuf bb;
    u8 *head, *end, *p;
    u32 q;
    u8 nb, c, lvl;
    s16 mask;
    s16 v;
    bb = *bs;
    tmp[1] = 0;
    memset(&tmp[2], 0, 124);
    {
        u32 bits = bb.bits;
        if (bits > 3) {
            nb = bb.buf & 15;
            bb.bits = bits - 4;
            bb.buf >>= 4;
        } else {
            u32 *pp = bb.ptr;
            u32 w = *pp;
            nb = (bb.buf | (w << bits)) & 15;
            bb.bits = bits + 32 - 4;
            bb.ptr = pp + 1;
            bb.buf = w >> (4 - bits);
        }
    }
    head = list + 68;
    head[0] = 0x10;
    head[1] = 0x60;
    head[2] = 0xB0;
    head[3] = 7;
    head[4] = 0xB;
    head[5] = 0xF;
    mask = (s16)(1 << (nb - 1));
    end = head + 6;
    for (lvl = nb; lvl > 1; mask >>= 1) {
        lvl--;
        PASS(VAL)
    }
    if (nb != 0) {
        u8 e;
#define c e
        PASS(VAL1)
#undef c
    }
    *bs = bb;
    out[1] = tmp[1];
#define CP(i, j) ((u32 *)out)[i] = ((u32 *)tmp)[j];
    CP(1, 2) CP(2, 4) CP(3, 6) CP(4, 1) CP(5, 3) CP(6, 5) CP(7, 7) CP(8, 12)
    CP(9, 22) CP(10, 8) CP(11, 10) CP(12, 13) CP(13, 23) CP(14, 9) CP(15, 11) CP(16, 14)
    CP(17, 16) CP(18, 24) CP(19, 26) CP(20, 15) CP(21, 17) CP(22, 25) CP(23, 27) CP(24, 18)
    CP(25, 20) CP(26, 28) CP(27, 30) CP(28, 19) CP(29, 21) CP(30, 29) CP(31, 31)
#undef CP
}
#undef GB1
#undef GBN
#undef RQV
#undef VAL
#undef VAL1
#undef PASS

#define MXE(q, e) { u8 x_ = (e); if (q < x_) q = x_; }
#define PUT1(c) \
    { \
        if (c) bs->buf |= 1 << bs->bits; \
        if (++bs->bits == 32) { \
            *bs->ptr = bs->buf; \
            bs->bits = 0; \
            bs->buf = 0; \
            bs->ptr++; \
        } \
    }
#define ONE(K) \
    PUT1(((K) ? *++bp : *bp) != lvl); \
    { \
    u8 t_ = *bp; \
    if (t_ != lvl) { \
        *--head = *bp | ((pos << 10) + 0x300) | (t_ & 0x100); \
    } else { \
        nzl[nz++] = av[pos]; \
        PUT1(sv[pos] & 0x80); \
    } \
    } \
    pos++;
s32 fn_80292974(BitBuf *bs, u8 *in) {
    u16 list[132];
    u8 bits[64];
    u8 g[16];
    u8 sv[64];
    u8 av[64];
    u8 nzl[64];
    u8 h[4];
    u16 *head, *end, *p;
    u8 *bp;
    u8 mx, lvl, q;
    u16 v, k;
#define pos v
    s16 mask;
    s32 i, nz;
    for (i = 0; i < 64; i++) sv[i] = in[lbl_802AF340[i]];
    for (i = 0; i < 64; i++) av[i] = abs((s8)sv[i]);
    mx = 0;
    for (i = 0; i < 64; i++) {
        u8 t = 32 - cntlzw_inline(av[i]);
        if (t > mx) mx = t;
        bits[i] = t;
    }
    if (mx == 0) return 0;
    for (i = 0; i < 64; i += 4) {
        q = bits[i];
        MXE(q, bits[i + 1]);
        MXE(q, bits[i + 2]);
        MXE(q, bits[i + 3]);
        g[i / 4] = q;
    }
    q = g[2]; MXE(q, g[3]); MXE(q, g[4]); MXE(q, g[5]); h[0] = q;
    q = g[7]; MXE(q, g[8]); MXE(q, g[9]); MXE(q, g[10]); h[1] = q;
    q = g[12]; MXE(q, g[13]); MXE(q, g[14]); MXE(q, g[15]); h[2] = q;
    bWT(bs, mx - 1, 3, lbl_802AB0CC);
    head = &list[68];
    head[0] = (h[0] > g[1] ? h[0] : g[1]) | (4 << 10);
    head[1] = (h[1] > g[6] ? h[1] : g[6]) | (24 << 10);
    head[2] = (h[2] > g[11] ? h[2] : g[11]) | (44 << 10);
    head[3] = g[0] + 0x200;
    end = head + 4;
    nz = 0;
    mask = 1 << (mx - 1);
    for (lvl = mx; lvl != 0; mask >>= 1, lvl--) {
        for (i = 0; i < nz;) {
            PUT1(nzl[i++] & mask);
        }
        for (p = head; p < end;) {
            v = *p;
            if (v == 0) goto next;
            PUT1((u8)v == lvl);
            if ((u8)v != lvl) goto next;
            switch (v & 0x300) {
            case 0x000:
                pos = v >> 10;
                *p = h[pos >> 4] + (((pos + 4) << 10) + 0x100);
                goto C;
            case 0x100:
                pos = v >> 10;
                k = pos >> 2;
                *p = g[k] + ((pos << 10) + 0x200);
                *end++ = g[k + 1] + (((pos + 4) << 10) + 0x200);
                *end++ = g[k + 2] + (((pos + 8) << 10) + 0x200);
                *end++ = g[k + 3] + (((pos + 12) << 10) + 0x200);
                continue;
            case 0x200:
                *p = 0;
                pos = v >> 10;
                p++;
            C:
                bp = bits + pos;
                ONE(0) ONE(1) ONE(2) ONE(3)
                continue;
            case 0x300:
                pos = v >> 10;
                nzl[nz++] = av[pos];
                PUT1(sv[pos] & 0x80);
                *p = 0;
                break;
            }
        next:
            p++;
        }
    }
    return 1;
}
#undef MXE
#undef PUT1
#undef ONE

#define GB1(q) (bb.bits != 0 ? ({ u32 w_ = bb.buf; bb.bits--; bb.buf = w_ >> 1; w_ & 1; }) \
                             : ({ u32 w_ = *bb.ptr; bb.ptr++; bb.bits = 31; bb.buf = w_ >> 1; w_ & 1; }))
#define RQ(K) \
    if (GB1(q)) { \
        *--head = (c << 2) + 3; \
    } else { \
        nzl[nz++] = c; \
        out[c] = GB1(q) ? -mask : mask; \
        if (n++ == limit) goto done; \
    }
void fn_80293258(s8 *out, BitBuf *bs, s32 limit) {
    u8 list[136];
    u8 nzl[64];
    BitBuf bb;
    u8 *head, *end, *p;
    u32 q;
    u8 nb, c, lvl;
    s32 mask;
    s32 nz, i, n;
    bb = *bs;
    n = 0;
    memset(out, 0, 64);
    {
        u32 bits = bb.bits;
        if (bits > 2) {
            c = bb.buf & 7;
            bb.bits = bits - 3;
            bb.buf >>= 3;
        } else {
            u32 *pp = bb.ptr;
            u32 w = *pp;
            c = (bb.buf | (w << bits)) & 7;
            bb.bits = bits + 32 - 3;
            bb.ptr = pp + 1;
            bb.buf = w >> (3 - bits);
        }
    }
    c = c + 1;
    head = list + 68;
    head[0] = 0x10;
    head[1] = 0x60;
    head[2] = 0xB0;
    head[3] = 2;
    mask = (s8)(1 << (c - 1));
    end = head + 4;
    nz = 0;
    for (lvl = c; lvl != 0; lvl--, mask >>= 1) {
        for (i = 0; i < nz; i++) {
            if (GB1(q)) {
                out[nzl[i]] += out[nzl[i]] < 0 ? -mask : mask;
                if (n++ == limit) goto done;
            }
        }
        p = head;
        while (p < end) {
            c = *p;
            if (c != 0 && GB1(q)) {
                switch (c & 3) {
                case 0:
                    c >>= 2;
                    *p = ((c + 4) << 2) + 1;
                    goto four;
                case 1:
                    c >>= 2;
                    *p = (c << 2) + 2;
                    *end++ = ((c + 4) << 2) + 2;
                    *end++ = ((c + 8) << 2) + 2;
                    *end++ = ((c + 12) << 2) + 2;
                    continue;
                case 2:
                    *p = 0;
                    c >>= 2;
                    p++;
                four:
                    RQ(0) c++;
                    RQ(1) c++;
                    RQ(2) c++;
                    RQ(3)
                    continue;
                case 3:
                    c >>= 2;
                    nzl[nz++] = c;
                    out[c] = GB1(q) ? -mask : mask;
                    if (n++ == limit) goto done;
                    *p = 0;
                    break;
                }
            }
            p++;
        }
    }
done:
    *bs = bb;
}

void fn_80293964(u16 *dst) {
    u16 t[32];
    u16 *d;
    u16 a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16;
    d = dst;
    ((void (*)(u16 *))fn_80293258)(t);
    a0 = t[0]; a1 = t[2]; a2 = t[4]; a3 = t[6];
    a4 = t[1]; a5 = t[3]; a6 = t[5]; a7 = t[7];
    a8 = t[12]; a9 = t[22]; a10 = t[8]; a11 = t[10];
    a12 = t[13]; a13 = t[23]; a14 = t[9]; a15 = t[11];
    a16 = t[14];
    d[0] = a0; d[1] = a1; d[2] = a2; d[3] = a3;
    d[4] = a4; d[5] = a5; d[6] = a6; d[7] = a7;
    d[8] = a8; d[9] = a9; d[10] = a10; d[11] = a11;
    d[12] = a12; d[13] = a13; d[14] = a14; d[15] = a15;
    d[16] = a16;
    a0 = t[16]; a1 = t[24]; a2 = t[26]; a3 = t[15];
    a4 = t[17]; a5 = t[25]; a6 = t[27]; a7 = t[18];
    a8 = t[20]; a9 = t[28]; a10 = t[30]; a11 = t[19];
    a12 = t[21]; a13 = t[29]; a14 = t[31];
    d[17] = a0; d[18] = a1; d[19] = a2; d[20] = a3;
    d[21] = a4; d[22] = a5; d[23] = a6; d[24] = a7;
    d[25] = a8; d[26] = a9; d[27] = a10; d[28] = a11;
    d[29] = a12; d[30] = a13; d[31] = a14;
}
void fn_80293A94(u8 *dst, s32 pitch, s32 a, s32 b, u8 *add) {
    u8 t[64];
    u8 *d = dst;
    ((void (*)(u8 *, s32, s32))fn_80293258)(t, a, b);
    d[0] = t[0] + add[0];
    d[1] = t[1] + add[1];
    d[2] = t[4] + add[2];
    d[3] = t[5] + add[3];
    d[4] = t[8] + add[4];
    d[5] = t[9] + add[5];
    d[6] = t[12] + add[6];
    d[7] = t[13] + add[7];
    d += pitch;
    d[0] = t[2] + add[8];
    d[1] = t[3] + add[9];
    d[2] = t[6] + add[10];
    d[3] = t[7] + add[11];
    d[4] = t[10] + add[12];
    d[5] = t[11] + add[13];
    d[6] = t[14] + add[14];
    d[7] = t[15] + add[15];
    d += pitch;
    d[0] = t[24] + add[16];
    d[1] = t[25] + add[17];
    d[2] = t[44] + add[18];
    d[3] = t[45] + add[19];
    d[4] = t[16] + add[20];
    d[5] = t[17] + add[21];
    d[6] = t[20] + add[22];
    d[7] = t[21] + add[23];
    d += pitch;
    d[0] = t[26] + add[24];
    d[1] = t[27] + add[25];
    d[2] = t[46] + add[26];
    d[3] = t[47] + add[27];
    d[4] = t[18] + add[28];
    d[5] = t[19] + add[29];
    d[6] = t[22] + add[30];
    d[7] = t[23] + add[31];
    d += pitch;
    d[0] = t[28] + add[32];
    d[1] = t[29] + add[33];
    d[2] = t[32] + add[34];
    d[3] = t[33] + add[35];
    d[4] = t[48] + add[36];
    d[5] = t[49] + add[37];
    d[6] = t[52] + add[38];
    d[7] = t[53] + add[39];
    d += pitch;
    d[0] = t[30] + add[40];
    d[1] = t[31] + add[41];
    d[2] = t[34] + add[42];
    d[3] = t[35] + add[43];
    d[4] = t[50] + add[44];
    d[5] = t[51] + add[45];
    d[6] = t[54] + add[46];
    d[7] = t[55] + add[47];
    d += pitch;
    d[0] = t[36] + add[48];
    d[1] = t[37] + add[49];
    d[2] = t[40] + add[50];
    d[3] = t[41] + add[51];
    d[4] = t[56] + add[52];
    d[5] = t[57] + add[53];
    d[6] = t[60] + add[54];
    d[7] = t[61] + add[55];
    d += pitch;
    d[0] = t[38] + add[56];
    d[1] = t[39] + add[57];
    d[2] = t[42] + add[58];
    d[3] = t[43] + add[59];
    d[4] = t[58] + add[60];
    d[5] = t[59] + add[61];
    d[6] = t[62] + add[62];
    d[7] = t[63] + add[63];
}

/* .rodata 0x802AF340-0x802AF7A0 (tables used by the neighbours too) */
const u8 lbl_802AF340[0x60] = {
    0x00, 0x01, 0x08, 0x09, 0x02, 0x03, 0x0A, 0x0B, 0x04, 0x05, 0x0C, 0x0D, 0x06, 0x07, 0x0E, 0x0F,
    0x14, 0x15, 0x1C, 0x1D, 0x16, 0x17, 0x1E, 0x1F, 0x10, 0x11, 0x18, 0x19, 0x20, 0x21, 0x28, 0x29,
    0x22, 0x23, 0x2A, 0x2B, 0x30, 0x31, 0x38, 0x39, 0x32, 0x33, 0x3A, 0x3B, 0x12, 0x13, 0x1A, 0x1B,
    0x24, 0x25, 0x2C, 0x2D, 0x26, 0x27, 0x2E, 0x2F, 0x34, 0x35, 0x3C, 0x3D, 0x36, 0x37, 0x3E, 0x3F,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const u32 lbl_802AF3A0[256] = {
    0x00081018, 0x20283038, 0x39312921, 0x19110901, 0x020A121A, 0x222A323A,
    0x3B332B23, 0x1B130B03, 0x040C141C, 0x242C343C, 0x3D352D25, 0x1D150D05,
    0x060E161E, 0x262E363E, 0x3F372F27, 0x1F170F07, 0x3B3A3938, 0x30313233,
    0x2B2A2928, 0x20212223, 0x1B1A1918, 0x10111213, 0x0B0A0908, 0x00010203,
    0x04050607, 0x0F0E0D0C, 0x14151617, 0x1F1E1D1C, 0x24252627, 0x2F2E2D2C,
    0x34353637, 0x3F3E3D3C, 0x1911121A, 0x1B130B03, 0x020A0901, 0x00081018,
    0x20283038, 0x3931292A, 0x323A3B33, 0x2B232221, 0x1D15161E, 0x1F170F07,
    0x060E0D05, 0x040C141C, 0x242C343C, 0x3D352D2E, 0x363E3F37, 0x2F272625,
    0x030B020A, 0x01090008, 0x10181119, 0x121A131B, 0x232B222A, 0x21292028,
    0x30383139, 0x323A333B, 0x3C343D35, 0x3E363F37, 0x2F272E26, 0x2D252C24,
    0x1C141D15, 0x1E161F17, 0x0F070E06, 0x0D050C04, 0x18191011, 0x08090001,
    0x02030A0B, 0x12131A1B, 0x1C1D1415, 0x0C0D0405, 0x06070E0F, 0x16171E1F,
    0x27262F2E, 0x37363F3E, 0x3D3C3534, 0x2D2C2524, 0x23222B2A, 0x33323B3A,
    0x39383130, 0x29282120, 0x00010203, 0x08090A0B, 0x10111213, 0x18191A1B,
    0x20212223, 0x28292A2B, 0x30313233, 0x38393A3B, 0x04050607, 0x0C0D0E0F,
    0x14151617, 0x1C1D1E1F, 0x24252627, 0x2C2D2E2F, 0x34353637, 0x3C3D3E3F,
    0x06070F0E, 0x0D050C04, 0x030B020A, 0x09010008, 0x10181119, 0x121A131B,
    0x141C151D, 0x161E171F, 0x272F262E, 0x252D242C, 0x232B222A, 0x21292028,
    0x31303839, 0x3A323B33, 0x3C343D35, 0x36373F3E, 0x00010203, 0x04050607,
    0x0F0E0D0C, 0x0B0A0908, 0x10111213, 0x14151617, 0x1F1E1D1C, 0x1B1A1918,
    0x20212223, 0x24252627, 0x2F2E2D2C, 0x2B2A2928, 0x30313233, 0x34353637,
    0x3F3E3D3C, 0x3B3A3938, 0x00080901, 0x02030B0A, 0x12131B1A, 0x19111018,
    0x20282921, 0x22232B2A, 0x32313038, 0x393A3B33, 0x343C3D3E, 0x3F373635,
    0x2D2C2425, 0x262E2F27, 0x1F17161E, 0x1D1C1415, 0x0D0C0405, 0x060E0F07,
    0x18191011, 0x08090001, 0x02030A0B, 0x12131A1B, 0x1C1D1415, 0x0C0D0405,
    0x06070E0F, 0x16171E1F, 0x26272E2F, 0x36373E3F, 0x3C3D3435, 0x2C2D2425,
    0x22232A2B, 0x32333A3B, 0x38393031, 0x28292021, 0x00080109, 0x020A030B,
    0x131B121A, 0x11191018, 0x20282129, 0x222A232B, 0x333B323A, 0x31393038,
    0x3C343D35, 0x3E363F37, 0x2F272E26, 0x2D252C24, 0x1F171E16, 0x1D151C14,
    0x0C040D05, 0x0E060F07, 0x00081018, 0x191A1B13, 0x0B030201, 0x0911120A,
    0x040C141C, 0x1D1E1F17, 0x0F070605, 0x0D15160E, 0x242C343C, 0x3D3E3F37,
    0x2F272625, 0x2D35362E, 0x20283038, 0x393A3B33, 0x2B232221, 0x2931322A,
    0x00080901, 0x02030B0A, 0x131B1A12, 0x11101819, 0x21202829, 0x2A22232B,
    0x333B3A32, 0x31393830, 0x343C3D35, 0x363E3F37, 0x2F27262E, 0x2D2C2425,
    0x1D1C1415, 0x161E1F17, 0x0E0F0706, 0x050D0C04, 0x18100800, 0x0102030B,
    0x131B1A19, 0x110A0912, 0x1C140C04, 0x0506070F, 0x171F1E1D, 0x150E0D16,
    0x3C342C24, 0x2526272F, 0x373F3E3D, 0x352E2D36, 0x38302820, 0x2122232B,
    0x333B3A39, 0x312A2932, 0x00080901, 0x020A1211, 0x1018191A, 0x1B130B03,
    0x07060E0F, 0x1716150D, 0x05040C14, 0x1C1D1E1F, 0x3F3E3637, 0x2F2E2D35,
    0x3D3C342C, 0x24252627, 0x38303139, 0x3A322A29, 0x28202122, 0x232B333B,
    0x00010809, 0x10111819, 0x20212829, 0x30313839, 0x3A3B3233, 0x2A2B2223,
    0x1A1B1213, 0x0A0B0203, 0x04050C0D, 0x14151C1D, 0x24252C2D, 0x34353C3D,
    0x3E3F3637, 0x2E2F2627, 0x1E1F1617, 0x0E0F0607,
};
