/* Functions from 0x80151E84 to 0x80151F08, found by decomp-toolkit. */
#include "common.h"

extern "C" {

typedef struct {
    f32 x, y, z;
} Vec3f;

extern f32 lbl_8036453C;
extern f32 lbl_80364544;

static inline void Mtx44Trans(f32 *m, f32 x, f32 y, f32 z) {
    m[0] = lbl_8036453C;
    m[1] = lbl_80364544;
    m[2] = lbl_80364544;
    m[3] = x;
    m[4] = lbl_80364544;
    m[5] = lbl_8036453C;
    m[6] = lbl_80364544;
    m[7] = y;
    m[8] = lbl_80364544;
    m[9] = lbl_80364544;
    m[10] = lbl_8036453C;
    m[11] = z;
    m[12] = lbl_80364544;
    m[13] = lbl_80364544;
    m[14] = lbl_80364544;
    m[15] = lbl_8036453C;
}

extern f32 lbl_8036453C;
extern f32 lbl_80364544;

/* QV=2.0p1 */
typedef struct V80151E84 { f32 x, y, z; } V80151E84;
void fn_80151E84(f32 (*m)[4], const V80151E84 *v) {
    m[0][0] = lbl_8036453C;
    m[0][1] = lbl_80364544;
    m[0][2] = lbl_80364544;
    m[0][3] = v->x;
    m[1][0] = lbl_80364544;
    m[1][1] = lbl_8036453C;
    m[1][2] = lbl_80364544;
    m[1][3] = v->y;
    m[2][0] = lbl_80364544;
    m[2][1] = lbl_80364544;
    m[2][2] = lbl_8036453C;
    m[2][3] = v->z;
    m[3][0] = lbl_80364544;
    m[3][1] = lbl_80364544;
    m[3][2] = lbl_80364544;
    m[3][3] = lbl_8036453C;
}

} /* extern "C" */
