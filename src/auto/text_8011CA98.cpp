// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct N { N *next; N *prev; s32 a8; s32 c12; u32 b16; void *q20; struct S *s24; };
struct Q16 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual u32 s19(); virtual u32 *s20(); virtual u32 *s21(); virtual u32 *s22(u32);
    u8 pad4[20];
    u32 n24;
};
struct S;
typedef void (S::*PMF)(u32, s32, s32, u32);
struct S {
    u32 pad0;
    PMF pmf;
    Q16 *q16;
    u8 pad20[12];
    N *free32;
    N *tail36;
    N **list56;
    u8 pad44[4];
    u32 n64;
};
extern "C" {
extern PMF lbl_802E3E50;
u32 *fn_8011F990(Q16 *, u32);
s32 fn_8011DF4C(void *, N *);
void fn_80118FC4(N ***, N *);

static inline N *find(S *p, void *q, s32 a, s32 c, u32 b) {
    u32 i;
    for (i = 0; i < p->n64; i++) {
        N *e = p->list56[i];
        if (e->q20 == q && e->a8 == a && e->c12 == c && e->b16 == b) return e;
    }
    return 0;
}

s32 fn_8011CA98(S *p, void *q, s32 a, s32 c, u32 b) {
    if (!q) {
        u32 *o;
        u32 i;
        p->pmf = lbl_802E3E50;
        o = p->q16->s20();
        if (o) o = (u32 *)*o;
        (p->*p->pmf)((u32)o, a, c, b);
        o = p->q16->s21();
        if (o) o = (u32 *)*o;
        (p->*p->pmf)((u32)o, a, c, b);
        for (i = 0; i < p->q16->n24; i++) {
            o = p->q16->s22(i);
        if (o) o = (u32 *)*o;
        (p->*p->pmf)((u32)o, a, c, b);
        }
        for (i = 0; i < p->q16->s19(); i++) {
            o = fn_8011F990(p->q16, i);
        if (o) o = (u32 *)*o;
        (p->*p->pmf)((u32)o, a, c, b);
        }
        return 1;
    }
    if (!find(p, q, a, c, b)) {
        N *n = p->free32;
        if (n) {
            if ((p->free32 = n->next) != 0) p->free32->prev = 0;
            else p->tail36 = 0;
        }
        n->q20 = q;
        n->a8 = a;
        n->c12 = c;
        n->b16 = b;
        n->s24 = p;
        if (fn_8011DF4C(q, n)) {
            fn_80118FC4(&p->list56, n);
        } else {
            if ((n->next = p->free32) != 0) p->free32->prev = n;
            else p->tail36 = n;
            p->free32 = n;
            n->prev = 0;
        }
    }
    return 1;
}

} /* extern "C" */
