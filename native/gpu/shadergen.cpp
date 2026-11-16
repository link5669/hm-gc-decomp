// GLSL generation for the current XF (vertex) and BP/TEV (pixel) state, cached by state key.
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <unordered_map>
#include <memory>
#include "glfuncs.h"
#include "gx_internal.h"

namespace gx {

static std::unordered_map<std::string, std::unique_ptr<Program>> s_progs;

static void put(std::string &k, u32 v) { k.append((const char *)&v, 4); }

void shader_key(std::string &k, const VtxComponents &comp, int pclass) {
  k.clear();
  put(k, comp.has_nrm | comp.has_col << 8 | comp.has_tc << 16 | (u32)pclass << 24);
  u32 ncol = xf[XF_NUMCOLORS] & 3;
  u32 ntg = xf[XF_NUMTEXGENS] & 15;
  put(k, ncol | ntg << 4 | (xf[XF_DUALTEX] & 1) << 8);
  for (int i = 0; i < 4; i++) put(k, xf[XF_CHAN0_COLOR + i]);
  for (u32 i = 0; i < ntg && i < 8; i++) {
    put(k, xf[XF_TEXMTXINFO + i]);
    if (xf[XF_DUALTEX] & 1) put(k, xf[XF_POSTMTXINFO + i] & 0x100);
  }
  // pixel side
  u32 gm = bp[0x00];
  put(k, gm & 0x7FFFF);
  u32 nst = bits(gm, 10, 4) + 1;
  u32 nind = bits(gm, 16, 3);
  for (u32 s = 0; s < nst; s++) {
    put(k, bp[0xC0 + 2 * s]);
    put(k, bp[0xC1 + 2 * s]);
    u32 ord = bp[0x28 + s / 2];
    put(k, (s & 1) ? (ord >> 12) & 0x3FF : ord & 0x3FF);
    u32 ks = bp[0xF6 + s / 2];
    put(k, (s & 1) ? (ks >> 14) & 0x3FF : (ks >> 4) & 0x3FF);
    if (nind) put(k, bp[0x10 + s] & 0x1FFFFF);
  }
  for (int i = 0; i < 8; i++) put(k, bp[0xF6 + i] & 15);
  if (nind) put(k, bp[0x27]);
  put(k, (bp[0xF3] >> 16) | (bp[0xF1] >> 20) << 8 | (bp[0x43] & 7) << 12 | ((bp[0x42] >> 8) & 1) << 16 | (u32)need_dual_source() << 17);
}

// ---------------------------------------------------------------------------------------------
static void app(std::string &s, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
static void app(std::string &s, const char *fmt, ...) {
  char buf[1024];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);
  s += buf;
}

static void gen_light(std::string &s, int light, u32 ctrl, bool alpha) {
  u32 diff = bits(ctrl, 7, 2), attn = bits(ctrl, 9, 2);
  const char *sw = alpha ? "a" : "rgb";
  const char *fl = alpha ? "float" : "vec3";
  const char *in = alpha ? "int" : "ivec3";
  int i = light;
  if (attn == 0 || attn == 2) {  // none / dir
    app(s, "  ldir = normalize(lpos[%d].xyz - pos.xyz);\n  attn = 1.0;\n", i);
    app(s, "  if (length(ldir) == 0.0) ldir = N;\n");
  } else if (attn == 1) {  // spec
    app(s, "  ldir = normalize(lpos[%d].xyz - pos.xyz);\n", i);
    app(s, "  attn = (dot(N, ldir) >= 0.0) ? max(0.0, dot(N, ldir_[%d].xyz)) : 0.0;\n", i);
    app(s, "  cosAttn = lcos[%d].xyz;\n  distAttn = %s(ldist[%d].xyz);\n", i, diff == 0 ? "" : "normalize", i);
    app(s, "  attn = max(0.0, dot(cosAttn, vec3(1.0, attn, attn*attn))) / dot(distAttn, vec3(1.0, attn, attn*attn));\n");
  } else {  // spot
    app(s, "  ldir = lpos[%d].xyz - pos.xyz;\n  dist2 = dot(ldir, ldir);\n  dist = sqrt(dist2);\n  ldir = ldir / dist;\n", i);
    app(s, "  attn = max(0.0, dot(ldir, ldir_[%d].xyz));\n", i);
    app(s, "  attn = max(0.0, lcos[%d].x + lcos[%d].y*attn + lcos[%d].z*attn*attn) / dot(ldist[%d].xyz, vec3(1.0, dist, dist2));\n", i, i, i, i);
  }
  if (diff == 0)
    app(s, "  lacc.%s += %s(round(attn * %s(lcol[%d].%s)));\n", sw, in, fl, i, sw);
  else
    app(s, "  lacc.%s += %s(round(attn * %sdot(ldir, N)) * %s(lcol[%d].%s)));\n", sw, in,
        diff == 2 ? "max(0.0," : "(", fl, i, sw);
}

static std::string gen_vs(const VtxComponents &comp, int pclass) {
  std::string s;
  s += "#version 330 core\n";
  s += "in vec3 a_pos; in vec3 a_nrm; in vec3 a_bin; in vec3 a_tan;\n"
       "in vec4 a_tc01; in vec4 a_tc23; in vec4 a_tc45; in vec4 a_tc67;\n"
       "in vec4 a_col0; in vec4 a_col1; in uvec4 a_mi0; in uvec4 a_mi1; in uvec4 a_mi2;\n"
       "uniform vec4 posmem[64]; uniform vec4 nrmmem[32]; uniform vec4 postmem[64];\n"
       "uniform vec4 lcol[8]; uniform vec4 lcos[8]; uniform vec4 ldist[8]; uniform vec4 lpos[8]; uniform vec4 ldir_[8];\n"
       "uniform vec4 matamb[4]; uniform mat4 proj; uniform vec4 vpscale; uniform vec4 vpoff; uniform float ptsize;\n"
       "out vec4 v_col0; out vec4 v_col1;\n";
  u32 ntg = xf[XF_NUMTEXGENS] & 15;
  if (ntg > 8) ntg = 8;
  for (u32 i = 0; i < ntg; i++) app(s, "out vec3 v_tex%u;\n", i);
  s += "vec3 mrow(uint r, vec4 p) { return vec3(dot(posmem[min(r,63u)], p), dot(posmem[min(r+1u,63u)], p), dot(posmem[min(r+2u,63u)], p)); }\n";
  s += "void main() {\n"
       "  uint mi[12] = uint[12](a_mi0.x, a_mi0.y, a_mi0.z, a_mi0.w, a_mi1.x, a_mi1.y, a_mi1.z, a_mi1.w, a_mi2.x, a_mi2.y, a_mi2.z, a_mi2.w);\n"
       "  vec2 tcin[8] = vec2[8](a_tc01.xy, a_tc01.zw, a_tc23.xy, a_tc23.zw, a_tc45.xy, a_tc45.zw, a_tc67.xy, a_tc67.zw);\n"
       "  vec4 rp = vec4(a_pos, 1.0);\n"
       "  uint pm = mi[0];\n"
       "  vec4 pos = vec4(mrow(pm, rp), 1.0);\n"
       "  uint nm = pm & 31u;\n"
       "  vec3 N = vec3(dot(nrmmem[nm].xyz, a_nrm), dot(nrmmem[(nm+1u)&31u].xyz, a_nrm), dot(nrmmem[(nm+2u)&31u].xyz, a_nrm));\n"
       "  if (dot(N, N) > 0.0) N = normalize(N);\n"
       "  vec3 T = vec3(dot(nrmmem[nm].xyz, a_tan), dot(nrmmem[(nm+1u)&31u].xyz, a_tan), dot(nrmmem[(nm+2u)&31u].xyz, a_tan));\n"
       "  vec3 B = vec3(dot(nrmmem[nm].xyz, a_bin), dot(nrmmem[(nm+1u)&31u].xyz, a_bin), dot(nrmmem[(nm+2u)&31u].xyz, a_bin));\n"
       "  vec4 clip = proj * pos;\n"
       "  gl_Position = vec4(clip.x * vpscale.x + clip.w * vpoff.x, clip.y * vpscale.y + clip.w * vpoff.y,\n"
       "                     clip.z * vpscale.z + clip.w * vpoff.z, clip.w);\n"
       "  gl_PointSize = ptsize;\n"
       // GX clips z to [-w, 0] in its own clip space and clamps the resulting depth (depth clamp is on)
       "  float cdz = clip.z * (1.0 - 1e-7);\n"
       "  gl_ClipDistance[0] = cdz + clip.w;\n"
       "  gl_ClipDistance[1] = -cdz;\n"
       "  ivec4 lacc; vec3 ldir, cosAttn, distAttn; float dist, dist2, attn;\n";
  // lighting
  u32 ncol = xf[XF_NUMCOLORS] & 3;
  for (u32 j = 0; j < 2; j++) {
    if (j >= ncol) {
      app(s, "  v_col%u = vec4(0.0);\n", j);
      continue;
    }
    u32 cc = xf[XF_CHAN0_COLOR + j], ac = xf[XF_CHAN0_ALPHA + j];
    bool hascol = (comp.has_col >> j) & 1;
    app(s, "  {\n  vec4 vc = %s;\n", hascol ? (j ? "a_col1" : "a_col0") : "vec4(1.0)");
    app(s, "  ivec4 mat = %s;\n", (cc & 1) ? "ivec4(round(vc * 255.0))" : (j ? "ivec4(matamb[3])" : "ivec4(matamb[2])"));
    if ((ac & 1) != (cc & 1))
      app(s, "  mat.w = %s;\n", (ac & 1) ? "int(round(vc.w * 255.0))" : (j ? "int(matamb[3].w)" : "int(matamb[2].w)"));
    if (cc & 2)
      app(s, "  lacc = %s;\n", (cc & 0x40) ? "ivec4(round(vc * 255.0))" : (j ? "ivec4(matamb[1])" : "ivec4(matamb[0])"));
    else
      s += "  lacc = ivec4(255);\n";
    if (ac & 2)
      app(s, "  lacc.w = %s;\n", (ac & 0x40) ? "int(round(vc.w * 255.0))" : (j ? "int(matamb[1].w)" : "int(matamb[0].w)"));
    else
      s += "  lacc.w = 255;\n";
    if (cc & 2) {
      u32 mask = bits(cc, 2, 4) | bits(cc, 11, 4) << 4;
      for (int l = 0; l < 8; l++)
        if (mask & (1 << l)) gen_light(s, l, cc, false);
    }
    if (ac & 2) {
      u32 mask = bits(ac, 2, 4) | bits(ac, 11, 4) << 4;
      for (int l = 0; l < 8; l++)
        if (mask & (1 << l)) gen_light(s, l, ac, true);
    }
    app(s, "  lacc = clamp(lacc, 0, 255);\n  v_col%u = vec4((mat * (lacc + (lacc >> 7))) >> 8) / 255.0;\n  }\n", j);
  }
  // texgen
  bool dual = xf[XF_DUALTEX] & 1;
  for (u32 i = 0; i < ntg; i++) {
    u32 ti = xf[XF_TEXMTXINFO + i];
    u32 proj = bits(ti, 1, 1), inform = bits(ti, 2, 1), type = bits(ti, 4, 3), src = bits(ti, 7, 5);
    app(s, "  {\n  vec4 c = vec4(0.0, 0.0, 1.0, 1.0);\n");
    switch (src) {
      case 0: s += "  c.xyz = a_pos;\n"; break;
      case 1: if (comp.has_nrm) s += "  c.xyz = a_nrm;\n"; break;
      case 2: s += "  c = v_col0;\n"; break;
      case 3: if (comp.has_nrm == 2) s += "  c.xyz = a_tan;\n"; break;
      case 4: if (comp.has_nrm == 2) s += "  c.xyz = a_bin;\n"; break;
      default:
        if (src >= 5 && src <= 12) app(s, "  c.xy = tcin[%u];\n", src - 5);
        break;
    }
    if (inform == 0) s += "  c.z = 1.0;\n";
    s += "  c.w = 1.0;\n";
    s += "  vec3 o;\n";
    if (type == 0) {
      app(s, "  uint tm = mi[%u];\n", i + 1);
      if (proj) s += "  o = mrow(tm, c);\n";
      else s += "  o = vec3(dot(posmem[min(tm,63u)], c), dot(posmem[min(tm+1u,63u)], c), 1.0);\n";
    } else if (type == 1) {  // emboss
      u32 ss = bits(ti, 12, 3), ls = bits(ti, 15, 3);
      if (ss < i) {
        app(s, "  vec3 ld = normalize(lpos[%u].xyz - pos.xyz);\n", ls);
        app(s, "  o = v_tex%u + vec3(dot(ld, T), dot(ld, B), 0.0);\n", ss);
      } else {
        s += "  o = vec3(0.0, 0.0, 1.0);\n";
      }
    } else if (type == 2) {
      s += "  o = vec3(v_col0.x, v_col0.y, 1.0);\n";
    } else {
      s += "  o = vec3(v_col1.x, v_col1.y, 1.0);\n";
    }
    if (dual && type == 0) {
      u32 pi = xf[XF_POSTMTXINFO + i];
      u32 row = bits(pi, 0, 6);
      if (pi & 0x100) s += "  o = normalize(o);\n";
      app(s, "  vec4 o4 = vec4(o, 1.0);\n  o = vec3(dot(postmem[%u], o4), dot(postmem[%u], o4), dot(postmem[%u], o4));\n",
          row, (row + 1) & 63, (row + 2) & 63);
    }
    app(s, "  v_tex%u = o;\n  }\n", i);
  }
  s += "}\n";
  (void)pclass;
  return s;
}

// ---------------------------------------------------------------------------------------------
static const char *cin[16] = {"prev.rgb", "prev.aaa", "c0.rgb", "c0.aaa", "c1.rgb", "c1.aaa", "c2.rgb",
                              "c2.aaa", "tex.rgb", "tex.aaa", "ras.rgb", "ras.aaa", "ivec3(255)",
                              "ivec3(128)", "konst.rgb", "ivec3(0)"};
static const char *ain[8] = {"prev.a", "c0.a", "c1.a", "c2.a", "tex.a", "ras.a", "konst.a", "0"};
static const char *outr[4] = {"prev", "c0", "c1", "c2"};

static const char *kc_tab(u32 k) {
  static const char *t[32] = {"ivec3(255)", "ivec3(223)", "ivec3(191)", "ivec3(159)", "ivec3(128)",
                              "ivec3(96)", "ivec3(64)", "ivec3(32)", "ivec3(0)", "ivec3(0)", "ivec3(0)",
                              "ivec3(0)", "kcolors[0].rgb", "kcolors[1].rgb", "kcolors[2].rgb",
                              "kcolors[3].rgb", "kcolors[0].rrr", "kcolors[1].rrr", "kcolors[2].rrr",
                              "kcolors[3].rrr", "kcolors[0].ggg", "kcolors[1].ggg", "kcolors[2].ggg",
                              "kcolors[3].ggg", "kcolors[0].bbb", "kcolors[1].bbb", "kcolors[2].bbb",
                              "kcolors[3].bbb", "kcolors[0].aaa", "kcolors[1].aaa", "kcolors[2].aaa",
                              "kcolors[3].aaa"};
  return t[k & 31];
}
static const char *ka_tab(u32 k) {
  static const char *t[32] = {"255", "223", "191", "159", "128", "96", "64", "32", "0", "0", "0", "0",
                              "0", "0", "0", "0", "kcolors[0].r", "kcolors[1].r", "kcolors[2].r",
                              "kcolors[3].r", "kcolors[0].g", "kcolors[1].g", "kcolors[2].g",
                              "kcolors[3].g", "kcolors[0].b", "kcolors[1].b", "kcolors[2].b",
                              "kcolors[3].b", "kcolors[0].a", "kcolors[1].a", "kcolors[2].a",
                              "kcolors[3].a"};
  return t[k & 31];
}

static void tev_regular(std::string &s, const char *comp, u32 v) {
  u32 bias = bits(v, 16, 2), op = bits(v, 18, 1), scale = bits(v, 20, 2);
  static const char *sl[4] = {"", " << 1", " << 2", ""};
  static const char *sr[4] = {"", "", "", " >> 1"};
  static const char *bt[4] = {"", " + 128", " - 128", ""};
  app(s, "(((d.%s%s)%s) %c (((((a.%s << 8) + (b.%s - a.%s) * (c.%s + (c.%s >> 7)))%s)%s) >> 8))%s",
      comp, bt[bias], sl[scale], op ? '-' : '+', comp, comp, comp, comp, comp, sl[scale],
      scale != 3 ? (op ? " + 127" : " + 128") : "", sr[scale]);
}

static std::string gen_fs() {
  std::string s;
  u32 gm = bp[0x00];
  u32 ntg = bits(gm, 0, 4), nst = bits(gm, 10, 4) + 1, nind = bits(gm, 16, 3);
  u32 ncol = xf[XF_NUMCOLORS] & 3;
  (void)ncol;
  if (ntg > 8) ntg = 8;
  u32 xntg = xf[XF_NUMTEXGENS] & 15;
  if (xntg > 8) xntg = 8;
  s += "#version 330 core\n";
  s += "in vec4 v_col0; in vec4 v_col1;\n";
  for (u32 i = 0; i < xntg; i++) app(s, "in vec3 v_tex%u;\n", i);
  s += "uniform sampler2D samp0, samp1, samp2, samp3, samp4, samp5, samp6, samp7;\n"
       "uniform ivec4 colors[4]; uniform ivec4 kcolors[4]; uniform ivec4 alpharef;\n"
       "uniform vec4 texdim[8]; uniform vec4 tcscale[8]; uniform ivec4 indmtx[6]; uniform ivec4 indscale[2];\n"
       "uniform ivec4 fogcol; uniform vec4 fogf; uniform ivec4 fogi; uniform float dstalpha;\n"
       "%OUTPUTS%"
       "ivec4 stex(sampler2D sm, int m, ivec2 uv) {\n"
       "  return ivec4(round(texture(sm, vec2(uv) / (texdim[m].xy * 128.0)) * 255.0));\n}\n"
       "int idot3(ivec3 x, ivec3 y) { ivec3 t = x * y; return t.x + t.y + t.z; }\n"
       "void main() {\n"
       "  ivec4 prev = colors[0], c0 = colors[1], c1 = colors[2], c2 = colors[3];\n"
       "  ivec4 tex = ivec4(0), ras = ivec4(0), konst = ivec4(0);\n"
       "  ivec4 a, b, c, d;\n"
       "  int alphabump = 0;\n"
       "  ivec3 tevcoord = ivec3(0);\n"
       "  ivec2 wrapped = ivec2(0);\n"
       "  const ivec3 comp16 = ivec3(1, 256, 0); const ivec3 comp24 = ivec3(1, 256, 65536);\n"
       "  ivec4 rc0 = ivec4(round(v_col0 * 255.0)), rc1 = ivec4(round(v_col1 * 255.0));\n";
  // fixed-point texcoords
  for (u32 i = 0; i < ntg; i++) {
    if (i < xntg)
      app(s, "  ivec2 uv%u = ivec2((v_tex%u.z == 0.0 ? v_tex%u.xy : v_tex%u.xy / v_tex%u.z) * tcscale[%u].xy * 128.0);\n",
          i, i, i, i, i, i);
    else
      app(s, "  ivec2 uv%u = ivec2(0);\n", i);
  }
  if (ntg == 0) s += "  ivec2 uv0 = ivec2(0);\n";
  // indirect stages
  u32 iref = bp[0x27];
  for (u32 i = 0; i < nind && i < 4; i++) {
    u32 tm = bits(iref, 6 * i, 3), tc = bits(iref, 6 * i + 3, 3);
    if (tc >= ntg) tc = 0;
    u32 sc = bp[0x25 + i / 2];
    u32 ss = bits(sc, (i & 1) * 8, 4), ts = bits(sc, (i & 1) * 8 + 4, 4);
    app(s, "  ivec2 tcI%u = ivec2(uv%u.x >> %u, uv%u.y >> %u);\n", i, tc, ss, tc, ts);
    app(s, "  ivec3 iind%u = stex(samp%u, %u, tcI%u).abg;\n", i, tm, tm, i);
  }
  static const char *rgba = "rgba";
  for (u32 st = 0; st < nst; st++) {
    u32 cc = bp[0xC0 + 2 * st], ac = bp[0xC1 + 2 * st];
    u32 ord = bp[0x28 + st / 2];
    if (st & 1) ord >>= 12;
    u32 texmap = bits(ord, 0, 3), texcoord = bits(ord, 3, 3), texen = bits(ord, 6, 1), chan = bits(ord, 7, 3);
    u32 ks = bp[0xF6 + st / 2];
    u32 kc = (st & 1) ? bits(ks, 14, 5) : bits(ks, 4, 5);
    u32 ka = (st & 1) ? bits(ks, 19, 5) : bits(ks, 9, 5);
    u32 rswap = bits(ac, 0, 2), tswap = bits(ac, 2, 2);
    u32 rs0 = bp[0xF6 + rswap * 2], rs1 = bp[0xF7 + rswap * 2];
    u32 ts0 = bp[0xF6 + tswap * 2], ts1 = bp[0xF7 + tswap * 2];
    app(s, "  // stage %u\n", st);
    bool has_tc = texcoord < ntg;
    // indirect
    u32 ti = nind ? bp[0x10 + st] : 0;
    u32 ibt = bits(ti, 0, 2), ifmt = bits(ti, 2, 2), ibias = bits(ti, 4, 3), ibs = bits(ti, 7, 2);
    u32 imtx = bits(ti, 9, 2), imid = bits(ti, 11, 2), isw = bits(ti, 13, 3), itw = bits(ti, 16, 3);
    u32 iaddprev = bits(ti, 20, 1);
    bool has_ind = nind && ibt < nind;
    if (has_tc || has_ind) {
      if (has_ind && ibs) {
        static const char asel[4] = {'x', 'x', 'y', 'z'};
        static const int ashift[4] = {0, 5, 4, 3};
        app(s, "  alphabump = (iind%u.%c << %d) & 248;\n", ibt, asel[ibs], ashift[ifmt]);
      }
      if (has_ind && imtx) {
        static const int fshift[4] = {0, 3, 4, 5};
        app(s, "  {\n  ivec3 crd = iind%u >> %d;\n", ibt, fshift[ifmt]);
        int add = ifmt == 0 ? -128 : 1;
        if (ibias & 1) app(s, "  crd.x += %d;\n", add);
        if (ibias & 2) app(s, "  crd.y += %d;\n", add);
        if (ibias & 4) app(s, "  crd.z += %d;\n", add);
        u32 m = 2 * (imtx - 1);
        if (imtx <= 3) {
          if (imid == 0)
            app(s, "  ivec2 itr = ivec2(idot3(indmtx[%u].xyz, crd), idot3(indmtx[%u].xyz, crd)) >> 3;\n", m, m + 1);
          else if (imid == 1 && has_tc)
            app(s, "  ivec2 itr = ivec2(uv%u * crd.xx) >> 8;\n", texcoord);
          else if (imid == 2 && has_tc)
            app(s, "  ivec2 itr = ivec2(uv%u * crd.yy) >> 8;\n", texcoord);
          else
            s += "  ivec2 itr = ivec2(0);\n";
          app(s, "  if (indmtx[%u].w >= 0) itr >>= indmtx[%u].w; else itr <<= -indmtx[%u].w;\n", m, m, m);
        } else {
          s += "  ivec2 itr = ivec2(0);\n";
        }
        s += "  indtrans = itr;\n  }\n";
      } else {
        s += "  indtrans = ivec2(0);\n";
      }
      static const char *wrapv[5] = {"(256<<7)", "(128<<7)", "(64<<7)", "(32<<7)", "(16<<7)"};
      std::string uv = has_tc ? ("uv" + std::to_string(texcoord)) : "ivec2(0)";
      if (isw == 0) app(s, "  wrapped.x = %s.x;\n", uv.c_str());
      else if (isw >= 6) s += "  wrapped.x = 0;\n";
      else app(s, "  wrapped.x = %s.x & (%s - 1);\n", uv.c_str(), wrapv[isw - 1]);
      if (itw == 0) app(s, "  wrapped.y = %s.y;\n", uv.c_str());
      else if (itw >= 6) s += "  wrapped.y = 0;\n";
      else app(s, "  wrapped.y = %s.y & (%s - 1);\n", uv.c_str(), wrapv[itw - 1]);
      if (has_ind && iaddprev) s += "  tevcoord.xy += wrapped + indtrans;\n";
      else s += "  tevcoord.xy = wrapped + indtrans;\n";
      s += "  tevcoord.xy = (tevcoord.xy << 8) >> 8;\n";
    }
    // ras
    static const char *rastab[8] = {"rc0", "rc1", "ivec4(0)", "ivec4(0)", "ivec4(0)", "ivec4(alphabump)",
                                    "ivec4(alphabump | (alphabump >> 5))", "ivec4(0)"};
    app(s, "  ras = %s.%c%c%c%c;\n", rastab[chan & 7], rgba[bits(rs0, 0, 2)], rgba[bits(rs0, 2, 2)],
        rgba[bits(rs1, 0, 2)], rgba[bits(rs1, 2, 2)]);
    if (texen) {
      app(s, "  tex = stex(samp%u, %u, tevcoord.xy).%c%c%c%c;\n", texmap, texmap, rgba[bits(ts0, 0, 2)],
          rgba[bits(ts0, 2, 2)], rgba[bits(ts1, 0, 2)], rgba[bits(ts1, 2, 2)]);
    } else {
      s += "  tex = ivec4(255);\n";
    }
    app(s, "  konst = ivec4(%s, %s);\n", kc_tab(kc), ka_tab(ka));
    app(s, "  a = ivec4(%s, %s) & 255;\n", cin[bits(cc, 12, 4)], ain[bits(ac, 13, 3)]);
    app(s, "  b = ivec4(%s, %s) & 255;\n", cin[bits(cc, 8, 4)], ain[bits(ac, 10, 3)]);
    app(s, "  c = ivec4(%s, %s) & 255;\n", cin[bits(cc, 4, 4)], ain[bits(ac, 7, 3)]);
    app(s, "  d = ivec4(%s, %s);\n", cin[bits(cc, 0, 4)], ain[bits(ac, 4, 3)]);
    // color
    app(s, "  %s.rgb = clamp(", outr[bits(cc, 22, 2)]);
    if (bits(cc, 16, 2) != 3) {
      tev_regular(s, "rgb", cc);
    } else {
      u32 eq = bits(cc, 18, 1), mode = bits(cc, 20, 2);
      static const char *gt[4] = {"((a.r > b.r) ? c.rgb : ivec3(0))",
                                  "((idot3(a.rgb, comp16) > idot3(b.rgb, comp16)) ? c.rgb : ivec3(0))",
                                  "((idot3(a.rgb, comp24) > idot3(b.rgb, comp24)) ? c.rgb : ivec3(0))",
                                  "(max(sign(a.rgb - b.rgb), ivec3(0)) * c.rgb)"};
      static const char *eqs[4] = {"((a.r == b.r) ? c.rgb : ivec3(0))",
                                   "((idot3(a.rgb, comp16) == idot3(b.rgb, comp16)) ? c.rgb : ivec3(0))",
                                   "((idot3(a.rgb, comp24) == idot3(b.rgb, comp24)) ? c.rgb : ivec3(0))",
                                   "((ivec3(1) - sign(abs(a.rgb - b.rgb))) * c.rgb)"};
      app(s, "d.rgb + %s", eq ? eqs[mode] : gt[mode]);
    }
    s += bits(cc, 19, 1) ? ", ivec3(0), ivec3(255));\n" : ", ivec3(-1024), ivec3(1023));\n";
    // alpha
    app(s, "  %s.a = clamp(", outr[bits(ac, 22, 2)]);
    if (bits(ac, 16, 2) != 3) {
      tev_regular(s, "a", ac);
    } else {
      u32 eq = bits(ac, 18, 1), mode = bits(ac, 20, 2);
      static const char *gt[4] = {"((a.r > b.r) ? c.a : 0)",
                                  "((idot3(a.rgb, comp16) > idot3(b.rgb, comp16)) ? c.a : 0)",
                                  "((idot3(a.rgb, comp24) > idot3(b.rgb, comp24)) ? c.a : 0)",
                                  "((a.a > b.a) ? c.a : 0)"};
      static const char *eqs[4] = {"((a.r == b.r) ? c.a : 0)",
                                   "((idot3(a.rgb, comp16) == idot3(b.rgb, comp16)) ? c.a : 0)",
                                   "((idot3(a.rgb, comp24) == idot3(b.rgb, comp24)) ? c.a : 0)",
                                   "((a.a == b.a) ? c.a : 0)"};
      app(s, "d.a + %s", eq ? eqs[mode] : gt[mode]);
    }
    s += bits(ac, 19, 1) ? ", 0, 255);\n" : ", -1024, 1023);\n";
  }
  {
    u32 cc = bp[0xC0 + 2 * (nst - 1)], ac = bp[0xC1 + 2 * (nst - 1)];
    if (bits(cc, 22, 2)) app(s, "  prev.rgb = %s.rgb;\n", outr[bits(cc, 22, 2)]);
    if (bits(ac, 22, 2)) app(s, "  prev.a = %s.a;\n", outr[bits(ac, 22, 2)]);
  }
  s += "  prev = prev & 255;\n";
  // alpha test
  {
    u32 at = bp[0xF3];
    u32 f0 = bits(at, 16, 3), f1 = bits(at, 19, 3), lg = bits(at, 22, 2);
    static const char *fn[8] = {"false", "(prev.a < alpharef.x)", "(prev.a == alpharef.x)", "(prev.a <= alpharef.x)",
                                "(prev.a > alpharef.x)", "(prev.a != alpharef.x)", "(prev.a >= alpharef.x)", "true"};
    static const char *lo[4] = {"&&", "||", "!=", "=="};
    std::string e0 = fn[f0], e1 = fn[f1];
    size_t p;
    while ((p = e1.find("alpharef.x")) != std::string::npos) e1.replace(p, 10, "alpharef.y");
    bool always = (lg == 0 && f0 == 7 && f1 == 7) || (lg == 1 && (f0 == 7 || f1 == 7));
    if (!always) app(s, "  if (!(%s %s %s)) discard;\n", e0.c_str(), lo[lg], e1.c_str());
  }
  // fog
  {
    u32 f3 = bp[0xF1];
    u32 fsel = bits(f3, 21, 3), proj = bits(f3, 20, 1);
    if (fsel >= 2) {
      s += "  int zc = int(clamp(gl_FragCoord.z, 0.0, 1.0) * 16777215.0);\n";
      if (proj == 0)
        s += "  float ze = (fogf.x * 16777216.0) / float(fogi.y - (zc >> fogi.w));\n";
      else
        s += "  float ze = fogf.x * float(zc) / 16777216.0;\n";
      s += "  float fog = clamp(ze - fogf.y, 0.0, 1.0);\n";
      if (fsel == 4) s += "  fog = 1.0 - exp2(-8.0 * fog);\n";
      if (fsel == 5) s += "  fog = 1.0 - exp2(-8.0 * fog * fog);\n";
      if (fsel == 6) s += "  fog = exp2(-8.0 * (1.0 - fog));\n";
      if (fsel == 7) s += "  fog = 1.0 - fog; fog = exp2(-8.0 * fog * fog);\n";
      s += "  int ifog = int(round(fog * 256.0));\n"
           "  prev.rgb = (prev.rgb * (256 - ifog) + fogcol.rgb * ifog) >> 8;\n";
    }
  }
  u32 pf = bp[0x43] & 7;
  if (pf == 1) s += "  prev = (prev >> 2); prev = (prev << 2) | (prev >> 4);\n";
  if (pf == 2) s += "  prev.rb = (prev.rb >> 3); prev.rb = (prev.rb << 3) | (prev.rb >> 2);\n"
                    "  prev.g = (prev.g >> 2); prev.g = (prev.g << 2) | (prev.g >> 4);\n";
  s += "  ocol0 = vec4(prev) / 255.0;\n";
  bool dual = need_dual_source();
  if (dual) s += "  ocol1 = vec4(0.0, 0.0, 0.0, float(prev.a) / 255.0);\n";
  {
    size_t op = s.find("%OUTPUTS%");
    s.replace(op, 9, dual ? "layout(location = 0, index = 0) out vec4 ocol0;\n"
                            "layout(location = 0, index = 1) out vec4 ocol1;\n"
                          : "layout(location = 0) out vec4 ocol0;\n");
  }
  if ((bp[0x42] >> 8) & 1) s += "  ocol0.a = dstalpha;\n";
  s += "}\n";
  // indtrans declaration
  size_t mpos = s.find("  ivec2 wrapped = ivec2(0);\n");
  s.insert(mpos, "  ivec2 indtrans = ivec2(0);\n");
  return s;
}

static unsigned compile(unsigned type, const std::string &src) {
  unsigned sh = glCreateShader(type);
  const char *p = src.c_str();
  glShaderSource(sh, 1, &p, nullptr);
  glCompileShader(sh);
  int ok = 0;
  glGetShaderiv(sh, GL_COMPILE_STATUS, &ok);
  if (!ok) {
    char log[4096];
    glGetShaderInfoLog(sh, sizeof(log), nullptr, log);
    logf("shader compile failed:\n%s\n--- source ---\n%s", log, src.c_str());
  }
  return sh;
}

static const char *s_attr_names[13] = {"a_pos", "a_nrm", "a_bin", "a_tan", "a_tc01", "a_tc23", "a_tc45",
                                       "a_tc67", "a_col0", "a_col1", "a_mi0", "a_mi1", "a_mi2"};

unsigned compile_program(const char *vs, const char *fs, bool dual_source) {
  unsigned v = compile(GL_VERTEX_SHADER, vs), f = compile(GL_FRAGMENT_SHADER, fs);
  unsigned p = glCreateProgram();
  glAttachShader(p, v);
  glAttachShader(p, f);
  for (int i = 0; i < 13; i++) glBindAttribLocation(p, i, s_attr_names[i]);
  (void)dual_source;
  glLinkProgram(p);
  int ok = 0;
  glGetProgramiv(p, GL_LINK_STATUS, &ok);
  if (!ok) {
    char log[4096];
    glGetProgramInfoLog(p, sizeof(log), nullptr, log);
    logf("program link failed: %s", log);
  }
  glDeleteShader(v);
  glDeleteShader(f);
  return p;
}

Program *shader_get(const std::string &key) {
  auto it = s_progs.find(key);
  if (it != s_progs.end()) return it->second.get();
  // regenerate component info from the key header
  u32 h;
  memcpy(&h, key.data(), 4);
  VtxComponents comp;
  comp.has_nrm = h & 0xFF;
  comp.has_col = (h >> 8) & 0xFF;
  comp.has_tc = (h >> 16) & 0xFF;
  int pclass = h >> 24;
  g_prof.compiles++;
  std::string vs = gen_vs(comp, pclass), fs = gen_fs();
  if (getenv("HM_GPU_DUMPSHADERS")) fprintf(stderr, "=== VS ===\n%s\n=== FS ===\n%s\n", vs.c_str(), fs.c_str());
  auto pr = std::make_unique<Program>();
  pr->prog = compile_program(vs.c_str(), fs.c_str(), true);
  unsigned p = pr->prog;
  glUseProgram(p);
  for (int i = 0; i < 8; i++) {
    char n[16];
    snprintf(n, sizeof(n), "samp%d", i);
    glUniform1i(glGetUniformLocation(p, n), i);
  }
#define LOC(x) pr->u_##x = glGetUniformLocation(p, #x)
  LOC(posmem); LOC(nrmmem); LOC(postmem); LOC(lcol); LOC(lcos); LOC(ldist); LOC(lpos);
  pr->u_ldir = glGetUniformLocation(p, "ldir_");
  LOC(matamb); LOC(proj); LOC(vpscale); LOC(vpoff); LOC(ptsize);
  LOC(colors); LOC(kcolors); LOC(alpharef); LOC(texdim); LOC(tcscale); LOC(indmtx); LOC(indscale);
  LOC(fogcol); LOC(fogf); LOC(fogi); LOC(dstalpha);
#undef LOC
  Program *ret = pr.get();
  s_progs[key] = std::move(pr);
  return ret;
}

void shader_shutdown() { s_progs.clear(); }

}  // namespace gx
