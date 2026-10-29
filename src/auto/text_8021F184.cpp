// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { f32 x, y, z; } V3_8021F184;
typedef struct { V3_8021F184 *v[3]; } Tri_8021F184;
extern f32 lbl_803659A4;
extern f32 lbl_803659A8;
#pragma opt_propagation off
s32 fn_8021F184(Tri_8021F184 *t, V3_8021F184 *p) {
    f32 T1, s, P4, T2, sZ, av, P3, d1, sY, P2, d2, k3, P1, pz, pv, py, pu, ay, au, az, bv, by, bu, bz, ccv, cy, ccu, cz, n1x, mu, mv, n2x, n1y, n2y, n3x, n3y, d3;
    ay = t->v[0]->y;
    az = t->v[0]->z;
    by = t->v[1]->y;
    bz = t->v[1]->z;
    cy = t->v[2]->y;
    cz = t->v[2]->z;
    k3 = lbl_803659A4;
    T1 = ay + by;
    sY = cy + T1;
    mu = k3 * sY;
    T2 = az + bz;
    sZ = cz + T2;
    mv = k3 * sZ;
    s = lbl_803659A8;
    ay = ay - mu;
    az = az - mv;
    by = by - mu;
    bz = bz - mv;
    cy = cy - mu;
    cz = cz - mv;
    au = s * ay;
    av = s * az;
    bu = s * by;
    bv = s * bz;
    ccu = s * cy;
    ccv = s * cz;
    py = p->y;
    pz = p->z;
    pu = py - mu;
    pv = pz - mv;
    n1x = ccv - av;
    n1y = au - ccu;
    n2x = av - bv;
    n2y = bu - au;
    P1 = n1y * ccv;
    d1 = n1x * ccu + P1;
    P2 = n2y * av;
    d2 = n2x * au + P2;
    P3 = n1y * n2x;
    P4 = n1x * n2y;
    if (P3 < P4) {
        if (n1x * pu + n1y * pv < d1) return 0;
        if (n2x * pu + n2y * pv < d2) return 0;
        n3y = ccu - bu;
        n3x = bv - ccv;
        d3 = n3x * bu + n3y * bv;
    } else {
        if (n1x * pu + n1y * pv > d1) return 0;
        if (n2x * pu + n2y * pv > d2) return 0;
        n3y = bu - ccu;
        n3x = ccv - bv;
        d3 = n3x * bu + n3y * bv;
    }
    if (n3x * pu + n3y * pv < d3) return 0;
    return 1;
}
#pragma opt_propagation reset

} /* extern "C" */
