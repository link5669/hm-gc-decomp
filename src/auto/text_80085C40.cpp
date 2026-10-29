// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V { f32 x, y, z; };
struct M { f32 m[4]; };
struct FT { u8 pad[12]; void (*f12)(void *, V *); u8 pad16[288]; void (*f304)(void *, V *); };
extern FT lbl_803286D0;
struct P { u8 pad[16]; void *f16; u8 pad20[12]; u32 f32; };
struct Q16 { u8 pad[68]; f32 f68; };
struct Q108 { u8 pad[16]; Q16 *f16; };
struct O { u8 pad[48]; P *f48; u8 pad52[56]; Q108 *f108; };
struct S156 { u8 pad[48]; P *f48; u8 pad52[52]; virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15(); virtual void set(M *); };
struct S888 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void go(); };
struct E52 { u8 pad[52]; };
struct G5E4 { u8 pad[104]; int f104; u8 pad108[4]; E52 *f112; };
extern G5E4 *lbl_8035B5E4;
extern f32 lbl_8035FDF4, lbl_8035FDF8, lbl_8035FDFC, lbl_8035FE00, lbl_8035FE04;
extern const u32 lbl_8035FDF0;
struct T;
extern T *lbl_8035A1A8;
struct T {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    u8 pad4[152]; S156 *f156; u8 pad160[544]; O *f704; u8 pad708[40]; O *f748; u8 pad752[132]; u8 f884; u8 pad885[3]; S888 *f888; u8 pad892[24]; f32 *f916;
};
void fn_80253304(E52 *, int, f32);
void fn_8005D6D0(T *, int, int, int);
void fn_80100CF4(M *);
void fn_80190C98(O *);
static inline void setPos(O *o, V *p) {
    P *q = o->f48;
    if (q) {
        lbl_803286D0.f12(q->f16, p);
        q->f32 |= lbl_8035FDF0;
        fn_80190C98(o);
    }
}
void fn_80085C40(T *t, int a, int b, int c) {
    V p;
    M m;
    O *o1;
    P *q1;
    O *o2;
    P *q2;
    if (t->f884 & 1) return;
    t->f888->go();
    fn_80253304(&lbl_8035B5E4->f112[lbl_8035B5E4->f104], 500, lbl_8035FDF4);
    fn_8005D6D0(t, a, b, c);
    fn_80100CF4(&m);
    m.m[3] = *t->f916;
    t->f156->set(&m);
    t->v17();
    P *q = t->f156->f48;
    if (q) lbl_803286D0.f304(q->f16, &p);
    else p.z = p.y = p.x = lbl_8035FDF8;
    p.z = p.z + lbl_8035FDFC;
    {
    o1 = t->f704;
    q1 = o1->f48;
    if (q1) {
        lbl_803286D0.f12(q1->f16, &p);
        q1->f32 |= lbl_8035FDF0;
        fn_80190C98(o1);
    }
    }
    p.z = p.z + lbl_8035FE00;
    o2 = t->f748;
    if (o2 && lbl_8035A1A8 == t) {
        q2 = o2->f48;
        if (q2) {
            lbl_803286D0.f12(q2->f16, &p);
            q2->f32 |= lbl_8035FDF0;
            fn_80190C98(o2);
        }
        t->f748->f108->f16->f68 = t->f748->f108->f16->f68 / lbl_8035FE04;
    }
    t->f884 |= 1;
}

} /* extern "C" */
