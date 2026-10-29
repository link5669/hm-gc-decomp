// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
typedef struct { char d[8]; } KeyFD908;
struct RFD908 {
    u8 pad[292];
    virtual void v0();
    virtual void v1();
    virtual void m2(char *s, s32 a, s32 b);
    virtual void v3();
    virtual void v4();
    virtual u32 m5();
};
struct OFD908 {
    u8 pad[12];
    virtual void m0(RFD908 *r, KeyFD908 *k);
};
struct AFD908 {
    u8 pad[16];
    virtual void v0();
    virtual void m1();
    virtual void v2();
    virtual void m3();
    virtual void v4();
    virtual OFD908 *m5(u32 i);
    u32 f20;
};
extern "C" {
extern char lbl_802EF4E0[];
void fn_800FB064(RFD908 *, KeyFD908 *);
u32 fn_800FADA8(RFD908 *);
void fn_800F8E38(AFD908 *, u32);
void fn_801FA7BC(void *, AFD908 *, KeyFD908 *);
void fn_800FB000(RFD908 *, s32);
void fn_800F87F0(AFD908 *, KeyFD908 *, OFD908 *);
void fn_800FAEA0(RFD908 *);
#pragma opt_propagation off
void fn_801FD908(AFD908 *p, void *q0, RFD908 *r) {
    KeyFD908 k16;
    KeyFD908 k8;
    void *q = q0;
    KeyFD908 *name;
    u32 tok;
    OFD908 *o;
    u32 i;
    if (p->f20 != 0) p->m1();
    name = 0;
    r->m2(lbl_802EF4E0, 11, 0);
    while ((tok = r->m5()) != 0) {
        switch ((s32)tok) {
        case 57:
            fn_800FB064(r, &k8);
            name = &k8;
            break;
        case 58: {
            p->f20 = fn_800FADA8(r);
            fn_800F8E38(p, p->f20);
            fn_801FA7BC(q, p, name);
            p->m3();
            for (i = 0; i < p->f20; i++) {
                fn_800FB000(r, 58);
                fn_800FB064(r, &k16);
                o = p->m5(i);
                fn_800F87F0(p, &k16, o);
                o->m0(r, &k16);
            }
            fn_800FAEA0(r);
            return;
        }
        }
    }
}
#pragma opt_propagation reset

} /* extern "C" */
