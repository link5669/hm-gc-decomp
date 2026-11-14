#include "common.h"

namespace n802405B8 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
extern "C" {
struct V { f32 x, y, z; };
extern f32 lbl_8036613C;
extern char lbl_802A8D48[];
extern char lbl_8036615C[8], lbl_80366164[8], lbl_8036616C[8], lbl_80366174[8], lbl_8036617C[8];
extern void *lbl_8035B65C;
f32 fn_802539FC(void *);
struct A { virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3(); virtual void q4(); virtual void q5(); virtual void q6(); virtual void q7(); virtual void q8(); virtual void q9(); virtual void q10(); virtual void q11(); virtual void q12(); virtual void probe(int, V *, int, int, int); u8 pad[420]; f32 f424; f32 f428; u8 pad432[8]; int *f440; };
struct B;
struct S { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void probe(int, V *, int, int, int); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void say(const char *, void *, int, void *, int); };
struct B { u8 pad0[280]; V n; u8 pad292[308]; f32 f600; int *f604; u8 pad608[16]; S *f624; };
struct G { u8 pad[72]; void *f72; };
extern G *lbl_8035B308;
struct T { u8 pad[184]; int f184; u8 pad188[36]; A *f224; B *f228; u32 f232; u32 f236; u32 f240; };
void fn_80249A18(T *, const char *);
static inline void go(T *t, B *b, const char *s) {
    if (t->f184) {
        t->f228 = b;
        t->f232 = 0;
        t->f236 = 0;
        t->f240 = 0;
        fn_80249A18(t, s);
    }
}
static inline int Num(A *a) { return a->f440 ? *a->f440 : 0; }
static inline int Is1(int *p) { if (p == 0) return 0; return *p == 1; }
void fn_802405B8(T *t) {
    char *str = lbl_802A8D48;
    f32 nx, ny, nz;
    B *b = t->f228;
    if (b->f624 == (S *)t->f224) return;
    if (Num(t->f224) < 0) return;
    f32 d = b->f600;
    if (Is1(b->f604)) d -= Num(t->f224);
    if (d <= lbl_8036613C) return;
    f32 dt = fn_802539FC(lbl_8035B65C);
    if (lbl_8035B308->f72 == t->f224) {
        f32 v = -d;
        v = v * dt;
        ((S *)lbl_8035B308->f72)->say(lbl_80366174, t->f228, 0, &v, 0);
    } else {
        A *a = t->f224;
        d = d / dt;
        a->f428 = a->f428 - d;
        if (a->f428 > a->f424) a->f428 = a->f424;
    }
    if (t->f224->f428 <= lbl_8036613C) {
        go(t, t->f228, lbl_8036615C);
        if (lbl_8035B308->f72 == b->f624) b->f624->say(str + 0xb0, t->f224, 0, 0, 0);
        if (lbl_8035B308->f72 == t->f224 && b->f624) b->f624->say(str + 0xbc, 0, 0, 0, 0);
        return;
    }
    V v;
    nx = b->n.x; ny = b->n.y; nz = b->n.z;
    t->f224->probe(0, &v, 0, 0, 0);
    if (v.x * nx + v.y * ny + v.z * nz <= lbl_8036613C) go(t, t->f228, str + 0xa4);
    else go(t, t->f228, lbl_80366164);
    go(t, t->f228, lbl_8036616C);
    if (lbl_8035B308->f72 == t->f224 && b->f624) b->f624->say(lbl_8036617C, 0, 0, 0, 0);
}
}
} /* namespace n802405B8 */

