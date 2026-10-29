// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct E801DF574 { u8 pad[16]; u32 id; u8 pad2[40]; } E801DF574;
typedef struct T801DF574 { u8 pad[172]; s32 count; E801DF574 *arr; } T801DF574;
typedef struct S801DF574 {
    u8 pad0[4]; u32 flags; u8 pad8[24]; void *f32; u8 pad36[4]; s32 idx; u32 id; u8 pad48[32]; s32 state;
} S801DF574;
T801DF574 *fn_8019556C(void *);
void fn_801EB698(S801DF574 *);
static inline BOOL Find(S801DF574 *self) {
    T801DF574 *t = fn_8019556C(self->f32);
    u32 lo, hi, j;
    if (t == 0) return 0;
    if (self->idx >= 0) {
        lo = self->idx;
        hi = lo;
    } else {
        lo = 0;
        hi = t->count - 1;
    }
    for (j = lo; j <= hi; j++) {
        u32 id = t->arr[j].id; if (id == self->id) return 1;
    }
    return 0;
}
void fn_801DF574(S801DF574 *self) {
    if (!(self->flags & 1)) return;
    if (self->state != 3) return;
    if (Find(self)) {
        fn_801EB698(self);
    }
}

} /* extern "C" */
