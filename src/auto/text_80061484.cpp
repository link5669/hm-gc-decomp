// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct Xo { u8 pad[6448]; virtual void x0(); virtual void x1(); virtual void x2(); virtual void set(u32, s32, s32);
    virtual void x4(); virtual void x5(); virtual void x6(); virtual void x7(); virtual void x8(); virtual void x9(); virtual void x10(); virtual void x11(); virtual void x12(); virtual void x13(); virtual void x14(); virtual void x15(); virtual void x16(); virtual void x17(); virtual void x18(); virtual void x19();
    virtual void x20(); virtual void x21(); virtual void x22(); virtual void x23(); virtual void x24(); virtual void x25(); virtual void x26(); virtual void x27(); virtual void x28(); virtual void x29();
    virtual void x30(); virtual void x31(); virtual void x32(); virtual void x33(); virtual void x34(); virtual void x35(); virtual void x36(); virtual void x37(); virtual void x38(); virtual void x39();
    virtual void x40(); virtual void x41(); virtual void x42(); virtual void x43(); virtual void x44(); virtual void x45(); virtual void x46(); virtual void x47(); virtual void x48(); virtual void x49();
    virtual void x50(); virtual void x51(); virtual void x52(); virtual void x53(); virtual void x54(); virtual void x55(); virtual void x56(); virtual void x57(); virtual void x58(); virtual void x59();
    virtual void x60(); virtual void x61(); virtual void flush(); };
struct Gm { u8 pad[672]; virtual void g0(); virtual void g1(); virtual void g2(); virtual void g3(); virtual void g4(); virtual void g5(); virtual void g6(); virtual void g7(); virtual void g8(); virtual void g9();
    virtual void g10(); virtual void g11(); virtual void g12(); virtual void g13(); virtual void g14(); virtual void g15(); virtual void g16(); virtual void g17(); virtual void g18(); virtual void g19();
    virtual void g20(); virtual void g21(); virtual void g22(); virtual void g23(); virtual void g24(); virtual void g25(); virtual void g26(); virtual void g27(); virtual void g28(); virtual void g29();
    virtual void g30(); virtual void g31(); virtual void g32(); virtual void g33(); virtual void g34(); virtual void g35(); virtual void g36(); virtual void g37(); virtual void g38(); virtual void end();
    u8 pad2[11344 - 676]; Xo *x; u8 pad3[13552 - 11348]; u32 f13552; s32 f13556; s32 f13560; u8 pad4[13616 - 13564]; u8 f13616[4]; };
struct Pop { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual s32 input(u32); };
struct G2 { u8 pad[452]; Pop *pop; };
struct Ctx { s32 on; u8 pad[60]; };
extern "C" {
extern Gm *lbl_8035A1DC;
extern G2 *lbl_8035B684;
extern Ctx lbl_80356DAC;
extern s32 lbl_8035A1E0;
extern s8 lbl_8035A1E4;
extern char *lbl_803592A4[2];
extern char *lbl_803592AC;
extern char *lbl_803592B0[2];
extern char *lbl_803592B8;
extern const f32 lbl_8035E608, lbl_8035E60C, lbl_8035E610, lbl_8035E614, lbl_8035E618, lbl_8035E61C;
void fn_802196E0(Ctx *, f32, f32, f32, f32, const char *, ...);
void fn_8021962C(Ctx *);
void fn_8003AF34(void *, s32, s32);

s32 fn_80061484(u32 btn) {
    s32 on;
    if (lbl_8035A1DC->f13556 && lbl_8035B684->pop) return lbl_8035B684->pop->input(btn);
    if (btn & 2) return 2;
    if (lbl_80356DAC.on) {
        Xo *x;
        Gm *g;
        u32 k;
        if (!lbl_8035A1E4) { lbl_8035A1E0 = 0; lbl_8035A1E4 = 1; }
        on = 0;
        if (btn & 8) {
            on = 1;
            fn_802196E0(&lbl_80356DAC, lbl_8035E608, lbl_8035E60C, lbl_8035E610, lbl_8035E610, lbl_803592A4[0]);
            fn_802196E0(&lbl_80356DAC, lbl_8035E614, lbl_8035E618, lbl_8035E610, lbl_8035E610, lbl_803592A4[1]);
        } else if (btn & 0x10) {
            on = 1;
            fn_802196E0(&lbl_80356DAC, lbl_8035E61C, lbl_8035E60C, lbl_8035E610, lbl_8035E610, lbl_803592AC);
        } else if (btn & 0x20) {
            on = 1;
            fn_802196E0(&lbl_80356DAC, lbl_8035E608, lbl_8035E60C, lbl_8035E610, lbl_8035E610, lbl_803592B0[0]);
            fn_802196E0(&lbl_80356DAC, lbl_8035E61C, lbl_8035E618, lbl_8035E610, lbl_8035E610, lbl_803592B0[1]);
        } else if (btn & 0x40) {
            on = 1;
            fn_802196E0(&lbl_80356DAC, lbl_8035E61C, lbl_8035E60C, lbl_8035E610, lbl_8035E610, lbl_803592B8);
        }
        x = (g = lbl_8035A1DC)->x;
        k = g->f13552;
        if (on) {
            x->set(k, 7, 0);
            fn_8021962C(&lbl_80356DAC);
            x->flush();
            g->end();
        } else if (lbl_8035A1E0 && g->f13560 != -1) {
            fn_8003AF34(g->f13616, g->f13560, 5000);
        } else if (lbl_8035A1E0) {
            x->set(k, 7, 0);
            x->flush();
            g->end();
        }
        lbl_8035A1E0 = on;
    }
    return 0;
}

} /* extern "C" */
