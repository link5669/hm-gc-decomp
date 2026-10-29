// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_8023C754(void *);
void __dt__9C8023C7CCFv(void *, s16);
void fn_80250028(void *, s16);
void __dt__9C801829F8Fv(void *, s16);
void __dt__9C801E5944Fv(void *, s16);
void __dt__9C8023CE38Fv(void *, s16);
void __dl__FPv(void *);
extern void *lbl_802F1F7C[];
extern s32 lbl_8035B594;
} /* extern "C" */

struct VA8024F9AC {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6(void *);
};
struct VB8024F9AC {
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
    virtual void v26();
    virtual void v27();
    virtual void v28(void *);
};
struct G8024F9AC {
    u8 pad[11332];
    VB8024F9AC *f11332;
    u8 pad2[12100 - 11336];
    VA8024F9AC *f12100;
};
struct GG8024F9AC {
    u8 pad[12];
    G8024F9AC *f12;
};
extern "C" {
extern GG8024F9AC *lbl_8035B460;
}
struct M1_8024F9AC {
    u8 pad[36];
    virtual void v0();
    virtual void v1();
};
struct M2_8024F9AC {
    u8 pad[116];
    virtual void v0();
    virtual void v1();
};
struct M3_8024F9AC {
    u8 pad[16];
    virtual void v0();
    virtual void v1();
};

extern "C" {
u8 *fn_8024F9AC(u8 *self, s16 flag) {
    VA8024F9AC *x;
    G8024F9AC *g;
    if (self != 0) {
        *(void ***)(self + 16) = lbl_802F1F7C;
        if (*(void **)(self + 148) != 0) {
            fn_8023C754(*(void **)(self + 148));
            __dt__9C8023C7CCFv(*(void **)(self + 148), 1);
        }
        if (*(u8 **)(self + 844) != 0) {
            delete[] *(u8 **)(self + 844);
        }
        g = lbl_8035B460->f12;
        x = g->f12100;
        if (*(void **)(self + 328) != 0) {
            g->f11332->v28(*(void **)(self + 328));
        }
        ((M1_8024F9AC *)(self + 452))->v1();
        ((M2_8024F9AC *)(self + 332))->v1();
        ((M2_8024F9AC *)(self + 496))->v1();
        if (*(void **)(self + 492) != 0) {
            x->v6(*(void **)(self + 492));
        }
        *(void **)(self + 148) = 0;
        *(void **)(self + 152) = 0;
        *(void **)(self + 840) = 0;
        *(void **)(self + 844) = 0;
        *(void **)(self + 328) = 0;
        *(void **)(self + 492) = 0;
        ((M3_8024F9AC *)(self + 76))->v1();
        lbl_8035B594 = 0;
        fn_80250028(self + 616, -1);
        __dt__9C801829F8Fv(self + 496, -1);
        __dt__9C801E5944Fv(self + 452, -1);
        __dt__9C801829F8Fv(self + 332, -1);
        __dt__9C801E5944Fv(self + 284, -1);
        __dt__9C801829F8Fv(self + 164, -1);
        __dt__9C8023CE38Fv(self + 76, -1);
        __dt__9C8023CE38Fv(self, 0);
        if (flag > 0) {
            __dl__FPv(self);
        }
    }
    return self;
}

} /* extern "C" */
