// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct C8018D904 { u8 pad[20]; void *f20; };
struct V8018D904 {
    u8 pad[20];
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
    virtual void m17(void *q, u32 a, u32 b, s32 c);
    virtual void v18();
    virtual void v19();
    virtual void m20(void *q, u32 a, s32 b, u32 c, u32 d);
};
struct A08018D904 {
    u32 f0;
    u8 pad4[20];
    u8 f24[80];
    virtual void v0();
    virtual void v1();
    virtual void m2();
    virtual void v3();
    virtual C8018D904 *m4();
};
struct A8018D904 : A08018D904 {
    u32 f108;
    u8 pad112[32];
    V8018D904 *f144;
    u32 f148;
    u32 f152;
    u32 f156;
};
struct B8018D904 {
    u8 pad[6444];
    void *f6444;
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
    virtual void *m67();
    virtual void *m68();
    virtual void m69(s32 a, void *b);
};
extern "C" {
void fn_801044C4(C8018D904 *, void *, void *);
void fn_801A07E4(A8018D904 *, B8018D904 *);
void fn_8018D904(A8018D904 *p, B8018D904 *q, C8018D904 *r) {
    if (p->f0 & 4) p->m2();
    q->f6444 = p->f24;
    if (r == 0) r = p->m4();
    if (r != 0) {
        fn_801044C4(r, q->m67(), q->m68());
        q->m69(0, r->f20);
    } else {
        q->m69(0, q->m67());
    }
    if (p->f144 != 0) {
        fn_801A07E4(p, q);
        if (p->f156 != 0) {
            p->f144->m20(q, p->f108, 1, p->f152, p->f156);
        } else {
            p->f144->m17(q, p->f108, p->f148, 1);
        }
    }
}

} /* extern "C" */
