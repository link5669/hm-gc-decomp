// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern s32 fn_80116B10(void *ctx, u32 h, u32 **out);
extern void fn_80116A70(u32 *s, void *len);
extern void fn_80116B58(void *ctx, s32 err);

static inline void Unpack(s32 *d, u32 *s) {
    s32 n;
    s32 i;
    if (*s > 255) {
        fn_80116A70(s, &n);
        d[n] = 0;
        for (i = n - 1; i >= 0; i--) {
            d[i] = (u8)(*(s32 *)((u8 *)s + (i & ~3)) >> ((3 - (i & 3)) * 8));
        }
    } else {
        s32 *ss = (s32 *)s;
        s32 v;
        do {
            v = *ss++;
            *d++ = v;
        } while (v != 0);
    }
}

static inline s32 Check(void *ctx, s32 err) {
    if (err) fn_80116B58(ctx, err);
    return err;
}

#pragma opt_propagation off
s32 fn_80114A5C(void *a, void *ctx, u32 *q) {
    u32 *dst;
    u32 *src;
    u32 len;
    u32 *tmp;
    u32 sz;
    fn_80116B10(ctx, q[2], &src);
    fn_80116A70(src, &len);
    sz = len + 1;
    if (Check(ctx, fn_80116B10(ctx, q[1] + sz, &tmp))) return 0;
    fn_80116B10(ctx, q[2], &dst);
    Unpack((s32 *)dst, src);
    return len;
}

#pragma opt_propagation reset

} /* extern "C" */
