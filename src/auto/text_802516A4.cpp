// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern s8 lbl_8035B5EC;
extern u32 lbl_8035B5E8;
u32 fn_800FBB9C(void);
void fn_802536B8(void *p, void *arg);
void fn_80252DB0(void *p);
} /* extern "C" */
struct S802516A4_R { u8 pad[192]; s32 f192; };
struct S802516A4_A {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void *v14(void *a);
    virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22();
    virtual S802516A4_R **v23(u32 a);
};
struct S802516A4_C;
struct S802516A4_E { u8 b[52]; };
struct S802516A4 {
    u8 pad0[24];
    S802516A4_A *f24;
    u8 pad1c[48 - 28];
    void **f48;
    u32 f52;
    u8 pad38[104 - 56];
    u32 f104;
    u8 pad6c[112 - 108];
    S802516A4_E *f112;
    u32 f116;
    u32 f120;
    s32 f124;
    void (S802516A4_C::*f128)();
    S802516A4_C *f140;
};
extern "C" {
void *fn_802516A4(S802516A4 *self, void *arg) {
    void *r;
    u32 i;
    u32 j;
    if (!lbl_8035B5EC) { lbl_8035B5E8 = 0; lbl_8035B5EC = 1; }
    if (fn_800FBB9C() - lbl_8035B5E8 < 17) return 0;
    lbl_8035B5E8 = fn_800FBB9C();
    if (self->f124 != 0) {
        if ((*self->f24->v23(self->f104))->f192 != 0 && self->f140 != 0) {
            self->f24->v15();
            (self->f140->*self->f128)();
            self->f124 = 0;
        }
    }
    r = self->f24->v14(arg);
    if (self->f48 != 0) {
        for (i = 0; i < self->f52; i++) {
            if (self->f48[i] != 0) fn_802536B8(self->f48[i], arg);
        }
    }
    for (j = 0; j < self->f116; j++) {
        fn_80252DB0(&self->f112[j]);
    }
    return r;
}

} /* extern "C" */
