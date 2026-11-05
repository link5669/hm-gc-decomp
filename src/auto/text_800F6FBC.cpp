/* Functions from 0x800F6FBC to 0x800F710C, found by decomp-toolkit. */
#include "common.h"

extern "C" {

extern u8 lbl_802E05C8[];
extern u8 lbl_802E06C8[];
extern u8 lbl_802E07C8[];


/* QV=2.0p1 */
void fn_800F6FBC(const char *src, char *dst) {
    int i;
    dst[0] = 0;
    for (i = 0; i < 8; i++) {
        dst[i] = src[i];
        if (src[i] == 0) return;
    }
}
void fn_800F7044(char *s) {
    int c;
    u32 i;
    for (i = 0; i < 8 && *s > 0; i++, s++) {
        c = *s;
        if (lbl_802E05C8[(u8)c] & 0x80) {
            *s = (c == -1) ? -1 : lbl_802E06C8[(u8)c];
        }
    }
}

void fn_800F70A8(char *s) {
    int c;
    u32 i;
    for (i = 0; i < 8 && *s > 0; i++, s++) {
        c = *s;
        if (lbl_802E05C8[(u8)c] & 0x40) {
            *s = (c == -1) ? -1 : lbl_802E07C8[(u8)c];
        }
    }
}

} /* extern "C" */
