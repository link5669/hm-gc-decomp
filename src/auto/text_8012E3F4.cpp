#include "common.h"
extern "C" {
struct C8012E79C { C8012E79C(); u32 d[6]; };
struct Rec { u32 w, h, x, y, x2, y2; };
struct GT { u32 a[16]; u32 b[16]; Rec r[64]; };
// The unit owns .bss 8032A490-8032BD10. lbl_8032A510 is the 256-entry array that the sinit fn_8012EE9C
// constructs (it refers to it by name), so these are globals with the original sizes.
u32 lbl_8032A490[16];
u32 lbl_8032A4D0[16];
Rec lbl_8032A510[256];
extern u32 lbl_80363F08;
extern void *lbl_8035ABE0;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void *memcpy(void *, const void *, u32);

struct Tex {
    u8 pad0[20];
    u32 flags;     /* 20 */
    u8 pad1[80];
    s32 f68;       /* 104 */
    s32 f6c;       /* 108 */
    s32 f70;       /* 112 */
    virtual void v0();
    virtual u32 w(u16);  /* 12 */
    virtual u32 h(u16);  /* 16 */
    virtual u32 w2(u16); /* 20 */
    virtual u32 h2(u16); /* 24 */
};
struct Src { u8 pad[52]; Tex *tex; };
struct Q { u16 f0; u16 id; };
struct Tiler {
    u8 pad0[16];
    u16 w;   /* 16 */
    u16 h;   /* 18 */
    u8 pad1[6];
    u16 n;   /* 26 */
    u8 pad2[16];
    C8012E79C *tiles; /* 44 */
    u8 pad3[8];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual u32 split(u32, u32, u16, Q *, u32 *); /* 24 */
};

inline u32 GetFlags(Tex *t, u32 g)
{
    u32 f = t->flags;
    if (t->f68) { f &= ~0x01000000; f |= g; }
    if (t->f6c && !t->f70) f &= ~0x02000000;
    return f;
}

inline u32 Shift(Tex *t, u32 g, u32 v, u32 lim)
{
    u32 n;
    if (!(GetFlags(t, g) & 0x00100000)) return 0;
    n = 0;
    while (v < lim) { v <<= 1; n++; }
    if (n > 3) return n - 3;
    return 0;
}

void fn_8012E3F4(Tiler *t, Src *s, Q *q)
{
    u32 g;
    u16 id = q->id;
    Tex *tex = s->tex;
    u32 v, sh, bh, aw, hrem, wrem, yoff, xoff, cnt, j, i, ny, nx;
    Rec *r;
    nx = t->split(tex->w(id), tex->h(id), t->w, q, lbl_8032A490);
    ny = t->split(tex->w2(id), tex->h2(id), t->h, q, lbl_8032A4D0);
    hrem = t->h;
    yoff = 0;
    cnt = 0;
    for (j = 0; j < ny; j++) {
        wrem = t->w;
        g = *(volatile u32 *)&lbl_80363F08;
        xoff = 0;
        for (i = 0; i < nx; i++) {
            aw = lbl_8032A490[i];
            bh = lbl_8032A4D0[j];
            lbl_8032A510[cnt].x = xoff;
            lbl_8032A510[cnt].y = yoff;
            if (aw > bh) {
                sh = Shift(tex, g, bh, aw);
                lbl_8032A510[cnt].w = aw;
                v = bh << sh;
                lbl_8032A510[cnt].h = v;
                if (wrem < lbl_8032A490[i]) lbl_8032A510[cnt].x2 = xoff + wrem; else lbl_8032A510[cnt].x2 = xoff + lbl_8032A490[i];
                if (hrem < v) lbl_8032A510[cnt].y2 = yoff + hrem; else lbl_8032A510[cnt].y2 = yoff + v;
            } else {
                sh = Shift(tex, g, aw, bh);
                v = aw << sh;
                lbl_8032A510[cnt].w = v;
                lbl_8032A510[cnt].h = lbl_8032A4D0[j];
                if (wrem < v) lbl_8032A510[cnt].x2 = xoff + wrem; else lbl_8032A510[cnt].x2 = xoff + v;
                if (hrem < lbl_8032A4D0[j]) lbl_8032A510[cnt].y2 = yoff + hrem; else lbl_8032A510[cnt].y2 = yoff + lbl_8032A4D0[j];
            }
            cnt++;
            wrem -= lbl_8032A490[i];
            xoff += lbl_8032A490[i];
        }
        hrem -= lbl_8032A4D0[j];
        yoff += lbl_8032A4D0[j];
    }
    t->n = cnt;
    if (!lbl_8035ABE0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035ABE0);
    t->tiles = new C8012E79C[t->n];
    fn_800F7E98();
    if (!t->tiles) fn_800604C4(-4, 0, 0, 0);
    memcpy(t->tiles, lbl_8032A510, t->n * 24);
}
}
