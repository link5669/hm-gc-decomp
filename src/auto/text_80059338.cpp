// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

#include "common.h"
struct V { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
  virtual void v30(); virtual void v31(); virtual void v32(); virtual void play(void *, void *, void *, void *, void *); };
struct G308 { u8 pad[72]; V *v72; };
struct O {
    u8 pad[224]; V *p224; V *p228; u8 pad2[48]; void *f280; u8 pad3[4]; char *s288; u8 pad4[4]; void *f296; u8 pad5[12];
    s32 *p312; u8 pad6[4]; s32 *p320; s32 *p324; u8 pad7[16]; s32 *p344; s32 *p348; u8 pad8[4]; char *s356; u8 pad9[4]; s32 *p364;
    u8 pad10[12]; s32 *p380; s32 *p384; f32 *p388; f32 *p392; u8 pad11[8]; s32 f404; s32 f408; s32 f412; s32 f416; u32 *p420; u32 m424; u32 m428; u32 m432;
};
extern "C" {
extern G308 *lbl_8035B308;
extern void *lbl_8035A0A4;
extern void *lbl_8035B79C;
extern void *lbl_8035B65C;
extern char lbl_8035E1F8[4];
extern char lbl_8035E264[7];
extern const f32 lbl_8035E26C;
s32 fn_8003C930(void *);
int rand(void);
void fn_8022B618(V *);
s32 fn_800F6CD0(char *, char *);
void fn_8024118C(O *, void *, s32);
void fn_8026820C(void *, s32);
void *fn_80242144(O *, s32);
void fn_80242BC0(void *, void *, void *, s32, char *, s32);
void __ct__9C80253F24Fiiii(void *, void *, void *, s32, char *);
void fn_802490E0(O *, s32, f32);
}
static inline bool inRange(O *o, s32 v) {
    bool r = false;
    if (v >= *o->p380 && v <= *o->p384) r = true;
    return r;
}
static inline char *sel(O *o) {
    if (fn_800F6CD0(o->s288, lbl_8035E1F8) == 0) return o->s288;
    return 0;
}
extern "C" {
void fn_80059338(O *o, s32 a, s32 b) {
    s32 hit;
    if (o->p228 && o->p228 == lbl_8035B308->v72) {
        o->f412 = 1;
        o->f416 = 1;
        if (*o->p348 && !o->f404) return;
    } else {
        o->f416 = 0;
    }
    if (*o->p420 & o->m428) return;
    if (!inRange(o, fn_8003C930(lbl_8035A0A4))) return;
    { s32 n = (u32)rand() % 10000; hit = lbl_8035E26C * n <= *o->p388; }
    if (*o->p312) *o->p420 |= o->m428;
    if ((*o->p420 & o->m428) && (*o->p420 & o->m432)) {
        fn_8022B618(o->p224);
        *o->p420 |= o->m428;
        *o->p420 |= o->m432;
        *o->p420 &= ~o->m424;
    }
    if (*o->p324 && o->p228 != o->p224 && hit) o->p228->play(o->f280, 0, 0, sel(o), 0);
    if (a) return;
    if (o->f416 && *o->p348 && !o->f404 && !o->f408) return;
    fn_8024118C(o, o->f296, 0);
    if (*o->p364) fn_8026820C(lbl_8035B79C, 3);
    if (fn_800F6CD0(o->s356, lbl_8035E1F8) == 0) lbl_8035B308->v72->play(lbl_8035E264, o->p224, 0, 0, o->s356);
    if (!hit) return;
    if (b) {
        if (*o->p320) {
            __ct__9C80253F24Fiiii(lbl_8035B65C, o->f280, o->p224, 0, sel(o));
        } else {
            fn_80242BC0(fn_80242144(o, 1), o->f280, o->p224, 0, o->s288, 0);
            if (*o->p344) fn_80242BC0(fn_80242144(o, 2), o->f280, o->p224, 0, o->s288, 0);
        }
    } else {
        fn_802490E0(o, 1, *o->p392);
    }
}
}

} /* extern "C" */
