// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct C8023C7CC {
    u8 pad[8];
    void *a;
    void *b;
    u8 pad2[16];
    C8023C7CC();
    ~C8023C7CC();
};
struct O { u8 pad[20]; char name[8]; u32 n28; };
struct P { u8 pad[16]; virtual void v0(); virtual void v1(); virtual void v2(); virtual s32 s3(); u8 pad20[56]; u8 sub76[4]; };
extern char lbl_80366450[8], lbl_80366458[8];
void fn_8023C720(C8023C7CC *, void *);
void fn_8023C528(C8023C7CC *, char *);
O *fn_8023A490(void *, void *);
void fn_8023C3F4(C8023C7CC *);
void fn_800F6E88(char *, char *);

static inline O *get(C8023C7CC *it) { return it->a ? fn_8023A490(it->a, it->b) : (O *)0; }

s32 fn_8024D814(P *p, char *out, s32 *kind) {
    C8023C7CC it;
    if (p->s3()) {
        fn_8023C720(&it, p);
        for (fn_8023C528(&it, lbl_80366450); it.a; fn_8023C3F4(&it)) {
            if (get(&it)->n28 > 1) {
                fn_800F6E88(out, get(&it)->name);
                *kind = 0;
                return 1;
            }
        }
        for (fn_8023C528(&it, lbl_80366458); it.a; fn_8023C3F4(&it)) {
            if (get(&it)->n28 > 1) {
                fn_800F6E88(out, get(&it)->name);
                *kind = 0;
                return 1;
            }
        }
    }
    fn_8023C720(&it, p->sub76);
    for (fn_8023C528(&it, lbl_80366450); it.a; fn_8023C3F4(&it)) {
        if (get(&it)->n28 > 1) {
            fn_800F6E88(out, get(&it)->name);
            *kind = 1;
            return 1;
        }
    }
    for (fn_8023C528(&it, lbl_80366458); it.a; fn_8023C3F4(&it)) {
        if (get(&it)->n28 > 1) {
            fn_800F6E88(out, get(&it)->name);
            *kind = 0;
            return 1;
        }
    }
    return 0;
}

} /* extern "C" */
