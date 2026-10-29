// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct {
    u8 pad0[4];
    u8 f4[32];
    u8 *f36;
    u8 *f40;
    u32 f44;
    u32 f48;
} Dir;

extern char *strcpy(char *d, const char *s);
extern unsigned long strlen(const char *s);
extern char *strchr(const char *s, int c);
extern s32 fn_8021263C(void *tbl, char *name);
extern u8 lbl_802E07C8[];

static inline int my_toupper(int c) {
    return (c == -1) ? -1 : lbl_802E07C8[(u8)c];
}

static inline u32 ReadLE(u8 *p) {
    return p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
}

u8 *fn_80210648(Dir *self, char *path, u32 *outCount, u32 *outX) {
    char buf[272];
    char *p;
    u8 *e;
    u32 count;
    u32 x;
    s32 found = 0;
    char *sep;
    u32 n, i;
    s32 h;
    if (path == 0 || path[0] == 0) {
        *outCount = self->f48;
        *outX = self->f44;
        return self->f40;
    }
    strcpy(buf, path);
    n = strlen(path);
    for (i = 0; i < n; i++) {
        buf[i] = my_toupper(buf[i]);
    }
    e = self->f40;
    p = buf;
    count = self->f48;
    x = self->f44;
    while (strlen(p) != 0) {
        sep = strchr(p, '\\');
        if (sep != 0) *sep = 0;
        h = fn_8021263C(self->f4, p);
        if (h < 0) return 0;
        if (sep == 0) {
            *p = 0;
        } else {
            p = sep + 1;
        }
        found = 0;
        for (i = 0; i < count; i++) {
            u32 w0 = ReadLE(e);
            u32 w1 = ReadLE(e + 4);
            e += 8;
            if ((w0 & 0xFFF) == h) {
                count = (w0 >> 12) & 0x1FF;
                x = w0 >> 21;
                found = 1;
                e = self->f36 + w1;
                break;
            }
        }
    }
    if (found) {
        if (outCount) *outCount = count;
        if (outX) *outX = x;
        return e;
    }
    return 0;
}

} /* extern "C" */
