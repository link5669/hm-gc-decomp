// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct S { u8 pad[68]; char name[200]; };
struct ST { u8 pad[32]; u32 a32; u32 time; u8 pad40[64]; u32 a104; };
struct FI { u32 a0; u32 fileNo; u8 pad8[12]; };
struct TM { s32 sec, min, hour, mday, mon, year, wday, yday, msec, usec; };
struct OBJ { u8 pad[8]; u32 fl; };
struct M {
    u8 pad0[1720];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual s32 s14(); virtual OBJ *s15();
    u32 *chan;
    u8 st1728[448];
    s32 fileNo;
    s32 a2180;
    s32 a2184;
};
extern char lbl_80365818[4];
void fn_800FA474(char *, char *, int);
s32 fn_800D22F0(u32, char *, FI *);
s32 fn_8020B114(s32);
s32 fn_800D339C(u32, s32, ST *);
void fn_800BA7DC(s64, TM *);
void fn_80214868(S *, s32, s32, s32, s32, s32, s32);
void fn_80214884(S *, s32);
void fn_80214854(S *, int, int, int, int);
void fn_80214834(S *, int, int, int, int, int, int);
s32 fn_800D2C2C(FI *, u8 *, int, int);
s32 fn_800D240C(FI *);
void fn_80214988(u8 *, S *);
void fn_8021488C(u8 *, char *);

s32 fn_8020D85C(M *m, S *s) {
    u8 raw[544];
    ST st;
    TM tm;
    char name[32];
    FI fi;
    s32 r;
    s32 e;
    u8 *buf;
    if (m->s14()) {
        fn_800FA474(s->name, name, 31);
        do r = fn_800D22F0(*m->chan, name, &fi); while (r == -1);
        if (r) return fn_8020B114(r);
        m->fileNo = fi.fileNo;
        do r = fn_800D339C(*m->chan, m->fileNo, &st); while (r == -1);
        if (r) { m->fileNo = -1; return fn_8020B114(r); }
        m->a2180 = st.a32;
        m->a2184 = st.a104;
        fn_800BA7DC((s64)st.time * (*(u32 *)0x800000F8 / 4), &tm);
        fn_80214868(s, tm.year, tm.mon + 1, tm.mday, tm.hour, tm.min, tm.sec);
        fn_80214884(s, m->a2180);
        fn_80214854(s, 0, 0, 0, 0);
        fn_80214834(s, 0, 4, 0, 0, 0, 0);
        buf = (u8 *)(((u32)raw + 31) & ~31);
        do r = fn_800D2C2C(&fi, buf, 512, 0); while (r == -1);
        if (r) e = fn_8020B114(r);
        else if (*(u32 *)(buf + 64) & 1) e = 17;
        else e = 0;
        if (e) {
            do r = fn_800D240C(&fi); while (r == -1);
            m->fileNo = -1;
            m->a2180 = -1;
            m->a2184 = -1;
            return e;
        }
        do r = fn_800D240C(&fi); while (r == -1);
        if (r == 0) {
            fn_80214988(m->st1728, s);
            fn_8021488C(m->st1728, lbl_80365818);
            return 0;
        }
        m->fileNo = -1;
        m->a2180 = -1;
        m->a2184 = -1;
        return fn_8020B114(r);
    }
    {
        OBJ *ob = m->s15();
        r = 12;
        if (ob->fl & 2) r = 11;
    }
    return r;
}

} /* extern "C" */
