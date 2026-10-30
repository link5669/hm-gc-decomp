// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct C800FBA24 { C800FBA24(); u32 f0; u8 pad[8];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); u32 f16; };
struct O404 { u8 pad[128];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(int); };
struct Q { u8 pad[8]; s32 type; u8 pad2[8]; s32 a; s32 b; };
struct QF { u8 pad[20]; f32 x; f32 y; };
struct P40 { Q *q; u8 pad[8]; u8 s12[20]; u8 t32[20]; s32 f52; };
struct D { u8 pad[36]; u32 f36; P40 *p; u8 pad2[16]; u8 s60[136]; f32 f196; };
struct S { u8 pad[104]; u32 f104; u8 pad1[4]; void *f112; u8 pad2[260]; u32 f376; u32 f380; u8 pad3[8];
    D *f392; C800FBA24 *f396; u8 pad4[4]; O404 *f404; s32 f408; };
extern "C" {
extern f32 lbl_803596E0[];
extern void *lbl_8035AFCC;
extern char lbl_80364EF0[4];
extern char lbl_80364EF4[4];
extern char lbl_802A28A0[];
void fn_801DB744(S *);
int fn_801CCA8C(void *, u32 *, D **, u32);
void __dl__FPv(void *);
void fn_800FB9AC(C800FBA24 *);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
int abs(int);
void fn_800E8F6C(char *, const char *, ...);
unsigned long strlen(const char *);
void fn_800FB9D4(C800FBA24 *, u8 *, int);
void fn_801AD760(D *);
void fn_801B1D54(S *, int);
void fn_80060568(char *, int, int, int);
int fn_801B2504(S *s) {
    int had = 0;
    char buf[256];
    fn_801DB744(s);
    s->f376 = 0;
    if (s->f404) s->f404->v20(0);
    if (s->f396 && (s->f408 == 2 || s->f408 == 3)) had = 1;
    if (s->f112 == 0) return 0;
    if (fn_801CCA8C(s->f112, &s->f376, &s->f392, s->f104)) {
    s->f392->f196 = lbl_803596E0[0];
    s->f408 = s->f392->p->q->type;
    if (s->f408 == 5) {
        if (had) __dl__FPv(s->f396);
        P40 *p = s->f392->p;
        s->f396 = (C800FBA24 *)(p->f52 ? p->t32 : p->s12);
    } else if (s->f408 == 2 || s->f408 == 3) {
        s->f392->f36 = 0;
        if (had) fn_800FB9AC(s->f396);
        else {
            if (lbl_8035AFCC == 0) fn_800604C4(-2, 0, 0, 0);
            fn_800F7EC0(lbl_8035AFCC);
            s->f396 = new C800FBA24;
            fn_800F7E98();
            if (s->f396 == 0) fn_800604C4(-4, 0, 0, 0);
        }
        if (s->f408 == 2) {
            Q *q = s->f392->p->q;
            s32 b;
            s32 a;
            a = q->a;
            b = q->b;
            fn_800E8F6C(buf, lbl_80364EF0, abs(b) > abs(a) ? b : a);
            strlen(buf);
        } else {
            QF *q = (QF *)s->f392->p->q;
            f32 y = q->y; f32 x = q->x;
            fn_800E8F6C(buf, lbl_80364EF4, (f32)__fabs(y) > (f32)__fabs(x) ? (u32)y : (u32)x);
            strlen(buf);
        }
        fn_800FB9D4(s->f396, s->f392->s60, 128);
        fn_801AD760(s->f392);
        fn_801B1D54(s, 0);
        s->f396->v5();
    } else {
        fn_80060568(lbl_802A28A0, 0, 0, 0);
    }
    } else {
        return 0;
    }
    s->f380 = s->f396->f0;
    if (s->f408 == 3) s->f380 -= 7;
    return 0;
}

} /* extern "C" */
