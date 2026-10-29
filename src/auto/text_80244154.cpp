// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct C80243F5C { C80243F5C(); ~C80243F5C(); u8 b[44]; };
struct OV { u8 pad[292]; virtual void v0(); virtual void v1(); virtual void s2(char *, int, int); };
struct C80215F50 { C80215F50(); ~C80215F50(); u8 pad[44]; OV *o44; u8 pad48[8]; };
struct GV {
    u8 pad[1696];
    s32 i1696;
    u8 pad1700[20];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual s32 s5(char *);
};
extern "C" {
struct P {
    u8 pad0[16];
    virtual void v0(); virtual void s1();
    s32 i20;
    C80243F5C *arr;
    u32 n28;
};
extern void *lbl_8035B4D0;
extern void *lbl_8035B308;
extern u8 *lbl_8035B65C;
extern char lbl_80366210[4], lbl_80366214[4];
extern char lbl_802F1AE0[];
void fn_800F8E38(P *, u32);
void fn_800604C4(int, int, int, int);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_800F6FBC(char *, char *);
void *fn_800F8274(P *, char *);
void fn_8024372C(void *, void *, char *, char ***);
void fn_800F87F0(P *, char *, void *);
void fn_800F6E88(char *, u8 *);
void fn_800F6E40(char *, char *);
GV *fn_8021616C(void *);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
s32 fn_80215C84(C80215F50 *, char *, char *, int, int);
void fn_80243FD8(P *, OV *);

static inline s32 find(P *p, void *o) {
    s32 i;
    for (i = 0; i < (s32)p->n28; i++) {
        if (&p->arr[i] == o) return i;
    }
    return -1;
}

s32 fn_80244154(P *p, u32 n, char **list, u8 *node) {
    u32 off;
    char ***pl;
    if (p->i20) p->s1();
    p->i20 = 1;
    p->n28 = n;
    fn_800F8E38(p, n);
    if (!lbl_8035B4D0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B4D0);
    p->arr = new C80243F5C[n];
    fn_800F7E98();
    if (!p->arr) fn_800604C4(-4, 0, 0, 0);
    pl = &list;
    off = 0;
    while (**list) {
        char buf[8];
        void *o;
        s32 idx;
        fn_800F6FBC(*list, buf);
        list++;
        o = fn_800F8274(p, buf);
        idx = find(p, o);
        if (idx == -1) {
            fn_8024372C((u8 *)p->arr + off, lbl_8035B308, buf, pl);
            fn_800F87F0(p, buf, (u8 *)p->arr + off);
            off += 44;
        } else {
            fn_8024372C(&p->arr[idx], lbl_8035B308, buf, pl);
        }
    }
    if (node) {
        char nm[8];
        fn_800F6E88(nm, node + 140);
        if (nm[0]) {
            char s[12];
            fn_800F6E40(s, nm);
            char t[64];
            {
                C80215F50 f;
                GV *g = fn_8021616C(*(void **)(lbl_8035B65C + 8));
                if (g->i1696 == 5) {
                    strcpy(t, s);
                    strcat(t, lbl_80366214);
                    if (g->s5(t)) goto done;
                }
                if (fn_80215C84(&f, s, lbl_80366210, 2, 0)) goto done;
                {
                    OV *o = f.o44;
                    o->s2(lbl_802F1AE0, 2, 0);
                    fn_80243FD8(p, o);
                }
            }
        }
    }
done:
    return 0;
}

} /* extern "C" */
