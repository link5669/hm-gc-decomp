// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */

struct C800FB754 { s32 cap; s32 f4; s32 f8; void *vt; u16 *buf; C800FB754(); };
void fn_800FB700(C800FB754 *, u16 *, s32);
void fn_801FE7EC(void *, const u8 *, C800FB754 *, C800FB754 *);
static const u8 guid[16] = { 0x9f, 0xff, 0x19, 0x19, 0x2f, 0x57, 0x49, 0xc7, 0x81, 0x58, 0x2d, 0xd4, 0x78, 0xcf, 0x43, 0x43 };
static const char name1[16] = "Atlas Sound GCN";
static const char name2[16] = "Atlas Sound GCN";

static inline void a2w(u16 *d, const char *s) {
    while (*s) { *d = *s; s++; d++; } *d = 0;
}

void fn_801FE894(u8 *self) {
    u16 w1[18];
    u16 w2[18];
    C800FB754 a;
    C800FB754 b;
    a2w(w1, name1);
    a2w(w2, name2);
    fn_800FB700(&a, w1, 17);
    fn_800FB700(&b, w2, 17);
    fn_801FE7EC(self + 4, guid, &a, &b);
}

} /* extern "C" */
