// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
char *strcpy(char *, const char *);
int strcmp(const char *, const char *);

typedef struct Ent_80116B64 {
    u32 f0;
    u32 val;
    char name[20];
} Ent_80116B64;

typedef struct Tbl_80116B64 {
    u8 pad0[50];
    s16 count;
    s32 off;
} Tbl_80116B64;

typedef struct Self_80116B64 {
    Tbl_80116B64 *tbl;
} Self_80116B64;
} /* extern "C" */
struct Name_80116B64 { char s[20]; char *c_str() { return s; } };
extern "C" {
static inline u32 GetEnt_80116B64(Tbl_80116B64 *t, s32 idx, char *name) {
    u32 val;
    if (idx < t->count) {
        Ent_80116B64 *e = (Ent_80116B64 *)((u8 *)t + t->off) + idx;
        if (name != 0) strcpy(name, e->name);
        val = e->val;
    }
    return val;
}

s32 fn_80116B64(Self_80116B64 *self, const char *name, u32 *out) {
    Name_80116B64 buf;
    s32 lo = 0;
    s32 hi = self->tbl->count;
    hi--;
    while (lo <= hi) {
        s32 mid = (lo + hi) / 2;
        u32 val = GetEnt_80116B64(self->tbl, mid, buf.s);
        s32 c = strcmp(buf.s, name);
        if (c > 0) hi = mid - 1;
        else if (c < 0) lo = mid + 1;
        else { *out = val; return 0; }
    }
    *out = 0;
    return 19;
}

} /* extern "C" */
