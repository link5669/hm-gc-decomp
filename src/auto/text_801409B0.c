/* Functions from 0x801409B0 to 0x80142990, found by decomp-toolkit. */
#include "common.h"

typedef struct ImgDec {
    u8 pad0[0x3C];
    u32 shr[4];
    u32 shl[4];
    u8 pad5C[0x7C - 0x5C];
    u32 mask[4];
    u8 pad8C[0x9C - 0x8C];
    s32 count;
    u8 padA0[0xB0 - 0xA0];
    u8 *src;
    u8 *out;
    u8 padB8[0x138 - 0xB8];
    u8 buf[0x184 - 0x138];
    u8 *dst;
    u8 pad188[4];
    u8 *px;
    u8 pad190[0x6D0 - 0x190];
    s32 wt[3];
} ImgDec;

typedef struct ImgPix {
    u8 pad0[0x5C];
    u32 shr[4];
    u32 shl[4];
    u8 pad7C[0x9C - 0x7C];
    s32 count;
    u8 padA0[0xB4 - 0xA0];
    u8 *out;
    u8 padB8[0x188 - 0xB8];
    u8 *src;
    u8 *px;
    u8 *mask;
} ImgPix;

void fn_801409B0(ImgPix *p) {
    u8 *s = p->src;
    u8 *e = s + p->count * 4;
    u8 *m;
    u32 *o = (u32 *)p->out;
    m = p->mask;
    do {
        if (*m != 0) {
            *o = ((u32)s[0] >> p->shr[0]) << p->shl[0];
            *o |= ((u32)s[1] >> p->shr[1]) << p->shl[1];
            *o |= ((u32)s[2] >> p->shr[2]) << p->shl[2];
            *o |= ((u32)s[3] >> p->shr[3]) << p->shl[3];
        }
        s += 4;
        m++;
        o++;
    } while (s < e);
    p->out += p->count * 4;
}

void fn_80140A78(ImgPix *p) {
    u8 *s = p->src;
    u8 *e = s + p->count * 4;
    u8 *m = p->mask;
    do {
        if (*m != 0) {
            p->out[0] = s[3];
            p->out[1] = s[0];
            p->out[2] = s[1];
            p->out[3] = s[2];
        }
        s += 4;
        m++;
        p->out += 4;
    } while (s < e);
}

void fn_80140AE8(ImgPix *p) {
    u8 *s = p->src;
    u8 *e = s + p->count * 4;
    u8 *m = p->mask;
    do {
        if (*m != 0) {
            p->out[0] = s[3];
            p->out[1] = s[2];
            p->out[2] = s[1];
            p->out[3] = s[0];
        }
        s += 4;
        m++;
        p->out += 4;
    } while (s < e);
}

void fn_80140B58(ImgPix *p) {
    u8 *s = p->src;
    u8 *e = s + p->count * 4;
    u8 *m = p->mask;
    do {
        if (*m != 0) {
            u32 v;
            v = ((u32)s[0] >> p->shr[0]) << p->shl[0];
            v |= ((u32)s[1] >> p->shr[1]) << p->shl[1];
            v |= ((u32)s[2] >> p->shr[2]) << p->shl[2];
            v |= ((u32)s[3] >> p->shr[3]) << p->shl[3];
            p->out[0] = v;
            p->out[1] = v >> 8;
            p->out[2] = v >> 16;
        }
        s += 4;
        m++;
        p->out += 3;
    } while (s < e);
}

void fn_80140C14(ImgPix *p) {
    u8 *s = p->src;
    u8 *e = s + p->count * 4;
    u8 *m = p->mask;
    do {
        if (*m != 0) {
            p->out[0] = s[2];
            p->out[1] = s[1];
            p->out[2] = s[0];
        }
        s += 4;
        m++;
        p->out += 3;
    } while (s < e);
}

void fn_80140C78(ImgPix *p) {
    u8 *s = p->src;
    u8 *e = s + p->count * 4;
    u8 *m = p->mask;
    do {
        if (*m != 0) {
            p->out[0] = s[0];
            p->out[1] = s[1];
            p->out[2] = s[2];
        }
        s += 4;
        m++;
        p->out += 3;
    } while (s < e);
}



