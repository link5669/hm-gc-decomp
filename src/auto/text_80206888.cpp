// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct Rng8 { u8 pad[8]; s32 max1; s32 min1; s32 step1; s32 max2; s32 min2; s32 step2; u8 pad2[92 - 32]; u32 flags; } Rng8;
typedef struct Tgt8 { u8 pad[32]; s32 active; u8 pad36[44 - 36]; f32 f44; u8 pad48[124 - 48]; u32 f124; } Tgt8;
typedef struct Self8 { u8 pad[8]; Rng8 *rng; s32 done; Tgt8 *tgt; void *f20; } Self8;
s32 fn_80201714(s32);
f32 fn_801FC18C(f32);
void fn_800C9A0C(void *, s32);
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);

void fn_80206888(Self8 *self) {
    s32 v;
    s32 lvl;
    self->done = 0;
    fn_800C9A0C(self->f20, 1);
    if (self->done == 0) {
        if (self->tgt->active != 0) {
            if (self->rng->flags & 1) {
                v = fn_80201714((self->rng->max1 - self->rng->min1) / self->rng->step1 + 1); v *= self->rng->step1; v += self->rng->min1; self->tgt->f44 = fn_801FC18C((f32)v);
            }
            if (self->rng->flags & 2) {
                v = fn_80201714((self->rng->max2 - self->rng->min2) / self->rng->step2 + 1); v *= self->rng->step2; v += self->rng->min2;
                lvl = OSDisableInterrupts();
                self->tgt->f124 = v << 16;
                OSRestoreInterrupts(lvl);
            }
        }
        self->done = 1;
    }
}

} /* extern "C" */
