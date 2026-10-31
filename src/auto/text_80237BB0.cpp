// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V3 { f32 x, y, z; };
struct Bone { void *o; u8 pad[16]; Bone *next; u8 pad2[4]; V3 p; };
struct Scl { u8 pad[40]; V3 s; };
struct Node {
    u32 flags;
    u8 pad[20];
    V3 pos;      /* 24 */
    u8 pad2[20];
    Bone *bones; /* 56 */
    u8 pad3[24];
    Node *sib;   /* 84 */
    Node *child; /* 88 */
    u8 pad4[12];
    virtual void v0(); virtual void v1(); virtual void Update(); /* 104 vptr, slot 16 */
    u8 pad5[12];
    Scl *scl;    /* 120 */
};
struct Act {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void GetDir(s32, V3 *, V3 *, s32, s32); /* 60 */
    u8 pad[152];
    Node *node;  /* 156 */
    u8 pad2[296];
    f32 *range;  /* 456 */
    f32 *fov;    /* 460 */
};
void *fn_8017BC48(Bone *, Node *);
void fn_80104004(void *, V3 *, V3 *);
void fn_80100F24(V3 *, V3 *);
void fn_80101820(V3 *);
double fn_800F045C(double);
s32 fn_80264E0C(V3 *, V3 *, s32, s32, s32, s32, Node **, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 lbl_80365EFC, lbl_80365F08, lbl_80365F40, lbl_80365F50, lbl_80365F54, lbl_80365F58, lbl_80365F5C;
extern f64 lbl_80365F28, lbl_80365F30, lbl_80365F48;

inline void GetPos(Node *n, V3 *o)
{
    if (n->flags & 4) n->Update();
    *o = n->pos;
}

inline f32 Sq(f32 x)
{
    if (x > lbl_80365EFC) {
        const f64 _half = lbl_80365F28;
        const f64 _three = lbl_80365F30;
        volatile f32 y;
        f64 g = __frsqrte((f64)x);
        g = _half * g * (_three - g * g * x);
        g = _half * g * (_three - g * g * x);
        g = _half * g * (_three - g * g * x);
        y = x * g;
        return y;
    }
    return x;
}

inline f32 Acos(f32 x)
{
    if ((f32)__fabs(x) <= lbl_80365F48) return fn_800F045C(x);
    if (x > lbl_80365EFC) return lbl_80365EFC;
    return lbl_80365F50;
}

s32 fn_80237BB0(Act *self, Act *tgt, s32 chkAng, s32 chkDist, s32 mask)
{
    Node *n = self->node;
    V3 eye;
    V3 tp;
    V3 dir;
    V3 up;
    V3 d;
    Node *hit;
    Bone *b;
    GetPos(n, &eye);
    self->GetDir(0, &dir, &up, 0, 0);
    n = tgt->node;
    b = n->bones;
    while (b && b->o) b = b->next;
    if (b && !b->o) {
        V3 lp;
        f32 sx, sy, sz;
        f32 px = b->p.x, py = b->p.y, pz = b->p.z;
        if (n->scl) { sx = n->scl->s.x; sy = n->scl->s.y; sz = n->scl->s.z; }
        else { sz = sy = sx = lbl_80365F5C; }
        px *= sx; py *= sy; pz *= sz;
        lp.x = px;
        lp.y = py;
        lp.z = pz;
        fn_80104004(fn_8017BC48(b, n), &lp, &tp);
    } else {
        GetPos(n, &tp);
    }
    d.x = tp.x - eye.x;
    d.y = tp.y - eye.y;
    d.z = tp.z - eye.z;
    if (chkDist) {
        f32 len = Sq(d.x * d.x + d.y * d.y + d.z * d.z);
        if (len > (self->range ? *self->range : lbl_80365F40)) return 0;
    }
    fn_80100F24(&d, &up);
    fn_80101820(&d);
    if (chkAng) {
        f64 ad = __fabs(Acos(dir.x * d.x + dir.y * d.y + dir.z * d.z));
        f32 a = ad;
        if (a > (self->fov ? lbl_80365F08 * (lbl_80365F54 * *self->fov) : lbl_80365F58)) return 0;
    }
    hit = 0;
    if (fn_80264E0C(&eye, &tp, mask, 0, 0, 0, &hit, 0, 0, 0, 0, 0, 0, 0, 1) == 0) return 1;
    if (hit && tgt->node) {
        Node *p = tgt->node;
        if (hit == p) return 1;
        for (p = p->child; p; p = p->sib)
            if (hit == p) return 1;
        return 0;
    }
    return 0;
}

} /* extern "C" */