namespace n80240948 {
#pragma push
#pragma use_lmw_stmw on
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct O80240948 {
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
    virtual void v14(f32 t);
};
struct Q80240948 {
    u8 pad[20];
    s32 f20;
};
struct M80240948 {
    u8 pad[256];
    Q80240948 *f256;
};
struct P80240948 {
    u8 pad[128];
    s32 count;
    u8 pad2[192 - 132];
    u32 *objs;
    void **names;
    u8 pad3[224 - 200];
    u8 *f224;
};
extern "C" {
extern char lbl_80366190[6];
extern char lbl_802A8E10[9];
extern u8 *lbl_8035B308;
extern f32 lbl_8036613C;
void fn_800F6FBC(void *obj, char *buf);
s32 fn_800F6F00(char *a, char *b);
void *fn_80247AE4(Q80240948 *q, void *a);
void fn_802635C0(void *o, void *x);
void fn_80263528(void *o, void *y);

static inline Q80240948 *GetQ80240948(M80240948 *m) {
    Q80240948 *q = 0;
    if (m) q = m->f256;
    return q;
}
static inline void *Find80240948(Q80240948 *q, void *a) {
    void *r = 0;
    if (q->f20) r = fn_80247AE4(q, a);
    return r;
}

void fn_80240948(P80240948 *p, void *a, void *b) {
    O80240948 *o;
    s32 i;
    char buf[16];
    for (i = 0; i < p->count; i++) {
        fn_800F6FBC(p->names[i], buf);
        if (fn_800F6F00(buf, lbl_80366190) == 0 || fn_800F6F00(buf, lbl_802A8E10) == 0) {
            u32 v = p->objs[i];
            if (v != 0) {
                M80240948 *m = *(M80240948 **)(*(u8 **)(*(u8 **)(lbl_8035B308 + 72) + 600) + 524);
                if (m != 0 && m->f256 != 0) {
                    void *r;
                    o = (O80240948 *)v;
                    r = Find80240948(GetQ80240948(m), a);
                    if (r != 0) {
                        fn_802635C0(o, r);
                        fn_80263528(o, b);
                        o->v11();
                        o->v14(lbl_8036613C);
                        *(s32 *)(p->f224 + 576) = 1;
                    }
                }
            }
        }
    }
}

} /* extern "C" */
#pragma pop
} /* namespace n80240948 */

namespace n80240A8C {
#pragma push
#pragma use_lmw_stmw on
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

extern char lbl_80366190[6];
extern char lbl_802A8E10[9];
void fn_800F6FBC(void *obj, char *buf);
s32 fn_800F6F00(char *a, char *b);
void *fn_80247AD4(void *a, void *b);
void fn_802635C0(void *o, void *x);
void fn_80263528(void *o, void *y);

typedef struct P80240A8C {
    u8 pad[128];
    s32 count;
    u8 pad2[192 - 132];
    u32 *objs;
    void **names;
    u8 pad3[256 - 200];
    void *f256;
    void *f260;
} P80240A8C;
void fn_80240A8C(P80240A8C *p, void *x, void *y) {
    void *o;
    s32 i;
    char buf[16];
    p->f260 = x;
    for (i = 0; i < p->count; i++) {
        fn_800F6FBC(p->names[i], buf);
        if (fn_800F6F00(buf, lbl_80366190) == 0 || fn_800F6F00(buf, lbl_802A8E10) == 0) {
            if (p->objs[i] != 0) {
                o = (void *)p->objs[i];
                fn_802635C0(o, fn_80247AD4(p->f256, p->f260));
                fn_80263528(o, y);
            }
        }
    }
}

} /* extern "C" */
#pragma pop
} /* namespace n80240A8C */

namespace n80240B50 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

extern void *lbl_8035B7BC;
extern f32 lbl_8036613C;
extern f32 lbl_80366198;
void *fn_8026D254(void *, void *);
void fn_80107244(void *, void *);
void fn_802482F8(void *, s32, s32);
void fn_80248668(void *, void *, s32, void *, void *, f32);

