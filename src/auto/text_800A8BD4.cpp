// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
typedef struct Vec800A8BD4 { f32 x, y, z; } Vec800A8BD4;
struct V800A8BD4 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13(Vec800A8BD4 *a, Vec800A8BD4 *b, Vec800A8BD4 *c, Vec800A8BD4 *d, s32 e);
    virtual void v14(Vec800A8BD4 *a, Vec800A8BD4 *b, Vec800A8BD4 *c, Vec800A8BD4 *d, s32 e);
};
extern "C" {
typedef struct F800A8BD4 { u8 pad[224]; f32 f224; } F800A8BD4;
typedef struct T800A8BD4 {
    u8 pad0[224];
    V800A8BD4 *f224;
    u8 pad1[280 - 228];
    void *f280;
    u8 pad2[360 - 284];
    u8 f360[16];
    u8 f376[16];
    u8 f392[44];
    u8 f436[44];
    F800A8BD4 *f480;
    u8 pad3[8];
    void *f492;
    s32 f496;
} T800A8BD4;
extern char lbl_803620B8[7];
extern char lbl_8036206C[8];
extern f32 lbl_803620C0;
extern f32 lbl_803620C4;
void fn_800A8EB0(T800A8BD4 *self);
void fn_8023FE08(T800A8BD4 *self, f32 dt);
f32 fn_8023C1BC(void *o, f32 dt);
f32 fn_8023D494(void *o, f32 dt, f32 v);
s32 fn_800F6CD0(void *s, char *t);
f32 fn_80072388(void *o);
void fn_80241DD0(T800A8BD4 *self, char *name, s32 a, s32 b, s32 c, s32 d);

void fn_800A8BD4(T800A8BD4 *self, f32 dt) {
    Vec800A8BD4 d;
    Vec800A8BD4 c;
    Vec800A8BD4 b;
    Vec800A8BD4 a;
    f32 t[2];
    f32 s0;
    f32 s1;
    f32 lim;
    if (self->f496 != 0) fn_800A8EB0(self);
    fn_8023FE08(self, dt);
    self->f224->v13(&a, &b, &c, &d, 0);
    t[0] = fn_8023C1BC(self->f360, dt);
    t[1] = fn_8023C1BC(self->f376, dt);
    s0 = fn_8023D494(self->f392, dt, t[0]);
    s1 = fn_8023D494(self->f436, dt, t[1]);
    if (fn_800F6CD0(self->f280, lbl_803620B8) != 0) {
        a.x += lbl_803620C0 * c.x;
        a.y += lbl_803620C0 * c.y;
        a.z += lbl_803620C0 * c.z;
    }
    a.x += s1 * c.x;
    a.y += s1 * c.y;
    a.z += s1 * c.z;
    a.x += s0 * d.x;
    a.y += s0 * d.y;
    a.z += s0 * d.z;
    self->f224->v14(&a, &b, &c, &d, 0);
    lim = self->f480->f224;
    if (lim < fn_80072388(self->f492) - lbl_803620C4) {
        fn_80241DD0(self, lbl_8036206C, 0, 0, 0, 0);
    }
}

} /* extern "C" */
