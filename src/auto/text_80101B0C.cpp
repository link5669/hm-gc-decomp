// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct E80101B0C { u8 pad[10]; u16 idx; };
struct T80101B0C { u32 a; u32 b; u32 c; };
struct O80101B0C { u8 pad[16]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void draw(E80101B0C *, u16, T80101B0C *, void *, f32, f32); };
struct M80101B0C { u8 pad[24]; O80101B0C *obj; u8 pad28[12]; E80101B0C *elems; };
struct P80101B0C { M80101B0C *m; u8 pad4[40]; u16 start; u16 count; u8 pad48[6]; u16 f54; };
struct Q80101B0C { u8 pad[24]; T80101B0C *t; };
static inline O80101B0C *getobj(P80101B0C *p) { return p->m->obj; }

void fn_80101B0C(P80101B0C *p, Q80101B0C *q, void *c, f32 x, f32 y) {
    u32 end;
    O80101B0C *obj;
    u32 i;
    obj = getobj(p);
    end = p->start + p->count;
    if (q != 0) {
        for (i = p->start; i < end; i++) {
            E80101B0C *e = &p->m->elems[i];
            T80101B0C *t = &q->t[e->idx];
            t->c = 0;
            obj->draw(e, p->f54, t, c, x, y);
        }
    } else {
        for (i = p->start; i < end; i++) {
            obj->draw(&p->m->elems[i], p->f54, 0, c, x, y);
        }
    }
}

} /* extern "C" */
