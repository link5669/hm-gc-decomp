// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { u32 a, b, c; } T_8003F18C; typedef struct { volatile u32 a; volatile u32 b; volatile u32 c; } S_8003F18C; extern S_8003F18C lbl_8029BF10;
extern void *volatile lbl_8035B65C;
void fn_80253AD8(void *, void *, void *, void *);
void fn_8003F18C(void *p, void *name) {
    volatile T_8003F18C t; u32 b, a;
    b = lbl_8029BF10.b; a = lbl_8029BF10.a; t.b = b; t.a = a; t.c = lbl_8029BF10.c;
    fn_80253AD8(lbl_8035B65C, p, (void *)&t, name);
}

} /* extern "C" */
