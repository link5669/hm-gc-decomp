// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct C80105EE8 {
    C80105EE8();
    u8 pad0[44];
    void *f44;
    u8 pad48[8];
};
struct Inner {
    u8 pad[48];
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
    virtual void *v15();
};
struct Holder44 { u8 pad[4]; Inner *f4; };
struct Sub {
    u8 pad[36];
    virtual void w0();
    virtual void w1();
    virtual void w2();
    virtual void w3();
    virtual void w4(void *x);
};
struct Elem { u8 pad[60]; };
struct Self {
    volatile u32 f0;
    u8 pad4[40];
    Holder44 *f44;
    u8 pad48[56];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual Sub *s4();
    u8 pad108[60];
    void *f168;
    u32 f172;
    Elem *f176;
};
struct ArrSt { void *p; u32 n; };
extern "C" {
extern void fn_8018DFAC(Self *self, void *a, Self *src, Self *other);
extern void fn_80190E48(Self *self);
extern void fn_801A0B20(Self *self);
extern void fn_80190348(Self *other, Self *self);
extern void fn_800604C4(s32 code, s32 a, s32 b, s32 c);
extern void fn_800F7EC0(void *heap);
extern void fn_800F7E98(void);
extern void fn_80105350(C80105EE8 *p, void *x, void *y);
extern void fn_8017A984(void *dst, ArrSt *st);
extern void fn_8017AFC0(Elem *dst, Elem *src);
extern volatile u32 lbl_803649EC;
extern u32 lbl_803649E8;
extern void *lbl_8035AEA8;

void fn_80188144(Self *self, void *a, Self *src, Self *other) {
    ArrSt st;
    void *x;
    u32 i;
    fn_8018DFAC(self, a, src, other);
    { u32 m = src->f0; self->f0 |= m & 0x80000; }
    x = src->f168;
    if (x != 0) {
        if (other != 0) {
            st.p = other->f168;
            self->f0 |= lbl_803649EC;
            fn_80190E48(self);
            fn_801A0B20(self);
            fn_80190348(other, self);
        } else {
            C80105EE8 *p;
            self->f0 |= lbl_803649E8;
            if (lbl_8035AEA8 == 0) fn_800604C4(-2, 0, 0, 0);
            fn_800F7EC0(lbl_8035AEA8);
            p = new C80105EE8;
            fn_800F7E98();
            if (p == 0) fn_800604C4(-4, 0, 0, 0);
            fn_80105350(p, self->f44->f4->v15(), x);
            if (p->f44 != 0 && self->s4() != 0) self->s4()->w4(p->f44);
            st.p = p;
        }
    } else {
        st.p = 0;
    }
    st.n = src->f172;
    fn_8017A984(&self->f168, &st);
    for (i = 0; i < st.n; i++) fn_8017AFC0(&self->f176[i], &src->f176[i]);
}

} /* extern "C" */
