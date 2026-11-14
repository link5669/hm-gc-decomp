#include "common.h"

// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct C80152B64 { u8 data[64]; C80152B64(); };
extern "C" {
typedef void (*FP80163BE4)(void *);
extern FP80163BE4 lbl_803286D0[];
void fn_800D9E98(u32);
void fn_800BC02C(void *p, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void fn_800D9CC8(void *p, s32 v);
extern f32 lbl_80364684;
extern f32 lbl_80364688;
struct S80163BE4 { u8 pad[28]; u16 w; u16 h; };
#pragma opt_propagation off
#pragma opt_common_subs off
void fn_80163BE4(u8 *self) {
    C80152B64 m;
    u8 *g = *(u8 **)(self + 6456);
    S80163BE4 *s;
    s32 w, h;
    if (*(u32 *)(g + 2072) != 3) {
        *(u32 *)(g + 2072) = 3;
        fn_800D9E98(*(u32 *)(g + 2072));
    }
    s = *(S80163BE4 **)(self + 4);
    w = s->w - 1;
    h = s->h - 1;
    fn_800BC02C(&m, lbl_80364684, (f32)h, lbl_80364684, (f32)w, lbl_80364684, lbl_80364688);
    lbl_803286D0[94](&m);
    fn_800D9CC8(&m, 1);
}
#pragma opt_common_subs reset
#pragma opt_propagation reset

} /* extern "C" */

namespace n80163CB4 {
#pragma push
#pragma use_lmw_stmw on
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

/* QV=2.0p1 */
typedef struct { s32 x0, y0, x1, y1; f32 n, f; } Rect80163CB4;
typedef struct { u8 pad[28]; u16 w, h; } FB80163CB4;
static inline s32 W80163CB4(FB80163CB4 *fb) { return fb->w; }
static inline s32 H80163CB4(FB80163CB4 *fb) { return fb->h; }
} /* extern "C" */
struct B80163CB4 {
    void *f0; FB80163CB4 *fb; u8 pad8[24]; Rect80163CB4 rect; u8 pad56[6448 - 56];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(s32 a);
};
struct D80163CB4 : B80163CB4 { u32 f6452, f6456; s32 f6460; };
extern "C" {
extern f32 lbl_80364684;
extern f32 lbl_80364680;
void fn_800DA010(f32 x, f32 y, f32 w, f32 h, f32 n, f32 f);
void fn_800DA0C4(u32 x, u32 y, u32 w, u32 h);
void fn_8014CBA4(Rect80163CB4 *dst, const Rect80163CB4 *src);
void fn_80163CB4(D80163CB4 *p, const Rect80163CB4 *r) {
    if (r == 0) {
        p->rect.x0 = 0;
        p->rect.y0 = 0;
        p->rect.x1 = p->fb->w;
        p->rect.y1 = p->fb->h;
        p->rect.n = lbl_80364684;
        p->rect.f = lbl_80364680;
        fn_800DA010(lbl_80364684, lbl_80364684, W80163CB4(p->fb), H80163CB4(p->fb), lbl_80364684, lbl_80364680);
        fn_800DA0C4(0, 0, (u32)(f32)(s32)p->fb->w, (u32)(f32)(s32)p->fb->h);
    } else {
        fn_8014CBA4(&p->rect, r);
        fn_800DA010((f32)r->x0, (f32)r->y0, (f32)(r->x1 - r->x0), (f32)(r->y1 - r->y0), r->n, r->f);
        fn_800DA0C4((u32)(f32)r->x0, (u32)(f32)r->y0, (u32)(f32)(r->x1 - r->x0), (u32)(f32)(r->y1 - r->y0));
    }
    p->v38(p->f6460);
}

} /* extern "C" */
#pragma pop
} /* namespace n80163CB4 */

namespace n80163F20 {
extern "C" {
/* Functions from 0x80163F20 to 0x80163F28, found by decomp-toolkit. */

s32 fn_80163F20(void* arg0) {
    return *(s32*)((u8*)arg0 + 0x193C);
}

}
} /* namespace n80163F20 */

