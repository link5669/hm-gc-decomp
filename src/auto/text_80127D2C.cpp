// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct D { u8 pad0[2]; u16 bits; u8 pad4[28]; virtual void d0(); virtual void d1(); virtual void d2(); virtual int which(); };
struct T { u8 pad[16]; u32 n; };
int fn_80127D2C(T *t, u32 *v, D *d, u8 *p, int stride, int x) {
    u32 i;
    u32 *q;
    switch (d->bits) {
    case 4:
        if (x ^ d->which()) {
            for (i = 0, q = v; i < t->n; i++, q++) {
                if ((u32)(*p & 0xF) != *q) return 0;
                p += stride;
            }
        } else {
            for (i = 0, q = v; i < t->n; i++, q++) {
                if ((u32)(*p >> 4) != *q) return 0;
                p += stride;
            }
        }
        return 1;
    case 8:
        for (i = 0; i < t->n; i++) {
            if (*p != v[i]) return 0;
            p += stride;
        }
        return 1;
    case 16:
        for (i = 0; i < t->n; i++) {
            if (*(u16 *)p != v[i]) return 0;
            p += stride;
        }
        return 1;
    case 24:
        for (i = 0; i < t->n; i++) {
            if ((u32)(p[0] | (p[1] << 8) | (p[2] << 16)) != v[i]) return 0;
            p += stride;
        }
        return 1;
    case 32:
        for (i = 0; i < t->n; i++) {
            if (*(u32 *)p != v[i]) return 0;
            p += stride;
        }
        return 1;
    }
    return 1;
}

} /* extern "C" */
