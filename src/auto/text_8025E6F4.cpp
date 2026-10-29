// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern void *lbl_8035B708;
extern char lbl_803669F8[4];
extern char lbl_803669FC[4];
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
} /* extern "C" */
struct C800F92E8 {
    C800F92E8();
    u8 pad[20];
};
struct C8025EDC0 {
    C8025EDC0();
    ~C8025EDC0();
    u8 pad[64];
};
extern "C" {
typedef struct {
    C800F92E8 *map;
    C8025EDC0 *items;
    C8025EDC0 *cur;
    s32 count;
} Obj_8025E6F4;
void fn_800F8E38(C800F92E8 *, s32);
void fn_8025E940(C8025EDC0 *, char *, char *, char *, void *, void *);
void fn_800F87F0(C800F92E8 *, char *, C8025EDC0 *);

void fn_8025E6F4(Obj_8025E6F4 *self, char **names, s32 n, void *a, void *b)
{
    s32 i;
    if (lbl_8035B708 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035B708);
    self->map = new C800F92E8;
    fn_800F7E98();
    if (self->map == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    fn_800F8E38(self->map, n);
    if (lbl_8035B708 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035B708);
    self->items = new C8025EDC0[n];
    fn_800F7E98();
    if (self->items == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    for (i = 0; i < n; i++) {
        fn_8025E940(&self->items[i], names[i], lbl_803669F8, lbl_803669FC, a, b);
        fn_800F87F0(self->map, names[i], &self->items[i]);
    }
    self->count = n;
    self->cur = self->items;
}

} /* extern "C" */
