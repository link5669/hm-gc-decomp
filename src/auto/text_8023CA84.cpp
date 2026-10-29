// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern "C" {
typedef struct {
    u32 f0;
    u8 pad4[16];
} T_8023CA84;

typedef struct It_8023CA84 {
    u8 pad0[4];
    u8 f4[8];
    u8 fC[8];
    struct It_8023CA84 *f14;
    struct It_8023CA84 *f18;
} It_8023CA84;
} /* extern "C" */

struct C8023A51C {
    u32 cnt; u32 grow; s32 f8; u8 pad[4]; u32 f16; u8 *items; C8023A51C *next; void *f28;
    C8023A51C();
    ~C8023A51C();
};

struct P_8023CA84 {
    T_8023CA84 table;
    u8 name[8];
    u32 f1C;
    struct P_8023CA84 *f20;
    It_8023CA84 *f24;
    C8023A51C *arr;
    T_8023CA84 table2;
    struct P_8023CA84 *next;
};

extern "C" {
extern T_8023CA84 lbl_8035758C;
extern void *lbl_8035B428;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_8023BB0C(P_8023CA84 *, void *);
void fn_800F6E88(void *, void *);
P_8023CA84 *fn_800F8274(T_8023CA84 *, void *);
void fn_800F8E38(T_8023CA84 *, u32);
void fn_800F87F0(T_8023CA84 *, void *, void *);
void fn_8023A444(C8023A51C *, u32, void *, void *);

void fn_8023CA84(P_8023CA84 *p, void *name) {
    P_8023CA84 *q;
    It_8023CA84 *it;
    u32 i;
    u8 buf[8];

    fn_8023BB0C(p, name);
    q = 0;
    if (lbl_8035758C.f0 != 0) {
        q = fn_800F8274(&lbl_8035758C, name);
    } else {
        fn_800F8E38(&lbl_8035758C, 50);
    }
    if (q == 0) {
        fn_800F87F0(&lbl_8035758C, name, p);
    } else {
        while (q->next != 0) {
            q = q->next;
        }
        q->next = p;
    }
    if (lbl_8035B428 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035B428);
    p->arr = new C8023A51C[p->f1C];
    fn_800F7E98();
    if (p->arr == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    it = p->f24;
    fn_800F8E38(&p->table2, p->f1C * 10 / 7);
    for (i = 0; it != 0; it = it->f18, i++) {
        fn_800F6E88(buf, it->fC);
        fn_8023A444(&p->arr[i], 0, buf, p);
        fn_800F87F0(&p->table2, buf, &p->arr[i]);
    }
}
} /* extern "C" */

} /* extern "C" */
