// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct A801B1764 { u8 pad_[128]; virtual void s0(); };
#define F(p,o,t) (*(t*)((u8*)(p)+(o)))
struct Arr801B1764 { int a; u32 b; u32 c; };
struct V2_801B1764 { f32 x, y; };
extern "C" {
extern f32 lbl_803596E0[];
extern f32 lbl_8035AF50;
extern f32 lbl_8035AF54;
void fn_801B1D54(A801B1764 *, u32);
int fn_801CCC7C(void *, int *, u8 **, u32, int);
void fn_8012CD20(void *, f32 *, Arr801B1764 *, u32, V2_801B1764 *, int, int, f32, f32, f32);
u32 fn_800FA8F4(Arr801B1764 *);
static inline bool inRect(f32 x, f32 y, f32 *r) { bool b = false; if (x >= r[0] && x <= r[2] && y >= r[1] && y <= r[3]) b = true; return b; }
int fn_801B1764(A801B1764 *p, f32 x) {
    Arr801B1764 *v;
    u32 i;
    void *o;
    f32 py;
    f32 lx;
    f32 px;
    switch (F(p,0x144,s32)) {
    case 128:
        if (F(p,0x168,int) == 0) {
        int a;
        u8 *b;
        u32 idx;
        a = 0;
        if (!fn_801CCC7C(F(p,0x70,void*), &a, &b, F(p,0x144,u32), F(p,0x68,int))) idx = 0;
        else {
            o = F(b,0x24,void*);
            if (!o) idx = 0;
            else {
                f32 *q = (f32 *)(F(F(p,0x70,u8*),0xc,u8*) + F(p,0x178,u32) * 16);
                V2_801B1764 pos;
                px = F(p,0x48,f32) + q[0];
                pos.x = px;
                py = F(p,0x4c,f32) + q[1];
                pos.y = py;
                lx = x - F(p,0x1a0,f32);
                if (lx < px) idx = 0;
                else {
                    F(p,0x18c,Arr801B1764*)->b = F(p,0x180,u32);
                    for (i = 0; i < F(p,0x18c,Arr801B1764*)->c - F(p,0x18c,Arr801B1764*)->b; i++) {
                        f32 r[4];
                        fn_8012CD20(o, r, F(p,0x18c,Arr801B1764*), i, &pos, 0, 17, lbl_803596E0[0], lbl_8035AF50, lbl_8035AF54);
                        if (inRect(lx, py, r)) break;
                    }
                    v = F(p,0x18c,Arr801B1764*);
                    v->b = 0;
                    v->c = fn_800FA8F4(v);
                    idx = i + F(p,0x180,u32);
                }
            }
        }
        fn_801B1D54(p, idx);
        }
        break;
    }
    return 0;
}

} /* extern "C" */
