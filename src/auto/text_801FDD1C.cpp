// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_801FA5A0(u8 *p, u8 *arg, f32 f);
void fn_80206164(u8 *q, u8 *arg, f32 f);
void fn_801FED50(u8 *q, f32 f);

#pragma optimization_level 1
void fn_801FDD1C(u8 *p, u8 *arg, f32 f) {
    u8 *a;
    u8 *q;
    fn_801FA5A0(p, arg, f);
    a = arg;
    if (arg != 0) {
        for (arg = *(u8 **)(p + 260); arg != 0; arg = *(u8 **)(arg + 156)) {
            fn_80206164(arg, a, f);
        }
        q = *(u8 **)(p + 264);
        while (q != 0) {
            arg = *(u8 **)(q + 96);
            fn_801FED50(q, f);
            q = arg;
        }
    }
}
#pragma optimization_level reset

} /* extern "C" */
