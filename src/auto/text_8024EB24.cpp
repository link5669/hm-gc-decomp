// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct C8023C7CC {
    u8 pad[8];
    void *a;
    void *b;
    u8 pad2[16];
};
struct O { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void s9(f32); virtual void s10(void *, void *); };
struct E40 { u8 b[40]; };
struct P {
    u8 pad0[72];
    s32 i72;
    u8 sub76[72];
    C8023C7CC *it;
    u8 pad152[12];
    u32 a164;
    u8 pad168[164];
    u8 s332[304];
    u32 n636;
    E40 e640[4];
};
extern char lbl_80366440[8], lbl_80366448[8], lbl_80366450[8], lbl_80366458[8];
extern u8 *lbl_8035B65C;
void fn_8023C720(C8023C7CC *, void *);
void fn_8023C528(C8023C7CC *, char *);
O *fn_8023A490(void *, void *);
void fn_8023C3F4(C8023C7CC *);
void fn_80250414(O *, f32);
void fn_80250F1C(O *, f32);
s32 fn_8024D814(P *, char *, s32 *);
O *fn_8024E3DC(P *, E40 *, u32 *);
void *memcpy(void *, const void *, u32);
void fn_80180600(void *, f32);

static inline O *get(C8023C7CC *it) { return it->a ? fn_8023A490(it->a, it->b) : (O *)0; }

void fn_8024EB24(P *p, f32 dt) {
    u32 pass;
    for (pass = 0; pass < 2; pass++) {
        if (pass == 0 && p->i72) fn_8023C720(p->it, p);
        else fn_8023C720(p->it, p->sub76);
        for (fn_8023C528(p->it, lbl_80366440); p->it->a; fn_8023C3F4(p->it)) fn_80250414(get(p->it), dt);
        for (fn_8023C528(p->it, lbl_80366448); p->it->a; fn_8023C3F4(p->it)) fn_80250F1C(get(p->it), dt);
        for (fn_8023C528(p->it, lbl_80366450); p->it->a; fn_8023C3F4(p->it)) get(p->it)->s9(dt);
        for (fn_8023C528(p->it, lbl_80366458); p->it->a; fn_8023C3F4(p->it)) get(p->it)->s9(dt);
    }
    if (p->n636) {
        char buf[8];
        s32 k;
        if (!fn_8024D814(p, buf, &k)) {
            u32 i;
            u32 tmp;
            p->n636--;
            if (!(*(u32 *)(lbl_8035B65C + 140) & 0x10)) fn_8024E3DC(p, p->e640, &tmp)->s10(p->e640[0].b + 8, p->e640[0].b + 16);
            for (i = 0; i < p->n636; i++) memcpy(&p->e640[i], &p->e640[i + 1], 40);
        }
    }
    if (p->a164) fn_80180600(&p->a164, dt);
    fn_80180600(p->s332, dt);
}

} /* extern "C" */
