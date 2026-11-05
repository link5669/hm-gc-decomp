// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct Cam {
    u8 pad[48];
    void *f48;
    f32 fovy;
    f32 aspect;
    f32 l;
    f32 b;
    f32 r;
    f32 t;
    f32 n;
    f32 f;
    u8 f84[8];
    u8 f92[8];
    s32 f100;
} Cam;

typedef struct GfxTbl {
    u8 pad[416];
    void (*f416)(void *, f32 *, u8 *, u8 *, f32, f32);
    void (*f420)(void *, f32 *, u8 *, u8 *, f32, f32);
} GfxTbl;

extern GfxTbl lbl_8032C110;
extern f32 lbl_80363E60;
void fn_80103C44(Cam *c, const f32 *v);
double fn_800F03E4(double x);

void fn_80129404(Cam *c, const f32 *v) {
    f32 r, t, x, y, z, w, tv;
    fn_80103C44(c, v);
    if (c->f100 == 0) {
        y = v[1]; x = v[0]; z = v[2]; w = v[3];
        c->fovy = y;
        c->aspect = x;
        c->n = z;
        c->f = w;
        c->f100 = 0;
        tv = (f32)fn_800F03E4(lbl_80363E60 * c->fovy);
        t = tv * c->n;
        r = c->aspect * t;
        c->l = -r;
        c->r = r;
        c->b = -t;
        c->t = t;
        if (c->f100 != 0) {
            lbl_8032C110.f420(c->f48, &c->l, c->f84, c->f92, c->n, c->f);
        } else {
            lbl_8032C110.f416(c->f48, &c->l, c->f84, c->f92, c->n, c->f);
        }
    }
}

} /* extern "C" */
