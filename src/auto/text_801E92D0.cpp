// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct X801E92D0 { u8 pad[80]; void *f80; };
struct P801E92D0 { u8 pad[40]; u8 f40[8]; X801E92D0 *f48; X801E92D0 *f52; X801E92D0 *f56; X801E92D0 *f60; };
void fn_801907D8(X801E92D0 *);
void *fn_8019556C(X801E92D0 *);
void fn_80190888(X801E92D0 *, void *, void *);
static inline X801E92D0 *getA(P801E92D0 *p) { return p->f60 ? p->f60 : p->f56; }
static inline X801E92D0 *getB(P801E92D0 *p) { return p->f52 ? p->f52 : p->f48; }
static inline void upd(P801E92D0 *p) { X801E92D0 *x = getA(p); if (x->f80) fn_801907D8(x); }
void fn_801E92D0(P801E92D0 *p) {
    X801E92D0 *o = getA(p);
    void *r;
    upd(p);
    r = fn_8019556C(getB(p));
    fn_80190888(o, r, p->f40);
}

} /* extern "C" */
