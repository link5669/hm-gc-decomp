// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Ray;
struct N {
    u8 pad[8];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(f32 t, Ray *ray, void *x);
};
extern "C" {
typedef struct Ray {
    void *f0;
    f32 f4;
    f32 f8;
    f32 f12;
    f32 f16;
} Ray;
typedef struct Node {
    u8 pad[12];
    N *f12;
    N *f16;
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f32_;
} Node;
extern f32 lbl_80364C60;
void *fn_8019BAB8(void *a);
void fn_80195208(void *x, void *y);

static inline f32 pdist(const Node *n, const Ray *r) {
    return r->f4 * n->f20 + r->f8 * n->f24 + r->f12 * n->f28 + n->f32_;
}
void fn_8019860C(Node *self, Ray *ray, void *x, f32 t) {
    f32 dist = pdist(self, ray);
    if (dist < -t) {
        dist = -dist - t;
        self->f16->v8(t, ray, x);
    } else if (dist >= t) {
        dist = dist - t;
        self->f12->v8(t, ray, x);
    } else {
        void *y = fn_8019BAB8(ray->f0);
        if (y == 0) {
            self->f12->v8(t, ray, x);
            return;
        }
        fn_80195208(x, y);
        if (dist < lbl_80364C60) {
            dist = -dist;
            self->f16->v8(t, ray, x);
            self->f12->v8(t, ray, y);
        } else {
            self->f16->v8(t, ray, y);
            self->f12->v8(t, ray, x);
        }
    }
    if (dist < ray->f16) ray->f16 = dist;
}

} /* extern "C" */
