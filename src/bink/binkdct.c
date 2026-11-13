/* RAD Bink: 0x8028F9D8-0x80290650 */
#include "bink_common.h"

void wAE_F9D8(u8 *out, s32 pitch, s16 *in, s32 *q) asm("fn_8028F9D8");
void wAE_F9D8(u8 *out, s32 pitch, s16 *in_, s32 *q_) {
    s32 *q = q_;
    s16 *in = in_;

    s32 tmp[8];
    s32 ws[64];
    s32 *w;
    s32 tmp10, tmp11, tmp12, tmp13;
    s32 z5, z10, z11, z12, z13;
    s32 d0, d1, d2, d3, d4, d5, d6, d7;
    int i;
    u8 *o;

    o = out;
    w = ws;
    for (i = 8; i > 0; i--) {
        if ((in[8] | in[16] | in[24] | in[32] | in[40] | in[48] | in[56]) == 0) {
            s32 dc = (in[0] * q[0]) >> 11;
            in++;
            q++;
            w[0] = dc;
            w[8] = dc;
            w[16] = dc;
            w[24] = dc;
            w[32] = dc;
            w[40] = dc;
            w[48] = dc;
            w[56] = dc;
        } else {
            d0 = (in[0] * q[0]) >> 11;
            d1 = (in[8] * q[8]) >> 11;
            d2 = (in[16] * q[16]) >> 11;
            d3 = (in[24] * q[24]) >> 11;
            d4 = (in[32] * q[32]) >> 11;
            d5 = (in[40] * q[40]) >> 11;
            d6 = (in[48] * q[48]) >> 11;
            d7 = (in[56] * q[56]) >> 11;
            in++;
            q++;

            tmp10 = d0 + d4;
            tmp11 = d0 - d4;
            tmp13 = d2 + d6;
            tmp12 = (((d2 - d6) * 2896) >> 11) - tmp13;
            tmp[0] = tmp10 + tmp13;
            tmp[3] = tmp10 - tmp13;
            tmp[1] = tmp11 + tmp12;
            tmp[2] = tmp11 - tmp12;

            z13 = d5 + d3;
            z10 = d5 - d3;
            z11 = d1 + d7;
            z12 = d1 - d7;
            tmp[7] = z11 + z13;
            tmp11 = ((z11 - z13) * 2896) >> 11;
            z5 = ((z10 + z12) * 3784) >> 11;
            tmp10 = ((z12 * 2217) >> 11) - z5;
            tmp12 = ((z10 * -5352) >> 11) + z5;
            tmp[6] = tmp12 - tmp[7];
            tmp[5] = tmp11 - tmp[6];
            tmp[4] = tmp10 + tmp[5];

            w[0] = tmp[0] + tmp[7];
            w[56] = tmp[0] - tmp[7];
            w[8] = tmp[1] + tmp[6];
            w[48] = tmp[1] - tmp[6];
            w[16] = tmp[2] + tmp[5];
            w[40] = tmp[2] - tmp[5];
            w[32] = tmp[3] + tmp[4];
            w[24] = tmp[3] - tmp[4];
        }
        w++;
    }
    w = ws;
    o = out;
    for (i = 8; i > 0; i--) {
        tmp10 = w[0] + w[4];
        tmp11 = w[0] - w[4];
        tmp13 = w[2] + w[6];
        tmp12 = (((w[2] - w[6]) * 2896) >> 11) - tmp13;
        tmp[0] = tmp10 + tmp13;
        tmp[3] = tmp10 - tmp13;
        tmp[1] = tmp11 + tmp12;
        tmp[2] = tmp11 - tmp12;

        z13 = w[5] + w[3];
        z10 = w[5] - w[3];
        z11 = w[1] + w[7];
        z12 = w[1] - w[7];
        tmp[7] = z11 + z13;
        tmp11 = ((z11 - z13) * 2896) >> 11;
        z5 = ((z10 + z12) * 3784) >> 11;
        tmp10 = ((z12 * 2217) >> 11) - z5;
        tmp12 = ((z10 * -5352) >> 11) + z5;
        tmp[6] = tmp12 - tmp[7];
        tmp[5] = tmp11 - tmp[6];
        tmp[4] = tmp10 + tmp[5];

        o[0] = (tmp[0] + tmp[7] + 127) >> 8;
        o[7] = (tmp[0] - tmp[7] + 127) >> 8;
        o[1] = (tmp[1] + tmp[6] + 127) >> 8;
        o[6] = (tmp[1] - tmp[6] + 127) >> 8;
        o[2] = (tmp[2] + tmp[5] + 127) >> 8;
        o[5] = (tmp[2] - tmp[5] + 127) >> 8;
        o[4] = (tmp[3] + tmp[4] + 127) >> 8;
        o[3] = (tmp[3] - tmp[4] + 127) >> 8;
        w += 8;
        o += pitch;
    }
}

