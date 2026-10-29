// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_8035C060;
extern f32 lbl_8035C064;
extern f32 lbl_8035C068;
extern f32 lbl_8035C06C;
extern u8 *lbl_8035B488;
extern u8 *lbl_8035B65C;
extern u8 *lbl_80359F2C;
extern u8 *lbl_8035A1DC;
} /* extern "C" */

struct V800396C0 {
    u8 pad[6448];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3(void *, s32, s32);
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
};

struct E800396C0 {
    u8 pad[16];
    f32 f16;
    u8 pad2[60];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4(V800396C0 *);
    u8 pad3[16];
};

struct L800396C0 {
    u8 pad[20];
    E800396C0 *f20;
    u32 f24;
};

struct W800396C0 {
    u8 pad[48];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8(s32);
};

struct C800396C0 {
    u8 pad[4];
    L800396C0 *f4;
    u8 pad2[4];
    V800396C0 *f12;
    void *f16;
    f32 f20;
    u32 f24;
    s32 f28;
};

static inline void Loop800396C0(C800396C0 *p, f32 delta, f32 &last) {
    u32 i;
    for (i = 0; i < p->f4->f24; i++) {
        E800396C0 *e = &p->f4->f20[i];
        last = e->f16;
        last -= delta;
        e->f16 = last;
        p->f4->f20[i].v4(p->f12);
    }
}

extern "C" {

void fn_800396C0(C800396C0 *p) {
    u32 dt;
    f32 delta;
    f32 last;

    p->f12->v3(p->f16, 7, 0);
    last = lbl_8035C060;
    dt = *(u32 *)(lbl_8035B488 + 16);
    if (dt > 100) {
        dt = 100;
    }
    p->f24 += dt;
    delta = lbl_8035C064 * ((f32)dt / lbl_8035C068);
    p->f20 += delta;
    Loop800396C0(p, delta, last);
    if (last < lbl_8035C06C) {
        p->f28 = 1;
        if (lbl_8035B65C != 0 && *(s32 *)(lbl_8035B65C + 2956) == 0) {
            *(s32 *)(lbl_80359F2C + 376) = 1;
        }
    }
    p->f12->v62();
    (*(W800396C0 **)(lbl_8035A1DC + 11340))->v8(0);
}

} /* extern "C" */

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct E8003984C_0 {
    u8 pad[16];
    f32 f16;
    u8 pad2[60];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4(void *a);
};
struct E8003984C : E8003984C_0 {
    u8 pad3[16];
};
extern "C" {
typedef struct L8003984C { u8 pad[20]; E8003984C *f20; u32 f24; } L8003984C;
typedef struct S8003984C { u8 pad[4]; L8003984C *f4; u8 pad2[4]; void *f12; u8 pad3[4]; f32 f20; u32 f24; u32 f28; } S8003984C;
typedef struct G8003984C_a { u8 pad[16]; u32 f16; } G8003984C_a;
typedef struct G8003984C_b { u8 pad[2956]; s32 f2956; } G8003984C_b;
typedef struct G8003984C_c { u8 pad[376]; u32 f376; } G8003984C_c;
/* lbl_8035B488 is declared above as u8 * */

void fn_8003984C(S8003984C *p) {
    u32 i;
    f32 v;
    f32 d;
    u32 n;
    v = lbl_8035C060;
    n = ((G8003984C_a *)lbl_8035B488)->f16;
    if (n > 100) {
        n = 100;
    }
    p->f24 += n;
    d = lbl_8035C064 * ((f32)n / lbl_8035C068);
    p->f20 += d;
    for (i = 0; i < p->f4->f24; i++) {
        E8003984C *e = &p->f4->f20[i];
        v = e->f16;
        v -= d;
        e->f16 = v;
        p->f4->f20[i].v4(p->f12);
    }
    if (v < lbl_8035C06C) {
        p->f28 = 1;
        if (lbl_8035B65C != 0 && ((G8003984C_b *)lbl_8035B65C)->f2956 == 0) {
            ((G8003984C_c *)lbl_80359F2C)->f376 = 1;
        }
    }
}

} /* extern "C" */
