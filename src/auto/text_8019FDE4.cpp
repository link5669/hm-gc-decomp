// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct O_8019FDE4 { u32 f0; u8 pad[4]; f32 f8; u8 pad2[4]; f32 f16; } O_8019FDE4;
} /* extern "C" */
struct V_8019FDE4 {
    u8 pad[8];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(f32, O_8019FDE4 *, void *);
};
extern "C" {
typedef struct { u8 pad[12]; V_8019FDE4 *f12; V_8019FDE4 *f16; f32 f20; } S_8019FDE4;
extern f32 lbl_80364D78;
void *fn_8019BAB8(u32);
void fn_80195208(void *, void *);

void fn_8019FDE4(S_8019FDE4 *self, O_8019FDE4 *obj, f32 amount, void *x) {
    f32 d;
    void *y;
    d = obj->f8 - self->f20;
    if (d < -amount) {
        d = -d - amount;
        self->f16->v8(amount, obj, x);
    } else if (d >= amount) {
        d = d - amount;
        self->f12->v8(amount, obj, x);
    } else {
        y = fn_8019BAB8(obj->f0);
        if (y == 0) {
            self->f12->v8(amount, obj, x);
            return;
        }
        fn_80195208(x, y);
        if (d < lbl_80364D78) {
            d = -d;
            self->f16->v8(amount, obj, x);
            self->f12->v8(amount, obj, y);
        } else {
            self->f16->v8(amount, obj, y);
            self->f12->v8(amount, obj, x);
        }
    }
    if (d < obj->f16) obj->f16 = d;
}

} /* extern "C" */
