// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct C4 { u8 r, g, b, a; };
struct T2 { u32 f0; u8 pad4[16]; u8 f20[20]; u8 f40[364]; C4 c404[256]; u32 f1428; u32 f1432; u32 f1436; u8 pad1440[300]; f32 f1740; };
extern f32 lbl_80364398;
void fn_801482DC(void *, void *);
void fn_801472C8(T2 *t, void *a, void *b, C4 *src, u32 n) {
    if (t->f0 & 1) {
        t->f0 = 0;
        t->f1432 = 0;
        t->f1428 = 0;
        t->f1436 = 0;
        t->f1740 = lbl_80364398;
    }
    t->f0 = 1;
    fn_801482DC(t->f20, a);
    fn_801482DC(t->f40, b);
    if (src) {
        for (u32 i = 0; i < n; i++) t->c404[i] = src[i];
    }
}

} /* extern "C" */
