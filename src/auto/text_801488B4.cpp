// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern char lbl_8029FBF8[];
extern char lbl_803643B8[2];
extern u32 lbl_8035ACA0;
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
char *strrchr(const char *, int);
u32 strlen(const char *);
void *fn_801488AC(void);
s32 fn_802160B8(void *, char *, s32 *);
void fn_800604C4(int, int, int, int);
void fn_80060568(const char *, int, int, int);
void fn_800F7EC0(u32);
void fn_800F7E98(void);
} /* extern "C" */
struct V_801488B4 { u8 pad[1340]; virtual void v0(); virtual void v1(); virtual s32 load(s32, char *); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual char *ext(); };
extern "C" {

void fn_801488B4(V_801488B4 *self, const char *name) {
    s32 x = 0;
    char buf[272];
    char *msg;
    strcpy(buf, name);
    if (strrchr(buf, '.') == 0) {
        strcat(buf, lbl_803643B8);
        strcat(buf, self->ext());
    }
    if (fn_802160B8(fn_801488AC(), buf, &x) ? 1 : self->load(x, buf)) {
        if (lbl_8035ACA0 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035ACA0);
        msg = new char[strlen(name) + 64];
        fn_800F7E98();
        if (msg == 0) fn_800604C4(-4, 0, 0, 0);
        if (msg == 0) {
            fn_80060568("Pixel map file not found.", 0, 0, 0);
            return;
        }
        strcpy(msg, name);
        strcat(msg, ": Unable to find ");
        strcat(msg, self->ext());
        strcat(msg, " pixel map file.");
        fn_80060568(msg, 0, 0, 0);
        delete[] msg;
    }
}

} /* extern "C" */
