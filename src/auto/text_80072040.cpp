// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_803286D0[];
extern f32 lbl_8035F3EC;
extern u32 lbl_8035F3F0;
extern u32 lbl_8035F3E8;
extern u8 *lbl_8035B460;
extern u8 *lbl_8035B65C;
void fn_80190C98(void *);
u8 *fn_800F9398(void *, void *);
void fn_8019B7E8(void *, void *);

typedef void (*VF)(void *, f32 *);

static inline void getpos(u8 *x, f32 *v) {
    u8 *q = *(u8 **)(x + 0x30);
    if (q != NULL) {
        (*(VF *)(lbl_803286D0 + 0x130))(*(void **)(q + 0x10), v);
    } else {
        v[0] = lbl_8035F3EC;
        v[1] = lbl_8035F3EC;
        v[2] = lbl_8035F3EC;
    }
}
static inline void getrot(u8 *x, f32 *v) {
    u8 *q = *(u8 **)(x + 0x30);
    if (q != NULL) {
        (*(VF *)(lbl_803286D0 + 0x12C))(*(void **)(q + 0x10), v);
    }
}
static inline void setpos(u8 *x, f32 *v) {
    u8 *s = *(u8 **)(x + 0x30);
    if (s != NULL) {
        (*(VF *)(lbl_803286D0 + 0xC))(*(void **)(s + 0x10), v);
        *(u32 *)(s + 0x20) |= lbl_8035F3F0;
        fn_80190C98(x);
    }
}
static inline void setrot(u8 *x, f32 *v) {
    u8 *s = *(u8 **)(x + 0x30);
    if (s != NULL) {
        (*(VF *)(lbl_803286D0 + 0x18))(*(void **)(s + 0x10), v);
        *(u32 *)(s + 0x20) |= lbl_8035F3F0;
        fn_80190C98(x);
    }
}

void fn_80072040(u8 *p, void *a) {
    f32 pad[3];
    f32 pos[3];
    f32 rot[4];
    u8 *o;
    u8 *s;
    u8 *x;
    u8 *n;
    getpos(*(u8 **)(p + 0xA0), pos);
    getrot(*(u8 **)(p + 0xA0), rot);
    o = fn_800F9398(*(u8 **)(lbl_8035B460 + 8) + 0x90, a);
    if (o != NULL) {
        getpos(o, pos);
        getrot(o, rot);
    }
    x = *(u8 **)(p + 0x424);
    s = *(u8 **)(x + 0x30);
    if (s != NULL) {
        (*(VF *)(lbl_803286D0 + 0xC))(*(void **)(s + 0x10), pos);
        *(u32 *)(s + 0x20) |= lbl_8035F3F0;
        fn_80190C98(x);
    }
    x = *(u8 **)(p + 0x424);
    s = *(u8 **)(x + 0x30);
    if (s != NULL) {
        (*(VF *)(lbl_803286D0 + 0x18))(*(void **)(s + 0x10), rot);
        *(u32 *)(s + 0x20) |= lbl_8035F3F0;
        fn_80190C98(x);
    }
    n = *(u8 **)(p + 0x424);
    if (!(*(volatile u32 *)n & 0x800)) *(u32 *)n |= lbl_8035F3E8;
    if (*(u32 *)(*(u8 **)(p + 0x424) + 0x48) == 0) fn_8019B7E8(*(void **)(lbl_8035B65C + 0xC), *(u8 **)(p + 0x424));
}

} /* extern "C" */
