// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct S8021263C {
    u32 table;
    u8 pad4[12];
    u32 count;
} S8021263C;
s32 strncmp(const char *a, const char *b, u32 n);

static inline s32 Find8021263C(const S8021263C *p, const char *key) {
    s32 lo;
    u32 table;
    s32 mid;
    u32 count;
    s32 off;
    s32 step;
    s32 r;
    count = p->count;
    lo = 0;
    table = p->table;
    step = count / 4;
    mid = count / 2;
    while ((u32)step > 5) {
        r = strncmp((const char *)(table + mid * 8), key, 8);
        if (r == 0) {
            return mid;
        }
        if (r < 0) {
            if (lo < mid) {
                lo = mid;
            }
            mid += step;
        } else {
            mid -= step;
        }
        step /= 2;
    }
    for (off = lo * 8; lo < (s32)count; lo++, off += 8) {
        r = strncmp((const char *)(table + off), key, 8);
        if (r == 0) {
            return lo;
        }
        if (r > 0) {
            return -1;
        }
    }
    return -1;
}

s32 fn_8021263C(const S8021263C *p, const char *key) {
    if (key[0] == 0) {
        return -1;
    }
    return Find8021263C(p, key);
}

} /* extern "C" */
