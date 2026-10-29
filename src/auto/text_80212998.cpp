// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct E80212998 {
    u8 pad[16];
    u16 id;
    u8 pad2[2];
};
struct T80212998 {
    E80212998 *arr;
    u8 pad[8];
    u16 count;
    u8 pad2[4];
    u16 flags;
};
void fn_80212DA4(T80212998 *, s32);

E80212998 *fn_80212998(T80212998 *t, u32 id, s32 x) {
    u32 i;
    if (!(t->flags & 2)) {
        fn_80212DA4(t, x);
    }
    for (i = 0; i < t->count; i++) {
        if (id == t->arr[i].id) {
            return &t->arr[i];
        }
    }
    return 0;
}

} /* extern "C" */
