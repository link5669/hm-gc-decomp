// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_803286D0[];
extern u8 *lbl_8035B65C;
extern f32 lbl_80365D28;
extern f32 lbl_80365D2C;
typedef struct V8022A0BC { f32 x, y, z; } V8022A0BC;
void fn_80107244(void *, V8022A0BC *);
f32 fn_8010155C(V8022A0BC *, V8022A0BC *);

s32 fn_8022A0BC(u8 *self) {
    u8 *o;
    V8022A0BC a;
    V8022A0BC b;
    f32 r;
    f32 *pr;
    o = M2C_FIELD(self, u8 **, 156);
    if (o == 0) {
        return 1;
    }
    if (M2C_FIELD(o, void **, 48) != 0) {
        fn_80107244(M2C_FIELD(o, void **, 48), &a);
    } else {
        a.x = lbl_80365D28;
        a.y = lbl_80365D28;
        a.z = lbl_80365D28;
    }
    (*(void (**)(void *, V8022A0BC *))(lbl_803286D0 + 304))(M2C_FIELD(M2C_FIELD(lbl_8035B65C, u8 **, 40), void **, 16), &b);
    pr = M2C_FIELD(self, f32 **, 172);
    if (pr != 0) {
        r = *pr;
    } else if ((pr = M2C_FIELD(lbl_8035B65C, f32 **, 724)) == 0) {
        r = lbl_80365D2C;
    } else {
        r = *pr;
    }
    return ((f32)__fabs(fn_8010155C(&b, &a)) < r * r) ? 1 : 0;
}

} /* extern "C" */
