// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */

struct V8025DF94 {
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
    virtual void Get(f32 *a, f32 *b, f32 *c, f32 *d, s32 e);
};

extern "C" {

extern char lbl_8036696C[7];
extern volatile u32 lbl_8035B6E8;
extern volatile u32 lbl_8035B6EC;
extern volatile u32 lbl_8035B6E0;
extern volatile u32 lbl_8035B6E4;
extern volatile u32 lbl_8035A244;
extern volatile u32 lbl_8035A248;
extern void *volatile lbl_8035B5E4;
extern f32 lbl_80357E90[4];
extern f32 lbl_80366950;
extern f32 lbl_80366954;
void *fn_800F8274(void *a, char *b);
void fn_8025732C(u8 *self);
void fn_80101820(f32 *v);
void fn_8022345C(void *p, f32 f);

static inline void VecSub(f32 *out, f32 *a, f32 *b) {
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}
static inline void VecCopy(f32 *out, f32 *a) {
    out[0] = a[0];
    out[1] = a[1];
    out[2] = a[2];
}
static inline void VecCross(f32 *out, f32 *a, f32 *b) {
    out[0] = a[1] * b[2] - a[2] * b[1];
    out[1] = a[2] * b[0] - a[0] * b[2];
    out[2] = a[0] * b[1] - a[1] * b[0];
}

void fn_8025DF94(u8 *self) {
    lbl_8035B6E8 = 0;
    lbl_8035B6EC = 0;
    lbl_8035B6E0 = 0;
    lbl_8035B6E4 = 0;
    lbl_8035A244 = 0;
    lbl_8035A248 = 0;
    *(void **)(self + 192) = fn_800F8274(lbl_8035B5E4, lbl_8036696C);
    fn_8025732C(self);
    (*(V8025DF94 **)(*(u8 **)(self + 156) + 396))->Get((f32 *)(self + 404), (f32 *)(self + 92), (f32 *)(self + 104), (f32 *)(self + 116), 0);
    (*(V8025DF94 **)(self + 156))->Get((f32 *)(self + 20), 0, 0, 0, 0);
    VecSub((f32 *)(self + 244), (f32 *)(self + 404), (f32 *)(self + 20));
    VecCopy((f32 *)(self + 256), lbl_80357E90);
    VecCross((f32 *)(self + 268), (f32 *)(self + 244), (f32 *)(self + 256));
    fn_80101820((f32 *)(self + 244));
    fn_80101820((f32 *)(self + 256));
    fn_80101820((f32 *)(self + 268));
    *(f32 *)(self + 384) = lbl_80366950;
    *(f32 *)(self + 388) = lbl_80366950;
    *(f32 *)(self + 200) = lbl_80366950;
    *(f32 *)(self + 356) = lbl_80366954;
    fn_8022345C(*(void **)(self + 156), lbl_80366950);
}

} /* extern "C" */
