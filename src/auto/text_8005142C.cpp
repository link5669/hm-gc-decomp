// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct {
    f32 x, y, z;
} Vec_8005142C;
} /* extern "C" */
struct V224_8005142C {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void f13(Vec_8005142C *, s32, s32, s32, s32);
};
extern "C" {
typedef struct {
    u8 pad0[16];
    void *f10;
    u8 pad14[12];
    u32 f20;
} B_8005142C;
typedef struct {
    u8 pad0[48];
    B_8005142C *f30;
} A_8005142C;
typedef struct {
    u8 pad0[156];
    A_8005142C *f9c;
} C_8005142C;
typedef struct {
    u8 pad0[96];
    s32 state;
    u8 pad64[120];
    s32 fdc;
    V224_8005142C *fe0;
    u8 pade4[376];
    Vec_8005142C f25c;
    f32 f268;
    C_8005142C *f26c;
    u8 pad270[8];
    s32 f278;
} Obj_8005142C;
extern f32 lbl_8035DC9C;
extern f32 lbl_8035DCA0;
extern u32 lbl_8035DC98;
extern void *lbl_803286D0[];
f32 fn_80101590(Vec_8005142C *, Vec_8005142C *);
void fn_80241588(Obj_8005142C *, s32, s32, f32);
void fn_802494A4(Obj_8005142C *, s32);
void fn_800515C4(Obj_8005142C *, s32, s32, f32);
s32 fn_8022C558(V224_8005142C *);
void fn_80190C98(A_8005142C *);
void fn_800A10D4(Obj_8005142C *, f32);

void fn_8005142C(Obj_8005142C *p, f32 dt)
{
    Vec_8005142C tmp;
    Vec_8005142C v;
    A_8005142C *a;
    B_8005142C *b;

    if (p->state == 7 && p->fdc != 4) {
        p->fe0->f13(&tmp, 0, 0, 0, 0);
        if (fn_80101590(&tmp, &p->f25c) <= p->f268) {
            fn_80241588(p, 4, 0, lbl_8035DC9C);
        }
    } else if (p->state == 5) {
        if (p->f278 != 0) {
            fn_802494A4(p, 2);
        } else {
            fn_800515C4(p, 0, 0, dt);
        }
    } else if (p->state == 11) {
        fn_800515C4(p, 0, 1, dt);
    }
    if (p->f26c != 0 && fn_8022C558(p->fe0) != 0) {
        v.x = lbl_8035DCA0;
        v.y = lbl_8035DCA0;
        v.z = lbl_8035DCA0;
        a = p->f26c->f9c;
        b = a->f30;
        if (b != 0) {
            ((void (*)(void *, Vec_8005142C *))lbl_803286D0[3])(b->f10, &v);
            b->f20 |= lbl_8035DC98;
            fn_80190C98(a);
        }
    }
    fn_800A10D4(p, dt);
}

} /* extern "C" */
