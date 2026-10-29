// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct A8026DD40 {
    u8 pad0[88];
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
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22(f32 v, s32 a);
};
struct C8026DD40 {
    u8 pad0[16];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual A8026DD40 *v4(u32 i);
    virtual A8026DD40 *v5(u32 i);
    u8 pad20[4];
    u32 f24;
};
struct B8026DD40 {
    u8 pad0[36];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual C8026DD40 *v8(s32 a);
};
struct G8026DD40 {
    u8 pad0[36];
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
    virtual void v12(f32 v);
};
struct E8026DD40 {
    A8026DD40 *p;
    u32 x;
};
struct S8026DD40 {
    u8 pad0[24];
    B8026DD40 *f24;
    f32 f28;
    f32 *f32;
    A8026DD40 *f36;
    A8026DD40 *f40;
    A8026DD40 *f44;
    u8 pad48[8];
    u32 f56;
    u8 pad60[8];
    u32 f68;
    E8026DD40 f72[1];
};
extern "C" {
extern G8026DD40 *lbl_8035B7C4;

void fn_8026DD40(S8026DD40 *self, s32 flag, f32 v) {
    C8026DD40 *c;
    u32 i;
    if (flag != 0) {
        *self->f32 = v;
    }
    if (self->f36 != 0) {
        self->f36->v22(v, 0);
    }
    if (self->f40 != 0) {
        self->f40->v22(v, 0);
    }
    if (self->f44 != 0) {
        self->f44->v22(v, 0);
    }
    if (self->f24 != 0) {
        c = self->f24->v8(0);
        for (i = 0; i < self->f56; i++) {
            c->v4(i)->v22(v, 0);
        }
        for (i = 0; i < c->f24; i++) {
            c->v5(i)->v22(v, 0);
        }
    }
    for (i = 0; i < self->f68; i++) {
        self->f72[i].p->v22(v, 0);
    }
    lbl_8035B7C4->v12(v);
    self->f28 = v;
}

} /* extern "C" */
