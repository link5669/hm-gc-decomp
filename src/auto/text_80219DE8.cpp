// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
#include <stdarg.h>
typedef struct { u8 pad[4]; s32 f4; s32 f8; s32 f12; s32 f16; } S80219DE8;
s32 fn_800C26AC(void);
void fn_800E90C4(char *, s32, const char *, va_list);
void fn_80219560(S80219DE8 *, char *);

void fn_80219DE8(S80219DE8 *p, s32 a, s32 b, const char *fmt, ...) {
    va_list va;
    char buf[256];
    b += (fn_800C26AC() == 0);
    p->f4 = a;
    p->f8 = b;
    p->f12 = 0;
    p->f16 = 0;
    va_start(va, fmt);
    fn_800E90C4(buf, 256, fmt, va);
    fn_80219560(p, buf);
}

} /* extern "C" */
