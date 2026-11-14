// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

// NonMatching draft. The scratch arrays below are the .bss of text_80261D18 (0x80357B68-0x80357E48);
// defining them here gives the same-TU section-base addressing the target uses. Needs a TU merge
// 802611B8..80261DEC to link.

extern "C" {

struct V3 { f32 x, y, z; };
struct Sph { f32 x, y, z, r; };

class Node { public:
    u32 f0; u8 pad4[0x20]; f32 r; u8 pad28[0x68 - 0x28];
    virtual void n0(); virtual void n1(); virtual void upd(); };

struct Tgt { u8 pad[0x9c]; Node *n; };

struct Obj {
    u8 pad0[0x14];
    V3 pos;
    u8 pad20[0xc];
    V3 vel;
    u8 pad38[0x18];
    V3 p50;
    V3 ay;
    V3 ax;
    V3 az;
    u8 pad80[0x9c - 0x80];
    Tgt *t;
};

struct Tbl { f32 f0; f32 k; f32 f8; V3 off[5]; };

V3 lbl_80357B68[8];
static V3 sB[8];
static V3 sC[8];
static V3 sD[8];
static s32 sHit[8];
static s32 sE[8];
static s32 sF[8];
static s32 sG[8];
static s32 sH[8];
static s32 sI[8];
static V3 sJ[8];
static s32 sK[8];
static s32 sL[8];
extern Tbl lbl_802F2A28;
extern f32 lbl_80366A60;
extern f32 lbl_80366A74;
extern f32 lbl_80366A78;
extern f64 lbl_80366A80;
extern f64 lbl_80366A88;
extern f32 lbl_80366A90;

void fn_80100CF4(Sph *s);
f32 fn_8010155C(V3 *a, V3 *b);
void fn_80101624(V3 *dst, V3 *a, V3 *b, f32 t);
s32 fn_80264E0C(V3 *a, V3 *b, V3 *c, V3 *d, s32 *e, s32 *f, s32 *g, s32 *h, s32 i, s32 *j, V3 *k, s32 *l, s32 *m, s32 n, s32 o);
s32 fn_80264AC0(s32 n, V3 *a, V3 *b, Sph *s, s32 *hit, V3 *c, V3 *d, s32 *e, s32 *f, s32 *g, s32 *h, s32 i, s32 *j, V3 *k, s32 *l, s32 *m, s32 n2, s32 o);

inline f32 Sq(f32 x) {
    if (x > lbl_80366A60) {
        volatile f32 y;
        f64 g = __frsqrte(x);
        g = lbl_80366A80 * g * (lbl_80366A88 - g * g * x);
        g = lbl_80366A80 * g * (lbl_80366A88 - g * g * x);
        g = lbl_80366A80 * g * (lbl_80366A88 - g * g * x);
        y = x * g;
        return y;
    }
    return x;
}

inline s32 Seg(int k) {
    return fn_80264E0C(&lbl_80357B68[k], &sB[k], &sC[k], &sD[k], &sE[k], &sF[k], &sG[k], &sH[k], 0, &sI[k], &sJ[k], &sK[k], &sL[k], 0, 1);
}

inline bool Eq(const V3 &a, const V3 &b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

inline bool Near(const V3 &a, const V3 &b) {
    return a.x >= b.x - lbl_80366A74 && a.x <= b.x + lbl_80366A74 && a.y >= b.y - lbl_80366A74 && a.y <= b.y + lbl_80366A74 && a.z >= b.z - lbl_80366A74 && a.z <= b.z + lbl_80366A74;
}

#pragma push
#pragma opt_loop_invariants off
void fn_802611B8(Obj *o) {
    s32 *hit = sHit;
    s32 moved = 0;
    int i;
    for (i = 0; i < 8; i++) hit[i] = 0;
    if (Eq(o->pos, o->p50) && Near(o->vel, o->ax)) return;

    Node *n = o->t->n;
    if (n->f0 & 4) n->upd();
    f32 r = n->r;
    V3 pos;
    pos = o->pos;
    f32 dt = lbl_802F2A28.k * r;
    pos.x += dt * o->vel.x;
    pos.y += dt * o->vel.y;
    pos.z += dt * o->vel.z;
    V3 q;
    q = o->p50;
    q.x += dt * o->ax.x;
    q.y += dt * o->ax.y;
    q.z += dt * o->ax.z;
    lbl_80357B68[6] = pos;
    sB[6] = q;
    if ((hit[6] = Seg(6)) != 0) {
        f32 d = fn_8010155C(&lbl_80357B68[6], &sC[6]);
        if (d > lbl_80366A78) {
            moved = 1;
            f32 len = Sq(d);
            fn_80101624(&pos, &lbl_80357B68[6], &sC[6], (len - lbl_80366A90) / len);
        }
    } else {
        pos = q;
        moved = 1;
    }

    Sph s;
    fn_80100CF4(&s);
    s.x = lbl_80366A60; s.y = lbl_80366A60; s.z = lbl_80366A60; s.r = lbl_80366A60;
    dt = lbl_802F2A28.k * r;
    for (i = 0; i < 5; i++) {
        lbl_80357B68[i] = pos;
        sB[i] = pos;
        f32 fx = r * lbl_802F2A28.off[i].x;
        f32 fy = r * lbl_802F2A28.off[i].y;
        f32 fz = r * lbl_802F2A28.off[i].z;
        sB[i].x -= dt * o->ax.x;
        sB[i].y -= dt * o->ax.y;
        sB[i].z -= dt * o->ax.z;
        sB[i].x += fx * o->ay.x;
        sB[i].y += fx * o->ay.y;
        sB[i].z += fx * o->ay.z;
        sB[i].x += fy * o->ax.x;
        sB[i].y += fy * o->ax.y;
        sB[i].z += fy * o->ax.z;
        sB[i].x += fz * o->az.x;
        sB[i].y += fz * o->az.y;
        sB[i].z += fz * o->az.z;
    }
    s.x = pos.x;
    s.y = pos.y;
    s.z = pos.z;
    s.r = r;
    if (fn_80264AC0(6, lbl_80357B68, sB, &s, sHit, sC, sD, sE, sF, sG, sH, 0, sI, sJ, sK, sL, 0, 1)) {
        f32 ax = pos.x, ay = pos.y, az = pos.z;
        for (i = 0; i < 5; i++) {
            if (hit[i]) {
                V3 *c = &sC[i], *b = &sB[i];
                ax += c->x - b->x;
                ay += c->y - b->y;
                az += c->z - b->z;
            }
        }
        lbl_80357B68[7] = pos;
        sB[7].x = ax; sB[7].y = ay; sB[7].z = az;
        if ((hit[7] = Seg(7)) != 0) {
            f32 d = fn_8010155C(&lbl_80357B68[7], &sC[7]);
            if (d > lbl_80366A78) {
                moved = 1;
                f32 len = Sq(d);
                fn_80101624(&pos, &lbl_80357B68[7], &sC[7], (len - lbl_80366A90) / len);
            }
        } else {
            pos.x = ax; pos.y = ay; pos.z = az;
            moved = 1;
        }
    }
    if (moved) {
        f32 px = *(volatile f32 *)&pos.x;
        f32 k = *(volatile f32 *)&lbl_802F2A28.k;
        *(volatile f32 *)&o->p50.x = px;
        f32 m = k * r;
        o->p50.y = pos.y;
        o->p50.z = pos.z;
        o->p50.x -= m * o->ax.x;
        o->p50.y -= m * o->ax.y;
        o->p50.z -= m * o->ax.z;
    }
}
#pragma pop

}
