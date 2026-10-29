// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Pal_8014BC1C { u8 r; u8 g; u8 b; u8 a; };
struct S_8014BC1C {
    u8 pad0[56];
    u32 n;
    Pal_8014BC1C pal[256];
    u8 pad1[277];
    u8 bits;
    u8 fmt;
    u8 pad2;
    u32 start;
};
extern "C" {
void fn_8014BC1C(S_8014BC1C *self, const u8 *src) {
    u32 rem;
    u32 amask;
    u32 i;
    u32 m3;
    u32 per;
    u32 lo;
    s32 bytes;
    const u16 * s16;
    u8 bits;
    u32 m;
    u32 m2;
    lo = self->fmt & 0xF;
    bits = self->bits;
    rem = bits - lo;
    bytes = (bits + 7) >> 3;
    per = rem / 3;
    amask = ((1 << lo) - 1) << rem;
    m = (1 << per) - 1;
    m2 = m << per;
    m3 = m2 << per;
    switch (bytes) {
    case 1:
        for (i = self->start; i < self->n; src++, i++) {
            self->pal[i].b = *src & m;
            self->pal[i].g = *src & m2;
            self->pal[i].r = *src & m3;
            self->pal[i].a = *src & amask;
        }
        break;
    case 2:
        s16 = (const u16 *)src;
        for (i = self->start; i < self->n; s16++, i++) {
            self->pal[i].b = *s16 & m;
            self->pal[i].g = *s16 & m2;
            self->pal[i].r = *s16 & m3;
            self->pal[i].a = *s16 & amask;
        }
        break;
    case 3:
        for (i = self->start; i < self->n; i++) {
            self->pal[i].b = src[0];
            self->pal[i].g = src[1];
            self->pal[i].r = src[2];
            self->pal[i].a = 0;
            src += 3;
        }
        break;
    case 4:
        for (i = self->start; i < self->n; i++) {
            self->pal[i].b = src[0];
            self->pal[i].g = src[1];
            self->pal[i].r = src[2];
            self->pal[i].a = src[3];
            src += 4;
        }
        break;
    }
}

} /* extern "C" */
