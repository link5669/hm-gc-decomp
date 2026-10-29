// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct RD {
    u8 pad[292];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(s32 a);
    virtual u32 v5();
};
struct A {
    u8 pad[20];
    u8 *f20;
};
struct SB {
    A *f0;
    s32 f4;
    u32 f8;
    u32 f12;
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
};
struct S : SB {
    s32 f20;
    s32 f24;
};
extern "C" {
void fn_800FAEF8(RD *rd);
void fn_800FB064(RD *rd, char *buf);
void fn_800F87F0(void *x, char *buf, S *self);
s32 fn_800F9398(void *tbl, char *name);
s32 fn_800F9788(void *tbl, char *a, char *b);

s32 fn_801C6330(S *self, A *a, RD *rd, void *x) {
    char name[16];
    char sub[8];
    u32 tok;
    if (self->f4 != 0) self->v6();
    self->f0 = a;
    fn_800FAEF8(rd);
    while ((tok = rd->v5()) != 6) {
        switch ((s32)tok) {
        case 57:
            fn_800FB064(rd, name);
            fn_800F87F0(x, name, self);
            break;
        case 75:
            fn_800FB064(rd, name);
            fn_800FB064(rd, sub);
            if (a->f20 != 0) {
                s32 r;
                if (sub == 0 || sub[0] == 0) r = fn_800F9398(a->f20 + 72, name);
                else r = fn_800F9788(a->f20 + 96, sub, name);
                self->f24 = r;
            }
            break;
        case 76:
            fn_800FB064(rd, name);
            fn_800FB064(rd, sub);
            if (a->f20 != 0) {
                s32 r;
                if (sub == 0 || sub[0] == 0) r = fn_800F9398(a->f20 + 132, name);
                else r = fn_800F9788(a->f20 + 156, sub, name);
                self->f20 = r;
            }
            break;
        default:
            rd->v4(30);
            break;
        }
    }
    self->f4 = 1;
    return 0;
}

} /* extern "C" */
