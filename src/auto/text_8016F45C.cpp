// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct T48 { u8 b[48]; };
struct TV { u8 b[48]; };
struct SS { u8 pad[1216]; s32 bl[4]; u32 a1232; u32 a1236; TV tev[16]; };
struct TT { u8 pad[44]; u32 fl44; };
struct C { u8 pad[6452]; TT *t6452; SS *s6456; u8 pad6460[396]; void *a6856; };
struct M12 { u8 pad[72]; u8 n72; };
struct M { u16 fl0; u16 a2; T48 *ent; void *a8; M12 *m12; u16 a16; u16 n18; u16 b20, b22, b24; };
extern u32 lbl_80364714;
void fn_80174E2C(TV *, int, int);
void fn_80175090(TV *, TT *, T48 *, int);
void fn_80174EA4(TV *, int);
void fn_80174E70(TV *, int);
void fn_80174CB8(TV *);
void fn_800D61A0(u8);
void fn_800D95E8(u8);
void fn_800D9958(s32, s32, s32, s32);
void fn_801636E8(C *, void *);
void fn_80161244(void *, C *);
void fn_80163A18(C *);

static inline void setBlend(SS *s, s32 a, s32 b, s32 c, s32 d) {
    if (s->bl[0] != a || s->bl[1] != b || s->bl[2] != c || s->bl[3] != d) {
        s->bl[0] = a;
        s->bl[1] = b;
        s->bl[2] = c;
        s->bl[3] = d;
        fn_800D9958(s->bl[0], s->bl[1], s->bl[2], s->bl[3]);
    }
}

void fn_8016F45C(M *m, C *c) {
    SS *s = c->s6456;
    TT *t = c->t6452;
    u32 i;
    if (!m->m12) {
        fn_80174E2C(&s->tev[0], 0, 0);
        for (i = 0; i < m->n18; i++) {
            fn_80175090(&s->tev[i], t, &m->ent[i], 0);
            fn_80174EA4(&s->tev[i], 12);
            fn_80174E70(&s->tev[i], 28);
        }
    } else {
        for (i = 0; i < m->n18; i++) fn_80175090(&s->tev[i], t, &m->ent[i], 1);
        for (; i < m->m12->n72; i++) fn_80174CB8(&s->tev[i]);
    }
    if (m->a2 != s->a1232) {
        s->a1232 = m->a2;
        fn_800D61A0(s->a1232);
    }
    if (m->n18 != s->a1236) {
        s->a1236 = m->n18;
        fn_800D95E8(s->a1236);
    }
    if (m->fl0 & 1) t->fl44 |= lbl_80364714;
    else t->fl44 &= ~0x800;
    if ((int)m->a16 != 0) setBlend(s, m->b20, m->b22, m->b24, 3);
    else setBlend(s, 0, 1, 0, 3);
    if (m->a8) fn_801636E8(c, m->a8);
    if (m->m12) {
        if (c->a6856) fn_80161244(c->a6856, c);
        else fn_80161244(m->m12, c);
    } else {
        fn_80163A18(c);
    }
}

} /* extern "C" */
