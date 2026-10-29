// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Loc { u8 d[24]; };
struct Gfx {
    u8 pad[6448];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(Loc *);
};
struct Node {
    u8 pad0[8];
    Node *f8;
    u8 pad12[68];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(Gfx *);
};
struct Ctx {
    u8 pad0[8];
    Gfx *f8;
};
struct O64 {
    u8 pad[8];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(u8 *, Ctx *);
};
struct SelfC {
    u8 pad0[64];
    O64 *f64;
    Node *f68;
    Node *f72;
};
extern "C" {
void fn_8014CBD8(Loc *);
void fn_8014CBA4(Loc *, u8 *);
void fn_8017F4BC(Ctx *);
void fn_8019A7D0(SelfC *, s32, s32);
void fn_8017F1E4(Ctx *);
void fn_8017F2B8(Ctx *);
void fn_8017F378(Ctx *);
void fn_8017F544(Ctx *);

void fn_8019AA94(SelfC *self, Ctx *ctx) {
    Loc m;
    Node *p;
    fn_8014CBD8(&m);
    fn_8017F4BC(ctx);
    fn_8019A7D0(self, 0, 1);
    fn_8019A7D0(self, 2, 0);
    if (self->f68) {
        fn_8014CBA4(&m, (u8 *)ctx->f8 + 32);
        ctx->f8->v40(0);
        for (p = self->f68; p; p = p->f8) {
            p->v4(ctx->f8);
        }
        ctx->f8->v40(&m);
    }
    self->f64->v6((u8 *)ctx->f8 + 56, ctx);
    fn_8017F1E4(ctx);
    ctx->f8->v30();
    fn_8017F2B8(ctx);
    fn_8017F378(ctx);
    if (self->f72) {
        fn_8014CBA4(&m, (u8 *)ctx->f8 + 32);
        ctx->f8->v40(0);
        for (p = self->f72; p; p = p->f8) {
            p->v4(ctx->f8);
        }
        ctx->f8->v40(&m);
    }
    fn_8017F544(ctx);
}

} /* extern "C" */
