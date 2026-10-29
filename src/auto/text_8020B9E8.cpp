// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
s32 fn_800CDD24(void *, s32 *, s32 *);
s32 fn_800D0B94(void *, s32 *, s32 *);

s32 fn_8020B9E8(u8 *p) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    if (*(u32 *)(p + 8) & 2) {
        if (fn_800CDD24(*(void **)p, &a, &b) == 0) {
            if (fn_800D0B94(*(void **)p, &c, &d) == 0) {
                return ((c << 17) - a) / d;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

} /* extern "C" */
