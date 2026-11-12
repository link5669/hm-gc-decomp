// fn_8003F1E0: schedule- and register-equivalent (schedequiv.txt; saved wave-42 draft): two instructions of the
// case-12 length block are in another order and FP temporaries are renamed.
#include "common.h"

struct V3 { f32 x, y, z; };
class C802449C4 { public: u8 d[56]; C802449C4(); ~C802449C4(); };
#define V(n) virtual void n();
class Cam { public: V(c0) V(c1) V(c2) V(c3) V(c4) V(c5) V(c6) V(c7) V(c8) V(c9) V(c10) V(c11) V(c12)
    virtual void get(V3 *, int, int, int, int); virtual void set(void *, int, int, int, int);
    u8 pad[276]; V3 f280; u8 p292[48]; f32 f340; };
struct St { u8 p[20]; u32 f20; };
class O { public: V(o0) V(o1) V(o2) V(o3) V(o4) V(o5) V(o6) V(o7) V(o8) V(o9) V(o10) V(o11) V(o12) V(o13) V(o14) V(o15) V(o16) V(o17)
    virtual void v80(); virtual void v84();
    u8 p4[92]; s32 f96; u8 p100[124]; Cam *f224; u8 p228[36]; void *f264; u8 p268[32]; void *f300; u8 p304[44]; u8 f348[12]; s32 f360; u8 p364[12]; f32 *f376; s32 f380; };
