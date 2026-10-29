// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct T12_801EF83C { u32 v[3]; };
struct Base_801EF83C {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
};
struct Obj_801EF83C : Base_801EF83C {
    s32 f4;
    s32 f8;
    s32 fC;
    T12_801EF83C f10;
    s32 f1C;
    s32 f20;
    u32 f24;
};
extern "C" {
extern T12_801EF83C lbl_8029BF10;
void fn_801EF83C(Obj_801EF83C *p) {
    if (p->f8 != 0) {
        if (p->f24 & 1) p->v7();
        p->f24 &= ~2;
        p->fC = 0;
        p->f8 = 0;
        p->f1C = 0;
        p->f10 = lbl_8029BF10;
        p->f20 = 0;
        p->f24 = 0;
    }
}

} /* extern "C" */
