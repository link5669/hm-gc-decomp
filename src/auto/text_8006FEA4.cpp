// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern char lbl_80297D28[];
extern void *volatile lbl_8035A0A4;
s32 fn_8003C674(void *, char *, s32 *volatile *);
void fn_800746A4(void *, void *);
void fn_80242210(void *);
} /* extern "C" */

struct E_8006FEA4 {
    u8 pad[104];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual ~E_8006FEA4();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
};

struct S_8006FEA4 {
    u8 pad0[224];
    void *f224;
    u8 pad1[304];
    u32 n532;
    u8 pad2[12];
    E_8006FEA4 **a548;
    s32 *a552;
    E_8006FEA4 *p556;
    u8 pad3[20];
    u8 f580[16];
    s32 f596;
    u8 pad4[16];
    s32 f616;
};

extern "C" {

void fn_8006FEA4(S_8006FEA4 *self) {
    s32 amt = self->f616;
    s32 *volatile ptr = 0;
    u32 i;
    s32 *q;
    u32 j;
    if (fn_8003C674(lbl_8035A0A4, lbl_80297D28, &ptr) == 0) {
        *ptr = 0;
    }
    q = ptr;
    *q += amt;
    self->f616 -= amt;
    if (self->f224 != 0 && self->f596 != 0) {
        fn_800746A4(self->f224, self->f580);
    }
    if (self->a548 != 0) {
        for (i = 0; i < self->n532; i++) {
            if (self->a548[i] != 0) {
                self->a548[i]->v10();
                delete self->a548[i];
            }
            self->a548[i] = 0;
        }
        delete[] self->a548;
        self->a548 = 0;
    }
    if (self->a552 != 0) {
        for (j = 0; j < self->n532; j++) {
            self->a552[j] = 0;
        }
        delete[] self->a552;
        self->a552 = 0;
    }
    if (self->p556 != 0) {
        delete self->p556;
        self->p556 = 0;
    }
    fn_80242210(self);
}

} /* extern "C" */
