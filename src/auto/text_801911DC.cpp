// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct V801911DC {
    f32 x, y, z;
} V801911DC;
extern f32 lbl_80364B3C;
extern f32 lbl_80364B40;
void fn_80107244(void *, V801911DC *);
void fn_801077B0(void *, V801911DC *, V801911DC *, V801911DC *, s32);

struct S801911DC {
    u8 pad[48];
    void *f48;
};

void fn_801911DC(S801911DC *p, void *q) {
    V801911DC posB;
    V801911DC posA;
    V801911DC diff;
    V801911DC up;
    if (p->f48 == 0) {
        return;
    }
    if (p->f48) {
        fn_80107244(p->f48, &posB);
    } else {
        posB.x = lbl_80364B3C;
        posB.y = lbl_80364B3C;
        posB.z = lbl_80364B3C;
    }
    fn_80107244(q, &posA);
    {
        volatile V801911DC *d = &diff;
        volatile V801911DC *u = &up;
        f32 z;
        d->x = posA.x - posB.x;
        d->y = posA.y - posB.y;
        d->z = posA.z - posB.z;
        z = *(volatile f32 *)&lbl_80364B3C;
        u->x = z;
        u->y = z;
        u->z = *(volatile f32 *)&lbl_80364B40;
    }
    fn_801077B0(p->f48, &diff, &up, &posB, 0);
}

} /* extern "C" */
