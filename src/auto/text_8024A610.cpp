#include "common.h"

extern "C" {

struct V { f32 x, y, z; };
struct Pr { s32 a, b; };
struct Prs { Pr p[3]; };
struct S { V p[3]; V v[3]; f32 rest[3]; f32 ground; s32 hit[3]; s32 active; };
extern const Prs lbl_802A9238;
f32 lbl_80366340 = 10000.0f;
f32 lbl_80366344 = 2.0f;
f32 lbl_80366348 = 0.01f;
f32 lbl_8036634C = 0.0001f;
f32 lbl_80366350 = 100.0f;
f32 lbl_80366354 = 10.0f;
f32 lbl_80366358 = 0.2f;
f32 lbl_8036635C = 1.0f;
f32 lbl_80366360 = 8.0f;
int rand(void);
f32 fn_80101590(V *, V *);
void fn_80101820(V *);

static inline u32 rmod(u32 n) { u32 r = 0; if (n != 0) r = rand() % n; return r; }
static inline f32 rndr(s32 n) {
    if (n < 0) return lbl_8036634C * (f32)-(s32)rmod(-n);
    return lbl_8036634C * (f32)(s32)rmod(n);
}
static inline f32 rf(u32 n) { return lbl_8036634C * (f32)(s32)rmod(n); }
static inline f32 jit() { return (f32)((s32)rmod(10) - 5) / lbl_80366354; }

#pragma opt_loop_invariants off
void fn_8024A610(S *s, V *c, V *d, f32 r, f32 g) {
    Prs pr = lbl_802A9238;
    V v;
    s32 n;
    u32 i, j = 0;
    n = (s32)(lbl_80366340 * (lbl_80366344 * (lbl_80366348 * r)));
    for (i = 0; i < 3; i++) {
        s->p[i].x = lbl_80366350 * rndr(n) + c->x - r;
        s->p[i].y = lbl_80366350 * rndr(n) + c->y - r;
        s->p[i].z = lbl_80366350 * rndr(n) + c->z - r;
        if (d) {
            s->v[i].x = d->x + jit();
            s->v[i].y = d->y + jit();
            s->v[i].z = d->z + jit();
            fn_80101820(&s->v[i]);
        } else {
            f32 x, y, z;
            z = rf(12000) - lbl_80366358;
            y = rf(20000) - lbl_8036635C;
            x = rf(20000) - lbl_8036635C;
            v.y = y; v.z = z; v.x = x;
            fn_80101820(&v);
            v.x *= lbl_80366360; v.y *= lbl_80366360; v.z *= lbl_80366360;
            s->v[i].x = v.x + jit();
            s->v[i].y = v.y + jit();
            s->v[i].z = v.z + jit();
        }
        s->hit[i] = j;
    }
    for (; j < 3; j++) {
        s->rest[j] = fn_80101590(&s->p[pr.p[j].a], &s->p[pr.p[j].b]);
    }
    s->ground = g;
    s->active = 1;
}

}
