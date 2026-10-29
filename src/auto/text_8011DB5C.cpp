// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V_8011DB5C {
    u32 f0; u32 n4; u32 n8; u8 pad12[68]; s32 *keys; u8 pad84[76]; f32 *vals; u8 pad164[8];
    u32 count; u8 pad176[32];
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void *m(u32);
};
extern "C" {
extern f32 lbl_80363DB0;
f32 fn_80118ACC(void *);

static inline u32 find_8011DB5C(V_8011DB5C *q, s32 k) {
    u32 i;
    for (i = 0; i < q->count; i++) {
        if (k == q->keys[i * 2]) return i;
    }
    return -1;
}

static inline f32 get_8011DB5C(V_8011DB5C *q, u32 i) {
    if (i >= q->count) return lbl_80363DB0;
    if (i < q->n4) return fn_80118ACC(q->m(i));
    i -= q->n4;
    if (i < q->n8) return q->vals[i];
    return lbl_80363DB0;
}

static inline f32 get2_8011DB5C(V_8011DB5C *q, u32 i) {
    if (i < q->count) {
        return get_8011DB5C(q, i);
    }
    return lbl_80363DB0;
}
f32 fn_8011DB5C(V_8011DB5C *q, s32 k) {
    u32 i = find_8011DB5C(q, k);
    if (i < q->count) {
        return get2_8011DB5C(q, i);
    }
    return lbl_80363DB0;
}

} /* extern "C" */
