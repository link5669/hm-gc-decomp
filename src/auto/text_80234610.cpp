// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct OBase {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
};
struct OD : OBase {
    u8 pad4[176];
    u32 f180;
};
struct SelfD {
    u8 pad0[524];
    u32 f524;
    u8 pad528[68];
    OD *arr[100];
    u32 *f996;
    u8 pad1000[12];
    u32 *f1012;
    u8 pad1016[36];
    s32 f1052;
    u32 f1056;
    u8 pad1060[8];
    u32 f1068;
    u32 f1072;
    u8 pad1076[4];
    u32 f1080;
    u32 f1084;
    f32 v[3];
    u32 f1100;
};
extern "C" {
void fn_80236E10(SelfD *, const char *, u32, u32, u32, const f32 *);
s32 fn_800F6CD0(const char *, const char *);
void fn_800F6FBC(const char *, char *);
void fn_80234028(SelfD *, s32, s32, s32);
extern const char lbl_80365E8C[6];
extern const char lbl_80365E98[6];
extern const char lbl_802A88E4[9];
extern const char lbl_802A88F0[];

static inline void purge(SelfD *self) {
    s32 i;
    if (self->f996) {
        for (i = 0; i < (s32)*self->f996; i++) {
            if (self->arr[i] && (self->arr[i]->f180 & 2)) {
                self->arr[i]->v4();
                self->f1052--;
                self->arr[i] = 0;
            }
        }
    }
}

void fn_80234610(SelfD *self, const char *ev, u32 a2, u32 a3, u32 a4, const f32 *pos) {
    char buf[16];
    if (self->f524) {
        fn_80236E10(self, ev, a2, a3, a4, pos);
        return;
    }
    if (fn_800F6CD0(ev, lbl_80365E8C)) {
        self->f1080 = a2;
        self->f1084 = a4;
        if (pos) {
            self->v[0] = pos[0];
            self->v[1] = pos[1];
            self->v[2] = pos[2];
            self->f1100 = 1;
        } else {
            self->f1100 = 0;
        }
        self->f1056 = *self->f1012;
        self->f1072 = 1;
        fn_80234028(self, 0, 0, 0);
    }
    fn_800F6FBC(lbl_802A88E4, buf);
    if (fn_800F6CD0(ev, buf)) {
        self->f1068 = 1;
    }
    fn_800F6FBC(lbl_802A88F0, buf);
    if (fn_800F6CD0(ev, buf)) {
        self->f1056 = 0;
        self->f1068 = 0;
    }
    fn_800F6FBC(lbl_80365E98, buf);
    if (fn_800F6CD0(ev, buf)) {
        purge(self);
        self->f1056 = 0;
        self->f1068 = 0;
    }
}

} /* extern "C" */
