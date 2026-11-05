// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct E801800D8 { u8 pad[16]; u32 f16; } E801800D8;
typedef struct S801800D8 { u8 pad[16]; u32 n1; E801800D8 *a1; u32 n2; E801800D8 *a2; } S801800D8;
} /* extern "C" */
struct V801800D8 {
    u8 pad[6448];
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
    virtual void m73(u32, E801800D8 *);
    virtual void m74(u32, E801800D8 *);
};
extern "C" {
typedef struct T801800D8 { u8 pad[8]; V801800D8 *f8; } T801800D8;

void fn_801800D8(S801800D8 *self, T801800D8 *t) {
    u32 i;
    for (i = 0; i < self->n1; i++) {
        t->f8->m73(self->a1[i].f16, &self->a1[i]);
    }
    for (i = 0; i < self->n2; i++) {
        t->f8->m74(self->a2[i].f16, &self->a2[i]);
    }
}

} /* extern "C" */
