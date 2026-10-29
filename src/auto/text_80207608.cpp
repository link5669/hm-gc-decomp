// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u32 lbl_8034E908[];

void fn_80207608(u32 key) {
    u32 n = lbl_8034E908[2];
    u32 m = lbl_8034E908[3];
    u32 i, j, k;
    for (i = 0; i < n; i++) {
        if (key == lbl_8034E908[4 + i]) {
            lbl_8034E908[0x1004 + m] = lbl_8034E908[4 + i];
            lbl_8034E908[0x1805 + m] = lbl_8034E908[0x804 + i];
            lbl_8034E908[3]++;
            for (j = 0; j < lbl_8034E908[3]; j++) {
                for (k = 0; k < lbl_8034E908[3]; k++) {
                    u32 a;
                    if (j == k) continue;
                    a = lbl_8034E908[0x1004 + j] + lbl_8034E908[0x1805 + j];
                    if (a == lbl_8034E908[0x1004 + k]) {
                        lbl_8034E908[0x1805 + j] = lbl_8034E908[0x1805 + j] + lbl_8034E908[0x1805 + k];
                        lbl_8034E908[0x1004 + k] = lbl_8034E908[0x1003 + lbl_8034E908[3]];
                        lbl_8034E908[0x1805 + k] = lbl_8034E908[0x1804 + lbl_8034E908[3]];
                        lbl_8034E908[3]--;
                        break;
                    }
                    a = lbl_8034E908[0x1004 + k] + lbl_8034E908[0x1805 + k];
                    if (a == lbl_8034E908[0x1004 + j]) {
                        lbl_8034E908[0x1805 + k] += lbl_8034E908[0x1805 + j];
                        lbl_8034E908[0x1004 + j] = lbl_8034E908[0x1003 + lbl_8034E908[3]];
                        lbl_8034E908[0x1805 + j] = lbl_8034E908[0x1804 + lbl_8034E908[3]];
                        lbl_8034E908[3]--;
                        break;
                    }
                }
            }
            lbl_8034E908[4 + i] = lbl_8034E908[3 + n];
            lbl_8034E908[0x804 + i] = lbl_8034E908[0x803 + n];
            lbl_8034E908[2]--;
            return;
        }
    }
}

} /* extern "C" */
