// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { u8 pad[32]; u32 count; } G_AAFAC;
typedef struct { u8 pad[12]; void *f12; } E_AAFAC;
typedef struct {
    void *f0;
    u8 pad4[12];
    G_AAFAC **f16;
    u8 pad20[8];
    E_AAFAC ***f28;
    u8 pad32[12];
    void *f44;
    u8 pad48[4];
    u16 f52;
    u8 pad54[18];
    u16 f72;
    u8 pad74[42];
    s32 f116;
} S_AAFAC;

void *fn_801A5550(G_AAFAC *g, u32 j);
void fn_801CC6CC(void *, void *);
void fn_801CC64C(void *, void *);
void fn_801CC694(void *);
void fn_800F93F8(void *, E_AAFAC *);
void fn_800F6E88(void *, void *);
void fn_801AAAB0(void *, E_AAFAC *);

void fn_801AAFAC(S_AAFAC *self, s32 idx) {
    char buf[16];
    u32 i, j;
    s32 old;
    void *r;
    buf[0] = 0;
    if (self->f116 != -1 && idx != -1) {
        for (i = 0; i < self->f52; i++) {
            for (j = 0; j < self->f16[i]->count; j++) {
                fn_801CC6CC(fn_801A5550(self->f16[i], j), self->f44);
            }
        }
    }
    old = self->f116;
    self->f116 = idx;
    if (self->f116 != -1) {
        for (i = 0; i < self->f72; i++) {
            fn_800F93F8(self->f28[0][i]->f12, self->f28[idx][i]);
        }
        if (old != -1) {
            for (i = 0; i < self->f52; i++) {
                for (j = 0; j < self->f16[i]->count; j++) {
                    r = fn_801A5550(self->f16[i], j);
                    fn_801CC64C(r, self->f44);
                    fn_801CC694(r);
                }
            }
        }
    } else {
        for (i = 0; i < self->f72; i++) {
            buf[0] = 0;
            if (self->f28[old][i]->f12) fn_800F6E88(buf, self->f28[old][i]->f12);
            fn_801AAAB0(self->f0, self->f28[old][i]);
        }
    }
}

} /* extern "C" */
