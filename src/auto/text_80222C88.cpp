// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct C80222C88 { u8 *f0; } C80222C88;
typedef struct B80222C88 { u8 pad[8]; C80222C88 *f8; } B80222C88;
typedef struct A80222C88 { u8 pad[8]; B80222C88 *f8; } A80222C88;
extern A80222C88 *lbl_8035B460;
extern u8 lbl_80357740[268];
extern u32 lbl_80365A74;
extern f32 lbl_80365A70;
extern f32 lbl_80365A78;
extern f32 lbl_80365A7C;
u32 fn_800F9398(u8 *, char *);
u32 fn_800F9788(u8 *, char *, char *);
void fn_800F6FBC(void *, char *);
void fn_800F7044(char *);

void fn_80222C88(u8 *p, char *name, f32 x) {
    u8 *o = M2C_FIELD(p, u8 **, 752);
    if (o != 0) {
        M2C_FIELD(o, u8 *, 11) = 255;
        M2C_FIELD(o, u32 *, 44) |= lbl_80365A74;
        M2C_FIELD(p, u8 **, 752) = 0;
    }
    M2C_FIELD(p, u32 *, 752) = fn_800F9398(lbl_8035B460->f8->f8->f0 + 120, name);
    if (M2C_FIELD(p, u32 *, 752) == 0) {
        char k[8];
        u8 *t;
        u32 r;
        fn_800F6FBC(lbl_80357740, k);
        fn_800F7044(k);
        t = lbl_8035B460->f8->f8->f0;
        if (k == 0 || k[0] == 0) {
            r = fn_800F9398(t + 120, name);
        } else {
            r = fn_800F9788(t + 144, k, name);
        }
        M2C_FIELD(p, u32 *, 752) = r;
    }
    M2C_FIELD(p, f32 *, 756) = lbl_80365A70;
    M2C_FIELD(p, s32 *, 760) = 1;
    M2C_FIELD(p, f32 *, 764) = lbl_80365A78 / (lbl_80365A7C * x);
}

} /* extern "C" */
