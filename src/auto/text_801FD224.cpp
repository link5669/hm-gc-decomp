// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_802EF3E0[];
extern u32 lbl_80365680;
} /* extern "C" */
struct R_801FD224 {
    u8 pad[292];
    virtual void v0(); virtual void v1(); virtual void v2(void *, s32, s32);
    virtual void v3(s32); virtual void v4(); virtual u32 v5();
};
struct A_801FD224 { u8 pad[72]; u8 f72[4]; };
struct E_801FD224 {
    u8 pad[8];
    u32 f8;
    u8 pad12[16];
    virtual void v0(A_801FD224 *, R_801FD224 *, char *);
};
struct Self_801FD224 {
    u8 pad[16];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(A_801FD224 *);
    virtual void v4(); virtual E_801FD224 *v5(u32);
    u32 f20;
};
extern "C" {
void fn_800FB000(R_801FD224 *, s32);
void fn_800FB064(R_801FD224 *, char *);
u32 fn_800FADA8(R_801FD224 *);
void fn_800FAEA0(R_801FD224 *);
void fn_800F8E38(Self_801FD224 *, u32);
void fn_800F87F0(Self_801FD224 *, char *, E_801FD224 *);
void fn_801FA778(A_801FD224 *, Self_801FD224 *, char *);
u32 fn_800F9398(void *, char *);

void fn_801FD224(Self_801FD224 *self, A_801FD224 *a, R_801FD224 *r) {
    char buf16[8];
    char buf8[8];
    u32 i;
    E_801FD224 *e;
    char *p;
    u32 t;

    p = 0;
    if (self->f20 != 0) self->v1();
    self->v3(a);
    r->v2(lbl_802EF3E0, 15, 0);
    while ((t = r->v5()) != 0) {
        switch ((s32)t) {
        case 57:
            fn_800FB064(r, buf8);
            p = buf8;
            break;
        case 58:
            self->f20 = fn_800FADA8(r);
            fn_800F8E38(self, self->f20);
            fn_801FA778(a, self, p);
            self->v2();
            for (i = 0; i < self->f20; i++) {
                fn_800FB000(r, 58);
                fn_800FB064(r, buf16);
                e = self->v5(i);
                if (fn_800F9398(a->f72, buf16) != 0) {
                    e->f8 |= lbl_80365680;
                    r->v3(36);
                } else {
                    fn_800F87F0(self, buf16, e);
                }
                e->v0(a, r, buf16);
            }
            fn_800FAEA0(r);
            return;
        }
    }
}

} /* extern "C" */