void fn_80140E38(ImgPix *p) {
    u8 *s = p->px;
    u8 *e = s + p->count;
    u8 *m = p->mask;
    do {
        if (*m != 0) {
            *p->out = *s;
        }
        s++;
        m++;
        p->out++;
    } while (s < e);
}

void fn_80140E80(ImgPix *p) {
    u8 *s;
    u8 *m;
    m = p->mask;
    s = p->px;
    if (m[0] != 0) {
        *p->out = (*p->out & 0xF0) | s[0];
    }
    m++;
    s++;
    p->out++;
    p->count--;
    while ((u32)p->count > 1) {
        if (m[0] != 0) {
            if (m[1] != 0) {
                *p->out = s[1] | (s[0] << 4);
            } else {
                *p->out = (*p->out & 0xF) | (s[0] << 4);
            }
        } else if (m[1] != 0) {
            *p->out = s[1] | (*p->out & 0xF0);
        }
        m += 2;
        s += 2;
        p->out++;
        p->count -= 2;
    }
    if ((u32)p->count != 0 && m[0] != 0) {
        *p->out = ((s[0] << 4) & 0xFF0) | (*p->out & ~0xFF0);
    }
}

void fn_80140F9C(ImgPix *p) {
    u8 *s;
    u8 *m;
    m = p->mask;
    s = p->px;
    while ((u32)p->count > 1) {
        if (m[0] != 0) {
            if (m[1] != 0) {
                *p->out = s[1] | (s[0] << 4);
            } else {
                *p->out = (*p->out & 0xF) | (s[0] << 4);
            }
        } else if (m[1] != 0) {
            *p->out = s[1] | (*p->out & 0xF0);
        }
        m += 2;
        s += 2;
        p->out++;
        p->count -= 2;
    }
    if ((u32)p->count != 0 && m[0] != 0) {
        *p->out = ((s[0] << 4) & 0xFF0) | (*p->out & ~0xFF0);
    }
}

void fn_80141074(ImgPix *p) {
    u8 *s;
    u8 *m;
    m = p->mask;
    s = p->px;
    if (m[0] != 0) {
        *p->out = (*p->out & 0xF) | (s[0] << 4);
    }
    m++;
    s++;
    p->out++;
    p->count--;
    while ((u32)p->count > 1) {
        if (m[0] != 0) {
            if (m[1] != 0) {
                *p->out = s[0] | (s[1] << 4);
            } else {
                *p->out = (*p->out & 0xF0) | s[0];
            }
        } else if (m[1] != 0) {
            *p->out = ((s[1] << 4) & 0xFF0) | (*p->out & ~0xFF0);
        }
        m += 2;
        s += 2;
        p->out++;
        p->count -= 2;
    }
    if ((u32)p->count != 0 && m[0] != 0) {
        *p->out = s[0] | (*p->out & 0xF0);
    }
}

void fn_80141190(ImgPix *p) {
    u8 *s;
    u8 *m = p->mask;
    s = p->px;
    while ((u32)p->count > 1) {
        if (m[0] != 0) {
            if (m[1] != 0) {
                *p->out = s[0] | (s[1] << 4);
            } else {
                *p->out = (*p->out & 0xF0) | s[0];
            }
        } else if (m[1] != 0) {
            *p->out = (s[1] << 4) | (*p->out & 0xF);
        }
        m += 2;
        s += 2;
        p->out++;
        p->count -= 2;
    }
    if ((u32)p->count != 0 && m[0] != 0) {
        *p->out = s[0] | (*p->out & 0xF0);
    }
}

void fn_80141268(ImgDec *p) {
    u8 *s = p->px;
    u8 *e = s + ((u32)p->count >> 1);
    do {
        u8 v = *s;
        s++;
        *p->out = v;
        p->out++;
    } while (s < e);
}

