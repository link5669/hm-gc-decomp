/* Functions from 0x800F7138 to 0x800F75B0, found by decomp-toolkit. */
#include "common.h"

typedef struct UnkBlock800F7520 {
    u32 unk0_0 : 6;
    u32 unk0_6 : 1;
    u32 unk0_7 : 1;
    u32 unk0_8 : 24;
    struct UnkBlock800F7520* unk4;
    struct UnkBlock800F7520* unk8;
    struct UnkBlock800F7520* unkC;
} UnkBlock800F7520;

typedef struct UnkHeap800F7520 {
    UnkBlock800F7520* unk0;
    UnkBlock800F7520* unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
} UnkHeap800F7520;


void* fn_800F72D0(UnkHeap800F7520* heap, u32 reqSize) {
    UnkBlock800F7520* head;
    UnkBlock800F7520* blk;
    UnkBlock800F7520* rest;
    UnkBlock800F7520* tmp;
    s32 mask;
    s32 hdr;
    u32 blkSize;
    s32 align;
    u32 size;

    blkSize = 0;
    align = 0;
    mask = (1 << heap->unk18) - 1;
    size = reqSize + mask;
    size &= ~mask;
    hdr = (mask + 8) & ~mask;
    if (heap->unk1C != heap->unk18) {
        s32 align2 = 1 << heap->unk1C;
        s32 mask2 = align2 - 1;
        align = hdr;
        align2 = mask2 + align2;
        align2 += 8;
        align2 -= 1 << heap->unk18;
        hdr = (hdr + align2) & ~mask2;
    }
    size += hdr;
    if (size < 16) {
        size = 16;
    }
    head = heap->unk4;
    for (blk = head; blk != NULL; blk = blk->unk8) {
        blkSize = *(u32*)blk & 0xFFFFFF;
        if (blkSize >= size) {
            break;
        }
    }
    if (blk == NULL) {
        return NULL;
    }
    if (size + 16 < blkSize) {
        rest = (UnkBlock800F7520*)((u8*)blk + size);
        *(u32*)blk = (*(u32*)blk & 0xFF000000) | (size & 0xFFFFFF);
        tmp = (UnkBlock800F7520*)((u8*)blk + blkSize);
        *(u32*)rest = (*(u32*)rest & 0xFF000000) | ((blkSize - size) & 0xFFFFFF);
        rest->unk8 = blk->unk8;
        rest->unkC = blk->unkC;
        if (rest->unk8 != NULL) {
            rest->unk8->unkC = rest;
        }
        if (heap->unk4 == blk) {
            heap->unk4 = rest;
        } else if (rest->unkC != NULL) {
            rest->unkC->unk8 = rest;
        }
        rest->unk4 = blk;
        if ((u8*)tmp < (u8*)heap->unk0 + heap->unk8) {
            tmp->unk4 = rest;
        }
        blkSize = size;
        *(u32*)rest &= ~0x02000000;
        *(u32*)rest &= ~0x01000000;
        *(u32*)rest = (*(u32*)rest & 0x03FFFFFF) | (heap->unk20 << 26);
    } else {
        if (head == blk) {
            heap->unk4 = blk->unk8;
        } else {
            blk->unkC->unk8 = blk->unk8;
        }
        if (blk->unk8 != NULL) {
            blk->unk8->unkC = blk->unkC;
        }
    }
    heap->unkC += blkSize;
    *(u32*)blk = (*(u32*)blk & ~0x02000000) | 0x02000000;
    *(u32*)blk = (*(u32*)blk & 0x03FFFFFF) | (heap->unk20 << 26);
    if (heap->unk1C != heap->unk18) {
        u32 addr = (u32)blk + hdr;
        addr &= ~((1 << heap->unk1C) - 1);
        tmp = (UnkBlock800F7520*)(addr - align);
        *(u32*)tmp = (*(u32*)tmp & ~0x01000000) | 0x01000000;
        *(u32*)tmp = (*(u32*)tmp & 0xFF000000) | (((u8*)tmp - (u8*)blk) & 0xFFFFFF);
        return (u8*)tmp + align;
    }
    return (u8*)blk + hdr;
}

void fn_800F74F4(UnkHeap800F7520* arg0) {
    arg0->unk0 = NULL;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk18 = 2;
    arg0->unk1C = 2;
    arg0->unk20 = 0;
    arg0->unk4 = NULL;
    arg0->unk24 = 0;
}