namespace n80163F28 {
#pragma push
#pragma use_lmw_stmw on
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

struct V { f32 x, y, z; };
struct C4 { u8 r, g, b, a; };
struct FT { u8 pad[392]; void (*f392)(void *, V *, V *); u8 pad396[8]; void (*f404)(void *, V *, V *); };
extern FT lbl_803286D0;
extern u32 lbl_802A0BE0[];
struct L { u8 b[4]; };
struct X { u8 pad[1132]; u8 f1132; C4 c; u8 pad1137[7]; u32 f1144; u32 f1148; int f1152; int f1156; };
struct S { u8 pad[76]; f32 f76; f32 f80; };
struct P { u8 pad[10888]; void *f10888; u8 pad2[0x20000 + 31212 - 10892]; f32 fa; f32 fb; };
struct T { u8 pad[12]; u32 f12; u8 pad16[40]; u8 f56[4]; u8 pad60[6392]; P *f6452; X *f6456; S *f6460; u8 pad6464[104]; int f6568; int f6572; u8 c6576, c6577, c6578; u8 pad6579; V f6580[8]; V f6676[8]; u8 pad6772[32]; u32 f6804; L *f6808[8]; };
void fn_8014CC80(void *);
void fn_8016C684(P *, S *);
void fn_800D7A88(int, C4);
void fn_800D7CA4(int, u8, int, u32, u32, int, int);
void fn_800D79B0(L *, f32, f32, f32);
void fn_800D7984(L *, f32, f32, f32);
void fn_800D7A0C(L *, u32);
static inline void mode(X *x, u32 a, int b, int c) {
    if (x->f1148 != a || x->f1152 != b || x->f1156 != c) {
        x->f1148 = a;
        x->f1152 = b;
        x->f1156 = c;
        fn_800D7CA4(0, x->f1132, 0, x->f1144, x->f1148, x->f1152, x->f1156);
    }
}
void fn_80163F28(T *t, S *s) {
    fn_8014CC80(t->f56);
    t->f6460 = s;
    fn_8016C684(t->f6452, t->f6460);
    t->f6452->fa = t->f6460->f76;
    t->f6452->fb = t->f6460->f80;
    if (t->f12 & 2 && t->f12 & 2) {
    if (t->f12 & 8) {
        X *x = t->f6456;
        if (x->c.r != t->c6576 || x->c.g != t->c6577 || x->c.b != t->c6578) {
            x->c.r = t->c6576;
            x->c.g = t->c6577;
            x->c.b = t->c6578;
            x->c.a = 255;
            fn_800D7A88(0, x->c);
        }
    } else {
        X *x = t->f6456;
        if (x->c.r || x->c.g || x->c.b) {
            x->c.r = 0;
            x->c.g = 0;
            x->c.b = 0;
            x->c.a = 255;
            fn_800D7A88(0, x->c);
        }
    }
    mode(t->f6456, lbl_802A0BE0[t->f6804], t->f6568, t->f6572);
    u32 i = 0;
    T *p12 = t;
    T *p4 = t;
    for (; i < t->f6804; i++) {
        V o;
        lbl_803286D0.f404(t->f6452->f10888, p12->f6676, &o);
        fn_800D79B0(p4->f6808[0], o.x, o.y, o.z);
        lbl_803286D0.f392(t->f6452->f10888, p12->f6580, &o);
        fn_800D7984(p4->f6808[0], o.x, o.y, o.z);
        fn_800D7A0C(p4->f6808[0], 1 << i);
        p12 = (T *)((u8 *)p12 + 12);
        p4 = (T *)((u8 *)p4 + 4);
    }
    }
}

} /* extern "C" */
#pragma pop
} /* namespace n80163F28 */

namespace n80164178 {
/* Functions from 0x80164178 to 0x801641F0, found by decomp-toolkit. */

extern "C" {

void fn_80164178(void) {

}

s32 fn_8016417C(void *arg0, s32 arg1) {
    return ((s32 *)(M2C_FIELD(arg0, u8 **, 0x1934) + 0x3ABC))[arg1];
}

void fn_80164190(void *arg0, s32 arg1, s32 arg2) {
    ((s32 *)(M2C_FIELD(arg0, u8 **, 0x1934) + 0x3ABC))[arg1] = arg2;
}

s32 fn_801641A4(void *arg0, s32 arg1) {
    return M2C_FIELD(M2C_FIELD(arg0, u8 **, 0x1934), s32 **, 0x2AA0)[arg1];
}

void fn_801641B8(void *arg0, s32 arg1, s32 arg2) {
    u8 *p = M2C_FIELD(arg0, u8 **, 0x1934);
    M2C_FIELD(p, s32 **, 0x2AA0)[arg1] = arg2;
    ((s32 *)(p + 0x36BC))[arg1] = 0;
}

s32 fn_801641D8(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x1934), s32 *, 0x2A84);
}

s32 fn_801641E4(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x1934), s32 *, 0x2A7C);
}

} /* extern "C" */
} /* namespace n80164178 */

namespace n801641F0 {
extern "C" {
}
#define V10 virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
struct FB801641F0 {
    u8 pad0[0x1c]; u16 w; u16 h;
    V10
    virtual void v9(u32 *a, u32 *b, int n);
    virtual void v10();
};
struct M801641F0 {
    u8 pad0[0x30];
    V10
    virtual void v9(); virtual void v10();
    virtual FB801641F0 *v11();
    u8 pad34[0x344 - 0x34];
    u32 x344;
};
struct S801641F0 {
    u8 pad0[4]; FB801641F0 *fb; u8 pad8[4]; u32 fc; u8 pad10[0x1930 - 0x10];
    V10
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30();
    M801641F0 *mgr; u8 pad1938[4]; u32 x193c;
};
extern "C" {
void *fn_8015B06C(FB801641F0 *);
void fn_800D7480(void *a, s32 b);
void fn_800D6EC4(u32, u32, u32, u32);
u32 fn_801562D8(FB801641F0 *);
void fn_800D6F74(u16, u16, u32, u32);
void fn_800D75E8(u32, u32);
void fn_800D6270(void);
void fn_800D8704(void);
void fn_801641F0(S801641F0 *s) {
    u32 a, b;
    s->v30();
    s->x193c = 0;
    s->fc &= ~2;
    if (s->mgr->v11() == s->fb) {
        if (s->mgr->x344 > 1) fn_800D7480(fn_8015B06C(s->fb), 0);
    } else {
        fn_800D6EC4(0, 0, s->fb->w, s->fb->h);
        u16 h = s->fb->h;
        u16 w = s->fb->w;
        fn_800D6F74(w, h, fn_801562D8(s->fb), 0);
        s->fb->v9(&a, &b, 2);
        fn_800D75E8(a, 0);
        fn_800D6270();
        fn_800D8704();
        s->fb->v10();
    }
}
}
} /* namespace n801641F0 */
#undef V10

