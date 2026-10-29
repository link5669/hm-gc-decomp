// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Q801D5F0C {
    u8 pad[292];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual s32 v5();
};
struct Y801D5F0C { u8 pad[8]; void *f8; };
struct T801D5F0C { u8 pad[52]; s32 f52; };
struct P801D5F0C {
    u8 pad[116];
    Y801D5F0C *f116;
    u8 pad2[8];
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
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78(s32, Q801D5F0C *, s32);
};
extern "C" {

void fn_800FAFA8(Q801D5F0C *);
s32 fn_800FB33C(Q801D5F0C *);
void fn_800FAF50(Q801D5F0C *);
void fn_800FAEF8(Q801D5F0C *);
void fn_800FAEA0(Q801D5F0C *);
void fn_800FB0F8(Q801D5F0C *, char **);
void fn_800FB064(Q801D5F0C *, s32 *);
T801D5F0C *fn_80207198(void *, char *, s32 *);
void __dla__FPv(void *);
s32 fn_801D52A0(P801D5F0C *, u8 *, s32, s32, s32, s32);

void fn_801D5F0C(P801D5F0C *p0, s32 msg, Q801D5F0C *q0, s32 a0) {
    Q801D5F0C *q = q0;
    P801D5F0C *p = p0;
    s32 i;
    T801D5F0C *t;
    s32 n;
    u8 *x;
    s32 a = a0;
    s32 id;
    char *name;
    switch (msg) {
    case 174:
        fn_800FAFA8(q);
        n = fn_800FB33C(q);
        fn_800FAF50(q);
        fn_800FB0F8(q, &name);
        fn_800FB064(q, &id);
        t = fn_80207198(p->f116->f8, name, &id);
        __dla__FPv(name);
        x = t->f52 != 0 ? (u8 *)t + 32 : (u8 *)t + 12;
        a = fn_801D52A0(p, x, a, fn_800FB33C(q), 0, 0);
        fn_800FAEF8(q);
        for (i = 0; i < n; i++) {
            s32 m = q->v5();
            switch (m) {
            case 174:
                p->v78(m, q, a);
                break;
            case 175:
                p->v78(m, q, a);
                break;
            }
        }
        fn_800FAEA0(q);
        break;
    case 175:
        fn_800FB0F8(q, &name);
        fn_800FB064(q, &id);
        t = fn_80207198(p->f116->f8, name, &id);
        __dla__FPv(name);
        x = t->f52 != 0 ? (u8 *)t + 32 : (u8 *)t + 12;
        fn_801D52A0(p, x, a, fn_800FB33C(q), 0, 0);
        break;
    }
}

} /* extern "C" */
