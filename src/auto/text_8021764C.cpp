// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { u8 f0; u8 f1; u16 f2; u8 *f4; u32 f8; } S_8021764C;
void fn_800D9C58(u8 *, u32);
void fn_800D6B8C(u32, u32, u16);

static inline void emit_8021764C(S_8021764C *self, u32 prim) {
    u8 *p;
    u8 *end;
    fn_800D6B8C(prim, self->f4[0] & 7, *(u16 *)(self->f4 + 1));
    p = self->f4 + 3;
    end = p + self->f1 * (self->f2 * 2);
    if (self->f0 & 2) end += self->f2;
    while (p < end) { *(volatile u8 *)0xCC008000 = *p++; }
}

void fn_8021764C(S_8021764C *self, s32 mode) {
    if (mode == 0) {
        fn_800D9C58(self->f4, self->f8);
    } else if (mode == 1) {
        emit_8021764C(self, 168);
    } else {
        emit_8021764C(self, 184);
    }
}

} /* extern "C" */