void fn_801412A0(ImgDec *p) {
    u32 *s = (u32 *)p->src;
    u8 *d = p->dst;
    u8 *e = d + p->count * 4;
    do {
        u32 v;
        v = *s >> p->shr[0];
        d[0] = (v << p->shl[0]) | (v & p->mask[0]);
        v = *s >> p->shr[1];
        d[1] = (v << p->shl[1]) | (v & p->mask[1]);
        v = *s >> p->shr[2];
        d[2] = (v << p->shl[2]) | (v & p->mask[2]);
        v = *s >> p->shr[3];
        s++;
        d[3] = (v << p->shl[3]) | (v & p->mask[3]);
        d += 4;
    } while (d < e);
    p->src += p->count * 4;
}

void fn_8014136C(ImgDec *p) {
    u8 *d = p->dst;
    u8 *e = d + p->count * 4;
    do {
        d[2] = p->src[0];
        d[1] = p->src[1];
        d[0] = p->src[2];
        d[3] = p->src[3];
        d += 4;
        p->src += 4;
    } while (d < e);
}

void fn_801413C8(ImgDec *p) {
    u8 *d = p->dst;
    u8 *e = d + p->count * 4;
    do {
        d[0] = p->src[0];
        d[1] = p->src[1];
        d[2] = p->src[2];
        d[3] = p->src[3];
        d += 4;
        p->src += 4;
    } while (d < e);
}

void fn_80141424(ImgDec *p) {
    u32 *s = (u32 *)p->src;
    u8 *d = p->dst;
    u8 *e = d + p->count * 4;
    do {
        u32 v;
        v = *s >> p->shr[0];
        d[0] = (v << p->shl[0]) | (v & p->mask[0]);
        v = *s >> p->shr[1];
        d[1] = (v << p->shl[1]) | (v & p->mask[1]);
        v = *s >> p->shr[2];
        s++;
        d[2] = (v << p->shl[2]) | (v & p->mask[2]);
        d[3] = 0xFF;
        d += 4;
    } while (d < e);
    p->src += p->count * 4;
}

void fn_801414D4(ImgDec *p) {
    u8 *d = p->dst;
    u8 *e = d + p->count * 4;
    do {
        d[2] = p->src[0];
        d[1] = p->src[1];
        d[0] = p->src[2];
        d[3] = 0xFF;
        d += 4;
        p->src += 4;
    } while (d < e);
}

void fn_8014152C(ImgDec *p) {
    u8 *d = p->dst;
    u8 *e = d + p->count * 4;
    do {
        d[0] = p->src[0];
        d[1] = p->src[1];
        d[2] = p->src[2];
        d[3] = 0xFF;
        d += 4;
        p->src += 4;
    } while (d < e);
}


void fn_8014164C(ImgDec *p) {
    u8 *d = p->dst;
    u8 *e = d + p->count * 4;
    do {
        d[2] = p->src[0];
        d[1] = p->src[1];
        d[0] = p->src[2];
        d[3] = 0xFF;
        d += 4;
        p->src += 3;
    } while (d < e);
}

void fn_801416A4(ImgDec *p) {
    u8 *d = p->dst;
    u8 *e = d + p->count * 4;
    do {
        d[0] = p->src[0];
        d[1] = p->src[1];
        d[2] = p->src[2];
        d[3] = 0xFF;
        d += 4;
        p->src += 3;
    } while (d < e);
}

void fn_801416FC(ImgDec *p) {
    u8 *e;
    u16 *s;
    u8 *d;
    u32 v;
    d = p->dst;
    s = (u16 *)p->src;
    e = d + p->count * 4;
    do {
        v = (u32)*s >> p->shr[0];
        d[0] = (v << p->shl[0]) | (v & p->mask[0]);
        v = (u32)*s >> p->shr[1];
        d[1] = (v << p->shl[1]) | (v & p->mask[1]);
        v = (u32)*s >> p->shr[2];
        d[2] = (v << p->shl[2]) | (v & p->mask[2]);
        v = (u32)*s >> p->shr[3];
        s++;
        d[3] = ~(v & 1) + 1;
        d += 4;
    } while (d < e);
    p->src += p->count * 2;
}

