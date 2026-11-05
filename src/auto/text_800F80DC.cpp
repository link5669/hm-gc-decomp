// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct HEnt {
    u8 key[8];
    u32 value;
} HEnt;

typedef struct HTab {
    HEnt *entries;
    u32 size;
} HTab;

s32 fn_800F6CD0(HEnt *e, const char *key);

static inline u32 hashkey(const char *key) {
    u32 hash;
    s32 i;
    u32 shift;
    hash = key[0];
    shift = 7;
    for (i = 1; i < 8; i++) {
        if (key[i] == 0) {
            break;
        }
        hash += key[i] << shift;
        shift = (shift + 7) & 31;
    }
    return hash;
}
#pragma opt_propagation off
u32 fn_800F80DC(HTab *tbl, const char *key, u32 *outIdx) {
    HEnt *entries; u32 size; u32 start; u32 off; u32 idx; u32 hash;
    hash = hashkey(key);
    size = tbl->size;
    start = hash % size;
    idx = start;
    goto top;
next:
    { u32 o8 = off + 8; if (*(u32 *)((u8 *)entries + o8) == 0) return 0; }
    if (++idx >= size) idx = 0;
    if (idx == start) return 0;
    goto cmp;
top:
    entries = tbl->entries;
cmp:
    off = idx * 12;
    if (!fn_800F6CD0((HEnt *)((u8 *)entries + off), key)) goto next;
    if (outIdx != 0) *outIdx = idx;
    return *(u32 *)((u8 *)&tbl->entries->value + off);
}
#pragma opt_propagation reset

} /* extern "C" */
