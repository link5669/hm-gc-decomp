#include "common.h"
namespace N800A10D4 {

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

}
namespace N800A14F0 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

typedef struct { u32 v[2]; } T8;
void fn_800F6E88(void *, T8 *);
u32 fn_80242144(u8 *, u32);
void fn_80242BC0(u32, void *, u32, u32, void *, u32);
struct A4 { u8 pad[0xc]; s32 *data; };
struct A8 { u8 pad[0xc]; T8 *data; };

void fn_800A14F0(u8 *param_1) {
    u32 i;
    u8 auStack_28[8];
    u8 auStack_20[16];

    for (i = 0; i < *(u32 *)(param_1 + 0x1cc); i++) {
        if (*(s32 *)(param_1 + 0x1d4) == (*(A4 **)(param_1 + 0x194))->data[i]) {
            fn_800F6E88(auStack_20, &(*(A8 **)(param_1 + 0x198))->data[i]);
            fn_800F6E88(auStack_28, &(*(A8 **)(param_1 + 0x19c))->data[i]);
            fn_80242BC0(fn_80242144(param_1, i + 4), auStack_20, *(u32 *)(param_1 + 0xe0), 0, auStack_28, 0);
        }
    }
}

} /* extern "C" */

}
namespace N800A15BC {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

extern u8 lbl_80361BD4[0x4];
s32 fn_800F6CD0(int, int);
void fn_80240B50(int, int, int);

void fn_800A15BC(s32 param_1) {
    s32 iVar1;

    iVar1 = fn_800F6CD0((int)(*(u32 *)(param_1 + 0x1a4)), (int)(lbl_80361BD4));
    if (iVar1 == 0) {
        fn_80240B50((int)(param_1), (int)(*(u32 *)(param_1 + 0x1a4)), (int)(0));
    }
}

} /* extern "C" */

}
namespace N800A1608 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

struct Vec800A1608 { f32 x, y, z; };
struct Node800A1608 { u8 pad[40]; f32 x, y, z; };
struct L2_800A1608 { u8 pad[120]; Node800A1608 *node; };
struct L1_800A1608 { u8 pad[156]; L2_800A1608 *l2; };
struct St800A1608;
struct Cb800A1608 {
    u32 pad;
    virtual void f0();
    virtual void f1(St800A1608 *);
};
struct St800A1608 { u32 flags; u8 pad4[8]; Cb800A1608 *cb; u8 pad10[32]; u32 f30; };
struct Ref800A1608 { u8 pad[12]; Vec800A1608 *scale; };
struct Obj800A1608 {
    u8 pad0[224];
    L1_800A1608 *l1;
    u8 padE4[416 - 228];
    Ref800A1608 *ref;
    u8 pad1A4[528 - 420];
    u32 f210;
};

extern const u32 lbl_80361BF0;
extern f32 lbl_80361BF4;
void fn_80107F3C(Node800A1608 *, Vec800A1608 *);
St800A1608 *fn_8022D694(L1_800A1608 *);

void fn_800A1608(Obj800A1608 *o) {
    Vec800A1608 v;
    Node800A1608 *n;
    Vec800A1608 sc;
    St800A1608 *st;
    o->f210 = 0;
    n = o->l1->l2->node;
    if (n != 0) {
        v.x = n->x;
        v.y = n->y;
        v.z = n->z;
    } else {
        v.x = lbl_80361BF4;
        v.y = lbl_80361BF4;
        v.z = lbl_80361BF4;
    }
    sc = *o->ref->scale;
    v.x = v.x / sc.x;
    v.y = v.y / sc.y;
    v.z = v.z / sc.z;
    n = o->l1->l2->node;
    if (n != 0) {
        fn_80107F3C(n, &v);
    }
    st = fn_8022D694(o->l1);
    if (st->f30 & 1) {
        st->flags |= lbl_80361BF0;
        if (st->cb != 0) {
            st->cb->f1(st);
        }
    }
}

} /* extern "C" */

}
namespace N800A1710 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

