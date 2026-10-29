// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct A { u8 pad[140]; u8 name[36]; u8 pad176[4]; u32 fl180; u8 pad184[92]; s32 i276; };
struct P {
    u8 pad0[224];
    A *a224;
    u8 pad228[52];
    void *a280;
    u8 pad284[32];
    s32 *s316;
    s32 *s320;
    s32 *s324;
    u8 pad328[68];
    void *a396;
    u8 pad400[16];
    s32 i416;
    u8 pad420[28];
    u32 *m448;
    u32 *m452;
    u32 b456;
    u32 b460;
};
extern void *lbl_8035A0A4;
extern void *lbl_8035B530;
extern char lbl_8035D288[4];
extern char lbl_80295CC8[];
s32 fn_8003C674(void *, void *, u32 **);
s32 fn_8003C778(void *, void *, u32 **);
void fn_800F6E88(char *, u8 *);
void fn_800604C4(int, int, int, int);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void *fn_8023F4A0(P *, char *, char *, char *, int);
void fn_802494A4(P *, int);

static inline void setb(P *p, bool c, u32 m) {
    if (c) *p->m452 |= m;
    else *p->m452 &= ~m;
}
void fn_8004B6B8(P *p) {
    s32 r;
    if (*p->s320 && p->i416) p->m452 = 0;
    r = 0;
    if (*p->s320 && p->a224->i276 == 0) {
        p->i416 = 1;
        if (p->s324 && *p->s324) {
            char buf[8];
            fn_800F6E88(buf, p->a224->name);
            r = fn_8003C674(lbl_8035A0A4, buf, &p->m452);
        } else {
            r = fn_8003C778(lbl_8035A0A4, p->a224, &p->m452);
        }
    } else if (!p->m452) {
        if (!lbl_8035B530) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B530);
        p->m452 = new u32;
        fn_800F7E98();
        if (!p->m452) fn_800604C4(-4, 0, 0, 0);
        p->i416 = 0;
    }
    if (r == 0) {
        bool b = false;
        if (*p->s316 && p->a224->i276 == 0) b = true;
        setb(p, b, p->b456);
        *p->m452 &= ~p->b460;
    } else {
        u32 *m = p->m452;
        if ((*m & p->b460) && (*m & p->b456)) *m &= ~p->b456;
    }
    if (fn_8003C674(lbl_8035A0A4, p->a280, &p->m448) == 0) *p->m448 = 0;
    p->a396 = fn_8023F4A0(p, lbl_8035D288, lbl_8035D288, lbl_80295CC8, 1);
    p->a224->fl180 |= 4;
    if (p->a224->i276 == 0) {
        if (*p->m452 & p->b456) fn_802494A4(p, 3);
        else fn_802494A4(p, 1);
    }
}

} /* extern "C" */
