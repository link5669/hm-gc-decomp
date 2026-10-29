// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Vec { f32 x, y, z; };
struct OBase {
    u32 flags;
    u8 pad4[20];
    Vec pos;
    u8 pad36[68];
    virtual void v0(); virtual void v1(); virtual void v2();
};
struct Obj : OBase {
    u8 pad108[12];
    void *f120;
};
inline Vec &GetPos(Obj *o) {
    if (o->flags & 4) o->v2();
    return o->pos;
}
struct H { u8 pad[156]; Obj *f156; };
struct G { u8 pad[72]; H *f72; };
struct CC { u8 pad[40]; Vec col; };
struct Q { u8 pad[40]; CC *f40; };
struct S4 { u8 pad[4]; f32 f4; };
struct R { u8 pad[8]; f32 f8; u8 pad12[4]; S4 *f16; u8 pad20[16]; f32 f36; };
struct P { u8 pad[168]; Q *f168; u8 pad172[4]; R *f176; };
struct SelfF {
    u8 pad[224];
    H *f224;
    u8 pad228[72];
    f32 *f300;
    f32 *f304;
    f32 *f308;
    f32 *f312;
    u8 pad316[24];
    P *f340;
    u8 pad344[36];
    s32 f380;
};
static inline void setF8(R *r, f32 v) {
    r->f8 = v;
    if (r->f16 != 0) {
        r->f36 = r->f8 / r->f16->f4;
    }
}
extern "C" {
extern G *lbl_8035B308;
extern volatile f32 lbl_8035F910;
extern f32 lbl_8035F974;
f32 fn_80101590(Vec *, Vec *);
void fn_80107F3C(void *, Vec *);

/* the copy goes through volatile stores and lbl_8035F910 is volatile: keeps the 0.0f load below the copy */
static inline void GetFlatPos(Obj *o, Vec *out) {
    Vec &p = GetPos(o);
    volatile Vec *v = (volatile Vec *)out;
    v->x = p.x;
    v->y = p.y;
    v->z = p.z;
    v->z = lbl_8035F910;
}

void fn_8007DE14(SelfF *self) {
    Vec a;
    Vec b;
    Vec col;
    f32 x;
    f32 y;
    f32 z;
    f32 d;
    f32 t;
    f32 s;
    void *q;
    Vec *c;
    GetFlatPos(lbl_8035B308->f72->f156, &a);
    GetFlatPos(self->f224->f156, &b);
    d = fn_80101590(&b, &a);
    if (self->f380) d = lbl_8035F910;
    if (d < *self->f300) d = *self->f300;
    else if (d > *self->f304) d = *self->f304;
    t = (*self->f304 - d) / (*self->f304 - *self->f300);
    c = &self->f340->f168->f40->col;
    x = c->x;
    y = c->y;
    z = c->z;
    col.x = t * (x - lbl_8035F974) + lbl_8035F974;
    col.y = t * (y - lbl_8035F974) + lbl_8035F974;
    col.z = t * (z - lbl_8035F974) + lbl_8035F974;
    s = t * (*self->f312 - *self->f308) + *self->f308;
    q = self->f224->f156->f120;
    if (q) fn_80107F3C(q, &col);
    setF8(self->f340->f176, s);
}

} /* extern "C" */
