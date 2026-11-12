#include "common.h"
extern "C" {
} /* extern "C" */
typedef struct V3 { f32 x, y, z; } V3;
struct VO {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void v13(V3 *a, V3 *b, V3 *c, V3 *d, s32 e);
    virtual void v14(s32 k, s32 a, s32 b, s32 c, s32 d);
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23();
    virtual void v24();
};
extern "C" {
struct FT { u8 pad[12]; void (*f12)(void *, V3 *); u8 pad16[12]; void (*f28)(void *, V3 *, V3 *, V3 *); };
extern FT lbl_803286D0;
typedef struct S5 { s32 a, b, c, d, e; } S5;
extern S5 lbl_8029A8CC;
extern char lbl_8029A8E0[];
extern char lbl_80361BD4[8];
extern char lbl_80361BDC[8];
extern f32 lbl_80361BCC;
extern f32 lbl_80361BD0;
extern f32 lbl_80361BD8;
extern u32 lbl_80361BC8;
typedef struct Q { u8 pad[16]; void *f16; u8 pad2[12]; u32 f32_; } Q;
typedef struct O { u8 pad[48]; Q *f48; } O;
typedef struct R0 { u8 pad[16]; u32 f16; } R0;
typedef struct R { R0 *f0; u8 pad[8]; u8 *f12; } R;
typedef struct G1 { u8 pad[188]; f32 f188; } G1;
typedef struct G { u8 pad[4]; G1 *f4; } G;
typedef struct T {
    u8 pad0[192]; G *f192; u8 p1[224 - 196]; VO *f224; u8 p2[324 - 228]; s32 f324; f32 *f328;
    u8 p3[364 - 332]; s32 *f364; s32 *f368; s32 *f372; f32 *f376; f32 *f380; s32 *f384;
    u8 p4[400 - 388]; R *f400; u8 p5[436 - 404]; s32 f436; s32 f440; u8 p6[448 - 444]; s32 f448; s32 f452;
    u8 p7[468 - 456]; s32 f468; u8 p8[516 - 472]; s32 f516; O *f520; f32 f524; s32 f528;
} T;
typedef struct Str { u8 pad[8]; } Str;
int rand(void);
s32 fn_8022C558(VO *o);
void fn_8023F764(T *self, O **p, S5 s);
void fn_80240DBC(T *self, f32 v);
void fn_80190C98(O *o);
void fn_80241DD0(T *self, char *name, s32 a, s32 b, s32 c, s32 d);
s32 fn_80245F8C(s32 a, s32 b);
void fn_800F6E88(Str *s, u8 *p);
s32 fn_800F6CD0(Str *s, char *t);
void fn_80240B50(T *self, Str *s, s32 v);
s32 fn_800A1860(T *self);
void fn_8023FE08(T *self, f32 dt);

static inline void rel(T *self) {
        if (self->f520 != 0) {
            S5 s;
            s = lbl_8029A8CC;
            s.a = self->f324;
            fn_8023F764(self, &self->f520, s);
            self->f520 = 0;
            fn_80240DBC(self, lbl_80361BCC);
        }
}
static inline void pickLoop(T *self, u32 i, u32 pick) {
    for (; i < self->f400->f0->f16; i++) {
                    Str s;
                    fn_800F6E88(&s, self->f400->f12 + i * 8);
                    if (fn_800F6CD0(&s, lbl_80361BD4) == 0 && (*self->f372 == 0 || (*self->f372 != 0 && i == pick))) {
                        fn_80240B50(self, &s, *self->f364);
                        {
                            s32 ri = rand() % 10000u;
                            f32 t = lbl_80361BD8 * (f32)ri;
                            f32 d = *self->f380 - *self->f376;
                            t = d * t + *self->f376;
                            self->f524 = t;
                        }
                    }
                }
}
void fn_800A10D4(T *self, f32 dt) {
Q *q;
u32 n;
u32 i;
u32 pick;
u32 vA;
#define o ((O *)vA)
#define off vA

    if (self->f440 == 0 && fn_8022C558(self->f224)) {
        self->f224->v24();
        rel(self);
        self->f440 = 0;
    }
    if (self->f440 != 0 && self->f452 != 0) {
        if (self->f520 != 0) {
            V3 a, b, c, d;
            self->f224->v13(&a, &b, &c, &d, 0);
            a.z += *self->f328;
            {
                vA = (u32)self->f520;
                q = o->f48;
                if (q) {
                    lbl_803286D0.f12(q->f16, &a);
                    q->f32_ |= lbl_80361BC8;
                    fn_80190C98(o);
                }
            }
            {
                vA = (u32)self->f520;
                q = o->f48;
                if (q) {
                    lbl_803286D0.f28(q->f16, &b, &c, &d);
                    q->f32_ |= lbl_80361BC8;
                    fn_80190C98(o);
                }
            }
        }
        if (self->f436 != 0 && self->f448 == 0) {
            fn_80241DD0(self, lbl_8029A8E0, 0, 0, 0, 0);
        } else if (lbl_80361BD0 == self->f192->f4->f188) {
            s32 k = fn_80245F8C(self->f516, self->f468);
            self->f224->v14(k, 0, 0, 0, 0);
        }
    }
    if (self->f440 != 0) {
        self->f524 -= dt;
        if (self->f524 < *(f32 *)&lbl_80361BD0) {
            self->f524 = lbl_80361BD0;
            if (self->f400 != 0 && *self->f368 != 0) {
                pick = 0;
                n = self->f400->f0->f16;
                if (n) pick = rand() % n;
                pickLoop(self, 0, pick);

            }
        }
        if (*self->f384 != 0 && self->f528 == 0 && fn_800A1860(self)) {
            fn_80241DD0(self, lbl_80361BDC, 0, 0, 0, 0);
        }
    }
    fn_8023FE08(self, dt);
}
#undef o
#undef off
}
