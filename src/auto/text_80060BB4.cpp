// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern "C" { char *strcpy(char *, const char *); unsigned long strlen(const char *); }
typedef struct S28 { u8 pad[12]; char *fC; } S28;
struct P;
struct C80215F50 { u8 pad0[36]; void *f24; S28 *f28; P *f2C; u8 pad30[8]; C80215F50(); ~C80215F50(); };
extern char lbl_80297594[], lbl_802975A0[], lbl_8035E570[8], lbl_8035E604[4];
extern u8 lbl_802BCE28[];
extern char lbl_80357740[];
extern int lbl_8035ABF8;
struct P { u8 pad[292]; virtual void p0(); virtual void p1(); virtual void init(void *, int, int); virtual void p3(); virtual void p4(); virtual int next(); };
struct K { u8 pad[1720]; virtual void k0(); virtual void k1(); virtual void k2(); virtual void k3(); virtual void k4(); virtual int has(const char *); };
struct T { u8 pad[13284]; K *f13284; u8 pad13288[676]; int f13964, f13968, f13972, f13976, f13980, f13984, f13988, f13992, f13996, f14000, f14004, f14008, f14012, f14016, f14020, f14024, f14028, f14032; void *f14036; };
s32 fn_80215C84(C80215F50 *, const char *, const char *, s32, s32);
void fn_80215BFC(C80215F50 *);
void fn_80060E30(s32, const char *, ...);
void fn_800FAEF8(P *);
int fn_800FB33C(P *);
char *fn_800FB284(P *);
void *fn_8023C894(void *, char *);
static inline void up(char *str) {
    u32 i;
    char *s = str;
    for (i = 0; i < strlen(str); s++, i++) {
        if (*s >= 'a' && *s <= 'z') *s = *s - 32;
    }
}
void fn_80060BB4(T *t) {
    C80215F50 f;
    if (t->f13284->has(lbl_80297594)) return;
    s32 r;
    if ((r = fn_80215C84(&f, lbl_8035E570, lbl_8035E604, 2, 0)) != 0) fn_80060E30(r, lbl_802975A0);
    P *p = f.f2C;
    p->init(lbl_802BCE28, 23, 0);
    fn_800FAEF8(p);
    u32 tok;
    while ((tok = p->next()) != 6) {
        switch (tok) {
        case 57:
            t->f14028 = fn_800FB33C(p);
            t->f14032 = fn_800FB33C(p);
            break;
        case 58: {
            strcpy(lbl_80357740, fn_800FB284(p));
            up(lbl_80357740);
            break;
        }
        case 59: t->f13964 = 0; break;
        case 60: t->f13968 = 1; break;
        case 61: t->f13976 = 0; break;
        case 64: t->f13980 = 1; break;
        case 66: t->f13984 = 1; break;
        case 67: t->f13988 = 0; break;
        case 68: t->f13992 = 0; break;
        case 69: t->f14000 = 1; break;
        case 70: t->f14000 = 1; break;
        case 72: t->f14012 = 1; break;
        case 65: t->f14016 = 1; break;
        case 73: t->f14024 = 1; break;
        case 75: t->f13996 = 1; break;
        case 74: t->f14020 = fn_800FB33C(p); break;
        case 76: t->f14008 = 1; break;
        case 77: t->f14036 = fn_8023C894(&t->f14036, fn_800FB284(p)); break;
        case 79: lbl_8035ABF8 = 1; break;
        }
    }
    fn_80215BFC(&f);
}

} /* extern "C" */
