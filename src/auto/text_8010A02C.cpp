// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern "C" { void *memset(void *, int, unsigned long); unsigned long strlen(const char *); }
extern void *lbl_8035AAB8;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
struct Str { void *f0; u8 pad[16]; };
struct T { void *f0; u8 pad4[4]; virtual void v0(); virtual void v1(); virtual void clear(); Str s12; Str s32; int f52; void *f56; };
void fn_8010C3BC(T *, void *);
void fn_8010C4B8(void *, u32 *, u32 *);
void fn_800FB700(Str *, u16 *, u32);
void fn_800FB9D4(Str *, char *, u32);
void fn_800FA5D8(Str *, const char *);
int fn_8010A02C(T *t, void *x, const char *s) {
    u32 a;
    u32 sz;
    u32 len;
    Str *cur = t->f52 ? &t->s32 : &t->s12;
    if (cur->f0) t->clear();
    fn_8010C3BC(t, x);
    if (t->f52) {
        fn_8010C4B8(t->f0, &a, &sz);
        len = strlen(s) + 2;
        if (sz != 0x7FFFFFFF && sz > len) len = sz;
        if (lbl_8035AAB8 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035AAB8);
        u16 *buf = new u16[len];
        fn_800F7E98();
        if (buf == 0) fn_800604C4(-4, 0, 0, 0);
        t->f56 = buf;
        memset(buf, 0, len);
        fn_800FB700(&t->s32, buf, len);
        fn_800FA5D8(&t->s32, s);
    } else {
        fn_8010C4B8(t->f0, &a, &sz);
        len = strlen(s) + 1;
        if (sz != 0x7FFFFFFF && sz > len) len = sz;
        if (lbl_8035AAB8 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035AAB8);
        char *buf = new char[len];
        fn_800F7E98();
        if (buf == 0) fn_800604C4(-4, 0, 0, 0);
        t->f56 = buf;
        memset(buf, 0, len);
        fn_800FB9D4(&t->s12, buf, len);
        fn_800FA5D8(&t->s12, s);
    }
    return 0;
}

} /* extern "C" */
