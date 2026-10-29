// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct R { u8 pad_[292]; virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void v4(int); virtual u32 v5(); };
struct P0 { u8 pad_[16]; virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void v6(); };
#define F(p,o,t) (*(t*)((u8*)(p)+(o)))
struct V3 { f32 x, y, z; };
extern u8 lbl_803286D0[];
extern u32 lbl_80364DD0;
void fn_800FB064(R *, char *);
void fn_800FAEF8(R *);
f32 fn_800FB2E0(R *);
void *fn_800F9398(void *, char *);
void *fn_800F9788(void *, char *, char *);
void fn_800F87F0(void *, char *, void *);
void fn_80121CE8(void *, R *);
void fn_80190C98(void *);
static inline void *find(u8 *m, char *g, char *n) { if ((u32)g == 0 || !g[0]) return fn_800F9398(m + 144, n); return fn_800F9788(m + 168, g, n); }
struct PP { P0 h; u8 pad[48 - 0x14]; char n48[8]; char n56[8]; };
#pragma opt_loop_invariants off
void __dt__9C801A4C14Fv(void);
void fn_801A4664(void);
void fn_801A466C(void);
void fn_801A46D4(void);
void fn_801A46D8(void);
int fn_801A480C(PP *p, u8 *a, R *r, void *d);
void fn_801A4AF4(void);
void fn_801A4B54(void);
void fn_801A4F54(void);
void fn_801A4F58(void);
void fn_801A517C(void);
void fn_801A5180(void);
void fn_801A5188(void);
void *lbl_802EA390[15] = { 0, 0, (void *)__dt__9C801A4C14Fv, (void *)fn_801A4AF4, (void *)fn_801A480C, (void *)fn_801A466C, (void *)fn_801A5180, (void *)fn_801A517C, (void *)fn_801A4B54, (void *)fn_801A46D8, (void *)fn_801A5188, (void *)fn_801A4664, (void *)fn_801A4F58, (void *)fn_801A4F54, (void *)fn_801A46D4 };
int fn_801A480C(PP *p, u8 *a, R *r, void *d) {
    u8 *g; u8 *q;
    V3 v64;
    V3 v52;
    V3 v40;
    V3 v28;
    V3 v16;
    char b8[8];
    u32 t;
    u8 *tbl;
    if (F(p,4,int)) p->h.v6();
    F(p,0,u8*) = a;
    fn_800FAEF8(r);
    tbl = lbl_803286D0;
    while ((t = r->v5()) != 6) {
        switch (t) {
        case 57:
            fn_800FB064(r, p->n48);
            fn_800F87F0(d, p->n48, p);
            break;
        case 81:
            fn_800FB064(r, p->n56);
            fn_800FB064(r, b8);
            F(p,36,void*) = find(F(a,12,u8*), b8, p->n56);
            break;
        case 58:
            fn_80121CE8((u8 *)p + 20, r);
            break;
        case 64: {
            v64.x = fn_800FB2E0(r); v64.y = fn_800FB2E0(r); v64.z = fn_800FB2E0(r);
            q = F(p,36,u8*); g = F(q,48,u8*);
            if (g) { (*(void (**)(void *, V3 *))(tbl + 12))(F(g,16,void*), &v64); F(g,32,u32) |= lbl_80364DD0; fn_80190C98(q); }
            F(p,104,int) = 1;
            break;
        }
        case 65: {
            v52.x = fn_800FB2E0(r); v52.y = fn_800FB2E0(r); v52.z = fn_800FB2E0(r);
            v40.x = fn_800FB2E0(r); v40.y = fn_800FB2E0(r); v40.z = fn_800FB2E0(r);
            q = F(p,36,u8*); g = F(q,48,u8*);
            if (g) { (*(void (**)(void *, V3 *, V3 *))(tbl + 44))(F(g,16,void*), &v52, &v40); F(g,32,u32) |= lbl_80364DD0; fn_80190C98(q); }
            F(p,108,int) = 1;
            break;
        }
        case 66: {
            v28.x = fn_800FB2E0(r); v28.y = fn_800FB2E0(r); v28.z = fn_800FB2E0(r);
            v16.x = fn_800FB2E0(r); v16.y = fn_800FB2E0(r); v16.z = fn_800FB2E0(r);
            q = F(p,36,u8*); g = F(q,48,u8*);
            if (g) { (*(void (**)(void *, V3 *, V3 *))(tbl + 48))(F(g,16,void*), &v16, &v28); F(g,32,u32) |= lbl_80364DD0; fn_80190C98(q); }
            F(p,108,int) = 1;
            break;
        }
        default:
            r->v4(30);
            break;
        }
    }
    F(p,4,int) = 1;
    return 0;
}
#pragma opt_loop_invariants reset

} /* extern "C" */
