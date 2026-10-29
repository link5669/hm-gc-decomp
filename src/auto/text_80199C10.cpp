// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct R80199C10 { u32 pad0; u32 eof; u8 pad8[0x11C]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void err(s32); virtual u32 next(); };
struct X80199C10 { u8 pad[20]; u8 *t; };
struct S80199C10 { u8 pad[108]; void *f108; };
struct Node80199C10 { void *a; s32 b; Node80199C10 *next; };
extern Node80199C10 *lbl_8035AE80;
extern void *lbl_8035A9F4;
void fn_800FB064(R80199C10 *, void *);
s32 fn_800FB33C(R80199C10 *);
void *fn_800F9398(void *, void *);
void *fn_800F9788(void *, char *, void *);
void *fn_801FDB64(void *);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_80191484(S80199C10 *, X80199C10 *, R80199C10 *);

static inline void *findA80199C10(u8 *t, char *grp, void *key) {
    if (grp == 0 || grp[0] == 0) {
        return fn_800F9398(t + 132, key);
    }
    return fn_800F9788(t + 156, grp, key);
}
static inline void *findB80199C10(u8 *t, char *grp, void *key) {
    if (grp == 0 || grp[0] == 0) {
        return fn_800F9398(t + 72, key);
    }
    return fn_800F9788(t + 96, grp, key);
}

void fn_80199C10(S80199C10 *self, X80199C10 *x, R80199C10 *r, s32 k) {
    void *res = 0;
    u8 key[8];
    char grp[8];
    Node80199C10 *n;
    switch (k) {
    case 85:
        fn_800FB064(r, key);
        fn_800FB064(r, grp);
        if (x->t != 0) {
            self->f108 = fn_801FDB64(findA80199C10(x->t, grp, key));
            if (self->f108 == 0) {
                r->err(37);
            }
        }
        break;
    case 161:
        fn_800FB064(r, key);
        fn_800FB064(r, grp);
        if (x->t != 0) {
            res = findB80199C10(x->t, grp, key);
            if (res == 0) {
                r->err(37);
            }
        }
        if (lbl_8035A9F4 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035A9F4);
        n = new Node80199C10;
        fn_800F7E98();
        if (n == 0) {
            fn_800604C4(-4, 0, 0, 0);
        }
        n->a = res;
        n->b = fn_800FB33C(r);
        n->next = lbl_8035AE80;
        lbl_8035AE80 = n;
        break;
    default:
        fn_80191484(self, x, r);
        break;
    }
}

} /* extern "C" */
