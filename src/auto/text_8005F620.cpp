// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct U { u8 pad[104]; virtual void u0(); virtual void u1(); virtual void u2(); virtual void u3(); virtual void u4(); virtual void u5(); virtual ~U(); virtual void u7(); virtual void u8_(); virtual void u9(); virtual void kill(); };
struct Z1 { u8 pad[60]; f32 w, x, y, z; };
struct Z { u8 pad[16]; Z1 *z; };
struct E { u8 pad[108]; Z *f108; };
struct W { u8 pad[16]; virtual void w0(); virtual void stop(); };
struct Mg { virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9(); virtual void rel(W *w); };
struct G2 { u8 pad[11332]; Mg *m; };
struct G { u8 pad[12]; G2 *g; };
struct P8 { u32 a, b; };
struct T { u8 pad[608]; s32 f608; u8 pad1[720 - 612]; u32 f720, f724; f32 s[3]; U *u0; U *u1; E *e; U *uu[2]; U *vv[6]; u32 f784; f32 c[4]; P8 f804[3]; u32 f828, f832; W *w; f32 f840;
    u8 pad4[868 - 844]; u32 f868; f32 f872; u32 f876; u8 pad7[884 - 880]; u8 f884; };
extern "C" {
extern G *lbl_8035B460;
extern f32 lbl_8035E4A8;
extern f32 lbl_8035E4CC;
void fn_8013E8C0(P8 *p);
void fn_80232B68(T *t);

void fn_8005F620(T *t) {
    u32 i;
    if (t->w) {
        t->w->stop();
        lbl_8035B460->g->m->rel(t->w);
    }
    if (t->e) {
        Z *z = t->e->f108;
        z->z->x = t->c[0];
        z->z->y = t->c[1];
        z->z->z = t->c[2];
        z->z->w = t->c[3];
    }
    if (t->u0) { t->u0->kill(); delete t->u0; t->u0 = 0; }
    if (t->u1) { t->u1->kill(); delete t->u1; t->u1 = 0; }
    for (i = 0; i < 2; i++) {
        if (t->uu[i]) { t->uu[i]->kill(); delete t->uu[i]; }
    }
    for (i = 0; i < 6; i++) {
        if (t->vv[i]) { t->vv[i]->kill(); delete t->vv[i]; }
    }
    for (i = 0; i < 3; i++) fn_8013E8C0(&t->f804[i]);
    fn_80232B68(t);
    t->f840 = lbl_8035E4A8;
    t->s[0] = lbl_8035E4A8;
    t->s[1] = lbl_8035E4A8;
    t->s[2] = lbl_8035E4A8;
    t->uu[0] = 0; t->uu[1] = 0;
    t->vv[0] = 0; t->vv[1] = 0; t->vv[2] = 0; t->vv[3] = 0; t->vv[4] = 0; t->vv[5] = 0;
    t->u0 = 0; t->u1 = 0;
    t->f720 = 0; t->f724 = 0;
    t->f608 = 1;
    t->e = 0;
    t->f868 = 0; t->f876 = 0;
    t->f872 = lbl_8035E4CC;
    t->f884 = 0;
    t->f828 = 0; t->f832 = 0; t->w = 0;
}

} /* extern "C" */