namespace n80164310 {
#pragma push
#pragma use_lmw_stmw on
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

typedef struct { u8 pad[28]; s32 idx; u8 pad2[132]; } Elem80164310;
typedef struct { u16 count; u8 pad[6]; Elem80164310 *elems; } Entry80164310;
typedef struct { u8 pad[136]; u32 n; Entry80164310 **arr; } Table80164310;
typedef struct { u8 *obj[8]; u16 id; } Key80164310;
typedef struct { u8 pad[6844]; Table80164310 *tbl; } Self80164310;
s32 fn_8014C6F4(u8 *a, Elem80164310 *e);

Entry80164310 *fn_80164310(Self80164310 *s, Key80164310 *key) {
    Elem80164310 *e;
    Elem80164310 *end;
    u32 i;
    u16 count;
    if (s->tbl != 0) {
        for (i = 0; i < s->tbl->n; i++) {
            count = s->tbl->arr[i]->count;
            if (count != key->id) {
                continue;
            }
            e = s->tbl->arr[i]->elems;
            end = s->tbl->arr[i]->elems + count;
            for (; e < end; e++) {
                if (!fn_8014C6F4(key->obj[e->idx] + 16, e)) {
                    break;
                }
            }
            if (e >= end) {
                break;
            }
        }
        if (i < s->tbl->n) {
            return s->tbl->arr[i];
        }
    }
    return 0;
}

} /* extern "C" */
#pragma pop
} /* namespace n80164310 */

namespace n801643F0 {
/* Functions from 0x801643F0 to 0x80164414, found by decomp-toolkit. */

extern "C" {

void fn_801643F0(u8 *__restrict arg0, u8 *__restrict arg1) {
    arg1[0] = arg0[0x19B0];
    arg1[1] = arg0[0x19B1];
    arg1[2] = arg0[0x19B2];
    arg1[3] = arg0[0x19B3];
}

} /* extern "C" */
} /* namespace n801643F0 */

namespace n80164414 {
#pragma push
#pragma use_lmw_stmw on
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
struct V4 { f32 x, y, z, w; };
struct GXLightObj;
extern "C" void fn_800D77D8(GXLightObj *, f32 *, f32 *, f32 *);
extern "C" f32 lbl_80364684;
struct T {
    u8 pad[0x1A98];
    GXLightObj *lights[8];
    void get(u32 i, V4 *v);
};
extern "C" void fn_80164414(T *__restrict t, u32 i, V4 *__restrict v) {
    fn_800D77D8(t->lights[i], &v->x, &v->y, &v->z);
    v->w = lbl_80364684;
}
#pragma pop
} /* namespace n80164414 */

namespace n80164460 {
extern "C" {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

typedef struct { u8 r, g, b, a; } C;
typedef struct { u8 pad[0x1a98]; void *p[1]; } O;
void fn_800D7A00(void *, C *);
static inline void set(C *d, u8 r, u8 g, u8 b, u8 a) { d->r = r; d->g = g; d->b = b; d->a = a; }
void fn_80164460(O *o, s32 i, C *out) { C c; fn_800D7A00(o->p[i], &c); set(out, c.r, c.g, c.b, c.a); }

}
} /* namespace n80164460 */

namespace n801644BC {
#pragma push
#pragma use_lmw_stmw on
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
struct V3 { f32 x, y, z; };
struct GXLightObj;
extern "C" void fn_800D79CC(GXLightObj *, f32 *, f32 *, f32 *);
struct T { u8 pad[0x1A98]; GXLightObj *lights[8]; };
extern "C" void fn_801644BC(T *__restrict t, u32 i, V3 *v) {
    fn_800D79CC(t->lights[i], &v->x, &v->y, &v->z);
    v->y = -v->y;
    v->z = -v->z;
}
#pragma pop
} /* namespace n801644BC */

namespace n80164518 {
#pragma push
#pragma use_lmw_stmw on
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
struct V3 { f32 x, y, z; };
struct GXLightObj;
extern "C" void fn_800D7994(GXLightObj *, f32 *, f32 *, f32 *);
struct T { u8 pad[0x1A98]; GXLightObj *lights[8]; };
extern "C" void fn_80164518(T *__restrict t, u32 i, V3 *v) {
    fn_800D7994(t->lights[i], &v->x, &v->y, &v->z);
    v->y = -v->y;
    v->z = -v->z;
}
#pragma pop
} /* namespace n80164518 */

namespace n80164574 {
extern "C" {
/* Functions from 0x80164574 to 0x80164584, found by decomp-toolkit. */

s32 fn_80164574(u8 *arg0, s32 arg1) {
    return ((s32 *)(arg0 + 0x1A74))[arg1];
}

}
} /* namespace n80164574 */

