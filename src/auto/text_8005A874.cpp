#include "common.h"
extern "C" {
struct Q_A874 { struct Q_A874 *f0; u8 pad4[0xc]; char *f10; };
struct L_A874 { u8 pad[0xc]; f32 *fc; };
struct P_A874 {
    u8 pad0[0x11c];
    s32 f11c;
    u8 pad120[4];
    s32 f124;
    s32 f128;
    u8 pad12c[4];
    void *f130;
    u8 pad134[0xc];
    Q_A874 *f140;
    L_A874 *f144;
    f32 f148;
};
extern char lbl_80296EC0[];
extern char lbl_8035E298[4];
extern char lbl_8035E35C[2];
extern char lbl_8035E360[6];
extern char lbl_8035E368[5];
extern f32 lbl_8035E354;
extern u8 *lbl_8035B65C;
void fn_800FA474(char *, char *, int);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
char *strncpy(char *, const char *, u32);
void *memcpy(void *, const void *, u32);
char *fn_8023F52C(P_A874 *, char *, char *, char *, s32, s32);
Q_A874 *fn_8023F4A0(P_A874 *, char *, char *, char *, s32);
void *fn_801104C0(void *, char *, void *, int);
void *fn_8010FEDC(void *, void *, char *, int);
void fn_800F6E88(char *, char *);
void fn_80234028(void *, char *, char *, char *);
void fn_802490E0(P_A874 *, int, f32);
void fn_802494A4(P_A874 *, int);
void __ct__9C80253F24Fiiii(void *, char *, int, int, int);

#pragma opt_propagation off
void fn_8005A874(P_A874 *p) {
    s32 off;
    char b148[256];
    char b48[256];
    char b38[16];
    char b28[16];
    char b1c[9];
    char b10[9];
    char b8[8];
    char *str = lbl_80296EC0;
    char *snd;
    Q_A874 *q;
    s32 n, i;
    fn_800FA474(p->f140->f10 + p->f124 * 20, b38, 16);
    strcpy(b148, str + 0x54);
    strcat(b148, b38);
    strcat(b148, lbl_8035E35C);
    snd = fn_8023F52C(p, lbl_8035E298, b148, lbl_8035E360, 0, 0);
    q = fn_8023F4A0(p, lbl_8035E298, b148, str + 0x60, 0);
    if (q) n = (s32)q->f0->f10;
    else n = 1;
    for (i = 0, off = 0; i < n; i++, off += 20) {
        char *name;
        s32 *cnt;
        void *set;
        char *grp;
        s32 j;
        void *mgr;
        if (q) fn_800FA474(q->f10 + off, b28, 16);
        else strcpy(b28, b38);
        strcpy(b48, str + 0x70);
        strcat(b48, b28);
        strcat(b48, lbl_8035E35C);
        name = fn_8023F52C(p, lbl_8035E298, b48, lbl_8035E368, 1, 0);
        strncpy(b1c, name, 8);
        b1c[8] = 0;
        cnt = (s32 *)fn_8023F52C(p, lbl_8035E298, b48, str + 0x7c, 1, 0);
        mgr = lbl_8035B65C + 0x90;
        set = fn_801104C0(mgr, b1c, 0, 0);
        grp = fn_8023F52C(p, lbl_8035E298, b48, str + 0x88, 0, 0);
        for (j = 0; j < *cnt; j++) {
            fn_800F6E88(b10, b28);
            b10[6] = j / 10 + '0';
            b10[7] = j % 10 + '1';
            b10[5] = 'S';
            b10[8] = 0;
            if (fn_8010FEDC(mgr, set, b10, 0)) {
                memcpy(b8, b10, 8);
                if (grp) fn_80234028(p->f130, b8, name, grp);
                else fn_80234028(p->f130, b8, name, 0);
            } else {
                if (grp) fn_80234028(p->f130, 0, name, grp);
                else fn_80234028(p->f130, 0, name, 0);
            }
        }
    }
    if (snd) __ct__9C80253F24Fiiii(lbl_8035B65C, snd, 0, 0, 0);
    p->f124++;
    if (p->f128 > p->f124) {
        if (p->f11c == 1) p->f148 = lbl_8035E354 + p->f144->fc[0];
        else fn_802490E0(p, 0, lbl_8035E354 + p->f144->fc[p->f124]);
    } else {
        fn_802494A4(p, 2);
    }
}
#pragma opt_propagation reset
}
