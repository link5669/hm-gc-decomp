// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct R { u8 pad[8]; s32 f8; void set(s32 v) { f8 = v; } };
struct V { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual R *get(s32 i); };
struct E52 { u8 pad[48]; s32 f48; void set(s32 v) { f48 = v; } };
struct G { u8 pad[24]; V *f24; u8 pad2[104-28]; s32 f104; u8 pad3[112-108]; E52 *f112;
  R *r() { return f24->get(f104); } E52 *cur() { return &f112[f104]; } };
extern "C" {
extern G *lbl_8035B5E4;
extern f32 lbl_8035C1C0;
void fn_80253304(E52 *e, s32 n, f32 f);
s32 fn_8003C4BC(void *a, u8 *b) {
    if ((*(u32 *)(b + 324) >> 16) == 2) {
        lbl_8035B5E4->r()->set(1);
        lbl_8035B5E4->cur()->set(0);
        fn_80253304(lbl_8035B5E4->cur(), 500, lbl_8035C1C0);
    } else {
        lbl_8035B5E4->r()->set(0);
        lbl_8035B5E4->cur()->set(1);
    }
    return 1;
}

} /* extern "C" */
