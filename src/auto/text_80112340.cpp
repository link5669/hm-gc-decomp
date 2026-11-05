// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct N112 { u8 pad[480]; struct N112 *next; } N112;
typedef struct { u32 f0; u32 f4; N112 *head; } L112;
void *fn_80110444(N112 *n, void *a, s32 b);
void *fn_80112340(const L112 *l, void *a) {
    N112 *n;
    void *r;
    for (n = l->head; n != 0; n = n->next) {
        r = fn_80110444(n, a, 0);
        if (r != 0) return r;
    }
    return 0;
}

} /* extern "C" */
