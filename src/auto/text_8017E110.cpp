// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct S17E { u8 pad[0xc]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void go();
  virtual void q7(); virtual void q8(); virtual void q9(); virtual void q10(); virtual void q11(); virtual void q12(); virtual void q13(); virtual void q14();
  virtual void q15(); virtual void q16(); virtual void q17(); virtual void q18(); virtual void q19(); virtual void q20(); virtual void q21(); virtual void load(void *, s32); };
struct P17E { u32 f0; };
S17E *fn_801320AC(u32, u32);
extern u32 lbl_80330258[4];
extern u32 lbl_8035ADB8;

u8 *fn_8017E110(P17E *p, u32 key, s32 idx) {
    if (key != lbl_8035ADB8 || lbl_80330258[0] == 0) {
        if (lbl_80330258[0] != 0) {
            fn_801320AC(p->f0, lbl_8035ADB8)->go();
        }
        lbl_8035ADB8 = key;
        fn_801320AC(p->f0, key)->load(lbl_80330258, 0);
    }
    return (u8 *)(lbl_80330258[0] + idx * lbl_80330258[1]);
}

} /* extern "C" */