namespace n80164584 {
#pragma push
#pragma use_lmw_stmw on

extern "C" {



struct V { f32 x, y, z; };
struct C4 { u8 r, g, b, a; C4() {} C4(u8 _r, u8 _g, u8 _b, u8 _a) { r = _r; g = _g; b = _b; a = _a; } };
struct L { u8 pad[64]; };
struct Pool { u8 pad[10888]; void *f10888; u8 pad10892[5248]; u32 n; L arr[512]; };
struct X { u8 pad[1132]; u8 f1132; u8 pad1133[11]; u32 f1144; u32 f1148; int f1152; int f1156; };
struct S { u8 pad[20]; f32 c[4]; u8 pad36[20]; f32 f56; u8 pad60[4]; f32 f64; f32 f68; f32 f72; };
struct FT { u8 pad[392]; void (*f392)(void *, V *, V *); u8 pad396[8]; void (*f404)(void *, V *, V *); };
extern FT lbl_803286D0;
struct T { u8 pad[12]; u32 f12; u8 pad16[6436]; Pool *f6452; X *f6456; u8 pad6460[108]; int f6568; int f6572; u8 pad6576[4]; V f6580[8]; V f6676[8]; int f6772[9]; L *f6808[8]; };
extern f32 lbl_80364698, lbl_8036469C, lbl_803646A0;
void fn_800D79F4(L *, C4);
void fn_800D7CA4(int, u8, int, u32, u32, int, int);
void fn_800D77F4(L *, int, f32);
void fn_800D77C8(L *, f32, f32, f32);
void fn_800D79B0(L *, f32, f32, f32);
void fn_800D7984(L *, f32, f32, f32);
void fn_800D7A0C(L *, u32);
static inline void mode(X *x, int a, int b) {
    if (x->f1152 != a || x->f1156 != b) {
        x->f1152 = a;
        x->f1156 = b;
        fn_800D7CA4(0, x->f1132, 0, x->f1144, x->f1148, x->f1152, x->f1156);
    }
}
void fn_80164584(T *__restrict t, u32 idx, S *s, V *__restrict pos, V *__restrict dir) {
    if (idx >= 8) return;
    Pool *p = t->f6452;
    L *l;
    if (p->n >= 512) l = 0;
    else l = &p->arr[p->n++];
    if (!l) return;
    *(L *volatile *)&t->f6808[idx] = l;
    *(volatile int *)&t->f6772[idx] = 2;
    f32 K, r, g, b, a;
    r = *(volatile f32 *)&s->c[0]; g = s->c[1]; b = s->c[2]; a = s->c[3];
    K = *(volatile f32 *)&lbl_80364698;
    r *= K; g *= K; b *= K; a *= K;
    C4 c((int)r, (int)g, (int)b, (int)a);
    fn_800D79F4(l, c);
    t->f6568 = 2;
    t->f6572 = 1;
    mode(t->f6456, t->f6568, t->f6572);
    fn_800D77F4(l, 3, lbl_8036469C * (lbl_803646A0 * s->f56));
    fn_800D77C8(l, s->f64, s->f68, s->f72);
    t->f6580[idx].x = pos->x;
    t->f6580[idx].y = pos->y;
    t->f6580[idx].z = pos->z;
    t->f6676[idx].x = dir->x;
    t->f6676[idx].y = dir->y;
    t->f6676[idx].z = dir->z;
    if (t->f12 & 2) {
        V o;
        lbl_803286D0.f404(t->f6452->f10888, dir, &o);
        fn_800D79B0(l, o.x, o.y, o.z);
        lbl_803286D0.f392(t->f6452->f10888, pos, &o);
        fn_800D7984(l, o.x, o.y, o.z);
        fn_800D7A0C(l, 1 << idx);
    } else {
        fn_800D79B0(l, dir->x, dir->y, dir->z);
        fn_800D7984(l, pos->x, pos->y, pos->z);
    }
}



} /* extern "C" */
#pragma pop
} /* namespace n80164584 */

