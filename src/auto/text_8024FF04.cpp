// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { s32 a, b, c; } T_8024FF04;
typedef struct { u8 pad[8]; u8 name[24]; s32 flag; u8 pad2[4]; } E_8024FF04;
extern T_8024FF04 lbl_802F20B8;
extern T_8024FF04 lbl_802F20C4;
extern void *lbl_8035B65C;
extern char lbl_80366498[8];
s32 fn_800F6CD0(void *, char *);
void fn_80253A48(void *, void *, void *, void *);
void fn_80253AD8(void *, void *, void *, void *);

static inline void *getmgr_8024FF04(void) { return lbl_8035B65C; }
void fn_8024FF04(u8 *p) {
    void *mgr;
    u32 i;
    mgr = getmgr_8024FF04();
    for (i = *(u32 *)(p + 8) - *(u32 *)(p + 12); i < *(u32 *)(p + 8); i++) {
        if (fn_800F6CD0((*(E_8024FF04 **)(p + 16))[i].name, lbl_80366498) == 0) {
            if ((*(E_8024FF04 **)(p + 16))[i].flag != 0) {
                T_8024FF04 t = lbl_802F20B8;
                fn_80253A48(mgr, p, &t, (*(E_8024FF04 **)(p + 16))[i].name);
            } else {
                T_8024FF04 t = lbl_802F20C4;
                fn_80253AD8(mgr, p, &t, (*(E_8024FF04 **)(p + 16))[i].name);
            }
        }
    }
    *(u32 *)(p + 8) = *(u32 *)(p + 8) - *(u32 *)(p + 12);
    *(u32 *)(p + 12) = 0;
}

} /* extern "C" */
