// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V3 { f32 x, y, z; };
struct Nm { char b[8]; };
struct Act {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); 
    virtual void getPos(V3 *o, s32 a, s32 b, s32 c, s32 d);
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32();
    virtual void play(const void *s, s32 a, s32 b, void *c, s32 d);
};
struct Tri { s32 *f0; s32 *f4; u8 pad8[0x2c]; s32 *f34; u8 pad38[0xc]; f32 *f44; u8 pad48[0x34]; s32 *f7c; u8 pad80[0xc]; char *f8c; char *f90; };
struct Wt { f32 b[3]; f32 e[6][3]; };

#define F(T, o) (*(T *)(p + (o)))
#define VP(o) ((V3 *)(p + (o)))
#define FC F(u8 *, 0xfc)

extern s8 lbl_80359FC4;
extern s8 lbl_80359FCC;
extern s32 lbl_80359FC8;
extern f32 lbl_80359FC0;
extern s32 lbl_8035A1F0;
extern Nm lbl_8035A1F4;
extern s32 lbl_8035A250;
extern s32 lbl_8035A25C;
extern s32 lbl_80359748;
extern u8 *lbl_8035B65C;
extern u8 *lbl_8035B488;
extern s32 lbl_8035B6E0;
extern u8 lbl_803286D0[];
extern V3 lbl_80302640;
extern V3 lbl_803064F8[6];
extern V3 lbl_80306540[6];
extern V3 lbl_80306588[6];
extern V3 lbl_803065D0[6];
extern s32 lbl_80306618[6];
extern s32 lbl_80306630[6];
extern s32 lbl_80306648[6];
extern s32 lbl_80306660[6];
extern Tri *lbl_80306678[6];
extern s32 lbl_80306690[6];
extern s32 lbl_803066A8[18];
extern s32 lbl_803066F0[6];
extern Tri *lbl_80306708[6];
extern V3 lbl_80357AEC;
extern V3 lbl_80357B04;
extern V3 lbl_80357E90;
extern char lbl_80294AB8[];
extern const char lbl_8035BEB0[6];
extern const char lbl_8035BEB8[8];
extern const char lbl_8035BF00[8];
extern const char lbl_8035BF08[8];
extern const char lbl_8035BF10[8];
extern const char lbl_8035BF18[8];
extern const char lbl_8035BF20[8];
extern const char lbl_8035BF28[4];
extern const char lbl_8035BF2C[8];
extern const char lbl_8035BF34[8];
extern const char lbl_8035BF3C[8];
extern const char lbl_8035BF44[8];
extern const char lbl_8035BF4C[8];
extern const char lbl_8035BF54[8];
extern const char lbl_8035BF5C[8];
extern const char lbl_8035BF64[8];
extern f32 lbl_8035BE98;
extern f32 lbl_8035BE9C;
extern f32 lbl_8035BEC0;
extern f32 lbl_8035BEC4;
extern f32 lbl_8035BEC8;
extern f32 lbl_8035BECC;
extern f32 lbl_8035BED0;
extern f32 lbl_8035BED4;
extern f64 lbl_8035BED8;
extern f32 lbl_8035BEE0;
extern f32 lbl_8035BEE4;
extern f32 lbl_8035BEE8;
extern f32 lbl_8035BEEC;
extern f32 lbl_8035BEF0;
extern f32 lbl_8035BEF4;
extern f32 lbl_8035BEF8;
extern f32 lbl_8035BEFC;

