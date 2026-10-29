// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct R80250FA4 { u32 pad0; u32 eof; u8 pad8[0x11C]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual u32 next(); };
struct P80250FA4 { u8 pad[0x14]; u8 key[8]; char name[256]; u8 flags; u8 pad285[3]; u32 v; u32 pad292; u32 f296; u8 *res; };
typedef struct { u32 a; u32 b; u32 c; u32 d; } Z80250FA4;
extern char lbl_803664FC[4];
extern u8 *lbl_8035B460;
extern void *volatile lbl_8035B818;
s32 fn_800FB33C(R80250FA4 *);
void fn_800FB2E0(R80250FA4 *);
void fn_800FB064(R80250FA4 *, void *);
char *fn_800FB1F8(R80250FA4 *, s32);
s32 fn_800F6CD0(void *, void *);
void *fn_800F9398(void *, void *);
void *fn_800F9788(void *, char *, void *);
void fn_800F6E88(void *, void *);
char *strcpy(char *, const char *);
void fn_80272AD0(void *, char *, volatile Z80250FA4 *, s32, s32);
void fn_8023D1BC(P80250FA4 *);

static inline void find80250FA4(u8 *t, char *grp, void *key) {
    if (grp == 0 || grp[0] == 0) {
        fn_800F9398(t + 60, key);
    } else {
        fn_800F9788(t + 84, grp, key);
    }
}

void fn_80250FA4(P80250FA4 *p, void *key, R80250FA4 *r, u32 v) {
    volatile Z80250FA4 z;
    u8 nm[8];
    char grp[8];
    if (fn_800FB33C(r) == 1) {
        p->flags |= 2;
    }
    fn_800FB33C(r);
    if (fn_800FB33C(r) == 1) {
        fn_800FB2E0(r);
    }
    fn_800FB064(r, nm);
    fn_800FB064(r, grp);
    p->res = *(u8 **)(*(u8 **)(lbl_8035B460 + 12) + 11340);
    if (fn_800F6CD0(nm, lbl_803664FC) == 0) {
        find80250FA4(p->res, grp, nm);
    }
    { char *s = fn_800FB1F8(r, 256); strcpy(p->name, s); }
    fn_800F6E88(p->key, key);
    p->flags |= 1;
    p->v = v;
    if (r->next() != 59) {
        r->eof = 1;
    }
    if (r->next() == 61) {
        p->f296 = 1;
    } else {
        p->f296 = 0;
        r->eof = 1;
    }
    z.a = 0;
    z.b = 0;
    fn_80272AD0(lbl_8035B818, p->name, &z, -1, 0);
    fn_8023D1BC(p);
}

} /* extern "C" */
