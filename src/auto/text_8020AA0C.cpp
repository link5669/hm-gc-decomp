// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct E8020AA0C {
    u8 pad0[16];
    virtual void v0();
    virtual void v1();
    virtual s32 v2(char *name, u8 *buf, void *arg);
    u8 pad20[160];
    s32 used;
};
struct M8020AA0C {
    u8 pad0[128];
    char name[1572];
    u32 f1700;
    u32 f1704;
    u32 f1708;
    s32 f1712;
    u8 pad1716[8];
    E8020AA0C *f1724;
};
extern "C" {
extern char lbl_802A6BEC[];
extern char lbl_803657EC[8];
void fn_80207E5C(M8020AA0C *self, void *a);
s32 fn_80207CDC(M8020AA0C *self, u8 *buf, u32 n, void *a);
void fn_80060568(char *s, s32 a, s32 b, s32 c);
void fn_8020A0BC(E8020AA0C *e, M8020AA0C *self);
void fn_800E8F6C(char *buf, char *fmt, ...);
void fn_800E91D0(char *fmt, ...);
static inline E8020AA0C *findfree8020AA0C(M8020AA0C *self) {
    u32 i;
    if (self->f1724 == 0) return 0;
    for (i = 0; i < self->f1704; i++) {
        if (self->f1724[i].used == 0) return &self->f1724[i];
    }
    return 0;
}
s32 fn_8020AA0C(M8020AA0C *self, void *a1, void *a2, E8020AA0C **out) {
    E8020AA0C *e;
    s32 r;
    u8 buf[268];
    char msg[268];
    if (a2 == 0) return 9;
    e = findfree8020AA0C(self);
    if (e == 0) return 3;
    fn_80207E5C(self, a1);
    if (fn_80207CDC(self, buf, 268, a1) == 0) fn_80060568(lbl_802A6BEC, 0, 0, 0);
    fn_8020A0BC(e, self);
    r = e->v2(self->name, buf, a2);
    if (r != 0) {
        e->v1();
        *out = 0;
        return r;
    }
    self->f1700++;
    if (self->f1700 > self->f1708) self->f1708 = self->f1700;
    *out = e;
    if (self->f1712 != 0) {
        fn_800E8F6C(msg, lbl_803657EC, self->name);
        fn_800E91D0(msg);
    }
    return 0;
}

} /* extern "C" */
