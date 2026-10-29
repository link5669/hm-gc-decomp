// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct O8026B090 {
    u8 pad[88];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(void *); virtual void v22(void *, f32);
};
struct E8026B090 { O8026B090 *obj; u32 key; };
struct S8026B090 { u8 pad[72]; E8026B090 arr[1]; };
extern "C" {
extern f32 lbl_80366DD4;
#pragma opt_propagation off
s32 fn_8026B090(S8026B090 *self, u32 key, s32 *idx, void *arg) {
    if (self->arr[*idx].key != key) return 0;
    if (self->arr[*idx].key == key) {
        void *a = arg;
        self->arr[*idx].obj->v22(a, lbl_80366DD4);
        self->arr[*idx].obj->v21(a);
        return 1;
    }
    return 0;
}
#pragma opt_propagation reset

} /* extern "C" */
