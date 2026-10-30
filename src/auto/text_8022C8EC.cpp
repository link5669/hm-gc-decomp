// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V { f32 x, y, z; };
struct FT { u8 pad[12]; void (*f12)(void *, V *); u8 pad16[12]; void (*f28)(void *, V *, V *, V *); };
extern FT lbl_803286D0;
extern u32 lbl_80365D44;
struct P { u8 pad[16]; void *f16; u8 pad20[12]; u32 f32; };
struct O { u8 pad[4]; u16 f4; u8 pad6[42]; P *f48; u8 pad52[68]; void *f120; };
struct T { u8 pad[20]; V a20; V c32; V b44; V d56; V p68; u8 pad80[76]; O *f156; };
void fn_80190C98(O *);
void fn_80107F3C(void *, V *);
static inline void upd(O *o, V *v) {
    if (o) {
        P *q = o->f48;
        if (q) {
            lbl_803286D0.f12(q->f16, v);
            q->f32 |= lbl_80365D44;
            fn_80190C98(o);
        }
    }
}
static inline bool rng(O *o) { return o->f4 >= 1 && o->f4 <= 13; }
void fn_8022C8EC(T *t, V *pos, V *a, V *b, V *c, V *d) {
    if (!t->f156) return;
    if (pos) {
        t->p68 = *pos;
        {
            O *o1 = t->f156;
            if (o1) {
                P *q1 = o1->f48;
                if (q1) {
                    lbl_803286D0.f12(q1->f16, pos);
                    q1->f32 |= lbl_80365D44;
                    fn_80190C98(o1);
                }
            }
        }
    }
    if (a) t->a20 = *a;
    if (b) t->b44 = *b;
    if (c) t->c32 = *c;
    if (d) t->d56 = *d;
    if (a && b && c) {
        V cn;
        V an;
        cn = *c;
        an = *a;
        cn.x = -cn.x; cn.y = -cn.y; cn.z = -cn.z;
        an.x = -an.x; an.y = -an.y; an.z = -an.z;
        O *o = t->f156;
        if (o) {
            P *q = o->f48;
            if (q) {
                lbl_803286D0.f28(q->f16, &cn, &an, b);
                q->f32 |= lbl_80365D44;
                fn_80190C98(o);
            }
        }
    }
    if (d && t->f156) {
        O *o = t->f156;
        if (rng(o) && o->f120) fn_80107F3C(o->f120, d);
    }
}

} /* extern "C" */
