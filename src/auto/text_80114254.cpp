// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void *memmove(void *, const void *, u32);
} /* extern "C" */
struct H80114254 { u8 pad[16]; u32 len; };
struct B80114254 { H80114254 *h; u32 f4; virtual void p0(); virtual void p1(); virtual void p2(); virtual void m(int); };
struct S80114254 : B80114254 { u8 *data; };
extern "C" {
void fn_80114254(S80114254 *s, s32 idx) {
    u32 n = idx + 1;
    if (n < s->h->len) {
        memmove(s->data + idx, &s->data[idx + 1], s->h->len - (idx + 1));
    }
    s->m(s->h->len - 1);
}

} /* extern "C" */
