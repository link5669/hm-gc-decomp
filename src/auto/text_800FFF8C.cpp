// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { f32 x, y, z, w; } Q800FFF8C;
extern f32 lbl_803637A4;
void fn_800FFF8C(const Q800FFF8C *q, f32 *v) {
    f32 vx, vy, vz, tw, qw, qy, qx, k, tx, ty, tz, qz, cx, cy, cz;
    vx = v[0]; vy = v[1]; vz = v[2];
    qx = q->x; qy = q->y; qz = q->z; qw = q->w;
    k = lbl_803637A4;
    tx = qx * k + vx * qw + vy * qz - vz * qy;
    ty = qy * k + vy * qw + vz * qx - vx * qz;
    tz = qz * k + vz * qw + vx * qy - vy * qx;
    tw = qw * k - (qx * vx + qy * vy + qz * vz);
    cx = -qx; cy = -qy; cz = -qz;
    v[0] = tx * qw + cx * tw + cy * tz - cz * ty;
    v[1] = ty * qw + cy * tw + cz * tx - cx * tz;
    v[2] = tz * qw + cz * tw + cx * ty - cy * tx;
}

} /* extern "C" */
