// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern unsigned char lbl_802E07C8[256];
char *strcpy(char *dst, const char *src);
char *strrchr(const char *s, int c);
char *strchr(const char *s, int c);
u32 strlen(const char *s);
s32 fn_80212548(u8 *p, char *ext);
s32 fn_8021263C(u8 *p, char *name);
u8 *fn_8021B0C8(u8 *self, char *dir, u32 *start, u32 *count);

static inline int tolower_8021AEE8(int c) {
    return (c == -1) ? -1 : (int)lbl_802E07C8[(unsigned char)c];
}

s32 fn_8021AEE8(u8 *self, const char *path, u32 *out) {
    char buf[280];
    u32 start;
    u32 count;
    char *name;
    char *dir;
    char *p;
    s32 id;
    s32 ext;
    u32 len;
    u32 i;
    u8 *e;

    strcpy(buf, path);
    p = strrchr(buf, '\\');
    if (p != 0) {
        *p = 0;
        name = p + 1;
        dir = buf;
    } else {
        name = buf;
        dir = 0;
    }
    if (name == 0) {
        return -1;
    }
    len = strlen(name);
    for (i = 0; i < len; i++) {
        name[i] = tolower_8021AEE8(name[i]);
    }
    p = strchr(name, '.');
    if (p != 0) {
        *p = 0;
        ext = fn_80212548(self + 4, p + 1);
    } else {
        ext = 0;
    }
    id = fn_8021263C(self + 4, name);
    if (id < 0 || ext < 0) {
        return -1;
    }
    e = fn_8021B0C8(self, dir, &start, &count);
    if (e == 0) {
        return -1;
    }
    e += start * 8;
    for (i = 0; i < count; i++) {
        u32 eid = e[0] + (e[1] << 8);
        u32 off = e[4] + (e[5] << 8) + (e[6] << 16) + (e[7] << 24);
        u32 eext = e[2];
        u32 size = e[8] + (e[9] << 8) + (e[10] << 16) + (e[11] << 24);
        e += 12;
        if (eid == id && eext == ext) {
            *out = size;
            return off;
        }
    }
    return -1;
}

} /* extern "C" */
