// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void *memset(void *, s32, u32);
void fn_80060E30(s32, ...);
extern void *lbl_8035B590;
extern char lbl_80366488[4];
extern char lbl_8036648C[4];
extern u8 lbl_802F1F18[];
} /* extern "C" */

struct X44_8024F6D8 {
    u8 pad[292];
    virtual void v0();
    virtual void v1();
    virtual void v2(u8 *, s32, s32);
};
struct C80215F50 {
    u8 pad[44];
    X44_8024F6D8 *f44;
    u8 pad2[12];
    C80215F50();
    ~C80215F50();
};
struct C80272E68 {
    u8 pad[28];
    C80272E68();
};
struct O_8024F6D8 {
    u8 pad[1720];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual s32 v5(char *);
};
struct A_8024F6D8 {
    u8 pad[188];
    void *f188;
};
struct S_8024F6D8 {
    u8 pad[848];
    C80272E68 *f848;
};
struct D_8024F6D8 {
    u32 f0;
    u32 f4;
    u32 f8;
    u32 f12;
    u32 f16;
};
struct G65C_8024F6D8 {
    u8 pad[4];
    u32 f4;
    u8 pad2[20];
    u32 f28;
    u8 pad3[8];
    u32 f40;
};
struct G460b_8024F6D8 {
    u8 pad[12332];
    u32 f12332;
};
struct G460_8024F6D8 {
    u8 pad[12];
    G460b_8024F6D8 *f12;
};

extern "C" {
extern G65C_8024F6D8 *lbl_8035B65C;
extern G460_8024F6D8 *volatile lbl_8035B460;
O_8024F6D8 *fn_8021616C(void *);
s32 fn_80215C84(C80215F50 *, char *, char *, s32, s32);
void fn_80272CD4(C80272E68 *, D_8024F6D8 *);
void fn_8024F13C(S_8024F6D8 *, A_8024F6D8 *, void *, X44_8024F6D8 *, s32, s32);
void fn_80215BFC(C80215F50 *);

void fn_8024F6D8(S_8024F6D8 *self, A_8024F6D8 *a, void *b, char *c, s32 d, s32 e, s32 f) {
    volatile D_8024F6D8 dd;
    C80215F50 l;
    O_8024F6D8 *obj;
    s32 err;
    X44_8024F6D8 *x;

    obj = fn_8021616C(a->f188);
    if (f != 0) {
        if (lbl_8035B590 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035B590);
        self->f848 = new C80272E68;
        fn_800F7E98();
        if (self->f848 == 0) {
            fn_800604C4(-4, 0, 0, 0);
        }
        memset((void *)&dd, 0, sizeof(dd));
        dd.f16 = lbl_8035B65C->f40;
        dd.f4 = lbl_8035B65C->f4;
        dd.f8 = lbl_8035B65C->f28;
        dd.f12 = lbl_8035B460->f12->f12332;
        fn_80272CD4(self->f848, (D_8024F6D8 *)&dd);
    }
    if (obj->v5(c) == 0) {
        if (d != 0) {
            err = fn_80215C84(&l, c, lbl_80366488, 2, 0);
        } else {
            err = fn_80215C84(&l, c, lbl_8036648C, 2, 0);
        }
        if (err != 0) {
            fn_80060E30(err, c);
        }
        x = l.f44;
        x->v2(lbl_802F1F18, 5, 0);
        fn_8024F13C(self, a, b, x, e, f);
        fn_80215BFC(&l);
    }
}

} /* extern "C" */
