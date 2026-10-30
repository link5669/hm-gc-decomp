// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u8 __vt__9C80129A9C[];
void __ct__9C80105074Fv(void *);
void fn_800604C4(int, int, int, int);
void fn_800F7E98(void);
void fn_800F7EC0(void *);
}
struct C80105818 {
    u8 pad[36];
    u8 *vt;
    C80105818() { __ct__9C80105074Fv(this); vt = __vt__9C80129A9C; }
};
struct C80106E10 { u8 pad[48]; C80106E10(); };
struct R { virtual void *g(); };
struct Q { u8 pad[48]; virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3(); virtual void q4(); virtual void q5(); virtual void q6(); virtual void q7(); virtual void q8(); virtual void q9(); virtual void q10(); virtual void q11(); virtual void q12(); virtual void q13(); virtual void q14(); virtual R *get(); };
struct O { u32 f0; Q *q; };
struct S { u32 f0; u16 f4; u16 pad6; f32 v[8]; f32 f40; O *o; C80105818 *a; C80106E10 *b; u32 f56; u32 f60; u8 pad64[104 - 64];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void reset();
    u8 pad108[136 - 108]; u32 f136; };
extern "C" {
extern void *lbl_8035AE60;
void fn_80190C98(S *s);
void fn_80104F78(void *, void *, void *);
void fn_80103CA0(void *, void *);
void fn_80106DAC(void *, void *);

static inline int canCopy(S *src) {
    int r = 1;
    if (src->f4 >= 1 && src->f4 <= 13 && src->f136) r = 0;
    return r;
}

void fn_80191F88(S *s, O *o, S *src) {
    R *r;
    if (s->f0 & 1) s->reset();
    s->f0 = 1;
    s->f0 |= src->f0 & 0x202;
    s->v[0] = src->v[0]; s->v[1] = src->v[1]; s->v[2] = src->v[2]; s->v[3] = src->v[3];
    s->v[4] = src->v[4]; s->v[5] = src->v[5]; s->v[6] = src->v[6]; s->v[7] = src->v[7];
    fn_80190C98(s);
    s->f40 = src->f40;
    s->o = o;
    r = s->o->q->get();
    s->f56 = src->f56;
    if (src->a && canCopy(src)) {
        if (!lbl_8035AE60) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035AE60);
        s->a = new C80105818;
        fn_800F7E98();
        if (!s->a) fn_800604C4(-4, 0, 0, 0);
        fn_80104F78(s->a, r->g(), r->g());
        fn_80103CA0(s->a, src->a);
        s->f0 |= 8;
    }
    if (src->b) {
        if (!lbl_8035AE60) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035AE60);
        s->b = new C80106E10;
        fn_800F7E98();
        if (!s->b) fn_800604C4(-4, 0, 0, 0);
        fn_80106DAC(s->b, src->b);
        s->f0 |= 16;
    }
    s->f60 = src->f60;
}

} /* extern "C" */
