// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct {
    u8 req[0x20];
    s32 busy;
} ArqSlot;

extern ArqSlot lbl_80356920[32];
extern volatile u32 lbl_8035B19C;
void fn_800C4EBC(void);
void DCFlushRange(void *addr, u32 len);
void fn_800C6D6C(void *req, u32 owner, u32 type, u32 prio, u32 src, u32 dst, u32 len, void *cb);
void fn_802079CC(void *req);
static inline void alloc(void **req, u32 *idx) {
    u32 i;
    for (i = 0; i < 32; i++) {
        if (lbl_80356920[i].busy == 0) {
            *req = &lbl_80356920[i];
            lbl_80356920[i].busy = 1;
            *idx = i;
            break;
        }
    }
}
void fn_80207510(u32 dst, void *src, s32 len0) {
    u32 len = len0;
    void *req;
    u32 idx;
    while (lbl_8035B19C != 0) fn_800C4EBC();
    DCFlushRange(src, len);
    lbl_8035B19C = 1;
    req = 0;
    alloc(&req, &idx);
    fn_800C6D6C(req, idx, 0, 1, (u32)src, dst, len, (void *)fn_802079CC);
    while (lbl_8035B19C != 0) fn_800C4EBC();
}

} /* extern "C" */
