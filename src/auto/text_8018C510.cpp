// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Obj18C {
    u8 pad[104];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16();
    virtual void OnAdd(void *list);
};
extern "C" {
typedef struct {
    u8 pad[152];
    u32 count;
    Obj18C **objs;
    f32 *keys;
} List18C;

void fn_8018C510(List18C *self, Obj18C *obj, f32 key) {
    u32 i;
    u32 j;
    for (i = 0; i < self->count; i++) {
        if (key <= self->keys[i]) {
            break;
        }
    }
    for (j = self->count; j > i; j--) {
        self->objs[j] = self->objs[j - 1];
        self->keys[j] = self->keys[j - 1];
    }
    self->objs[i] = obj;
    self->keys[i] = key;
    obj->OnAdd(self);
    self->count++;
}

} /* extern "C" */
