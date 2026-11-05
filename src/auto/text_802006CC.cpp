// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=1.3 */
typedef struct BV6CC { u32 *begin; u32 *end; } BV6CC;
extern BV6CC lbl_8035B160;
extern u32 lbl_8034E8E4[9];
typedef struct { u32 f0; u32 f4; s32 f8; u8 pad[188]; u32 f200; } S6CC;
void fn_801FE890(u32 *p);
void fn_801FE894(u32 *p);
void fn_802006CC(S6CC *p) {
    u32 *b;
    u32 *e;
    if (p->f8 != 0) {
        p->f200 = 0;
        fn_801FE890(&p->f4);
    }
    b = lbl_8034E8E4;
    lbl_8035B160.begin = b;
    e = b + 8;
    lbl_8035B160.end = e;
    for (; b != e; b++) *b = 0;
    fn_801FE894(&p->f4);
    p->f200 = 0;
}

} /* extern "C" */