void fn_801417C0(ImgDec *p) {
    u8 *e;
    u16 *s;
    u8 *d;
    u32 v;
    d = p->dst;
    s = (u16 *)p->src;
    e = d + p->count * 4;
    do {
        v = (u32)*s >> p->shr[0];
        d[0] = (v << p->shl[0]) | (v & p->mask[0]);
        v = (u32)*s >> p->shr[1];
        d[1] = (v << p->shl[1]) | (v & p->mask[1]);
        v = (u32)*s >> p->shr[2];
        d[2] = (v << p->shl[2]) | (v & p->mask[2]);
        v = (u32)*s >> p->shr[3];
        s++;
        d[3] = (v << p->shl[3]) | (v & p->mask[3]);
        d += 4;
    } while (d < e);
    p->src += p->count * 2;
}

void fn_8014188C(ImgDec *p) {
    u8 *e;
    u16 *s;
    u8 *d;
    u32 v;
    d = p->dst;
    s = (u16 *)p->src;
    e = d + p->count * 4;
    do {
        v = (u32)*s >> p->shr[0];
        d[0] = (v << p->shl[0]) | (v & p->mask[0]);
        v = (u32)*s >> p->shr[1];
        d[1] = (v << p->shl[1]) | (v & p->mask[1]);
        v = (u32)*s >> p->shr[2];
        s++;
        d[2] = (v << p->shl[2]) | (v & p->mask[2]);
        d[3] = 0xFF;
        d += 4;
    } while (d < e);
    p->src += p->count * 2;
}

void fn_8014193C(ImgDec *p) {
    u8 *d = p->buf;
    u8 *e = (u8 *)p + p->count;
    e += sizeof(p->padB8) + 0xB8;
    do {
        u8 v = *p->src++;
        *d = v;
        ++d;
    } while (e > d);
}

void fn_80141970(ImgDec *p) {
    u8 *d;
    s32 n;
    n = p->count;
    d = p->buf;
    do {
        d[0] = *p->src & 0xF;
        p->src++;
        if (--n == 0) return;
        d[1] = *p->src >> 4;
        d += 2;
    } while (--n != 0);
}

void fn_801419BC(ImgDec *p) {
    u8 *d;
    s32 n;
    n = p->count;
    d = p->buf;
    do {
        d[0] = *p->src >> 4;
        if (--n == 0) return;
        d[1] = *p->src & 0xF;
        d += 2;
        p->src++;
    } while (--n != 0);
}

void fn_80141A08(ImgDec *p) {
    u8 *d;
    s32 n;
    n = p->count;
    d = p->buf;
    do {
        d[0] = *p->src >> 4;
        p->src++;
        if (--n == 0) return;
        d[1] = *p->src & 0xF;
        d += 2;
    } while (--n != 0);
}

void fn_80141A54(ImgDec *p) {
    u8 *d;
    s32 n;
    n = p->count;
    d = p->buf;
    do {
        d[0] = *p->src & 0xF;
        if (--n == 0) return;
        d[1] = *p->src >> 4;
        d += 2;
        p->src++;
    } while (--n != 0);
}

void fn_80141AA0(ImgDec *p) {
    u8 *d = p->buf;
    u8 *e = d + ((u32)p->count >> 1);
    do {
        *d = *p->src;
        d++;
        p->src++;
    } while (d < e);
}

void fn_80141AD8(ImgPix *p) {
 u8 *s = p->src;
 u32 *d = (u32 *)p->out;
 u8 *e = s + 0x80;
 do {
 d[0] = ((u32)s[0] >> p->shr[0]) << p->shl[0];
 d[0] |= ((u32)s[1] >> p->shr[1]) << p->shl[1];
 d[0] |= ((u32)s[2] >> p->shr[2]) << p->shl[2];
 d[0] |= ((u32)s[3] >> p->shr[3]) << p->shl[3];
 d[1] = ((u32)s[4] >> p->shr[0]) << p->shl[0];
 d[1] |= ((u32)s[5] >> p->shr[1]) << p->shl[1];
 d[1] |= ((u32)s[6] >> p->shr[2]) << p->shl[2];
 d[1] |= ((u32)s[7] >> p->shr[3]) << p->shl[3];
 d[2] = ((u32)s[8] >> p->shr[0]) << p->shl[0];
 d[2] |= ((u32)s[9] >> p->shr[1]) << p->shl[1];
 d[2] |= ((u32)s[10] >> p->shr[2]) << p->shl[2];
 d[2] |= ((u32)s[11] >> p->shr[3]) << p->shl[3];
 d[3] = ((u32)s[12] >> p->shr[0]) << p->shl[0];
 d[3] |= ((u32)s[13] >> p->shr[1]) << p->shl[1];
 d[3] |= ((u32)s[14] >> p->shr[2]) << p->shl[2];
 d[3] |= ((u32)s[15] >> p->shr[3]) << p->shl[3];
 s += 16;
 d += 4;
 } while (s < e);
 p->out += 0x80;
}

