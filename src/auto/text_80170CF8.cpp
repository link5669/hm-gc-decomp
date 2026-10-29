// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct E80170CF8 {
    u16 flags;
    u16 f2;
    u8 pad[16];
} E80170CF8;
typedef struct K80170CF8 {
    u16 f0;
    u16 f2;
} K80170CF8;
typedef struct S80170CF8 {
    u8 pad[72];
    E80170CF8 ents[8];
} S80170CF8;

s32 fn_80147A68(E80170CF8 *e, K80170CF8 *k);
s32 fn_80147800(E80170CF8 *e, K80170CF8 *k);
s32 fn_80147570(E80170CF8 *e, K80170CF8 *k);
void fn_801482DC(void *out, E80170CF8 *e);

void fn_80170CF8(S80170CF8 *p, K80170CF8 *k, void *out) {
    u32 i;
    for (i = 0; i < 8; i++) {
        if (fn_80147A68(&p->ents[i], k)) {
            fn_801482DC(out, &p->ents[i]);
            return;
        }
    }
    for (i = 0; i < 8; i++) {
        if (fn_80147800(&p->ents[i], k)) {
            fn_801482DC(out, &p->ents[i]);
            return;
        }
    }
    for (i = 0; i < 8; i++) {
        if (fn_80147570(&p->ents[i], k)) {
            fn_801482DC(out, &p->ents[i]);
            return;
        }
    }
    {
    u16 f2 = k->f2;
    S80170CF8 *q = p;
    u32 j;
    for (j = 0; j < 8; q = (S80170CF8 *)((u8 *)q + 20), j++) {
        if ((q->ents[0].flags & 1) && q->ents[0].f2 >= f2) {
            fn_801482DC(out, &p->ents[j]);
            return;
        }
    }
    }
    for (i = 0; i < 8; i++) {
        if (p->ents[i].flags & 1) {
            fn_801482DC(out, &p->ents[i]);
            return;
        }
    }
    fn_801482DC(out, &p->ents[0]);
}

} /* extern "C" */
