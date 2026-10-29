// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern char lbl_803656B8[4];
extern char lbl_803656BC[6];
extern u32 lbl_8035A9F4;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7E98(void);
void fn_800F7EC0(u32);
void fn_80060E30(...);
int fn_800E8F6C(char *, const char *, ...);
s32 fn_80215C84(void *, char *, char *, s32, s32);
void fn_80215BFC(void *);
void fn_80207A54(char *, char *);
u32 fn_80207DAC(char *, char *, u32);
void fn_802079F0(char *, s32);
unsigned long strlen(const char *);

} /* extern "C" */
struct X_801FD748 { u8 pad[12]; char *f12; };
struct C80215F50 {
    u8 pad[36];
    char *f36;
    X_801FD748 *f40;
    u32 f44;
    u8 pad48[8];
    C80215F50();
    ~C80215F50();
};
struct A_801FD748 { u8 pad[8]; u32 f8; };
struct SelfB_801FD748;
struct E_801FD748 {
    u8 pad[12];
    virtual void v0(); virtual void v1(); virtual void v2(SelfB_801FD748 *);
};
struct SelfB_801FD748 {
    u8 pad[16];
    virtual void v0(); virtual void v1(); virtual void v2(u32, char *); virtual void v3();
    virtual void v4(A_801FD748 *, u32); virtual E_801FD748 *v5(u32);
};
struct Self_801FD748 : SelfB_801FD748 {
    u32 f20;
};
extern "C" {

void fn_801FD748(Self_801FD748 *self, A_801FD748 *a, char *name) {
    C80215F50 obj;
    char buf[128];
    char *s;
    char *t;
    s32 err;
    char *mem;
    u32 len;
    u32 i;

    err = fn_80215C84(&obj, name, lbl_803656B8, 2, 0);
    if (err != 0) {
        fn_800E8F6C(buf, lbl_803656BC, name, lbl_803656B8);
        fn_80060E30(err, buf);
    }
    s = obj.f36;
    fn_80207A54(s, obj.f40->f12);
    t = obj.f40->f12;
    len = strlen(t) + strlen(s) + 4;
    if (lbl_8035A9F4 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035A9F4);
    mem = new char[len];
    fn_800F7E98();
    if (mem == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    fn_80207DAC(s, mem, len);
    self->v4(a, obj.f44);
    self->v2(a->f8, mem);
    for (i = 0; i < self->f20; i++) {
        self->v5(i)->v2(self);
    }
    fn_802079F0(obj.f36, 0);
    fn_80215BFC(&obj);
    delete[] mem;
}

} /* extern "C" */
