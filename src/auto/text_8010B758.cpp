// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern s32 lbl_8035AAA4;
extern s32 lbl_8035AAA0;
} /* extern "C" */
struct A {
    u8 pad[488];
    s32 f488;
    virtual ~A();
};
struct B0 {
    u8 pad0[16];
    virtual ~B0();
    virtual void v1();
};
struct B : B0 {
    u8 pad1[52];
    s32 f72;
};
extern "C" void fn_80110E5C(A *);
struct C8010B8F8 {
    s32 f0;
    s32 f4;
    A **arr8;
    B **arrC;
    u16 n10;
    u16 n12;
    ~C8010B8F8();
    inline void FreeA() {
        if (arr8 != 0) {
            for (u32 i = 0; i < n10; i++) {
                if (arr8[i] != 0) {
                    if (arr8[i]->f488 != 0) fn_80110E5C(arr8[i]);
                    delete arr8[i];
                    arr8[i] = 0;
                }
            }
            delete[] arr8;
        }
    }
    inline void FreeB() {
        if (arrC != 0) {
            for (u32 i = 0; i < n12; i++) {
                if (arrC[i] != 0) {
                    if (arrC[i]->f72 != 0) arrC[i]->v1();
                    delete arrC[i];
                    arrC[i] = 0;
                }
            }
            delete[] arrC;
        }
    }
};
C8010B8F8::~C8010B8F8() {
    if (f0 != 0) {
        FreeA();
        FreeB();
        f0 = 0;
        arr8 = 0;
        arrC = 0;
        n10 = 0;
        n12 = 0;
        f4 = 0;
        lbl_8035AAA4 = 0;
        lbl_8035AAA0 = 0;
    }
}
extern "C" {

} /* extern "C" */
