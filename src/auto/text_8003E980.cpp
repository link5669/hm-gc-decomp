// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct E20 { u8 pad[16]; virtual void v0(); virtual void v1(); };
struct O672 { u8 pad[36]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); };
struct Mgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(O672 *);
};
extern "C" {
typedef struct {
    u8 pad0[28]; u8 b28; u8 pad29[29]; u8 b58; u8 pad59[29]; u8 b88; u8 pad89[29]; u8 b118; u8 pad119[29];
    u8 b148; u8 pad149[29]; u8 b178; u8 pad179[485];
    s32 f664; s32 f668; O672 *f672; s32 f676; s32 f680; s32 f684; s32 f688; s32 f692; s32 f696; s32 f700;
    u8 pad704[32]; s32 f736;
    E20 arr[31];
    void *bufs[31];
    s32 x[31];
    void *vt;
} S8003E980;
extern u8 *lbl_8035A1DC;
extern u8 lbl_802B0470[40];
void __dla__FPv(void *);
void __dl__FPv(void *);
void __dt__9C800F92E8Fv(void);
void fn_800E1F04(void *, void *, u32, u32);

static inline void rel(S8003E980 *self) {
    u32 i;
    for (i = 0; i < 31; i++) {
        self->arr[i].v1();
        __dla__FPv(self->bufs[i]);
    }
}
static inline void clr(S8003E980 *self) {
    u32 i;
    self->f664 = 0; self->f668 = 0; self->f672 = 0; self->f676 = 0; self->f680 = 0; self->f684 = 0;
    self->f688 = 1; self->f692 = 0; self->f696 = 1; self->f700 = 0; self->f736 = 0;
    for (i = 0; i < 31; i++) {
        self->x[i] = 0;
        self->bufs[i] = 0;
    }
    self->b28 = 0; self->b58 = 0; self->b88 = 0; self->b118 = 0; self->b148 = 0; self->b178 = 0;
}
void *fn_8003E980(S8003E980 *self, s16 flag) {
    if (self != 0) {
        self->vt = lbl_802B0470;
        if (self->f672 != 0) {
            self->f672->v3();
            (*(Mgr **)(lbl_8035A1DC + 11332))->v26(self->f672);
        }
        rel(self);
        clr(self);
        fn_800E1F04(self->arr, (void *)__dt__9C800F92E8Fv, 20, 31);
        if (flag > 0) __dl__FPv(self);
    }
    return self;
}

} /* extern "C" */
