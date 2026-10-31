// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct V3 { f32 x, y, z; };
#define VF(n) virtual void v##n();
struct H156 { u8 pad[120]; void *f120; u8 pad2[28]; u32 f152; };
struct A224 { VF(0) VF(1) VF(2) VF(3) VF(4) VF(5) VF(6) VF(7) VF(8) VF(9) VF(10) VF(11) VF(12) VF(13) VF(14) VF(15)
    VF(16) VF(17) VF(18) VF(19) VF(20) VF(21) VF(22) VF(23) virtual void f24(); u8 pad[152]; H156 *f156; };
struct O528 { VF(0) VF(1) VF(2) VF(3) VF(4) VF(5) VF(6) VF(7) VF(8) VF(9) VF(10) VF(11) VF(12) VF(13) VF(14) VF(15)
    VF(16) VF(17) VF(18) VF(19) VF(20) VF(21) VF(22) VF(23) VF(24) VF(25) VF(26) VF(27) VF(28) VF(29) VF(30) VF(31) VF(32)
    virtual void f33(void *, A224 *, int, int, int); };
struct O572 { u8 pad[104]; VF(0) VF(1) VF(2) VF(3) VF(4) VF(5) VF(6) VF(7) VF(8) VF(9) VF(10) virtual void f11(f32); };
struct P { u8 pad[96]; s32 f96; u8 pad2[124]; A224 *f224; u8 pad3[8]; u32 f236; u8 pad4[80]; s32 *f320; s32 *f324; s32 *f328;
    s32 *f332; s32 *f336; u8 pad5[16]; s32 *f356; u8 pad6[28]; u32 f388; u32 f392; u8 pad7[16]; s32 *f412; u8 pad8[16];
    s32 *f432; u8 pad9[68]; s32 f504; s32 f508; u8 pad10[8]; s32 f520; s32 f524; O528 *f528; s32 f532; u8 pad11[16];
    s32 f552; s32 f556; u8 pad12[4]; s32 f564; u8 pad13[4]; O572 *f572; u8 pad14[4]; u32 *f580; u32 f584; };
extern "C" {
extern u32 lbl_8035E194;
extern f32 lbl_8035E1A0;
extern u8 lbl_8035E164[4];
void fn_8005748C(P *, s32);
int fn_8022C558(A224 *);
void fn_8022B618(A224 *);
void fn_8022A7A8(A224 *);
void fn_80107F3C(void *, V3 *);
void fn_8023FE08(P *, f32);
void fn_80056D3C(P *, int, int, int, int);
void fn_80056590(P *);
void fn_800567F0(P *p, f32 dt) {
    if (p->f556) { fn_8005748C(p, p->f96 - 1); return; }
    if (!(*p->f580 & p->f584) && fn_8022C558(p->f224)) {
        s32 a, c, b;
        a = *p->f432;
        b = *p->f332;
        c = *p->f336;
        if (a) {
            if (a) p->f224->f156->f152 |= lbl_8035E194;
        } else if (*p->f324) {
            p->f224->f24();
        }
        *p->f580 &= ~p->f584;
        if (b) fn_8022B618(p->f224);
        if (c) fn_8022A7A8(p->f224);
        if (p->f572 && *p->f412) {
            V3 v;
            void *h;
            v.z = v.y = v.x = lbl_8035E1A0;
            h = p->f224->f156->f120;
            if (h) fn_80107F3C(h, &v);
        }
        fn_8023FE08(p, dt);
        return;
    }
    fn_8023FE08(p, dt);
    if (p->f532) return;
    if (p->f96 != 1 && p->f96 != 3) return;
    if (p->f564 == 0) {
        O528 *o = p->f528;
        if (o && (void *)o != (void *)p->f224) o->f33(lbl_8035E164, p->f224, 0, 0, 0);
        p->f528 = 0;
        p->f564 = 1;
    }
    if (*p->f320) {
        s32 x = p->f524;
        if (x && p->f96 == 1) { p->f236 = p->f388; fn_80056D3C(p, 0, 0, 0, 1); return; }
        if (!x && p->f96 == 3) { p->f236 = p->f392; fn_80056D3C(p, 0, 1, 0, 1); return; }
    }
    if (*p->f356 && p->f552) {
        s32 x = p->f504;
        if ((x && p->f96 == 1) || (!x && p->f508 && p->f96 == 3)) { fn_80056D3C(p, 1, 0, 0, 0); return; }
    }
    if (p->f520) { p->f236 = p->f392; fn_80056D3C(p, 0, 1, 0, 0); return; }
    if (p->f572 && *p->f412) {
        fn_80056590(p);
        p->f572->f11(dt);
    }
}

} /* extern "C" */
