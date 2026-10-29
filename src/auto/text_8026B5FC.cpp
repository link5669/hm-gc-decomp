// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct C8023C7CC {
    u8 pad[8];
    void *a;
    void *b;
    u8 pad2[16];
    C8023C7CC();
    ~C8023C7CC();
};
struct E8026B5FC {
    u8 pad[88];
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
    virtual void v21(s32);
    virtual void v22(s32, f32);
};
struct B8026B5FC {
    u8 pad[16];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual E8026B5FC *v4(u32);
    virtual E8026B5FC *v5(u32);
    u8 pad3[4];
    u32 f24;
};
struct A8026B5FC {
    u8 pad[12];
    void *f12;
    u8 pad2[20];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual B8026B5FC *v8(s32);
};
struct P8026B5FC {
    u8 pad[24];
    A8026B5FC *f24;
    u8 pad2[28];
    u32 f56;
};
struct G8026B5FC {
    u8 pad[16];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual s32 v3();
};
struct X8026B5FC {
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
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26(s32, f32);
};
extern "C" {

extern G8026B5FC *lbl_8035B308;
extern f32 lbl_80366DD4;
void fn_8023C720(C8023C7CC *, void *);
void fn_8023C528(C8023C7CC *, s32);
X8026B5FC *fn_8023A490(void *, void *);
void fn_8023C3F4(C8023C7CC *);

void fn_8026B5FC(P8026B5FC *p) {
    B8026B5FC *b;
    E8026B5FC *e;
    u32 i;
    void *v;
    A8026B5FC *a = p->f24;
    if (a == 0 || a->f12 == 0) return;
    b = a->v8(0);
    for (i = 0; i < p->f56; i++) {
        e = b->v4(i);
        e->v22(0, lbl_80366DD4);
        e->v21(0);
    }
    for (i = 0; i < b->f24; i++) {
        v = b->v5(i);
        e = (E8026B5FC *)v;
        e->v22(0, lbl_80366DD4);
        e->v21(0);
    }
    {
        C8023C7CC it;
        if (lbl_8035B308->v3() == 1) {
            fn_8023C720(&it, lbl_8035B308);
            fn_8023C528(&it, 0);
            while (it.a != 0) {
                (it.a != 0 ? fn_8023A490(it.a, it.b) : 0)->v26(0, lbl_80366DD4);
                fn_8023C3F4(&it);
            }
        }
    }
}

} /* extern "C" */
