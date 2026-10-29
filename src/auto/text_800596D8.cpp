// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct P {
    u8 pad0[224];
    void *a224;
    u8 pad228[76];
    s32 *s304;
    s32 *s308;
    u8 pad312[24];
    s32 *s336;
    u8 pad340[12];
    s32 *s352;
    u8 pad356[40];
    s32 i396;
    u8 pad400[20];
    u32 *m420;
    u32 b424;
    u32 b428;
    u32 b432;
};
extern void *lbl_8035A0A4;
extern void *lbl_8035B530;
s32 fn_8003C778(void *, void *, u32 **);
void fn_800604C4(int, int, int, int);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_8022BBF4(void *);
void fn_8022B618(void *);

static inline void setb(P *p, s32 c, u32 m) {
    if (c) *p->m420 |= m;
    else *p->m420 &= ~m;
}

void fn_800596D8(P *p) {
    s32 r = 0;
    if (*p->s352 && p->i396) {
        p->m420 = 0;
        p->i396 = 0;
    }
    if (*p->s352) {
        p->i396 = 1;
        r = fn_8003C778(lbl_8035A0A4, p->a224, &p->m420);
    } else if (!p->m420) {
        if (!lbl_8035B530) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B530);
        p->m420 = new u32;
        fn_800F7E98();
        if (!p->m420) fn_800604C4(-4, 0, 0, 0);
    }
    if (r == 0) {
        setb(p, *p->s336, p->b424);
        setb(p, !*p->s304, p->b428);
        setb(p, !*p->s308, p->b432);
    }
    if (*p->m420 & p->b424) {
        fn_8022BBF4(p->a224);
        setb(p, !*p->s304, p->b428);
        setb(p, !*p->s308, p->b432);
        *p->m420 |= p->b424;
    } else {
        fn_8022B618(p->a224);
        *p->m420 |= p->b428;
        *p->m420 |= p->b432;
        *p->m420 &= ~p->b424;
    }
}

} /* extern "C" */
