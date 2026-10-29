// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Stream {
    u8 pad[292];
    virtual void r0();
    virtual void r1();
    virtual void r2(void *buf, s32 size, s32 z);
};
struct F40 { u8 pad[12]; void *f12; };
struct C80215F50 {
    C80215F50();
    ~C80215F50();
    u8 pad0[36];
    void *f36;
    F40 *f40;
    Stream *f44;
};
struct Obj {
    u8 pad[24];
    virtual void o0(void *a);
    virtual void o1();
    virtual void o2();
    virtual void o3(void *a, Stream *s);
};
struct Self {
    u8 pad[16];
    virtual void s0();
    virtual void s1();
    virtual void s2(void *a);
    virtual Obj *s3(u32 i);
    u32 f20;
};
extern "C" {
extern s32 fn_80215C84(C80215F50 *f, char *path, char *mode, s32 a, s32 b);
extern void fn_80060E30(s32 err, char *fmt, ...);
extern void fn_80207A54(void *a, void *b);
extern void fn_800FB000(Stream *s, s32 n);
extern u32 fn_800FADA8(Stream *s);
extern void fn_800F8E38(Self *self, u32 n);
extern void fn_80135CDC(void *a, Self *self);
extern void fn_800FB064(Stream *s, void *out);
extern void fn_800F87F0(Self *self, void *buf, Obj *o);
extern void fn_800FAEA0(Stream *s);
extern void fn_802079F0(void *a, s32 b);
extern void fn_80215BFC(C80215F50 *f);
extern char lbl_803642F8[4];
extern char lbl_803642FC[6];
extern u8 lbl_802E59D0[928];

static inline void Load(Self *self, u8 *buf, Obj *o, void *a, Stream *s) {
    fn_800F87F0(self, buf, o);
    o->o3(a, s);
}

void fn_8013BE6C(Self *self, void *a, char *path) {
    u8 buf[8];
    C80215F50 file;
    u32 i;
    Stream *s;
    u32 j;
    s32 err;
    err = fn_80215C84(&file, path, lbl_803642F8, 2, 0);
    if (err != 0) {
        fn_80060E30(err, lbl_803642FC, path, lbl_803642F8);
    }
    fn_80207A54(file.f36, file.f40->f12);
    s = file.f44;
    if (self->f20 != 0) self->s1();
    s->r2(lbl_802E59D0, 116, 0);
    fn_800FB000(s, 88);
    self->f20 = fn_800FADA8(s);
    fn_800F8E38(self, self->f20);
    fn_80135CDC(a, self);
    self->s2(a);
    for (i = 0; i < self->f20; i++) {
        fn_800FB000(s, 88);
        fn_800FB064(s, buf);
        Load(self, buf, self->s3(i), a, s);
    }
    fn_800FAEA0(s);
    for (j = 0; j < self->f20; j++) {
        self->s3(j)->o0(a);
    }
    fn_802079F0(file.f36, 0);
    fn_80215BFC(&file);
}

} /* extern "C" */
