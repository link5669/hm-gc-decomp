// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern void *lbl_8035B530;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
struct B { u32 a, b; };
struct Nd { Nd *next; Nd *prev; int v; int f12; };
struct G5DC { u8 pad[20]; int f20; };
extern G5DC lbl_803575DC;
extern char lbl_80361A58[8], lbl_80361B6C[8];
extern f32 lbl_80361B30;
struct L { u8 pad[12]; int f12; u8 pad16[36]; u8 *f52; };
struct S224 { u8 pad[180]; u32 f180; };
struct S192 { u8 pad[4]; int f4; };
struct G308 { u8 pad[72]; void *f72; };
extern G308 *lbl_8035B308;
struct T { u8 pad[192]; S192 *f192; u8 pad196[28]; S224 *f224; u8 pad228[104]; void *f332; L *f336; u8 pad340[20]; int f360; int f364; int f368; u8 pad372[16]; Nd *head; Nd *tail; };
int fn_800F6CD0(void *, const void *);
L *fn_80247AE4(G5DC *, B *);
u32 fn_8024548C(L *, int, int, int, B *, f32 *, B *);
void fn_800F6FBC(const char *, B *);
void fn_8022ADD4(S224 *);
void fn_800A0654(T *t, B *name) {
    t->f364 = -1;
    if (fn_800F6CD0(name, lbl_80361A58) == 0 && lbl_803575DC.f20) t->f336 = fn_80247AE4(&lbl_803575DC, name);
    while (t->head) {
        Nd *n = t->head;
        if (n) {
            if ((t->head = n->next) != 0) t->head->prev = 0;
            else t->tail = 0;
        }
        delete n;
    }
    if (t->f336) {
        int val = -1;
        t->f360 = t->f336->f12;
        for (int i = 0; i < t->f360; i++) {
            t->f336->f52[i] = 0;
            B a[10];
            B c[10];
            f32 b[10];
            u32 cnt = fn_8024548C(t->f336, i, -1, 10, a, b, c);
            B key;
            fn_800F6FBC(lbl_80361B6C, &key);
            for (u32 j = 0; j < cnt; j++) {
                if (fn_800F6CD0(&a[j], &key)) {
                    val = (int)(lbl_80361B30 * b[j]);
                    break;
                }
            }
            if (lbl_8035B530 == 0) fn_800604C4(-2, 0, 0, 0);
            fn_800F7EC0(lbl_8035B530);
            Nd *nd = new Nd;
            fn_800F7E98();
            if (nd == 0) fn_800604C4(-4, 0, 0, 0);
            nd->v = val;
            nd->f12 = 0;
            if (i == 0) {
                if ((nd->next = t->head) != 0) t->head->prev = nd;
                else t->tail = nd;
                t->head = nd;
                nd->prev = 0;
            } else {
                if ((nd->prev = t->tail) != 0) t->tail->next = nd;
                else t->head = nd;
                t->tail = nd;
                nd->next = 0;
            }
        }
    }
    fn_8022ADD4(t->f224);
    t->f224->f180 |= 4;
    t->f368 = t->f192->f4;
    t->f332 = lbl_8035B308->f72;
}

} /* extern "C" */
