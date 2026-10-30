// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

#define F(p,o,t) (*(t*)((u8*)(p)+(o)))
struct Node { Node *parent; Node *child; Node *next; Node *prev; Node *selNext; int pad14; int open; int sel; };
struct Scr { u8 pad_[128]; virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void key(u32, int); virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71(); virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75(); virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79(); virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83(); virtual void s84(); virtual void setPos(f32); };
struct Own { u8 pad_[52]; virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void post(int, u32); };
extern f32 lbl_80365188;
extern f32 lbl_8036518C;
extern f32 lbl_803596E0[];
Scr *fn_801D9744(void *, void *, u32);
static inline Node *nextVis(Node *n) {
    Node *r;
    if ((r = n->child) && n->open) return r;
    if ((r = n->next)) return r;
    for (r = n->parent; r; r = r->parent) {
        if (r->next) { r = r->next; break; }
    }
    return r;
}
static inline f32 rowPos(u8 *t, Node *n) {
    Node *q = F(t,0x2ec,Node*);
    f32 y = lbl_80365188;
    for (; q; ) {
        if (q == n) return y;
        q = nextVis(q);
        y += F(t,0x334,f32);
    }
    return -lbl_803596E0[0];
}
static inline void scrollTo(u8 *t, Node *n) {
    f32 y;
    if (!n) return;
    y = rowPos(t, n);
    if (y != -lbl_803596E0[0]) {
        f32 top;
        f32 row;
        f32 vis;
        f32 bot;
        vis = (F(t,0x54,f32) - F(t,0x4c,f32)) / F(t,0x334,f32);
        top = -F(t,0x33c,f32) / F(t,0x334,f32);
        row = y / F(t,0x334,f32);
        F(t,0x310,Node*) = n;
        bot = top + vis;
        if (row < top) {
            if (F(t,0x2e0,Scr*)) F(t,0x2e0,Scr*)->setPos(row);
        }
        if (row >= bot - lbl_8036518C) {
            if (F(t,0x2e0,Scr*)) F(t,0x2e0,Scr*)->setPos(lbl_8036518C + (row - vis));
        }
    }
}
static inline void scrollTo2(u8 *t, Node *n) {
    f32 y;
    if (!n) return;
    y = rowPos(t, n);
    if (y != -lbl_803596E0[0]) {
        f32 top;
        f32 bot;
        f32 row;
        f32 vis;
        vis = (F(t,0x54,f32) - F(t,0x4c,f32)) / F(t,0x334,f32);
        top = -F(t,0x33c,f32) / F(t,0x334,f32);
        row = y / F(t,0x334,f32);
        F(t,0x310,Node*) = n;
        bot = top + vis;
        if (row < top) {
            if (F(t,0x2e0,Scr*)) F(t,0x2e0,Scr*)->setPos(row);
        }
        if (row >= bot - lbl_8036518C) {
            if (F(t,0x2e0,Scr*)) F(t,0x2e0,Scr*)->setPos(lbl_8036518C + (row - vis));
        }
    }
}
struct Own2 { u8 pad_[128]; virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59(); virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65(); virtual void s66(); virtual void notify(u8 *); };
void fn_801D2780(u8 *t, Node *n);
static inline int isAnc(Node *q, Node *n) {
    int r;
    for (; q; q = q->parent) {
        if (q == n) { r = 1; goto done; }
    }
    r = 0;
done:
    return r;
}
static inline void ens(u8 *t, Node *n) { if (isAnc(F(t,0x310,Node*), n)) scrollTo(t, n); }
int fn_801D3634(u8 *t, u32 key, int a) {
    if (F(t,0x144,u32) == 32) {
        Node *c = F(t,0x310,Node*);
        if (c && c->child) {
            Node *n;
            c->open = (u32)__cntlzw(c->open) >> 5;
            if (!F(t,0x310,Node*)->open) fn_801D2780(t, F(t,0x310,Node*));
            ens(t, F(t,0x30c,Node*));
            F(t,0x164,int) = 1;
        }
    }
    if (F(t,0x144,u32) == 16) {
        F(t,0x144,u32) = 32;
        if (F(t,0x11c,Own2*)) F(t,0x11c,Own2*)->notify(t);
    }
    if (a && F(t,0x70,Own*)) F(t,0x70,Own*)->post(16, F(t,0x68,u32));
    return 0;
}

} /* extern "C" */
