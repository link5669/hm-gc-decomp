// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V801DD54C {
    u8 pad[128];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual u32 v19();
};
struct N801DD54C { u8 pad[284]; void *owner; u8 pad2[20]; N801DD54C *next; };
struct S801DD54C { u8 pad[312]; N801DD54C *head; };
extern "C" {
static inline void Remove(S801DD54C *self, N801DD54C *node) {
    N801DD54C *p;
    node->owner = 0;
    p = self->head;
    if (p == 0) {
        node->next = 0;
        return;
    }
    if (p == node) {
        self->head = p->next;
        node->next = 0;
        return;
    }
    for (; p->next != 0; p = p->next) {
        if (p->next == node) {
            p->next = node->next;
            break;
        }
    }
    node->next = 0;
}
static inline void Insert(S801DD54C *self, N801DD54C *node) {
    N801DD54C *p;
    node->owner = self;
    p = self->head;
    if (p == 0) {
        self->head = node;
        return;
    }
    for (; p->next != 0; p = p->next) {
        if (((V801DD54C *)p->next)->v19() == 95) break;
    }
    node->next = p->next;
    p->next = node;
}
void fn_801DD54C(S801DD54C *self, N801DD54C *node) {
    if (node->next == 0) return;
    Remove(self, node);
    Insert(self, node);
}

} /* extern "C" */
