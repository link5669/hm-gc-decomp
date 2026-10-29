// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct X80236628 {
    u8 pad[104];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual ~X80236628();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
};
struct E80236628 { X80236628 *obj; };
struct V140_80236628 {
    u8 pad[16];
    virtual void v0();
    virtual void v1();
};
struct M80236628 {
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
    virtual void v10(void *);
};
struct F80236628 { u8 b; u8 pad[7]; };
struct S80236628 {
    u32 f0;
    u32 f4[10];
    F80236628 f44[10];
    u32 f124;
    E80236628 ***f128;
    void *f132;
    void *f136;
    V140_80236628 *f140;
};
extern "C" {

extern u8 *lbl_8035B460;
void fn_800E1E88(void *, void (*)(void *, s32));
void __dla__FPv(void *);
void __dl__FPv(void *);
void fn_8023C754(void *);
void __dt__9C8023C7CCFv(void *, s32);
void __dt__9C8013ECE4Fv(void *, s32);

void fn_80236628(S80236628 *p) {
    u32 i;
    u32 j;
    u32 k;
    if (p->f136) {
        fn_800E1E88(p->f136, __dt__9C8013ECE4Fv);
    }
    if (p->f140) {
        p->f140->v1();
        (*(M80236628 **)(*(u8 **)(lbl_8035B460 + 12) + 11332))->v10(p->f140);
    }
    if (p->f128) {
        for (i = 0; i < p->f124; i++) {
            if (p->f128[i]) {
                for (j = 0; j < p->f4[i]; j++) {
                    if (p->f128[i][j]) {
                        p->f128[i][j]->obj->v10();
                        delete p->f128[i][j]->obj;
                        __dl__FPv(p->f128[i][j]);
                    }
                }
                __dla__FPv(p->f128[i]);
            }
        }
        __dla__FPv(p->f128);
    }
    if (p->f132) {
        fn_8023C754(p->f132);
        __dt__9C8023C7CCFv(p->f132, 1);
    }
    p->f0 = 0;
    p->f124 = 0;
    p->f128 = 0;
    for (k = 0; k < 10; k++) {
        p->f4[k] = 0;
        p->f44[k].b = 0;
    }
    p->f132 = 0;
    p->f136 = 0;
    p->f140 = 0;
}

} /* extern "C" */
