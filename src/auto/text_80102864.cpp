// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct Q4 { f32 x, y, z, w; };
struct V3 { f32 x, y, z; };
struct QE { f32 wt; Q4 q; };
struct VE { f32 wt; V3 v; };
struct A { QE *q; VE *v; VE *s; u32 n12; u32 n16; int slerp; };
struct W { f32 *q; f32 *v; f32 *s; };
extern f32 lbl_80363864;
void fn_80100060(Q4 *, Q4 *, Q4 *, f32);
void fn_80100104(Q4 *, Q4 *, Q4 *, f32);
void fn_80101624(V3 *, V3 *, V3 *, f32);
static inline void bq(A *a, QE *d, QE *s, f32 w) {
    if (lbl_80363864 != d->wt) {
        d->wt += w;
        f32 f = w / d->wt;
        if (a->slerp) fn_80100060(&d->q, &d->q, &s->q, f);
        else fn_80100104(&d->q, &d->q, &s->q, f);
    } else {
        d->wt = w;
        d->q = s->q;
    }
}
static inline void bv(VE *d, VE *s, f32 w) {
    if (lbl_80363864 != d->wt) {
        d->wt += w;
        fn_80101624(&d->v, &d->v, &s->v, w / d->wt);
    } else {
        d->wt = w;
        d->v = s->v;
    }
}
void fn_80102864(A *a, A *b, W *wts, f32 base) {
    u32 i;
    QE *dq;
    QE *sq;
    VE *dv;
    VE *sv;
    dq = a->q;
    dv = a->v;
    f32 w = base;
    sq = b->q;
    sv = b->v;
    for (i = 0; i < a->n12; i++) {
        if (wts) w = base * wts->q[i];
        bq(a, dq, sq, w);
        bv(dv, sv, w);
        dq++; dv++; sq++; sv++;
    }
    VE *ds = a->s;
    VE *ss = b->s;
    for (i = 0; i < a->n16; i++) {
        if (wts) w = base * wts->s[i];
        bv(ds, ss, w);
        ds++; ss++;
    }
}

} /* extern "C" */
