// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct S800F9398 { u8 pad[8]; struct S800F9398 *f8; };
void *fn_800F8274(const S800F9398 *, void *);
void *fn_800F9398(const S800F9398 *p, void *key) {
    const S800F9398 *n;
    for (n = p->f8; n != 0; n = n->f8) {
        void *r = fn_800F8274(n, key);
        if (r != 0) return r;
    }
    return 0;
}

} /* extern "C" */
