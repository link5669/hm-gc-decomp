// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct O801DAE5C {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual s32 v40(void *s, void *a);
};
struct N801DAE5C { O801DAE5C *obj; s32 f4; N801DAE5C *next; };
struct S801DAE5C { u8 pad[136]; N801DAE5C *list; };
extern "C" {
void fn_801DAE5C(S801DAE5C *self, void *arg) {
    N801DAE5C *n;
    s32 failed = 0;
    for (n = self->list; n != 0; n = n->next) {
        if (n->obj->v40(self, arg) == 0) failed = 1;
    }
    if (failed) return;
}

} /* extern "C" */
