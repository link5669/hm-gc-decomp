// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct G8003B87C {
    u8 pad[6448];
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(u32 a, s32 b, s32 c);
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61();
    virtual void v62();
    virtual void v63(u8 *color);
};
struct R8003B87C {
    u8 pad[80];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(G8003B87C *g);
};
struct S8003B87C {
    u8 pad[48];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(s32 a);
};
struct T8003B87C {
    u8 pad[56];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11();
};
extern "C" {
extern u8 *lbl_8035A02C;
extern u8 *lbl_8035A1DC;
extern const f32 lbl_8035C178;
extern const f32 lbl_8035C170;
void fn_80039E80(u8 *p, s32 a, f32 f);
s32 fn_800FBB9C(void);
void fn_80039EA4(u8 *p, f32 f);
void fn_80039F78(u8 *p, G8003B87C *g);

void fn_8003B87C(u8 *self, s32 flag) {
    u8 *g;
    s32 start;
    u8 color[4];
    if (flag != 0) {
        fn_80039E80(lbl_8035A02C, 1, lbl_8035C178);
        start = fn_800FBB9C();
        while (*(s32 *)(lbl_8035A02C + 32) != 0) {
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;
            color[3] = 255;
            (*(G8003B87C **)(self + 24))->v63(color);
            (*(G8003B87C **)(self + 24))->v3(*(u32 *)(self + 4), 7, 0);
            (*(R8003B87C **)(self + 32))->v4(*(G8003B87C **)(self + 24));
            (*(G8003B87C **)(self + 24))->v62();
            g = lbl_8035A02C;
            fn_80039EA4(g, (f32)(fn_800FBB9C() - start) / lbl_8035C170);
            start = fn_800FBB9C();
            fn_80039F78(lbl_8035A02C, *(G8003B87C **)(self + 24));
            (*(S8003B87C **)(lbl_8035A1DC + 11340))->v8(1);
        }
    }
    if (*(T8003B87C **)(self + 40) != 0) {
        (*(T8003B87C **)(self + 40))->v11();
        *(T8003B87C **)(self + 40) = 0;
    }
    if (*(T8003B87C **)(self + 36) != 0) {
        (*(T8003B87C **)(self + 36))->v11();
        *(T8003B87C **)(self + 36) = 0;
    }
}

} /* extern "C" */
