// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct B_8018C710 {
    u8 pad[104];
    u8 f104[4];
};
struct Node_8018C710 {
    u32 flags;
    u8 pad[20];
    u8 f24[80];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void *v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
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
    virtual void v27(B_8018C710 *, void *);
};
struct Group_8018C710 : Node_8018C710 {
    u8 pad2[152 - 108];
    u32 n;
    Node_8018C710 **children;
    f32 *thresholds;
    s32 offset;
};
f32 fn_8010155C(void *, void *);

void fn_8018C710(Group_8018C710 *self, B_8018C710 *b, void *c) {
    void *pos = b->f104;
    f32 t;
    u32 i;
    if (self->flags & 4) self->v2();
    t = fn_8010155C(self->f24, pos);
    if (c == 0) c = self->v4();
    for (i = 0; i < self->n; i++) {
        if (t <= self->thresholds[i]) {
            self->children[i]->v27(b, c);
            break;
        }
    }
}

} /* extern "C" */
