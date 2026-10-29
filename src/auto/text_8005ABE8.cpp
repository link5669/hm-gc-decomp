// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern char lbl_80296EC0[];
extern char lbl_8035E298[4];
extern char lbl_8035E35C[2];
extern char lbl_8035E360[6];
extern char lbl_8035E368[5];
extern char lbl_8035E370[7];
extern char lbl_8035E378[8];
extern char lbl_8035E380[7];
struct G8005ABE8 { u8 pad[72]; u32 f72; };
extern G8005ABE8 *lbl_8035B308;
extern u8 *lbl_8035B65C;
struct X8005ABE8 { u8 pad[8]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual char *name(s32); };
struct N8005ABE8 { u8 pad[12]; N8005ABE8 *next; N8005ABE8 *child; };
struct R8005ABE8 { u8 pad[16]; u32 f16; };
struct P8005ABE8 { R8005ABE8 *r; };
struct S8005ABE8 { u8 pad[224]; u32 f224; u8 pad228[68]; u32 f296; u32 f300; u32 f304; char *f308; f32 f312; void *f316; P8005ABE8 *f320; void *f324; };
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
char *strncpy(char *, const char *, u32);
f32 *fn_8023F52C(S8005ABE8 *, char *, char *, char *, s32, s32);
void *fn_8023F4A0(S8005ABE8 *, char *, char *, char *, s32);
N8005ABE8 *fn_8010FFD0(void *, char *, s32);
void *fn_8010FEDC(void *, N8005ABE8 *, char *, s32);
void *fn_801104C0(void *, char *, s32, s32);
void fn_8010CA7C(N8005ABE8 *);
void fn_8010CAF4(N8005ABE8 *, void *);
void fn_8005ADD0(S8005ABE8 *, void *, N8005ABE8 *);

#pragma opt_propagation off
void fn_8005ABE8(S8005ABE8 *self) {
    char *str = lbl_80296EC0;
    char path[256];
    char name[256];
    char tag[9];
    f32 *pf;
    void *m;
    N8005ABE8 *o;
    N8005ABE8 *next;
    N8005ABE8 *c;
    N8005ABE8 *n;
    void *h;
    self->f300 = lbl_8035B308->f72;
    self->f304 = self->f224;
    strcpy(path, lbl_8035E370);
    strcat(path, self->f308);
    strcat(path, lbl_8035E35C);
    pf = fn_8023F52C(self, lbl_8035E298, path, str + 152, 0, 0);
    if (pf != 0) {
        self->f312 = *pf;
    }
    self->f316 = fn_8023F52C(self, lbl_8035E298, path, lbl_8035E360, 0, 0);
    self->f320 = (P8005ABE8 *)fn_8023F4A0(self, lbl_8035E298, path, lbl_8035E378, 1);
    self->f324 = fn_8023F4A0(self, lbl_8035E298, path, str + 164, 1);
    self->f296 = self->f320->r->f16;
    strcpy(name, str + 112);
    m = lbl_8035B65C + 144;
    for (n = fn_8010FFD0(m, name, 0)->child; n != 0; n = n->next) {
        o = (N8005ABE8 *)fn_8010FEDC(m, n, lbl_8035E380, 0);
        if (o != 0) {
            X8005ABE8 *x = *(X8005ABE8 **)fn_8010FEDC(m, n, lbl_8035E368, 0);
            strncpy(tag, x->name(0), 8);
            tag[8] = 0;
            h = fn_801104C0(m, tag, 0, 0);
            for (c = o->child; c != 0; c = next) {
                next = c->next;
                fn_8010CA7C(c);
                fn_8010CAF4(c, h);
                fn_8005ADD0(self, h, c);
            }
        }
    }
}
#pragma opt_propagation reset

} /* extern "C" */
