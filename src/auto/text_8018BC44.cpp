#include "common.h"
#pragma explicit_zero_data on
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {
__declspec(section ".sdata2") f32 lbl_80364A70 = 0.0f;
__declspec(section ".sdata2") f32 lbl_80364A74 = 1.0f;
__declspec(section ".sdata2") f64 lbl_80364A78 = 0.5;
__declspec(section ".sdata2") f64 lbl_80364A80 = 3.0;
}

extern "C" {


extern "C" {
struct Vec { f32 x, y, z; };
struct Sph { Vec c; f32 r; };
struct Edge { u8 pad[84]; Vec *v0; Vec *v1; u8 pad2[152 - 92]; };
struct Mesh { u8 pad0[20]; s32 n; u32 flags; u8 pad3[4]; Sph s; u8 pad4[4]; Edge *edges; };
f32 fn_8010155C(Vec *a, Vec *b);

static inline void vadd(Vec *d, Vec *s) { d->x += s->x; d->y += s->y; d->z += s->z; }
static inline f32 sq(f32 x) {
    if (x > lbl_80364A70) {
        f64 guess;
        volatile f32 y;
        guess = __frsqrte((f64)x);
        guess = lbl_80364A78 * guess * (lbl_80364A80 - guess * guess * x);
        guess = lbl_80364A78 * guess * (lbl_80364A80 - guess * guess * x);
        guess = lbl_80364A78 * guess * (lbl_80364A80 - guess * guess * x);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

void fn_8018BC44(Mesh *m, Sph *out) {
    if (!(m->flags & 2)) {
        out->c.x = m->s.c.x; out->c.y = m->s.c.y; out->c.z = m->s.c.z; out->r = m->s.r;
        return;
    }
    {
        Edge *e = m->edges;
        Edge *end = e + m->n;
        f32 inv, r, d;
        m->s.c.x = lbl_80364A70;
        m->s.c.y = lbl_80364A70;
        m->s.c.z = lbl_80364A70;
        for (; e < end; e++) {
            vadd(&m->s.c, e->v0);
            vadd(&m->s.c, e->v1);
        }
        inv = lbl_80364A74 / (f32)m->n;
        m->s.c.x *= inv; m->s.c.y *= inv; m->s.c.z *= inv;
        e = m->edges;
        r = lbl_80364A70;
        for (; e < end; e++) {
            d = fn_8010155C(&m->s.c, e->v0);
            if (d > r) r = d;
            d = fn_8010155C(&m->s.c, e->v1);
            if (d > r) r = d;
        }
        m->s.r = sq(r);
        m->flags &= ~2;
        out->c.x = m->s.c.x; out->c.y = m->s.c.y; out->c.z = m->s.c.z; out->r = m->s.r;
    }
}
}

} /* extern "C" */

