// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct G8003CF0C {
    u8 pad[192];
    virtual void p0(); virtual void p1(); virtual void p2();
    virtual void m3(void *, s32);
    virtual void p4();
    virtual s32 m5(void *);
};
struct O8003CF0C { u8 pad[740]; char names[8][20]; };
extern "C" {
extern G8003CF0C *lbl_8035B684;
extern char lbl_80294E1C[];
s32 fn_800F8274(char *, char *);
s32 fn_8003CF0C(O8003CF0C *o, void *a) {
    u8 buf[16];
    s32 i;
    s32 r;
    i = lbl_8035B684->m5(a);
    if (i == -1) {
        lbl_8035B684->m3(buf, -1);
        i = lbl_8035B684->m5(buf);
    }
    r = fn_800F8274(o->names[i], lbl_80294E1C);
    return (r != 0) & ~-(r == 0);
}

} /* extern "C" */
