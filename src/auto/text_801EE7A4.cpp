// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct Key7A4 { u8 d[8]; };
s32 fn_800FB33C(void *);
void fn_800FB064(void *, void *);
u32 fn_800F9398(void *, void *);
u32 fn_800F9788(void *, char *, void *);
void fn_801EF720(u8 *, void *, s32);

void fn_801EE7A4(u8 *p, void *r, s32 id) {
    Key7A4 key;
    char grp[8];
    u8 *q;
    u32 v;
    s32 n;
    switch (id) {
    case 108:
        n = fn_800FB33C(r);
        *(u32 *)(p + 40) = *(u32 *)(*(u8 **)(*(u8 **)(p + 8) + 216) + 28) + n * 36;
        break;
    case 111:
        n = fn_800FB33C(r);
        *(u32 *)(p + 40) = *(u32 *)(*(u8 **)(*(u8 **)(p + 8) + 216) + 36) + n * 24;
        break;
    case 112:
        n = fn_800FB33C(r);
        *(u32 *)(p + 40) = *(u32 *)(*(u8 **)(*(u8 **)(p + 8) + 216) + 44) + n * 24;
        break;
    case 113:
        n = fn_800FB33C(r);
        *(u32 *)(p + 40) = *(u32 *)(*(u8 **)(*(u8 **)(p + 8) + 216) + 52) + n * 24;
        break;
    case 107:
        n = fn_800FB33C(r);
        *(u32 *)(p + 40) = *(u32 *)(*(u8 **)(*(u8 **)(p + 8) + 216) + 60) + n * 44;
        break;
    case 106:
        fn_800FB064(r, &key);
        fn_800FB064(r, grp);
        q = *(u8 **)(*(u8 **)(p + 8) + 212);
        if ((char *)grp == 0 || grp[0] == 0) {
            v = fn_800F9398(q + 204, &key);
        } else {
            v = fn_800F9788(q + 228, grp, &key);
        }
        *(u32 *)(p + 44) = v;
        break;
    case 165:
        *(u32 *)(p + 12) = 13;
        break;
    case 166:
        *(u32 *)(p + 12) = 14;
        break;
    default:
        fn_801EF720(p, r, id);
        break;
    }
}

} /* extern "C" */