void fn_80290190(s32 n, f32 *a, s32 nc, s32 idx) {
    fn_8028F9D8(n, a, nc, lbl_802AD300[idx]);
}

void fn_802901C0(void *a, void *b, void *c, s32 d) {
    fn_8028F9D8(a, b, c, lbl_802AB2C0 + d * 256);
}

void fn_802901F0(void *a, void *b, void *c, s32 d) {
    fn_8028FDB4(a, b, c, lbl_802AB2C0 + d * 256);
}

/* wBA draft: fn_8028FDB4 (~166 diff lines vs target, size matches; regalloc). */
void wBA_FDB4(u8 *out, s32 pitch, s16 *in, s32 *q) asm("fn_8028FDB4");
void wBA_FDB4(u8 *out, s32 pitch, s16 *in_, s32 *q_) {
    s32 *q = q_;
    s16 *in = in_;

    s32 tmp[8];
    s32 ws[64];
    s32 *w;
    s32 *p;
    s32 tmp10, tmp11, tmp12, tmp13;
    s32 z5, z10, z11, z12, z13;
    s32 d0, d1, d2, d3, d4, d5, d6, d7;
    int i;
    u32 *o0, *o1;
    s32 pitch2;

    pitch2 = pitch + pitch;
    o1 = (u32 *)(out + pitch);
    w = ws;
    for (i = 8; i > 0; i--) {
        if ((in[8] | in[16] | in[24] | in[32] | in[40] | in[48] | in[56]) == 0) {
            s32 dc = (in[0] * q[0]) >> 11;
            in++;
            q++;
            w[0] = dc;
            w[8] = dc;
            w[16] = dc;
            w[24] = dc;
            w[32] = dc;
            w[40] = dc;
            w[48] = dc;
            w[56] = dc;
        } else {
            s32 tmp11;
            s32 tmp12;
            s32 z10;
            d0 = (in[0] * q[0]) >> 11;
            d1 = (in[8] * q[8]) >> 11;
            d2 = (in[16] * q[16]) >> 11;
            d3 = (in[24] * q[24]) >> 11;
            d4 = (in[32] * q[32]) >> 11;
            d5 = (in[40] * q[40]) >> 11;
            d6 = (in[48] * q[48]) >> 11;
            d7 = (in[56] * q[56]) >> 11;
            q++;
            in++;

            tmp10 = d0 + d4;
            tmp11 = d0 - d4;
            tmp13 = d2 + d6;
            tmp12 = (((d2 - d6) * 2896) >> 11) - tmp13;
            tmp[0] = tmp10 + tmp13;
            tmp[3] = tmp10 - tmp13;
            tmp[1] = tmp11 + tmp12;
            tmp[2] = tmp11 - tmp12;

            z13 = d5 + d3;
            z10 = d5 - d3;
            z11 = d1 + d7;
            z12 = d1 - d7;
            tmp[7] = z11 + z13;
            z5 = ((z10 + z12) * 3784) >> 11;
            tmp10 = ((z12 * 2217) >> 11) - z5;
            tmp11 = ((z11 - z13) * 2896) >> 11;
            tmp12 = ((z10 * -5352) >> 11) + z5;
            tmp[6] = tmp12 - tmp[7];
            tmp[5] = tmp11 - tmp[6];
            tmp[4] = tmp10 + tmp[5];

            w[0] = tmp[0] + tmp[7];
            w[56] = tmp[0] - tmp[7];
            w[8] = tmp[1] + tmp[6];
            w[48] = tmp[1] - tmp[6];
            w[16] = tmp[2] + tmp[5];
            w[40] = tmp[2] - tmp[5];
            w[32] = tmp[3] + tmp[4];
            w[24] = tmp[3] - tmp[4];
        }
        w++;
    }
    p = ws;
    o0 = (u32 *)out;
    for (i = 8; i > 0; i--) {
        tmp10 = p[0] + p[4];
        tmp11 = p[0] - p[4];
        tmp13 = p[2] + p[6];
        tmp12 = (((p[2] - p[6]) * 2896) >> 11) - tmp13;
        tmp[0] = tmp10 + tmp13;
        tmp[3] = tmp10 - tmp13;
        tmp[1] = tmp11 + tmp12;
        tmp[2] = tmp11 - tmp12;

        z10 = p[5] - p[3];
        z13 = p[5] + p[3];
        z11 = p[1] + p[7];
        z12 = p[1] - p[7];
        tmp[7] = z11 + z13;
        tmp11 = ((z11 - z13) * 2896) >> 11;
        z5 = ((z10 + z12) * 3784) >> 11;
        tmp10 = ((z12 * 2217) >> 11) - z5;
        tmp12 = ((z10 * -5352) >> 11) + z5;
        tmp[6] = tmp12 - tmp[7];
        tmp[5] = tmp11 - tmp[6];
        tmp[4] = tmp10 + tmp[5];

        {
            u32 a, b, c, d;
            s32 v0, v1, v2, v3, v4, v5, v6, v7;
            v5 = (tmp[2] - tmp[5] + 127) >> 8;
            v0 = (tmp[0] + tmp[7] + 127) >> 8;
            v7 = (tmp[0] - tmp[7] + 127) >> 8;
            v1 = (tmp[1] + tmp[6] + 127) >> 8;
            v6 = (tmp[1] - tmp[6] + 127) >> 8;
            v2 = (tmp[2] + tmp[5] + 127) >> 8;
            v4 = (tmp[3] + tmp[4] + 127) >> 8;
            v3 = (tmp[3] - tmp[4] + 127) >> 8;
            b = ((v2 & 0xFF) << 16) | (v3 & 0xFF);
            c = ((v4 & 0xFF) << 16) | (v5 & 0xFF);
            d = ((v6 & 0xFF) << 16) | (v7 & 0xFF);
            a = ((v0 & 0xFF) << 16) | (v1 & 0xFF);
            c |= c << 8;
            a |= a << 8;
            d |= d << 8;
            b |= b << 8;
            o0[0] = a; o0[1] = b; o0[2] = c; o0[3] = d;
            o1[0] = a; o1[1] = b; o1[2] = c; o1[3] = d;
        }
        p += 8;
        o0 = (u32 *)((u8 *)o0 + pitch2);
        o1 = (u32 *)((u8 *)o1 + pitch2);
    }
}

