// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct R { u8 pad_[292]; virtual void s0(); virtual void s1(); virtual void s2(void *, int, int); virtual void s3(); virtual void v4(int); virtual u32 v5(); };
struct B { u8 pad[60]; u8 f60[24]; u8 f84[4]; };
struct T {
    u8 pad[16];
    virtual void v0(); virtual void v1(); virtual void v2(B *); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void *v8(u32);
    u32 f20;
    u32 f24;
    u32 f28;
    void **f32;
    u32 f36;
    u32 f40;
    void **f44;
};
extern char lbl_802E4A78[];
extern void *lbl_8035AC00;
u32 fn_800FADA8(R *);
void fn_800FAEA0(R *);
void fn_800FAD08(R *, void *);
void fn_800FB000(R *, int);
void fn_800FB064(R *, void *);
void *fn_800F9398(void *, void *);
void *fn_800F9788(void *, char *, void *);
void fn_800F8E38(T *, u32);
void fn_80135FB0(B *, T *, char *);
void fn_800F87F0(T *, void *, void *);
void fn_801300B8(void *, B *, T *, R *, char *);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
#define ALLOC(H, dst, expr) \
    if (!H) fn_800604C4(-2, 0, 0, 0); \
    fn_800F7EC0(H); \
    dst = expr; \
    fn_800F7E98(); \
    if (!dst) fn_800604C4(-4, 0, 0, 0);
static inline void *look(B *b, char *nm, void *id) {
    if (nm == 0 || *nm == 0) return fn_800F9398(b->f60, id);
    return fn_800F9788(b->f84, nm, id);
}
static inline void ldA0(T *t, B *b, R *r, u32 &cnt, void **&arr, char *name) {
    void **p;
    u32 n;
    u32 i;
    if (cnt) r->v4(39);
    cnt = fn_800FADA8(r);
    if (cnt < 1) r->v4(35);
    ALLOC(lbl_8035AC00, arr, new void *[cnt])
    n = cnt;
    p = arr;
    for (i = 0; i < n; p++, i++) {
        switch (r->v5()) {
        case 2: {
            u8 id[8];
            fn_800FAD08(r, id);
            *p = look(b, name, id);
            if (*p == 0) r->v4(37);
            break;
        }
        case 62:
            *p = 0;
            break;
        default:
            r->v4(3);
            break;
        }
    }
    fn_800FAEA0(r);
}
static inline void ldA(T *t, B *b, R *r, u32 &cnt, void **&arr, char *name) {
    u32 n;
    u32 i;
    void **p;
    if (cnt) r->v4(39);
    cnt = fn_800FADA8(r);
    if (cnt < 1) r->v4(35);
    ALLOC(lbl_8035AC00, arr, new void *[cnt])
    n = cnt;
    p = arr;
    for (i = 0; i < n; p++, i++) {
        switch (r->v5()) {
        case 2: {
            u8 id[8];
            fn_800FAD08(r, id);
            *p = look(b, name, id);
            if (*p == 0) r->v4(37);
            break;
        }
        case 62:
            *p = 0;
            break;
        default:
            r->v4(3);
            break;
        }
    }
    fn_800FAEA0(r);
}
static inline void ldB(T *t, B *b, R *r, u32 &cnt, void **&arr) {
    u32 n;
    u32 i;
    void **p;
    if (cnt) r->v4(39);
    cnt = fn_800FADA8(r);
    if (cnt < 1) r->v4(35);
    ALLOC(lbl_8035AC00, arr, new void *[cnt])
    n = cnt;
    p = arr;
    for (i = 0; i < n; p++, i++) {
        switch (r->v5()) {
        case 2: {
            u8 id[8];
            char nm[8];
            fn_800FAD08(r, id);
            fn_800FB064(r, nm);
            *p = look(b, nm, id);
            if (*p == 0) r->v4(37);
            break;
        }
        case 62:
            *p = 0;
            break;
        default:
            r->v4(3);
            break;
        }
    }
    fn_800FAEA0(r);
}
void fn_80131240(T *t, B *b, R *r) {
    char *name;
    u32 tok;
    u32 i;
    if (t->f20) t->v1();
    r->s2(lbl_802E4A78, 64, 0);
    tok = r->v5();
    name = 0;
    if (tok == 57) {
        char nb[8];
        fn_800FB064(r, nb);
        name = nb;
        tok = r->v5();
    }
    while (tok != 0) {
        switch (tok) {
        case 58: ldA0(t, b, r, t->f24, t->f32, name); break;
        case 59: ldA(t, b, r, t->f36, t->f44, name); break;
        case 60: ldB(t, b, r, t->f24, t->f32); break;
        case 61: ldB(t, b, r, t->f36, t->f44); break;
        case 63: {
            u8 buf[12];
            t->f20 = fn_800FADA8(r);
            fn_800F8E38(t, t->f20);
            fn_80135FB0(b, t, name);
            t->v2(b);
            for (i = 0; i < t->f20; i++) {
                void *e;
                fn_800FB000(r, 63);
                fn_800FB064(r, buf);
                e = t->v8(i);
                fn_800F87F0(t, buf, e);
                fn_801300B8(e, b, t, r, name);
            }
            fn_800FAEA0(r);
            break;
        }
        default:
            r->v4(30);
            break;
        }
        tok = r->v5();
    }
}

} /* extern "C" */