namespace n801647F8 {
#pragma push
#pragma use_lmw_stmw on

extern "C" {

struct V { f32 x, y, z; };
struct C4 { u8 r, g, b, a; C4() {} C4(u8 _r, u8 _g, u8 _b, u8 _a) { r = _r; g = _g; b = _b; a = _a; } };
struct L { u8 b[64]; };
struct FT { u8 pad[404]; void (*f404)(void *, V *, V *); };
extern FT lbl_803286D0;
extern f32 lbl_80364680;
extern f32 lbl_80364684;
extern f32 lbl_80364698;
extern f32 lbl_803646A4;
struct P { u8 pad[10888]; void *f10888; u8 pad2[0x3f0c - 10892]; u32 cnt; L items[512]; };
struct X { u8 pad[1132]; u8 f1132; u8 pad1133[11]; u32 f1144; u32 f1148; int f1152; int f1156; };
struct Src { u8 pad[20]; f32 r, g, b, a; };
struct T { u8 pad[12]; u32 f12; u8 pad16[0x1934 - 16]; P *f6452; X *f6456; u8 pad6460[0x19a8 - 0x193c]; int f6568; int f6572; u8 pad6576[4]; V f6580[8]; V f6676[8]; int f6772[8]; u32 f6804; L *f6808[8]; };
void fn_800D79F4(L *, C4);
void fn_800D7CA4(int, u8, int, u32, u32, int, int);
void fn_800D77AC(L *, f32, f32, f32, f32, f32, f32);
void fn_800D7984(L *, f32, f32, f32);
void fn_800D7A0C(L *, u32);
static inline L *Alloc(P *p) {
    if (p->cnt >= 0x200) return 0;
    return &p->items[p->cnt++];
}
static inline void mode(X *x, int b, int c) {
    if (x->f1152 != b || x->f1156 != c) {
        x->f1152 = b;
        x->f1156 = c;
        fn_800D7CA4(0, x->f1132, 0, x->f1144, x->f1148, x->f1152, x->f1156);
    }
}
void fn_801647F8(T *__restrict t, u32 n, Src *s, V *__restrict pos) {
    if (n >= 8) return;
    L *l = Alloc(t->f6452);
    if (!l) return;
    *(L *volatile *)&t->f6808[n] = l;
    *(volatile int *)&t->f6772[n] = 1;
    f32 K, r, g, b, a;
    r = *(volatile f32 *)&s->r; g = s->g; b = s->b; a = s->a;
    K = *(volatile f32 *)&lbl_80364698;
    r *= K; g *= K; b *= K; a *= K;
    C4 c((int)r, (int)g, (int)b, (int)a);
    fn_800D79F4(l, c);
    t->f6568 = 2;
    t->f6572 = 1;
    mode(t->f6456, t->f6568, t->f6572);
    fn_800D77AC(l, lbl_80364680, lbl_80364684, lbl_80364684, lbl_80364680, lbl_80364684, lbl_80364684);
    *(volatile f32 *)&t->f6580[n].x = *(volatile f32 *)&lbl_80364684;
    *(volatile f32 *)&t->f6580[n].y = *(volatile f32 *)&lbl_80364684;
    *(volatile f32 *)&t->f6580[n].z = *(volatile f32 *)&lbl_80364684;
    t->f6676[n].x = pos->x;
    t->f6676[n].y = pos->y;
    t->f6676[n].z = pos->z;
    if (t->f12 & 2) {
        V o;
        lbl_803286D0.f404(t->f6452->f10888, pos, &o);
        fn_800D7984(l, lbl_803646A4 * -o.x, lbl_803646A4 * -o.y, lbl_803646A4 * -o.z);
        fn_800D7A0C(l, 1 << n);
    } else {
        fn_800D7984(l, lbl_803646A4 * -pos->x, lbl_803646A4 * -pos->y, lbl_803646A4 * -pos->z);
    }
}

} /* extern "C" */
#pragma pop
} /* namespace n801647F8 */

namespace n80164A54 {
#pragma push
#pragma use_lmw_stmw on
extern "C" {
struct V { f32 x, y, z; };
struct C4 { u8 r, g, b, a; C4() {} C4(u8 _r, u8 _g, u8 _b, u8 _a) { r = _r; g = _g; b = _b; a = _a; } };
struct L { u8 pad[64]; };
struct Pool { u8 pad[10888]; void *f10888; u8 pad10892[5248]; u32 n; L arr[512]; };
struct X { u8 pad[1132]; u8 f1132; u8 pad1133[11]; u32 f1144; u32 f1148; int f1152; int f1156; };
struct S { u8 pad[20]; f32 c[4]; u8 pad36[28]; f32 f64; f32 f68; f32 f72; };
struct FT { u8 pad[392]; void (*f392)(void *, V *, V *); };
extern FT lbl_803286D0;
struct T { u8 pad[12]; u32 f12; u8 pad16[6436]; Pool *f6452; X *f6456; u8 pad6460[108]; int f6568; int f6572; u8 pad6576[4]; V f6580[8]; V f6676[8]; int f6772[9]; L *f6808[8]; };
extern f32 lbl_80364680, lbl_80364684, lbl_80364698;
void fn_800D79F4(L *, C4);
void fn_800D7CA4(int, u8, int, u32, u32, int, int);
void fn_800D77AC(L *, f32, f32, f32, f32, f32, f32);
void fn_800D79B0(L *, f32, f32, f32);
void fn_800D7984(L *, f32, f32, f32);
void fn_800D7A0C(L *, u32);
static inline void mode(X *x, int a, int b) {
    if (x->f1152 != a || x->f1156 != b) {
        x->f1152 = a;
        x->f1156 = b;
        fn_800D7CA4(0, x->f1132, 0, x->f1144, x->f1148, x->f1152, x->f1156);
    }
}
void fn_80164A54(T *t, u32 idx, S *s, V *pos) {
    if (idx >= 8) return;
    Pool *p = t->f6452;
    L *l;
    if (p->n >= 512) l = 0;
    else l = &p->arr[p->n++];
    if (!l) return;
    t->f6808[idx] = l;
    t->f6772[idx] = 0;
    f32 r = s->c[0], g = s->c[1], b = s->c[2], a = s->c[3];
    f32 K = lbl_80364698;
    r *= K; g *= K; b *= K; a *= K;
    C4 c((int)r, (int)g, (int)b, (int)a);
    fn_800D79F4(l, c);
    t->f6568 = 2;
    t->f6572 = 1;
    mode(t->f6456, t->f6568, t->f6572);
    fn_800D77AC(l, lbl_80364680, lbl_80364684, lbl_80364684, s->f64, s->f68, s->f72);
    fn_800D79B0(l, lbl_80364684, lbl_80364684, lbl_80364680);
    f32 px = pos->x;
    f32 py = pos->y;
    f32 pz = pos->z;
    t->f6580[idx].x = px;
    t->f6580[idx].y = py;
    t->f6580[idx].z = pz;
    t->f6676[idx].x = lbl_80364684;
    t->f6676[idx].y = lbl_80364684;
    t->f6676[idx].z = lbl_80364680;
    if (t->f12 & 2) {
        V o;
        lbl_803286D0.f392(t->f6452->f10888, pos, &o);
        fn_800D7984(l, o.x, o.y, o.z);
        fn_800D7A0C(l, 1 << idx);
    } else {
        fn_800D7984(l, px, py, pz);
    }
}

}
#pragma pop
} /* namespace n80164A54 */

