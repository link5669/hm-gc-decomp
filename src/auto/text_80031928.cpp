// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct L80031928 {
    u32 count;
};
struct A80031928 {
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
    virtual L80031928 **v23(s32 id);
};
struct B80031928 {
    u8 pad0[192];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3(char *buf, s32 n);
};
struct O80031928 {
    u8 pad0[128];
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
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59(s32 a, s32 b);
};
extern "C" {
typedef struct X80031928 {
    u8 pad0[1248];
    s32 f1248;
    s32 f1252;
    u8 pad1256[312];
    s32 f1568;
} X80031928;
typedef struct G80031928 {
    u8 pad0[72];
    X80031928 *f72;
} G80031928;
typedef struct H80031928 {
    u8 pad0[10224];
    u32 f10224;
} H80031928;
typedef struct M80031928 {
    u8 pad0[24];
    A80031928 *f24;
    u8 pad28[76];
    s32 f104;
} M80031928;
typedef struct K80031928 {
    u8 pad0[13232];
    void *f13232;
} K80031928;
typedef struct J80031928 {
    u8 pad0[36];
    K80031928 *f36;
} J80031928;
typedef struct S80031928 {
    u8 pad0[120];
    void *f120;
    u8 pad124[4];
    void *f128;
    u8 pad132[8];
    u32 f140;
    u8 pad144[1928];
    u8 f2072[860];
    s32 *f2932;
    u8 pad2936[4];
    s32 f2940;
} S80031928;
extern G80031928 *lbl_8035B308;
extern H80031928 *lbl_8035B488;
extern M80031928 *lbl_8035B5E4;
extern B80031928 *lbl_8035B684;
extern J80031928 *lbl_8035B65C;
extern char lbl_8035BDA0[6];
extern char lbl_8035BDA8[6];
extern char lbl_8035BDB0[7];
extern char lbl_802947C8[9];
extern char lbl_802947D4[48];
void fn_8002B42C(u8 *, s32);
void fn_8011D988(L80031928 *, u32, s32, s32);
void fn_802516A4(M80031928 *, s32);
void fn_8002AE30(u8 *);
void fn_8026D7C0(void *);
s32 fn_800F6CD0(char *, char *);
O80031928 *fn_801AA960(void *, char *, char *);
void fn_801C2368(void *, O80031928 *, s32);

void fn_80031928(S80031928 *self, s32 flag) {
    X80031928 *x;
    u32 i;
    O80031928 *o;
    char buf[16];
    x = lbl_8035B308->f72;
    if (x != 0) {
        x->f1248 = 1;
        x->f1568 = 0;
        x->f1252 = 1;
    }
    self->f2940 = 0;
    self->f140 ^= 16;
    *self->f2932 = 0;
    lbl_8035B488->f10224 &= ~2;
    fn_8002B42C(self->f2072, 1);
    if (flag != 0) {
        for (i = 0; i < (*lbl_8035B5E4->f24->v23(lbl_8035B5E4->f104))->count; i++) {
            fn_8011D988(*lbl_8035B5E4->f24->v23(lbl_8035B5E4->f104), i, 0, 1);
        }
        fn_802516A4(lbl_8035B5E4, 0);
        fn_8002AE30(self->f2072);
        fn_8026D7C0(self->f128);
        lbl_8035B684->v3(buf, -1);
        if (fn_800F6CD0(buf, lbl_8035BDA0) != 0) {
            o = fn_801AA960(lbl_8035B65C->f36->f13232, lbl_802947C8, lbl_802947D4);
        } else {
            o = fn_801AA960(lbl_8035B65C->f36->f13232, lbl_8035BDA8, lbl_8035BDB0);
        }
        o->v59(0, 1);
        fn_801C2368(self->f120, o, 1);
    }
}

} /* extern "C" */