void fn_80240B50(u8 *p, void *a, void *b) {
    void *r = fn_8026D254(lbl_8035B7BC, a);
    if (r != NULL && *(void **)(p + 264) != NULL) {
        f32 v[3];
        u8 *t = *(u8 **)(*(u8 **)(p + 224) + 156);
        if (t != NULL) {
            void *x = *(void **)(t + 48);
            if (x != NULL) {
                fn_80107244(x, v);
            } else {
                v[0] = lbl_8036613C;
                v[1] = lbl_8036613C;
                v[2] = lbl_8036613C;
            }
        }
        if (*(s32 **)(p + 164) != NULL) {
            fn_802482F8(*(void **)(p + 264), 0, **(s32 **)(p + 164));
        } else {
            fn_802482F8(*(void **)(p + 264), 0, 2);
        }
        fn_80248668(*(void **)(p + 264), r, 0, v, b, lbl_80366198);
    }
}

} /* extern "C" */
} /* namespace n80240B50 */

namespace n80240C2C {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

typedef struct {
    u8 pad[8];
    void *data;
} E80240C2C;

typedef struct {
    u8 pad[48];
    void *obj;
} C80240C2C;

typedef struct {
    u8 pad[156];
    C80240C2C *c;
} B80240C2C;

typedef struct {
    u8 pad0[164];
    s32 *mode;
    u8 pad1[204 - 168];
    E80240C2C *entries;
    u8 pad2[212 - 208];
    void **items;
    u8 pad3[224 - 216];
    B80240C2C *b;
    u8 pad4[264 - 228];
    void *player;
} P80240C2C;

extern f32 lbl_8036613C;
extern f32 lbl_80366198;
void fn_80107244(void *, f32 *);
void fn_802482F8(void *, s32, s32);
void fn_80248668(void *, void *, s32, f32 *, void *, f32);

void fn_80240C2C(P80240C2C *p, s32 i) {
    void *a;
    void *b;
    C80240C2C *c;
    f32 v[3];
    b = p->entries[i].data;
    a = p->items[i];
    if (a != 0 && p->player != 0) {
        c = p->b->c;
        if (c != 0) {
            if (c->obj != 0) {
                fn_80107244(c->obj, v);
            } else {
                v[0] = lbl_8036613C;
                v[1] = lbl_8036613C;
                v[2] = lbl_8036613C;
            }
        }
        if (p->mode != 0) {
            fn_802482F8(p->player, 0, *p->mode);
        } else {
            fn_802482F8(p->player, 0, 2);
        }
        fn_80248668(p->player, a, 0, v, b, lbl_80366198);
    }
}

} /* extern "C" */
} /* namespace n80240C2C */

namespace n80240D18 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

void fn_80248790(int);

void fn_80240D18(s32 param_1) {
    if (*(void **)(param_1 + 0x108) != 0) {
        fn_80248790((int)(*(void **)(param_1 + 0x108)));
    }
}

} /* extern "C" */
} /* namespace n80240D18 */

namespace n80240D44 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

void fn_802487B4(int);

void fn_80240D44(s32 param_1) {
    if (*(void **)(param_1 + 0x108) != 0) {
        fn_802487B4((int)(*(void **)(param_1 + 0x108)));
    }
}

} /* extern "C" */
} /* namespace n80240D44 */

namespace n80240D70 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

void fn_802487D8(int, int, int);

void fn_80240D70(s32 param_1, s32 param_2) {
    u32 uVar1;

    if (*(u32 *)(param_1 + 0x108) != 0) {
        uVar1 = 0;
        if (param_2 != -1) {
            uVar1 = *(u32 *)(*(u32 *)(param_1 + 0xd4) + param_2 * 4);
        }
        fn_802487D8((int)(*(u32 *)(param_1 + 0x108)), (int)(0), (int)(uVar1));
    }
}

} /* extern "C" */
} /* namespace n80240D70 */

namespace n80240DBC {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

void fn_80248820(int, int);

void fn_80240DBC(s32 param_1) {
    if (*(u32 *)(param_1 + 0x108) != 0) {
        fn_80248820((int)(*(u32 *)(param_1 + 0x108)), (int)(0));
    }
}

} /* extern "C" */
} /* namespace n80240DBC */

