// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { u32 v[3]; } T12;
extern u8 * volatile lbl_8035B684;
void fn_801090D4(void *p, u32 b, T12 *c, s32 x, u32 d);
void fn_80253B24(void *a, u32 b, T12 * __restrict c, u32 d) {
    volatile T12 t;
    *(T12 *)&t = *c;
    fn_801090D4(lbl_8035B684 + 136, b, (T12 *)&t, -1, d);
}

} /* extern "C" */
