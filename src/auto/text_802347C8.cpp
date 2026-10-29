// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct Q { u8 pad[104]; virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3(); virtual void q4(); virtual void q5(); virtual void q6(); virtual void q7(); virtual void q8(); virtual void q9(); virtual void q10(); virtual void upd(f32); };
struct O { virtual void o0(); virtual void o1(); virtual void o2(); virtual void o3(); virtual void kill(); u8 pad4[152]; Q *f156; u8 pad160[20]; u32 f180; };
struct P76 { u8 pad[676]; int f676; };
struct G308 { u8 pad[76]; P76 *f76; };
extern G308 *lbl_8035B308;
extern f32 lbl_80365E88;
extern char lbl_80365EA0[8];
struct T { virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3(); virtual void t4(); virtual void t5(); virtual void t6(); virtual void t7(); virtual void t8(); virtual void t9(); virtual void t10(); virtual void t11(); virtual void t12(); virtual void t13(); virtual void t14(); virtual void t15(); virtual void t16(); virtual void t17(); virtual void t18(); virtual void t19(); virtual void t20(); virtual void t21(); virtual void t22(); virtual void t23(); virtual void t24(); virtual void t25(); virtual void t26(); virtual void t27(); virtual void t28(); virtual void t29(); virtual void t30(); virtual void t31(); virtual void t32(); virtual void say(const char *, int, int, int, int); u8 pad4[520]; void *f524; u8 pad528[68]; O *f596[100]; int *f996; u8 pad1000[4]; f32 *f1004; u8 pad1008[44]; int f1052; int f1056; f32 f1060; int f1064; int f1068; u8 pad1072[4]; int f1076; };
int fn_8022A0BC(void *);
void fn_80234028(T *, int, int, int);
void fn_80238618(T *, f32);
void fn_802347C8(T *t, f32 dt) {
    int i;
    int all = 1;
    for (i = 0; i < *t->f996; i++) {
        O *o = t->f596[i];
        if (o) {
            if (o->f180 & 2) {
                if (lbl_8035B308->f76->f676 == 0) {
                    if (fn_8022A0BC(o)) {
                        t->f596[i]->f156->upd(dt);
                        all = 0;
                    } else {
                        t->f596[i]->kill();
                        t->f1052--;
                        t->f1064--;
                        t->f596[i] = 0;
                    }
                }
            } else {
                o->kill();
                t->f1052--;
                t->f596[i] = 0;
            }
        }
    }
    if (t->f1076 == 1 && all == 1) {
        t->f1076 = 0;
        t->say(lbl_80365EA0, 0, 0, 0, 0);
    }
    if (fn_8022A0BC(t)) {
        if ((t->f1068 || t->f1056 > 0) && t->f1060 > lbl_80365E88) {
            t->f1060 = t->f1060 - dt;
            if (t->f1060 < lbl_80365E88) {
                t->f1060 = *t->f1004;
                if (t->f1052 < *t->f996) fn_80234028(t, 0, 0, 0);
            }
        }
        if (t->f524) fn_80238618(t, dt);
    }
}

} /* extern "C" */