extern "C" {
extern u8 lbl_8035C248[];
extern u8 lbl_8035C250[];
extern u8 lbl_8035C254[];
extern const char lbl_80294EB0[];
extern u8 lbl_8035C25C[];
extern u8 lbl_8035C264[];
extern u8 lbl_8035C26C[];
extern u8 lbl_8035C274[];
extern u8 lbl_8035C27C[];
extern u8 lbl_8035C284[];
extern u8 lbl_8035C28C[];
extern u8 lbl_8035C294[];
extern u8 lbl_8035C29C[];
extern u8 lbl_8035C2A4[];
extern u8 lbl_8035C2AC[];
extern const char lbl_80294EBC[];
extern const char lbl_80294EC8[];
extern u8 lbl_8035C2B4[];
extern u8 lbl_8035C2BC[];
extern const char lbl_80294ED4[];
extern u8 lbl_8035C2C4[];
void fn_8003F8CC(void);
void fn_80249AC4(void);
void fn_8003F87C(void);
void fn_80040960(void);
void fn_8003F850(void);
void fn_8023D198(void);
void fn_8003FA68(void);
extern "C" void fn_8003F1E0(O *o, s32 idx);
void fn_80241D80(void);
void fn_8003F140(void);
void fn_8003F18C(void);
void fn_8003F768(void);
void fn_8003F700(void);
void fn_80040ABC(void);
void fn_8003F1DC(void);
void fn_80240054(void);
void fn_8023F5F4(void);
void fn_8003F734(void);
void fn_800408D4(void);
void fn_8003FC58(void);
extern f32 lbl_8035C2CC, lbl_8035C2D0, lbl_8035C2E8;
extern f64 lbl_8035C2D8, lbl_8035C2E0;
int rand(void);
void fn_80241628(O *, int, int);
void fn_80240DBC(O *, f32);
void fn_8003FB70(O *);
St *fn_80242144(O *, int);
void fn_80242BC0(St *, char *, int, int, int, int);
void fn_8003FBF0(O *, void *, int);
void fn_80240D70(O *, int);
void fn_802494A4(O *, int);
void fn_8003FD24(O *, int);
void fn_80040274(O *);
void fn_80040570(O *);
void fn_802448C8(C802449C4 *, St *);
void fn_80244750(C802449C4 *, int);
Cam *fn_8024457C(C802449C4 *);
void fn_80244594(C802449C4 *);
void fn_80101820(V3 *);
void fn_80248514(void *, int, f32);
}
// The unit owns .data 802B0498-802B095C: the descriptor tables (taken from jt_802AFF20, filled from the DOL,
// pointers as relocations), the walker tables tI/tB/tS, the class vtable and the switch jump table.
__declspec(section ".data") u8 lbl_802B0498[276] = { 0, 0, 0, 0, 0, 0, 0, 0xFA, 0, 0, 1, 0xF4, 0, 0, 2, 0xEE, 0x55, 0x49, 0x5C, 0x4D, 0x45, 0x4D, 0x43, 0x41, 0x52, 0x44, 0x5C, 0, 0x41, 0x54, 0x54, 0x49, 0x43, 0, 0, 0, 0x42, 0x41, 0x4C, 0x4C, 0x52, 0x4F, 0x4F, 0x4D, 0x43, 0x48, 0x49, 0x4C, 0x44, 0x52, 0x45, 0x4E, 0x43, 0x4F, 0x4E, 0x53, 0x45, 0x52, 0x56, 0, 0x44, 0x49, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x46, 0x4F, 0x59, 0x45, 0x52, 0, 0, 0, 0x47, 0x41, 0x4C, 0x4C, 0x45, 0x52, 0x59, 0, 0x47, 0x52, 0x41, 0x56, 0x45, 0x59, 0x44, 0, 0x47, 0x52, 0x4F, 0x4F, 0x4D, 0, 0, 0, 0x47, 0x52, 0x54, 0x48, 0x41, 0x4C, 0x4C, 0, 0x47, 0x55, 0x45, 0x53, 0x54, 0, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x41, 0x42, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x43, 0x44, 0, 0, 0x4B, 0x49, 0x54, 0x43, 0x48, 0x45, 0x4E, 0, 0x4C, 0x41, 0x42, 0, 0, 0, 0, 0, 0x4D, 0x55, 0x53, 0x45, 0x55, 0x4D, 0, 0, 0x4D, 0x41, 0x49, 0x44, 0, 0, 0, 0, 0x4D, 0x41, 0x53, 0x54, 0x52, 0x42, 0x45, 0x44, 0x4D, 0x41, 0x55, 0x53, 0x4F, 0x4C, 0x4D, 0, 0x4D, 0x45, 0x41, 0x53, 0x55, 0x52, 0x45, 0, 0x54, 0x4F, 0x59, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x4F, 0x42, 0x53, 0x45, 0x52, 0x56, 0, 0, 0x50, 0x41, 0x4E, 0x54, 0x52, 0x59, 0, 0, 0x50, 0x41, 0x52, 0x4C, 0x4F, 0x52, 0, 0, 0x53, 0x49, 0x54, 0x54, 0x49, 0x4E, 0x47, 0, 0x53, 0x54, 0x52, 0x45, 0x54, 0x43, 0x48, 0, 0x53, 0x55, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x57, 0x49, 0x4E, 0x54, 0x45, 0x52, 0, 0, 0x54, 0x49, 0x54, 0x4C, 0x45, 0, 0, 0, 0x53, 0x50, 0x49, 0x52, 0x49, 0x54, 0, 0, 0x47, 0x4C, 0x4F, 0x42, 0x41, 0x4C, 0, 0 };
__declspec(section ".data") u8 lbl_802B05AC[264] = { 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0xBF, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0xBF, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0x40, 0, 0, 0, 0x43, 0, 0, 0, 0x46, 0, 0, 0, 0x49, 0, 0, 0, 0x4C, 0, 0, 0, 0x4F, 0, 0, 0, 0x52, 0, 0, 0, 0x55, 0, 0, 0, 0x1E, 0, 0, 0, 0x21, 0, 0, 0, 0x24, 0, 0, 0, 0x27, 0, 0, 0, 0x2A, 0, 0, 0, 0x2D, 0, 0, 0, 0x30, 0, 0, 0, 0x33 };
static __declspec(section ".data") void *sPad_21C[32] = { (void *)lbl_8035C248, (void *)lbl_8035C248, (void *)lbl_8035C250, (void *)lbl_8035C250, (void *)lbl_8035C254, (void *)lbl_80294EB0, (void *)lbl_8035C250, (void *)lbl_8035C250, (void *)lbl_8035C25C, (void *)lbl_8035C264, (void *)lbl_8035C26C, (void *)lbl_8035C250, (void *)lbl_8035C250, (void *)lbl_8035C274, (void *)lbl_8035C250, (void *)lbl_8035C250, (void *)lbl_8035C250, (void *)lbl_8035C27C, (void *)lbl_8035C284, (void *)lbl_8035C28C, (void *)lbl_8035C294, (void *)lbl_8035C29C, (void *)lbl_8035C2A4, (void *)lbl_8035C2AC, (void *)lbl_80294EBC, (void *)lbl_80294EBC, (void *)lbl_80294EC8, (void *)lbl_8035C2B4, (void *)lbl_8035C2BC, (void *)lbl_80294ED4, (void *)lbl_8035C2C4, (void *)lbl_8035C29C };
static __declspec(section ".data") u8 sPad_29C[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_2A4[1] = { (void *)lbl_8035C2A4 };
static __declspec(section ".data") u8 sPad_2A8[8] = { 0, 0, 0, 1, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_2B0[1] = { (void *)lbl_8035C2AC };
static __declspec(section ".data") u8 sPad_2B4[8] = { 0, 0, 0, 2, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_2BC[1] = { (void *)lbl_80294EBC };
static __declspec(section ".data") u8 sPad_2C0[8] = { 0, 0, 0, 3, 0, 0, 0, 2 };
static __declspec(section ".data") void *sPad_2C8[1] = { (void *)lbl_80294EC8 };
static __declspec(section ".data") u8 sPad_2CC[8] = { 0, 0, 0, 5, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_2D4[1] = { (void *)lbl_8035C2B4 };
static __declspec(section ".data") u8 sPad_2D8[8] = { 0, 0, 0, 6, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_2E0[1] = { (void *)lbl_8035C2BC };
static __declspec(section ".data") u8 sPad_2E4[8] = { 0, 0, 0, 7, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_2EC[1] = { (void *)lbl_80294ED4 };
static __declspec(section ".data") u8 sPad_2F0[8] = { 0, 0, 0, 8, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_2F8[1] = { (void *)lbl_8035C2C4 };
static __declspec(section ".data") u8 sPad_2FC[48] = { 0, 0, 0, 9, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 8, 0, 0, 0, 9 };
static __declspec(section ".data") s32 tI[10] = { 0, 4, 6, 0xA, 0xC, 0xE, 0x10, 0x12, 0x15, 0x17 };
static __declspec(section ".data") s32 tB[27] = { 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 2, 1, 3, 1, 1, 1, 1, 1 };
static __declspec(section ".data") s32 tS[27] = { 0, 1, 2, 3, 4, 5, 6, 7, 6, 7, 8, 7, 9, 7, 0xA, 7, 0xA, 7, 7, 0xB, 7, 0xC, 7, 0xD, 7, 0xE, 7 };
__declspec(section ".data") u8 lbl_802B08C4[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *fill_802B08CC[20] = { (void *)fn_8003F8CC, (void *)fn_80249AC4, (void *)fn_8003F87C, (void *)fn_80040960, (void *)fn_8003F850, (void *)fn_8023D198, (void *)fn_8003FA68, (void *)fn_8003F1E0, (void *)fn_80241D80, (void *)fn_8003F140, (void *)fn_8003F18C, (void *)fn_8003F768, (void *)fn_8003F700, (void *)fn_80040ABC, (void *)fn_8003F1DC, (void *)fn_80240054, (void *)fn_8023F5F4, (void *)fn_8003F734, (void *)fn_800408D4, (void *)fn_8003FC58 };
// The TU string pool (.rodata 80294E98-80294F04) in its original order; the entries other units refer to
// by name are globals, the code addresses the rest relative to the first one.
extern const char lbl_80294E98[];
const char lbl_80294E98[] = "MStation";
extern const char lbl_80294EA4[];
const char lbl_80294EA4[] = "MFalling";
extern const char lbl_80294EB0[];
const char lbl_80294EB0[] = "BillBall";
extern const char lbl_80294EBC[];
const char lbl_80294EBC[] = "STRT_COL";
extern const char lbl_80294EC8[];
const char lbl_80294EC8[] = "BOUNCSND";
extern const char lbl_80294ED4[];
const char lbl_80294ED4[] = "FAKESINK";
static const char sEE0[] = "BALLMOVE";
static const char sEEC[] = "BALLSUNK";
static const char sEF8[12] = "BALLSTOP";   // padded: the pool ends at 80294F04
inline f32 Sq(f32 x) {
    volatile f32 y;
    f64 g = __frsqrte(x);
    g = lbl_8035C2D8 * g * (lbl_8035C2E0 - g * g * x);
    g = lbl_8035C2D8 * g * (lbl_8035C2E0 - g * g * x);
    g = lbl_8035C2D8 * g * (lbl_8035C2E0 - g * g * x);
    y = x * g;
    return y;
}
extern "C" void fn_8003F1E0(O *o, s32 idx) {
    s32 *q;
    s32 i;
    s32 t;
    i = tI[idx];
    t = o->f96;
    q = &tB[i];
    while (t > 0) {
        if (*q > t) break;
        t -= tB[i++];
        q++;
    }
    switch (tS[i]) {
    case 0:
        fn_80241628(o, 0, 0);
        o->v80();
        break;
    case 1:
        fn_80240DBC(o, lbl_8035C2CC);
        fn_80241628(o, 0, 0);
        fn_8003FB70(o);
        break;
    case 2:
        fn_80241628(o, 1, 0);
        fn_80242BC0(fn_80242144(o, 2), (char *)sEE0, 0, 0, 0, 0);
        fn_8003FBF0(o, o->f300, 1);
        break;
    case 3:
        fn_80241628(o, 0, 0);
        fn_80242BC0(fn_80242144(o, 2), (char *)sEEC, 0, 0, 0, 0);
        fn_80240D70(o, -1);
        break;
    case 4:
        fn_80241628(o, 0, 0);
        o->f380 = 0;
        if (!o->f360) o->f224->set(o->f348, 0, 0, 0, 0);
        o->f360 = 1;
        o->v80();
        break;
    case 5:
        o->f380 = 0;
        o->f360 = 1;
        o->f224->set(o->f348, 0, 0, 0, 0);
        fn_802494A4(o, 0);
        break;
    case 6:
        fn_802494A4(o, 1);
        break;
    case 7:
        return;
    case 8:
        fn_8003FD24(o, 1);
        break;
    case 9:
        fn_8003FD24(o, 0);
        break;
    case 10:
        fn_80040274(o);
        break;
    case 11:
        o->v84();
        fn_802494A4(o, 3);
        break;
    case 12: {
        u32 n, k, j;
        fn_80241628(o, 1, 0);
        n = fn_80242144(o, 3)->f20;
        if (!n) {
            o->v84();
            fn_802494A4(o, 3);
            break;
        }
        k = 0;
        if (n) k = rand() % n;
        {
            C802449C4 it;
            fn_802448C8(&it, fn_80242144(o, 3));
            fn_80244750(&it, 0);
            for (j = 0; j < k; j++) fn_80244594(&it);
            n = (u32)fn_8024457C(&it);
            if (n) {
                Cam *x = (Cam *)n;
                V3 d, b, a;
                f32 f, l;
                o->f224->get(&a, 0, 0, 0, 0);
                x->get(&b, 0, 0, 0, 0);
                d.x = b.x - a.x; d.y = b.y - a.y; d.z = b.z - a.z;
                fn_80101820(&d);
                *(volatile f32 *)&d.x = d.x * *o->f376; *(volatile f32 *)&d.y = d.y * *o->f376; *(volatile f32 *)&d.z = d.z * *o->f376;
                { f32 xy = d.x * d.x + d.y * d.y; l = xy + d.z * d.z; }
                { f32 k = *(volatile f32 *)&lbl_8035C2D0; if (l > k) l = Sq(l); }
                { Cam *c = o->f224; c->f280.x = d.x; c->f280.y = d.y; c->f280.z = d.z; c->f340 = l; }
                fn_802494A4(o, 2);
            }
        }
        break;
    }
    case 13:
        fn_80040570(o);
        break;
    case 14:
        if (!o->f360) {
            fn_80242BC0(fn_80242144(o, 2), (char *)sEF8, 0, 0, 0, 0);
            if (o->f264) fn_80248514(o->f264, 0, lbl_8035C2E8);
        }
        break;
    case 15:
        break;
    }
}
