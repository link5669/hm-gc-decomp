#include "common.h"

extern "C" {

struct Desc { u8 d[28]; };
struct VL { f32 *p; u32 stride; u8 pad8[40]; f32 *uv; u8 pad52[28]; u32 uvstride; u8 pad84[32]; };
struct IL { u16 *p; };
struct Buf { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void lockV(Desc *, int, VL *); virtual void setN(int); virtual void s7(); virtual void s8(); virtual void lockI(int, IL *); virtual void unlock(int); virtual int draw(void *, void *, int, u8 *); };
struct Mk { u8 pad_[48]; virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual Buf *make(); };
extern f32 lbl_80364100;
extern f32 lbl_80364104;
void fn_8014CA08(Desc *);
void fn_8014C8C8(Desc *, u32, int, int);
static inline void corner(VL *v, f32 cx, f32 cy, f32 cz, f32 ex, f32 ey, f32 ez) {
    { f32 *q = v->p; q[0] = cx; q[1] = cy; q[2] = cz; }
    v->p[0] = v->p[0] + ex;
    v->p[1] = v->p[1] + ey;
    v->p[2] = v->p[2] + ez;
    v->p = (f32 *)((u8 *)v->p + v->stride);
}
static inline void uv(VL *v, int a, int b) {
    v->uv[0] = a ? lbl_80364104 : lbl_80364100;
    v->uv[1] = b ? lbl_80364104 : lbl_80364100;
    v->uv = (f32 *)((u8 *)v->uv + v->uvstride);
}
static inline void tri(IL *l, u16 a, u16 b, u16 c) { *l->p++ = a; *l->p++ = b; *l->p++ = c; }
int fn_801351AC(Mk **__restrict o, f32 *__restrict box, void *__restrict q, u8 fl) {
    u8 f = fl;
    IL il;
    Desc d;
    VL v;
    Buf *b;
    f32 ez, ey, ex, cz, cy, cx;
    fn_8014CA08(&d);
    fn_8014C8C8(&d, 0xa080, 0, 1);
    b = (*o)->make();
    b->lockV(&d, 8, &v);
    b->lockI(36, &il);
    { f32 *q = v.p; cx = box[0]; cy = box[1]; cz = box[2];
    ex = box[3]; ey = box[4]; ez = box[5]; q[0] = cx; q[1] = cy; q[2] = cz; }
    v.p[0] = v.p[0] + ex;
    v.p[1] = v.p[1] + ey;
    v.p[2] = v.p[2] + ez;
    v.p = (f32 *)((u8 *)v.p + v.stride);
    corner(&v, cx, cy, cz, ex, -ey, ez);
    corner(&v, cx, cy, cz, -ex, ey, ez);
    corner(&v, cx, cy, cz, -ex, -ey, ez);
    corner(&v, cx, cy, cz, ex, ey, -ez);
    corner(&v, cx, cy, cz, ex, -ey, -ez);
    corner(&v, cx, cy, cz, -ex, ey, -ez);
    corner(&v, cx, cy, cz, -ex, -ey, -ez);
    uv(&v, 0, 1);
    uv(&v, 0, 0);
    uv(&v, 1, 1);
    uv(&v, 1, 0);
    uv(&v, 0, 1);
    uv(&v, 0, 0);
    uv(&v, 1, 1);
    uv(&v, 1, 0);
    tri(&il, 0, 1, 2); tri(&il, 1, 3, 2); tri(&il, 3, 1, 7); tri(&il, 1, 5, 7);
    tri(&il, 1, 0, 5); tri(&il, 0, 4, 5); tri(&il, 0, 2, 4); tri(&il, 2, 6, 4);
    tri(&il, 2, 3, 6); tri(&il, 3, 7, 6); tri(&il, 6, 7, 4); tri(&il, 7, 5, 4);
    b->unlock(36);
    b->setN(8);
    return b->draw(o, q, 1, &f);
}
}
