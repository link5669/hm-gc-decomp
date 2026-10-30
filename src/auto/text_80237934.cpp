// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V { f32 x, y, z; };
extern f32 lbl_80365EFC, lbl_80365F08, lbl_80365F40, lbl_80365F50, lbl_80365F54, lbl_80365F58;
extern f64 lbl_80365F28, lbl_80365F30, lbl_80365F48;

f64 fn_800F045C(f64);
struct O { u32 f0; u8 pad4[20]; V pos; u8 pad36[68]; virtual void a0(); virtual void a1(); virtual void upd(); };
struct T { virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3(); virtual void t4(); virtual void t5(); virtual void t6(); virtual void t7(); virtual void t8(); virtual void t9(); virtual void t10(); virtual void t11(); virtual void t12(); virtual void get(int, V *, void *, int, int); u8 pad4[152]; O *f156; u8 pad160[296]; f32 *f456; f32 *f460; };
void fn_80100F24(V *, void *);
void fn_80101820(V *);
int fn_80264E0C(V *, V *, void *, int, int, int, void **, int, int, int, int, int, int, int, int);
static inline f32 Sq(f32 x) {
    if (x > lbl_80365EFC) {
        const f64 _half = lbl_80365F28;
        const f64 _three = lbl_80365F30;
        volatile f32 y;
        f64 g = __frsqrte((f64)x);
        g = _half * g * (_three - g * g * x);
        g = _half * g * (_three - g * g * x);
        g = _half * g * (_three - g * g * x);
        y = (f32)(x * g);
        return y;
    }
    return x;
}
int fn_80237934(T *t, V *tgt, int cone, int dist, void *arg) {
    O *o = t->f156;
    if (o->f0 & 4) o->upd();
    V p;
    V fwd;
    u8 m[12];
    V d;
    p.x = o->pos.x;
    p.y = o->pos.y;
    p.z = o->pos.z;
    t->get(0, &fwd, m, 0, 0);
    f32 pz, py, px;
    d.x = px = tgt->x - p.x;
    d.y = py = tgt->y - p.y;
    d.z = pz = tgt->z - p.z;
    if (dist) {
        f32 a = px * px;
        f32 b = py * py;
        f32 c = pz * pz;
        f32 l = Sq(c + (a + b));
        f32 mx = t->f456 ? *t->f456 : lbl_80365F40;
        if (l > mx) return 0;
    }
    fn_80100F24(&d, m);
    fn_80101820(&d);
    if (cone) {
        f32 c = fwd.x * d.x + fwd.y * d.y + fwd.z * d.z;
        f32 ang;
        if ((f32)__fabs((f64)c) <= lbl_80365F48) ang = fn_800F045C(c);
        else if (c > lbl_80365EFC) ang = lbl_80365EFC;
        else ang = lbl_80365F50;
        f64 da = __fabs((f64)ang);
        f32 aa = (f32)da;
        f32 lim = t->f460 ? lbl_80365F08 * (lbl_80365F54 * *t->f460) : lbl_80365F58;
        if (aa > lim) return 0;
    }
    if (!fn_80264E0C(&p, tgt, arg, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)) return 1;
    return 0;
}

} /* extern "C" */
