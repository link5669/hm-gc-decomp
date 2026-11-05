// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void *memset(void *, s32, u32);
} /* extern "C" */
struct C80272E68 {
    u8 pad[28];
    C80272E68();
};
struct Obj_8003AD38 {
    u8 pad[36];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};
struct Mgr_8003AD38 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual Obj_8003AD38 *v25();
    virtual void v26(Obj_8003AD38 *);
};
struct G_8003AD38 {
    u8 pad[11316];
    u8 f11316[16];
    Mgr_8003AD38 *f11332;
    u8 pad2[4];
    u32 f11340;
    u32 f11344;
    u8 pad3[984];
    u32 f12332;
};
struct D_8003AD38 {
    u32 f0;
    void *f4;
    u32 f8;
    u32 f12;
    Obj_8003AD38 *f16;
};
extern "C" {
extern C80272E68 *lbl_8035B818;
extern void *lbl_8035A060;
extern G_8003AD38 *lbl_8035A1DC;
extern u8 *lbl_8035B5E4;
extern const char lbl_8035C130[5];
void fn_80129938(Obj_8003AD38 *, u32);
void fn_80272CD4(C80272E68 *, D_8003AD38 *);
void fn_80251428(u8 *, const char *);
void fn_80251488(u8 *, const char *);
void fn_80272538(C80272E68 *, u32, u32, s32);
void fn_80272D7C(C80272E68 *);
void fn_80272DDC(C80272E68 *, s32);

static inline u8 *getlock(void) { return lbl_8035B5E4; }
#pragma scheduling 604
void fn_8003AD38(void *self, u32 a, u32 b, u32 c, u32 d) {
    u8 *lock;
    s32 created;
    C80272E68 *p;
    Obj_8003AD38 *obj;
    volatile D_8003AD38 dd;
    G_8003AD38 *g;

    created = 1;
    obj = 0;
    if (lbl_8035B818 == 0) {
        if (lbl_8035A060 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035A060);
        p = new C80272E68;
        fn_800F7E98();
        if (p == 0) {
            fn_800604C4(-4, 0, 0, 0);
        }
        memset((void *)&dd, 0, sizeof(dd));
        obj = lbl_8035A1DC->f11332->v25();
        fn_80129938(obj, lbl_8035A1DC->f11340);
        dd.f16 = obj;
        g = *(G_8003AD38 *volatile *)&lbl_8035A1DC;
        dd.f4 = g->f11316;
        dd.f8 = g->f11344;
        dd.f12 = g->f12332;
        fn_80272CD4(p, (D_8003AD38 *)&dd);
    } else {
        p = lbl_8035B818;
        created = 0;
    }
    lock = getlock();
    fn_80251428(lock, lbl_8035C130);
    fn_80272538(p, a, b, 0);
    if (c != 0) {
        fn_80272538(p, c, d, 0);
    }
    fn_80251488(lock, lbl_8035C130);
    if (created == 1) {
        fn_80272D7C(p);
        fn_80272DDC(p, 1);
        if (obj != 0) {
            obj->v3();
            lbl_8035A1DC->f11332->v26(obj);
        }
    }
}
#pragma scheduling reset

} /* extern "C" */
