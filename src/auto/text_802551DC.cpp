#include "common.h"
extern "C" {
} /* extern "C" */
struct C80226AB0 { u8 pad[10640]; C80226AB0(); };
struct C8027245C { u8 pad[492]; C8027245C(); };
struct C8025245C { u8 pad[8]; C8025245C(); };
struct C80273D98 { u8 pad[20]; C80273D98(); };
struct C802739F0 { u8 pad[8]; C802739F0(); };
struct R4 { f32 v[4]; R4(f32 a, f32 b, f32 c, f32 d) { *(volatile f32 *)&v[0] = a; *(volatile f32 *)&v[1] = b; *(volatile f32 *)&v[2] = c; *(volatile f32 *)&v[3] = d; } };
struct V3c { f32 x, y, z; V3c() {} V3c(f32 a, f32 b, f32 c) { *(volatile f32 *)&x = a; *(volatile f32 *)&y = b; *(volatile f32 *)&z = c; } };
struct VR { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void *v8(); };
struct VM { u8 pad[48]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual VR *v15(); };
struct VF { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void *v25(); };
extern "C" {
typedef struct A4 { u8 pad[16]; VF *f16; u8 pad2[4]; VM *f24; } A4;
typedef struct A24 { u8 pad[8]; void *f8; } A24;
typedef struct B { u8 pad[13160]; s32 f13160; u8 p1[13172 - 13164]; void *f13172; void *f13176; u8 p2[4]; void *f13184; u8 p3[13200 - 13188]; void *f13200; u8 p4[13232 - 13204]; void *f13232; } B;
typedef struct S {
    u8 pad0[4]; A4 *f4; s32 f8; u8 p1[12]; A24 *f24; u8 *f28; void *f32; B *f36; void *f40; void *f44;
    u8 p2[112 - 48]; C80226AB0 *f112; C8027245C *f116; u8 p3[128 - 120]; s32 f128; s32 f132; u8 p4[144 - 136];
    u8 f144[728 - 144]; u8 f728[756 - 728]; C8025245C *f756; C80273D98 *f760; C802739F0 *f764;

} S;
typedef struct S2 { u8 pad[640]; u32 f640; u32 f644; u8 p[656 - 648]; void *f656; void *f660; void *f664; } S2;
typedef struct G65C { u8 pad[36]; B *f36; } G65C;
typedef struct G488 { u8 pad[10224]; u32 f10224; } G488;
typedef struct G5E4 { u8 pad[36]; s32 f36; } G5E4;
extern G65C *volatile lbl_8035B65C;
extern G488 *volatile lbl_8035B488;
extern s32 *lbl_8035B7AC;
extern G5E4 *lbl_8035B5E4;
extern void *lbl_8035B658;
extern u8 lbl_8035784C[];
extern u8 lbl_803578F0[];
extern char lbl_803665D0[8];
extern char lbl_803665D8[6];
extern char lbl_803665E0[7];
extern volatile f32 lbl_803665A8;
extern f32 lbl_803665B8;
extern f32 lbl_803665F4;
#define VS(a) (*(volatile f32 *)&(a))
void fn_80129938(void *, void *);
void fn_8012962C(void *, f32, f32, f32, f32);
void fn_80129564(void *, const f32 *r, f32 c, f32 d);
void fn_80129710(void *, const f32 *a, const f32 *b, const f32 *c);
void fn_801AA7F4(void *, u32, u32);
void fn_8018B5E4(void *, s32);
void fn_800FD050(void *, s32, s32);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_802266B4(void *);
void fn_80272028(void *);
void fn_8014CBA4(void *, void *);
void fn_802523EC(void *);
void fn_80273D08(void *);
void fn_80273980(void *);
void fn_802514B8(G5E4 *, char *, void *);

void fn_802551DC(S *s, u8 *b, s32 a5, u32 a6, u32 a7) {
    S2 *s2 = (S2 *)s;
    G5E4 *g;
    lbl_8035B65C = (G65C *)s;
    lbl_8035B488->f10224 &= ~2;
    s->f24 = (A24 *)(b + 12352);
    s->f4 = (A4 *)(b + 11316);
    s->f8 = a5;
    s->f28 = (u8 *)s->f24->f8;
    s->f32 = ((void **)s->f4)[6];
    s->f36 = (B *)b;
    s2->f640 = a6;
    s2->f644 = a7;
    s->f40 = s->f4->f16->v25();
    fn_80129938(s->f40, s->f32);
    fn_8012962C(s->f40, lbl_803665F4, 1.3333334f, 0.1f, 10000.0f);
    s->f44 = s->f4->f16->v25();
    fn_80129938(s->f44, s->f32);
    {
        f32 b_ = (f32)s2->f644; f32 a_ = (f32)s2->f640; f32 k0 = lbl_803665B8;
        R4 r(k0, k0, a_, b_);
        fn_80129564(*(void *volatile *)&s->f44, r.v, k0, lbl_803665A8);
    }
    {
        V3c eye, at, up;
        VS(eye.x) = s2->f640;
        f32 k = VS(lbl_803665B8);
        VS(eye.y) = k; VS(eye.z) = k;
        VS(at.x) = eye.x; VS(at.y) = k; VS(at.z) = k;
        { f32 z = at.z + lbl_803665A8; VS(up.x) = k; VS(at.z) = z; }
        VS(up.y) = -1.0f; VS(up.z) = k;
        fn_80129710(s->f44, &eye.x, &at.x, &up.x);
    }
    s->f128 = lbl_8035B7AC[0];
    s->f132 = lbl_8035B7AC[1];
    fn_801AA7F4(lbl_8035B65C->f36->f13232, s2->f640, s2->f644);
    fn_8018B5E4(lbl_8035784C, 10);
    fn_800FD050(lbl_803578F0, 6, 10);
    if (lbl_8035B658 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B658);
    s->f112 = new C80226AB0;
    fn_800F7E98();
    if (s->f112 == 0) fn_800604C4(-4, 0, 0, 0);
    fn_802266B4(s->f112);
    if (lbl_8035B658 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B658);
    s->f116 = new C8027245C;
    fn_800F7E98();
    if (s->f116 == 0) fn_800604C4(-4, 0, 0, 0);
    fn_80272028(s->f116);
    {
        void *p = (u8 *)s->f112 + 10596;
        B *bb = s->f36;
        bb->f13172 = s->f40;
        bb->f13200 = p;
        bb->f13184 = s->f144;
        bb->f13160 = lbl_8035B5E4->f36;
        fn_8014CBA4(s->f728, s->f28 + 32);
        bb->f13176 = s->f728;
    }
    g = lbl_8035B5E4;
    if (lbl_8035B658 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B658);
    s->f756 = new C8025245C;
    fn_800F7E98();
    if (s->f756 == 0) fn_800604C4(-4, 0, 0, 0);
    fn_802523EC(s->f756);
    fn_802514B8(g, lbl_803665D0, s->f756);
    if (lbl_8035B658 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B658);
    s->f760 = new C80273D98;
    fn_800F7E98();
    if (s->f760 == 0) fn_800604C4(-4, 0, 0, 0);
    fn_80273D08(s->f760);
    fn_802514B8(g, lbl_803665D8, s->f760);
    if (lbl_8035B658 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B658);
    s->f764 = new C802739F0;
    fn_800F7E98();
    if (s->f764 == 0) fn_800604C4(-4, 0, 0, 0);
    fn_80273980(s->f764);
    fn_802514B8(g, lbl_803665E0, s->f764);
    s2->f656 = s->f4->f24->v15()->v8();
    s2->f660 = s->f4->f24->v15()->v8();
    s2->f664 = s->f4->f24->v15()->v8();
}
}
