// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct N_8022D77C { N_8022D77C *next; N_8022D77C *prev; };
struct S_8022D77C {
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
    virtual void v14(void *, void *, void *, void *, void *);
    u8 pad4[76];
    u8 f80[12];
    u8 f92[12];
    u8 f104[12];
    u8 f116[12];
    u8 f128[12];
    u8 pad140[16];
    void *f156;
    u8 pad160[28];
    N_8022D77C *f188;
    N_8022D77C *f192;
    f32 f196;
    s32 f200;
    s32 f204;

    N_8022D77C *pop() {
        N_8022D77C *n = f188;
        if (n != 0) {
            if ((f188 = n->next) != 0) {
                f188->prev = 0;
            } else {
                f192 = 0;
            }
        }
        return n;
    }
};
extern f32 lbl_80365D28;

void fn_8022D77C(S_8022D77C *self) {
    if (self->f156 != 0) {
        self->f196 = lbl_80365D28;
        self->f200 = 0;
        self->f204 = 0;
        while (self->f188 != 0) {
            delete self->pop();
        }
        self->v14(self->f80, self->f92, self->f116, self->f104, self->f128);
    }
}

} /* extern "C" */