namespace n80240DEC {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

typedef struct { f32 x, y, z; } Vec;
typedef struct E12 { u32 f0; u32 f4; u32 f8; } E12;
typedef struct Q9C { u8 pad[0x30]; void *f30; } Q9C;
typedef struct QE0 { u8 pad[0x9C]; Q9C *f9C; } QE0;
typedef struct P80240DEC {
    u8 pad0[0xA4]; u32 *fA4; u8 padA8[0xCC - 0xA8]; E12 *fCC; u8 padD0[4]; u32 *fD4;
    u8 padD8[0xE0 - 0xD8]; QE0 *fE0; u8 padE4[0x108 - 0xE4]; void *f108;
} P80240DEC;
u32 rand(void);
void fn_80107244(void *, Vec *);
void fn_802482F8(void *, s32, u32);
void fn_802488C4(void *, u32, s32, Vec *, u32, f32);
extern f32 lbl_8036613C;
extern f32 lbl_80366198;

void fn_80240DEC(P80240DEC *p, s32 chance, s32 lo, s32 hi) {
    u32 range;
    s32 r;
    u32 b;
    u32 a;
    void *obj;
    Vec v;
    if ((s32)(rand() % 100) < chance) {
        r = 0;
        range = hi - lo + 1;
        if (range != 0) {
            r = rand() % range;
        }
        a = p->fCC[lo + r].f8;
        b = p->fD4[lo + r];
        if (p->f108 != 0) {
            obj = p->fE0->f9C->f30;
            if (obj != 0) {
                fn_80107244(obj, &v);
            } else {
                v.x = lbl_8036613C;
                v.y = lbl_8036613C;
                v.z = lbl_8036613C;
            }
            if (p->fA4 != 0) {
                fn_802482F8(p->f108, 0, *p->fA4);
            } else {
                fn_802482F8(p->f108, 0, 2);
            }
            fn_802488C4(p->f108, b, 0, &v, a, lbl_80366198);
        }
    }
}

} /* extern "C" */
} /* namespace n80240DEC */

namespace n80240F24 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

/* QV=2.0p1 */
typedef struct { f32 x, y, z; } Vec;
typedef struct { u32 a, b, c; } E12;

extern f32 lbl_8036613C;
extern f32 lbl_80366198;
int rand(void);
void fn_80107244(void *, Vec *);
void fn_802482F8(void *, s32, s32);
void fn_802488C4(void *, u32, s32, Vec *, u32, f32);

void fn_80240F24(u8 *p, s32 lo, s32 hi) {
    s32 idx;
    u32 s;
    u32 c;
    Vec v;
    {
        u32 range = hi - lo + 1;
        u32 r = 0;
        if (range != 0) r = (u32)rand() % range;
        idx = lo + r;
    }
    c = (*(E12 **)(p + 204))[idx].c;
    s = (*(u32 **)(p + 212))[idx];
    if (*(void **)(p + 264) == 0) return;
    {
        void *o = *(void **)(*(u8 **)(*(u8 **)(p + 224) + 156) + 48);
        if (o != 0) {
            fn_80107244(o, &v);
        } else {
            v.x = lbl_8036613C;
            v.y = lbl_8036613C;
            v.z = lbl_8036613C;
        }
    }
    if (*(s32 **)(p + 164) != 0) {
        fn_802482F8(*(void **)(p + 264), 0, **(s32 **)(p + 164));
    } else {
        fn_802482F8(*(void **)(p + 264), 0, 2);
    }
    fn_802488C4(*(void **)(p + 264), s, 0, &v, c, lbl_80366198);
}

} /* extern "C" */
} /* namespace n80240F24 */

namespace n80241028 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

extern u8 lbl_80366138[0x1];
extern const f32 lbl_80366198;
s32 strcmp(int, int);
void fn_80248A68(f32, int, int);