namespace n80164C78 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

extern u32 lbl_802A0BE0[];
void fn_800D7CA4(s32, u8, s32, u32, u32, u32, u32);

void fn_80164C78(u8 *p, u32 n) {
    if (n != *(u32 *)(p + 6804)) {
        if (n > 8) {
            n = 8;
        }
        if (*(u32 *)(p + 12) & 2) {
            u8 *s = *(u8 **)(p + 6456);
            u32 v = lbl_802A0BE0[n];
            if (*(u32 *)(s + 1148) != v) {
                *(u32 *)(s + 1148) = v;
                fn_800D7CA4(0, s[1132], 0, *(u32 *)(s + 1144), *(u32 *)(s + 1148), *(u32 *)(s + 1152), *(u32 *)(s + 1156));
            }
        }
        *(u32 *)(p + 6804) = n;
    }
}

} /* extern "C" */
} /* namespace n80164C78 */

namespace n80164D18 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

typedef struct { u8 r, g, b, a; } GXColor;
typedef struct {
    u8 pad[1133];
    GXColor c;
} Q;
typedef struct {
    u8 pad0[12];
    u32 flags;
    u8 pad1[6456 - 16];
    Q *q;
    u8 pad2[6576 - 6460];
    GXColor c;
} P;
extern u32 lbl_803646A8;
void fn_80121848(GXColor *, void *);
void fn_800D7A88(int, GXColor *);

void fn_80164D18(P *p, void *a) {
    Q *q;
    GXColor c;
    p->flags |= lbl_803646A8;
    fn_80121848(&p->c, a);
    if (p->flags & 2) {
        q = p->q;
        if (q->c.r != p->c.r || q->c.g != p->c.g || q->c.b != p->c.b) {
            q->c.r = p->c.r;
            q->c.g = p->c.g;
            q->c.b = p->c.b;
            q->c.a = 255;
            *(u32 *)&c = *(u32 *)&q->c;
            fn_800D7A88(0, &c);
        }
    }
}

} /* extern "C" */
} /* namespace n80164D18 */

namespace n80164DC8 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

void fn_800D7A88(int, int);
void fn_800D7CA4(int, int, int, int, int, int, int);
extern void *memset(void *, int, unsigned long);

void fn_80164DC8(s32 param_1) {
    s32 iVar1;
    s32 iVar2;
    s32 iVar3;
    u32 local_18 [1];

    *(u32 *)(param_1 + 0xc) = *(u32 *)(param_1 + 0xc) & 0xfffffff7;
    *(u32 *)(param_1 + 0x1a94) = 0;
    *(u32 *)(param_1 + 0x19a8) = 2;
    *(u32 *)(param_1 + 0x19ac) = 2;
    if ((*(u32 *)(param_1 + 0xc) & 2) != 0) {
        iVar1 = *(s32 *)(param_1 + 0x1938);
        if (((*(u8 *)(iVar1 + 0x46d) != 0) || (*(u8 *)(iVar1 + 0x46e) != 0)) ||
              (*(u8 *)(iVar1 + 0x46f) != 0)) {
            *(u8 *)(iVar1 + 0x46d) = 0;
            *(u8 *)(iVar1 + 0x46e) = 0;
            *(u8 *)(iVar1 + 0x46f) = 0;
            *(u8 *)(iVar1 + 0x470) = 0xff;
            local_18[0] = *(u32 *)(iVar1 + 0x46d);
            fn_800D7A88((int)(0), (int)(local_18));
        }
        iVar3 = *(s32 *)(param_1 + 0x1938);
        iVar2 = *(s32 *)(param_1 + 0x19ac);
        iVar1 = *(s32 *)(param_1 + 0x19a8);
        if (((*(void **)(iVar3 + 0x47c) != NULL) || (*(s32 *)(iVar3 + 0x480) != iVar1)) ||
              (*(s32 *)(iVar3 + 0x484) != iVar2)) {
            *(u32 *)(iVar3 + 0x47c) = 0;
            *(s32 *)(iVar3 + 0x480) = iVar1;
            *(s32 *)(iVar3 + 0x484) = iVar2;
            fn_800D7CA4((int)(0), (int)(*(u8 *)(iVar3 + 0x46c)), (int)(0), (int)(*(u32 *)(iVar3 + 0x478)), (int)(*(u32 *)(iVar3 + 0x47c)), (int)(*(u32 *)(iVar3 + 0x480)), (int)(*(u32 *)(iVar3 + 0x484)));
        }
    }
    memset((void *)(param_1 + 0x1a98),0,0x20);
}

} /* extern "C" */
} /* namespace n80164DC8 */

