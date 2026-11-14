#include "common.h"
extern "C" {
}
struct V3 { f32 x, y, z; };
struct V2 { f32 u, v; };
struct VB { virtual void v0(); virtual int max(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void lock(void *, int, f32 **); virtual void unlock(int); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void draw(void *, u32, int, s32 *); };
struct Dev { u8 pad[6448];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
    virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
    virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65();
    virtual void v66(); virtual u32 get(); virtual u32 get2(); virtual void set(s32, u32); };
struct M156 { u8 pad[20]; u32 f20; };
struct R { u8 pad[28]; VB *vb; f32 *p; s32 ps; u8 pad2[16]; f32 *n; s32 ns; u8 pad3[16]; f32 *t; u8 pad4[28]; s32 ts;
    u8 pad5[28]; Dev *dev; u32 f148; u32 f152; M156 *f156; };
extern "C" {
extern s32 lbl_8035B3CC;
extern s8 lbl_8035B3D0;
extern f32 lbl_80366000;
extern f32 lbl_80366004;
void fn_801044C4(M156 *, u32, u32);
static inline void fill(R *r, V3 *pos, V2 *uv, u32 start, u32 len) {
            u32 k, end;
            V3 *pp;
            V2 *tp;
            r->vb->lock(r, len, &r->p);
            pp = &pos[start];
            tp = &uv[start];
            end = start + len;
            k = start;
            if (uv) {
                for (; k < end; k++) {
                    r->p[0] = pp->x; r->p[1] = pp->y; r->p[2] = pp->z; pp++;
                    r->p = (f32 *)((u8 *)r->p + r->ps);
                    r->n[0] = lbl_80366000; r->n[1] = lbl_80366004; r->n[2] = lbl_80366004;
                    r->n = (f32 *)((u8 *)r->n + r->ns);
                    r->t[0] = tp->u; r->t[1] = tp->v; tp++;
                    r->t = (f32 *)((u8 *)r->t + r->ts);
                }
            } else {
                for (; k < end; k++) {
                    r->p[0] = pp->x; r->p[1] = pp->y; r->p[2] = pp->z; pp++;
                    r->p = (f32 *)((u8 *)r->p + r->ps);
                    r->n[0] = lbl_80366000; r->n[1] = lbl_80366004; r->n[2] = lbl_80366004;
                    r->n = (f32 *)((u8 *)r->n + r->ns);
                    r->t[0] = lbl_80366004; r->t[1] = lbl_80366004;
                    r->t = (f32 *)((u8 *)r->t + r->ts);
                }
            }
}
#pragma opt_loop_invariants off
#pragma push
#pragma opt_common_subs off
void fn_8023AFDC(R *r, void *unused, V3 *pos, s32 count, V2 *uv) {
    s32 tmp;
    s32 n;
    u32 chunks, i, off, last, start, len;
    if (!lbl_8035B3D0) { lbl_8035B3CC = 0; lbl_8035B3D0 = 1; }
    tmp = lbl_8035B3CC;
    r->f148 = r->dev->get();
    if (r->f156) {
        fn_801044C4(r->f156, r->f148, r->dev->get2());
        r->dev->set(lbl_8035B3CC, r->f156->f20);
    } else {
        r->dev->set(lbl_8035B3CC, r->f148);
    }
    n = r->vb->max();
    if (count > n) n -= (u32)n % 3;
    chunks = (u32)count / (u32)n;
    off = 0;
    last = chunks * n;
    for (i = 0; i < chunks + 1; i++) {
        if (i == chunks) { start = last; len = count - last; }
        else { start = off; len = n; }
        if (len) {
            fill(r, pos, uv, start, len);
            r->vb->unlock(len);
            r->vb->draw(r->dev, r->f152, 1, &tmp);
        }
        off += n;
    }
}
#pragma pop
}
