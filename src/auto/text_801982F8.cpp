// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { f32 x, y, z; } Vec801982F8;
typedef struct { u8 pad[96]; Vec801982F8 v[9]; u32 pad2; u32 n; } Poly801982F8;
typedef struct { u8 pad[8]; Poly801982F8 poly; } Obj801982F8;
} /* extern "C" */
struct N801982F8 { u8 pad[8]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(Obj801982F8 *o); };
extern "C" {
typedef struct { u8 pad[12]; N801982F8 *front; N801982F8 *back; f32 nx, ny, nz, d; } Node801982F8;
extern volatile f32 lbl_80364C60;

void fn_801982F8(Node801982F8 *nd, Obj801982F8 *o) {
    u32 i = 1;
    const Poly801982F8 *p = &o->poly;
    if (nd->d + (p->v[0].x * nd->nx + p->v[0].y * nd->ny + p->v[0].z * nd->nz) < lbl_80364C60) {
        nd->back->v7(o);
        do {
            const Vec801982F8 *v = &p->v[i]; if (nd->d + (v->x * nd->nx + v->y * nd->ny + v->z * nd->nz) >= lbl_80364C60) {
                nd->front->v7(o);
                return;
            }
            i++;
        } while (i < p->n);
    } else {
        nd->front->v7(o);
        do {
            const Vec801982F8 *v = &p->v[i]; if (nd->d + (v->x * nd->nx + v->y * nd->ny + v->z * nd->nz) < lbl_80364C60) {
                nd->back->v7(o);
                return;
            }
            i++;
        } while (i < p->n);
    }
}

} /* extern "C" */
