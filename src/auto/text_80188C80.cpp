// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V { f32 x, y, z; };
struct O { u32 f0; u8 pad4[20]; V pos; f32 r36; u8 pad40[64]; virtual void a0(); virtual void a1(); virtual void upd(); };
struct E { f32 lo, hi; u8 pad8[4]; O *o; u8 pad16[8]; E *prev; E *next; };
struct B { u8 pad[16]; int axis16; E *tail[3]; };
void fn_80188C80(B *b, int ax, E *e) {
    O *o;
    switch (b->axis16) {
    case 0:
        o = e->o;
        if (o->f0 & 4) o->upd();
        e->lo = o->pos.x - o->r36;
        e->hi = o->pos.x + o->r36;
        break;
    case 1:
        o = e->o;
        if (o->f0 & 4) o->upd();
        e->lo = o->pos.y - o->r36;
        e->hi = o->pos.y + o->r36;
        break;
    case 2:
        o = e->o;
        if (o->f0 & 4) o->upd();
        e->lo = o->pos.z - o->r36;
        e->hi = o->pos.z + o->r36;
        break;
    }
    if (e->next && e->lo < e->next->lo) {
        e->next->prev = e->prev;
        if (e->prev) e->prev->next = e->next;
        E *p;
        E *q = e->next;
        for (;;) {
            p = q;
            q = q->next;
            if (!q) {
                e->prev = p;
                e->next = 0;
                p->next = e;
                b->tail[ax] = e;
                return;
            }
            if (!(e->lo < q->lo)) break;
        }
        e->prev = p;
        e->next = q;
        q->prev = e;
        p->next = e;
    }
    if (e->prev && e->lo > e->prev->lo) {
        e->prev->next = e->next;
        if (e->next) e->next->prev = e->prev;
        else b->tail[ax] = e->prev;
        E *q = e->prev;
        E *p;
        for (;;) {
            p = q;
            q = q->prev;
            if (!q) {
                e->next = p;
                e->prev = 0;
                p->prev = e;
                return;
            }
            if (!(e->lo > q->lo)) break;
        }
        e->next = p;
        e->prev = q;
        q->next = e;
        p->prev = e;
    }
}

} /* extern "C" */