void fn_802610A0(u8 *p);
void fn_80066050(u8 *p);
void fn_80064B8C(u8 *p, Wt *w, f32 dt);
void fn_80064AF0(u8 *p);
void fn_80065740(u8 *p, Tri *a, Tri *b, f32 dt);
void fn_80065B48(u8 *p);
void __ct__9C80253F24Fiiii(u8 *m, const char *s, s32 a, s32 b, s32 c);
void fn_80036E0C(u8 *o, V3 *v);
void fn_80036E28(u8 *o, V3 *v);
void fn_80036E44(u8 *o, s32 v);
s32 fn_80036F10(Tri *t);
void fn_80036FF8(V3 *a, V3 *b, f32 s);
void fn_8003702C(V3 *o, V3 *a, V3 *b);
void fn_80037060(V3 *p, V3 *q, f32 a, f32 b);
void fn_80037118(V3 *a, V3 *b, f32 s);
f32 fn_8003714C(V3 *v);
void fn_800371D0(V3 *v, f32 s);
void fn_800371F8(V3 *d, V3 *s);
void fn_80037214(V3 *v);
void fn_8003723C(V3 *d, V3 *a, V3 *b);
void fn_8003727C(V3 *d, V3 *s);
void fn_800372B0(V3 *d, V3 *s);
f32 fn_80037A38(u8 *t, s32 id);
s32 fn_800724A4(Act *a);
s32 fn_80072988(u8 *o, V3 v);
s32 fn_800F6CD0(Nm *a, char *b);
void fn_800F6E88(void *d, void *s);
void fn_80100CF4(f32 *v);
void fn_80100F24(V3 *a, V3 *b);
void fn_80101030(V3 *a, V3 *b);
void fn_80101414(V3 *a, V3 *b, f32 s);
f32 fn_80101590(V3 *a, V3 *b);
void fn_80101820(V3 *v);
void fn_80107F3C(void *o, V3 *s);
void fn_8023BE44(V3 *o, V3 a, V3 b, f32 k, f32 z, f32 t);
s32 fn_80264E0C(V3 *a, V3 *b, V3 *c, V3 *d, s32 *e, s32 *f, s32 *g, s32 h, s32 i, s32 j, s32 k, s32 l, s32 m, s32 n, s32 o);
void fn_80264AC0(s32 n, V3 *a, V3 *b, f32 *c, s32 *d, V3 *e, V3 *f, s32 *g, s32 *h, s32 *i, Tri **j, s32 k, s32 *l, s32 *m, s32 *n2, Tri **o, s32 q, s32 r);

