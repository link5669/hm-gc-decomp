// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct E68 { u8 pad[68]; };
struct E128 { u8 pad[128]; };
typedef void (E68::*PMF)(E128 *, u32);
struct S801F37B0 {
    u8 pad[32];
    u32 f32;
    u8 pad2[12];
    u32 f48;
    u32 f52;
    E68 *arr68;
    u32 f60;
    E128 *arr128;
};
extern "C" {
extern PMF lbl_80330CC8;

void fn_801F37B0(S801F37B0 *self) {
    u32 n;
    u32 i;
    if (self->arr68 == 0 || self->arr128 == 0) return;
    n = self->f52 * self->f48;
    for (i = 0; i < n; i++) {
        (self->arr68[i].*lbl_80330CC8)(&self->arr128[i], self->f32);
    }
}

} /* extern "C" */
