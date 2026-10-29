// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct C800322B0_F24 { u32 a; s32 b; u32 c; C800322B0_F24() { a = 0; c = 0; b = 0; } ~C800322B0_F24() {} };
void __ct__9C80242B00Fi(void *p);
struct C80032274_F24 : C800322B0_F24 {
    u8 name[8];
    s32 f20;
    s32 f24;
    u8 pad28[4];
    s32 f32;
    u8 pad36[8];
    C80032274_F24() { __ct__9C80242B00Fi(this); }
    ~C80032274_F24() {}
};
extern u8 *lbl_8035B684;
u8 *fn_8010915C(u8 *p, char *name);
void fn_800F6E88(u8 *dst, char *name);
void fn_801089F0(u8 *obj, void *l);

void __ct__9C80253F24Fiiii(void *self, char *name, s32 a, s32 b, s32 c) {
    u8 *obj;
    C80032274_F24 loc;
    obj = fn_8010915C(lbl_8035B684 + 136, name);
    if (obj != 0) {
        fn_800F6E88(loc.name, name);
        loc.a = (u32)obj;
        loc.b = -1;
        loc.f20 = a;
        loc.f24 = b;
        loc.f32 = c;
        fn_801089F0(obj, &loc);
    }
}

} /* extern "C" */
