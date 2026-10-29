// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_80060568(char *, s32, s32, s32);
extern char lbl_8029C9F8[];
extern char lbl_8029CA30[];
} /* extern "C" */

struct B800F7B04 {
    s32 size;
    B800F7B04 *next;
    B800F7B04 *prev;
};
struct E800F7B04 {
    u8 pad[8];
    void *f8;
    u8 pad2[24];
    u32 f36;
};
struct S800F7B04 {
    u8 pad[8];
    B800F7B04 *f8;
    E800F7B04 arr[16];
    u32 f652;
};

extern "C" {
void fn_800F7520(E800F7B04 *, B800F7B04 *, s32, s32, void *);

E800F7B04 *fn_800F7B04(S800F7B04 *self, s32 size, void *c) {
    s32 idx;
    E800F7B04 *p;
    B800F7B04 *blk;
    B800F7B04 *nb;
    s32 bsize;
    u32 id;
    E800F7B04 *q;
    E800F7B04 *end;

    size += 63;
    size &= ~63;
    idx = 0;
    end = self->arr + 16;
    for (p = self->arr; p < end; p++) {
        if (p->f8 == 0) {
            break;
        }
        idx++;
    }
    if (p >= end) {
        fn_80060568(lbl_8029C9F8, 0, 0, 0);
    }
    for (blk = self->f8; blk != 0 && blk->size < size; blk = blk->next) {
    }
    if (blk == 0) {
        fn_80060568(lbl_8029CA30, 0, 0, 0);
    }
    bsize = blk->size;
    if ((u32)(bsize - size) > 64) {
        nb = (B800F7B04 *)((u8 *)blk + size);
        nb->size = bsize - size;
        nb->next = blk->next;
        if (nb->next != 0) {
            nb->next->prev = nb;
        }
        nb->prev = blk;
        blk->size = size;
        blk->next = nb;
    } else {
        size = bsize;
    }
    if (self->f8 == blk) {
        self->f8 = blk->next;
        if (self->f8 != 0) {
            self->f8->prev = 0;
        }
    } else {
        blk->prev->next = blk->next;
    }
    if (blk->next != 0) {
        blk->next->prev = blk->prev;
    }
    end = self->arr + 16;
    do {
        self->f652++;
        for (q = self->arr; q < end; q++) {
            if (self->f652 == q->f36) {
                break;
            }
        }
    } while (q < end);
    id = self->f652;
    fn_800F7520(p, blk, size, idx, c);
    p->f36 = id;
    return p;
}

} /* extern "C" */
