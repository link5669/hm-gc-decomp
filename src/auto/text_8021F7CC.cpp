// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct R { u8 pad_[292]; virtual void s0(); virtual void s1(); virtual void s2(void *, int, int); virtual void s3(); virtual void v4(int); virtual u32 v5(); };
struct B { virtual void *v0(); };
struct O24 { u8 pad[16]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); };
struct K { u32 a, b; u16 c, d; };
struct C80102660 { u8 d[76]; C80102660(); ~C80102660(); };
struct T {
    u8 pad[16];
    virtual void v0(); virtual void v1();
    B *f20;
    O24 *f24;
    K *k[5];
    u32 n[5];
    C80102660 *f68;
    u32 f72;
};
extern char lbl_802F0460[];
extern void *lbl_8035B260;
u32 fn_800FADA8(R *);
void fn_800FAEA0(R *);
u32 fn_800FB33C(R *);
void fn_800FB000(R *, int);
void fn_800FB064(R *, void *);
void fn_8021C124(O24 *, R *);
void fn_800F8E38(T *, u32);
void fn_800F87F0(T *, void *, C80102660 *);
void fn_801022FC(C80102660 *, T *, R *);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
#define ALLOC(H, dst, expr) \
    if (!H) fn_800604C4(-2, 0, 0, 0); \
    fn_800F7EC0(H); \
    dst = expr; \
    fn_800F7E98(); \
    if (!dst) fn_800604C4(-4, 0, 0, 0);
static inline void ldK(T *t, R *r, int X) {
    u32 i;
    if (t->k[X]) r->v4(39);
    t->n[X] = fn_800FADA8(r);
    ALLOC(lbl_8035B260, t->k[X], new K[t->n[X]])
    for (i = 0; i < t->n[X]; i++) {
        t->k[X][i].a = fn_800FB33C(r);
        t->k[X][i].b = fn_800FB33C(r);
        t->k[X][i].c = fn_800FB33C(r);
        if (t->k[X][i].c == 0) r->v4(35);
        t->k[X][i].d = fn_800FB33C(r);
    }
    fn_800FAEA0(r);
}
static inline void ldC(T *t, R *r, u8 *buf) {
    u32 i;
    for (i = 0; i < t->f72; i++) {
        fn_800FB000(r, 67);
        fn_800FB064(r, buf);
        fn_800F87F0(t, buf, &t->f68[i]);
        fn_801022FC(&t->f68[i], t, r);
    }
}
#define CASE(N, X) case N: ldK(t, r, X); break;
void fn_8021F7CC(T *t, B *b, R *r) {
    u8 buf[8];
    u32 i;
    u32 tok;
    if (t->f24) t->v1();
    r->s2(lbl_802F0460, 21, 0);
    t->f20 = b;
    t->f24 = (O24 *)b->v0();
    while ((tok = r->v5()) != 0) {
        switch (tok) {
        case 57:
            fn_8021C124(t->f24, r);
            break;
        CASE(63, 0)
        CASE(64, 1)
        CASE(65, 2)
        CASE(66, 3)
        CASE(77, 4)
        case 67:
            if (t->f68) r->v4(39);
            t->f72 = fn_800FADA8(r);
            ALLOC(lbl_8035B260, t->f68, new C80102660[t->f72])
            fn_800F8E38(t, t->f72);
            ldC(t, r, buf);
            fn_800FAEA0(r);
            break;
        default:
            r->v4(30);
            break;
        }
    }
    t->f24->v7();
}

} /* extern "C" */
