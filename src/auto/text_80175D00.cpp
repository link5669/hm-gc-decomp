// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V {
    u8 pad0[16];
    u32 fl;
    u32 a20;
    u8 t24, t25, t26, t27;
    u32 n28;
    u8 t32[8];
    u8 pad40[28];
    u32 a68, a72, a76, a80, a84, a88, a92;
    u8 pad96[4];
    u32 a100;
};
struct D { u32 a[12]; u32 off[8]; u32 b[8]; };
s32 fn_80101A7C(u8);

void fn_80175D00(V *v, D *d) {
    u32 off;
    u32 i;
    d->a[0] = v->a76;
    if (v->fl & 0x100) d->a[1] = fn_80101A7C(v->t24) * 4;
    else if (v->fl & 0x80) d->a[1] = fn_80101A7C(v->t24) * 3;
    else if (v->fl & 0x40) d->a[1] = fn_80101A7C(v->t24) * 2;
    else d->a[1] = 0;
    d->a[2] = v->a80;
    if (v->fl & 0x200) { s32 k = fn_80101A7C(v->t25); d->a[3] = k * v->a20; }
    else d->a[3] = 0;
    d->a[4] = v->a84;
    if (v->fl & 0x400) {
        u32 t = v->a20;
        s32 k = fn_80101A7C(v->t26);
        d->a[5] = k * (t + 1);
    } else {
        d->a[5] = 0;
    }
    d->a[6] = v->a88;
    if (v->fl & 0x800) d->a[7] = fn_80101A7C(v->t27) * 3;
    else d->a[7] = 0;
    d->a[8] = v->a68;
    if (v->fl & 0x2000) d->a[9] = 4;
    else d->a[9] = 0;
    d->a[10] = v->a72;
    if (v->fl & 0x4000) d->a[11] = 4;
    else d->a[11] = 0;
    off = v->a92;
    for (i = 0; i < v->n28; i++) {
        d->off[i] = off;
        d->b[i] = v->a100;
        if (v->fl & (0x1000000 << i)) off += fn_80101A7C(v->t32[i]) * 4;
        else if (v->fl & (0x10000 << i)) off += fn_80101A7C(v->t32[i]) * 3;
        else off += fn_80101A7C(v->t32[i]) * 2;
    }
    for (; i < 8; i++) {
        d->off[i] = 0;
        d->b[i] = 0;
    }
}

} /* extern "C" */
