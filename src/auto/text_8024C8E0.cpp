// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V30 { u8 pad[644]; int f644; u8 pad648[8]; f32 f656; };
struct V72 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9();
    virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27(); virtual void a28(); virtual void a29();
    virtual void a30(); virtual void a31(); virtual void a32(); virtual void play(const char *, int, int, int, int); };
struct G308 { u8 pad[72]; V72 *f72; V30 *f76; };
extern G308 *lbl_8035B308;
struct E52 { u8 pad[52]; };
struct G5E4 { u8 pad[104]; int f104; u8 pad108[4]; E52 *f112; };
extern G5E4 *lbl_8035B5E4;
extern void *lbl_8035B594;
extern void *lbl_8035B79C;
struct G65C { u8 pad[752]; virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void stop(int); };
extern G65C *lbl_8035B65C;
extern f32 lbl_803663B8;
extern char lbl_803663F0[8];
extern char lbl_802A9314[];
struct S156 { u8 pad[28]; virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(int); };
struct R40 { u8 pad[40]; int f40; };
struct T {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(int);
    u8 pad4[16]; u8 f20[8]; int f28; u8 pad32[8]; int f40; u8 pad44[40]; f32 f84; u32 f88; u8 pad92[12]; int *f104; u8 pad108[4]; int f112; u8 pad116[16]; int f132; u32 f136; int f140; u8 pad144[12]; S156 *f156;
};
void fn_80222ED0(V30 *, int);
void *fn_800F8274(void *, const char *);
u32 fn_80253664(void *, int);
int fn_8024D814(void *, void *, void *);
R40 *fn_8024E3DC(void *, void *, void *);
void fn_80268020(void *);
void fn_8024C18C(T *);
void fn_80253250(E52 *);
static inline bool busy(V30 *o) { return o->f644 != 0 || o->f656 != lbl_803663B8; }
void fn_8024C8E0(T *t) {
    u32 a;
    u32 c;
    u32 b;
    V30 *o = lbl_8035B308->f76;
    if (o && busy(o)) fn_80222ED0(o, 0);
    t->f136 = fn_80253664(fn_800F8274(lbl_8035B5E4, lbl_803663F0), 76) != 0;
    t->f140 = 0;
    if (t->f40 != 0) return;
    if (fn_8024D814(lbl_8035B594, &a, &b)) {
        fn_8024E3DC(lbl_8035B594, t->f20, &c);
        if (fn_8024E3DC(lbl_8035B594, &a, &b)->f40 == 0) {
            t->v11(0);
            return;
        }
    }
    t->f28 = 2;
    t->f84 = lbl_803663B8;
    for (u32 i = 0; i < t->f88; i++) {
        if (t->f112) t->f104[i] = 1;
        else t->f104[i] = 0;
    }
    if (t->f156) {
        t->f156->c7(0);
        fn_80268020(lbl_8035B79C);
    }
    fn_8024C18C(t);
    t->f132 = 0;
    if (t->f112 == 0) {
        lbl_8035B65C->stop(0);
        fn_80253250(&lbl_8035B5E4->f112[lbl_8035B5E4->f104]);
        lbl_8035B308->f72->play(lbl_802A9314, 0, 0, 0, 0);
    }
}

} /* extern "C" */
