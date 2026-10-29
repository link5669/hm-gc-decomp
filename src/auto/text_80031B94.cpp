// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_8010344C(void *);
void fn_80222BE8(void *);
extern void *lbl_802F069C[];
} /* extern "C" */
struct C80031B94 {
    u32 f0;
    C80031B94() { fn_8010344C(this); }
    ~C80031B94();
};
struct D80031B94 : C80031B94 {
    void **vt;
    u32 f8;
    void *f12;
    void *f16;
    D80031B94() { vt = lbl_802F069C; fn_80222BE8(this); }
};
extern "C" {
struct E60_80031B94 { u8 pad[12]; D80031B94 *f12; u8 pad16[44]; };
struct E_80031B94 { u8 pad[60]; u32 f60; u8 pad64[108]; u32 f172; E60_80031B94 *f176; u8 pad180[24]; };
struct M_80031B94 { u8 pad[120]; u32 f120; u8 pad124[64]; E_80031B94 *f188; };
struct N_80031B94 { u8 pad[88]; u16 f88; u8 pad90[18]; u16 f108; };
struct R_80031B94 { u32 f0; };
struct S_80031B94 { u8 pad[3004]; u32 f3004; D80031B94 *arr[20]; };
struct B_80031B94 { u8 b[16]; };
extern u8 *lbl_8035B7C8;
extern void *lbl_8035B658;
N_80031B94 *fn_80180E7C(N_80031B94 *, u32);
M_80031B94 *fn_80180E9C(N_80031B94 *, u32);
void fn_800F806C(M_80031B94 *, E_80031B94 *, B_80031B94 *);
R_80031B94 *fn_800F9398(void *, B_80031B94 *);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);

void __ct__9C80031B94Fi(S_80031B94 *self, N_80031B94 *node) {
    R_80031B94 *r;
    E_80031B94 *e;
    u32 off;
    u32 j;
    u32 k;
    M_80031B94 *m;
    u32 i;
    u32 l;
    D80031B94 *x;
    B_80031B94 buf;
    if (node == 0) return;
    for (i = 0; i < node->f108; i++) {
        __ct__9C80031B94Fi(self, fn_80180E7C(node, i));
    }
    for (j = 0; j < node->f88; j++) {
        m = fn_80180E9C(node, j);
        for (k = 0, off = 0; k < m->f120; off += 204, k++) {
            e = (E_80031B94 *)((u8 *)m->f188 + off);
            if (e->f60 == 0) {
                fn_800F806C(m, e, &buf);
                r = fn_800F9398(lbl_8035B7C8 + 132, &buf);
                if (r != 0 && (r->f0 & 4) && self->f3004 < 20) {
                    if (lbl_8035B658 == 0) fn_800604C4(-2, 0, 0, 0);
                    fn_800F7EC0(lbl_8035B658);
                    self->arr[self->f3004] = new D80031B94;
                    fn_800F7E98();
                    if (self->arr[self->f3004] == 0) fn_800604C4(-4, 0, 0, 0);
                    x = self->arr[self->f3004];
                    x->f12 = e;
                    x->f16 = r;
                    for (l = 0; l < e->f172; l++) {
                        e->f176[l].f12 = self->arr[self->f3004];
                    }
                    self->f3004++;
                }
            }
        }
    }
}

} /* extern "C" */
