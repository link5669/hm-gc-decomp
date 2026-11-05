// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct RGB80160B9C { u8 r, g, b; };
struct S80160B9C { u16 n; u8 pad[18]; void *f20; u16 *ids; };
extern "C" {
void fn_80147AD8(void *p, u16 id, RGB80160B9C *out);
#pragma optimization_level 1
BOOL fn_80160B9C(const S80160B9C *self, const RGB80160B9C *key, u32 *out) {
    u32 n; u32 b; u32 g; u32 r; u16 *p; u32 i; RGB80160B9C c;
    p = self->ids; r = key->r; i = 0; n = self->n; g = key->g; b = key->b;
    for (; i < n; p++, i++) {
        fn_80147AD8(self->f20, *p, &c);
        if ((c.r == r && c.g == g && c.b == b) ? true : false) {
            *out = i;
            return 1;
        }
    }
    return 0;
}
#pragma optimization_level reset

} /* extern "C" */
