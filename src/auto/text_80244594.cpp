// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct Node {
    u8 pad0[12];
    char name[8];
    u32 count;
    void **children;
    u32 f28;
    struct Node *next;
    struct Node *up;
} Node;

typedef struct Sub {
    u32 f0;
    u32 f4;
    void *obj;
    void *arg;
} Sub;

typedef struct Iter {
    u32 f0;
    Node *cur;
    Node *root;
    u32 f12;
    void *item;
    u32 idx;
    Sub sub;
    u32 f40;
    u32 f44;
    u32 f48;
    s32 f52;
} Iter;

extern char lbl_80359A20[8];
void fn_8023C3F4(Sub *s);
void fn_8023C528(Sub *s, char *name);
void *fn_8023A490(void *obj, void *arg);
int fn_800F6CD0(char *a, char *b);

static inline void *Sub_get(Sub *s) {
    return s->obj ? fn_8023A490(s->obj, s->arg) : 0;
}

void fn_80244594(Iter *it) {
    if (it->cur->children != 0) {
        for (it->idx++; it->idx < it->cur->count; it->idx++) {
            it->item = it->cur->children[it->idx];
            if (it->item != 0) return;
        }
    } else {
        fn_8023C3F4(&it->sub);
        if (it->sub.obj != 0) {
            it->item = Sub_get(&it->sub);
            return;
        }
    }
    it->idx = 0;
    if (it->cur->next != 0) {
        it->cur = it->cur->next;
    } else if (it->f52 == 0 && it->root->up != 0) {
        do {
            it->root = it->root->up;
            it->cur = it->root;
        } while (it->cur != 0 && fn_800F6CD0(it->cur->name, lbl_80359A20) != 0);
        if (it->cur == 0) {
            it->item = 0;
            return;
        }
    } else {
        it->item = 0;
        return;
    }
    if (it->cur->children != 0) {
        it->item = it->cur->children[0];
        if (it->item == 0) fn_80244594(it);
    } else {
        fn_8023C528(&it->sub, it->cur->name);
        it->item = Sub_get(&it->sub);
        if (it->item == 0) fn_80244594(it);
    }
}

} /* extern "C" */
