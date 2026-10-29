// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct O7C3BC {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void m39(void *a, s32 b, char *c, char *d, f32 e);
};
extern "C" {
typedef struct { char d[8]; } Key7C3BC;
typedef struct { u8 pad[12]; Key7C3BC *f12; } KA7C3BC;
typedef struct { u8 pad[12]; f32 *f12; } FA7C3BC;
typedef struct { s32 f0; } S7C3BC;
typedef struct {
    u8 pad0[224];
    void *f224;
    u8 pad228[60];
    S7C3BC *f288;
    void *f292;
    KA7C3BC *f296;
    FA7C3BC *f300;
    s32 f304;
    s32 f308;
    s32 f312;
    s32 f316;
    u32 f320;
    u32 f324;
    s32 f328;
} P7C3BC;
extern void *lbl_8035B374;
extern char lbl_8035F8E8[4];
extern f32 lbl_8035F8EC;
void fn_800F6E88(void *, void *);
O7C3BC *fn_80233550(void *, Key7C3BC *);
void fn_8023F5E8(P7C3BC *, s32);
void fn_8024118C(P7C3BC *, void *, s32);
void fn_802490E0(P7C3BC *, s32, f32);
void fn_8023FE08(P7C3BC *, f32);
inline BOOL chk7C3BC(P7C3BC *p) {
    return p->f304 != 0 && (p->f312 != 0 || p->f288->f0 != 0);
}
void fn_8007C3BC(P7C3BC *p, f32 dt) {
    if (p->f316 != 0) {
        if (p->f308 != 0 && p->f320 != 0) {
            Key7C3BC k;
            O7C3BC *o;
            fn_800F6E88(&k, &p->f296->f12[p->f324]);
            o = fn_80233550(lbl_8035B374, &k);
            if (o) {
                if (p->f304 == 0 || (p->f304 != 0 && (p->f312 != 0 || p->f288->f0 != 0))) {
                    fn_8023F5E8(p, p->f328);
                } else {
                    fn_8023F5E8(p, 0);
                }
                if (p->f292 != 0) fn_8024118C(p, p->f292, 0);
                o->m39(p->f224, 0, lbl_8035F8E8, lbl_8035F8E8, lbl_8035F8EC);
            }
            p->f324 = (p->f324 + 1) % p->f320;
            if (p->f308 != 0 && p->f320 != 0) {
                fn_802490E0(p, 0, p->f300->f12[p->f324]);
            }
            p->f316 = 0;
        } else {
            p->f316 = 1;
        }
    }
    fn_8023FE08(p, dt);
}

} /* extern "C" */
