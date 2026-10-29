// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
typedef struct { u32 v[3]; } T12_D508;
extern "C" {
extern T12_D508 lbl_8029BF10;
extern u8 lbl_802E3E68[];
}
class N_D508 { public: N_D508 *next; N_D508 *prev; u8 pad8[12]; void *owner; u32 pad18; private: u32 dummy[0]; };

struct C80119180 {
    N_D508 **data;
    u32 pad4;
    u32 count;
    u32 padC;
    C80119180();
    ~C80119180();
};

extern "C" { void fn_8011DE7C(void *, N_D508 *); void fn_8011DD10(void *, N_D508 *); void fn_80118F3C(C80119180 *, N_D508 *); void fn_80118FF8(C80119180 *); }

struct C8011D6B4 {
    void *vt;
    T12_D508 v;
    void *h;
    u32 x14;
    N_D508 *arrA;
    N_D508 *arrB;
    N_D508 *head;
    N_D508 *tail;
    C80119180 la;
    C80119180 lb;
    ~C8011D6B4();
};

static inline void push_D508(C8011D6B4 *p, N_D508 *n) {
    if ((n->next = p->head) != 0) {
        p->head->prev = n;
    } else {
        p->tail = n;
    }
    p->head = n;
    n->prev = 0;
}

C8011D6B4::~C8011D6B4() {
    N_D508 *n;
    vt = lbl_802E3E68;
    while (la.count != 0) {
        n = *la.data;
        fn_8011DE7C(n->owner, n);
        fn_80118F3C(&la, n);
        push_D508(this, n);
    }
    while (lb.count != 0) {
        n = *lb.data;
        fn_8011DD10(n->owner, n);
        fn_80118F3C(&lb, n);
        push_D508(this, n);
    }
    fn_80118FF8(&la);
    fn_80118FF8(&lb);
    if (arrA) delete[] arrA;
    if (arrB) delete[] arrB;
    h = 0;
    arrA = 0;
    arrB = 0;
    v = lbl_8029BF10;
    x14 = 0;
}
extern "C" {

} /* extern "C" */
