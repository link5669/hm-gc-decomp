// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern "C" {
typedef struct E8019 { u32 f0; u8 pad[60]; } E8019;
typedef struct N8019 { u8 pad[108]; E8019 *f108; u8 pad2[36]; struct N8019 *f148; } N8019;
typedef struct X8019 { u8 pad[548]; u8 f548[60]; N8019 *f608; } X8019;
typedef struct A8019 { u32 f0; X8019 *f4; E8019 *f8; u8 pad[12]; s32 f24; } A8019;
typedef struct B8019 { u32 f0; u32 f4; E8019 *f8; } B8019;
extern u32 lbl_80364BF8;
void fn_800FCF74(void *);
void fn_80195A10(A8019 *a, B8019 *b) {
    X8019 *x = a->f4;
    u8 *y = x->f548;
    N8019 *n = x->f608;
    for (; n != 0; n = n->f148) {
        E8019 *e = n->f108;
        if (e->f0 & 4) {
            s32 i = e - b->f8;
            E8019 *arr = a->f8;
            if ((arr[i].f0 & 0xF) == 0) {
                a->f24--;
            }
            arr[i].f0 |= lbl_80364BF8;
        }
    }
    fn_800FCF74(y);
}
}

} /* extern "C" */
