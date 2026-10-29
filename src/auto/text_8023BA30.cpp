// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct It8023BA30 { s8 found; u8 pad[3]; void *a; void *b; } It8023BA30;
typedef struct O8023BA30 {
    u8 pad[20]; u8 name[8]; void *f28; struct O8023BA30 *next; void *f36;
} O8023BA30;
extern u8 lbl_8035756C[];
O8023BA30 *fn_800F8274(void *, void *);
void fn_800F806C(void *, void *, It8023BA30 *);
void fn_800F8410(void *, It8023BA30 *);
void fn_800F87F0(void *, It8023BA30 *, void *);
void fn_800F8DD0(O8023BA30 *);
void fn_8023BA30(O8023BA30 *self) {
    O8023BA30 *p = fn_800F8274(lbl_8035756C, self->name);
    It8023BA30 it;
    fn_800F806C(lbl_8035756C, self, &it);
    if (it.found) {
        fn_800F8410(lbl_8035756C, &it);
        if (self->next != 0) {
            fn_800F87F0(lbl_8035756C, &it, self->next);
        }
    }
    if (p != self) {
        for (; p->next != 0; p = p->next) {
            if (p->next == self) {
                p->next = self->next;
                break;
            }
        }
    }
    self->next = 0;
    self->f28 = 0;
    self->f36 = 0;
    fn_800F8DD0(self);
}

} /* extern "C" */
