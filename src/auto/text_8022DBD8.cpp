// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct V3 { f32 x, y, z; };
struct M48 { u8 pad[16]; void *h; };
struct Xf { u8 pad[40]; V3 p; };
struct N { u8 pad[4]; u16 type; u8 pad2[48 - 6]; M48 *m; u8 pad3[60 - 52]; void *owner; u8 pad4[120 - 64]; Xf *xf; u8 pad5[156 - 124]; N **kids; u32 cur; };
struct FT { u8 pad[12]; void (*f12)(void *, void *); u8 pad2[304 - 16]; void (*getPos)(void *, V3 *); void (*getAx)(void *, V3 *, V3 *, V3 *); };
struct O { virtual void o0(); virtual void o1(); virtual void o2(); virtual void o3(); virtual void o4(); virtual void o5(); virtual void setA(void *a);
    u8 pad[20 - 4]; V3 ax0; V3 ax1; V3 ax2; V3 f56; V3 f68; V3 pos; V3 n0; V3 n1; V3 n2; V3 f128; u8 f140[156 - 140]; N *node; N *grp; };
extern "C" {
extern FT lbl_803286D0;
extern f32 lbl_80365D28, lbl_80365D58;
void fn_800F6E88(void *a, void *b);

static inline bool inRange(N *n) {
    return n->type >= 1 && n->type <= 13;
}

void fn_8022DBD8(O *o, void *a, N *n, void *name) {
    N *m;
    o->node = n;
    m = o->node;
    if (m && m->type == 3) {
        o->grp = m;
    } else if (m && m->type == 13) {
        N *k = m->kids[0];
        if (k->type == 3) o->grp = k;
    } else if (m && m->type == 12) {
        N *k = m->kids[m->cur];
        if (k->type == 3) o->grp = k;
    }
    fn_800F6E88(o->f140, name);
    o->setA(a);
    if (o->node) {
        if (o->node->m) lbl_803286D0.getPos(o->node->m->h, &o->pos);
        else { o->pos.x = lbl_80365D28; o->pos.y = lbl_80365D28; o->pos.z = lbl_80365D28; }
        o->f68.x = o->pos.x; o->f68.y = o->pos.y; o->f68.z = o->pos.z;
        if (o->node->m) lbl_803286D0.getAx(o->node->m->h, &o->n1, &o->n0, &o->n2);
        o->n1.x = -o->n1.x; o->n1.y = -o->n1.y; o->n1.z = -o->n1.z;
        o->n0.x = -o->n0.x; o->n0.y = -o->n0.y; o->n0.z = -o->n0.z;
        o->ax0.x = o->n0.x; o->ax0.y = o->n0.y; o->ax0.z = o->n0.z;
        o->ax1.x = o->n1.x; o->ax1.y = o->n1.y; o->ax1.z = o->n1.z;
        o->ax2.x = o->n2.x; o->ax2.y = o->n2.y; o->ax2.z = o->n2.z;
        if (inRange(o->node)) {
            Xf *x = n->xf;
            if (x) { o->f128.x = x->p.x; o->f128.y = x->p.y; o->f128.z = x->p.z; }
            else { o->f128.x = lbl_80365D58; o->f128.y = lbl_80365D58; o->f128.z = lbl_80365D58; }
            o->f56.x = o->f128.x; o->f56.y = o->f128.y; o->f56.z = o->f128.z;
        }
        o->node->owner = o;
    }
}

} /* extern "C" */
