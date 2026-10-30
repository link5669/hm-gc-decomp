// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct H {
    u32 a0, a4;
    f32 f8, f12, f16;
    u16 a20;
    u8 pad22[2];
    u32 a24, a28, a32, a36, a40;
    u8 b44, b45, b46, b47, b48, b49;
    u8 pad50[14];
    s32 o64, o68, o72, o76, o80, o84, o88;
    u32 a92;
};
struct M {
    u32 a0, a4, n8;
    u8 pad12[4];
    u32 fl;
    u8 pad20[4];
    u8 t24, t25, t26, t27;
    u8 pad28[16];
    f32 f44, f48, f52;
    u8 pad56[8];
    u16 a64;
    u8 pad66[2];
    u32 p68, p72, p76, p80, p84, p88, p92, a96, a100;
};
void fn_8014C830(u32 *, u32, u32, u32, u8, u8, u8, u8, u32, u32, u8 *);
s32 fn_80101A7C(u8);
void fn_800B48F4(u32, u32);
void fn_800D5F10(void);

void fn_80175FA0(M *m, H **pp, u32 *base) {
    H *h = *pp;
    m->a0 = h->a0;
    m->a4 = 0;
    m->n8 = h->a4;
    fn_8014C830(&m->fl, h->a32, h->a36, h->a40, h->b44, h->b46, h->b45, h->b47, h->b48, h->b49, (u8 *)h + 53);
    m->f44 = h->f8;
    m->f48 = h->f12;
    m->f52 = h->f16;
    m->a64 = h->a20;
    m->a96 = h->a24;
    m->a100 = h->a28;
    *(u8 **)pp += 96;
    *base = (*base + 31) & ~31;
    if (h->o64 >= 0) m->p76 = *base + h->o64;
    if (h->o68 >= 0) m->p84 = *base + h->o68;
    if (h->o72 >= 0) m->p88 = *base + h->o72;
    if (h->o76 >= 0) m->p92 = *base + h->o76;
    if (h->o80 >= 0) m->p80 = *base + h->o80;
    if (h->o84 >= 0) m->p68 = *base + h->o84;
    if (h->o88 >= 0) m->p72 = *base + h->o88;
    *base = *base + h->a92;
    if (m->fl & 0x40) {
        s32 k = fn_80101A7C(m->t24);
        fn_800B48F4(m->p76, m->n8 * (k * 2));
    } else if (m->fl & 0x80) {
        s32 k = fn_80101A7C(m->t24);
        fn_800B48F4(m->p76, m->n8 * (k * 3));
    } else if (m->fl & 0x100) {
        s32 k = fn_80101A7C(m->t24);
        fn_800B48F4(m->p76, m->n8 * (k * 4));
    }
    if (m->fl & 0x800) {
        s32 k = fn_80101A7C(m->t27);
        fn_800B48F4(m->p88, m->n8 * (k * 3));
    }
    if (m->fl & 0x2000) fn_800B48F4(m->p68, m->n8 * 4);
    if (m->fl & 0x4000) fn_800B48F4(m->p72, m->n8 * 4);
    if (m->fl & 0x8000) fn_800B48F4(m->p92, m->a100 * m->n8);
    fn_800D5F10();
}

} /* extern "C" */
