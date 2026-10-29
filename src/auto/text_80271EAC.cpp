// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Q80271EAC { f32 x, y, z, w; };
struct B80271EAC {
    u32 flags;
    u8 pad4[20];
    Q80271EAC q;
    u8 pad40[64];
    virtual void v0(); virtual void v1(); virtual void v2();
};
struct A80271EAC {
    volatile u32 flags;
    u8 pad4[100];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(Q80271EAC *q);
};
struct S80271EAC {
    u32 count;
    A80271EAC *a[60];
    B80271EAC *b[60];
    void *f484;
};
struct ID80271EAC { u32 a, b; };
struct G80271EAC_2 { u8 pad[11340]; u8 *f11340; };
struct M80271EAC { u8 pad[12]; void *f12; };
struct G80271EAC { u8 pad[12]; G80271EAC_2 *f12; };
extern "C" {
extern G80271EAC *lbl_8035B460;
extern M80271EAC *lbl_8035B65C;
extern char lbl_802AA948[9];
extern const u32 lbl_80366F44;
extern const char lbl_80366F40[1];
void fn_800F6FBC(char *name, ID80271EAC *id);
void fn_800F9398(void *p, ID80271EAC *id);
void fn_800F9788(void *p, const char *s, ID80271EAC *id);
void fn_8019B6B8(void *mgr, B80271EAC *b);
void fn_80100CF4(Q80271EAC *q);
void fn_8019AA94(void *p, void *q);
static inline void set80271EAC(u8 *p, const char *s, ID80271EAC *id) {
    if (s == 0 || s[0] == 0) fn_800F9398(p + 360, id);
    else fn_800F9788(p + 384, s, id);
}
void fn_80271EAC(S80271EAC *self) {
    A80271EAC *a;
    B80271EAC *b;
    void *mgr;
    S80271EAC *s;
    u32 i;
    u8 *p;
    ID80271EAC id;
    Q80271EAC q;
    p = lbl_8035B460->f12->f11340;
    fn_800F6FBC(lbl_802AA948, &id);
    set80271EAC(p, lbl_80366F40, &id);
    mgr = lbl_8035B65C->f12;
    for (i = 0, s = self; i < self->count; s = (S80271EAC *)((u32 *)s + 1), i++) {
        if (s->b[0]->flags & 0x800) {
            a = s->a[0];
            if (!((a->flags >> 11) & 1)) a->flags |= lbl_80366F44;
            fn_8019B6B8(mgr, s->b[0]);
        } else {
            a = s->a[0];
            if (a->flags & 0x800) a->flags &= ~0x800;
        }
        fn_80100CF4(&q);
        b = s->b[0];
        if (b->flags & 4) b->v2();
        q = b->q;
        s->a[0]->v16(&q);
    }
    fn_8019AA94(self->f484, (u8 *)lbl_8035B460->f12 + 12352);
}

} /* extern "C" */
