// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u32 lbl_803308C8[256];
void fn_801F10F8(u32 *crc, const char *data, u32 len) {
    u32 i;
    for (i = 0; i < len; i++) {
        *crc = (*crc >> 8) ^ lbl_803308C8[(*crc ^ data[i]) & 0xFF];
    }
}

} /* extern "C" */
