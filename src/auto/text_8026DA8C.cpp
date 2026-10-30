// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct Q { virtual void q0(); virtual s32 busy(); u8 pad[464]; Q *next; };
struct Y { u8 pad[88]; virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void idle(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void stop(s32); virtual void fade(s32, f32);
    u8 pad2[176 - 92]; Q *q; };
struct W { u8 pad[16]; virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual Y *getA(u32); virtual Y *getB(u32); u32 pad20; u32 nb; };
struct Wh { u8 pad[36]; virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3(); virtual void h4(); virtual void h5(); virtual void h6(); virtual void h7(); virtual W *get(s32); };
struct Gv { u8 pad[36]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void setVol(f32); };
struct G { u8 pad[256]; virtual void h0(); virtual void h1(); virtual void h2(); virtual void tick(Gv *, f32); };
struct Ent { Y *p; u32 q; };
struct S { u8 pad[24]; Wh *f24; f32 f28; f32 *vol; Y *a36; Y *a40; Y *a44; u8 pad48[56 - 48]; u32 n56; u8 pad60[68 - 60]; u32 n68; Ent ent[40]; u8 pad3[428 - 392]; s32 f428; };
extern "C" {
extern f32 lbl_80366DD4;
extern G *lbl_8035B7C8;
extern Gv *lbl_8035B7C4;

void fn_8026DA8C(S *s, f32 dt) {
    u32 i;
    if (lbl_80366DD4 != *s->vol - s->f28 && !s->f428) {
        if (s->a36) s->a36->fade(0, *s->vol);
        if (s->a40) s->a40->fade(0, *s->vol);
        if (s->a44) s->a44->fade(0, *s->vol);
        if (s->f24) {
            W *w = s->f24->get(0);
            for (i = 0; i < s->n56; i++) w->getA(i)->fade(0, *s->vol);
            for (i = 0; i < w->nb; i++) w->getB(i)->fade(0, *s->vol);
        }
        for (i = 0; i < s->n68; i++) s->ent[i].p->fade(0, *s->vol);
        lbl_8035B7C4->setVol(*s->vol);
        s->f28 = *s->vol;
    }
    if (s->f428) s->f428 = 0;
    for (i = 0; i < s->n68; i++) {
        if (s->ent[i].q) {
            s32 f = 0;
            Q *q;
            for (q = s->ent[i].p->q; q; q = q->next) {
                if (q->busy()) f = 1;
            }
            if (!f) {
                s->ent[i].q = 0;
                s->ent[i].p->idle();
            }
        }
    }
    lbl_8035B7C8->tick(lbl_8035B7C4, dt);
}

} /* extern "C" */
