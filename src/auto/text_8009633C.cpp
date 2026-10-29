/* Functions from 0x8009633C to 0x8009651C, found by decomp-toolkit. */
#include "common.h"

extern "C" {

/* QV=2.0p1 */
#pragma opt_propagation off
extern f32 lbl_803610A0;

typedef struct S8009633C {
    u8 pad[284];
    f32 *cur[6];
    f32 *src[6];
    u8 pad2[348 - 332];
    f32 start[6];
} S8009633C;

#define CL(x) x = v; if ((v < cur && cur < start) || (v > cur && cur > start)) x = cur;
#define CL1(x) x = v; if ((v < cur && cur < start) || (x > cur && cur > start)) x = cur;

void fn_8009633C(S8009633C *p, s32 mode, s32 which, f32 t) {
    f32 v, a, start, cur, b, c, d, e, f;
    if (t < lbl_803610A0) t = lbl_803610A0;
    if (mode) {
        a = which ? *p->src[0] : p->start[0];
        b = which ? *p->src[1] : p->start[1];
        c = which ? *p->src[2] : p->start[2];
        d = which ? *p->src[3] : p->start[3];
        e = which ? *p->src[4] : p->start[4];
        f = which ? *p->src[5] : p->start[5];
    } else {
        start = p->start[0];
        cur = *p->cur[0];
        v = start - t * (start - cur);
        CL1(a)
        CL(b)
        CL(c)
        CL(d)
        CL(e)
        CL(f)
    }
    *p->cur[0] = a;
    *p->cur[1] = b;
    *p->cur[2] = c;
    *p->cur[3] = d;
    *p->cur[4] = e;
    *p->cur[5] = f;
}
#pragma opt_propagation reset

} /* extern "C" */
