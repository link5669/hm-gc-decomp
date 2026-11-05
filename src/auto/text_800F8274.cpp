// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.5 */
typedef struct { char name[8]; void *value; } E800F8274;
typedef struct { E800F8274 *entries; u32 count; } T800F8274;
s32 fn_800F6CD0(E800F8274 *e, const char *key);
static inline u32 hash_800F8274(const char *key) {
    u32 h, shift;
    s32 k;
    h = key[0];
    shift = 7;
    for (k = 1; k < 8; k++) {
        if (key[k] == 0) break;
        h += key[k] << shift;
        shift = (shift + 7) & 31;
    }
    return h;
}
void *fn_800F8274(const T800F8274 *t, const char *key) {
    s32 start;
    u32 i;
    if (t->count == 0) return 0;
    start = hash_800F8274(key) % t->count;
    i = start;
    while (!fn_800F6CD0(&t->entries[i], key)) {
        if (t->entries[i].value == 0) return 0;
        i++;
        if (i >= t->count) i = 0;
        if (i == start) return 0;
    }
    return t->entries[i].value;
}

} /* extern "C" */