typedef struct { f32 x, y, z; } V800A1710;
typedef struct { u8 pad[40]; V800A1710 scale; } O800A1710;
typedef struct { u8 pad[120]; O800A1710 *f78; } B800A1710;
typedef struct { u8 pad[156]; B800A1710 *f9C; } A800A1710;
typedef struct { u8 pad[12]; V800A1710 *fC; } C800A1710;
typedef struct { u8 pad[16]; u32 f10; } E800A1710;
typedef struct { u8 b[8]; } N800A1710;
typedef struct { E800A1710 *f0; u8 pad4[8]; N800A1710 *fC; } D800A1710;
typedef struct { u32 f0; u8 pad4[44]; u32 f30; } Q800A1710;
typedef struct S800A1710 {
    u8 pad0[224];
    A800A1710 *fE0;
    u8 padE4[396 - 228];
    D800A1710 *f18C;
    u8 pad190[416 - 400];
    C800A1710 *f1A0;
    u8 pad1A4[528 - 420];
    s32 f210;
} S800A1710;
extern f32 lbl_80361BF4;
extern N800A1710 lbl_80361BD4;
void fn_80107F3C(O800A1710 *, V800A1710 *);
u32 rand(void);
void fn_800F6E88(N800A1710 *, N800A1710 *);
s32 fn_800F6CD0(N800A1710 *, N800A1710 *);
void fn_802410CC(S800A1710 *, N800A1710 *, s32);
Q800A1710 *fn_8022D694(A800A1710 *);

void fn_800A1710(S800A1710 *p) {
    N800A1710 name;
    V800A1710 v;
    O800A1710 *o;
    V800A1710 *s;
    f32 sx, sy, sz;
    u32 n;
    u32 r;
    Q800A1710 *q;
    p->f210 = 1;
    o = p->fE0->f9C->f78;
    if (o != 0) {
        v.x = o->scale.x;
        v.y = o->scale.y;
        v.z = o->scale.z;
    } else {
        v.x = lbl_80361BF4;
        v.y = lbl_80361BF4;
        v.z = lbl_80361BF4;
    }
    s = p->f1A0->fC;
    sx = s->x;
    sy = s->y;
    sz = s->z;
    v.x *= sx;
    v.y *= sy;
    v.z *= sz;
    o = p->fE0->f9C->f78;
    if (o != 0) {
        fn_80107F3C(o, &v);
    }
    n = p->f18C->f0->f10;
    if (n != 0) {
        r = rand();
        fn_800F6E88(&name, &p->f18C->fC[r % n]);
        if (fn_800F6CD0(&name, &lbl_80361BD4) == 0) {
            fn_802410CC(p, &name, 0);
        }
    }
    q = fn_8022D694(p->fE0);
    if (q->f30 & 1) {
        q->f0 &= ~2;
    }
}

} /* extern "C" */

}
namespace N800A1860 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {



extern "C" {

struct V { f32 x, y, z; };
struct P {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void pos(V *, int, int, int, int);
};
struct S { u8 pad[216]; s32 f216; };
struct G : P { u8 pad4[276]; f32 x, y, z; u8 pad292[232]; S *f524; };
struct GM { u8 pad[72]; G *f72; };
struct T { u8 pad[224]; P *f224; u8 pad228[160]; f32 *f388; f32 *f392; };
extern GM *lbl_8035B308;
extern f32 lbl_80361BD0;
extern f64 lbl_80361BF8, lbl_80361C00;

static inline f32 Sq(f32 x) {
    if (x > lbl_80361BD0) {
        const f64 _half = lbl_80361BF8;
        const f64 _three = lbl_80361C00;
        volatile f32 y;
        f64 g = __frsqrte((f64)x);
        g = _half * g * (_three - g * g * x);
        g = _half * g * (_three - g * g * x);
        g = _half * g * (_three - g * g * x);
        y = x * g;
        return y;
    }
    return x;
}

s32 fn_800A1860(T *o) {
    s32 r = 0;
    G *g = lbl_8035B308->f72;
    if (g->f524->f216 != 1) {
        f32 x = g->x, y = g->y, z = g->z;
        f32 d = Sq(x * x + y * y + z * z);
        if (d > lbl_80361BD0) {
            V a, b;
            lbl_8035B308->f72->pos(&a, 0, 0, 0, 0);
            o->f224->pos(&b, 0, 0, 0, 0);
            if ((f32)__fabs((f64)(b.z - a.z)) <= *o->f392) {
                f32 dx, dy, dz;
                dz = b.z - b.z;
                dy = b.y - a.y;
                *(volatile f32 *)&a.z = b.z;
                dx = *(volatile f32 *)&b.x - a.x;
                if (Sq(dx * dx + dy * dy + dz * dz) <= *o->f388) r = 1;
            }
        }
    }
    return r;
}

}

} /* extern "C" */

}
namespace N800A1A44 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

