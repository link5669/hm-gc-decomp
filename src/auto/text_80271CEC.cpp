// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct T_1CEC { u8 pad[28]; u8 f28[4]; };
struct O_1CEC { u8 pad[108]; void *f108; u8 pad2[32]; T_1CEC *f144; };
struct C801883E0 { u8 pad[108]; void *f108; u8 pad2[92]; C801883E0(); };
struct A_1CEC { u8 pad[156]; O_1CEC *f156; };
struct M_1CEC { u8 pad[360]; u8 f360[24]; u8 f384[4]; };
struct G2_1CEC { u8 pad[11340]; M_1CEC *f11340; };
struct G_1CEC { u8 pad[8]; void *f8; G2_1CEC *f12; };
struct S_1CEC { s32 n; C801883E0 *arr4[60]; O_1CEC *arr244[60]; void *f484; };
extern "C" {
extern G_1CEC *lbl_8035B460;
extern void *lbl_8035B808;
extern char lbl_802AA948[];
extern char lbl_80366F40[1];
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_80188144(C801883E0 *, void *, O_1CEC *, O_1CEC *);
void fn_800F6FBC(char *, void *);
void *fn_800F9398(void *, void *);
void *fn_800F9788(void *, char *, void *);
void fn_8019B6B8(void *, O_1CEC *);
void fn_8019B7E8(void *, void *);

static inline void *gettex_1CEC(O_1CEC *o) { void *r = o->f108; if (r == 0) r = o->f144->f28; return r; }

void fn_80271CEC(S_1CEC *self, A_1CEC *a, void *b) {
    M_1CEC *mgr = lbl_8035B460->f12->f11340;
    O_1CEC *o = a->f156;
    u32 key[1];
    void *tex;
    self->arr244[self->n] = o;
    if (lbl_8035B808 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B808);
    self->arr4[self->n] = new C801883E0;
    fn_800F7E98();
    if (self->arr4[self->n] == 0) fn_800604C4(-4, 0, 0, 0);
    fn_80188144(self->arr4[self->n], lbl_8035B460->f8, o, o);
    fn_800F6FBC(lbl_802AA948, key);
    if (lbl_80366F40 == 0 || lbl_80366F40[0] == 0)
        tex = fn_800F9398(mgr->f360, key);
    else
        tex = fn_800F9788(mgr->f384, lbl_80366F40, key);
    if (gettex_1CEC(self->arr244[self->n]) != tex) self->arr4[self->n]->f108 = tex;
    fn_8019B6B8(b, self->arr244[self->n]);
    fn_8019B7E8(self->f484, self->arr244[self->n]);
    fn_8019B7E8(self->f484, self->arr4[self->n]);
    self->n++;
}

} /* extern "C" */
