// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct D8013A034 { u8 *data; s32 stride; u8 pad[104]; };
struct C8013A034 {
    u8 pad[12];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual s32 v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(D8013A034 *d, s32 n);
};
extern "C" {
s32 fn_8013A034(C8013A034 *self, s32 idx, f32 *out) {
    D8013A034 d;
    f32 *p;
    self->v22(&d, 4);
    p = (f32 *)(d.data + idx * d.stride);
    out[0] = p[0];
    out[1] = p[1];
    return self->v6();
}

} /* extern "C" */