namespace n80164EE0 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

struct V_80164EE0 { u8 pad[0x1930]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void m(); };
extern "C" { extern u32 lbl_803646AC; void fn_8016B800(void *); }

void fn_80164EE0(V_80164EE0 *p, s32 a) {
    if (a != 0) {
        p->m();
    }
    *(u32 *)((u8 *)p + 12) |= lbl_803646AC;
    fn_8016B800(*(void **)((u8 *)p + 6452));
}

} /* extern "C" */
} /* namespace n80164EE0 */

namespace n80164F38 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {



} /* extern "C" */

extern "C" {
void fn_8016B848(int);
struct VCall_fn_80164F38_0 { char vptr_pad[0x1930]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void m(); };

void fn_80164F38(s32 param_1, s32 param_2) {
    if (param_2 != 0) {
        ((VCall_fn_80164F38_0 *)(param_1))->m();
    }
    *(u32 *)(param_1 + 0xc) = *(u32 *)(param_1 + 0xc) & 0xfffffbff;
    fn_8016B848((int)(*(u32 *)(param_1 + 0x1934)));
}
}
} /* namespace n80164F38 */

namespace n80164F8C {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

struct V_80164F8C { u8 pad[0x1930]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void m(); };
extern "C" { extern u32 lbl_803646B0; void fn_8016B88C(void *); }

void fn_80164F8C(V_80164F8C *p, s32 a) {
    if (a != 0) {
        p->m();
    }
    *(u32 *)((u8 *)p + 12) |= lbl_803646B0;
    fn_8016B88C(*(void **)((u8 *)p + 6452));
}

} /* extern "C" */
} /* namespace n80164F8C */

namespace n80164FE4 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {



} /* extern "C" */

extern "C" {
void fn_8016B8E0(int);
struct VCall_fn_80164FE4_0 { char vptr_pad[0x1930]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void m(); };

void fn_80164FE4(s32 param_1, s32 param_2) {
    if (param_2 != 0) {
        ((VCall_fn_80164FE4_0 *)(param_1))->m();
    }
    *(u32 *)(param_1 + 0xc) = *(u32 *)(param_1 + 0xc) & 0xffffff7f;
    fn_8016B8E0((int)(*(u32 *)(param_1 + 0x1934)));
}
}
} /* namespace n80164FE4 */

namespace n80165038 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

struct V_80165038 { u8 pad[0x1930]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void m(); };
extern "C" { extern u32 lbl_803646B4; void fn_8016B930(void *); }

void fn_80165038(V_80165038 *q) {
    u8 *p = (u8 *)q;
    q->m();
    *(u32 *)(p + 6848) = *(u32 *)(p + 12) & 0x30;
    *(u32 *)(p + 12) &= ~0x30;
    *(u32 *)(p + 12) |= lbl_803646B4;
    fn_8016B930(*(void **)(p + 6452));
}

} /* extern "C" */
} /* namespace n80165038 */

namespace n801650A0 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {



} /* extern "C" */

extern "C" {
void fn_8016B984(int);
struct VCall_fn_801650A0_0 { char vptr_pad[0x1930]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void m(); };

void fn_801650A0(s32 param_1) {
    ((VCall_fn_801650A0_0 *)(param_1))->m();
    *(u32 *)(param_1 + 0xc) = *(u32 *)(param_1 + 0xc) | *(u32 *)(param_1 + 0x1ac0);
    fn_8016B984((int)(*(u32 *)(param_1 + 0x1934)));
}
}
} /* namespace n801650A0 */

namespace n801650F0 {
extern "C" {
/* Functions from 0x801650F0 to 0x801650F8, found by decomp-toolkit. */

int fn_801650F0(int a) { return a; }

int fn_801650F4(int a) { return a; }

}
} /* namespace n801650F0 */

#pragma push
#pragma use_lmw_stmw on
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
// NonMatching: 66 asm diff lines left: saved-reg colouring of the zen/zfn/zup/b13 locals in the 3 branches,
// and xoris/stw order in the 3 inlined ortho setups. int->float magic lbl_80364690 is shared .sdata2.