void fn_80241028(s32 param_1, u32 param_2) {
    s32 iVar1;

    iVar1 = strcmp((int)(param_2), (int)(lbl_80366138));
    if ((iVar1 != 0) && (*(u32 *)(param_1 + 0x108) != 0)) {
        fn_80248A68(lbl_80366198, (int)(*(u32 *)(param_1 + 0x108)), (int)(param_2));
    }
}

} /* extern "C" */
} /* namespace n80241028 */

namespace n80241088 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

extern const f32 lbl_80366198;
void fn_80248A14(int, int, f32);

void fn_80241088(s32 param_1, s32 param_2) {
    if ((*(u32 *)(*(u32 *)(param_1 + 0xd4) + param_2 * 4) != 0) && (*(u32 *)(param_1 + 0x108) != 0)) {
        fn_80248A14((int)(*(u32 *)(param_1 + 0x108)), (int)(*(u32 *)(*(u32 *)(param_1 + 0xd4) + param_2 * 4)), lbl_80366198);
    }
}

} /* extern "C" */
} /* namespace n80241088 */

namespace n802410CC {

extern "C" {

extern u8 lbl_80366138[0x1];
extern const f32 lbl_80366198;
s32 strcmp(void *, void *);
void fn_80248B54(f32, void *, void *, s32, u32);

void fn_802410CC(u8 *param_1, void *param_2, u32 param_3) {
    s32 iVar1;

    iVar1 = strcmp(param_2, lbl_80366138);
    if ((iVar1 != 0) && (*(void **)(param_1 + 0x108) != 0)) {
        fn_80248B54(lbl_80366198, *(void **)(param_1 + 0x108), param_2, 0, param_3);
    }
}

} /* extern "C" */
} /* namespace n802410CC */

namespace n80241140 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

extern const f32 lbl_80366198;
void fn_80248AF4(f32, int, int, int, int);

void fn_80241140(u32 param_1, u32 param_2) {
    u32 iVar1;

    iVar1 = *(u32 *)(*(u32 *)(param_1 + 0xd4) + param_2 * 4);
    if ((iVar1 != 0) && (*(u32 *)(param_1 + 0x108) != 0)) {
        fn_80248AF4(lbl_80366198, (int)(*(u32 *)(param_1 + 0x108)), (int)(iVar1), (int)(0), (int)(0));
    }
}

} /* extern "C" */
} /* namespace n80241140 */

namespace n8024118C {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

extern void *lbl_8035B7BC;
extern f32 lbl_8036613C;
extern f32 lbl_80366198;
void *fn_8026D254(void *, void *);
void fn_80107244(void *, void *);
void fn_802482F8(void *, s32, s32);
void fn_802488C4(void *, void *, s32, void *, void *, f32);

void fn_8024118C(u8 *p, void *a, void *b) {
    void *r = fn_8026D254(lbl_8035B7BC, a);
    if (*(void **)(p + 264) != NULL) {
        f32 v[3];
        void *x = *(void **)(*(u8 **)(*(u8 **)(p + 224) + 156) + 48);
        if (x != NULL) {
            fn_80107244(x, v);
        } else {
            v[0] = lbl_8036613C;
            v[1] = lbl_8036613C;
            v[2] = lbl_8036613C;
        }
        if (*(s32 **)(p + 164) != NULL) {
            fn_802482F8(*(void **)(p + 264), 0, **(s32 **)(p + 164));
        } else {
            fn_802482F8(*(void **)(p + 264), 0, 2);
        }
        fn_802488C4(*(void **)(p + 264), r, 0, v, b, lbl_80366198);
    }
}

} /* extern "C" */
} /* namespace n8024118C */

