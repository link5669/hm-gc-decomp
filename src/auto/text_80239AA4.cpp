// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u8 lbl_802F189C[];
extern u8 lbl_802F069C[];
void fn_80222BE8(void *);
void __dt__9C80031B94Fv(void *, s32);
void __dt__9C8022DFC8Fv(void *, s32);
void __dl__FPv(void *);
} /* extern "C" */
struct V80239B40 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};
extern "C" {

u8 *__dt__9C80239B40Fv(u8 *p, s16 f) {
    if (p) {
        *(u8 **)p = lbl_802F189C;
        ((V80239B40 *)p)->v3();
        if (p + 376) {
            *(u8 **)(p + 380) = lbl_802F069C;
            fn_80222BE8(p + 376);
            __dt__9C80031B94Fv(p + 376, 0);
        }
        __dt__9C8022DFC8Fv(p, 0);
        if (f > 0) __dl__FPv(p);
    }
    return p;
}

} /* extern "C" */
