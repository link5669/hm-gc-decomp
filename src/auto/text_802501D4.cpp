// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern "C" {
extern u8 *lbl_8035B65C;
extern u8 *lbl_8035B7BC;
extern void *lbl_8035B79C;
extern void **lbl_8035B334;
extern char lbl_803664A8[4];
void fn_80268014(void *);
void fn_8026B5CC(void *, f32);
void fn_8026D7C0(void *);
u8 *fn_802288FC(void *, char *);
void fn_801E1F94(void *);
} /* extern "C" */
struct V1_8025 { u8 pad[752]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(s32); };
struct V2_8025 { u8 pad[88]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(s32); };
extern "C" {
void fn_802501D4(u8 *p) {
    if (*(s32 *)(p + 36) != 0) {
        *(s32 *)(lbl_8035B65C + 712) = 1;
        if (*(s32 *)(p + 28) != 0) {
            ((V1_8025 *)lbl_8035B65C)->v15(0);
        }
        if (*(u32 *)(p + 52) != 0) {
            (*(V2_8025 **)(lbl_8035B7BC + 40))->v21(0);
            *(s32 *)(p + 60) = 0;
            fn_80268014(lbl_8035B79C);
        }
        fn_8026B5CC(lbl_8035B7BC, **(f32 **)(lbl_8035B7BC + 32));
        fn_8026D7C0(lbl_8035B7BC);
    }
    *(s32 *)(p + 36) = 0;
    if (*(s32 *)(p + 32) != 0) {
        u8 *q = fn_802288FC(*lbl_8035B334, lbl_803664A8);
        *(volatile s32 *)(q + 788) = 0;
    }
    fn_801E1F94(*(void **)(p + 64));
}
}

} /* extern "C" */