/* .data 0x802AFAF0-0x802AFBE4: two float tables + vtable (owned here so the unit starts 8-aligned) */
extern "C" {
void __dt__9C800374F4Fv();
void fn_8023D1BC();
void fn_8023D1B4();
void fn_80037438();
void fn_80034AF8();
void fn_8023D198();
void fn_80261914();
void fn_802611B8();
void fn_802611B4();
void fn_80037368();
void fn_800372CC();
void fn_80035318();
void fn_80034AEC();
void fn_80034AFC();
void fn_80034AF0();
void fn_80034AF4();
void fn_80035398(u8 *, f32);
u32 lbl_802AFAF0[21] = {
    0x00000000, 0x3F400000, 0x00000000, 0x00000000, 0xBF400000, 0x00000000,
    0x3F0CCCCD, 0x3F400000, 0x00000000, 0xBF0CCCCD, 0x3F400000, 0x00000000,
    0x00000000, 0x3F400000, 0x3F0CCCCD, 0x00000000, 0x3F400000, 0xBF0CCCCD,
    0x00000000, 0x3FD9999A, 0x00000000,
};
u32 lbl_802AFB44[21] = {
    0x00000000, 0x3F000000, 0x00000000, 0x00000000, 0xBD4CCCCD, 0x00000000,
    0x3E4CCCCD, 0x3F000000, 0x00000000, 0xBE4CCCCD, 0x3F000000, 0x00000000,
    0x00000000, 0x3F000000, 0x3E4CCCCD, 0x00000000, 0x3F000000, 0xBE4CCCCD,
    0x00000000, 0x3FD9999A, 0x00000000,
};
void *lbl_802AFB98[19] = { 0, 0, (void *)__dt__9C800374F4Fv, (void *)fn_8023D1BC, (void *)fn_8023D1B4, (void *)fn_80037438, (void *)fn_80034AF8, (void *)fn_8023D198, (void *)fn_80261914, (void *)fn_802611B8, (void *)fn_802611B4, (void *)fn_80037368, (void *)fn_800372CC, (void *)fn_80035318, (void *)fn_80034AEC, (void *)fn_80034AFC, (void *)fn_80035398, (void *)fn_80034AF0, (void *)fn_80034AF4 };
}
static inline s32 Get(s32 *x) { return x != 0 ? *x : 0; }
static inline int SetNm(Nm *n, char *s) {
    if (s != 0 && *s != 0) {
        fn_800F6E88(n, s);
        return 1;
    }
    return 0;
}
static inline void Place(u8 *p, V3 *o) {
    Wt *w;
    fn_800371F8(o, VP(0x14));
    fn_80037118(o, VP(0x20), F(Wt *, 0x18c)->b[0]);
    fn_80037118(o, VP(0x2c), F(Wt *, 0x18c)->b[1]);
    fn_80037118(o, VP(0x38), F(Wt *, 0x18c)->b[2]);
}
static inline void PlaceE(u8 *p, V3 *o) {
    fn_800371F8(o, VP(0x50));
    fn_80037118(o, VP(0x5c), F(Wt *, 0x18c)->b[0]);
    fn_80037118(o, VP(0x68), F(Wt *, 0x18c)->b[1]);
    fn_80037118(o, VP(0x74), F(Wt *, 0x18c)->b[2]);
}
static inline void Back(u8 *p) {
    fn_800371F8(VP(0x50), VP(0x14));
    fn_80037118(VP(0x50), VP(0x20), F(Wt *, 0x18c)->b[0]);
    fn_80037118(VP(0x50), VP(0x2c), F(Wt *, 0x18c)->b[1]);
    fn_80037118(VP(0x50), VP(0x38), F(Wt *, 0x18c)->b[2]);
    fn_80036FF8(VP(0x50), VP(0x5c), F(Wt *, 0x18c)->b[0]);
    fn_80036FF8(VP(0x50), VP(0x68), F(Wt *, 0x18c)->b[1]);
    fn_80036FF8(VP(0x50), VP(0x74), F(Wt *, 0x18c)->b[2]);
}
static inline void Reset(u8 *p) {
    fn_80036E44(FC, 0);
    *(s32 *)(FC + 0x338) = 0;
    *(s32 *)(FC + 0x5e4) = 0;
}
static inline void Name(u8 *p, Nm *n, Tri *t) {
}

