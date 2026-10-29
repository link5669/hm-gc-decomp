// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern char lbl_802A1BD8[];
void fn_80060568(char *, s32, s32, s32);
void fn_80190C98(void *);
} /* extern "C" */
struct I801906E0 {
    u8 pad[36];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(void *o);
};
struct O801906E0 {
    u8 pad[80];
    u32 f80;
    O801906E0 *f84;
    O801906E0 *f88;
    u8 pad2[104 - 92];
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void *v3();
};
extern "C" {
void fn_801906E0(O801906E0 *a, O801906E0 *b) {
    I801906E0 *pb;
    void *pa;
    O801906E0 **pp;
    O801906E0 *e;
    pa = a->v3();
    pb = (I801906E0 *)b->v3();
    if (pa == 0 || pb == 0) {
        fn_80060568(lbl_802A1BD8, 0, 0, 0);
    }
    pb->v5(pa);
    for (pp = &b->f88, e = b->f88; e != 0; pp = &e->f84, e = e->f84) {
        if (e == a) {
            *pp = e->f84;
            e->f84 = 0;
            e->f80 = 0;
            break;
        }
    }
    fn_80190C98(a);
}

} /* extern "C" */