void fn_80141CE4(ImgPix *p) {
    u8 *s = p->src;
    u8 *e = s + 0x80;
    do {
        p->out[0] = s[3];
        p->out[1] = s[0];
        p->out[2] = s[1];
        p->out[3] = s[2];
        p->out += 4;
        p->out[0] = s[7];
        p->out[1] = s[4];
        p->out[2] = s[5];
        p->out[3] = s[6];
        p->out += 4;
        p->out[0] = s[11];
        p->out[1] = s[8];
        p->out[2] = s[9];
        p->out[3] = s[10];
        p->out += 4;
        p->out[0] = s[15];
        p->out[1] = s[12];
        p->out[2] = s[13];
        p->out[3] = s[14];
        p->out += 4;
        s += 16;
    } while (s < e);
}

void fn_80141DEC(ImgPix *p) {
    u8 *s = p->src;
    u8 *e = s + 0x80;
    do {
        p->out[0] = s[3];
        p->out[1] = s[2];
        p->out[2] = s[1];
        p->out[3] = s[0];
        p->out += 4;
        p->out[0] = s[7];
        p->out[1] = s[6];
        p->out[2] = s[5];
        p->out[3] = s[4];
        p->out += 4;
        p->out[0] = s[11];
        p->out[1] = s[10];
        p->out[2] = s[9];
        p->out[3] = s[8];
        p->out += 4;
        p->out[0] = s[15];
        p->out[1] = s[14];
        p->out[2] = s[13];
        p->out[3] = s[12];
        p->out += 4;
        s += 16;
    } while (s < e);
}

void fn_80141EF4(ImgPix *p) {
    u8 *s;
    u8 *e;
    s = p->src;
    e = s + 0x80;
    do {
        u32 v;
        v = ((u32)s[0] >> p->shr[0]) << p->shl[0];
        v |= ((u32)s[1] >> p->shr[1]) << p->shl[1];
        v |= ((u32)s[2] >> p->shr[2]) << p->shl[2];
        v |= ((u32)s[3] >> p->shr[3]) << p->shl[3];
        p->out[0] = v;
        p->out[1] = v >> 8;
        p->out[2] = v >> 16;
        p->out += 3;
        v = ((u32)s[4] >> p->shr[0]) << p->shl[0];
        v |= ((u32)s[5] >> p->shr[1]) << p->shl[1];
        v |= ((u32)s[6] >> p->shr[2]) << p->shl[2];
        v |= ((u32)s[7] >> p->shr[3]) << p->shl[3];
        p->out[0] = v;
        p->out[1] = v >> 8;
        p->out[2] = v >> 16;
        p->out += 3;
        v = ((u32)s[8] >> p->shr[0]) << p->shl[0];
        v |= ((u32)s[9] >> p->shr[1]) << p->shl[1];
        v |= ((u32)s[10] >> p->shr[2]) << p->shl[2];
        v |= ((u32)s[11] >> p->shr[3]) << p->shl[3];
        p->out[0] = v;
        p->out[1] = v >> 8;
        p->out[2] = v >> 16;
        p->out += 3;
        v = ((u32)s[12] >> p->shr[0]) << p->shl[0];
        v |= ((u32)s[13] >> p->shr[1]) << p->shl[1];
        v |= ((u32)s[14] >> p->shr[2]) << p->shl[2];
        v |= ((u32)s[15] >> p->shr[3]) << p->shl[3];
        s += 16;
        p->out[0] = v;
        p->out[1] = v >> 8;
        p->out[2] = v >> 16;
        p->out += 3;
    } while (s < e);
}

