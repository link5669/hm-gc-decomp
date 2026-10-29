// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern "C" {
extern void *lbl_8035A9F4;
extern char lbl_80365850[4];
extern char lbl_80365854[4];
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_80207E5C(void *, char *);
} /* extern "C" */
struct C8020F398 { u8 pad[20]; C8020F398(); };
struct V8021 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void m(void *, char *, C8020F398 *); };
extern "C" {
C8020F398 *fn_80211820(u8 *p, char *name) {
    C8020F398 *o;
    if (lbl_8035A9F4 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035A9F4);
    o = new C8020F398;
    fn_800F7E98();
    if (o == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    fn_80207E5C(p, lbl_80365850);
    if (name == 0) {
        name = lbl_80365854;
    }
    (*(V8021 **)(p + 1760))->m(p + 128, name, o);
    return o;
}
}

} /* extern "C" */
