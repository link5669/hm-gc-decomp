// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Item {
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
    virtual s32 v27(void *owner, void *arg);
};
struct Node { Item *f0; s32 f4; Node *f8; };
struct Tgt {
    u8 pad[128];
    virtual void t0();
    virtual void t1();
    virtual void t2();
    virtual void t3();
    virtual void t4();
    virtual void t5();
    virtual void t6();
    virtual void t7();
    virtual void t8();
    virtual void t9();
    virtual void t10();
    virtual void t11();
    virtual void t12();
    virtual void t13();
    virtual void t14();
    virtual void t15();
    virtual void t16();
    virtual void t17();
    virtual void t18();
    virtual void t19();
    virtual void t20();
    virtual void t21();
    virtual void t22();
    virtual void t23();
    virtual void t24();
    virtual void t25();
    virtual void t26();
    virtual void t27();
    virtual void t28();
    virtual void t29();
    virtual void t30();
    virtual void t31();
    virtual void t32();
    virtual void t33();
    virtual void t34();
    virtual void t35();
    virtual void t36();
    virtual void t37();
    virtual void t38();
    virtual void t39();
    virtual void t40();
    virtual void t41();
    virtual void t42();
    virtual void t43();
    virtual void t44();
    virtual void t45();
    virtual void t46();
    virtual void t47();
    virtual void t48();
    virtual void t49();
    virtual void t50();
    virtual void t51();
    virtual void t52();
    virtual void t53();
    virtual void t54();
    virtual void t55();
    virtual void t56();
    virtual void t57();
    virtual void t58();
    virtual void t59();
    virtual void t60();
    virtual void t61();
    virtual void t62();
    virtual void t63();
    virtual void t64();
    virtual void t65();
    virtual void t66();
    virtual void t67();
    virtual void t68();
    virtual void t69(void *owner);
};
struct FOut { u8 pad[12]; f32 v; };
struct IOut { u8 pad[12]; s32 v; };
struct Slider { s32 on; f32 cur; f32 min; f32 max; FOut *a; IOut *b; };
struct Self {
    u8 pad[128];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    u8 pad132[4];
    Node *f136;
    u8 pad140[144];
    Tgt *f284;
    u8 pad288[36];
    s32 f324;
    u8 pad328[32];
    Slider sl0;
    Slider sl1;
};
extern "C" {
static inline void Update(Self *self, Slider *s) {
    if (s->on) {
        f32 v = s->max;
        if (v > s->max) v = s->max;
        if (v < s->min) v = s->min;
        if (s->a) { s->cur = v; s->a->v = v; }
        if (s->b) { s->cur = v; s->b->v = (s32)v; }
        if (self->f284) self->f284->t69(self);
        self->s25();
    }
}

s32 fn_801CF610(Self *self, void *arg) {
    Node *n;
    s32 found = 0;
    for (n = self->f136; n != 0; n = n->f8) {
        if (n->f4 != 0) {
            if (n->f0->v27(self, arg) == 0) found = 1;
        }
    }
    if (found) return 0;
    switch (self->f324) {
    case 32:
        Update(self, &self->sl0);
        Update(self, &self->sl1);
        break;
    }
    return 0;
}

} /* extern "C" */
