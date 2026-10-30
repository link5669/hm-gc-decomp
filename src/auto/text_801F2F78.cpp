// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct Strm {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual int more(); virtual void fill();
    u8 *cur; u8 *end; s32 bit;
};
struct Huf { u8 pad[4]; s32 max[15]; s32 min[15]; s32 vp[288]; s32 vals[1]; };
extern "C" {
extern char lbl_802A4540[];
void fn_80060568(char *, int, int, int);
static inline bool eof(Strm *s) { return s->cur < s->end || !s->more(); }
static inline bool atEnd(Strm *s) { bool r = eof(s); return r; }
static inline bool getBit(Strm **pp) {
    Strm *s = *pp;
    if (s->bit >= 8) {
        s->cur++;
        (*pp)->bit = 0;
        if ((*pp)->cur >= (*pp)->end) {
            (*pp)->fill();
            if (!atEnd(*pp)) fn_80060568(lbl_802A4540, 0, 0, 0);
        }
    }
    s = *pp;
    s32 v = *s->cur >> s->bit++;
    return v & 1;
}
s32 fn_801F2F78(Huf *h, Strm **pp) {
    s32 code = getBit(pp);
    s32 i = 0;
    while (code > h->max[i]) {
        code = (code << 1) | getBit(pp);
        i++;
    }
    return h->vals[h->vp[i] + (code - h->min[i])];
}

} /* extern "C" */