void fn_80035398(u8 *p, f32 dt) {
    V3 r, u, s, f, c;
    V3 h, a, z, d, e;
    V3 save;
    V3 q0, q1, q2, q3;
    f32 bb[4];
    V3 g, k0, k1;
    V3 m0, m1, m2, m3, m4;
    Nm n0, n1, n2;
    s32 e0, e1, e2;
    u32 i;
    s32 e3, e4, e5;
    Act *act;
    f32 a0, len, len0, t, lim;
    u8 *cam;
    s32 launch, any, hit, old, mode, sw;
    Tri *t0, *t1;

    if (!lbl_80359FC4) lbl_80359FC4 = 1;
    fn_802610A0(p);
    fn_80066050(p);
    if (lbl_8035A1F0 != 0) {
        lbl_8035A1F0 = 0;
        (*(Act **)(p + 0x9c))->play(lbl_8035BEB0, 0, 0, 0, 0);
        __ct__9C80253F24Fiiii(lbl_8035B65C, lbl_80294AB8, 0, 0, 0);
        __ct__9C80253F24Fiiii(lbl_8035B65C, lbl_8035BEB8, 0, 0, 0);
        return;
    }
    fn_80064B8C(p, F(Wt *, 0x18c), dt);
    fn_800372B0(VP(0x50), VP(0x14));
    fn_800372B0(VP(0x5c), VP(0x20));
    fn_800372B0(VP(0x68), VP(0x2c));
    fn_800372B0(VP(0x74), VP(0x38));
    fn_800372B0(VP(0x80), VP(0x44));
    {
        f32 v = F(f32, 0xec);
        act = F(Act *, 0x9c);
        if (v < *F(f32 *, 0xd4)) v = lbl_8035BE98;
        else if (v > *F(f32 *, 0xdc)) v = *F(f32 *, 0xb0);
        else v = *F(f32 *, 0xb4) * v;
        if (lbl_8035A250 != 0) v *= lbl_8035BEC0;
        if (*(s32 *)((u8 *)act + 0x710) > 0) v *= *(f32 *)((u8 *)act + 0x714);
        F(f32, 0x170) = v;
    }
    if (lbl_80359748 == 5 && *F(s32 *, 0x184) == 0) F(f32, 0x170) = lbl_8035BE98;
    if (lbl_80306678[0] != 0) {
        f32 m;
        if (lbl_80306678[0]->f44 != 0) m = *lbl_80306678[0]->f44;
        else m = lbl_8035BE9C;
        F(f32, 0x170) = F(f32, 0x170) * m;
    }
    *(u32 *)((u8 *)act + 0x228) &= ~4;
    cam = *(u8 **)(lbl_8035B65C + 0x28);
    (*(void (**)(void *, V3 *))(lbl_803286D0 + 0x144))(*(void **)(cam + 0x10), &r);
    fn_80100F24(&r, lbl_803065D0);
    fn_80101820(&r);
    (*(void (**)(void *, V3 *))(lbl_803286D0 + 0x144))(*(void **)(cam + 0x10), &s);
    fn_80100F24(&s, lbl_803065D0);
    fn_80101820(&s);
    (*(void (**)(void *, V3 *))(lbl_803286D0 + 0x14c))(*(void **)(cam + 0x10), &u);
    fn_8003727C(&u, &lbl_80357AEC);
    (*(void (**)(void *, V3 *))(lbl_803286D0 + 0x14c))(*(void **)(cam + 0x10), &f);
    fn_80100F24(&f, lbl_803065D0);
    fn_80101820(&f);
    fn_8003723C(&c, &r, lbl_803065D0);
    fn_80101820(&c);
    if (c.x * u.x + c.y * u.y + c.z * u.z < lbl_8035BE98) fn_80037214(&c);
    fn_800371F8(&u, &c);
    if (!lbl_80359FCC) {
        lbl_80359FC8 = 1;
        lbl_80359FCC = 1;
    }
    if (*F(s32 *, 0xf8) == 0) {
        f32 k;
        if (F(f32, 0x15c) > (k = lbl_8035BEC4)) lbl_80359FC8 = 0;
        else if (F(f32, 0x70) < k) lbl_80359FC8 = 1;
        if (lbl_80359FC8 != 0) fn_800371F8(&u, VP(0x5c));
    }
    fn_80101820(&r);
    fn_80101820(&u);
    fn_800371D0(&r, F(f32, 0x158));
    fn_800371D0(&u, -F(f32, 0x15c));
    {
        u8 *t = lbl_8035B65C + 0x770;
        if (lbl_80359748 == 5 && lbl_8035A25C == 0) {
            a0 = fn_80037A38(t, 0x5f);
            fn_80037A38(t, 0x5e);
        } else {
            a0 = fn_80037A38(t, 0x60);
            fn_80037A38(t, 0x61);
        }
    }
    fn_800371D0(&s, a0);
    if (fn_800724A4(act)) F(Wt *, 0x18c) = (Wt *)lbl_802AFB44;
    else F(Wt *, 0x18c) = (Wt *)lbl_802AFAF0;
    if (fn_800724A4(act)) {
        if (lbl_80359748 == 5 && (f32)__fabs(a0) > lbl_8035BEC8) {
            t = lbl_8035BECC * a0 * dt;
            fn_80101414(VP(0x5c), VP(0x68), t);
            fn_80101414(VP(0x74), VP(0x68), t);
        }
        { f32 k = lbl_8035BEC8; h.x = k; h.y = k; h.z = k; }
        if (*(void **)(*(u8 **)((u8 *)act + 0xa0) + 0x78) != 0) fn_80107F3C(*(void **)(*(u8 **)((u8 *)act + 0xa0) + 0x78), &h);
        fn_800371F8(VP(0x80), VP(0x44));
        fn_800371F8(&a, &r);
        fn_8003727C(&a, &u);
        len0 = fn_8003714C(&a);
        fn_800371D0(&a, lbl_8035BED0);
        fn_80100F24(&a, lbl_803065D0);
        fn_8003714C(&a);
        lim = fn_8003714C(VP(0x80));
        fn_80037118(VP(0x80), &a, dt);
        { f32 k = lbl_8035BE98; z.x = k; z.y = k; z.z = k; }
        if (len0 < lbl_8035BED4) fn_80037060(VP(0x80), &z, lbl_8035BE9C, dt);
        {
            f32 l = fn_8003714C(VP(0x80));
            if (l > lbl_8035BED8 && l > lim) {
                fn_80101820(VP(0x80));
                fn_800371D0(VP(0x80), lim);
            }
        }
        fn_800371F8(&d, &lbl_80357E90);
        fn_80037214(&d);
        fn_800371D0(&d, lbl_8035BEE0);
        fn_80100F24(&d, lbl_803065D0);
        fn_8003714C(&d);
        fn_80037118(VP(0x80), &d, dt);
        len = fn_8003714C(VP(0x80));
        {
            u8 zr = 0;
            if (len >= lbl_8035BEE4 && len <= lbl_8035BEE8) zr = 1;
            if (!zr) {
                fn_80100F24(VP(0x80), lbl_803065D0);
                fn_80101820(VP(0x80));
                fn_800371D0(VP(0x80), len);
            }
        }
        fn_80037118(VP(0x50), VP(0x80), dt);
        if (*(s32 *)(FC + 0x73c) == 0) fn_8003727C(VP(0x50), (V3 *)(FC + 0x730));
        fn_8023BE44(VP(0x5c), *VP(0x80), lbl_80357E90, lbl_8035BEEC, lbl_8035BE98, dt);
    } else {
        fn_800371F8(VP(0x80), &r);
        fn_8003727C(VP(0x80), &u);
        fn_800371F8(&lbl_80302640, VP(0x80));
        fn_80101820(VP(0x80));
        if (F(f32, 0xec) > lbl_8035BE98) fn_80101820(&lbl_80302640);
        fn_800371D0(VP(0x80), F(f32, 0x170));
        fn_80037118(VP(0x50), VP(0x80), dt);
        if (*(s32 *)(FC + 0x73c) == 0) fn_8003727C(VP(0x50), (V3 *)(FC + 0x730));
        t = *(f32 *)(lbl_8035B488 + 0x14);
        if (*(s32 *)(FC + 0x4d4) != 0) {
            Act *o = F(Act *, 0x160);
            if (o != 0 && *(s32 *)(FC + 0x4d8) == 0) {
                o->getPos(&e, 0, 0, 0, 0);
                fn_8003702C(&lbl_80302640, &e, VP(0x50));
                fn_80100F24(&lbl_80302640, VP(0x2c));
                fn_80101820(&lbl_80302640);
                fn_8023BE44(VP(0x5c), lbl_80302640, lbl_80357E90, lbl_8035BEF0, lbl_8035BE98, t);
                fn_8003723C(VP(0x74), VP(0x68), VP(0x5c));
                fn_80101820(VP(0x74));
                fn_8003723C(VP(0x68), VP(0x5c), VP(0x74));
                fn_80101820(VP(0x68));
            }
        } else if (lbl_80359748 == 5) {
            if (F(f32, 0x15c) < lbl_8035BEF4)
                fn_8023BE44(VP(0x5c), lbl_80302640, lbl_80357E90, lbl_8035BEC0, lbl_8035BE98, t);
            if ((f32)__fabs(a0) > lbl_8035BEC8) {
                t = lbl_8035BECC * a0 * dt;
                fn_80101414(VP(0x5c), VP(0x68), t);
                fn_80101414(VP(0x74), VP(0x68), t);
            }
        } else if (lbl_80359748 == 1) {
            if (F(f32, 0x15c) < lbl_8035BEF4) {
                f32 v = F(f32, 0xec);
                fn_80037060(VP(0x5c), &lbl_80302640, lbl_8035BEC0 * v * v, v * t);
            }
        } else if (lbl_80359748 == 4) {
            fn_8023BE44(VP(0x5c), lbl_80302640, lbl_80357E90, lbl_8035BEF8, lbl_8035BE98, t);
        } else {
            fn_8023BE44(VP(0x5c), lbl_80302640, lbl_80357E90, lbl_8035BED0, lbl_8035BE98, t);
        }
    }
    if (lbl_8035B6E0 != 0) {
        fn_800371F8(VP(0x5c), &lbl_80357B04);
        fn_8003723C(VP(0x74), VP(0x5c), VP(0x68));
        fn_80101820(VP(0x74));
    }
    launch = 0;
    t0 = 0;
    t1 = 0;
    fn_80101820(VP(0x5c));
    fn_80101820(VP(0x68));
    fn_80101820(VP(0x74));
    Place(p, &q0);
    PlaceE(p, &q1);
    if (fn_80264E0C(&q0, &q1, &q3, &q2, &e0, &e1, &e2, 0, 0, 0, 0, 0, 0, 0, 1)) {
        Back(p);
        launch = 0;
        F(f32, 0x80) = lbl_8035BE98;
        F(f32, 0x84) = lbl_8035BE98;
        F(f32, 0x88) = lbl_8035BE98;
    }
    {
        u32 *o = (u32 *)lbl_80306678;
        o[0] = 0;
        o[1] = 0;
        o[2] = 0;
        o[3] = 0;
        o[4] = 0;
        o[5] = 0;
    }
    fn_8003702C(VP(0x174), VP(0x50), VP(0x14));
    fn_800371D0(VP(0x174), lbl_8035BE9C / dt);
    fn_800371F8(VP(0x174), VP(0x80));
    fn_800371F8(&save, lbl_803065D0);
    fn_80100CF4(bb);
    bb[0] = lbl_8035BE98;
    bb[1] = lbl_8035BE98;
    bb[2] = lbl_8035BE98;
    bb[3] = lbl_8035BE98;
    for (i = 0; i < 6; i++) {
        fn_800371F8(&lbl_803064F8[i], VP(0x50));
        fn_80037118(&lbl_803064F8[i], VP(0x5c), F(Wt *, 0x18c)->b[0]);
        fn_80037118(&lbl_803064F8[i], VP(0x68), F(Wt *, 0x18c)->b[1]);
        fn_80037118(&lbl_803064F8[i], VP(0x74), F(Wt *, 0x18c)->b[2]);
        fn_800371F8(&lbl_80306540[i], VP(0x50));
        fn_80037118(&lbl_80306540[i], VP(0x5c), F(Wt *, 0x18c)->e[i][0]);
        fn_80037118(&lbl_80306540[i], VP(0x68), F(Wt *, 0x18c)->e[i][1]);
        fn_80037118(&lbl_80306540[i], VP(0x74), F(Wt *, 0x18c)->e[i][2]);
        if (i == 2 && *(s32 *)(*(u8 **)(FC + 0x20c) + 0x60) == 0x13)
            fn_80037118(&lbl_80306540[2], VP(0x5c), lbl_8035BEFC);
        {
            f32 dd = fn_80101590(&lbl_80306540[i], &lbl_803064F8[i]);
            if (dd > bb[3]) bb[3] = dd;
        }
    }
    fn_800372B0((V3 *)bb, &lbl_803064F8[0]);
    fn_80264AC0(6, lbl_803064F8, lbl_80306540, bb, lbl_80306618, lbl_80306588, lbl_803065D0, lbl_80306630,
                lbl_80306648, lbl_80306660, lbl_80306678, 0, lbl_80306690, lbl_803066A8, lbl_803066F0, lbl_80306708, 0, 1);
    old = 0;
    if (lbl_80306618[0] != 0) {
        old = *(s32 *)(FC + 0x4c0);
        *(s32 *)(FC + 0x4c0) = 0;
        if (fn_80036F10(lbl_80306678[0])) {
            if (Get(lbl_80306678[0]->f34) == 0) t0 = lbl_80306678[0];
        }
        fn_800371F8(VP(0x50), lbl_80306588);
        if (lbl_80306678[0] != *(Tri **)(FC + 0x338)) {
            if (SetNm(&n0, lbl_80306678[0]->f8c)) __ct__9C80253F24Fiiii(lbl_8035B65C, n0.b, 0, 0, 0);
        }
        if (lbl_803065D0[0].z > lbl_8035BEC8) {
            fn_80037060(VP(0x68), &lbl_80357E90, lbl_8035BED0, dt);
            fn_80100F24(VP(0x5c), VP(0x68));
            fn_80036E44(FC, lbl_80306660[0]);
            fn_80036E28(FC, lbl_803065D0);
            *(Tri **)(FC + 0x338) = lbl_80306678[0];
        } else if (Get(lbl_80306678[0]->f4) != 0) {
            fn_800371F8(VP(0x50), VP(0x14));
            F(f32, 0x80) = lbl_8035BE98;
            F(f32, 0x84) = lbl_8035BE98;
            F(f32, 0x88) = lbl_8035BE98;
            fn_800371F8(lbl_803065D0, &save);
        } else {
            Reset(p);
            F(f32, 0x170) = fn_8003714C(VP(0x80));
            launch = 1;
        }
        if (Get(lbl_80306678[0]->f7c) != 0) {
            u8 *o = FC;
            *(s32 *)(o + 0x4e0) = 0;
            *(s32 *)(o + 0x620) = 1;
        }
    } else {
        Reset(p);
        F(f32, 0x170) = fn_8003714C(VP(0x80));
        launch = 1;
    }
    if (lbl_80306618[1] != 0) {
        if (fn_800724A4(act)) {
            fn_800371F8(&g, VP(0x80));
            fn_80101030(&g, &lbl_803065D0[1]);
            fn_80036FF8(VP(0x80), &g, lbl_8035BEC0);
            fn_800371D0(VP(0x80), lbl_8035BEC8);
        }
        if (fn_80036F10(lbl_80306678[1]) && t0 == 0) t0 = lbl_80306678[1];
    }
    if (lbl_80306618[2] != 0 && fn_80036F10(lbl_80306678[2]) && t0 == 0) t0 = lbl_80306678[2];
    if (lbl_80306618[3] != 0 && fn_80036F10(lbl_80306678[3]) && t0 == 0) t0 = lbl_80306678[3];
    if (lbl_80306618[4] != 0 && fn_80036F10(lbl_80306678[4]) && t0 == 0) t0 = lbl_80306678[4];
    if (lbl_80306618[5] != 0 && fn_80036F10(lbl_80306678[5]) && t0 == 0) t0 = lbl_80306678[5];
    any = 0;
    for (i = 0; i < 6; i++) {
        if (lbl_80306618[i] != 0) {
            Tri *o = lbl_80306678[i];
            if (Get(o->f34) != 0) {
                lbl_8035A1F0 = 1;
                *(Tri **)(FC + 0x5e4) = o;
            }
            if (SetNm(&n1, lbl_80306678[i]->f90)) {
                any = 1;
                if (fn_800F6CD0(&n1, lbl_8035A1F4.b) == 0) {
                    (*(Act **)(p + 0xfc))->play(&n1, 0, 0, &i, 0);
                    fn_800F6E88(&lbl_8035A1F4, &n1);
                }
            }
        }
        if (lbl_80306690[i] != 0) {
            if (SetNm(&n2, lbl_80306708[i]->f90)) {
                any = 1;
                if (fn_800F6CD0(&n2, lbl_8035A1F4.b) == 0) {
                    (*(Act **)(p + 0xfc))->play(&n2, 0, 0, &i, 0);
                    fn_800F6E88(&lbl_8035A1F4, &n2);
                }
            }
            if (fn_80036F10(lbl_80306708[i]) && t1 == 0) t1 = lbl_80306708[i];
        }
    }
    fn_80065740(p, t0, t1, dt);
    sw = F(s32, 0x180);
    mode = fn_80072988(FC, *VP(0x80));
    if (*(s32 *)(FC + 0x4d4) == 0 && mode != 0) mode = 1;
    if (fn_800724A4(act) && mode == 0 && len > lbl_8035BE9C) mode = 1;
    if (*(s32 *)(FC + 0x710) > 0) {
        fn_80036E0C(FC, &k0);
        fn_800371F8(&k1, VP(0x50));
        fn_8003702C(&k1, &k0, VP(0x50));
        mode = fn_80072988(FC, k1);
        if (mode == 1) mode = 2;
        else if (mode == 2) mode = 1;
        mode += 8;
    } else if (F(f32, 0xec) > *F(f32 *, 0xdc) || (fn_800724A4(act) && len > lbl_8035BE9C)) {
        mode += 4;
    }
    F(s32, 0x180) = mode;
    if (old != 0 || (F(s32, 0x180) != sw && sw != -1)) {
        switch (F(u32, 0x180)) {
        case 0: act->play(lbl_8035BF00, 0, 0, 0, 0); break;
        case 1: act->play(lbl_8035BF08, 0, 0, 0, 0); break;
        case 2: act->play(lbl_8035BF10, 0, 0, 0, 0); break;
        case 3: act->play(lbl_8035BF18, 0, 0, 0, 0); break;
        case 4: act->play(lbl_8035BF20, 0, 0, 0, 0); break;
        case 5: act->play(lbl_8035BF28, 0, 0, 0, 0); break;
        case 6: act->play(lbl_8035BF2C, 0, 0, 0, 0); break;
        case 7: act->play(lbl_8035BF34, 0, 0, 0, 0); break;
        case 8: act->play(lbl_8035BF3C, 0, 0, 0, 0); break;
        case 9: act->play(lbl_8035BF44, 0, 0, 0, 0); break;
        case 10: act->play(lbl_8035BF4C, 0, 0, 0, 0); break;
        case 11: act->play(lbl_8035BF54, 0, 0, 0, 0); break;
        case 12: act->play(lbl_8035BF5C, 0, 0, 0, 0); break;
        }
    }
    fn_800371F8(&m0, VP(0x50));
    fn_80065B48(p);
    fn_80101820(VP(0x5c));
    fn_80101820(VP(0x68));
    fn_8003723C(VP(0x74), VP(0x5c), VP(0x68));
    fn_80101820(VP(0x74));
    Place(p, &m1);
    PlaceE(p, &m2);
    if (fn_80264E0C(&m1, &m2, &m4, &m3, &e3, &e4, &e5, 0, 0, 0, 0, 0, 0, 0, 1)) {
        Back(p);
        launch = 0;
        F(f32, 0x80) = lbl_8035BE98;
        F(f32, 0x84) = lbl_8035BE98;
        F(f32, 0x88) = lbl_8035BE98;
        act->play(lbl_8035BF00, 0, 0, 0, 0);
    }
    if (launch) {
        Reset(p);
        F(Act *, 0x9c)->play(lbl_8035BF64, 0, 0, 0, 0);
    }
    if (!any) lbl_8035A1F4.b[0] = 0;
    fn_80064AF0(p);
    lbl_80359FC0 = F(f32, 0x58);
}

} /* extern "C" */
