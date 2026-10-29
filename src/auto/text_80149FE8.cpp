// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern const char lbl_80364440[8];
extern const char lbl_8036444C[5];
extern char lbl_802A0030[], lbl_802A0040[], lbl_802A0054[], lbl_802A007C[], lbl_802A0094[], lbl_802A00B8[], lbl_802A00D8[];
int fn_802108B4(u8 *, u8 *, int, u32 *);
void fn_801485B4(u8 *, int);
int strncmp(const char *, const char *, u32);
void fn_801486B4(u8 *, char *);
void fn_80148210(u8 *, u32, u32, u32, u32);
void fn_8014824C(u8 *, u32, u32, u32, u32);
void fn_80148288(u8 *, u32, u32, u32, u32, u32, u32);
#define BE32(b) ((b)[3] + ((b)[2] << 8) + ((b)[1] << 16) + ((b)[0] << 24))

// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"
extern "C" {

#define BE32(b) ((b)[3] + ((b)[2] << 8) + ((b)[1] << 16) + ((b)[0] << 24))
void fn_80149FE8(u8 *p) {
    u8 *b;
    u32 len;
    u8 buf[33];
    int r;
    u8 c;
    r = fn_802108B4(p + 48, buf, 33, &len);
    if (r) fn_801485B4(p, r);
    b = buf;
    if (strncmp(lbl_80364440, (char *)b, 8)) fn_801486B4(p, lbl_802A0030);
    if ((u32)BE32(b + 8) != 13) fn_801486B4(p, lbl_802A0040);
    if (strncmp(lbl_8036444C, (char *)b + 12, 4)) fn_801486B4(p, lbl_802A0040);
    *(u32 *)(p + 16) = BE32(b + 16);
    *(u32 *)(p + 20) = BE32(b + 20);
    p[1358] = b[24];
    p[1356] = b[25];
    switch (p[1356]) {
    case 0: p[1357] = p[1358]; break;
    case 2: p[1357] = p[1358] * 3; break;
    case 3: fn_801486B4(p, lbl_802A0054); break;
    case 4: p[1357] = p[1358] * 2; break;
    case 6: p[1357] = p[1358] * 4; break;
    default: fn_801486B4(p, lbl_802A007C); break;
    }
    c = p[1356];
    if (!(c & 2)) {
        if (c & 4) fn_80148210(p + 28, p[1357], 0xFF00, 255, 0);
        else fn_80148210(p + 28, p[1357], 255, 0, 0);
    } else if (c & 1) {
        fn_8014824C(p + 28, p[1357], 255, 0, 0);
    } else if (c & 4) {
        fn_80148288(p + 28, p[1357], 0xFF00, 0xFF0000, 0xFF000000, 255, 0);
    } else {
        fn_80148288(p + 28, p[1357], 0xFF0000, 0xFF00, 255, 0, 0);
    }
    *(u32 *)(p + 24) = (*(u32 *)(p + 16) * p[1357] + 7) >> 3;
    p[1359] = b[26];
    if (p[1359]) fn_801486B4(p, lbl_802A0094);
    p[1360] = b[27];
    if (p[1360]) fn_801486B4(p, lbl_802A00B8);
    p[1361] = b[28];
    if (p[1361]) fn_801486B4(p, lbl_802A00D8);
    *(u32 *)(p + 1344) = *(u32 *)(*(u8 **)(p + 52) + 4) - 33;
    *(u32 *)(p + 1352) = 33;
}

}

} /* extern "C" */
