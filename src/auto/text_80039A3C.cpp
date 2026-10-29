// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 **lbl_8035B418;
extern u8 *lbl_8035A1DC;
extern u32 lbl_8035A018;
extern char lbl_80294D84[];
extern char lbl_8035C078[8];
u32 fn_8023C824(u8 **, u8 *);
void fn_800E8F6C(char *, const char *, ...);
void fn_80207BF4(void *, char *);
void fn_800604C4(int, int, int, int);
void fn_800F7EC0(u32);
void fn_800F7E98(void);
void fn_80215534(void *, u8 *, char *, int);
void fn_8019E610(void *, u8 *, char *, int);
void fn_802079F0(void *, int);
void fn_80129938(void *, void *);
} /* extern "C" */
struct C80215B8C { u8 pad[52]; C80215B8C(); };
struct C8019E778 { u8 pad[28]; C8019E778(); };
struct V_80039A3C { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23(); virtual void v24(); virtual void *m(); };
struct Ctx_80039A3C { u8 pad[11332]; V_80039A3C *f11332; u32 pad2; void *f11340; u32 f11344; };
struct Self_80039A3C { void *f0; C8019E778 *f4; C80215B8C *f8; u32 f12; void *f16; };
extern "C" {

void fn_80039A3C(Self_80039A3C *self, Ctx_80039A3C *ctx, void *a) {
    char buf[72];
    u8 *res;
    self->f0 = a;
    { u32 id = fn_8023C824(lbl_8035B418, *lbl_8035B418); fn_800E8F6C(buf, lbl_80294D84, id); }
    fn_80207BF4(self->f0, buf);
    res = lbl_8035A1DC + 852;
    if (lbl_8035A018 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035A018);
    self->f8 = new C80215B8C;
    fn_800F7E98();
    if (self->f8 == 0) fn_800604C4(-4, 0, 0, 0);
    fn_80215534(self->f8, res, lbl_8035C078, 1);
    if (lbl_8035A018 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035A018);
    self->f4 = new C8019E778;
    fn_800F7E98();
    if (self->f4 == 0) fn_800604C4(-4, 0, 0, 0);
    fn_8019E610(self->f4, lbl_8035A1DC + 12352, lbl_8035C078, 1);
    fn_802079F0(self->f0, 0);
    self->f16 = ctx->f11332->m();
    fn_80129938(self->f16, ctx->f11340);
    self->f12 = ctx->f11344;
}

} /* extern "C" */
