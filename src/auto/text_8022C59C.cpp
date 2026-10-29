// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern "C" {
typedef struct S8022 { u32 f0; u16 f4; } S8022;
typedef struct G8022 { u8 pad[12]; void *f12; } G8022;
extern G8022 *lbl_8035B65C;
void fn_8019B6B8(void *a, S8022 *s);
} /* extern "C" */
static inline bool inRange(u16 t) { return t >= 1 && t <= 13; }
extern "C" {
void fn_8022C59C(u8 *p) {
    S8022 *s = *(S8022 **)(p + 156);
    if (s != 0 && inRange(s->f4)) {
        if (s->f0 & 0x800) {
            fn_8019B6B8(lbl_8035B65C->f12, s);
            s->f0 &= ~0x800;
        }
        *(u32 *)(p + 180) &= ~2;
    }
}
}

} /* extern "C" */