void fn_8014212C(ImgPix *p) {
    u8 *s = p->src;
    u8 *e = s + 0x80;
    do {
        p->out[0] = s[2];
        p->out[1] = s[1];
        p->out[2] = s[0];
        p->out += 3;
        p->out[0] = s[6];
        p->out[1] = s[5];
        p->out[2] = s[4];
        p->out += 3;
        p->out[0] = s[10];
        p->out[1] = s[9];
        p->out[2] = s[8];
        p->out += 3;
        p->out[0] = s[14];
        p->out[1] = s[13];
        p->out[2] = s[12];
        s += 16;
        p->out += 3;
    } while (s < e);
}

void fn_80142204(ImgPix *p) {
    u8 *s = p->src;
    u8 *e = s + 0x80;
    do {
        p->out[0] = s[0];
        p->out[1] = s[1];
        p->out[2] = s[2];
        p->out += 3;
        p->out[0] = s[4];
        p->out[1] = s[5];
        p->out[2] = s[6];
        p->out += 3;
        p->out[0] = s[8];
        p->out[1] = s[9];
        p->out[2] = s[10];
        p->out += 3;
        p->out[0] = s[12];
        p->out[1] = s[13];
        p->out[2] = s[14];
        p->out += 3;
        s += 16;
    } while (s < e);
}

void fn_801422DC(ImgPix *p) {
    u16 *d;
    u8 *s;
    u8 *e;
    s = p->src;
    d = (u16 *)p->out;
    e = s + 0x80;
    do {
        u32 v;
        v = ((u32)s[0] >> p->shr[0]) << p->shl[0];
        v |= ((u32)s[1] >> p->shr[1]) << p->shl[1];
        v |= ((u32)s[2] >> p->shr[2]) << p->shl[2];
        v |= ((u32)s[3] >> p->shr[3]) << p->shl[3];
        d[0] = v;
        v = ((u32)s[4] >> p->shr[0]) << p->shl[0];
        v |= ((u32)s[5] >> p->shr[1]) << p->shl[1];
        v |= ((u32)s[6] >> p->shr[2]) << p->shl[2];
        v |= ((u32)s[7] >> p->shr[3]) << p->shl[3];
        d[1] = v;
        v = ((u32)s[8] >> p->shr[0]) << p->shl[0];
        v |= ((u32)s[9] >> p->shr[1]) << p->shl[1];
        v |= ((u32)s[10] >> p->shr[2]) << p->shl[2];
        v |= ((u32)s[11] >> p->shr[3]) << p->shl[3];
        d[2] = v;
        v = ((u32)s[12] >> p->shr[0]) << p->shl[0];
        v |= ((u32)s[13] >> p->shr[1]) << p->shl[1];
        v |= ((u32)s[14] >> p->shr[2]) << p->shl[2];
        v |= ((u32)s[15] >> p->shr[3]) << p->shl[3];
        s += 16;
        d[3] = v;
        d += 4;
    } while (s < e);
    p->out += 0x40;
}

void fn_80142488(ImgPix *p) {
    u16 *d;
    u8 *s;
    u8 *e;
    s = p->src;
    d = (u16 *)p->out;
    e = s + 0x80;
    do {
        u32 v;
        v = ((u32)s[0] >> p->shr[0]) << p->shl[0];
        v |= ((u32)s[1] >> p->shr[1]) << p->shl[1];
        v |= ((u32)s[2] >> p->shr[2]) << p->shl[2];
        d[0] = v;
        v = ((u32)s[4] >> p->shr[0]) << p->shl[0];
        v |= ((u32)s[5] >> p->shr[1]) << p->shl[1];
        v |= ((u32)s[6] >> p->shr[2]) << p->shl[2];
        d[1] = v;
        v = ((u32)s[8] >> p->shr[0]) << p->shl[0];
        v |= ((u32)s[9] >> p->shr[1]) << p->shl[1];
        v |= ((u32)s[10] >> p->shr[2]) << p->shl[2];
        d[2] = v;
        v = ((u32)s[12] >> p->shr[0]) << p->shl[0];
        v |= ((u32)s[13] >> p->shr[1]) << p->shl[1];
        v |= ((u32)s[14] >> p->shr[2]) << p->shl[2];
        s += 16;
        d[3] = v;
        d += 4;
    } while (s < e);
    p->out += 0x40;
}

