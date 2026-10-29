// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct S80090970 {
    u8 pad[284];
    u32 f284;
    u32 f288;
    u32 f292;
    u32 f296;
    u32 f300;
    u32 f304;
    u32 f308;
    u32 f312;
    u32 f316;
    u32 f320;
    u32 f324;
} S80090970;

u32 fn_8023F52C(S80090970 *p, char *a, char *b, char *name, s32 c, s32 d);
void fn_8023F214(S80090970 *p);
extern char lbl_802995A8[];
extern char lbl_80360740[4];
extern char lbl_80360970[7];
extern char lbl_80360978[5];

#pragma opt_propagation off
void fn_80090970(S80090970 *p) {
    char *str = lbl_802995A8;
    p->f284 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 288, 1, 0);
    p->f288 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 304, 1, 0);
    p->f292 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 320, 1, 0);
    p->f296 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 332, 1, 0);
    p->f300 = fn_8023F52C(p, lbl_80360740, lbl_80360740, lbl_80360970, 0, 0);
    p->f304 = fn_8023F52C(p, lbl_80360740, lbl_80360978, str + 348, 1, 0);
    p->f308 = fn_8023F52C(p, lbl_80360740, lbl_80360978, str + 364, 1, 0);
    p->f312 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 380, 1, 0);
    p->f316 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 396, 1, 0);
    p->f320 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 412, 1, 0);
    p->f324 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 424, 0, 0);
    fn_8023F214(p);
}
#pragma opt_propagation reset

} /* extern "C" */
