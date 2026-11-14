#include "common.h"
extern "C" {
struct C8023C7CC {
    u8 pad[8];
    void *a;
    void *b;
    u8 pad2[16];
    C8023C7CC();
    ~C8023C7CC();
};
struct V_80228D7C;
struct VT_80228D7C { void *p[7]; s32 (*m5)(V_80228D7C *); };
struct V_80228D7C { virtual void p0(); virtual void p1(); virtual void p2(); virtual void m3(); virtual void p4(); virtual s32 m5(); };
typedef struct {
    u8 pad[0x48];
    s32 f48;
    s32 f4c;
    C8023C7CC *f50;
    s32 f54;
    s32 f58;
    s32 f5c;
} S80228D7C;
void fn_8023C720(C8023C7CC *, void *);
void fn_8023C528(C8023C7CC *, s32);
void *fn_8023A490(void *, void *);
void fn_8023C3F4(C8023C7CC *);
void fn_8023C754(C8023C7CC *);
void fn_80225F58(void *, void *);
void fn_802356C8(void *);
void fn_80236628(void *);
void fn_8022F2A0(void *);
void fn_80233CE8(void *);
void fn_8023CC40(void *);
extern u8 *lbl_8035B65C;
extern void *lbl_8035B388;
extern void *lbl_8035B39C;
extern void *lbl_8035B34C;
extern void *lbl_8035B374;

void fn_80228D7C(S80228D7C *p) {
    if (p->f50 != NULL) {
        {
        C8023C7CC it;
        V_80228D7C *o;
        fn_8023C720(&it, p);
        o = 0;
        fn_8023C528(&it, 0);
        while (it.a != NULL) {
            if (o != NULL) {
                if (o->m5() != 0) {
                    p->f54--;
                    fn_80225F58(*(void **)(lbl_8035B65C + 0x70), o);
                }
                o->m3();
            }
            o = (V_80228D7C *)(it.a != NULL ? fn_8023A490(it.a, it.b) : NULL);
            fn_8023C3F4(&it);
        }
        }
        fn_8023C754(p->f50);
        delete p->f50;
    }
    fn_802356C8(lbl_8035B388);
    fn_80236628(lbl_8035B39C);
    fn_8022F2A0(lbl_8035B34C);
    fn_80233CE8(lbl_8035B374);
    p->f48 = 0;
    p->f50 = 0;
    p->f54 = 0;
    p->f58 = 0;
    p->f5c = 0;
    fn_8023CC40(p);
}
}
