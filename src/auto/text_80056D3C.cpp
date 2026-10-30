// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct OV {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void s33(char *, int, int, int, int);
};
struct P {
    u8 pad0[96];
    s32 st96;
    u8 pad100[128];
    OV *o228;
    u8 pad232[4];
    char *s236;
    u8 pad240[68];
    s32 *s308;
    u8 pad312[64];
    u32 *u376;
    u32 *u380;
    u8 pad384[4];
    char *n388;
    char *n392;
    u8 pad396[132];
    OV *o528;
    s32 i532;
    u8 pad536[12];
    u32 c548;
    u8 pad552[12];
    s32 i564;
    u8 pad568[12];
    u32 *m580;
    u8 pad584[4];
    u32 b588;
    u32 b592;
};
extern char lbl_8035E060[4];
extern char lbl_80296838[];
int fn_800F6CD0(char *, char *);
void fn_802494A4(P *, int);
void fn_80056B4C(P *, int);

static inline u8 match(P *p, char *n) {
    u8 r = 0;
    if (fn_800F6CD0(n, lbl_8035E060) || (p->s236 && fn_800F6CD0(p->s236, n))) r = 1;
    return r;
}
static inline void play(P *p) {
    if (p->o228) {
        p->o528 = p->o228;
        p->o528->s33(lbl_80296838, 0, 0, 0, 0);
    }
}

void fn_80056D3C(P *p, s32 a, s32 b, s32 c, s32 d) {
    s32 m;
    u32 v;
    if (p->st96 == 1) {
        u8 r = 0;
        if (fn_800F6CD0(p->n388, lbl_8035E060) || (p->s236 && fn_800F6CD0(p->s236, p->n388))) r = 1;
        m = r;
    } else {
        u8 r = 0;
        if (fn_800F6CD0(p->n392, lbl_8035E060) || (p->s236 && fn_800F6CD0(p->s236, p->n392))) r = 1;
        m = r;
    }
    v = *p->m580;
    if (v & p->b592) return;
    if (b == 0) {
        if (!m) return;
        if (p->i532) return;
        if ((a == 0 || *p->s308 != 0) && c == 0 && d == 0) {
            if (p->c548 < ((v & p->b588) ? *p->u376 : *p->u380)) return;
        }
    }
    if (v & p->b588) {
        p->c548 = 0;
        *p->m580 &= ~p->b588;
        play(p);
        p->i564 = 0;
        if (c) fn_802494A4(p, 3);
        else fn_802494A4(p, 2);
        fn_80056B4C(p, 1);
    } else {
        if (a || b || c || d || *p->s308 == 0) {
            p->c548 = 0;
            *p->m580 |= p->b588;
            play(p);
            p->i564 = 0;
            if (c) fn_802494A4(p, 1);
            else fn_802494A4(p, 4);
            fn_80056B4C(p, 1);
        }
    }
}

} /* extern "C" */
