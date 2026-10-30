// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct OV { u8 pad[8]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual u32 s5(int); };
struct A { u8 pad[12]; void *x; void *y; };
struct P { u8 pad0[12]; void *a12; u8 pad16[136]; u32 a152, a156, a160, a164, a168; u8 pad172[52]; A *a224; };
static const char sPad[68] = {1};
static const char s68[] = "abLoopAnimation";
static const char s84[] = "MinSoundDist";
static const char s100[] = "MaxSoundDist";
static const char s116[] = "SoundPriority";
static const char s132[] = "VolumeAttenuation";
extern char lbl_80366138[4];
void *fn_8010FEDC(void *, void *, const char *, int);
void fn_8023D1B4(P *);

static inline u32 get0(P *p, const char *name) {
    void *x = p->a224->x;
    void *y = p->a224->y;
    if (x && y) {
        u32 *r;
        if (lbl_80366138[0]) y = fn_8010FEDC(p->a12, y, lbl_80366138, 1);
        r = (u32 *)fn_8010FEDC(x, y, name, 1);
        if (r) return *r;
    }
    return 0;
}
static inline u32 getv(P *p, const char *name) {
    void *x = p->a224->x;
    void *y = p->a224->y;
    if (x && y) {
        OV **r;
        if (lbl_80366138[0]) y = fn_8010FEDC(p->a12, y, lbl_80366138, 1);
        r = (OV **)fn_8010FEDC(x, y, name, 1);
        if (r) return (*r)->s5(0);
    }
    return 0;
}

void fn_8023F214(P *p) {
    p->a152 = get0(p, s68);
    p->a156 = getv(p, s84);
    p->a160 = getv(p, s100);
    p->a164 = getv(p, s116);
    p->a168 = getv(p, s132);
    fn_8023D1B4(p);
}

} /* extern "C" */
