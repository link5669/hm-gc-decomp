// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct P {
    u8 pad0[16];
    u32 w16;
    u32 h20;
    u32 a24;
    u16 a28;
    u8 fmt30[26];
    u32 a56;
    u8 pad60[1280];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void s4();
    u8 pad1344[4];
    u32 a1348;
    u8 *a1352;
    s32 a1356;
    u8 t1360;
    u8 b1361;
    u8 c1362;
    u8 pad1363;
    u32 a1364;
};
extern char lbl_802A01C8[], lbl_802A01EC[];
void fn_801486B4(P *, char *);
void fn_8014824C(u16 *, u32, u32, int, int);
void fn_80148288(u16 *, u32, u32, u32, u32, u32, int);
void fn_80148210(u16 *, u32, u32, int, int);
void fn_80060568(char *, int, int, int);
void fn_8014BC1C(P *, u8 *);

static inline u32 rd32(u8 *b) { return b[0] + (b[1] << 8) + (b[2] << 16) + (b[3] << 24); }
void fn_8014C1A4(P *p, u8 *h) {
    u8 *data;
    u32 bpp;
    if (p->a28) p->s4();
    data = h + 21;
    p->w16 = h[0] + (h[1] << 8);
    p->h20 = h[2] + (h[3] << 8);
    bpp = (u8)(h[4] + (h[5] << 8));
    p->a56 = h[6] + (h[7] << 8);
    p->a24 = rd32(h + 8);
    p->a1348 = rd32(h + 12);
    p->t1360 = h[16];
    p->b1361 = h[17];
    p->c1362 = h[18];
    p->a1364 = h[19] + (h[20] << 8);
    switch (p->t1360) {
    case 0:
        fn_801486B4(p, lbl_802A01C8);
        break;
    case 1:
        fn_8014824C(&p->a28, bpp, (1 << bpp) - 1, 0, 0);
        p->a1356 = 0;
        break;
    case 2:
        switch (bpp) {
        case 16:
            fn_80148288(&p->a28, bpp, 0x7C00, 0x3E0, 0x1F, 0x8000, 0);
            break;
        case 24:
            fn_80148288(&p->a28, bpp, 0xFF0000, 0xFF00, 0xFF, 0, 0);
            break;
        case 32:
            fn_80148288(&p->a28, bpp, 0xFF00, 0xFF0000, 0xFF000000, 0xFF, 0);
            break;
        default:
            fn_80060568(lbl_802A01EC, 0, 0, 0);
            break;
        }
        p->a1356 = 0;
        break;
    case 3:
        fn_80148210(&p->a28, bpp, (1 << bpp) - 1, 0, 0);
        p->a1356 = 0;
        break;
    default:
        fn_801486B4(p, lbl_802A01C8);
        break;
    }
    fn_8014BC1C(p, data);
    data += ((p->b1361 + 7) >> 3) * p->a56;
    p->a1352 = data;
}

} /* extern "C" */
