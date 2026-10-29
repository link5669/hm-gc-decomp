// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V8007B1F0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(f32 *out, s32 a, s32 b, s32 c, s32 d);
    virtual void v14(f32 *pos, s32 a, s32 b, s32 c, s32 d);
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24();
};
extern "C" {
extern f32 lbl_8035F76C;
extern char lbl_802984F4[];
extern char lbl_8035F720[4];
s32 fn_8022C558(V8007B1F0 *p);
void fn_8022A7A8(V8007B1F0 *p);
void fn_8022B618(V8007B1F0 *p);
void fn_80241DD0(u8 *self, char *name, s32 a, s32 b, s32 c, s32 d);
void fn_80101820(f32 *v);
s32 fn_800F6CD0(void *p, char *name);
void fn_8007AC1C(u8 *self, f32 dt);
void fn_8023FE08(u8 *self, f32 dt);

void fn_8007B1F0(u8 *self, f32 dt) {
    f32 t[3];
    f32 d[3];
    f32 pos[3];
    f32 s;
    if (*(s32 *)(self + 404) == 0) {
        if (fn_8022C558(*(V8007B1F0 **)(self + 224)) != 0) {
            (*(V8007B1F0 **)(self + 224))->v24();
            fn_8022A7A8(*(V8007B1F0 **)(self + 224));
            fn_8022B618(*(V8007B1F0 **)(self + 224));
            *(s32 *)(self + 404) = 0;
        }
    }
    if (*(s32 *)(self + 96) == 2) {
        *(f32 *)(self + 424) -= **(f32 **)(self + 376) * dt;
        if (*(f32 *)(self + 424) <= lbl_8035F76C) {
            fn_80241DD0(self, lbl_802984F4, 0, 0, 0, 0);
        } else {
            (*(V8007B1F0 **)(self + 224))->v13(pos, 0, 0, 0, 0);
            d[0] = pos[0] - *(f32 *)(self + 408);
            d[1] = pos[1] - *(f32 *)(self + 412);
            d[2] = pos[2] - *(f32 *)(self + 416);
            fn_80101820(d);
            s = *(f32 *)(self + 424);
            d[0] *= s;
            d[1] *= s;
            d[2] *= s;
            t[0] = *(f32 *)(self + 408) + d[0];
            t[1] = *(f32 *)(self + 412) + d[1];
            t[2] = *(f32 *)(self + 416) + d[2];
            (*(V8007B1F0 **)(self + 224))->v14(t, 0, 0, 0, 0);
        }
    } else if (fn_800F6CD0(*(void **)(self + 292), lbl_8035F720) != 0) {
        fn_8007AC1C(self, dt);
    }
    *(s32 *)(self + 400) = *(s32 *)(self + 396);
    fn_8023FE08(self, dt);
}

} /* extern "C" */
