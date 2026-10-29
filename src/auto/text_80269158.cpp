// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V88 {
    u8 pad[88];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(int);
};
struct VB {
    virtual void v0(); virtual int v1();
};
struct VG {
    u8 pad[256];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(void *, f32);
};
struct E88 {
    u32 f0;
    u32 f4;
    u32 a[10];
    u32 b[10];
};
struct S {
    u8 pad0[20];
    E88 e[15];
    u8 pad1340[4];
    u32 f1344;
    u8 pad1348[4];
    f32 f1352;
    V88 *f1356;
    VB *f1360;
    u8 pad1364[4];
    V88 *f1368;
    u8 pad1372[4];
    f32 f1376;
    u32 f1380;
    u32 g[20];
    f32 f1464;
    u32 f1468;
};
extern "C" {
extern VG *lbl_8035B7C8;
extern void *lbl_8035B7C4;
extern f32 lbl_80366D50;
extern f32 lbl_80366D48;

void fn_80269158(S *self) {
    u32 i;
    u32 j;
    if (self->f1356) self->f1356->v21(0);
    if (self->f1368) self->f1368->v21(0);
    if (self->f1360) {
        while (self->f1360->v1()) {
            lbl_8035B7C8->v3(lbl_8035B7C4, lbl_80366D50);
        }
    }
    self->f1344 = 0;
    self->f1352 = lbl_80366D48;
    self->f1376 = lbl_80366D48;
    self->f1468 = 0;
    self->f1464 = lbl_80366D48;
    self->f1380 = 15;
    for (i = 0; i < 15; i++) {
        self->e[i].f0 = 0;
        self->e[i].f4 = 0;
        for (j = 0; j < 10; j++) {
            self->e[i].a[j] = 0;
            self->e[i].b[j] = 0;
        }
    }
    for (i = 0; i < 20; i++) {
        self->g[i] = 15;
    }
}

} /* extern "C" */
