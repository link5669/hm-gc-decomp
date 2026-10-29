// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Self801DA1E4;
struct Obj801DA1E4 {
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
    virtual s32 v11(Self801DA1E4 *, s32);
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
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50(Self801DA1E4 *, s32);
};
struct Node801DA1E4 { Obj801DA1E4 *obj; s32 active; Node801DA1E4 *next; };
struct Self801DA1E4 { u8 pad[136]; Node801DA1E4 *list; u8 pad2[324 - 140]; u32 f324; u32 f328; };
extern "C" {

s32 fn_801DA1E4(Self801DA1E4 *self, s32 arg) {
    Node801DA1E4 *n;
    s32 found;
    Node801DA1E4 *m;
    s32 found2;

    found = 0;
    for (n = self->list; n != 0; n = n->next) {
        if (n->active != 0) {
            if (n->obj->v11(self, arg) == 0) found = 1;
        }
    }
    if (found) return 0;
    switch ((u16)self->f324) {
    case 2:
        for (n = self->list; n != 0; n = n->next) n->obj->v50(self, 256);
        self->f328 = self->f324;
        self->f324 = (self->f324 & 0xFFFF0000) | 256;
        break;
    case 8:
        for (n = self->list; n != 0; n = n->next) n->obj->v50(self, 512);
        self->f328 = self->f324;
        self->f324 = (self->f324 & 0xFFFF0000) | 512;
        break;
    }
    m = self->list;
    found2 = 0;
    for (; m != 0; m = m->next) {
        if (m->active == 0) {
            if (m->obj->v11(self, arg) == 0) found2 = 1;
        }
    }
    return found2 ? 0 : 0;
}

} /* extern "C" */
