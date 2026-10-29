// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern "C" int rand(void);
struct T { u8 pad[220]; int f220; u8 pad224[56]; void *f280; u8 pad284[380]; int f664; };
int fn_800724A4(void *);
void fn_8007115C(T *);
void fn_80241588(T *, int, int, f32);
extern f32 lbl_8035F1BC;
static inline void Set(T *p, int id) {
    if (p->f220 == 14 && !fn_800724A4(p->f280)) fn_8007115C(p);
    fn_80241588(p, id, 0, lbl_8035F1BC);
}
void fn_8006B6F4(T *t) {
    switch (t->f220) {
    case 29:
        break;
    case 4:
        t->f664++;
        if (t->f664 > 5) {
            t->f664 = 0;
            switch ((int)((u32)rand() % 5)) {
            case 0: Set(t, 110); break;
            case 1: Set(t, 6); break;
            case 2: Set(t, 88); break;
            case 3: Set(t, 97); break;
            case 4: Set(t, 89); break;
            }
        }
        break;
    default:
        Set(t, 4);
        t->f664 = 0;
        break;
    }
}

} /* extern "C" */
