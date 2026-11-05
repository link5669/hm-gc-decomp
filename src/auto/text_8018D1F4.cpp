// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct I8018D1F4 { u8 pad[16]; s32 f16; s32 f20; };
struct E8018D1F4 {
    u32 f0;
    f32 f4;
    u8 pad8[8];
    I8018D1F4 *f16;
    u32 f20;
    s32 f24;
    s32 f28;
};
struct B8018D1F4 { u32 a, b; };
struct P8018D1F4 {
    u8 pad[152];
    B8018D1F4 *f152;
    u32 f156;
    E8018D1F4 *f160;
    u32 f164;
};
void fn_801A0A1C(P8018D1F4 *p, f32 t);
void fn_80107018(E8018D1F4 *p, f32 dt, s32 lo, s32 hi);
u32 fn_8013FCD0(I8018D1F4 *a, f32 f, B8018D1F4 *buf, s32 max, s32 c, s32 d);

static inline s32 lo8018D1F4(I8018D1F4 *a) { return a->f16; }
static inline s32 hi8018D1F4(I8018D1F4 *a) { return a->f20; }

void fn_8018D1F4(P8018D1F4 *p, f32 f) {
    B8018D1F4 *ptr;
    u32 i;
    E8018D1F4 *e;
    u32 r;
    fn_801A0A1C(p, f);
    if (p->f164 != 0) {
        for (i = 0; i < p->f164; i++) {
            e = &p->f160[i];
            if (e->f20 & 1) fn_80107018(e, f, lo8018D1F4(e->f16), hi8018D1F4(e->f16));
        }
        p->f156 = 0;
        ptr = p->f152;
        for (i = 0; i < p->f164; i++) {
            e = &p->f160[i];
            if (e->f20 & 1) {
                r = fn_8013FCD0(e->f16, e->f4, ptr, 4 - p->f156, e->f24, e->f28);
                if (r != 0) {
                    ptr += r;
                    p->f156 += r;
                }
            }
        }
    }
}

} /* extern "C" */
