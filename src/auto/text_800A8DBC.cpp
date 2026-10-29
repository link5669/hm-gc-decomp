// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V800A8DBC {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
};
extern "C" {
typedef struct F800A8DBC { u8 pad[192]; s32 f192; s32 f196; u8 pad2[224 - 200]; f32 f224; } F800A8DBC;
typedef struct T800A8DBC {
    u8 pad0[224];
    V800A8DBC *f224;
    u8 pad1[480 - 228];
    F800A8DBC *f480;
    u8 pad3[8];
    void *f492;
    s32 f496;
} T800A8DBC;
extern f32 lbl_803620C8;
extern f32 lbl_803620CC;
extern f32 lbl_803620D0;
void fn_800A8EB0(T800A8DBC *self);
void fn_80241628(T800A8DBC *self, s32 a, s32 b);
void fn_8022BBF4(V800A8DBC *o);
void fn_8022AD0C(V800A8DBC *o);
int rand(void);
f32 fn_80072388(void *o);

#pragma fp_contract off
void fn_800A8DBC(T800A8DBC *self) {
    f32 r;
    s32 n;
    f32 t;
    if (self->f496 != 0) fn_800A8EB0(self);
    fn_80241628(self, 1, 0);
    self->f224->v19();
    fn_8022BBF4(self->f224);
    fn_8022AD0C(self->f224);
    n = (u32)rand() % 10000;
    r = lbl_803620C8 * (f32)n;
    t = lbl_803620CC + fn_80072388(self->f492);
    self->f480->f224 = t + lbl_803620D0 * r;
    self->f480->f196 = 0;
    self->f480->f192 = 0;
}
#pragma fp_contract reset

} /* extern "C" */
