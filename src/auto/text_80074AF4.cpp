// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
// NonMatching draft: 151 asm diff lines (49 structural): reg colouring of old/flag temps, NEAR/UNNEAR string-image load order, a few const-load schedules.
#include "common.h"

struct V3 { f32 x, y, z; };
struct Q4 { f32 x, y, z, w; };

struct C802449C4 {
    u8 b[0x40];
    C802449C4();
    ~C802449C4();
};

struct VO {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(f32);
    virtual void v12();
    virtual void v13(void *, void *, void *, void *, void *);
    virtual void v14(void *, void *, void *, void *, void *);
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32();
    virtual void v33(const char *, void *, s32, s32, s32);
};

struct M { u32 fl; u16 x4; u8 p6[0x30 - 6]; void *x30; u8 p34[0x78 - 0x34]; void *x78; };
struct Mf { u32 fl; };
struct En : VO { u8 p4[0x9c - 4]; Mf *x9c; };
struct A0 { u8 p0[0xa8]; void *xa8; void *xac; };
struct Q90 { u8 p0[0xc]; u32 xc; u8 p10[0x174 - 0x10]; f32 x174; f32 x178; };
struct Nd {
    u32 fl; u8 p4[0x10 - 4]; void *x10; u8 p14[0x20 - 0x14]; u32 x20; u8 p24[0x30 - 0x24]; void *x30;
    u8 p34[0x78 - 0x34]; void *x78; u8 p7c[0x90 - 0x7c]; Q90 *x90; u8 p94[0x98 - 0x94]; u32 x98; f32 x9c;
    u8 pa0[0xac - 0xa0]; f32 xac; void *xb0;
};
struct T6B8 { u8 p0[0xc]; f32 *xc; };
struct S3F4 { u32 fl; u8 p4[0x48 - 4]; void *x48; };
struct Lv { u8 p0[0xc0]; virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(char *, s32); };
struct G65C { u8 p0[0xc]; void *xc; };
struct G488 { u8 p0[0x27ec]; f32 x27ec; };
struct G460 { u8 p0[8]; void *x8; };
struct Ply : VO {
    u8 p4[0x10];
    V3 x14;
    V3 x20;
    V3 x2c;
    V3 x38;
    V3 x44;
    u8 p50[0x4c];
    M *x9c;
    A0 *xa0;
    u8 pa4[0x10];
    u32 xb4;
    u8 pb8[0x60];
    V3 x118;
    u8 p124[0xc];
    V3 x130;
    u8 p13c[0x1c];
    u32 x158[7];
    s32 x174;
    u8 p178[0x14];
    En *x18c;
    u8 p190[0x10];
    f32 x1a0;
    u8 p1a4[0x8];
    f32 x1ac;
    u8 p1b0[0x4];
    f32 x1b4;
    u8 p1b8[0x10];
    f32 *x1c8;
    u8 p1cc[0x24];
    void *x1f0;
    u8 p1f4[0x8];
    s32 x1fc;
    s32 x200;
    u8 p204[0x8];
    VO *x20c;
    u8 p210[0x48];
    VO *x258;
    u8 p25c[0x1cc];
    Nd *x428;
    Nd *x42c;
    Nd *x430;
    VO *x434;
    Nd *x438;
    void *x43c;
    Nd *x440;
    Nd *x444;
    u8 p448[0xc];
    void *x454;
    Nd *x458;
    V3 x45c;
    u8 x468[0x2c];
    u8 x494[4];
    u8 p498[0x30];
    s32 x4c8;
    s32 x4cc;
    s32 x4d0;
    s32 x4d4;
    s32 x4d8;
    s32 x4dc;
    s32 x4e0;
    s32 x4e4;
    s32 x4e8;
    s32 x4ec;
    s32 x4f0;
    s32 x4f4;
    f32 x4f8;
    u8 p4fc[0x4];
    f32 x500;
    f32 x504;
    u8 p508[0x1c];
    f32 *x524;
    u8 p528[0x8];
    f32 *x530;
    f32 *x534;
    u8 p538[0x18];
    f32 x550;
    u8 p554[0xc];
    s32 x560;
    u8 p564[0xbc];
    s32 x620;
    u8 p624[0x8];
    void *x62c;
    u8 p630[0x40];
    f32 x670;
    u8 p674[0x18];
    s32 x68c;
    u8 p690[0x4];
    f32 x694;
    u8 p698[0x4];
    f32 *x69c;
    u8 p6a0[0x8];
    f32 *x6a8;
    f32 x6ac;
    f32 x6b0;
    u8 x6b4;
    u8 p6b5[0x3];
    T6B8 *x6b8;
    f32 *x6bc;
    u8 p6c0[0x4];
    s32 x6c4;
    u8 p6c8[0x4];
    s32 x6cc;
    s32 x6d0;
    u8 p6d4[0x4];
    s32 x6d8;
    u8 p6dc[0x30];
    s32 x70c;
    s32 x710;
    f32 x714;
    void *x718;
    s32 x71c;
    u8 p720[0x4];
    V3 x724;
    V3 x730;
    u8 p73c[0x4];
    void *x740;
};

