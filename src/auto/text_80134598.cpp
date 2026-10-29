// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern char lbl_803640D0[4];
extern char lbl_803640D4[6];
extern u8 lbl_802E5080[];
} /* extern "C" */
struct R_80134598 {
    u8 pad[292];
    virtual void v0(); virtual void v1(); virtual void v2(void *, s32, s32);
};
struct X_80134598 { u8 pad[12]; char *f12; };
struct C80215F50 {
    u8 pad[36];
    char *f36;
    X_80134598 *f40;
    R_80134598 *f44;
    u8 pad48[8];
    C80215F50();
    ~C80215F50();
};
struct A_80134598;
struct E_80134598 {
    u8 pad[12];
    virtual void v0(A_80134598 *); virtual void v1(); virtual void v2(A_80134598 *, R_80134598 *);
};
struct Self_80134598 {
    u8 pad[16];
    virtual void v0(); virtual void v1(); virtual void v2(A_80134598 *); virtual E_80134598 *v3(u32);
    u32 f20;
};
extern "C" {
s32 fn_80215C84(C80215F50 *, char *, char *, s32, s32);
void fn_80215BFC(C80215F50 *);
void fn_80060E30(...);
void fn_80207A54(char *, char *);
void fn_802079F0(char *, s32);
void fn_800FB000(R_80134598 *, s32);
void fn_800FB064(R_80134598 *, char *);
u32 fn_800FADA8(R_80134598 *);
void fn_800FAEA0(R_80134598 *);
void fn_800F8E38(Self_80134598 *, u32);
void fn_800F87F0(Self_80134598 *, char *, E_80134598 *);
void fn_80135CB8(A_80134598 *, Self_80134598 *);

static inline void one_80134598(Self_80134598 *self, A_80134598 *a, R_80134598 *r, char *buf, E_80134598 *e) {
    fn_800F87F0(self, buf, e);
    e->v2(a, r);
}

void fn_80134598(Self_80134598 *self, A_80134598 *a, char *name) {
    char buf[8];
    C80215F50 obj;
    E_80134598 *e;
    u32 i;
    R_80134598 *r;
    s32 err;
    u32 j;

    err = fn_80215C84(&obj, name, lbl_803640D0, 2, 0);
    if (err != 0) {
        fn_80060E30(err, lbl_803640D4, name, lbl_803640D0);
    }
    fn_80207A54(obj.f36, obj.f40->f12);
    r = obj.f44;
    if (self->f20 != 0) self->v1();
    r->v2(lbl_802E5080, 19, 0);
    fn_800FB000(r, 57);
    self->f20 = fn_800FADA8(r);
    fn_800F8E38(self, self->f20);
    fn_80135CB8(a, self);
    self->v2(a);
    for (i = 0; i < self->f20; i++) {
        fn_800FB000(r, 57);
        fn_800FB064(r, buf);
        one_80134598(self, a, r, buf, self->v3(i));
    }
    fn_800FAEA0(r);
    for (j = 0; j < self->f20; j++) {
        self->v3(j)->v0(a);
    }
    fn_802079F0(obj.f36, 0);
    fn_80215BFC(&obj);
}

} /* extern "C" */
