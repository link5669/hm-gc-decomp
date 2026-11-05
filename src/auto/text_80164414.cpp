// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_80364684;
void fn_800D77D8(u32 obj, f32 *a, f32 *b, f32 *c);
struct S80164414 { u8 pad[6808]; u32 arr[8]; };
void fn_80164414(const S80164414 *p, s32 i, f32 *out) {
    fn_800D77D8(p->arr[i], out, out + 1, out + 2);
    out[3] = lbl_80364684;
}

} /* extern "C" */
