// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct O801D1DE8 {
    virtual s32 v0(s32 id);
    virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50();
    virtual void v51(void *owner, void *x, void *arg);
    virtual void v52(void *owner, void *arg);
};
struct N801D1DE8 { O801D1DE8 *obj; s32 f4; N801D1DE8 *next; };
extern "C" {
void fn_801D1DE8(u8 *self, void *arg) {
    N801D1DE8 *p;
    if (*(void **)(self + 792) != 0) {
        for (p = *(N801D1DE8 **)(self + 136); p != 0; p = p->next) {
            if (p->obj->v0(19) != 0 && p->f4 != 0) {
                p->obj->v51(self, *(void **)(self + 792), arg);
            }
        }
    } else {
        for (p = *(N801D1DE8 **)(self + 136); p != 0; p = p->next) {
            if (p->obj->v0(19) != 0 && p->f4 != 0) {
                p->obj->v52(self, arg);
            }
        }
    }
    if (*(void **)(self + 792) != 0) {
        for (p = *(N801D1DE8 **)(self + 136); p != 0; p = p->next) {
            if (p->obj->v0(19) != 0 && p->f4 == 0) {
                p->obj->v51(self, *(void **)(self + 792), arg);
            }
        }
    } else {
        for (p = *(N801D1DE8 **)(self + 136); p != 0; p = p->next) {
            if (p->obj->v0(19) != 0 && p->f4 == 0) {
                p->obj->v52(self, arg);
            }
        }
    }
}

} /* extern "C" */
