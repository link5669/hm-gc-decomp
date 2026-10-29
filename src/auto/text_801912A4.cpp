// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_80364B3C;
extern f32 lbl_80364B40;
typedef struct V3_801912A4 { f32 x, y, z; } V3_801912A4;
typedef struct P_801912A4 { u8 pad[48]; void *f30; } P_801912A4;
void fn_80107244(void *, V3_801912A4 *);
void fn_801077B0(void *, V3_801912A4 *, V3_801912A4 *, V3_801912A4 *, void *);

static inline void GetPos_801912A4(P_801912A4 *p, V3_801912A4 *out) {
    if (p->f30) fn_80107244(p->f30, out);
    else { out->x = lbl_80364B3C; out->y = lbl_80364B3C; out->z = lbl_80364B3C; }
}
void fn_801912A4(P_801912A4 *self, V3_801912A4 *pos) {
    V3_801912A4 c; volatile V3_801912A4 d; volatile V3_801912A4 up;
    f32 z;
    if (self->f30) {
        GetPos_801912A4(self, &c);
        d.x = pos->x - c.x;
        d.y = pos->y - c.y;
        d.z = pos->z - c.z;
        z = *(volatile f32 *)&lbl_80364B3C;
        up.x = z;
        up.y = z;
        up.z = *(volatile f32 *)&lbl_80364B40;
        fn_801077B0(self->f30, (V3_801912A4 *)&d, (V3_801912A4 *)&up, &c, 0);
    }
}

} /* extern "C" */
