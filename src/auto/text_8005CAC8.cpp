// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { char d[8]; } Key5CAC8;
typedef struct { f32 x, y, z; } Vec5CAC8;
typedef struct { volatile f32 x, y, z; } VVec5CAC8;
typedef struct { u32 f0; u8 pad4[104]; void *f108; u8 pad112[8]; void *f120; } Obj5CAC8;
typedef struct { u8 pad[12]; Key5CAC8 *f12; } A5CAC8;
typedef struct { u8 pad[12]; Vec5CAC8 *f12; } B5CAC8;
typedef struct {
    u8 pad0[660];
    A5CAC8 *f660;
    u8 pad664[4];
    B5CAC8 *f668;
    f32 *f672;
    void *f676;
    u8 pad680[40];
    Key5CAC8 f720;
    Obj5CAC8 *f728[10];
    s32 f768;
    u8 pad772[8];
    f32 f780;
} P5CAC8;
typedef struct { u8 pad[11340]; u8 *f11340; } G5CAC8;
extern G5CAC8 **lbl_8035B684;
extern u32 lbl_8035E46C;
extern volatile f32 lbl_8035E438;
void fn_80232064(P5CAC8 *, s32, s32, Key5CAC8 *);
void fn_800F6E88(void *, void *);
void *fn_800F9398(void *, void *);
void *fn_800F9788(void *, char *, void *);
void fn_80107F3C(void *, Vec5CAC8 *);
inline void *lookup5CAC8(u8 *tb, Key5CAC8 *k, char *grp) {
    if (grp == 0 || grp[0] == 0) return fn_800F9398(tb + 360, k);
    return fn_800F9788(tb + 384, grp, k);
}
#pragma opt_propagation off
void fn_8005CAC8(P5CAC8 *p0, s32 a, s32 b, Key5CAC8 *c0) {
    u8 *q1;
    s32 i;
    Key5CAC8 *c;
    P5CAC8 *p;
    s32 off;
    s32 j;
    u8 *q2;
    p = p0;
    c = c0;
    fn_80232064(p, a, b, c);
    fn_800F6E88(&p->f720, c);
    for (q1 = (u8 *)p, i = 0, off = 0; i < p->f768; q1 += 4, i++, off += 8) {
        Key5CAC8 k;
        void *x;
        fn_800F6E88(&k, (char *)p->f660->f12 + off);
        x = lookup5CAC8((*lbl_8035B684)->f11340, c, k.d);
        if (((P5CAC8 *)q1)->f728[0]) {
            if (x) ((P5CAC8 *)q1)->f728[0]->f108 = x;
            ((P5CAC8 *)q1)->f728[0]->f0 |= lbl_8035E46C;
        }
    }
    for (q2 = (u8 *)p, j = 0; j < p->f768; q2 += 4, j++) {
        if (((P5CAC8 *)q2)->f728[0]) {
            VVec5CAC8 t;
            Vec5CAC8 *v;
            f32 x;
            f32 y;
            f32 s;
            f32 z;
            v = p->f668->f12;
            z = v->z;
            y = v->y;
            x = v->x;
            t.x = x;
            t.y = y;
            t.z = z;
            if (p->f672 && p->f676) {
                s = *p->f672;
                t.x = x * s;
                t.y = y * s;
                t.z = z * s;
                p->f780 = lbl_8035E438;
            }
            if (((P5CAC8 *)q2)->f728[0]->f120) fn_80107F3C(((P5CAC8 *)q2)->f728[0]->f120, (Vec5CAC8 *)&t);
        }
    }
}
#pragma opt_propagation reset

} /* extern "C" */
