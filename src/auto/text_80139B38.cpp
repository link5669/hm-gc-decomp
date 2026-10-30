// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct Buf {
    u8 *p0; s32 s0; u8 *p1; s32 s1; u8 *p2; s32 s2; u8 *p3; s32 s3;
    u8 *p4; s32 s4; u8 *p5; s32 s5;
    u8 *tp[8]; s32 ts[8];
};
struct Loc { u8 hdr[20]; };
struct Out { u32 a; u32 b; u8 pad[44]; u32 n; u32 c0; u32 c1; f32 t[8][4]; };
struct Obj {
    u8 pad_[12];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void v22(Buf *, int); virtual void v23(Loc *);
    u32 fl; u32 f14; u32 f18; u32 n;
};
extern "C" {
extern f32 lbl_803641D0;
extern f32 lbl_803641D4;
void fn_80148310(Loc *);
void fn_801399F4(Obj *, s32, Out *, Buf *);
void fn_80147AD8(Loc *, u32, u32 *);
void fn_80139B38(Obj *o, s32 idx, Out *out) {
    Loc l; Buf bf;
    u32 i;
    fn_80148310(&l);
    out->a = o->fl;
    out->b = o->f14;
    out->n = o->n;
    o->v22(&bf, 4);
    fn_801399F4(o, idx, out, &bf);
    o->v23(&l);
    if (o->fl & 0x2000) fn_80147AD8(&l, *(u32 *)(bf.p4 + idx * bf.s4), &out->c0);
    if (o->fl & 0x4000) fn_80147AD8(&l, *(u32 *)(bf.p5 + idx * bf.s5), &out->c1);
    if (o->fl & 0x8000) {
        for (i = 0; i < o->n; i++) {
            if (o->fl & (0x1000000 << i)) {
                f32 *s = (f32 *)(bf.tp[i] + idx * bf.ts[i]);
                out->t[i][0] = s[0]; out->t[i][1] = s[1]; out->t[i][2] = s[2]; out->t[i][3] = s[3];
            } else if (o->fl & (0x10000 << i)) {
                f32 *s = (f32 *)(bf.tp[i] + idx * bf.ts[i]);
                out->t[i][0] = s[0]; out->t[i][1] = s[1]; out->t[i][2] = s[2]; out->t[i][3] = lbl_803641D4;
            } else {
                f32 *s = (f32 *)(bf.tp[i] + idx * bf.ts[i]);
                out->t[i][0] = s[0]; out->t[i][1] = s[1]; out->t[i][2] = lbl_803641D0; out->t[i][3] = lbl_803641D4;
            }
        }
    }
    o->v6();
}

} /* extern "C" */