s32 fn_80242144(int, int);
void fn_80242BC0(int, int, int, int, int, int);
void fn_802494A4(int, int);

void fn_800A1A44(s32 param_1) {
    u32 uVar1;

    if (**(s32 **)(param_1 + 0x140) != 0) {
        fn_802494A4((int)(param_1), (int)(3));
    }
    uVar1 = fn_80242144((int)(param_1), (int)(3));
    fn_80242BC0((int)(uVar1), (int)(*(u32 *)(param_1 + 0x130)), (int)(*(u32 *)(param_1 + 0xe0)), (int)(0), (int)(*(u32 *)(param_1 + 0x134)), (int)(0));
}

} /* extern "C" */

}
namespace N800A1AA8 {

extern "C" {
typedef struct V3 { f32 x, y, z; } V3;
struct VO {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void v13(V3 *a, V3 *b, V3 *c, V3 *d, s32 e);
    virtual void v14(V3 *a, s32 b, s32 c, s32 d, s32 e);
};
typedef struct G1 { u8 pad[188]; f32 f188; } G1;
typedef struct G { u8 pad[4]; G1 *f4; } G;
typedef struct M { u8 pad[72]; VO *f72; } M;
typedef struct T {
    u8 pad0[192]; G *f192; u8 p1[224 - 196]; VO *f224; u8 p2[284 - 228];
    f32 *f284; f32 *f288; u8 p3[296 - 292]; f32 *f296; u8 p4[340 - 300]; s32 *f340; f32 *f344;
    u8 p5[360 - 348]; s32 *f360; u8 p6[424 - 364]; f32 f424; u8 p7[432 - 428]; f32 f432; s32 f436;
    u8 p8[448 - 440]; s32 f448; u8 p9[456 - 452]; s32 f456; u8 p10[464 - 460]; u32 f464; u32 f468;
    u8 p11[508 - 472]; s32 *f508; s32 *f512; void *f516;
} T;
extern "C" {
extern M *lbl_8035B308;
extern f32 lbl_803596E0[];
extern f32 lbl_80361BD0;
extern f32 lbl_80361C08;
extern f64 lbl_80361C10;
extern f32 lbl_80361C18;
extern f32 lbl_80361C1C;
int rand(void);
void fn_80101820(V3 *);
f32 fn_80101590(V3 *, V3 *);
V3 *fn_80245F8C(void *, u32);
void fn_80245E58(void *, u32, V3 *);
f64 fn_800F045C(f64);
void fn_8023F5E8(T *, s32);
void fn_80257A4C(G1 *, V3 *);
void fn_80241628(T *, s32, s32);
}
static inline bool zle(T *self, V3 *e, V3 *pos) {
    f32 d = (f32)__fabs(pos->z - e->z);
    return d <= *self->f344;
}
static inline bool zok(T *self, V3 *e, V3 *pos) {
    return *self->f340 || (!*self->f340 && zle(self, e, pos));
}
static inline f32 Acos(f32 x) {
    if ((f32)__fabs(x) <= lbl_80361C10) return (f32)fn_800F045C(x);
    if (x > lbl_80361BD0) return lbl_80361BD0;
    return lbl_80361C18;
}
static inline u32 pickIdx(u32 n) { u32 p = 0; if (n) p = (u32)rand() % n; return p; }
#pragma push
#pragma opt_common_subs off
extern "C" void fn_800A1AA8(T *self) {
    V3 pos;
    V3 dir;
    V3 tmp;
    V3 p2;
    V3 d;
    u32 cnt;
    u32 i;
    f32 thr;
    s32 found;
    u32 n;
    self->f224->v13(&pos, &dir, 0, 0, 0);
    fn_80101820(&dir);
    cnt = 0;
    if (!self->f456 || !*self->f360) fn_80245F8C(self->f516, self->f468);
    for (i = 0; i < self->f464; i++) {
        V3 *e = fn_80245F8C(self->f516, i);
        u8 vis = 0;
        bool near = i != self->f468 && fn_80101590(e, &pos) <= self->f424;
        if (near) {
            if (zok(self, e, &pos)) vis = 1;
        }
        self->f508[i] = vis;
        self->f512[i] = vis;
        if (vis) cnt++;
    }
    self->f448 = self->f436;
    if (!self->f464) return;
    if (!((!self->f448 && self->f432 > lbl_80361BD0) || (self->f448 && *self->f296 > lbl_80361BD0))) return;
    {
        if (cnt == 0 || (self->f456 && *self->f360)) {
            u32 bi = 0;
            u32 bj = 0;
            f32 bd = lbl_803596E0[0];
            f32 bd2 = bd;
            for (i = 0; i < self->f464; i++) {
                f32 dd = fn_80101590(fn_80245F8C(self->f516, i), &pos);
                if (i != self->f468) {
                    if (dd < bd) { bi = i; bd = dd; }
                    if (dd < bd2) {
                        if ((f32)__fabs(pos.z - fn_80245F8C(self->f516, i)->z) <= *self->f344) { bj = i; bd2 = dd; }
                    }
                }
            }
            if (!*self->f340 && bd2 != lbl_803596E0[0]) {
                self->f508[bj] = 1;
                self->f512[bj] = 1;
            } else {
                self->f508[bi] = 1;
                self->f512[bi] = 1;
            }
            if (self->f456 && *self->f360) {
                if (!*self->f340 && bd2 != lbl_803596E0[0]) self->f468 = bj;
                else self->f468 = bi;
                fn_80245E58(self->f516, self->f468, &tmp);
                self->f224->v14(&tmp, 0, 0, 0, 0);
                self->f456 = 0;
                fn_800A1AA8(self);
                return;
            }
        }
        if (self->f436) {
            lbl_8035B308->f72->v13(&p2, 0, 0, 0, 0);
            dir.x = p2.x - pos.x;
            dir.y = p2.y - pos.y;
            dir.z = p2.z - pos.z;
            fn_80101820(&dir);
        }
        thr = self->f448 ? *self->f284 : lbl_80361C08;
        G1 *g0 = self->f192->f4;
        g0->f188 = self->f448 ? *self->f296 : self->f432;
        found = 0;
        n = 0;
        while (!found) {
            n = 0;
            for (i = 0; i < self->f464; i++) {
                if (self->f508[i]) {
                    V3 *e = fn_80245F8C(self->f516, i);
                    s32 ok;
                    d.x = pos.x - e->x;
                    d.y = pos.y - e->y;
                    d.z = pos.z - e->z;
                    fn_80101820(&d);
                    ok = lbl_80361C1C * Acos(dir.x * d.x + dir.y * d.y + dir.z * d.z) <= thr;
                    self->f512[i] = ok;
                    if (ok) { found = 1; n++; }
                }
            }
            if (!found) thr += *self->f288;
        }
        {
            u32 pick;
            u32 k;
            pick = pickIdx(n);
            for (i = 0, k = 0; i < self->f464; i++) {
                if (self->f512[i]) {
                    if (k == pick) {
                        V3 *e = fn_80245F8C(self->f516, i);
                        G1 *g = self->f192->f4;
                        fn_8023F5E8(self, 0);
                        fn_80257A4C(g, e);
                        self->f468 = i;
                        if (g->f188 > lbl_80361BD0) fn_80241628(self, 1, 0);
                        else { self->f224->v14(e, 0, 0, 0, 0); self->f448 = 0; }
                        return;
                    }
                    k++;
                }
            }
        }
    }
}
#pragma pop
}

}
namespace N800A210C {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

s32 fn_80242144(int, int);
void fn_80242BC0(int, int, int, int, int, int);

u32 fn_800A210C(s32 param_1) {
    u32 uVar1;

    uVar1 = 0;
    if ((*(u32 *)(param_1 + 0x1d0) == 0) ||
          (*(u32 *)(param_1 + 0x1d4) == *(u32 *)(param_1 + 0x1d0) + -1)) {
        uVar1 = fn_80242144((int)(param_1), (int)(1));
        fn_80242BC0((int)(uVar1), (int)(*(u32 *)(param_1 + 300)), (int)(*(u32 *)(param_1 + 0xe0)), (int)(0), (int)(0), (int)(0));
        uVar1 = 1;
    }
    return uVar1;
}

} /* extern "C" */

}
namespace N800A217C {
/* Functions from 0x800A217C to 0x800A2198, found by decomp-toolkit. */


extern "C" void fn_800A217C(u8* arg0) {
    *(f32*)(arg0 + 0x1A8) = **(f32**)(arg0 + 0x118);
    **(f32**)(arg0 + 0x14C) = *(f32*)(arg0 + 0x1AC);
}

}
namespace N800A2198 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

