// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_800FB064(void *, void *);
void fn_801C068C(u8 *, void *, u8 *, void *);
void fn_801A6EC8(u8 *, s32, void *, void *);

void fn_801B9028(u8 *p, s32 c, void *a, void *b) {
    char key[16];
    switch (c) {
    case 'a':
        fn_800FB064(b, key);
        fn_801C068C(p, a, p + 360, key);
        break;
    case 'd':
        *(u32 *)(p + 364) |= 1;
        break;
    case 'e':
        *(u32 *)(p + 364) |= 4;
        break;
    case 'h':
        *(u32 *)(p + 364) |= 32;
        break;
    case 'i':
        *(u32 *)(p + 364) |= 64;
        break;
    case 'f':
        *(u32 *)(p + 364) |= 8;
        break;
    case 'g':
        *(u32 *)(p + 364) |= 16;
        break;
    case 'j':
        *(u32 *)(p + 364) |= 128;
        break;
    default:
        fn_801A6EC8(p, c, a, b);
    }
}

} /* extern "C" */
