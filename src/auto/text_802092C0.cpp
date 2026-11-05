// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V_802092C0 { virtual void p0(); virtual void p1(); virtual void m(); };
extern "C" { extern u8 lbl_802EF9A0[]; void fn_80208814(void *); void fn_80208B64(void *); void fn_8020888C(void *, s32); void __dt__9C80208BF0Fv(void *, s32); void __dt__9C80208C80Fv(void *, s32); void __dl__FPv(void *); }

void *fn_802092C0(u8 *p, s16 f) {
    if (p != NULL) {
        *(void **)p = lbl_802EF9A0;
        if (*(void **)(p + 88) != NULL) {
            ((V_802092C0 *)p)->m();
        }
        fn_80208814(p + 72);
        fn_80208B64(p + 4);
        fn_8020888C(p + 72, -1);
        __dt__9C80208BF0Fv(p + 4, -1);
        __dt__9C80208C80Fv(p, 0);
        if (f > 0) {
            __dl__FPv(p);
        }
    }
    return p;
}

} /* extern "C" */