extern char lbl_80361C20[8];
s32 fn_800F6CD0(void *, const char *);
void fn_800F6E40(void *, void *);
double fn_800EB838(void *);

void fn_800A2198(u8 *p) {
    if (fn_800F6CD0(*(void **)(p + 236), lbl_80361C20) != 0) {
        **(f32 **)(p + 332) = *(f32 *)(p + 428);
    } else {
        u8 buf[12];
        fn_800F6E40(buf, *(void **)(p + 236));
        **(f32 **)(p + 332) = fn_800EB838(buf);
    }
}

} /* extern "C" */

}
namespace N800A2204 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

extern char lbl_80361C20[8];
s32 fn_800F6CD0(void *, const char *);
void fn_800F6E40(void *, void *);
double fn_800EB838(void *);

void fn_800A2204(u8 *p) {
    if (fn_800F6CD0(*(void **)(p + 236), lbl_80361C20) != 0) {
        *(f32 *)(p + 424) = **(f32 **)(p + 280);
    } else {
        u8 buf[12];
        fn_800F6E40(buf, *(void **)(p + 236));
        *(f32 *)(p + 424) = fn_800EB838(buf);
    }
}

} /* extern "C" */

}
namespace N800A226C {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

} /* extern "C" */
typedef struct V3 { f32 x, y, z; } V3;
struct X156 { u8 pad[120]; void *f120; };
struct VO {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void v13(V3 *a, s32 b, s32 c, s32 d, s32 e);
    virtual void v14(V3 *a, s32 b, s32 c, s32 d, s32 e);
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23();
    virtual void v24();
    u8 pad[152]; X156 *f156; u8 pad2[276 - 160]; s32 f276;
};
extern "C" {
typedef struct S5 { s32 a, b, c, d, e; } S5;
extern S5 lbl_8029A8B8;
extern S5 lbl_8029A8CC;
extern char lbl_80361BD4[8];
extern f32 lbl_80361BCC;
extern f32 lbl_80361BD0;
extern f32 lbl_80361BD8;
extern f32 lbl_80361C28;
extern f64 lbl_80361C30;
extern f32 lbl_80361BF4;
extern u32 lbl_8035B530;
typedef struct L { u8 pad[20]; s32 f20; } L;
extern L lbl_803575DC;
typedef struct O { u8 pad[48]; void *f48; } O;
typedef struct R0 { u8 pad[16]; u32 f16; } R0;
typedef struct R { R0 *f0; } R;
typedef struct G1 { u8 pad[188]; f32 f188; } G1;
typedef struct G { u8 pad[4]; G1 *f4; } G;
typedef struct W { u8 pad[12]; u32 f12; } W;
typedef struct T { u8 p0[192]; G *f192; u8 p196[28]; VO *f224; u8 p228[52]; f32 *f280; u8 p284[28]; s32 *f312; u8 p316[8]; s32 f324; u8 p328[4]; f32 *f332; u8 p336[12]; f32 *f348; f32 *f352; s32 f356; u8 p360[4]; s32 *f364; u8 p368[8]; f32 *f376; f32 *f380; u8 p384[24]; R *f408; R *f412; u8 p416[8]; f32 f424; f32 f428; f32 f432; u8 p436[4]; s32 f440; u8 p444[4]; s32 f448; u8 p452[4]; s32 f456; u32 f460; u32 f464; s32 f468; V3 f472; V3 f484; V3 f496; u32 *f508; u32 *f512; W *f516; O *f520; f32 f524; } T;
int rand(void);
s32 fn_800F6CD0(s32 a, char *t);
void fn_8023FA2C(T *self, O **p, S5 s);
void fn_8023F764(T *self, O **p, S5 s);
void fn_80240DBC(T *self, f32 v);
W *fn_80247AE4(L *l, s32 a);
W *fn_80240028(T *self);
void fn_800604C4(int, int, int, int);
void fn_800F7EC0(u32);
void fn_800F7E98(void);
V3 *fn_80245F8C(W *w, s32 i);
void fn_80107F3C(void *, V3 *);

static inline int isZero(V3 *v) { return v->x == lbl_80361BD0 && v->y == lbl_80361BD0 && v->z == lbl_80361BD0; }
static inline bool canGo(T *s) { bool r = *s->f312 != 0; if (r) r = s->f224->f276 == 0; return r; }

static inline void acq(T *self) {
    if (fn_800F6CD0(self->f324, lbl_80361BD4) == 0) {
        S5 s;
        self->f520 = 0;
        s = lbl_8029A8B8;
        s.a = self->f324;
        fn_8023FA2C(self, &self->f520, s);
    }
}
static inline void acq2(T *self) { acq(self); }
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
void fn_800A226C(T *self) {
    self->f456 = 1;
    self->f468 = 0;
    self->f448 = 0;
    if (isZero(&self->f472)) {
        self->f224->v13(&self->f472, 0, 0, 0, 0);
    } else {
        self->f224->v14(&self->f472, 0, 0, 0, 0);
    }
    if (canGo(self)) {
        self->f224->v23();
        acq2(self);
        if (*self->f364 != 0) {
            self->f524 = lbl_80361BD0;
        } else {
            s32 ri = rand() % 10000u;
            f32 t = lbl_80361BD8 * (f32)ri;
            f32 d = *self->f380 - *self->f376;
            t = d * t + *self->f376;
            self->f524 = t;
        }
        self->f440 = 1;
    } else {
        self->f224->v24();
        rel(self);
        self->f440 = 0;
    }
    if (fn_800F6CD0(self->f356, lbl_80361BD4) == 0 && lbl_803575DC.f20 != 0) {
        self->f516 = fn_80247AE4(&lbl_803575DC, self->f356);
    }
    if (self->f516 == 0) self->f516 = fn_80240028(self);
    self->f464 = self->f516->f12;
    if (self->f508 == 0) {
        if (lbl_8035B530 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B530);
        self->f508 = new u32[self->f464];
        fn_800F7E98();
        if (self->f508 == 0) fn_800604C4(-4, 0, 0, 0);
        if (lbl_8035B530 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B530);
        self->f512 = new u32[self->f464];
        fn_800F7E98();
        if (self->f512 == 0) fn_800604C4(-4, 0, 0, 0);
    }
    {
        G1 *g = self->f192->f4;
        if (self->f432 < lbl_80361BD0) {
            self->f432 = g->f188;
        } else {
            g->f188 = self->f432;
        }
    }
    if (self->f464 != 0) {
        V3 *a = fn_80245F8C(self->f516, 0);
        self->f484.x = a->x; self->f484.y = a->y; self->f484.z = a->z;
        a = fn_80245F8C(self->f516, self->f464 - 1);
        self->f496.x = a->x; self->f496.y = a->y; self->f496.z = a->z;
    }
    if (self->f408->f0->f16 < self->f460) self->f460 = self->f408->f0->f16;
    if (self->f412->f0->f16 < self->f460) self->f460 = self->f412->f0->f16;
    self->f424 = *self->f280;
    self->f428 = *self->f332;
    {
        u32 r = 0;
        u32 n = (u32)(lbl_80361C28 * (*self->f352 - *self->f348));
        V3 s;
        void *m;
        if (n) r = rand() % n;
        {
            f32 q = (f32)(s32)r / lbl_80361C30;
            f32 v = *self->f348 + q;
            s.z = s.y = s.x = lbl_80361BF4;
            s.x *= v; s.y *= v; s.z *= v;
        }
        m = self->f224->f156->f120;
        if (m) fn_80107F3C(m, &s);
    }
}

} /* extern "C" */

}
namespace N800A27B0 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

