// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct {
    u8 pad0[20];
    u32 f14;
} C_8019E860;
typedef struct {
    u8 pad0[4];
    void **arr;
} T_8019E860;
typedef struct {
    u8 b[20];
} E_8019E860;
} /* extern "C" */
struct B_8019E860 {
    u8 pad0[6444];
    void *f192c;
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
    virtual void *f67();
    virtual void *f68();
    virtual void f69(s32, u32);
};
struct AV_8019E860 {
    u32 f0;
    u8 pad4[20];
    u8 f18[80];
    virtual void v0();
    virtual void v1();
    virtual void f2();
    virtual void v3();
    virtual C_8019E860 *f4();
};
struct A_8019E860 : AV_8019E860 {
    T_8019E860 *f6c;
    u8 pad70[32];
    E_8019E860 arr[2];
    u8 fb8[20];
    s32 fcc;
    s32 fd0;
    f32 fd4;
    u8 pad_d8[4];
    f32 fdc;
    u8 pade0[12];
    u8 fec[8];
    u8 ff4[8];
    u8 ffc[8];
};
extern "C" {
void fn_801044C4(C_8019E860 *, void *, void *);
void fn_801A07E4(A_8019E860 *, B_8019E860 *);
void fn_80185EB4(void *, E_8019E860 *, E_8019E860 *, f32);
void fn_80185FF0(void *, B_8019E860 *, void *, void *, void *, void *, s32, u8 *, f32);

void fn_8019E860(A_8019E860 *self0, B_8019E860 *b0, C_8019E860 *c0)
{
    u8 flag;
    A_8019E860 *self = self0;
    B_8019E860 *b = b0;
    C_8019E860 *c = c0;
    if (self->f0 & 4) {
        self->f2();
    }
    b->f192c = self->f18;
    if (c == 0) {
        c = self->f4();
    }
    if (c != 0) {
        fn_801044C4(c, b->f67(), b->f68());
        b->f69(0, c->f14);
    } else {
        b->f69(0, (u32)b->f67());
    }
    fn_801A07E4(self, b);
    flag = 0;
    fn_80185EB4(self->fb8, &self->arr[!self->fd0], &self->arr[self->fd0], self->fd4);
    fn_80185FF0(self->fb8, b, self->f6c->arr[self->fcc], self->fec, self->ff4, self->ffc, 1, &flag, self->fdc);
}
/* prag=0 call=0 flag self b c */

} /* extern "C" */
