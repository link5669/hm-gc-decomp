// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct X_80106560 { u32 f0; s32 idx; };
struct E80_80106560 { u8 pad[20]; X_80106560 *f20; u8 pad2[24]; u8 f48[32]; };
struct E40_80106560 { u8 pad[16]; u32 f16; u8 pad2[12]; u32 f32; u8 pad3[4]; };
struct Self_80106560 { u8 pad[36]; u32 count; E80_80106560 *arr; u8 f44[4]; };
struct P2_80106560 { u8 pad[36]; E40_80106560 *arr; };
struct FnTab_80106560 { u8 pad[12]; void (*f12)(u32, void *); u8 pad2[8]; void (*f24)(u32, void *); };
extern FnTab_80106560 lbl_803286D0;
extern u32 lbl_803638C4;
static inline void Set_80106560(E40_80106560 *e, void (*fn)(u32, void *), void *d) {
    fn(e->f16, d);
    e->f32 |= lbl_803638C4;
}
void fn_80106560(Self_80106560 *self, P2_80106560 *p) {
    u32 i;
    for (i = 0; i < self->count; i++) {
        Set_80106560(&p->arr[i], lbl_803286D0.f24, self->arr[i].f48);
    }
    Set_80106560(&p->arr[self->arr->f20->idx], lbl_803286D0.f12, self->f44);
}

} /* extern "C" */