void fn_80290220(u8 *out, s32 pitch, s16 *in, s32 idx, u8 *pred) {
    s32 *q = (s32 *)lbl_802AD300[idx];

    s32 tmp[8];
    s32 ws[64];
    s32 *w;
    s32 tmp10, tmp11, tmp12, tmp13;
    s32 z5, z10, z11, z12, z13;
    s32 d0, d1, d2, d3, d4, d5, d6, d7;
    int i;
    u8 *o;

    o = out;
    w = ws;
    for (i = 8; i > 0; i--) {
        if ((in[8] | in[16] | in[24] | in[32] | in[40] | in[48] | in[56]) == 0) {
            s32 dc = (in[0] * q[0]) >> 11;
            in++;
            q++;
            w[0] = dc;
            w[8] = dc;
            w[16] = dc;
            w[24] = dc;
            w[32] = dc;
            w[40] = dc;
            w[48] = dc;
            w[56] = dc;
        } else {
            d0 = (in[0] * q[0]) >> 11;
            d1 = (in[8] * q[8]) >> 11;
            d2 = (in[16] * q[16]) >> 11;
            d3 = (in[24] * q[24]) >> 11;
            d4 = (in[32] * q[32]) >> 11;
            d5 = (in[40] * q[40]) >> 11;
            d6 = (in[48] * q[48]) >> 11;
            d7 = (in[56] * q[56]) >> 11;
            in++;
            q++;

            tmp10 = d0 + d4;
            tmp11 = d0 - d4;
            tmp13 = d2 + d6;
            tmp12 = (((d2 - d6) * 2896) >> 11) - tmp13;
            tmp[0] = tmp10 + tmp13;
            tmp[3] = tmp10 - tmp13;
            tmp[1] = tmp11 + tmp12;
            tmp[2] = tmp11 - tmp12;

            z13 = d5 + d3;
            z10 = d5 - d3;
            z11 = d1 + d7;
            z12 = d1 - d7;
            tmp[7] = z11 + z13;
            tmp11 = ((z11 - z13) * 2896) >> 11;
            z5 = ((z10 + z12) * 3784) >> 11;
            tmp10 = ((z12 * 2217) >> 11) - z5;
            tmp12 = ((z10 * -5352) >> 11) + z5;
            tmp[6] = tmp12 - tmp[7];
            tmp[5] = tmp11 - tmp[6];
            tmp[4] = tmp10 + tmp[5];

            w[0] = tmp[0] + tmp[7];
            w[56] = tmp[0] - tmp[7];
            w[8] = tmp[1] + tmp[6];
            w[48] = tmp[1] - tmp[6];
            w[16] = tmp[2] + tmp[5];
            w[40] = tmp[2] - tmp[5];
            w[32] = tmp[3] + tmp[4];
            w[24] = tmp[3] - tmp[4];
        }
        w++;
    }
    w = ws;
    o = out;
    for (i = 8; i > 0; i--) {
        tmp10 = w[0] + w[4];
        tmp11 = w[0] - w[4];
        tmp13 = w[2] + w[6];
        tmp12 = (((w[2] - w[6]) * 2896) >> 11) - tmp13;
        tmp[0] = tmp10 + tmp13;
        tmp[3] = tmp10 - tmp13;
        tmp[1] = tmp11 + tmp12;
        tmp[2] = tmp11 - tmp12;

        z13 = w[5] + w[3];
        z10 = w[5] - w[3];
        z11 = w[1] + w[7];
        z12 = w[1] - w[7];
        tmp[7] = z11 + z13;
        tmp11 = ((z11 - z13) * 2896) >> 11;
        z5 = ((z10 + z12) * 3784) >> 11;
        tmp10 = ((z12 * 2217) >> 11) - z5;
        tmp12 = ((z10 * -5352) >> 11) + z5;
        tmp[6] = tmp12 - tmp[7];
        tmp[5] = tmp11 - tmp[6];
        tmp[4] = tmp10 + tmp[5];

        o[0] = pred[0] + ((tmp[0] + tmp[7] + 127) >> 8);
        o[7] = pred[7] + ((tmp[0] - tmp[7] + 127) >> 8);
        o[1] = pred[1] + ((tmp[1] + tmp[6] + 127) >> 8);
        o[6] = pred[6] + ((tmp[1] - tmp[6] + 127) >> 8);
        o[2] = pred[2] + ((tmp[2] + tmp[5] + 127) >> 8);
        o[5] = pred[5] + ((tmp[2] - tmp[5] + 127) >> 8);
        o[4] = pred[4] + ((tmp[3] + tmp[4] + 127) >> 8);
        o[3] = pred[3] + ((tmp[3] - tmp[4] + 127) >> 8);
        w += 8;
        pred += 8;
        o += pitch;
    }
}
