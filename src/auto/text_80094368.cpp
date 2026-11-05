// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern char lbl_80299B08[];
extern void *volatile lbl_8035A0A4;
s32 fn_8003C674(void *, char *, s32 *volatile *);
void fn_80072438(void *, s32);
void fn_80242210(void *);

typedef struct {
    u8 pad0[284];
    s32 *f11C;
    s32 *f120;
    u8 pad124[16];
    void *f134;
    u8 pad138[52];
    s32 f16C;
    s32 f170;
} S80094368;

#pragma scheduling 604
void fn_80094368(S80094368 *p) {
    if (p->f16C != 0) {
s32 *volatile v = 0; s32 *q; if (fn_8003C674(lbl_8035A0A4, lbl_80299B08, &v) == 0) { *v = 0; } q = v; *q += *p->f120;
        p->f16C = 0;
    }
    if (p->f170 != 0) {
        fn_80072438(p->f134, *p->f11C);
        p->f170 = 0;
    }
    fn_80242210(p);
}
#pragma scheduling reset

} /* extern "C" */
