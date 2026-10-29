// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
u32 strlen(const char *);
char *strncpy(char *, const char *, u32);

void fn_80207EC8(char *dst, const char *src) {
    strlen(src);
    strncpy(dst, src, 128);
    dst[127] = 0;
    if (dst[strlen(dst) - 1] != '\\') {
        dst[strlen(dst)] = '\\';
        dst[strlen(dst) + 1] = 0;
    }
}

} /* extern "C" */
