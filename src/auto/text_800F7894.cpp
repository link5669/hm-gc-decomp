// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct FreeBlk {
    u32 size;
    struct FreeBlk *next;
    struct FreeBlk *prev;
} FreeBlk;

typedef struct SubHeap {
    FreeBlk *base;
    u32 unk4;
    u32 size;
    u32 unkC;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u32 id;
} SubHeap;

typedef struct HeapMgr {
    u8 *base;
    u32 size;
    FreeBlk *freeList;
    SubHeap heaps[16];
    u32 counter;
} HeapMgr;

void fn_800F74F4(SubHeap *h);

void fn_800F7894(HeapMgr *m, SubHeap *h) {
    FreeBlk *blk;
    u8 *base;
    FreeBlk *cur;
    FreeBlk *prev;
    u32 size;
    SubHeap *end;
    SubHeap *e;

    end = m->heaps + 16;
    do {
        m->counter++;
        for (e = m->heaps; e < end; e++) {
            if (m->counter == e->id) break;
        }
    } while (e < end);
    h->id = m->counter;
    blk = h->base;
    base = m->base;
    if ((u8 *)blk >= base && (u8 *)blk < base + m->size) {
        size = h->size;
        prev = 0;
        cur = m->freeList;
        while (cur != 0 && blk > cur) {
            prev = cur;
            cur = cur->next;
        }
        blk->size = size;
        blk->next = cur;
        blk->prev = prev;
        if (prev == 0) {
            m->freeList = blk;
        } else {
            prev->next = blk;
        }
        if (cur != 0) {
            if ((FreeBlk *)((u8 *)blk + size) == cur) {
                blk->next = cur->next;
                blk->size += cur->size;
                if (cur->next != 0) {
                    cur->next->prev = blk;
                }
            } else {
                cur->prev = blk;
            }
        }
        if (prev != 0) {
            if ((FreeBlk *)((u8 *)prev + prev->size) == blk) {
                prev->next = blk->next;
                prev->size += blk->size;
                if (blk->next != 0) {
                    blk->next->prev = prev;
                }
            }
        }
    }
    fn_800F74F4(h);
}

} /* extern "C" */
