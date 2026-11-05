// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V801638D4 { u8 pad[6448]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); };
extern "C" {
typedef struct { u8 r, g, b, a; } C801638D4;
typedef struct { u8 pad[162268]; C801638D4 c; } D801638D4;

void fn_801638D4(V801638D4 *p, const C801638D4 *c) {
    if (M2C_FIELD(p, u32 *, 12) & 2) {
        p->v30();
        M2C_FIELD(p, D801638D4 **, 6452)->c = *c;
    }
}

} /* extern "C" */
