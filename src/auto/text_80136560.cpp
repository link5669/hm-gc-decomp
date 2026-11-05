/* Functions from 0x80136560 to 0x80136640, found by decomp-toolkit. */
#include "common.h"

extern "C" {

typedef struct Entry20 {
    u8 pad0[8];
    u32 flags;
    u8 padC[2];
    u16 id;
    u8 pad10[0x10];
} Entry20;

typedef struct Entry10 {
    u8 pad0[8];
    u32 flags;
    u8 padC[2];
    u16 id;
} Entry10;

typedef struct Group94 {
    u32 unk0;
    u32 count;
    Entry10 entries[8];
    u8 pad88[0xC];
} Group94;

typedef struct List20 {
    u32 unk0;
    Entry20 entries[1];
} List20;

typedef struct IdList {
    u32 groupCount;
    Group94* groups;
    u32 entryCount;
    List20* list;
    u32 ids[8];
    s32 numIds;
} IdList;

void fn_80136560(IdList* p) {
    u32 i;
    p->numIds = 0;
    for (i = 0; i < p->entryCount; i++) {
        Entry20* e = &p->list->entries[i];
        if (e->flags & 0x1C00) {
            p->ids[p->numIds++] = e->id;
        }
    }
}

/* QV=2.0p1 */

typedef struct E20_365BC {
    u8 pad0[8];
    u32 flags;
    u8 padC[2];
    u16 id;
    u8 pad10[0x10];
} E20_365BC;

typedef struct E10_365BC {
    u8 pad0[8];
    u32 flags;
    u8 padC[2];
    u16 id;
} E10_365BC;

typedef struct G94_365BC {
    u32 unk0;
    u32 count;
    E10_365BC entries[8];
    u8 pad88[0xC];
} G94_365BC;

typedef struct L20_365BC {
    u32 unk0;
    E20_365BC entries[1];
} L20_365BC;

typedef struct IdL_365BC {
    u32 groupCount;
    G94_365BC* groups;
    u32 entryCount;
    L20_365BC* list;
    u32 ids[8];
    s32 numIds;
} IdL_365BC;


static inline void add_365BC(IdL_365BC *p, E10_365BC *e) {
    if (e->flags & 0x1C00) {
        p->ids[p->numIds++] = e->id;
    }
}
void fn_801365BC(IdL_365BC* p) {
    u32 i;
    u32 j;
    p->numIds = 0;
    for (i = 0; i < p->groupCount; i++) {
        for (j = 0; j < p->groups[i].count; j++) {
            add_365BC(p, &p->groups[i].entries[j]);
        }
    }
}

} /* extern "C" */
