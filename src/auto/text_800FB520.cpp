// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void *memmove(void *, const void *, u32);
struct WStr { s32 cap; s32 start; s32 len; void *vt; u16 *buf; };

s32 fn_800FB520(WStr *s, u16 c, s32 idx) {
    memmove(s->buf + s->start + idx + 1, s->buf + s->start + idx, (s->len - s->start - idx + 1) * 2);
    s->buf[s->start + idx] = c;
    return s->len++;
}

} /* extern "C" */
