// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct S801644BC { u8 pad[6808]; void *arr[1]; } S801644BC;
typedef struct V801644BC { f32 x, y, z; } V801644BC;
void fn_800D79CC(void *o, f32 *x, f32 *y, f32 *z);
void fn_801644BC(const S801644BC *p, s32 i, V801644BC *out) {
    fn_800D79CC(p->arr[i], &out->x, &out->y, &out->z);
    out->y = -out->y;
    out->z = -out->z;
}

} /* extern "C" */
