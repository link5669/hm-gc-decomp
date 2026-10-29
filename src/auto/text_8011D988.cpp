// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct Ev8011D988 { void *self; u32 f4; u32 x; u32 f12; s32 val; u32 t; u32 flag; };
struct L8011D988 { virtual void on(Ev8011D988 *); virtual void off(Ev8011D988 *); };
struct Node8011D988 { Node8011D988 *next; u32 f4; u32 f8; s32 key; u32 f16; u32 f20; L8011D988 *l; };
struct Entry8011D988 { Node8011D988 *head; u32 f4; };
struct Pair8011D988 { u32 a; u32 b; };
struct S8011D988 {
    u8 pad0[56]; L8011D988 **ls; u32 pad60; u32 n; u32 pad68[2]; Pair8011D988 *ids;
    u8 pad80[40]; s32 *cur; s32 *prev; u32 *time; u8 pad132[16]; Entry8011D988 *ents;
    u8 pad152[16]; u32 count; u32 pad172; u32 t0; u32 pad180; u32 t1;
};

static inline void set8011D988(S8011D988 *self, u32 idx, s32 val) {
    if (idx < self->count) {
        if (val != self->cur[idx]) {
            self->cur[idx] = val;
            self->time[idx] = self->t0 + self->t1;
        }
    }
}

static inline Entry8011D988 *ent8011D988(S8011D988 *self, u32 idx) {
    return idx < self->count ? &self->ents[idx] : 0;
}

static inline void notify8011D988(S8011D988 *self, u32 n, Ev8011D988 *ev) {
    u32 i;
    for (i = 0; i < n; i++) {
        L8011D988 *l = self->ls[i];
        if (ev->val != 0) {
            l->on(ev);
        } else {
            l->off(ev);
        }
    }
}

static inline void notify2_8011D988(Entry8011D988 *e, Ev8011D988 *ev) {
    Node8011D988 *nd;
    if (e != 0) {
        nd = e->head;
        while (nd != 0) {
            if (nd->key == ev->val) {
                ev->f12 = nd->f16;
                if (ev->val == 0) {
                    nd->l->off(ev);
                } else {
                    nd->l->on(ev);
                }
            }
            nd = nd != 0 ? nd->next : e->head;
        }
    }
}

void fn_8011D988(S8011D988 *self, u32 idx, s32 val, s32 notify) {
    Entry8011D988 *e;
    u32 n;
    Ev8011D988 ev;
    u8 b;
    if (idx < self->count) {
        set8011D988(self, idx, val);
        if (notify != 0) {
            e = ent8011D988(self, idx);
            n = self->n;
            ev.self = self;
            ev.f4 = 0;
            ev.x = self->ids[idx].a;
            ev.f12 = 0;
            ev.val = val;
            ev.t = self->t0;
            b = 0;
            if (self->cur[idx] == self->prev[idx] && val != 0) {
                b = 1;
            }
            ev.flag = (b != 0);
            notify8011D988(self, n, &ev);
            notify2_8011D988(e, &ev);
        }
    }
}

} /* extern "C" */
