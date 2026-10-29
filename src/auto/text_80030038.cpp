// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct A_30038 {
    u8 pad[1720];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual s32 v5(const char *s);
};
struct V_30038 {
    virtual void d0();
    virtual void v1();
};
extern "C" {
typedef struct {
    u8 *f0;
    u8 pad4[4];
    u8 f8[128];
    u8 f136[32];
    V_30038 *f168;
    s32 f172;
    u8 pad176[20];
    u8 f196[244];
    u8 f440[12];
    V_30038 *f452;
    u8 f456[4];
} S_30038;
extern void *lbl_8035B680;
extern const char lbl_80294724[9];
extern const char lbl_80294730[9];
extern char lbl_80357740[268];
extern const char lbl_8035BC18[7];
extern const char lbl_8035BC20[7];
extern const char lbl_8035BC28[5];
extern const char lbl_8035BC30[8];
extern const char lbl_8035BC38[6];
extern const char lbl_8035BC40[8];
void fn_802558DC(void);
void fn_8003EC40(void *p);
void fn_8008E49C(void *p);
void fn_8002FAE8(void *p);
void *fn_8023BC90(const char *s);
void *fn_8023B8FC(void *p, const char *s, s32 n);
void fn_8003E8A0(void *a, void *b);
A_30038 *fn_8021616C(void *p);
void fn_80207BF4(A_30038 *a, const char *s);
void fn_802079F0(A_30038 *a, s32 n);
void fn_8003ED90(void *p);
void fn_8010917C(void *a, void *b, const char *s, s32 n);
char *strcpy(char *d, const char *s);
void fn_800F6E88(void *p, const char *s);
void fn_802495F0(V_30038 *p, s32 n);

void fn_80030038(S_30038 *self) {
    fn_802558DC();
    fn_8003EC40(lbl_8035B680);
    fn_8008E49C(lbl_8035B680);
    fn_8002FAE8(lbl_8035B680);
    self->f452 = (V_30038 *)fn_8023B8FC(fn_8023BC90(lbl_80294724), lbl_8035BC18, -1);
    fn_8003E8A0(self->f456, self->f0 + 852);
    fn_80207BF4(fn_8021616C(self->f0 + 852), lbl_8035BC20);
    fn_802079F0(fn_8021616C(self->f0 + 852), 0);
    fn_8003ED90(self->f196);
    fn_80207BF4(fn_8021616C(self->f0 + 852), lbl_8035BC20);
    if (fn_8021616C(self->f0 + 852)->v5(lbl_80294730) == 0) {
        fn_8010917C(self->f136, self->f8, lbl_8035BC28, 0);
    }
    fn_802079F0(fn_8021616C(self->f0 + 852), 0);
    if (self->f172 != 0) {
        self->f168 = (V_30038 *)fn_8023B8FC(fn_8023BC90(lbl_80294724), lbl_8035BC30, -1);
        if (lbl_80357740[0] == 0) {
            strcpy(lbl_80357740, lbl_8035BC38);
        }
    } else {
        self->f168 = (V_30038 *)fn_8023B8FC(fn_8023BC90(lbl_80294724), lbl_8035BC28, -1);
    }
    fn_800F6E88(self->f440, lbl_8035BC40);
    self->f168->v1();
    self->f452->v1();
    fn_802495F0(self->f452, 0);
}

} /* extern "C" */
