// fn_800FD530: box (half extents) vs sphere: vector from box surface to sphere surface, returns signed distance.
// Register-equivalent (regequiv.txt): the zero constant lbl_80363740 and one product sit in swapped FPRs (GC/2.6).
#include "common.h"

extern "C" {

extern f32 lbl_80363740;
extern const f64 lbl_80363748;
extern const f64 lbl_80363750;

typedef struct { f32 x, y, z; } V3_800FD530;
typedef struct { V3_800FD530 c; V3_800FD530 e; } Box_800FD530;
typedef struct { V3_800FD530 c; f32 r; } Sph_800FD530;

void fn_80101744(V3_800FD530 *out, const V3_800FD530 *in);
f32 fn_80101664(V3_800FD530 *v);

static inline f32 sqrtf_800FD530(f32 x) {
    volatile f32 y;
    if (x > lbl_80363740) {
        f64 _half = lbl_80363748;
        f64 _three = lbl_80363750;
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

#define Z2 (*(f32 *)&lbl_80363740)
static inline f64 FA(f64 x) { return __fabs(x); }

f32 fn_800FD530(Box_800FD530 *a, Sph_800FD530 *__restrict p, V3_800FD530 *out, f32 *o1, f32 *o2) {
    V3_800FD530 d;
    f32 ax, ay, az;
    f32 s;
    int neg = 0;

    ax = FA(p->c.x);
    ay = FA(p->c.y);
    az = FA(p->c.z);
    *(volatile f32 *)&d.x = ax - a->e.x;
    *(volatile f32 *)&d.y = ay - a->e.y;
    *(volatile f32 *)&d.z = az - a->e.z;
    *o1 = *o2 = *(volatile f32 *)&lbl_80363740;
    if (d.x <= lbl_80363740 && d.y <= lbl_80363740 && d.z <= lbl_80363740) {
        d.x = -d.x;
        d.y = -d.y;
        d.z = -d.z;
        f32 nx = d.x, ny = d.y;
        if (nx < ny) {
            f32 nz = d.z;
            if (nz < nx) {
                out->x = lbl_80363740;
                s = -nz - p->r;
                out->y = lbl_80363740;
                out->z = s;
            } else {
                out->x = -nx - p->r;
                out->y = lbl_80363740;
                out->z = lbl_80363740;
            }
        } else {
            f32 nz = d.z;
            if (nz < ny) {
                out->x = lbl_80363740;
                s = -nz - p->r;
                out->y = lbl_80363740;
                out->z = s;
            } else {
                s = -ny - p->r;
                out->x = lbl_80363740;
                out->y = s;
                out->z = lbl_80363740;
            }
        }
    } else {
        if (d.x <= Z2) {
            if (d.y <= Z2) {
                s = d.z - p->r;
                out->x = Z2;
                out->y = Z2;
                out->z = s;
            } else if (d.z <= Z2) {
                s = d.y - p->r;
                out->x = Z2;
                out->y = s;
                out->z = Z2;
            } else {
                fn_80101744(out, &d);
                s = sqrtf_800FD530(d.y * d.y + d.z * d.z) - p->r;
                out->x *= s;
                out->y *= s;
                out->z *= s;
            }
        } else if (d.y <= Z2) {
            if (d.z <= Z2) {
                s = d.x - p->r;
                out->x = s;
                out->y = Z2;
                out->z = Z2;
            } else {
                fn_80101744(out, &d);
                s = sqrtf_800FD530(d.x * d.x + d.z * d.z) - p->r;
                out->x *= s;
                out->y *= s;
                out->z *= s;
            }
        } else if (d.z <= Z2) {
            fn_80101744(out, &d);
            s = sqrtf_800FD530(d.x * d.x + d.y * d.y) - p->r;
            out->x *= s;
            out->y *= s;
            out->z *= s;
        } else {
            fn_80101744(out, &d);
            s = sqrtf_800FD530(d.x * d.x + d.y * d.y + d.z * d.z) - p->r;
            out->x *= s;
            out->y *= s;
            out->z *= s;
        }
        neg = s < Z2;
    }
    if (p->c.x < ax) out->x = -out->x;
    if (p->c.y < ay) out->y = -out->y;
    if (p->c.z < az) out->z = -out->z;
    if (neg) return -fn_80101664(out);
    return fn_80101664(out);
}

}
