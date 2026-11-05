// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct O800FA474 { u32 f0; u32 f4; u32 f8; virtual char v0(u32) const; };
extern "C" {
void fn_800FA474(const O800FA474 *p, char *buf, u32 size) {
    char *d;
    u32 i;
    u32 len;
    u32 n;
    len = p->f8 - p->f4;
    n = len;
    if (size <= len) n = size - 1;
    d = buf;
    for (i = 0; i < n; i++) buf[i] = p->v0(i);
    buf[i] = 0;
}

} /* extern "C" */
