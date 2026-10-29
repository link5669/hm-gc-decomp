// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V { f32 x, y, z; };
struct P { u8 pad[12]; u32 n; int closed; u8 pad20[4]; V *pts; };
extern f32 lbl_80366250, lbl_80366258, lbl_80366260;
void fn_80101820(V *);
void fn_80101624(V *, V *, V *, f32);
static inline u32 nx(P *p, u32 i) { u32 j = i + 1; if (j >= p->n) j = 0; return j; }
static inline u32 pv(P *p, u32 i) {
    if (p->closed) return i ? i - 1 : p->n - 1;
    return i ? i - 1 : 0;
}
static inline void sub(V *o, V *a, V *b) { o->x = a->x - b->x; o->y = a->y - b->y; o->z = a->z - b->z; }
static inline void dir(P *p, u32 i, V *o) { u32 j = nx(p, i); sub(o, &p->pts[j], &p->pts[i]); fn_80101820(o); }
void fn_80244DC4(P *p, u32 i, V *out) {
    V d0;
    V d1;
    f32 s = lbl_80366260;
    if (p->n == 2) {
        dir(p, 0, &d1);
        d0 = d1;
    } else {
        if (!p->closed) {
            if (i == p->n - 1) s = lbl_80366250;
            if (i == 0) s = lbl_80366258;
        }
        dir(p, i, &d1);
        dir(p, pv(p, i), &d0);
    }
    fn_80101624(out, &d0, &d1, s);
}

} /* extern "C" */
