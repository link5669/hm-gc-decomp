#include "common.h"
extern "C" {
typedef struct { f32 x, y, z; } V3;
struct VO {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5();
    virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11();
    virtual void p12();
    virtual void getPos(V3 *, s32, s32, s32, s32);
    virtual void setPos(V3 *, s32, s32, s32, s32);
};
struct FT { void *a[3]; void (*f)(void *, V3 *); };
extern FT lbl_803286D0;
extern u32 lbl_8035C324, lbl_8035C320;
extern char lbl_8035C334[5];
extern f32 lbl_8035C328;
extern f32 lbl_8035C2FC, lbl_8035C300;
extern f32 lbl_8035C32C, lbl_8035C330;
void fn_80241628(void *, s32, s32);
s32 fn_80264E0C(V3 *, V3 *, V3 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void fn_80190C98(void *);
void fn_80107F3C(void *, V3 *);
void fn_80248514(void *, f32, s32);
void fn_80241DD0(void *, char *, s32, s32, s32, s32);
void fn_802494A4(void *, s32);
void fn_8023FE08(void *, f32);

#define F(T, o) (*(T *)(p + (o)))
static inline void setv(u8 *o, f32 v) { if (*(f32 **)(o + 448) != 0) **(f32 **)(o + 448) = v; }
static inline void setw(u8 *o, f32 v) { f32 *q = *(f32 **)(o + 448); if (q != 0) *q = v; }
void fn_8004058C(u8 *p, f32 dt) {
    V3 v;
    V3 pos;
    if (F(s32, 360) != 0) {
        F(s32, 360) = 0;
        F(VO *, 224)->getPos((V3 *)(p + 348), 0, 0, 0, 0);
        *(u32 *)((u8 *)F(VO *, 224) + 180) |= 4;
        fn_80241628(p, 1, 0);
    }
    if (F(s32, 364) != 0) {
        f32 *q;
        F(s32, 364) = 0;
        v = *(V3 *)(p + 348);
        v.z += *F(f32 *, 304);
        F(VO *, 224)->setPos(&v, 0, 0, 0, 0);
        setw((u8 *)F(VO *, 224), *F(f32 *, 308));
        fn_80241628(p, 1, 0);
    }
    F(s32, 336) = 0;
    F(VO *, 224)->getPos(&pos, 0, 0, 0, 0);
    if (F(void *, 340) != 0) {
        V3 a, b, res;
        f32 x = pos.x, y = pos.y, z = pos.z;
        ((f32 *)&b)[3] = x; ((f32 *)&b)[4] = y; ((f32 *)&b)[5] = z;
        a.z = z + lbl_8035C328;
        b.x = x; b.y = y; b.z = z;
        b.z -= *F(f32 *, 324);
        if (fn_80264E0C(&a, &b, &res, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1) == 0) {
            *F(u32 *, 340) &= ~0x800;
        } else {
            u8 *o;
            u8 *c;
            f32 s;
            V3 sc;
            *F(u32 *, 340) |= lbl_8035C324;
            o = F(u8 *, 340);
            c = *(u8 **)(o + 48);
            if (c != 0) {
                lbl_803286D0.f(*(void **)(c + 16), &res);
                *(u32 *)(c + 32) |= lbl_8035C320;
                fn_80190C98(o);
            }
            s = lbl_8035C300 - (pos.z - res.z) / *F(f32 *, 324);
            if (s < lbl_8035C2FC) s = (*(f32 *)&lbl_8035C2FC);
            sc.x = s; sc.y = s; sc.z = s;
            if (*(void **)(F(u8 *, 340) + 120) != 0) fn_80107F3C(*(void **)(F(u8 *, 340) + 120), &sc);
        }
    }
    if (F(s32, 96) == 2) {
        f32 t = *(f32 *)((u8 *)F(VO *, 224) + 340);
        if (t < lbl_8035C32C && F(void *, 264) != 0) fn_80248514(F(void *, 264), t / lbl_8035C32C, 0);
    }
    if (pos.z < F(f32, 356) - lbl_8035C330) {
        fn_80241DD0(p, lbl_8035C334, 0, 0, 0, 0);
        fn_802494A4(p, 0);
    }
    fn_8023FE08(p, dt);
}
}
