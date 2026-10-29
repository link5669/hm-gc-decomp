/* Functions from 0x8014EB30 to 0x8014F264, found by decomp-toolkit. */
#include "common.h"

extern "C" {
extern f32 lbl_8036453C;
extern f32 lbl_80364544;

extern f32 lbl_80364540;
extern s32 lbl_8035ACB8;

static inline void MtxMultVec4(f32 (*__restrict m)[4], f32 *__restrict v, f32 *__restrict out) {
    out[0] = v[0] * m[0][0];
    out[1] = v[0] * m[1][0];
    out[2] = v[0] * m[2][0];
    out[3] = v[0] * m[3][0];
    out[0] = v[1] * m[0][1] + out[0];
    out[1] = v[1] * m[1][1] + out[1];
    out[2] = v[1] * m[2][1] + out[2];
    out[3] = v[1] * m[3][1] + out[3];
    out[0] = v[2] * m[0][2] + out[0];
    out[1] = v[2] * m[1][2] + out[1];
    out[2] = v[2] * m[2][2] + out[2];
    out[3] = v[2] * m[3][2] + out[3];
    out[0] = out[0] + m[0][3];
    out[1] = out[1] + m[1][3];
    out[2] = out[2] + m[2][3];
    out[3] = out[3] + m[3][3];
}
void fn_8014EB30(void **arg0) {
    extern u8 lbl_802E3F78[];
    extern u8 lbl_802E67C0[];
    arg0[0] = lbl_802E3F78;
    arg0[0] = lbl_802E67C0;
}

void fn_8014EB4C(s32 arg0) {
    lbl_8035ACB8 = arg0;
}

u32 fn_8014EB54(f32 (*__restrict m)[4], f32 *__restrict v, f32 *__restrict out) {
    extern u32 lbl_80364538;
    u32 x, y, z;
    u32 code;

    out[0] = v[0] * m[0][0];
    out[1] = v[0] * m[1][0];
    out[2] = v[0] * m[2][0];
    out[0] = v[1] * m[0][1] + out[0];
    out[1] = v[1] * m[1][1] + out[1];
    out[2] = v[1] * m[2][1] + out[2];
    out[0] = v[2] * m[0][2] + out[0];
    out[1] = v[2] * m[1][2] + out[1];
    out[2] = v[2] * m[2][2] + out[2];
    out[0] = out[0] + m[0][3];
    out[1] = out[1] + m[1][3];
    out[2] = out[2] + m[2][3];

    x = ((u32 *)out)[0];
    y = ((u32 *)out)[1];
    z = ((u32 *)out)[2];
    if (x & 0x80000000) {
        code = ((0x3F800000 - (x & 0x7FFFFFFF)) >> 29) & 4;
    } else {
        code = ((0x3F800000 - x) >> 28) & 8;
    }
    if (y & 0x80000000) {
        code |= ((0x3F800000 - (y & 0x7FFFFFFF)) >> 27) & 0x10;
    } else {
        code |= ((0x3F800000 - y) >> 26) & 0x20;
    }
    if (z & 0x80000000) {
        return code | lbl_80364538;
    }
    return code | (((0x3F800000 - z) >> 30) & 2);
}

/* QV=2.0p1 */
static inline void MtxMultVec4_8014EC90(const f32 (*m)[4], const f32 *v, f32 *out) {
    out[0] = v[0] * m[0][0];
    out[1] = v[0] * m[1][0];
    out[2] = v[0] * m[2][0];
    out[3] = v[0] * m[3][0];
    out[0] = v[1] * m[0][1] + out[0];
    out[1] = v[1] * m[1][1] + out[1];
    out[2] = v[1] * m[2][1] + out[2];
    out[3] = v[1] * m[3][1] + out[3];
    out[0] = v[2] * m[0][2] + out[0];
    out[1] = v[2] * m[1][2] + out[1];
    out[2] = v[2] * m[2][2] + out[2];
    out[3] = v[2] * m[3][2] + out[3];
    out[0] = out[0] + m[0][3];
    out[1] = out[1] + m[1][3];
    out[2] = out[2] + m[2][3];
    out[3] = out[3] + m[3][3];
}

#pragma opt_propagation off
u32 fn_8014EC90(const f32 (*m)[4], const f32 *v, f32 *out, f32 *ndc) {
    extern u32 lbl_80364538;
    extern f32 lbl_8036453C;
    u32 x, y, z, w;
    u32 code;
    u32 t;
    f32 inv;

    MtxMultVec4_8014EC90(m, v, out);
    inv = lbl_8036453C / out[3];
    x = ((u32 *)out)[0];
    y = ((u32 *)out)[1];
    z = ((u32 *)out)[2];
    w = ((u32 *)out)[3];
    if (w & 0x80000000) {
        x ^= 0x80000000;
        y ^= 0x80000000;
        z ^= 0x80000000;
        w ^= 0x80000000;
    }
    if (x & 0x80000000) {
        code = ((w - (x & 0x7FFFFFFF)) >> 29) & 4;
    } else {
        code = ((w - x) >> 28) & 8;
    }
    if (y & 0x80000000) {
        code |= ((w - (y & 0x7FFFFFFF)) >> 27) & 0x10;
    } else {
        code |= ((w - y) >> 26) & 0x20;
    }
    if (z & 0x80000000) {
        t = lbl_80364538;
        code |= t;
    } else {
        code |= ((w - z) >> 30) & 2;
    }
    ndc[0] = out[0] * inv;
    ndc[1] = out[1] * inv;
    ndc[2] = out[2] * inv;
    return code;
}
#pragma opt_propagation reset


u32 fn_8014EF58(f32 (*__restrict m)[4], f32 *__restrict v, f32 *__restrict out, f32 *ndc) {
    extern f32 lbl_8036453C;
    u32 x, y, z, w;
    u32 neg, over;
    f32 inv;

    MtxMultVec4(m, v, out);
    x = ((u32 *)out)[0];
    y = ((u32 *)out)[1];
    z = ((u32 *)out)[2];
    w = ((u32 *)out)[3];
    inv = lbl_8036453C / out[3];
    ndc[0] = out[0] * inv;
    ndc[1] = out[1] * inv;
    ndc[2] = out[2] * inv;

    neg = ((y >> 27) & 0x10) | ((x >> 29) & 4) | (z >> 31);
    over = (((w - y) >> 26) & 0x20) | (((w - x) >> 28) & 8) | (((w - z) >> 30) & 2);
    return neg | (over & ~(neg << 1));
}



/* QV=2.0p1 */
void fn_8014F0D8(f32 *m, const f32 *rect, const f32 *scale, const f32 *ofs, f32 n, f32 f) {
    m[0] = lbl_80364540 * scale[0] / (rect[2] - rect[0]);
    m[4] = lbl_80364544;
    m[8] = lbl_80364544;
    m[12] = lbl_80364544;
    m[1] = lbl_80364544;
    m[5] = lbl_80364540 * scale[1] / (rect[3] - rect[1]);
    m[9] = lbl_80364544;
    m[13] = lbl_80364544;
    m[2] = lbl_80364544;
    m[6] = lbl_80364544;
    m[10] = lbl_8036453C / (f - n);
    m[14] = lbl_80364544;
    m[3] = ofs[0];
    m[7] = ofs[1];
    m[11] = -(n / (f - n));
    m[15] = lbl_8036453C;
}

/* QV=2.0p1 */
void fn_8014F198(f32 *m, const f32 *r, const f32 *s, const f32 *o, f32 n, f32 f) {
    f32 a = s[0] / (r[2] - r[0]);
    f32 b = s[1] / (r[3] - r[1]);
    f32 q = f / (f - n);
    f32 n2 = lbl_80364540 * n;
    m[0] = n2 * a;
    m[4] = lbl_80364544;
    m[8] = lbl_80364544;
    m[12] = lbl_80364544;
    m[1] = lbl_80364544;
    m[5] = n2 * b;
    m[9] = lbl_80364544;
    m[13] = lbl_80364544;
    m[2] = o[0] - a * (r[0] + r[2]);
    m[6] = o[1] - b * (r[3] + r[1]);
    m[10] = q;
    m[14] = lbl_8036453C;
    m[3] = lbl_80364544;
    m[7] = lbl_80364544;
    m[11] = -(n * q);
    m[15] = lbl_80364544;
}

/* QV=2.0p1 */
u32 fn_8014EE48(f32 (*__restrict m)[4], f32 *__restrict v, f32 *__restrict out) {
    u32 x, y, z;
    u32 neg, over;

    out[0] = v[0] * m[0][0];
    out[1] = v[0] * m[1][0];
    out[2] = v[0] * m[2][0];
    out[0] = v[1] * m[0][1] + out[0];
    out[1] = v[1] * m[1][1] + out[1];
    out[2] = v[1] * m[2][1] + out[2];
    out[0] = v[2] * m[0][2] + out[0];
    out[1] = v[2] * m[1][2] + out[1];
    out[2] = v[2] * m[2][2] + out[2];
    out[0] = out[0] + m[0][3];
    out[1] = out[1] + m[1][3];
    out[2] = out[2] + m[2][3];
    x = ((u32 *)out)[0];
    y = ((u32 *)out)[1];
    z = ((u32 *)out)[2];
    neg = ((x >> 29) & 4);
    over = (((0x3F800000 - x) >> 28) & 8);
    neg |= ((y >> 27) & 16);
    over |= (((0x3F800000 - y) >> 26) & 32);
    neg |= (z >> 31);
    over |= (((0x3F800000 - z) >> 30) & 2);
    return neg | (over & ~(neg << 1));
}

} /* extern "C" */
