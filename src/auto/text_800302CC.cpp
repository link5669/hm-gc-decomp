// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { u32 v[3]; } T12;
extern T12 lbl_802AF9B0;
extern void *volatile lbl_8035B65C;
void fn_80253B24(void *g, u32 a, T12 *v, u32 b);
void fn_800302CC(u32 a, u32 b) {
    volatile T12 t; const volatile T12 *s = &lbl_802AF9B0; u32 z, y, x; x = s->v[0]; y = s->v[1]; z = s->v[2]; t.v[0] = x; t.v[1] = y; t.v[2] = z; fn_80253B24(lbl_8035B65C, a, (T12 *)&t, b);
}

} /* extern "C" */