typedef struct { s32 a, b, c, d, e; } P5;
void fn_8023F764(void *p, void *h, P5 prm);
void fn_80240DBC(void *p, f32 f);
extern f32 lbl_80361BCC;
extern const P5 lbl_8029A8CC;
struct V800A27B0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void m();
};

static inline void helper(u8 *p, void *h, s32 x) {
    P5 prm = lbl_8029A8CC;
    prm.a = x;
    fn_8023F764(p, h, prm);
}
void fn_800A27B0(u8 *p) {
    (*(V800A27B0 **)(p + 224))->m();
    if (*(void **)(p + 520) != 0) {
        helper(p, p + 520, *(s32 *)(p + 324));
        *(void **)(p + 520) = 0;
        fn_80240DBC(p, lbl_80361BCC);
    }
    *(s32 *)(p + 440) = 0;
}

} /* extern "C" */

}
namespace N800A2870 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).


extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V_800A2870 {
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
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
};
extern "C" {
typedef struct { u32 a, b, c, d, e; } S20_800A2870;

extern char lbl_80361BD4[4];
extern S20_800A2870 lbl_8029A8B8;
extern f32 lbl_80361BD0;
extern volatile f32 lbl_80361BD8;
s32 fn_800F6CD0(void *, char *);
void fn_8023FA2C(u8 *, u32 *, S20_800A2870);
int rand(void);
static inline S20_800A2870 MakeS(u32 a) { S20_800A2870 s = lbl_8029A8B8; s.a = a; return s; }
static inline s32 RandI(s32 n) { return (u32)rand() % n; }
static inline f32 RandF(void) { return lbl_80361BD8 * (f32)RandI(10000); }


void fn_800A2870(u8 *p) {
    (*(V_800A2870 **)(p + 224))->v23();
    if (fn_800F6CD0(*(void **)(p + 324), lbl_80361BD4) == 0) {
        *(u32 *)(p + 520) = 0;
        fn_8023FA2C(p, (u32 *)(p + 520), MakeS(*(u32 *)(p + 324)));
    }
    if (**(s32 **)(p + 364) != 0) {
        *(f32 *)(p + 524) = lbl_80361BD0;
    } else {
        *(f32 *)(p + 524) = **(f32 **)(p + 376) + (**(f32 **)(p + 380) - **(f32 **)(p + 376)) * RandF();
    }
    *(s32 *)(p + 440) = 1;
}

} /* extern "C" */

}
