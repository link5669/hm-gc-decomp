#include "common.h"
// fn_8011CD28: function-equivalent (funcequiv proves it): target store order, self/it saved regs swapped.

extern "C" {
typedef struct Item8011 {
    struct Item8011 *next;
    struct Item8011 *prev;
    s32 f8;
    u32 fC;
    u32 f10;
    u32 f14;
    void *f18;
} Item8011;

typedef struct Self8011 {
    u8 pad0[32];
    Item8011 *head;
    Item8011 *tail;
    u8 pad28[16];
    Item8011 **items;
    u32 f3C;
    u32 count;
} Self8011;

s32 fn_8011DDE0(u32 a, Item8011 *it);
void fn_80118FC4(void *vec, Item8011 *it);

static inline Item8011 *find8011(Self8011 *self, u32 a, s32 b, u32 c) {
    u32 i;
    for (i = 0; i < self->count; i++) {
        Item8011 *it = self->items[i];
        if (it->f14 == a && it->f8 == b && it->f10 == c) return it;
    }
    return 0;
}

static inline Item8011 *pop8011(Self8011 *self) {
    Item8011 *it = self->head;
    if (it != 0) {
        if ((self->head = it->next) != 0) self->head->prev = 0;
        else self->tail = 0;
    }
    return it;
}

void fn_8011CD28(Self8011 *__restrict self, u32 a, s32 b, s32 d, u32 c) {
    Item8011 *__restrict it;
    if (find8011(self, a, b, c) != 0) return;
    it = pop8011(self);
    it->f14 = a;
    it->f8 = b;
    it->f10 = c;
    it->f18 = self;
    if (fn_8011DDE0(a, it) != 0) {
        fn_80118FC4(&self->items, it);
    } else {
        if ((it->next = self->head) != 0) self->head->prev = it;
        else self->tail = it;
        self->head = it;
        it->prev = 0;
    }
}

} /* extern "C" */
