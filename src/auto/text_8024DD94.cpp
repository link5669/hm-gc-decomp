// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct C8023C7CC {
    u8 pad[8];
    void *a;
    void *b;
    u8 pad2[12];
    C8023C7CC();
    ~C8023C7CC();
};
extern "C" {
struct O { u8 pad[20]; char name[8]; };
struct OV { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void s11(void *); };
struct P { u8 pad[16]; virtual void v0(); virtual void v1(); virtual void v2(); virtual s32 s3(); u8 pad20[56]; u8 sub76[4]; };
extern char lbl_80366440[8], lbl_80366448[8];
void fn_8023C720(C8023C7CC *, void *);
void fn_8023C528(C8023C7CC *, char *);
O *fn_8023A490(void *, void *);
void fn_8023C3F4(C8023C7CC *);
void fn_800F6E88(char *, char *);
s32 fn_800F6F00(char *, char *);
void fn_802501D4(O *);
void fn_80250E80(O *);
OV *fn_8024E3DC(P *, char *, u32 *);

static inline O *get(C8023C7CC *it) { return it->a ? fn_8023A490(it->a, it->b) : (O *)0; }
static inline O *find(P *p, char *name, char *kind) {
    C8023C7CC it;
    u32 pass;
    for (pass = 0; pass < 2; pass++) {
        if (pass == 0 && p->s3()) fn_8023C720(&it, p);
        else fn_8023C720(&it, p->sub76);
        for (fn_8023C528(&it, kind); it.a; fn_8023C3F4(&it)) {
            O *o = get(&it);
            char buf[8];
            fn_800F6E88(buf, o->name);
            if (!fn_800F6F00(name, buf)) return o;
        }
    }
    return 0;
}

void fn_8024DD94(P *p, char *name, s32 kind, void *arg) {
    C8023C7CC outer;
    switch (kind) {
    case 1:
        fn_802501D4(find(p, name, lbl_80366440));
        break;
    case 2:
        fn_80250E80(find(p, name, lbl_80366448));
        break;
    case 3: {
        u32 tmp;
        fn_8024E3DC(p, name, &tmp)->s11(arg);
        break;
    }
    }
}

} /* extern "C" */