extern "C" {
extern char lbl_80298060[];
extern void *lbl_803286D0[];
extern char lbl_80357AE0[];
extern V3 lbl_80306868;
extern volatile s32 lbl_80359748;
extern s32 lbl_8035A238;
extern f32 lbl_8035A23C;
extern s32 lbl_8035A258;
extern s32 lbl_8035A25C;
extern s32 lbl_8035A264;
extern volatile f32 lbl_8035A268, lbl_8035A26C, lbl_8035A270, lbl_8035A274, lbl_8035A278;
extern f32 lbl_8035A27C, lbl_8035A280;
extern s32 lbl_8035A284;
extern volatile s32 lbl_8035A288;
extern volatile s8 lbl_8035A28C;
extern volatile f32 lbl_8035A290;
extern volatile s8 lbl_8035A294;
extern volatile f32 lbl_8035A298;
extern volatile s8 lbl_8035A29C;
extern volatile s32 lbl_8035A2A0;
extern volatile s8 lbl_8035A2A4;
extern volatile s32 lbl_8035A2A8;
extern volatile s8 lbl_8035A2AC;
extern volatile s8 lbl_8035A2AD;
extern void *lbl_8035B374;
extern G460 *lbl_8035B460;
extern G488 *lbl_8035B488;
extern G65C *volatile lbl_8035B65C;
extern Lv *lbl_8035B684;
extern s32 lbl_8035B6E8, lbl_8035B6EC;
extern u32 lbl_8035F3E8, lbl_8035F3F0, lbl_8035F400, lbl_8035F404, lbl_8035F408;
extern volatile f32 lbl_8035F3EC;
extern volatile f32 lbl_8035F4E0, lbl_8035F4F8, lbl_8035F598, lbl_8035F4F0, lbl_8035F4F4;
extern f32 lbl_8035F500;
extern f64 lbl_8035F440, lbl_8035F4B8, lbl_8035F5B0;
extern f32 lbl_8035F448, lbl_8035F45C, lbl_8035F490, lbl_8035F4A0, lbl_8035F4A8,
    lbl_8035F548, lbl_8035F550, lbl_8035F56C,
    lbl_8035F59C, lbl_8035F5A8, lbl_8035F5B8, lbl_8035F5BC, lbl_8035F5C0, lbl_8035F5C4, lbl_8035F5C8;
extern char lbl_8035F40C[8], lbl_8035F478[8], lbl_8035F518[8], lbl_8035F554[5], lbl_8035F55C[8], lbl_8035F564[6],
    lbl_8035F570[8], lbl_8035F578[8], lbl_8035F580[7], lbl_8035F588[7], lbl_8035F590[7], lbl_8035F5A0[8];

void __ct__9C80253F24Fiiii(void *, char *, s32, s32, s32);
void fn_8003702C(V3 *, V3 *, V3 *);
void fn_80037118(V3 *, V3 *, f32);
f32 fn_8003714C(V3 *);
void fn_800371D0(V3 *, f32);
void fn_800371F8(V3 *, V3 *);
void fn_80037214(V3 *);
void fn_8003723C(V3 *, V3 *, V3 *);
void fn_800372B0(V3 *, V3 *);
s32 fn_800377E0(void *, s32);
f32 fn_80037A38(void *, s32);
s32 fn_80037AA4(void *, s32);
void fn_8007225C(Ply *, f32);
void fn_800724AC(Ply *);
void fn_80072944(Ply *);
void fn_80072D94(Ply *, s32, f32);
void fn_80072DB8(void);
void fn_80073E4C(Ply *, s32);
void fn_800746E8(Ply *);
void fn_8007479C(Ply *);
void fn_80076974(void *, V3 *);
void fn_80076990(M *, V3 *, V3 *);
void fn_80076A04(f32 *, f32);
void fn_80076A2C(void *, f32);
void fn_80076A50(M *, V3 *);
void fn_80076A98(M *, V3 *, V3 *, V3 *);
void fn_80076AD8(void *, V3 *);
void fn_80076B40(M *, V3 *, V3 *, V3 *);
Nd *fn_80076BAC(void *, char *, s32);
void fn_80076C00(void *, V3 *);
void fn_80076D50(Ply *, s32);
f32 fn_80076E54(f32, f32);
double fn_800EFDA4(double);
int fn_800F6CD0(char *, char *);
void fn_80101414(V3 *, V3 *, f32);
f32 fn_80101590(V3 *, V3 *);
void fn_80101820(V3 *);
void *fn_8010511C(void *, char *);
void fn_80107244(void *, V3 *);
void fn_801074D0(void *, V3 *, V3 *, V3 *);
void fn_801075B8(void *, Q4 *);
void fn_801078CC(void *, V3 *, V3 *, V3 *, V3 *, s32);
void fn_801079E8(void *, Q4 *, V3 *, s32);
void fn_80107F3C(void *, V3 *);
void *fn_80185A54(void *, s32);
void fn_80190C98(Nd *);
void fn_80196688(Nd *);
void fn_8019B7E8(void *, void *);
void fn_8022BE28(Ply *, void *);
S3F4 *fn_8022C3F4(Ply *);
void fn_8022CBD4(Ply *, f32);
void fn_8022CF14(Ply *, f32);
u32 *fn_8022D694(Ply *);
void *fn_80233550(void *, char *);
void fn_80236EA0(Ply *, f32);
void fn_80236F28(Ply *, f32, f32, char *, s32, s32, En *, s32);
f32 fn_8023D494(void *, f32, f32);
void fn_80241DD0(VO *, char *, s32, s32, s32, s32);
En *fn_80242144(VO *, s32);
void *fn_8024457C(C802449C4 *);
s32 fn_80244584(C802449C4 *);
void fn_80244594(C802449C4 *);
void fn_80244750(C802449C4 *, s32);
void fn_802448C8(C802449C4 *, void *);
s32 fn_80264E0C(V3 *, V3 *, V3 *, V3 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

static inline void Ev(char *s) { __ct__9C80253F24Fiiii(lbl_8035B65C, s, 0, 0, 0); }
static inline void Dz(volatile f32 *x) {
    f32 k;
    f32 v = *x;
    if (v < lbl_8035F598) {
        *x = v + lbl_8035F4E0;
        *x = *x * lbl_8035F4F8;
    } else if (v > (k = lbl_8035F4E0)) {
        *x = v - k;
        *x = *x * lbl_8035F4F8;
    } else {
        *x = lbl_8035F3EC;
    }
}
static inline f32 Dot(V3 *a, V3 *b) { return a->x * b->x + a->y * b->y + a->z * b->z; }
static inline f32 Ang(Ply *p) { return fn_800EFDA4(lbl_8035F500 * *p->x524); }

void fn_80074AF4(Ply *p, f32 dt) {
    char *str = lbl_80298060;
    u8 *in;
    u8 *g;
    s32 old;
    En *t;
    Nd *n;
    void *w;

    if (p->x6cc && p->x6d0 < 10) {
        if (lbl_8035A258) fn_80072DB8();
        p->x6d0++;
        if (p->x6d0 >= 10) p->x6cc = 0;
    }
    if (p->x44.z > lbl_8035A23C) lbl_8035A23C = p->x44.z;
    fn_800372B0(&p->x730, &p->x724);
    p->x724.x = lbl_8035F3EC;
    p->x724.y = lbl_8035F3EC;
    p->x724.z = lbl_8035F3EC;
    if (!p->x4f4) {
        p->x4f8 -= dt;
        if (p->x4f8 <= lbl_8035F3EC) p->x4f4 = 1;
    }
    g = (u8 *)lbl_8035B65C;
    in = g + 0x770;
    if (lbl_8035F3EC == dt) {
        if (fn_80037AA4(in, 0x68) && !lbl_8035A284) lbl_8035B488->x27ec = lbl_8035F490;
        lbl_8035A284 = fn_80037AA4(in, 0x68);
        return;
    }
    lbl_8035A284 = 1;
    if (p->x718 && p->x71c) {
        V3 a, b;
        p->x258->v13(&a, &b, 0, 0, 0);
        fn_80037118(&a, &b, lbl_8035F4F8);
        fn_80076C00(p->x718, &a);
    }
    p->x710 = p->x70c;
    p->x70c = 0;
    if (lbl_8035A264) return;
    if (p->x68c) {
        V3 pos;
        if (p->x1ac <= lbl_8035F3EC) p->v33(lbl_8035F554, 0, 0, 0, 0);
        fn_800371F8(&pos, &p->x44);
        p->x500 = fn_80037A38(in, 0x5e);
        p->x504 = fn_80037A38(in, 0x5f);
        if (lbl_80359748 == 5 && !lbl_8035A25C) {
            p->x500 = lbl_8035F3EC;
            p->x504 = lbl_8035F3EC;
        }
        p->x500 = fn_80076E54(p->x500, lbl_8035F4A8);
        p->x504 = fn_80076E54(p->x504, lbl_8035F4A8);
        lbl_8035A27C = p->x504;
        lbl_8035A280 = p->x500;
        old = p->x4dc;
        p->x4dc = fn_80037AA4(in, 0x67);
        if (p->x4dc && !old) {
            fn_80241DD0(p->x20c, str + 0xe4, 0, 0, 0, 0);
        } else if (!p->x4dc && old) {
            fn_80241DD0(p->x20c, str + 0xf0, 0, 0, 0, 0);
        }
        if (p->x6ac > lbl_8035F3EC) {
            p->x6ac -= dt;
            f32 k;
            k = lbl_8035F3EC;
            p->x6ac = p->x6ac < k ? k : p->x6ac;
        }
        old = p->x4c8;
        p->x4c8 = fn_80037AA4(in, 0x6a);
        if (p->x4c8 && !old) {
            p->x6b0 = lbl_8035F3EC;
            fn_80241DD0(p->x20c, str + 0xfc, 0, 0, 0, 0);
            fn_80076D50(p, 1);
            fn_80072944(p);
            if (p->x6b4 == 6) {
                Nd *a = fn_80076BAC(lbl_8035B460->x8, lbl_8035F40C, 0);
                Nd *b = fn_80076BAC(lbl_8035B460->x8, str + 0x30, 0);
                if (a) {
                    if (p->x440) p->x440->x98 |= lbl_8035F400;
                    if (p->x444) p->x444->x98 |= lbl_8035F400;
                    p->x440 = a;
                    p->x444 = b;
                    p->x440->fl |= lbl_8035F3E8;
                    p->x444->fl |= lbl_8035F3E8;
                    n = p->x440;
                    n->x9c = lbl_8035F3EC;
                    n->x98 &= ~6;
                    n->xac = lbl_8035F3EC;
                    fn_80196688(n);
                    n = p->x444;
                    n->x9c = lbl_8035F3EC;
                    n->x98 &= ~6;
                    n->xac = lbl_8035F3EC;
                    fn_80196688(n);
                    p->x440->x98 |= lbl_8035F404;
                    p->x444->x98 |= lbl_8035F404;
                    p->x440->x98 &= ~8;
                    p->x444->x98 &= ~8;
                    p->x434->v33(str + 0x108, 0, 0, 0, 0);
                }
                if (p->x440) {
                    Q90 *q = p->x440->x90;
                    q->x174 = lbl_8035F440 * (p->x6b0 / p->x6b8->xc[p->x6b4]);
                    q->x178 = q->x174;
                    q->xc |= lbl_8035F408;
                }
                if (p->x444) {
                    Q90 *q = p->x444->x90;
                    q->x174 = lbl_8035F440 * (p->x6b0 / p->x6b8->xc[p->x6b4]);
                    q->x178 = q->x174;
                    q->xc |= lbl_8035F408;
                }
            }
        } else if (!p->x4c8 && old) {
            if (p->x4cc) {
                p->x6ac = *p->x6a8;
                fn_80241DD0(p->x20c, str + 0x114, 0, 0, 0, 0);
                p->x6b0 = lbl_8035F3EC;
            }
            fn_80076D50(p, 0);
        }
        if (p->x4c8 && p->x4cc) {
            p->x694 = p->x6b0;
            if (lbl_8035F3EC == p->x6ac && p->x6b0 < *p->x69c) {
                p->x6b0 += dt;
                if (p->x6b4 == 6) {
                    if (p->x6b0 > p->x6b8->xc[p->x6b4]) {
                        fn_80073E4C(p, 1);
                        p->x6b0 -= *p->x6bc;
                    }
                } else {
                    f32 m;
                    if (p->x6b0 > p->x6b8->xc[p->x6b4]) fn_800724AC(p);
                    m = p->x6b8->xc[p->x6b4];
                    if (p->x6b0 > m) p->x6b0 = m;
                    m = *p->x69c;
                    if (p->x6b0 > m) p->x6b0 = m;
                }
            }
        }
        old = p->x4e4;
        p->x4e4 = fn_80037AA4(in, 0x69);
        if (p->x4e4 && !old) {
            fn_80241DD0(p->x20c, lbl_8035F55C, 0, 0, 0, 0);
            t = p->x18c;
            if (t) {
                fn_80236F28(p, lbl_8035F56C, Ang(p), lbl_8035F564, 1, 1, p->x18c, 0);
                if (!p->x18c) p->x18c = t;
            }
        } else if (!p->x4e4 && old) {
            fn_80241DD0(p->x20c, lbl_8035F570, 0, 0, 0, 0);
        }
        p->x4d0 = fn_80037AA4(in, 0x6c);
        if (!lbl_8035A25C) {
            if (p->x4d0) {
                if (lbl_80359748 == 3) {
                    lbl_80359748 = 5;
                    Ev(str + 0x120);
                }
            } else if (lbl_80359748 == 5) {
                lbl_80359748 = 3;
                Ev(str + 0x12c);
            }
        } else {
            if (p->x4d0) {
                if (lbl_80359748 == 5) {
                    lbl_80359748 = 3;
                    Ev(str + 0x12c);
                }
            } else if (lbl_80359748 == 3) {
                lbl_80359748 = 5;
                Ev(str + 0x120);
            }
        }
        old = p->x4d4;
        p->x4d4 = fn_80037AA4(in, 0x6d);
        if (p->x4d4) {
            lbl_8035B6EC = 1;
        } else {
            lbl_8035B6EC = 0;
            if (old && p) {
                p->v13(0, lbl_80357AE0, 0, 0, 0);
                lbl_8035B6E8 = 1;
            }
        }
        {
            u8 j;
            old = p->x4e0;
            j = 0;
            if (fn_80037AA4(in, 0x68) || p->x620) j = 1;
            p->x4e0 = j;
        }
        if (lbl_80359748 == 5 && !lbl_8035A25C) p->x4e0 = 0;
        if (p->x4e0 && !old) {
            if (p->x620) {
                p->x118.x = lbl_8035F3EC;
                p->x118.y = lbl_8035F3EC;
                p->x118.z = lbl_8035F3EC;
                p->x130.x = lbl_8035F3EC;
                p->x130.y = lbl_8035F3EC;
                p->x130.z = lbl_8035F3EC;
                p->x620 = 0;
                fn_80241DD0(p->x20c, str + 0x138, 0, 0, 0, 0);
            } else {
                fn_80241DD0(p->x20c, str + 0x144, 0, 0, 0, 0);
            }
        } else if (!p->x4e0 && old) {
            fn_80241DD0(p->x20c, str + 0x150, 0, 0, 0, 0);
        }
        {
            u8 k;
            old = p->x4f0;
            k = 0;
            if (fn_80037AA4(in, 0x71) || lbl_8035F3EC != fn_80037A38(in, 0x64) || lbl_8035F3EC != fn_80037A38(in, 0x65)) k = 1;
            p->x4f0 = k;
        }
        if (!p->x6c4 && p->x4f4 && p->x4f0 && !old) {
            char name[8];
            lbl_8035B684->s3(name, -1);
            if (!fn_800F6CD0(name, lbl_8035F578) && !fn_800F6CD0(name, lbl_8035F580) && !fn_800F6CD0(name, lbl_8035F588))
                Ev(lbl_8035F590);
        }
        old = p->x4e8;
        p->x4e8 = fn_800377E0(g + 0x804, 0x7d);
        if (p->x4e8 && !old) {
            if (p->x6c4) Ev(str + 0x84);
            else Ev(lbl_8035F478);
        }
        old = p->x4ec;
        p->x4ec = fn_800377E0(g + 0x804, 0x7e);
        if (p->x4ec && !old) Ev(str + 0x15c);
        if (p->x560) {
            f32 k;
            p->x550 -= dt;
            if (p->x550 < (k = lbl_8035F3EC)) {
                p->x550 = k;
                p->v33(lbl_8035F554, 0, 0, 0, 0);
            }
        }
    }
    {
        V3 pos2;
        V3 a, b;
        V3 me, o;
        V3 t198, t18c, t180;
        V3 ov;
        V3 cur;
        fn_800371F8(&pos2, &p->x44);
        fn_8022CF14(p, dt);
        if (p->x20c) {
            void *an;
            p->x20c->v11(dt);
            an = p->xa0 ? p->xa0->xac : 0;
            if (an && !(p->xb4 & 1) && fn_8022D694(p) && (*fn_8022D694(p) & 0x10)) {
                p->xb4 |= 1;
                fn_80241DD0(p->x20c, str + 0x168, 0, 0, 0, 0);
            }
        }
        fn_800371F8(&p->x130, &p->x118);
        if (p->x1b4 > lbl_8035F3EC) fn_8007225C(p, dt * p->x1b4);
        if (p->x1a0 > lbl_8035F3EC) {
            f32 s;
            if (p->x710 > 0) s = p->x1a0 * (fn_8003714C(&p->x118) / p->x714);
            else s = p->x1a0 * fn_8003714C(&p->x118);
            fn_8022CBD4(p, s);
        }
        if (p->x9c) {
            fn_80076C00(p->x9c, &p->x44);
            fn_800371F8(&a, &p->x20);
            fn_800371F8(&b, &p->x14);
            fn_80037214(&a);
            fn_80037214(&b);
            fn_80076B40(p->x9c, &a, &b, &p->x2c);
            if (p->x9c->x4 == 1 && p->x9c->x78) fn_80107F3C(p->x9c->x78, &p->x38);
            if (p->x174) {
                u32 i;
                for (i = 0; i < 7; i++) {
                    if (p->x158[i] != 0xFFFFFFFF) {
                        C802449C4 it;
                        s32 st = p->x158[i];
                        s32 found = 0;
                        fn_80076AD8(p->x9c, &me);
                        {
                            En *l = fn_80242144(p->x20c, i);
                            fn_802448C8(&it, (void *)l);
                        }
                        fn_80244750(&it, 0);
                        while (!fn_80244584(&it)) {
                            fn_80076AD8(((En *)fn_8024457C(&it))->x9c, &o);
                            f32 dd = fn_80101590(&me, &o);
                            if (dd <= (p->x1c8 ? *p->x1c8 : lbl_8035F550)) {
                                if (st == 0) {
                                    char s[8] = "NEARG";
                                    s[5] = '0' + i;
                                    s[6] = 0;
                                    p->v33(s, fn_8024457C(&it), 0, 0, 0);
                                }
                                found = 1;
                                break;
                            }
                            fn_80244594(&it);
                        }
                        if (st == 1 && !found) {
                            char s[8] = "UNNEARG";
                            s[7] = '0' + i;
                            p->v33(s, 0, 0, 0, 0);
                        }
                        p->x158[i] = found;
                    }
                }
            }
            if (p->x1fc) {
                if (p->x200) {
                    fn_8022BE28(p, 0);
                    p->x200 = 0;
                } else {
                    fn_8022BE28(p, p->x1f0);
                    p->x200 = 1;
                }
            }
        }
        fn_80076A98(p->x9c, &t198, &t18c, &t180);
        fn_8007479C(p);
        if (fn_80233550(lbl_8035B374, lbl_8035F518) && !p->x560) {
            if (p->x4d4 && !p->x4d8 && (!p->x18c || !(p->x18c->x9c->fl & 2))) {
                fn_80236F28(p, lbl_8035F56C, Ang(p), lbl_8035F564, 1, 1, 0, 0);
            } else if (!p->x4d4 || p->x4d8) {
                fn_80236EA0(p, lbl_8035F56C);
            }
        }
        if (p->x18c) {
            p->x18c->v13(&ov, 0, 0, 0, 0);
            if (fn_80101590(&ov, &p->x44) < lbl_8035F490) p->x18c = 0;
        }
        if (p->x670 >= lbl_8035F3EC) {
            if (!lbl_8035A28C) {
                lbl_8035A288 = 1;
                lbl_8035A28C = 1;
            }
            p->x670 -= dt;
            if (p->x670 <= lbl_8035F3EC) {
                fn_80072D94(p, 0, lbl_8035F45C);
                p->v19();
            } else if (fn_8022C3F4(p)->fl & 0x800) {
                p->v20();
            } else {
                p->v19();
            }
        } else {
            if (!(fn_8022C3F4(p)->fl & 0x800)) p->v19();
            if (!fn_8022C3F4(p)->x48) {
                w = lbl_8035B65C->xc;
                fn_8019B7E8(w, fn_8022C3F4(p));
            }
        }
        if (lbl_8035A238) {
            if (p->x68c) {
                lbl_8035A268 = fn_80037A38(in, 0x5f);
                lbl_8035A270 = fn_80037A38(in, 0x5e);
                lbl_8035A26C = fn_80037A38(in, 0x60);
                {
                    f32 m = -(lbl_8035F500 * *p->x530);
                    lbl_8035A26C = lbl_8035A26C * m;
                }
                lbl_8035A274 = lbl_8035F3EC;
                lbl_8035A278 = lbl_8035F3EC;
            }
        } else {
            f32 v;
            f32 v2;
            f32 k;
            if (!lbl_8035A294) {
                lbl_8035A290 = lbl_8035F3EC;
                lbl_8035A294 = 1;
            }
            if (!lbl_8035A29C) {
                lbl_8035A298 = lbl_8035F3EC;
                lbl_8035A29C = 1;
            }
            if (p->x68c) {
                if (lbl_80359748 == 5 && !lbl_8035A25C) {
                    lbl_8035A268 = fn_80037A38(in, 0x5f);
                    lbl_8035A270 = fn_80037A38(in, 0x5e);
                } else {
                    lbl_8035A268 = fn_80037A38(in, 0x60);
                    lbl_8035A270 = fn_80037A38(in, 0x61);
                }
                if (lbl_80359748 == 5 && lbl_8035A25C) lbl_8035A270 = lbl_8035A270 * lbl_8035F548;
                Dz(&lbl_8035A270);
                Dz(&lbl_8035A268);
            }
            lbl_8035A274 = lbl_8035F3EC;
            lbl_8035A278 = lbl_8035F3EC;
            t = p->x18c;
            if (t) {
                v = lbl_8035A268;
                if (v < (k = lbl_8035F598) && lbl_8035A290 > k) {
                    fn_80236F28(p, lbl_8035F56C, Ang(p), lbl_8035F564, 1, 1, p->x18c, 2);
                    if (p->x18c == t || !p->x18c) fn_80236F28(p, lbl_8035F56C, Ang(p), lbl_8035F564, 1, 1, t, 0);
                } else if (v > (k = lbl_8035F4E0) && lbl_8035A290 < k) {
                    fn_80236F28(p, lbl_8035F56C, Ang(p), lbl_8035F564, 1, 1, p->x18c, 1);
                    if (p->x18c == t || !p->x18c) fn_80236F28(p, lbl_8035F56C, Ang(p), lbl_8035F564, 1, 1, t, 0);
                }
                v2 = lbl_8035A270;
                if (v2 < (k = lbl_8035F598) && lbl_8035A298 > k) {
                    fn_80236F28(p, lbl_8035F56C, Ang(p), lbl_8035F564, 1, 1, p->x18c, 3);
                    if (p->x18c == t || !p->x18c) fn_80236F28(p, lbl_8035F56C, Ang(p), lbl_8035F564, 1, 1, t, 0);
                } else if (v2 > (k = lbl_8035F4E0) && lbl_8035A298 < k) {
                    fn_80236F28(p, lbl_8035F56C, Ang(p), lbl_8035F564, 1, 1, p->x18c, 4);
                    if (p->x18c == t || !p->x18c) fn_80236F28(p, lbl_8035F56C, Ang(p), lbl_8035F564, 1, 1, t, 0);
                }
                if (!p->x18c) p->x18c = t;
            }
            lbl_8035A290 = lbl_8035A268;
            lbl_8035A298 = lbl_8035A270;
        }
        if (p->x4d4 && p->x18c) lbl_8035A270 = lbl_8035F3EC;
        if (p->x68c) {
            lbl_8035A270 = lbl_8035A270 * -(lbl_8035F500 * *p->x534);
            lbl_8035A268 = lbl_8035A268 * -(lbl_8035F500 * *p->x530);
        }
        fn_80107244(p->x454, &cur);
        if (!lbl_8035A2A4) {
            lbl_8035A2A0 = 0;
            lbl_8035A2A4 = 1;
        }
        if (!lbl_8035A2AC) {
            lbl_8035A2A8 = 0;
            lbl_8035A2AC = 1;
        }
        if (lbl_8035A238) {
            V3 sc;
            Q4 q;
            ((void (*)(void *, V3 *))lbl_803286D0[0x130 / 4])(p->x458->x10, &sc);
            sc.z = lbl_8035F490;
            n = p->x458;
            ((void (*)(void *, V3 *))lbl_803286D0[0xc / 4])(n->x10, &sc);
            n->x20 |= lbl_8035F3F0;
            if (p->x9c->x30) fn_801075B8(p->x9c->x30, &q);
            fn_80076A50(p->x9c, &p->x44);
            if (p->x42c) {
                V3 h;
                h.z = h.y = h.x = lbl_8035F4E0;
                if (p->x42c->x78) fn_80107F3C(p->x42c->x78, &h);
                p->x42c->fl &= ~2;
                n = p->x42c;
                if (n->x30) {
                    fn_801079E8(n->x30, &q, &p->x44, 0);
                    fn_80190C98(n);
                }
                w = p->x42c->xb0;
                fn_80076A2C(w, lbl_8035F59C * fn_8003714C(&p->x118));
            }
            lbl_8035A2A8 = 1;
            if (p->x430) {
                V3 s0, s1, hit, nrm;
                fn_800372B0(&s0, &p->x44);
                s0.z += lbl_8035F448;
                fn_800372B0(&s1, &p->x44);
                s1.z -= lbl_8035F4F8;
                if (!fn_80264E0C(&s0, &s1, &hit, &nrm, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)) {
                    p->x430->fl &= ~0x800;
                } else {
                    V3 c, d, e;
                    f32 s, k;
                    fn_8003723C(&c, &p->x14, &nrm);
                    fn_8003723C(&d, &nrm, &c);
                    fn_80101820(&c);
                    fn_80101820(&d);
                    hit.z += lbl_8035F448;
                    p->x430->fl |= lbl_8035F3E8;
                    fn_80037214(&d);
                    fn_80037214(&c);
                    n = p->x430;
                    if (n->x30) {
                        fn_801078CC(n->x30, &c, &d, &nrm, &hit, 0);
                        fn_80190C98(n);
                    }
                    s = -((p->x44.z - hit.z) * lbl_8035F4A0 - lbl_8035F4E0);
                    k = lbl_8035F3EC;
                s = s < k ? k : s;
                    e.x = s;
                    e.y = s;
                    e.z = s;
                    if (p->x430->x78) fn_80107F3C(p->x430->x78, &e);
                }
            }
        } else if (p->x560) {
            V3 c;
            lbl_8035A2A0 = 1;
            c.z = c.y = c.x = lbl_8035F4F0;
            p->v14(0, 0, 0, 0, &c);
        } else {
            if (lbl_8035A2A0) {
                fn_800746E8(p);
                lbl_8035A2A0 = 0;
            }
            if (lbl_8035A2A8) {
                fn_800746E8(p);
                lbl_8035A2A8 = 0;
            }
        }
        {
            V3 d4, c8, bc;
            V3 tb0, vel, acc, t8c;
            volatile f32 b, d, a, c;
            V3 t80, t74;
            p->v13(0, &d4, &bc, &c8, 0);
            fn_800371F8(&t198, &c8);
            fn_800371F8(&t18c, &d4);
            fn_801074D0(fn_8010511C(p->xa0->xa8, lbl_8035F5A0), &t198, &t18c, &tb0);
            if (!lbl_8035A2AD) {
                lbl_80306868.z = lbl_80306868.y = lbl_80306868.x = lbl_8035F3EC;
                lbl_8035A2AD = 1;
            }
            if (dt > lbl_8035F5A8) dt = lbl_8035F5A8;
            fn_8003702C(&vel, &cur, &p->x45c);
            fn_800371D0(&vel, lbl_8035F490 / dt);
            if (fn_8003714C(&vel) > lbl_8035F5B0) {
                vel.z = vel.y = vel.x = lbl_8035F3EC;
            }
            fn_8003702C(&acc, &vel, &lbl_80306868);
            fn_800371D0(&acc, lbl_8035F4B8 / dt);
            fn_8003702C(&t8c, &cur, &p->x45c);
            a = lbl_8035F4A0 * (vel.x * t18c.x + vel.y * t18c.y + vel.z * t18c.z);
            fn_80076A04((f32 *)&a, lbl_8035F4F4);
            b = -fn_8023D494(p->x468, dt, a);
            fn_80076A04((f32 *)&b, lbl_8035F4E0);
            c = lbl_8035F5B8 * -Dot(&vel, &tb0);
            fn_80076A04((f32 *)&c, lbl_8035F4F4);
            d = -fn_8023D494(p->x494, dt, c);
            fn_80076A04((f32 *)&d, lbl_8035F4E0);
            fn_800371F8(&t80, &t18c);
            fn_80101414(&t198, &tb0, b);
            fn_80101414(&t18c, &tb0, b);
            fn_80101414(&t198, &t80, d);
            fn_80101414(&tb0, &t80, d);
            fn_80037214(&tb0);
            n = p->x428;
            if (n->x30) {
                fn_801078CC(n->x30, &tb0, &t18c, &t198, &cur, 0);
                fn_80190C98(n);
            }
            fn_800371F8(&p->x45c, &cur);
            fn_800371F8(&lbl_80306868, &vel);
            fn_80037118(&cur, &p->x14, lbl_8035F5BC);
            fn_80037118(&cur, &p->x2c, lbl_8035F5BC);
            fn_80037118(&cur, &p->x20, lbl_8035F5C0);
            p->x434->v14(&cur, 0, 0, 0, 0);
            fn_800372B0(&t74, &cur);
            fn_80037118(&t74, &t198, lbl_8035F5C4);
            n = p->x440;
            if (n && n->x30) {
                fn_801078CC(n->x30, &tb0, &t18c, &t198, &t74, 0);
                fn_80190C98(n);
            }
            n = p->x444;
            if (n && n->x30) {
                fn_801078CC(n->x30, &tb0, &t18c, &t198, &t74, 0);
                fn_80190C98(n);
            }
            fn_80037118(&t74, &t198, lbl_8035F5C8);
            if (p->x62c) fn_80076C00(p->x62c, &t74);
            if (p->x6d8) {
                V3 t68, t5c, t50;
                if (p->x438) p->x438->fl |= lbl_8035F3E8;
                fn_800371F8(&t68, &p->x44);
                t68.z = cur.z;
                fn_80076C00(p->x43c, &t68);
                fn_80076990(p->x9c, &cur, &t5c);
                fn_800372B0(&t50, &t5c);
                fn_80076974(fn_80185A54(p->x740, 1), &t5c);
            } else if (p->x438) {
                p->x438->fl &= ~0x800;
            }
        }
    }
}
} /* extern "C" */