void fn_801425D4(ImgDec *p) {
    u8 *s = p->px;
    u8 *e = s + 0x20;
    do {
        p->out[0] = s[0];
        p->out[1] = s[1];
        p->out[2] = s[2];
        p->out[3] = s[3];
        s += 4;
        p->out += 4;
    } while (s < e);
}

void fn_80142628(ImgDec *p) {
    u32 *d;
    u32 *s;
    u32 *e;
    s = (u32 *)p->px;
    d = (u32 *)p->out;
    e = s + 8;
    do {
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        s += 4;
        d += 4;
    } while (s < e);
    p->out += 0x20;
}

typedef struct ImgDec_80142674 {
    u8 pad0[0xB4];
    u8 *out;
    u8 padB8[0x18C - 0xB8];
    u8 *px;
} ImgDec_80142674;

void fn_80142674(ImgDec_80142674 *p) {
    u8 *s = p->px;
    u8 *e = s + 0x20;
    do {
        p->out[0] = s[0] | (p->out[0] & 0xF0);
        p->out[1] = s[2] | (s[1] << 4);
        p->out[2] = s[4] | (s[3] << 4);
        p->out[3] = s[6] | (s[5] << 4);
        p->out[4] = (p->out[4] & 0xF) | (s[7] << 4);
        s += 8;
        p->out += 4;
    } while (s < e);
}


void fn_80142710(ImgDec *p) {
    u8 *s = p->px;
    u8 *e = s + 0x20;
    do {
        p->out[0] = s[1] | (s[0] << 4);
        p->out[1] = s[3] | (s[2] << 4);
        p->out[2] = s[5] | (s[4] << 4);
        p->out[3] = s[7] | (s[6] << 4);
        s += 8;
        p->out += 4;
    } while (s < e);
}

void fn_80142794(ImgDec *p) {
    u8 *s = p->px;
    u8 *e = s + 0x20;
    do {
        p->out[0] = (p->out[0] & 0xF) | (s[0] << 4);
        p->out[1] = s[1] | (s[2] << 4);
        p->out[2] = s[3] | (s[4] << 4);
        p->out[3] = s[5] | (s[6] << 4);
        p->out[4] = s[7] | (p->out[4] & 0xF0);
        s += 8;
        p->out += 4;
    } while (s < e);
}

void fn_80142830(ImgDec *p) {
    u8 *s = p->px;
    u8 *e = s + 0x20;
    do {
        p->out[0] = s[0] | (s[1] << 4);
        p->out[1] = s[2] | (s[3] << 4);
        p->out[2] = s[4] | (s[5] << 4);
        p->out[3] = s[6] | (s[7] << 4);
        s += 8;
        p->out += 4;
    } while (s < e);
}

void fn_801428B4(ImgDec *p) {
    u32 *d = (u32 *)p->out;
    u32 *s = (u32 *)p->px;
    u32 *e = s + 4;
    do {
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        s += 4;
        d += 4;
    } while (s < e);
    p->out += 0x10;
}

typedef struct ImgDec_80142900 {
    u8 pad0[0x3C];
    u32 shr[4];
    u32 shl[4];
    u8 pad5C[0x7C - 0x5C];
    u32 mask[4];
    u8 pad8C[0x9C - 0x8C];
    s32 count;
    u8 padA0[0xB0 - 0xA0];
    u8 *src;
    u8 *out;
    u8 padB8[0x138 - 0xB8];
    u8 buf[0x184 - 0x138];
    u8 *dst;
    u8 pad188[4];
    u8 *px;
    u8 pad190[0x6D0 - 0x190];
    s32 wt[3];
} ImgDec_80142900;

void fn_80142900(ImgDec_80142900 *p) {
    u8 *d = p->dst;
    u8 *e = d + p->count * 4;
    for (; d < e; d += 4) {
        s32 x = d[0] * 2 - 0xFF; s32 y = d[1] * 2 - 0xFF; s32 z = d[2] * 2 - 0xFF;
        s32 v = x * p->wt[0] + y * p->wt[1] + z * p->wt[2];
        if (v < 0) v = 0;
        d[0] = (u32)v >> 8;
        d[1] = (u32)v >> 8;
        d[2] = (u32)v >> 8;
    }
}

