// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_8024EDB8(void *);
void fn_8024FC04(void *);
void fn_80251380(void *);
void fn_80250B2C(void *);
void fn_8024C118(void *);
void fn_80250194(void *);
void fn_8024F8A8(void *);
void fn_80216044(void *, char *);
void fn_80215FDC(void *);
void fn_8024F6D8(void *, u8 *, char *, void *, s32, s32, s32);
typedef struct { u8 pad[32]; u32 f32; } G8025;
extern G8025 lbl_8035771C;
extern G8025 lbl_803576EC;
extern G8025 lbl_8035768C;
extern G8025 lbl_803576BC;
extern void *volatile lbl_8035B5C0;
typedef struct { u8 pad[12]; u8 *f12; } G8035B460;
extern G8035B460 *lbl_8035B460;
extern char lbl_803664E8[1];
extern u8 lbl_802A93F8[];
} /* extern "C" */
struct C8024FB58 {
    u8 pad[16];
    virtual ~C8024FB58();
    C8024FB58();
    u8 rest[852 - 20];
};
extern "C" {
typedef struct { s32 f0; C8024FB58 *f4; } S80250BA0;
typedef struct { u32 f0; void *f4; void *f8; } A80250BA0;
void fn_80250BA0(S80250BA0 *self, A80250BA0 *arg) {
    u8 *b;
    void *o;
    if (self->f0 != 0) {
        if (self->f4 != 0) {
            fn_8024EDB8(self->f4);
            delete self->f4;
        }
        self->f0 = 0;
        self->f4 = 0;
    }
    self->f0 = 1;
    lbl_8035771C.f32 = 1;
    lbl_803576EC.f32 = 1;
    lbl_8035768C.f32 = 1;
    lbl_803576BC.f32 = 1;
    lbl_8035B5C0 = arg->f8;
    fn_8024FC04(lbl_8035B5C0);
    fn_80251380(lbl_8035B5C0);
    fn_80250B2C(lbl_8035B5C0);
    fn_8024C118(lbl_8035B5C0);
    fn_80250194(lbl_8035B5C0);
    if (lbl_8035B5C0 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035B5C0);
    self->f4 = new C8024FB58;
    fn_800F7E98();
    if (self->f4 == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    fn_8024F8A8(self->f4);
    o = arg->f4;
    b = lbl_8035B460->f12 + 12980;
    fn_80216044(o, lbl_803664E8);
    fn_8024F6D8(self->f4, b, lbl_803664E8, lbl_802A93F8, 0, 0, 0);
    fn_80215FDC(o);
}

} /* extern "C" */
