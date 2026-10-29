// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { u32 v[3]; } Vec80053FD4;
extern u32 lbl_8035DF58;
extern volatile f32 lbl_8035DF6C;
void fn_80107244(void *, void *);
void fn_80053D9C(u8 *, Vec80053FD4 *, f32);

void fn_80053FD4(u8 *p) {
    u32 *q;
    volatile Vec80053FD4 v;
    volatile Vec80053FD4 w;
    u32 c, b, a;

    q = *(u32 **)(p + 344);
    if (q != 0) {
        *q |= lbl_8035DF58;
    }
    *(s32 *)(p + 300) = 1;
    fn_80107244(*(void **)(p + 348), p + 376);
    *(f32 *)(p + 428) = lbl_8035DF6C;
    fn_80107244(*(void **)(p + 352), (void *)&v);
    a = v.v[0];
    b = v.v[1];
    c = v.v[2];
    w.v[0] = a;
    w.v[1] = b;
    w.v[2] = c;
    fn_80053D9C(p, (Vec80053FD4 *)&w, lbl_8035DF6C);
}

} /* extern "C" */