namespace n8024125C {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

void fn_80107244(void *, f32 *);
void fn_802482F8(void *, s32, s32);
void fn_802488C4(void *, u32, s32, f32 *, u32, f32);
extern f32 lbl_8036613C;
extern f32 lbl_80366198;
typedef struct { u32 f0, f4, f8; } E12;

void fn_8024125C(u8 *p, s32 i) {
    u32 y, x;
    f32 v[3];
    u8 *q;
    x = (*(E12 **)(p + 204))[i].f8;
    y = (*(u32 **)(p + 212))[i];
    if (*(u8 **)(p + 264) != NULL) {
        q = *(u8 **)(*(u8 **)(*(u8 **)(p + 224) + 156) + 48);
        if (q != NULL) {
            fn_80107244(q, v);
        } else {
            v[0] = lbl_8036613C;
            v[1] = lbl_8036613C;
            v[2] = lbl_8036613C;
        }
        if (*(u32 **)(p + 164) != NULL) {
            fn_802482F8(*(u8 **)(p + 264), 0, **(u32 **)(p + 164));
        } else {
            fn_802482F8(*(u8 **)(p + 264), 0, 2);
        }
        fn_802488C4(*(u8 **)(p + 264), y, 0, v, x, lbl_80366198);
    }
}

} /* extern "C" */
} /* namespace n8024125C */

namespace n80241338 {
#pragma push
#pragma use_lmw_stmw on
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

extern void *lbl_8035B7BC;
extern char lbl_802A8E1C[];
s32 fn_800F6CD0(void *, void *);
void *fn_8026D254(void *, void *);
void fn_800E8F6C(char *, const char *, ...);

void fn_80241338(u8 *p, void *a, void *b) {
    char buf[100];
    s32 i;
    for (i = 0; i < *(s32 *)(p + 0x84); i++) {
        if (fn_800F6CD0(((void **)*(u8 **)(p + 0xCC))[i * 3], a) != 0) {
            (*(void ***)(p + 0xD4))[i] = fn_8026D254(lbl_8035B7BC, b);
            return;
        }
    }
    fn_800E8F6C(buf, lbl_802A8E1C, a, b);
}

} /* extern "C" */
#pragma pop
} /* namespace n80241338 */

namespace n802413D8 {
#pragma push
#pragma use_lmw_stmw on
#include <string.h>

#define F(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern "C" {
extern void *lbl_8035B308;
extern f32 lbl_8036613C;
void fn_800F6E40(char *, char *);
void fn_8022CC44(void *, void *, s32, f32, bool, s32, s32, f32);
void *fn_8022D694(void *);
int stricmp(const char *, const char *);
}

struct O {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual bool vf(s32);
};

static inline s32 GetFlag() { return F(F(F(lbl_8035B308, void *, 72), void *, 600), s32, 768); }
static inline void Hit(O *o, s32 i, f32 f, s32 b, s32 c, f32 *pf, s32 flag) {
    F(o, s32, 220) = i;
    F(F(o, void *, 224), f32, 416) = lbl_8036613C;
    if (pf && !flag) {
        void *e = F(o, void **, 208)[i];
        fn_8022CC44(F(o, void *, 224), e, 1, f, o->vf(i), b, c, *pf);
    } else {
        void *e = F(o, void **, 208)[i];
        fn_8022CC44(F(o, void *, 224), e, 1, f, o->vf(i), b, c, lbl_8036613C);
    }
    if (flag) {
        u16 h = F(F(o, void **, 208)[i], u16, 52);
        void *z = fn_8022D694(F(o, void *, 224));
        F(z, f32, 4) = (f32)(h - 1);
    }
}
extern "C" void fn_802413D8(O *o, char *name, f32 f, s32 b, s32 c, f32 *pf) {
    char key[12];
    char tmp[12];
    s32 flag;
    s32 i;
    flag = GetFlag();
    if (flag) {
        b = 1;
        f = lbl_8036613C;
    }
    fn_800F6E40(key, name);
    for (i = 0; i < F(o, s32, 124); i++) {
        strcpy(tmp, *(char **)(F(o, u8 *, 200) + i * 12));
        if (stricmp(tmp, key) == 0) {
            Hit(o, i, f, b, c, pf, flag);
            return;
        }
    }
}
#pragma pop
} /* namespace n802413D8 */
#undef F