extern "C" {

/* QV=2.0p1 */

typedef struct { s32 x0, y0, x1, y1; f32 n, f; } Rect;
typedef struct { u8 pad[28]; u16 w, h; } FB;
struct St {
    u8 pad0[0x4b4]; bool zen; u8 pad4b5[3]; s32 zfn; bool zup; bool b13; u8 pad4be[0x818 - 0x4be]; u32 x818;
};
struct Gx { u8 pad0[0x2c]; u32 x2c; u8 pad30[0x279f4 - 0x30]; s32 x279f4; };
static inline s32 W(FB *fb) { return fb->w; }
static inline s32 H(FB *fb) { return fb->h; }
} /* extern "C" */
struct B {
    void *f0; FB *fb; u8 pad8[4]; u32 xc; u8 pad10[16]; Rect rect; u8 pad56[0x192c - 56]; void *x192c;
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(s32 a);
};
struct D : B { Gx *x1934; St *x1938; u8 pad193c[4]; u8 x1940[4]; };
extern "C" {

/* QV=2.0p1 */
typedef void (*FP)(void *);
extern FP lbl_803286D0[];
extern f32 lbl_80364680;
extern f32 lbl_80364684;
extern f32 lbl_80364688;
extern u32 lbl_803646B8;
extern u32 lbl_803646BC;
extern u8 lbl_802A04E8[];
extern u8 lbl_8032E4A8[];
void fn_800DA010(f32 x, f32 y, f32 w, f32 h, f32 n, f32 f);
void fn_800DA0C4(u32 x, u32 y, u32 w, u32 h);
void fn_8014CBA4(Rect *dst, const Rect *src);
void fn_800D9E98(u32);
void fn_800BC02C(void *p, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void fn_800D9CC8(void *p, s32 v);
void fn_800D9A04(bool, s32, bool);
void fn_800D99AC(bool);
void fn_8016C7BC(Gx *);
void fn_8016C640(Gx *);
void fn_8016B848(Gx *);
void fn_8016B984(Gx *);
void fn_8016B8E0(Gx *);
void fn_8016B794(Gx *, s32);
void fn_80165944(D *);
void fn_801699D8(Gx *, void *, s32, s32, void *, s32, s32);

static inline void SetZ(St *s, bool en, s32 fn, bool up) {
    if (s->zen != en || s->zfn != fn || s->zup != up) {
        s->zen = en; s->zfn = fn; s->zup = up;
        fn_800D9A04(s->zen, s->zfn, s->zup);
    }
}
static inline void SetZEn(St *s, bool v) {
    if (v ? !s->zen : s->zen) { s->zen = v; fn_800D9A04(s->zen, s->zfn, s->zup); }
}
static inline void SetB13(St *s, bool v) {
    if (v ? !s->b13 : s->b13) { s->b13 = v; fn_800D99AC(s->b13); }
}
static inline void SetMode(St *g, u32 v) {
    if (g->x818 != v) {
        g->x818 = v;
        fn_800D9E98(g->x818);
    }
}
static inline void Ortho(D *p) {
    C80152B64 m;
    SetMode(p->x1938, 3);
    fn_800BC02C(&m, lbl_80364684, (f32)(H(p->fb) - 1), lbl_80364684, (f32)(W(p->fb) - 1), lbl_80364684, lbl_80364688);
    lbl_803286D0[94](&m);
    fn_800D9CC8(&m, 1);
}
static inline void Draw(D *p) {
    Ortho(p);
    fn_801699D8(p->x1934, p->x1940, 0, 0, lbl_802A04E8, 0, 4);
    fn_8016C640(p->x1934);
}

void fn_801650F8(D *p, s32 a, u32 fl, const Rect *r) {
    fn_8016C7BC(p->x1934);
    if (fl & 8) p->xc |= lbl_803646B8;
    else if (fl & 0x10) p->xc |= lbl_803646B8;
    else p->xc &= ~4;
    if (r == 0) {
        p->rect.x0 = 0;
        p->rect.y0 = 0;
        p->rect.x1 = p->fb->w;
        p->rect.y1 = p->fb->h;
        p->rect.n = lbl_80364684;
        p->rect.f = lbl_80364680;
        fn_800DA010(lbl_80364684, lbl_80364684, W(p->fb), H(p->fb), lbl_80364684, lbl_80364680);
        fn_800DA0C4(0, 0, (u32)(f32)(s32)p->fb->w, (u32)(f32)(s32)p->fb->h);
    } else {
        fn_8014CBA4(&p->rect, r);
        fn_800DA010((f32)r->x0, (f32)r->y0, (f32)(r->x1 - r->x0), (f32)(r->y1 - r->y0), r->n, r->f);
        fn_800DA0C4((u32)(f32)r->x0, (u32)(f32)r->y0, (u32)(f32)(r->x1 - r->x0), (u32)(f32)(r->y1 - r->y0));
    }
    p->v38(a);
    p->x1934->x279f4 = 0;
    if (fl & 1) {
        fn_80165944(p);
        if (fl & 2) {
            St *s = p->x1938;
            bool zen = s->zen;
            u8 b13 = s->b13;
            s32 zfn = s->zfn;
            bool zup = s->zup;
            SetZ(s, true, 7, true);
            SetB13(p->x1938, true);
            Draw(p);
            SetZ(p->x1938, zen, zfn, zup);
            if (!b13) SetB13(p->x1938, false);
        } else {
            St *s = p->x1938;
            u8 zen = s->zen;
            u8 b13 = s->b13;
            SetZEn(s, false);
            SetB13(p->x1938, true);
            Draw(p);
            if (!b13) SetB13(p->x1938, false);
            if (zen) SetZEn(p->x1938, true);
        }
    } else if (fl & 2) {
        p->x1934->x2c &= ~0x800;
        St *s = p->x1938;
        bool zen = s->zen;
        u8 b13 = s->b13;
        s32 zfn = s->zfn;
        bool zup = s->zup;
        SetZ(s, true, 7, true);
        SetB13(p->x1938, false);
        Draw(p);
        SetZ(p->x1938, zen, zfn, zup);
        if (b13) SetB13(p->x1938, true);
    }
    p->xc &= ~0x4C0;
    fn_8016B848(p->x1934);
    fn_8016B984(p->x1934);
    fn_8016B8E0(p->x1934);
    fn_8016B794(p->x1934, 2);
    p->xc |= lbl_803646BC;
    p->v31();
    p->x192c = lbl_8032E4A8;
}

} /* extern "C" */
#pragma pop
