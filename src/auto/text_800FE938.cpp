#include "common.h"

extern "C" {

#pragma opt_propagation off
typedef struct V3 { f32 x, y, z; } V3;
typedef struct Box { V3 c; V3 e; } Box;
void fn_80101624(V3 *, V3 *, V3 *, f32);
extern const u32 lbl_80363764, lbl_80363768, lbl_8036376C, lbl_80363770, lbl_80363774, lbl_80363778, lbl_8036377C, lbl_80363780, lbl_80363784, lbl_80363788, lbl_8036378C, lbl_80363790;

u32 fn_800FE938(Box *box, V3 *a, V3 *b, V3 *o0, V3 *o1, f32 *t0, f32 *t1) {
    u32 code = 0;
    f32 ax = a->x, ay = a->y, az = a->z, bx = b->x;
    o0->x = ax; o0->y = ay; o0->z = az;
    o1->x = bx; o1->y = b->y; o1->z = b->z;
    if (o0->x > o1->x) {
        if (o0->x >= box->e.x + box->c.x) {
            if (o1->x < box->e.x + box->c.x) {
                *t0 = (box->e.x + box->c.x - ax) / (bx - ax);
                fn_80101624(o0, a, b, *t0);
                code = lbl_80363764;
            } else return 0;
        }
        if (o0->x >= -box->e.x + box->c.x) {
            if (o1->x < -box->e.x + box->c.x) {
                *t1 = (-box->e.x + box->c.x - a->x) / (b->x - a->x);
                fn_80101624(o1, a, b, *t1);
                code |= lbl_80363768;
            }
        } else return 0;
    } else {
        if (o1->x >= box->e.x + box->c.x) {
            if (o0->x < box->e.x + box->c.x) {
                *t1 = (box->e.x + box->c.x - ax) / (bx - ax);
                fn_80101624(o1, a, b, *t1);
                code = lbl_8036376C;
            } else return 0;
        }
        if (o1->x >= -box->e.x + box->c.x) {
            if (o0->x < -box->e.x + box->c.x) {
                *t0 = (-box->e.x + box->c.x - a->x) / (b->x - a->x);
                fn_80101624(o0, a, b, *t0);
                code |= lbl_80363770;
            }
        } else return 0;
    }
    if (o0->y > o1->y) {
        if (o0->y >= box->e.y + box->c.y) {
            if (o1->y < box->e.y + box->c.y) {
                *t0 = (box->e.y + box->c.y - a->y) / (b->y - a->y);
                fn_80101624(o0, a, b, *t0);
                code &= ~0x3F; code |= lbl_80363774;
            } else return 0;
        }
        if (o0->y >= -box->e.y + box->c.y) {
            if (o1->y < -box->e.y + box->c.y) {
                *t1 = (-box->e.y + box->c.y - a->y) / (b->y - a->y);
                fn_80101624(o1, a, b, *t1);
                code &= ~0xFC0; code |= lbl_80363778;
            }
        } else return 0;
    } else {
        if (o1->y >= box->e.y + box->c.y) {
            if (o0->y < box->e.y + box->c.y) {
                *t1 = (box->e.y + box->c.y - a->y) / (b->y - a->y);
                fn_80101624(o1, a, b, *t1);
                code &= ~0xFC0; code |= lbl_8036377C;
            } else return 0;
        }
        if (o1->y >= -box->e.y + box->c.y) {
            if (o0->y < -box->e.y + box->c.y) {
                *t0 = (-box->e.y + box->c.y - a->y) / (b->y - a->y);
                fn_80101624(o0, a, b, *t0);
                code &= ~0x3F; code |= lbl_80363780;
            }
        } else return 0;
    }
    if (o0->z > o1->z) {
        if (o0->z >= box->e.z + box->c.z) {
            if (o1->z < box->e.z + box->c.z) {
                *t0 = (box->e.z + box->c.z - a->z) / (b->z - a->z);
                fn_80101624(o0, a, b, *t0);
                code &= ~0x3F; code |= lbl_80363784;
            } else return 0;
        }
        if (o0->z >= -box->e.z + box->c.z) {
            if (o1->z < -box->e.z + box->c.z) {
                *t1 = (-box->e.z + box->c.z - a->z) / (b->z - a->z);
                fn_80101624(o1, a, b, *t1);
                code &= ~0xFC0; code |= lbl_80363788;
            }
        } else return 0;
    } else {
        if (o1->z >= box->e.z + box->c.z) {
            if (o0->z < box->e.z + box->c.z) {
                *t1 = (box->e.z + box->c.z - a->z) / (b->z - a->z);
                fn_80101624(o1, a, b, *t1);
                code &= ~0xFC0; code |= lbl_8036378C;
            } else return 0;
        }
        if (o1->z >= -box->e.z + box->c.z) {
            if (o0->z < -box->e.z + box->c.z) {
                *t0 = (-box->e.z + box->c.z - a->z) / (b->z - a->z);
                fn_80101624(o0, a, b, *t0);
                code &= ~0x3F; code |= lbl_80363790;
            }
        } else return 0;
    }
    return code;
}

} /* extern "C" */
