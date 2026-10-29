// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 __dt__9C80199ECCFv[];
extern u8 __dt__9C8018CED0Fv[];
extern u8 __dt__9C8019DC90Fv[];
extern u8 __dt__9C80185960Fv[];
extern u8 __dt__9C80197988Fv[];
extern u8 __dt__9C8019F0B4Fv[];
extern u8 __dt__9C8018AACCFv[];
extern u8 __dt__9C801883E0Fv[];
extern u8 __dt__9C8018E150Fv[];
extern u8 __dt__9C80197F58Fv[];
extern u8 __dt__9C80192398Fv[];
extern u8 __dt__9C8018FCF0Fv[];
void fn_800E1E88(void *p, void *dtor);
void __dla__FPv(void *p);
void fn_800F8DD0(void *p);
void fn_80193BD0(void *p);
} /* extern "C" */
struct V80193C7C { u8 pad[16]; virtual void v0(); virtual void v1(); };
extern "C" {
#define F(o, t) (*(t *)(self + (o)))
void fn_80193C7C(u8 *self) {
    if (F(236, void *)) fn_800E1E88(F(236, void *), __dt__9C80199ECCFv);
    if (F(228, void *)) fn_800E1E88(F(228, void *), __dt__9C8018CED0Fv);
    if (F(224, void *)) fn_800E1E88(F(224, void *), __dt__9C8019DC90Fv);
    if (F(220, void *)) fn_800E1E88(F(220, void *), __dt__9C80185960Fv);
    if (F(208, void *)) fn_800E1E88(F(208, void *), __dt__9C80197988Fv);
    if (F(212, void *)) fn_800E1E88(F(212, void *), __dt__9C8019F0B4Fv);
    if (F(216, void *)) fn_800E1E88(F(216, void *), __dt__9C8018AACCFv);
    if (F(188, void *)) fn_800E1E88(F(188, void *), __dt__9C801883E0Fv);
    if (F(184, void *)) fn_800E1E88(F(184, void *), __dt__9C8018E150Fv);
    if (F(232, void *)) fn_800E1E88(F(232, void *), __dt__9C80197F58Fv);
    if (F(172, void *)) fn_800E1E88(F(172, void *), __dt__9C80192398Fv);
    if (F(176, void *)) fn_800E1E88(F(176, void *), __dt__9C8018FCF0Fv);
    if (F(76, u8 *)) { if (F(76, u8 *)) __dla__FPv(F(76, u8 *) - 16); }
    ((V80193C7C *)(self + 20))->v1();
    fn_800F8DD0(self);
    fn_80193BD0(self);
}

} /* extern "C" */
