// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct S801D8CBC;
struct O801D8CBC {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual s32 v19(S801D8CBC *self, u32 arg);
};
struct N801D8CBC { O801D8CBC *obj; s32 f4; N801D8CBC *next; };
struct B801D8CBC {
    u8 pad[128];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); 
    virtual void v59(u32 a, s32 b);
    virtual void v60(u32 a, s32 b);
};
struct S801D8CBC : B801D8CBC {
    u32 f132;
    N801D8CBC *f136;
    u8 pad2[244 - 140];
    S801D8CBC *f244;
    u8 pad3[264 - 248];
    S801D8CBC *f264;
};
extern "C" {
s32 fn_801D8CBC(S801D8CBC *self, u32 arg) {
    N801D8CBC *n1;
    s32 found1;
    N801D8CBC *n2;
    s32 found2;
    found1 = 0;
    for (n1 = self->f136; n1 != 0; n1 = n1->next) {
        if (n1->f4 != 0) {
            if (n1->obj->v19(self, arg) == 0) found1 = 1;
        }
    }
    if (found1) return 0;
    if (arg & 3) {
        if (self->f264) {
            self->v60(arg, 1);
            self->f264->v59(arg, 1);
        }
    } else {
        if (self->f244) {
            self->v60(arg, 1);
            self->f244->v59(arg, 1);
        }
    }
    found2 = 0;
    for (n2 = self->f136; n2 != 0; n2 = n2->next) {
        if (n2->f4 == 0) {
            if (n2->obj->v19(self, arg) == 0) found2 = 1;
        }
    }
    return found2 ? 0 : 0;
}

} /* extern "C" */
