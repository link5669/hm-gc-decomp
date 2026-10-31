// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct Rc { f32 x0, y0, x1, y1; };
struct S;
struct Ob { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
    virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46();
    virtual int draw(S *, void *, void *, void *, Rc *, f32); };
struct Nd { Ob *o; u8 pad[4]; Nd *next; };
struct Q { u8 pad[72]; Rc r; };
struct W { u8 pad[28]; u32 f28; s32 g32; u8 pad2[244]; f32 f280; };
struct P52 { u8 pad[52]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void f(void *, void *, void *, u32, u32, u32, Rc *, int, int, int, f32); };
struct P128 { u8 pad[128]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void f(void *, void *, void *, Rc *, f32); };
struct S { u8 pad[4]; u32 kind[4]; Q *q[4]; f32 m[4]; u8 pad2[20]; u8 f72[32]; u32 f104; u32 f108; P52 *f112; W *f116;
    u8 pad3[8];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void upd();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual u32 type();
    u8 padv[4]; Nd *f136; u8 pad4[168]; P128 *f308; P128 *f312; u8 pad5[8]; u32 f324; u32 f328; u8 pad6[52]; f32 f384; f32 f388; u8 pad7[4]; f32 f396; };
extern "C" {
extern f32 lbl_803596E0[];
extern volatile s8 lbl_8035B048;
extern volatile f32 lbl_8035B044;
extern f32 lbl_80365260;
extern f32 lbl_80365258;
void fn_8010069C(Rc *, Rc *);
void fn_801DC730(S *s, void *a, void *b, void *c, Rc *rect, f32 dt) {
    int stop;
    Nd *n;
    n = s->f136;
    stop = 0;
    Rc *cr;
    volatile Rc r;
    S *p;
    u32 i;
    for (; n; n = n->next) {
        if (!n->o->draw(s, a, b, c, rect, dt)) stop = 1;
    }
    if (stop) return;
    cr = rect;
    {
        f32 nk, k;
        k = lbl_803596E0[0];
        nk = -k;
        r.x1 = k; r.y1 = k; r.x0 = nk; r.y0 = nk;
    }
    if (!lbl_8035B048) { lbl_8035B044 = lbl_80365260; lbl_8035B048 = 1; }
    if (rect) fn_8010069C((Rc *)&r, rect);
    for (i = 0, p = s; i < 4; i++, p = (S *)((u8 *)p + 4)) {
        if ((s32)p->kind[0] == 0x8000) {
            Rc t;
            f32 m;
            t = p->q[0]->r;
            t.y0 = t.y0 + p->m[0];
            t.x0 = t.x0 + p->m[0];
            t.y1 = t.y1 - p->m[0];
            t.x1 = t.x1 - p->m[0];
            fn_8010069C((Rc *)&r, &t);
            cr = (Rc *)&r;
        }
    }
    if (s->type() == 95) {
        if (s->f116->f28 == 1) {
            f32 a0 = s->f396, a1 = s->f388;
            f64 d0 = __fabs(a0), d1 = __fabs(a1);
            f32 b0 = d0, b1 = d1;
            s->f396 = -b0;
            s->f388 = -b1;
            s->upd();
        }
        if (s->f116->f28 == 2) {
            f32 a0 = s->f396, a1 = s->f388;
            f64 d0 = __fabs(a0), d1 = __fabs(a1);
            f32 b0 = d0, b1 = d1;
            s->f396 = b0;
            s->f388 = b1;
            s->upd();
        }
        if (s->f116->g32 == 1) {
            f32 y = s->f388;
            lbl_8035B044 = s->f116->f280 * lbl_80365258;
            s->f384 = -(f32)__fabs(lbl_8035B044);
            s->f388 = y;
            s->upd();
        }
        if (s->f116->g32 == 2) {
            s->f384 = lbl_80365260;
            s->upd();
        }
    }
    if (s->f108 & 1) {
        if (s->f112) s->f112->f(a, s->f72, c, s->f328, s->f324, s->f104, cr, 0, 0, 0, dt);
        if (s->f312) s->f312->f(a, b, c, cr, dt);
    }
    if (s->f308) s->f308->f(a, b, c, rect, dt);
}

} /* extern "C" */