void fn_800F7520(UnkHeap800F7520* arg0, UnkBlock800F7520* arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0->unk0 = arg1;
    arg0->unk8 = arg2;
    arg0->unk18 = arg4;
    arg0->unk1C = arg4;
    arg0->unk20 = arg3;
    arg0->unk24 = arg3;
    arg0->unkC = 0;
    arg0->unk4 = arg0->unk0;
    *(u32*)arg0->unk4 = (*(u32*)arg0->unk4 & 0xFF000000) | (arg0->unk8 & 0x00FFFFFF);
    *(u32*)arg0->unk4 &= ~0x01000000;
    *(u32*)arg0->unk4 &= ~0x02000000;
    *(u32*)arg0->unk4 = (*(u32*)arg0->unk4 & 0x03FFFFFF) | (arg0->unk20 << 26);
    arg0->unk4->unk4 = 0;
    arg0->unk4->unk8 = 0;
    arg0->unk4->unkC = 0;
}

typedef struct UnkBlock800F7138x {
    u32 unk0_0 : 6;
    u32 unk0_6 : 1;
    u32 unk0_7 : 1;
    u32 unk0_8 : 24;
    struct UnkBlock800F7138x* unk4;
    struct UnkBlock800F7138x* unk8;
    struct UnkBlock800F7138x* unkC;
} UnkBlock800F7138x;

typedef struct UnkHeap800F7138x {
    UnkBlock800F7138x* unk0;
    UnkBlock800F7138x* unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
} UnkHeap800F7138x;
void fn_800F7138(UnkHeap800F7138x* heap, u8* ptr) {
    s32 size;
    u8* end;
    UnkBlock800F7138x* tmp;
    UnkBlock800F7138x* other;
    s32 mask;
    s32 hdr;
    UnkBlock800F7138x* blk;
    mask = (1 << heap->unk18) - 1;
    hdr = mask + 8;
    hdr &= ~mask;
    blk = (UnkBlock800F7138x*)(ptr - hdr);
    if ((*(u32*)blk >> 24) & 1) {
        hdr += *(u32*)blk & 0xFFFFFF;
        blk = (UnkBlock800F7138x*)(ptr - hdr);
    }
    hdr = 0;
    size = *(u32*)blk & 0xFFFFFF;
    *(u32*)blk &= ~0x02000000;
    other = (UnkBlock800F7138x*)((u8*)blk + size);
    heap->unkC -= size;
    end = (u8*)heap->unk0 + heap->unk8;
    if ((u8*)other < end && !((*(u32*)other >> 25) & 1)) {
        size += *(u32*)other & 0xFFFFFF;
        *(u32*)blk = (*(u32*)blk & 0xFF000000) | (size & 0xFFFFFF);
        blk->unk8 = other->unk8;
        blk->unkC = other->unkC;
        if (heap->unk4 == other) {
            heap->unk4 = blk;
        } else if (other->unkC != 0) {
            other->unkC->unk8 = blk;
        }
        if (other->unk8 != 0) {
            other->unk8->unkC = blk;
        }
        tmp = (UnkBlock800F7138x*)((u8*)blk + size);
        if ((u8*)tmp < end) {
            tmp->unk4 = blk;
        }
        hdr = 1;
    }
    other = blk->unk4;
    if (other != 0 && !((*(u32*)other >> 25) & 1)) {
        size += *(u32*)other & 0xFFFFFF;
        *(u32*)other = (*(u32*)other & 0xFF000000) | (size & 0xFFFFFF);
        if (hdr) {
            if (heap->unk4 == blk) {
                heap->unk4 = blk->unk8;
            } else {
                blk->unkC->unk8 = blk->unk8;
            }
            if (blk->unk8 != 0) {
                blk->unk8->unkC = blk->unkC;
            }
        }
        tmp = (UnkBlock800F7138x*)((u8*)other + size);
        if ((u8*)tmp < end) {
            tmp->unk4 = other;
        }
    } else if (!hdr) {
        blk->unk8 = heap->unk4;
        blk->unkC = 0;
        if (heap->unk4 != 0) {
            heap->unk4->unkC = blk;
        }
        heap->unk4 = blk;
    }
}
