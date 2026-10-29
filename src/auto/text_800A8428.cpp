// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct O800A8428 {
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
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33(const char *a, void *b, s32 c, f32 *d, s32 e);
};
extern "C" {
extern const char lbl_80362018[8];
void fn_8007225C(void *, f32);
void fn_8023FE08(void *, f32);
void fn_800A8428(u8 *self, f32 dt) {
    if (*(s32 *)(self + 284) == 1) {
        f32 v = -**(f32 **)(self + 292) * dt;
        if (*(s32 *)(self + 288) != 0) {
            (*(O800A8428 **)(self + 280))->v33(lbl_80362018, *(void **)(self + 224), 0, &v, 0);
            *(s32 *)(self + 288) = 0;
        } else {
            fn_8007225C(*(void **)(self + 280), v);
        }
    }
    fn_8023FE08(self, dt);
}

} /* extern "C" */
