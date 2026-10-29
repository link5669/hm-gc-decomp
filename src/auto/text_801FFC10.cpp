// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct BitVec_FC10 { u32 *begin; u32 *end; } BitVec_FC10;
extern BitVec_FC10 lbl_8035B160;
typedef struct Obj_FC10 { u8 data[476]; } Obj_FC10;
extern Obj_FC10 lbl_80330CE4[];
void fn_80202C08(Obj_FC10 *);

static inline u32 FindFree_FC10(BitVec_FC10 *bv) {
    u32 w;
    u32 *end;
    u32 *p;
    s32 i;
    end = bv->end;
    for (p = bv->begin; p != end; p++) {
        w = *p;
        if (w != 0xFFFFFFFF) {
            for (i = 0; i < 32; i++) {
                if (!((1 << i) & w)) {
                    return i + (p - bv->begin) * 32;
                }
            }
        }
    }
    return -1;
}

Obj_FC10 *fn_801FFC10(void) {
    u32 idx = FindFree_FC10(&lbl_8035B160);
    Obj_FC10 *o;
    lbl_8035B160.begin[idx >> 5] |= 1 << (idx & ~32);
    o = &lbl_80330CE4[idx];
    fn_80202C08(o);
    return o;
}

} /* extern "C" */