typedef struct ImgDec_80141584 {
    u8 pad0[0x3C];
    u32 shr[4];
    u32 shl[4];
    u8 pad5C[0x7C - 0x5C];
    u32 mask[4];
    u8 pad8C[0x9C - 0x8C];
    s32 count;
    u8 padA0[0xB0 - 0xA0];
    u8 *src;
    u8 *out;
    u8 padB8[0x138 - 0xB8];
    u8 buf[0x184 - 0x138];
    u8 *dst;
    u8 pad188[4];
    u8 *px;
    u8 pad190[0x6D0 - 0x190];
    s32 wt[3];
} ImgDec_80141584;
void fn_80141584(ImgDec_80141584 *p) {
    u8 *d;
    u32 v;
    u32 c;
    u8 *e;
    u32 b;
    u32 a;
    d = p->dst;
    e = d + p->count * 4;
    do {
        b = p->src[1] << 8;
        a = p->src[2] << 16;
        c = p->src[0];
        p->src += 3;
        c |= b;
        c |= a;
        v = c >> p->shr[0];
        d[0] = (v << p->shl[0]) | (v & p->mask[0]);
        v = c >> p->shr[1];
        d[1] = (v << p->shl[1]) | (v & p->mask[1]);
        v = c >> p->shr[2];
        d[2] = (v << p->shl[2]) | (v & p->mask[2]);
        v = c >> p->shr[3];
        d[3] = (v << p->shl[3]) | (v & p->mask[3]);
        d += 4;
    } while (d < e);
}

typedef struct ImgPix80140CDC {
    u8 pad0[0x5C];
    u32 shr[4];
    u32 shl[4];
    u8 pad7C[0x9C - 0x7C];
    s32 count;
    u8 padA0[0xB4 - 0xA0];
    u8 *out;
    u8 padB8[0x188 - 0xB8];
    u8 *src;
    u8 *px;
    u8 *mask;
} ImgPix80140CDC;

static inline u16 Pack80140CDC(ImgPix80140CDC *p, u8 *s) {
    u16 v;
    v = ((u32)s[0] >> p->shr[0]) << p->shl[0];
    v |= ((u32)s[1] >> p->shr[1]) << p->shl[1];
    v |= ((u32)s[2] >> p->shr[2]) << p->shl[2];
    v |= ((u32)s[3] >> p->shr[3]) << p->shl[3];
    return v;
}

void fn_80140CDC(ImgPix80140CDC *p) {
    u16 *d;
    u8 *s = p->src;
    u8 *e = s + p->count * 4;
    u8 *m = p->mask;
    d = (u16 *)p->out;
    do {
        if (*m != 0) {
            *d = Pack80140CDC(p, s);
        }
        s += 4;
        m++;
        d++;
    } while (s < e);
    p->out += p->count * 2;
}

typedef struct S80140D98 {
    u8 pad0[92];
    u32 rs;
    u32 gs;
    u32 bs;
    u8 pad1[4];
    u32 rp;
    u32 gp;
    u32 bp;
    u8 pad2[36];
    s32 count;
    u8 pad3[20];
    u16 *dst;
    u8 pad4[208];
    u8 *src;
    u8 pad5[4];
    u8 *mask;
} S80140D98;

void fn_80140D98(S80140D98 *p) {
    u16 *dst;
    u16 c;
    u8 *src;
    u8 *end;
    u8 *mask;
    src = p->src;
    end = src + p->count * 4;
    mask = p->mask;
    dst = p->dst;
    do {
        if (*mask != 0) {
            c = ((u32)src[0] >> p->rs) << p->rp;
            c |= ((u32)src[1] >> p->gs) << p->gp;
            c |= ((u32)src[2] >> p->bs) << p->bp;
            *dst = c;
        }
        src += 4;
        mask++;
        dst++;
    } while (src < end);
    p->dst += p->count;
}
