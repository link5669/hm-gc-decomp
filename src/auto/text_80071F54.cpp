// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct E_80071F54 { u8 pad[4]; f32 f4; u8 pad8[52]; };
struct S160_80071F54 { u8 pad[176]; E_80071F54 *f176; };
struct S12_80071F54 { u8 pad[160]; S160_80071F54 *f160; };
struct X_80071F54 { u8 pad[8]; s32 f8; S12_80071F54 *f12; };
struct H_80071F54 { u8 pad[168]; void *f168; };
struct O_80071F54 { u8 pad0[160]; H_80071F54 *f160; u8 pad164[20]; X_80071F54 *f184; u8 pad188[336]; void *f524; u8 pad528[532]; H_80071F54 *f1060; };
extern "C" {
extern f32 lbl_8035F3EC;
void fn_802413D8(void *p, char *a, s32 b, s32 c, s32 d, f32 f);
void fn_8017AF08(E_80071F54 *, void *);
void fn_8023CEEC(void *, void *);
static inline E_80071F54 *get_80071F54(X_80071F54 *x) {
    if (x->f12 != 0 && x->f12->f160 != 0) return &x->f12->f160->f176[x->f8];
    return 0;
}
void fn_80071F54(O_80071F54 *o, char *s, f32 f) {
    if (s[0] != 0) fn_802413D8(o->f524, s, 0, 0, 0, lbl_8035F3EC);
    get_80071F54(o->f184)->f4 = f;
    { void *h = o->f160->f168; fn_8017AF08(get_80071F54(o->f184), h); }
    fn_8023CEEC(o->f1060->f168, o->f160->f168);
}

} /* extern "C" */
