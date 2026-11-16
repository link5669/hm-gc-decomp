// OpenGL backend: EFB, primitive batching, draw state, EFB copies, XFB present, peek/poke.
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "glfuncs.h"
#include "gx_internal.h"

namespace gx {

int g_scale = 1;
u32 g_epoch = 1;

static const int EFB_W = 640, EFB_H = 528;
static int W, H;  // EFB size in host pixels
static unsigned s_efb_fbo, s_efb_color, s_efb_depth;
static unsigned s_vao, s_vbo, s_ebo;
static unsigned s_samplers[8];
static unsigned s_copy_fbo;
static unsigned s_copy_prog, s_present_prog, s_empty_vao;
static unsigned s_xfb_tex;
// ---- widescreen ----
// Physical EFB width W = 640*scale*aspect/(4/3); logical EFB x maps linearly to physical x.
static float s_aspect = 4.0f / 3.0f, s_pending_aspect = 4.0f / 3.0f, s_xfb_aspect = 4.0f / 3.0f;
static float s_aniso = 1;
static bool wide() { return W != EFB_W * g_scale; }
static int PX(int x) { return wide() ? (int)((long long)x * W / EFB_W) : x * g_scale; }
static float XS() { return (float)W / EFB_W; }  // host pixels per logical x
// Ortho draws whose x extent covers at least this fraction of their viewport are stretched (k = 1)
// instead of kept at their 4:3 shape (k = 1/s). Override with HM_WIDE_FULL.
static float s_full_thresh = 0.95f;
static float b_k = 1.0f;
static int s_xfb_w, s_xfb_h;  // host pixels
static bool s_have_xfb = false;

static unsigned s_cur_prog = 0;
static int s_draw_idx = 0;
static BoundTex s_last_samp[8];
// streaming vertex/index ring buffers (written unsynchronized, orphaned on wrap)
static const size_t VB_SIZE = 16u << 20, IB_SIZE = 4u << 20;
static size_t s_vb_off = VB_SIZE, s_ib_off = IB_SIZE;

// ---------------- batch ----------------
static std::vector<Vertex> b_verts;
static std::vector<u32> b_idx;
static int b_pclass = 0;
static VtxComponents b_comp;
static BoundTex b_tex[8];
static std::string s_key;

// ---------------- helpers ----------------
static unsigned make_tex(int w, int h, int ifmt, int fmt, int type) {
  unsigned t;
  glGenTextures(1, &t);
  glBindTexture(GL_TEXTURE_2D, t);
  glTexImage2D(GL_TEXTURE_2D, 0, ifmt, w, h, 0, fmt, type, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
  return t;
}

static const char *s_fullscreen_vs =
    "#version 330 core\n"
    "out vec2 v_uv;\n"
    "void main() { vec2 p = vec2((gl_VertexID & 1) * 4.0 - 1.0, (gl_VertexID & 2) * 2.0 - 1.0);\n"
    "  v_uv = p * 0.5 + 0.5; gl_Position = vec4(p, 0.0, 1.0); }\n";

// EFB -> texture/XFB conversion. Output pixel (x,y) of the destination (row 0 = top).
static const char *s_copy_fs =
    "#version 330 core\n"
    "uniform sampler2D efb; uniform sampler2D efbz;\n"
    "uniform ivec4 src;      // x, y, w, h of the source rect in host pixels\n"
    "uniform ivec4 params;   // scale(host px per EFB px), half, fmt, flags(1=intensity,2=depth,4=xfb)\n"
    "uniform vec4 filt;      // vertical filter weights (top, mid, bottom), gamma\n"
    "uniform float yscale;   // XFB vertical scale (dest rows per src row)\n"
    "uniform vec4 stepf;     // source host pixels per destination pixel (x, y), box filter offset (x, y)\n"
    "out vec4 o;\n"
    "vec4 fetch(ivec2 p) {\n"
    "  p = clamp(p, src.xy, src.xy + src.zw - 1);\n"
    "  if ((params.w & 2) != 0) {\n"
    "    uint d = uint(texelFetch(efbz, p, 0).r * 16777215.0 + 0.5);\n"
    "    return vec4(float(d >> 16), float((d >> 8) & 255u), float(d & 255u), float(d >> 16)) / 255.0;\n"
    "  }\n"
    "  return texelFetch(efb, p, 0);\n"
    "}\n"
    "vec4 samp(ivec2 p, int s) {\n"
    "  vec4 t = fetch(p - ivec2(0, s)) * filt.x + fetch(p) * filt.y + fetch(p + ivec2(0, s)) * filt.z;\n"
    "  return ((params.w & 2) != 0) ? fetch(p) : min(t, vec4(1.0));\n"
    "}\n"
    "void main() {\n"
    "  int s = params.x;\n"
    "  ivec2 d = ivec2(gl_FragCoord.xy);\n"
    "  vec4 c;\n"
    "  if ((params.w & 4) != 0) d.y = int(float(d.y) / yscale);\n"
    "  ivec2 p = src.xy + ivec2(vec2(d) * stepf.xy);\n"
    "  if (params.y != 0) {\n"
    "    ivec2 bo = ivec2(stepf.zw);\n"
    "    c = (samp(p, s) + samp(p + ivec2(bo.x, 0), s) + samp(p + ivec2(0, bo.y), s) + samp(p + bo, s)) * 0.25;\n"
    "  } else {\n"
    "    c = samp(p, s);\n"
    "  }\n"
    "  if ((params.w & 4) != 0) { o = vec4(pow(c.rgb, vec3(1.0 / filt.w)), 1.0); return; }\n"
    "  ivec4 v = ivec4(round(c * 255.0));\n"
    "  int fmt = params.z;\n"
    "  if ((params.w & 1) != 0 && fmt < 4 || (params.w & 1) != 0 && fmt == 8) {\n"
    "    int y = ((66 * v.r + 129 * v.g + 25 * v.b + 128) >> 8) + 16;\n"
    "    v.r = clamp(y, 0, 255);\n"
    "  }\n"
    "  ivec4 r;\n"
    "  if (fmt == 0) { int i = (v.r >> 4) * 17; r = ivec4(i); }\n"
    "  else if (fmt == 1 || fmt == 8) r = ivec4(v.r);\n"
    "  else if (fmt == 2) { int i = (v.r >> 4) * 17; r = ivec4(i, i, i, (v.a >> 4) * 17); }\n"
    "  else if (fmt == 3) r = ivec4(v.r, v.r, v.r, v.a);\n"
    "  else if (fmt == 4) { ivec3 q = v.rgb >> ivec3(3, 2, 3); r = ivec4((q.r << 3) | (q.r >> 2), (q.g << 2) | (q.g >> 4), (q.b << 3) | (q.b >> 2), 255); }\n"
    "  else if (fmt == 5) {\n"
    "    if (v.a >= 224) { ivec3 q = v.rgb >> 3; r = ivec4((q << 3) | (q >> 2), 255); }\n"
    "    else { ivec3 q = v.rgb >> 4; int a = v.a >> 5; r = ivec4(q * 17, (a << 5) | (a << 2) | (a >> 1)); }\n"
    "  }\n"
    "  else if (fmt == 6) r = v;\n"
    "  else if (fmt == 7) r = ivec4(v.a);\n"
    "  else if (fmt == 9) r = ivec4(v.g);\n"
    "  else if (fmt == 10) r = ivec4(v.b);\n"
    "  else if (fmt == 11) r = ivec4(v.g, v.g, v.g, v.r);\n"
    "  else if (fmt == 12) r = ivec4(v.b, v.b, v.b, v.g);\n"
    "  else r = v;\n"
    "  o = vec4(r) / 255.0;\n"
    "}\n";

static const char *s_present_fs =
    "#version 330 core\n"
    "in vec2 v_uv; uniform sampler2D tex; out vec4 o;\n"
    "void main() { o = vec4(texture(tex, vec2(v_uv.x, 1.0 - v_uv.y)).rgb, 1.0); }\n";

// Guest-RAM XFB (YUYV 4:2:2, bytes Y0 U Y1 V uploaded as RGBA8 texels, 2 pixels per texel).
static const char *s_yuyv_fs =
    "#version 330 core\n"
    "in vec2 v_uv; uniform sampler2D tex; uniform ivec2 size; out vec4 o;\n"
    "void main() {\n"
    "  ivec2 p = ivec2(int(v_uv.x * float(size.x)), int((1.0 - v_uv.y) * float(size.y)));\n"
    "  p = clamp(p, ivec2(0), size - 1);\n"
    "  vec4 t = texelFetch(tex, ivec2(p.x >> 1, p.y), 0) * 255.0;\n"
    "  float y = ((p.x & 1) != 0 ? t.b : t.r) - 16.0, u = t.g - 128.0, v = t.a - 128.0;\n"
    "  vec3 c = vec3(1.164 * y + 1.596 * v, 1.164 * y - 0.392 * u - 0.813 * v, 1.164 * y + 2.017 * u);\n"
    "  o = vec4(clamp(c / 255.0, 0.0, 1.0), 1.0);\n"
    "}\n";
static unsigned s_yuyv_prog, s_yuyv_tex;
static int s_yuyv_w, s_yuyv_h;

static unsigned build_simple(const char *vs, const char *fs) {
  extern unsigned compile_program(const char *, const char *, bool);
  return compile_program(vs, fs, false);
}

static int phys_width(float a) {
  float s = a / (4.0f / 3.0f);
  if (std::fabs(s - 1.0f) < 1e-4f) return EFB_W * g_scale;
  return std::max(EFB_W * g_scale / 2, (int)std::lround(EFB_W * g_scale * s));
}

void set_aspect(float a) {
  if (!(a > 0.5f && a < 8.0f)) a = 4.0f / 3.0f;
  s_pending_aspect = a;
  if (!W) s_aspect = a;  // before init: applied at allocation
}

// Reallocates the EFB for a new display aspect (frame boundary only). Contents are cleared.
static int s_pending_scale = 0;
float g_frame_gpu_ms = 0;
void request_scale(int s) { s_pending_scale = std::max(1, std::min(s, 8)); }
// One GL_TIME_ELAPSED query per frame (XFB copy to XFB copy), read when available (no stall).
static void frame_timer_tick() {
  if (g_prof_on) return;  // the profiler uses TIME_ELAPSED queries itself
  static unsigned qs[4]; static bool used[4]; static int cur = -1, n = 0;
  if (!n) { glGenQueries(4, qs); n = 4; }
  if (cur >= 0) glEndQuery(GL_TIME_ELAPSED);
  for (int i = 0; i < 4; i++) {
    if (!used[i] || i == cur) continue;
    int avail = 0; glGetQueryObjectiv(qs[i], GL_QUERY_RESULT_AVAILABLE, &avail);
    if (avail) {
      GLuint64 ns = 0; glGetQueryObjectui64v(qs[i], GL_QUERY_RESULT, &ns);
      float ms = (float)(ns * 1e-6);
      g_frame_gpu_ms = g_frame_gpu_ms == 0 ? ms : g_frame_gpu_ms * 0.9f + ms * 0.1f;
      used[i] = false;
    }
  }
  int next = -1;
  for (int i = 0; i < 4; i++) if (!used[i] && i != cur) { next = i; break; }
  cur = next;
  if (cur >= 0) { used[cur] = true; glBeginQuery(GL_TIME_ELAPSED, qs[cur]); }
}
static void resize_efb(float a) {
  flush_batch();
  s_aspect = a;
  bool scale_change = s_pending_scale && s_pending_scale != g_scale;
  if (scale_change) { g_scale = s_pending_scale; H = EFB_H * g_scale; g_frame_gpu_ms = 0; }
  s_pending_scale = 0;
  int nw = phys_width(a);
  if (nw == W && !scale_change) return;
  W = nw;
  glDeleteTextures(1, &s_efb_color);
  glDeleteTextures(1, &s_efb_depth);
  s_efb_color = make_tex(W, H, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
  s_efb_depth = make_tex(W, H, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT);
  glBindFramebuffer(GL_FRAMEBUFFER, s_efb_fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, s_efb_color, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, s_efb_depth, 0);
  glDisable(GL_SCISSOR_TEST);
  glColorMask(1, 1, 1, 1);
  glDepthMask(1);
  u32 ar = bp[0x4F], gb = bp[0x50];
  glClearColor(bits(ar, 0, 8) / 255.0f, bits(gb, 8, 8) / 255.0f, bits(gb, 0, 8) / 255.0f, 1.0f);
  glClearDepth((bp[0x51] & 0xFFFFFF) / 16777215.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool render_init(int scale) {
  g_scale = std::max(1, std::min(scale, 8));
  if (const char *e = getenv("HM_WIDE_FULL")) s_full_thresh = (float)atof(e);
  W = phys_width(s_aspect);
  s_pending_aspect = s_aspect;
  H = EFB_H * g_scale;
  s_efb_color = make_tex(W, H, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
  s_efb_depth = make_tex(W, H, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT);
  glGenFramebuffers(1, &s_efb_fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, s_efb_fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, s_efb_color, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, s_efb_depth, 0);
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    logf("EFB framebuffer incomplete");
    return false;
  }
  glDisable(GL_SCISSOR_TEST);
  glColorMask(1, 1, 1, 1);
  glDepthMask(1);
  glClearColor(0, 0, 0, 1);
  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glGenFramebuffers(1, &s_copy_fbo);

  glGenVertexArrays(1, &s_vao);
  glBindVertexArray(s_vao);
  glGenBuffers(1, &s_vbo);
  glGenBuffers(1, &s_ebo);
  glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ebo);
  const int st = sizeof(Vertex);
#define OFF(f) (const void *)offsetof(Vertex, f)
  for (int i = 0; i < 13; i++) glEnableVertexAttribArray(i);
  glVertexAttribPointer(0, 3, GL_FLOAT, 0, st, OFF(pos));
  glVertexAttribPointer(1, 3, GL_FLOAT, 0, st, OFF(nrm));
  glVertexAttribPointer(2, 3, GL_FLOAT, 0, st, OFF(bin));
  glVertexAttribPointer(3, 3, GL_FLOAT, 0, st, OFF(tan));
  for (int i = 0; i < 4; i++) glVertexAttribPointer(4 + i, 4, GL_FLOAT, 0, st, (const void *)(offsetof(Vertex, tc) + 16 * i));
  glVertexAttribPointer(8, 4, GL_UNSIGNED_BYTE, 1, st, OFF(col[0]));
  glVertexAttribPointer(9, 4, GL_UNSIGNED_BYTE, 1, st, OFF(col[1]));
  for (int i = 0; i < 3; i++) glVertexAttribIPointer(10 + i, 4, GL_UNSIGNED_BYTE, st, (const void *)(offsetof(Vertex, midx) + 4 * i));
#undef OFF
  glGenVertexArrays(1, &s_empty_vao);
  glGenSamplers(8, s_samplers);
  {  // anisotropic filtering (GL 4.6 core / EXT_texture_filter_anisotropic): sharper textures at grazing angles
    float mx = 0;
    while (glGetError()) {}
    glGetFloatv(0x84FF /*MAX_TEXTURE_MAX_ANISOTROPY*/, &mx);
    if (glGetError() || mx < 1) mx = 1;
    const char *e = getenv("HM_ANISO");
    s_aniso = e ? std::max(1.0f, std::min(mx, (float)atof(e))) : std::min(mx, 16.0f);
  }
  s_copy_prog = build_simple(s_fullscreen_vs, s_copy_fs);
  s_present_prog = build_simple(s_fullscreen_vs, s_present_fs);
  s_yuyv_prog = build_simple(s_fullscreen_vs, s_yuyv_fs);
  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_DEPTH_CLAMP);  // GX clamps depth to the 24-bit range instead of clipping at the depth range
  glEnable(GL_CLIP_DISTANCE0);
  glEnable(GL_CLIP_DISTANCE1);
  return true;
}

void render_shutdown() {
  b_verts.clear();
  b_idx.clear();
}

// ---------------- primitives ----------------
static u32 s_texmask_cache;

static u32 used_texmaps() {
  u32 gm = bp[0x00];
  u32 nst = bits(gm, 10, 4) + 1, nind = bits(gm, 16, 3);
  u32 m = 0;
  for (u32 s = 0; s < nst; s++) {
    u32 ord = bp[0x28 + s / 2];
    if (s & 1) ord >>= 12;
    if (bits(ord, 6, 1)) m |= 1u << bits(ord, 0, 3);
  }
  for (u32 i = 0; i < nind && i < 4; i++) m |= 1u << bits(bp[0x27], 6 * i, 3);
  return m;
}

// Clip-space x factor for a primitive in widescreen (see s_full_thresh).
static float prim_k(const Vertex *v, u32 count) {
  if (!wide()) return 1.0f;
  float inv = (float)(EFB_W * g_scale) / W;
  if (xf[XF_PROJ + 6] == 0) return inv;  // perspective: wider FOV
  float p0 = u2f(xf[XF_PROJ]), p1 = u2f(xf[XF_PROJ + 1]);
  float mn = 1e30f, mx = -1e30f;
  for (u32 i = 0; i < count; i++) {
    u32 r = std::min<u32>(v[i].midx[0], 61) * 4;
    float ex = u2f(xf[r]) * v[i].pos[0] + u2f(xf[r + 1]) * v[i].pos[1] + u2f(xf[r + 2]) * v[i].pos[2] + u2f(xf[r + 3]);
    float cx = p0 * ex + p1;
    mn = std::min(mn, cx);
    mx = std::max(mx, cx);
  }
  return (mx - mn) * 0.5f >= s_full_thresh ? 1.0f : inv;
}

void add_primitive(int prim, const Vertex *v, u32 count, const VtxComponents &comp) {
  int pclass = prim <= 4 ? PC_TRI : prim <= 6 ? PC_LINE : PC_POINT;
  float k = prim_k(v, count);
  if (!b_verts.empty() &&
      (pclass != b_pclass || k != b_k || memcmp(&comp, &b_comp, sizeof(comp)) != 0 || b_verts.size() + count > 65000))
    flush_batch();
  if (b_verts.empty()) {
    b_pclass = pclass;
    b_k = k;
    b_comp = comp;
    s_texmask_cache = used_texmaps();
    for (int n = 0; n < 8; n++) b_tex[n] = (s_texmask_cache >> n) & 1 ? texcache_get(n) : BoundTex();
  }
  u32 base = (u32)b_verts.size();
  b_verts.insert(b_verts.end(), v, v + count);
  switch (prim) {
    case 0: case 1:  // quads
      for (u32 i = 0; i + 3 < count; i += 4) {
        u32 a = base + i;
        b_idx.insert(b_idx.end(), {a, a + 1, a + 2, a, a + 2, a + 3});
      }
      break;
    case 2:
      for (u32 i = 0; i + 2 < count; i += 3) b_idx.insert(b_idx.end(), {base + i, base + i + 1, base + i + 2});
      break;
    case 3:
      for (u32 i = 2; i < count; i++) {
        if (i & 1) b_idx.insert(b_idx.end(), {base + i - 1, base + i - 2, base + i});
        else b_idx.insert(b_idx.end(), {base + i - 2, base + i - 1, base + i});
      }
      break;
    case 4:
      for (u32 i = 2; i < count; i++) b_idx.insert(b_idx.end(), {base, base + i - 1, base + i});
      break;
    case 5:
      for (u32 i = 0; i + 1 < count; i += 2) b_idx.insert(b_idx.end(), {base + i, base + i + 1});
      break;
    case 6:
      for (u32 i = 1; i < count; i++) b_idx.insert(b_idx.end(), {base + i - 1, base + i});
      break;
    default:
      for (u32 i = 0; i < count; i++) b_idx.push_back(base + i);
      break;
  }
}

static void unpack_color(u32 v, float *o) {  // RGBA8888 -> 0..255 floats
  o[0] = (float)(v >> 24);
  o[1] = (float)((v >> 16) & 255);
  o[2] = (float)((v >> 8) & 255);
  o[3] = (float)(v & 255);
}

static float fog_float(u32 v) {
  u32 mant = bits(v, 0, 11), ex = bits(v, 11, 8), sg = bits(v, 19, 1);
  return u2f(sg << 31 | ex << 23 | mant << 12);
}

// True (and remembers the value) if the uniform at loc differs from what the program last received.
static bool uchanged(Program *p, int loc, const void *d, size_t n) {
  if (loc < 0) return false;
  if ((size_t)loc >= p->ucache.size()) p->ucache.resize(loc + 1);
  std::vector<u8> &v = p->ucache[loc];
  if (v.size() == n && !memcmp(v.data(), d, n)) return false;
  v.assign((const u8 *)d, (const u8 *)d + n);
  return true;
}

static void set_uniforms(Program *p) {
  static float tmp[64 * 4];
  for (int i = 0; i < 256; i++) tmp[i] = u2f(xf[i]);
  if (uchanged(p, p->u_posmem, tmp, 64 * 16)) glUniform4fv(p->u_posmem, 64, tmp);
  for (int i = 0; i < 32; i++) {
    for (int k = 0; k < 3; k++) tmp[i * 4 + k] = u2f(xf[0x400 + i * 3 + k]);
    tmp[i * 4 + 3] = 0;
  }
  if (uchanged(p, p->u_nrmmem, tmp, 32 * 16)) glUniform4fv(p->u_nrmmem, 32, tmp);
  for (int i = 0; i < 256; i++) tmp[i] = u2f(xf[0x500 + i]);
  if (uchanged(p, p->u_postmem, tmp, 64 * 16)) glUniform4fv(p->u_postmem, 64, tmp);
  float lc[32], lcos[32], ld[32], lp[32], ldir[32];
  for (int i = 0; i < 8; i++) {
    u32 b = 0x600 + 16 * i;
    unpack_color(xf[b + 3], lc + 4 * i);
    for (int k = 0; k < 3; k++) {
      lcos[4 * i + k] = u2f(xf[b + 4 + k]);
      ld[4 * i + k] = u2f(xf[b + 7 + k]);
      lp[4 * i + k] = u2f(xf[b + 10 + k]);
      ldir[4 * i + k] = u2f(xf[b + 13 + k]);
    }
    lcos[4 * i + 3] = ld[4 * i + 3] = lp[4 * i + 3] = ldir[4 * i + 3] = 0;
  }
  if (uchanged(p, p->u_lcol, lc, 8 * 16)) glUniform4fv(p->u_lcol, 8, lc);
  if (uchanged(p, p->u_lcos, lcos, 8 * 16)) glUniform4fv(p->u_lcos, 8, lcos);
  if (uchanged(p, p->u_ldist, ld, 8 * 16)) glUniform4fv(p->u_ldist, 8, ld);
  if (uchanged(p, p->u_lpos, lp, 8 * 16)) glUniform4fv(p->u_lpos, 8, lp);
  if (uchanged(p, p->u_ldir, ldir, 8 * 16)) glUniform4fv(p->u_ldir, 8, ldir);
  float ma[16];
  for (int i = 0; i < 4; i++) unpack_color(xf[XF_AMB0 + i], ma + 4 * i);
  if (uchanged(p, p->u_matamb, ma, 4 * 16)) glUniform4fv(p->u_matamb, 4, ma);
  // projection (row-major, uploaded transposed)
  float pr[6];
  for (int i = 0; i < 6; i++) pr[i] = u2f(xf[XF_PROJ + i]);
  float m[16] = {};
  if (xf[XF_PROJ + 6] == 0) {
    m[0] = pr[0]; m[2] = pr[1]; m[5] = pr[2]; m[6] = pr[3]; m[10] = pr[4]; m[11] = pr[5]; m[14] = -1;
  } else {
    m[0] = pr[0]; m[3] = pr[1]; m[5] = pr[2]; m[7] = pr[3]; m[10] = pr[4]; m[11] = pr[5]; m[15] = 1;
  }
  if (uchanged(p, p->u_proj, m, 64)) glUniformMatrix4fv(p->u_proj, 1, GL_TRUE, m);
  float wd = u2f(xf[XF_VIEWPORT]), ht = u2f(xf[XF_VIEWPORT + 1]), zr = u2f(xf[XF_VIEWPORT + 2]);
  float xo = u2f(xf[XF_VIEWPORT + 3]), yo = u2f(xf[XF_VIEWPORT + 4]), fz = u2f(xf[XF_VIEWPORT + 5]);
  float offx = (float)(bits(bp[0x59], 0, 10) * 2), offy = (float)(bits(bp[0x59], 10, 10) * 2);
  float vs[4] = {wd / (EFB_W / 2.0f), ht / (EFB_H / 2.0f), 2.0f * zr / 16777216.0f, 0};
  float vo[4] = {(xo - offx) / (EFB_W / 2.0f) - 1.0f, (yo - offy) / (EFB_H / 2.0f) - 1.0f, 2.0f * fz / 16777216.0f - 1.0f, 0};
  vs[0] *= b_k;
  if (uchanged(p, p->u_vpscale, vs, 1 * 16)) glUniform4fv(p->u_vpscale, 1, vs);
  if (uchanged(p, p->u_vpoff, vo, 1 * 16)) glUniform4fv(p->u_vpoff, 1, vo);
  { float ps = std::max(1.0f, bits(bp[0x22], 8, 8) / 6.0f * g_scale); if (uchanged(p, p->u_ptsize, &ps, 4)) glUniform1f(p->u_ptsize, ps); }
  // pixel
  int col[16], kc[16];
  for (int i = 0; i < 4; i++) {
    col[4 * i + 0] = sbits(tev_color[i][0], 0, 11);
    col[4 * i + 3] = sbits(tev_color[i][0], 12, 11);
    col[4 * i + 2] = sbits(tev_color[i][1], 0, 11);
    col[4 * i + 1] = sbits(tev_color[i][1], 12, 11);
    kc[4 * i + 0] = bits(tev_konst[i][0], 0, 8);
    kc[4 * i + 3] = bits(tev_konst[i][0], 12, 8);
    kc[4 * i + 2] = bits(tev_konst[i][1], 0, 8);
    kc[4 * i + 1] = bits(tev_konst[i][1], 12, 8);
  }
  if (uchanged(p, p->u_colors, col, 4 * 16)) glUniform4iv(p->u_colors, 4, col);
  if (uchanged(p, p->u_kcolors, kc, 4 * 16)) glUniform4iv(p->u_kcolors, 4, kc);
  int ar[4] = {(int)bits(bp[0xF3], 0, 8), (int)bits(bp[0xF3], 8, 8), 0, 0};
  if (uchanged(p, p->u_alpharef, ar, 1 * 16)) glUniform4iv(p->u_alpharef, 1, ar);
  float td[32], tcs[32];
  for (int i = 0; i < 8; i++) {
    td[4 * i] = (float)b_tex[i].w;
    td[4 * i + 1] = (float)b_tex[i].h;
    td[4 * i + 2] = td[4 * i + 3] = 0;
    tcs[4 * i] = (float)(bits(bp[0x30 + 2 * i], 0, 16) + 1);
    tcs[4 * i + 1] = (float)(bits(bp[0x31 + 2 * i], 0, 16) + 1);
    tcs[4 * i + 2] = tcs[4 * i + 3] = 0;
  }
  if (uchanged(p, p->u_texdim, td, 8 * 16)) glUniform4fv(p->u_texdim, 8, td);
  if (uchanged(p, p->u_tcscale, tcs, 8 * 16)) glUniform4fv(p->u_tcscale, 8, tcs);
  int im[24];
  for (int m3 = 0; m3 < 3; m3++) {
    u32 A = bp[0x06 + 3 * m3], B = bp[0x07 + 3 * m3], C = bp[0x08 + 3 * m3];
    int sc = bits(A, 22, 2) | bits(B, 22, 2) << 2 | bits(C, 22, 2) << 4;
    int *r0 = im + 8 * m3, *r1 = r0 + 4;
    r0[0] = sbits(A, 0, 11); r0[1] = sbits(B, 0, 11); r0[2] = sbits(C, 0, 11); r0[3] = 17 - sc;
    r1[0] = sbits(A, 11, 11); r1[1] = sbits(B, 11, 11); r1[2] = sbits(C, 11, 11); r1[3] = 17 - sc;
  }
  if (uchanged(p, p->u_indmtx, im, 6 * 16)) glUniform4iv(p->u_indmtx, 6, im);
  int fc[4] = {(int)bits(bp[0xF2], 16, 8), (int)bits(bp[0xF2], 8, 8), (int)bits(bp[0xF2], 0, 8), 0};
  if (uchanged(p, p->u_fogcol, fc, 1 * 16)) glUniform4iv(p->u_fogcol, 1, fc);
  float ff[4] = {fog_float(bp[0xEE]), fog_float(bp[0xF1]), 0, 0};
  if (uchanged(p, p->u_fogf, ff, 1 * 16)) glUniform4fv(p->u_fogf, 1, ff);
  int fi[4] = {0, (int)(bp[0xEF] & 0xFFFFFF), 0, (int)(bp[0xF0] & 0x1F)};
  if (fi[1] == 0) fi[1] = 1;
  if (uchanged(p, p->u_fogi, fi, 1 * 16)) glUniform4iv(p->u_fogi, 1, fi);
  { float da = bits(bp[0x42], 0, 8) / 255.0f; if (uchanged(p, p->u_dstalpha, &da, 4)) glUniform1f(p->u_dstalpha, da); }
}

static void apply_scissor() {
  int offx = bits(bp[0x59], 0, 10) * 2, offy = bits(bp[0x59], 10, 10) * 2;
  int x0 = (int)bits(bp[0x20], 12, 11) - offx, y0 = (int)bits(bp[0x20], 0, 11) - offy;
  int x1 = (int)bits(bp[0x21], 12, 11) - offx + 1, y1 = (int)bits(bp[0x21], 0, 11) - offy + 1;
  x0 = std::max(0, x0); y0 = std::max(0, y0);
  x1 = std::min(EFB_W, x1); y1 = std::min(EFB_H, y1);
  if (x1 < x0) x1 = x0;
  if (y1 < y0) y1 = y0;
  glEnable(GL_SCISSOR_TEST);
  glScissor(PX(x0), y0 * g_scale, PX(x1) - PX(x0), (y1 - y0) * g_scale);
}

static void apply_state() {
  u32 pf = bp[0x43] & 7;
  bool has_alpha = pf == 1;
  // depth
  u32 zm = bp[0x40];
  static bool nodepth = getenv("HM_GPU_NODEPTH") != nullptr;  // debug
  if ((zm & 1) && !nodepth) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_NEVER + bits(zm, 1, 3));
    glDepthMask((zm >> 4) & 1);
  } else {
    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);
  }
  // blend
  u32 bm = bp[0x41];
  bool blend = bm & 1, logic = (bm >> 1) & 1, sub = (bm >> 11) & 1;
  bool cu = (bm >> 3) & 1, au = ((bm >> 4) & 1) && has_alpha;
  glColorMask(cu, cu, cu, au);
  bool dstalpha = (bp[0x42] >> 8) & 1;
  glDisable(GL_COLOR_LOGIC_OP);
  if (sub) {
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT);
    glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
  } else if (blend) {
    static const int srcf[8] = {GL_ZERO, GL_ONE, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR,
                                GL_SRC1_ALPHA, GL_ONE_MINUS_SRC1_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA};
    static const int dstf[8] = {GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR,
                                GL_SRC1_ALPHA, GL_ONE_MINUS_SRC1_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA};
    static const int srcfa[8] = {GL_ZERO, GL_ONE, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,
                                 GL_SRC1_ALPHA, GL_ONE_MINUS_SRC1_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA};
    static const int dstfa[8] = {GL_ZERO, GL_ONE, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
                                 GL_SRC1_ALPHA, GL_ONE_MINUS_SRC1_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA};
    u32 s = bits(bm, 8, 3), d = bits(bm, 5, 3);
    int cs = srcf[s], cd = dstf[d], as = srcfa[s], ad = dstfa[d];
    if (!has_alpha) {
      auto fix = [](int f) { return f == GL_DST_ALPHA ? GL_ONE : f == GL_ONE_MINUS_DST_ALPHA ? GL_ZERO : f; };
      cs = fix(cs); cd = fix(cd); as = fix(as); ad = fix(ad);
    }
    if (dstalpha) { as = GL_ONE; ad = GL_ZERO; }
    if (!need_dual_source()) {  // single output: its alpha is the TEV alpha
      auto nod = [](int f) { return f == GL_SRC1_ALPHA ? GL_SRC_ALPHA : f == GL_ONE_MINUS_SRC1_ALPHA ? GL_ONE_MINUS_SRC_ALPHA : f; };
      cs = nod(cs); cd = nod(cd); as = nod(as); ad = nod(ad);
    }
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(cs, cd, as, ad);
  } else {
    glDisable(GL_BLEND);
    if (logic) {
      glEnable(GL_COLOR_LOGIC_OP);
      glLogicOp(GL_CLEAR + bits(bm, 12, 4));
    }
  }
  // cull
  u32 cull = bits(bp[0x00], 14, 2);
  static bool nocull = getenv("HM_GPU_NOCULL") != nullptr;  // debug
  if (nocull) cull = 0;
  if (b_pclass != PC_TRI || cull == 0) {
    glDisable(GL_CULL_FACE);
  } else {
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(cull == 1 ? GL_BACK : cull == 2 ? GL_FRONT : GL_FRONT_AND_BACK);
  }
  if (b_pclass == PC_LINE) glLineWidth(std::max(1.0f, bits(bp[0x22], 0, 8) / 6.0f * g_scale));
  apply_scissor();
}


void flush_batch() {
  if (b_idx.empty()) {
    b_verts.clear();
    return;
  }
  ProfScope ps(g_prof.flush);
  g_prof.draws++;
  {  // debug: HM_GPU_SKIPDRAWS=a-b skips draws a..b of each frame; HM_GPU_DRAWLOG=1 lists them
    static int lo = -1, hi = -1, log = -1;
    if (log < 0) {
      log = getenv("HM_GPU_DRAWLOG") != nullptr;
      if (const char *e = getenv("HM_GPU_SKIPDRAWS")) sscanf(e, "%d-%d", &lo, &hi);
    }
    int id = s_draw_idx++;
    if (log)
      fprintf(stderr, "draw %d: pc %d nv %zu ni %zu gm %06x cc0 %06x ac0 %06x ord %06x tex0 %06x@%06x zm %02x bm %04x proj %u vcd %05x\n",
              id, b_pclass, b_verts.size(), b_idx.size(), bp[0], bp[0xC0], bp[0xC1], bp[0x28], bp[0x88], bp[0x94], bp[0x40],
              bp[0x41], xf[XF_PROJ + 6], 0u);
    if (log && !b_verts.empty()) {
      const Vertex &v = b_verts[0];
      u32 r = std::min<u32>(v.midx[0], 61) * 4;
      float e[3];
      for (int k = 0; k < 3; k++)
        e[k] = u2f(xf[r + 4 * k]) * v.pos[0] + u2f(xf[r + 4 * k + 1]) * v.pos[1] + u2f(xf[r + 4 * k + 2]) * v.pos[2] + u2f(xf[r + 4 * k + 3]);
      float pr[6];
      for (int i = 0; i < 6; i++) pr[i] = u2f(xf[XF_PROJ + i]);
      bool persp = xf[XF_PROJ + 6] == 0;
      float cz = pr[4] * e[2] + pr[5], cw = persp ? -e[2] : 1.0f;
      float zr = u2f(xf[XF_VIEWPORT + 2]), fz = u2f(xf[XF_VIEWPORT + 5]);
      fprintf(stderr, "   v0 pos %g %g %g eye %g %g %g proj %g %g %g %g %g %g clipz %g w %g depth %g (zr %g fz %g) clearz %06x\n",
              v.pos[0], v.pos[1], v.pos[2], e[0], e[1], e[2], pr[0], pr[1], pr[2], pr[3], pr[4], pr[5], cz, cw,
              fz + zr * cz / cw, zr, fz, bp[0x51]);
    }
    static int dumpid = getenv("HM_GPU_DUMPDRAW") ? atoi(getenv("HM_GPU_DUMPDRAW")) : -1;
    if (id == dumpid)
      for (size_t i = 0; i < b_verts.size(); i++)
        fprintf(stderr, "  vtx %zu: %g %g %g mtx %u col %02x%02x%02x%02x tc %g %g\n", i, b_verts[i].pos[0], b_verts[i].pos[1],
                b_verts[i].pos[2], b_verts[i].midx[0], b_verts[i].col[0][0], b_verts[i].col[0][1], b_verts[i].col[0][2],
                b_verts[i].col[0][3], b_verts[i].tc[0][0], b_verts[i].tc[0][1]);
    if (id >= lo && id <= hi) { b_verts.clear(); b_idx.clear(); return; }
  }
  glBindFramebuffer(GL_FRAMEBUFFER, s_efb_fbo);
  glViewport(0, 0, W, H);
  shader_key(s_key, b_comp, b_pclass);
  Program *p = shader_get(s_key);
  if (p->prog != s_cur_prog) { glUseProgram(p->prog); s_cur_prog = p->prog; }
  set_uniforms(p);
  apply_state();
  for (int n = 0; n < 8; n++) {
    if (!b_tex[n].gltex) continue;
    glActiveTexture(GL_TEXTURE0 + n);
    glBindTexture(GL_TEXTURE_2D, b_tex[n].gltex);
    unsigned s = s_samplers[n];
    glBindSampler(n, s);
    BoundTex &lt = s_last_samp[n];
    if (lt.gltex == 1 && lt.wrap_s == b_tex[n].wrap_s && lt.wrap_t == b_tex[n].wrap_t && lt.minf == b_tex[n].minf &&
        lt.magf == b_tex[n].magf && lt.bias == b_tex[n].bias && lt.minlod == b_tex[n].minlod && lt.maxlod == b_tex[n].maxlod)
      continue;
    lt = b_tex[n];
    lt.gltex = 1;  // marks "params valid"
    glSamplerParameteri(s, GL_TEXTURE_WRAP_S, b_tex[n].wrap_s);
    glSamplerParameteri(s, GL_TEXTURE_WRAP_T, b_tex[n].wrap_t);
    glSamplerParameteri(s, GL_TEXTURE_MIN_FILTER, b_tex[n].minf);
    glSamplerParameteri(s, GL_TEXTURE_MAG_FILTER, b_tex[n].magf);
    if (s_aniso > 1) glSamplerParameterf(s, 0x84FE /*TEXTURE_MAX_ANISOTROPY*/, b_tex[n].minf == GL_NEAREST ? 1.0f : s_aniso);
    glSamplerParameterf(s, GL_TEXTURE_LOD_BIAS, b_tex[n].bias + (g_scale > 1 ? std::log2((float)g_scale) * 0 : 0));
    glSamplerParameterf(s, GL_TEXTURE_MIN_LOD, b_tex[n].minlod);
    glSamplerParameterf(s, GL_TEXTURE_MAX_LOD, b_tex[n].maxlod);
  }
  glBindVertexArray(s_vao);
  size_t vbytes = b_verts.size() * sizeof(Vertex), ibytes = b_idx.size() * 4;
  glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
  s_vb_off = (s_vb_off + sizeof(Vertex) - 1) / sizeof(Vertex) * sizeof(Vertex);
  if (s_vb_off + vbytes > VB_SIZE) {
    glBufferData(GL_ARRAY_BUFFER, std::max(VB_SIZE, vbytes), nullptr, GL_STREAM_DRAW);
    s_vb_off = 0;
  }
  void *vp = glMapBufferRange(GL_ARRAY_BUFFER, s_vb_off, vbytes,
                              GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
  if (vp) { memcpy(vp, b_verts.data(), vbytes); glUnmapBuffer(GL_ARRAY_BUFFER); }
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ebo);
  if (s_ib_off + ibytes > IB_SIZE) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, std::max(IB_SIZE, ibytes), nullptr, GL_STREAM_DRAW);
    s_ib_off = 0;
  }
  void *ip = glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, s_ib_off, ibytes,
                              GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
  if (ip) { memcpy(ip, b_idx.data(), ibytes); glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER); }
  GLenum mode = b_pclass == PC_TRI ? GL_TRIANGLES : b_pclass == PC_LINE ? GL_LINES : GL_POINTS;
  glDrawElementsBaseVertex(mode, (int)b_idx.size(), GL_UNSIGNED_INT, (const void *)s_ib_off,
                           (int)(s_vb_off / sizeof(Vertex)));
  s_vb_off += vbytes;
  s_ib_off += ibytes;
  b_verts.clear();
  b_idx.clear();
}

// ---------------- EFB copies ----------------
static void clear_rect(int x, int y, int w, int h) {
  u32 pf = bp[0x43] & 7;
  bool has_alpha = pf == 1;
  u32 bm = bp[0x41];
  bool cu = (bm >> 3) & 1, au = (bm >> 4) & 1, zu = (bp[0x40] >> 4) & 1;
  u32 ar = bp[0x4F], gb = bp[0x50];
  float r = bits(ar, 0, 8) / 255.0f, a = bits(ar, 8, 8) / 255.0f, g = bits(gb, 8, 8) / 255.0f, b = bits(gb, 0, 8) / 255.0f;
  if (!has_alpha) { a = 1.0f; au = true; }
  glBindFramebuffer(GL_FRAMEBUFFER, s_efb_fbo);
  glEnable(GL_SCISSOR_TEST);
  glScissor(PX(x), y * g_scale, PX(x + w) - PX(x), h * g_scale);
  glColorMask(cu, cu, cu, au);
  glDepthMask(zu);
  glClearColor(r, g, b, a);
  glClearDepth((bp[0x51] & 0xFFFFFF) / 16777215.0);
  GLbitfield mask = 0;
  if (cu || au) mask |= GL_COLOR_BUFFER_BIT;
  if (zu) mask |= GL_DEPTH_BUFFER_BIT;
  if (mask) glClear(mask);
}

static void run_copy_pass(unsigned dst, int dw, int dh, int sx, int sy, int sw, int sh, bool native, bool half,
                          int fmt, int flags, const float *filt, float yscale) {
  int step = g_scale;
  float st[4] = {(native ? XS() : 1.0f) * (half ? 2 : 1), (float)((native ? g_scale : 1) * (half ? 2 : 1)),
                 native ? std::max(1.0f, std::round(XS())) : 1.0f, (float)(native ? g_scale : 1)};
  glBindFramebuffer(GL_FRAMEBUFFER, s_copy_fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, dst, 0);
  glViewport(0, 0, dw, dh);
  glDisable(GL_SCISSOR_TEST);
  glDisable(GL_BLEND);
  glDisable(GL_COLOR_LOGIC_OP);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glColorMask(1, 1, 1, 1);
  glUseProgram(s_copy_prog);
  s_cur_prog = 0;
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, s_efb_color);
  glBindSampler(0, 0);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, s_efb_depth);
  glBindSampler(1, 0);
  glUniform1i(glGetUniformLocation(s_copy_prog, "efb"), 0);
  glUniform1i(glGetUniformLocation(s_copy_prog, "efbz"), 1);
  int src[4] = {sx, sy, sw, sh};
  int par[4] = {step, half ? 1 : 0, fmt, flags};
  glUniform4iv(glGetUniformLocation(s_copy_prog, "src"), 1, src);
  glUniform4iv(glGetUniformLocation(s_copy_prog, "params"), 1, par);
  glUniform4fv(glGetUniformLocation(s_copy_prog, "filt"), 1, filt);
  glUniform1f(glGetUniformLocation(s_copy_prog, "yscale"), yscale);
  glUniform4fv(glGetUniformLocation(s_copy_prog, "stepf"), 1, st);
  glBindVertexArray(s_empty_vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(s_vao);
}

static void copy_filter(float *f) {
  u32 lo = bp[0x53], hi = bp[0x54];
  u32 w[7] = {bits(lo, 0, 6), bits(lo, 6, 6), bits(lo, 12, 6), bits(lo, 18, 6), bits(hi, 0, 6), bits(hi, 6, 6), bits(hi, 12, 6)};
  f[0] = (w[0] + w[1]) / 64.0f;
  f[1] = (w[2] + w[3] + w[4]) / 64.0f;
  f[2] = (w[5] + w[6]) / 64.0f;
  if (f[0] + f[1] + f[2] == 0) { f[1] = 1.0f; }
}

static const int s_copy_texfmt[16] = {TF_I4, TF_I8, TF_IA4, TF_IA8, TF_RGB565, TF_RGB5A3, TF_RGBA8, TF_I8,
                                      TF_I8, TF_I8, TF_I8, TF_IA8, TF_IA8, TF_I8, TF_I8, TF_I8};


// ---------------- async EFB-copy write-back ----------------
struct PendingCopy {
  unsigned pbo = 0;
  GLsync fence = nullptr;
  u32 dest = 0, stride = 0, serial = 0, frame = 0;
  int dw = 0, dh = 0, tf = 0, fmt = 0;
};
static std::vector<PendingCopy> s_pending_copies;
static std::vector<unsigned> s_pbo_pool;
static u32 s_copy_serial = 0, s_frame = 0;
static bool s_sync_copies = getenv("HM_GPU_SYNC_COPIES") != nullptr;  // old behaviour (immediate write-back)

static void finish_copy(PendingCopy &pc) {
  glClientWaitSync(pc.fence, GL_SYNC_FLUSH_COMMANDS_BIT, 2000000000ull);
  glDeleteSync(pc.fence);
  if (texcache_copy_pending(pc.dest, pc.serial)) {
    glBindBuffer(GL_PIXEL_PACK_BUFFER, pc.pbo);
    const u8 *px = (const u8 *)glMapBufferRange(GL_PIXEL_PACK_BUFFER, 0, (size_t)pc.dw * pc.dh * 4, GL_MAP_READ_BIT);
    if (px) {
      if (getenv("HM_GPU_DUMPCOPIES")) { char fn[64]; snprintf(fn, sizeof fn, "copy_%08x_%dx%d.rgba", pc.dest, pc.dw, pc.dh); FILE *df = fopen(fn, "wb"); if (df) { fwrite(px, 1, (size_t)pc.dw * pc.dh * 4, df); fclose(df); } }
      tex_encode(ram_ptr(pc.dest), px, pc.dw, pc.dh, pc.tf, pc.stride, pc.fmt);
      glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
      g_epoch++;
      texcache_copy_resolved(pc.dest);
    }
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
  }
  s_pbo_pool.push_back(pc.pbo);
}

// Completes write-backs whose GPU work is done (or all of them / those older than a frame when waiting).
void copies_resolve(bool wait_all) {
  ProfScope pr(g_prof.readback);
  size_t j = 0;
  for (size_t i = 0; i < s_pending_copies.size(); i++) {
    PendingCopy &pc = s_pending_copies[i];
    bool done = wait_all || s_frame - pc.frame >= 2 ||
                glClientWaitSync(pc.fence, 0, 0) != GL_TIMEOUT_EXPIRED;
    if (done) finish_copy(pc);
    else s_pending_copies[j++] = pc;
  }
  s_pending_copies.resize(j);
}

void copies_resolve_addr(u32 addr) {
  addr &= 0x01FFFFFF;
  size_t j = 0;
  for (size_t i = 0; i < s_pending_copies.size(); i++) {
    PendingCopy &pc = s_pending_copies[i];
    if ((pc.dest & 0x01FFFFFF) == addr) finish_copy(pc);
    else s_pending_copies[j++] = pc;
  }
  s_pending_copies.resize(j);
}

void efb_copy(u32 trig) {
  flush_batch();
  ProfScope ps(g_prof.copy);
  g_prof.copies++;
  int sx = bits(bp[0x49], 0, 10), sy = bits(bp[0x49], 10, 10);
  int sw = bits(bp[0x4A], 0, 10) + 1, sh = bits(bp[0x4A], 10, 10) + 1;
  if (sx + sw > EFB_W) sw = std::max(0, EFB_W - sx);
  if (sy + sh > EFB_H) sh = std::max(0, EFB_H - sy);
  u32 dest = (bp[0x4B] & 0xFFFFFF) << 5;
  bool to_xfb = (trig >> 14) & 1, clear = (trig >> 11) & 1, half = (trig >> 9) & 1;
  float filt[4];
  copy_filter(filt);
  if (sw > 0 && sh > 0) {
    if (to_xfb) {
      float yscale = 1.0f;
      if ((trig >> 10) & 1) {
        u32 ys = bp[0x4E] & 0x1FF;
        if (ys) yscale = 256.0f / ys;
      }
      int xfb_lines = (int)((sh - 1) * yscale) + 1;
      int dw = wide() ? PX(sx + sw) - PX(sx) : sw * g_scale, dh = xfb_lines * g_scale;
      s_xfb_aspect = s_aspect;
      if (!s_xfb_tex || s_xfb_w != dw || s_xfb_h != dh) {
        if (s_xfb_tex) glDeleteTextures(1, &s_xfb_tex);
        s_xfb_tex = make_tex(dw, dh, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        s_xfb_w = dw;
        s_xfb_h = dh;
      }
      static const float gam[4] = {1.0f, 1.7f, 2.2f, 2.2f};
      filt[3] = gam[bits(trig, 7, 2)];
      gpu_timer(1);
      run_copy_pass(s_xfb_tex, dw, dh, PX(sx), sy * g_scale, PX(sx + sw) - PX(sx), sh * g_scale, false, false,
                    6, 4, filt, yscale);
      s_have_xfb = true;
      u32 width = bits(bp[0x4D], 0, 10) * 16;
      if (!width) width = sw;
      gpu_timer(0);
      s_frame++;
      copies_resolve(false);
      static bool xfb_ram = getenv("HM_GPU_XFB_RAM") != nullptr;  // YUYV write-back for CPU readers (off: slow)
      if (xfb_ram) {
        // native-resolution readback, encoded as YUYV into guest RAM for CPU readers
        int nw = sw, nh = xfb_lines;
        unsigned nt = make_tex(nw, nh, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
        run_copy_pass(nt, nw, nh, PX(sx), sy * g_scale, PX(sx + sw) - PX(sx), sh * g_scale, true, false, 6, 4, filt,
                      yscale);
        std::vector<u8> px((size_t)nw * nh * 4);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        { ProfScope pr(g_prof.readback); glReadPixels(0, 0, nw, nh, GL_RGBA, GL_UNSIGNED_BYTE, px.data()); }
        glDeleteTextures(1, &nt);
        u32 rowb = width * 2;
        if (ram_ok(dest, rowb * nh)) {
          for (int y = 0; y < nh; y++) {
            u8 *d = ram_ptr(dest + y * rowb);
            for (int x = 0; x + 1 < nw && x + 1 < (int)width; x += 2) {
              const u8 *a = &px[((size_t)y * nw + x) * 4], *b = a + 4;
              auto Y = [](const u8 *c) { return (u8)std::min(235, ((66 * c[0] + 129 * c[1] + 25 * c[2] + 128) >> 8) + 16); };
              int r = (a[0] + b[0]) / 2, g = (a[1] + b[1]) / 2, bl = (a[2] + b[2]) / 2;
              int U = ((-38 * r - 74 * g + 112 * bl + 128) >> 8) + 128;
              int V = ((112 * r - 94 * g - 18 * bl + 128) >> 8) + 128;
              d[2 * x] = Y(a); d[2 * x + 1] = (u8)std::clamp(U, 16, 240);
              d[2 * x + 2] = Y(b); d[2 * x + 3] = (u8)std::clamp(V, 16, 240);
            }
          }
          g_epoch++;
        }
      }
      if (clear) clear_rect(sx, sy, sw, sh);
      if (s_pending_aspect != s_aspect || (s_pending_scale && s_pending_scale != g_scale)) resize_efb(s_pending_aspect);
      frame_timer_tick();
      texcache_gc();
      g_prof.xfbs++;
      prof_frame();
      cap_xfb();
      s_draw_idx = 0;
      gpu_cb_xfb_copy(dest, width, xfb_lines);
      return;
    }
    // copy to texture
    int fmt = bits(trig, 3, 4);
    fmt = fmt / 2 + (fmt & 1) * 8;
    bool intensity = (trig >> 15) & 1;
    bool depth = (bp[0x43] & 7) == 3;
    int flags = (intensity ? 1 : 0) | (depth ? 2 : 0);
    int tf = s_copy_texfmt[fmt & 15];
    int dw = half ? std::max(1, sw / 2) : sw, dh = half ? std::max(1, sh / 2) : sh;
    int hw = wide() ? std::max(1, (PX(sx + sw) - PX(sx)) / (half ? 2 : 1)) : dw * g_scale;
    unsigned tex = make_tex(hw, dh * g_scale, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    run_copy_pass(tex, hw, dh * g_scale, PX(sx), sy * g_scale, PX(sx + sw) - PX(sx), sh * g_scale,
                  false, half, fmt, flags, filt, 1.0f);
    u32 stride = bits(bp[0x4D], 0, 10) * 32;
    u32 bytes = 0;
    {
      int tw = (tf == TF_I4) ? 8 : (tf == TF_I8 || tf == TF_IA4) ? 8 : 4;
      int th = (tf == TF_I4) ? 8 : 4;
      bytes = stride * ((dh + th - 1) / th);
      (void)tw;
    }
    if (stride && ram_ok(dest, bytes)) {
      // native-resolution image for the guest RAM copy, read back asynchronously through a PBO
      PendingCopy pc;
      pc.dest = dest; pc.dw = dw; pc.dh = dh; pc.tf = tf; pc.fmt = fmt; pc.stride = stride;
      pc.serial = ++s_copy_serial;
      pc.frame = s_frame;
      unsigned nt = 0;
      if (!(g_scale == 1 && !wide())) {
        nt = make_tex(dw, dh, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
        run_copy_pass(nt, dw, dh, PX(sx), sy * g_scale, PX(sx + sw) - PX(sx), sh * g_scale, true, half, fmt, flags,
                      filt, 1.0f);
      }
      if (!s_pbo_pool.empty()) { pc.pbo = s_pbo_pool.back(); s_pbo_pool.pop_back(); }
      else glGenBuffers(1, &pc.pbo);
      {
        ProfScope pr(g_prof.readback);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, pc.pbo);
        glBufferData(GL_PIXEL_PACK_BUFFER, (size_t)dw * dh * 4, nullptr, GL_STREAM_READ);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadPixels(0, 0, dw, dh, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
        pc.fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
      }
      if (nt) glDeleteTextures(1, &nt);
      texcache_register_copy(dest, tex, dw, dh, tf, bytes, pc.serial);
      s_pending_copies.push_back(pc);
      if (s_pending_copies.size() > 32) copies_resolve(true);  // no frame boundaries seen: don't pile up
      if (s_sync_copies) copies_resolve(true);
    } else {
      glDeleteTextures(1, &tex);
    }
  }
  if (clear) clear_rect(sx, sy, sw, sh);
}


// ---------------- present ----------------
void present(int ww, int wh) {
  flush_batch();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_SCISSOR_TEST);
  glColorMask(1, 1, 1, 1);
  glViewport(0, 0, ww, wh);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  if (!s_have_xfb) return;
  int vw = ww, vh = ww * 3 / 4;
  if (vh > wh) { vh = wh; vw = wh * 4 / 3; }
  if (s_xfb_aspect != 4.0f / 3.0f) {
    vw = ww;
    vh = (int)std::lround(ww / s_xfb_aspect);
    if (vh > wh) { vh = wh; vw = (int)std::lround(wh * s_xfb_aspect); }
  }
  glViewport((ww - vw) / 2, (wh - vh) / 2, vw, vh);
  glDisable(GL_BLEND);
  glDisable(GL_COLOR_LOGIC_OP);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glUseProgram(s_present_prog);
  s_cur_prog = 0;
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, s_xfb_tex);
  glBindSampler(0, 0);
  glUniform1i(glGetUniformLocation(s_present_prog, "tex"), 0);
  glBindVertexArray(s_empty_vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(s_vao);
}

void present_ram_xfb(u32 addr, int w, int h, int stride, int ww, int wh) {
  flush_batch();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_SCISSOR_TEST);
  glColorMask(1, 1, 1, 1);
  glViewport(0, 0, ww, wh);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  if (w < 2 || h < 1) return;
  if (stride < w) stride = w;
  if (!ram_ok(addr, (u32)stride * 2 * (h - 1) + w * 2)) return;
  int tw = w / 2;
  glActiveTexture(GL_TEXTURE0);
  if (!s_yuyv_tex || s_yuyv_w != tw || s_yuyv_h != h) {
    if (s_yuyv_tex) glDeleteTextures(1, &s_yuyv_tex);
    s_yuyv_tex = make_tex(tw, h, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
    s_yuyv_w = tw;
    s_yuyv_h = h;
  }
  glBindTexture(GL_TEXTURE_2D, s_yuyv_tex);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, stride / 2);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, tw, h, GL_RGBA, GL_UNSIGNED_BYTE, ram_ptr(addr));
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  int vw = ww, vh = ww * 3 / 4;
  if (vh > wh) { vh = wh; vw = wh * 4 / 3; }
  glViewport((ww - vw) / 2, (wh - vh) / 2, vw, vh);
  glDisable(GL_BLEND);
  glDisable(GL_COLOR_LOGIC_OP);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glUseProgram(s_yuyv_prog);
  s_cur_prog = 0;
  glBindSampler(0, 0);
  glUniform1i(glGetUniformLocation(s_yuyv_prog, "tex"), 0);
  int sz[2] = {tw * 2, h};
  glUniform2iv(glGetUniformLocation(s_yuyv_prog, "size"), 1, sz);
  glBindVertexArray(s_empty_vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(s_vao);
}

bool read_xfb(std::vector<u8> &rgba, int &w, int &h) {
  if (!s_have_xfb) return false;
  w = s_xfb_w;
  h = s_xfb_h;
  rgba.resize((size_t)w * h * 4);
  flush_batch();
  GLint old_fb = 0, old_read_fb = 0, old_pack = 0;   // debug readback: leave GL state as we found it
  glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &old_fb);
  glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &old_read_fb);
  glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING, &old_pack);
  glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, s_copy_fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, s_xfb_tex, 0);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, rgba.data());
  glBindBuffer(GL_PIXEL_PACK_BUFFER, old_pack);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, old_fb);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, old_read_fb);
  return true;
}

// ---------------- peek / poke ----------------
u32 efb_peek(int x, int y, int is_z) {
  flush_batch();
  if (x < 0 || y < 0 || x >= EFB_W || y >= EFB_H) return 0;
  glBindFramebuffer(GL_FRAMEBUFFER, s_efb_fbo);
  int hx = wide() ? (PX(x) + PX(x + 1)) / 2 : x * g_scale + g_scale / 2, hy = y * g_scale + g_scale / 2;
  if (is_z) {
    u32 d = 0;
    glReadPixels(hx, hy, 1, 1, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, &d);
    return d >> 8;
  }
  u8 c[4];
  glReadPixels(hx, hy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, c);
  u32 a = ((bp[0x43] & 7) == 1) ? c[3] : 255;
  return a << 24 | (u32)c[0] << 16 | (u32)c[1] << 8 | c[2];
}

void efb_poke(int x, int y, int is_z, u32 v) {
  flush_batch();
  if (x < 0 || y < 0 || x >= EFB_W || y >= EFB_H) return;
  int px0 = PX(x), pw = std::max(1, PX(x + 1) - px0);
  int n = pw * g_scale;
  glActiveTexture(GL_TEXTURE0);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  if (is_z) {
    std::vector<u32> d(n, (v & 0xFFFFFF) << 8 | (v >> 16 & 0xFF));
    glBindTexture(GL_TEXTURE_2D, s_efb_depth);
    glTexSubImage2D(GL_TEXTURE_2D, 0, px0, y * g_scale, pw, g_scale, GL_DEPTH_COMPONENT,
                    GL_UNSIGNED_INT, d.data());
  } else {
    std::vector<u8> c(n * 4);
    for (int i = 0; i < n; i++) {
      c[4 * i] = v >> 16; c[4 * i + 1] = v >> 8; c[4 * i + 2] = v; c[4 * i + 3] = v >> 24;
    }
    glBindTexture(GL_TEXTURE_2D, s_efb_color);
    glTexSubImage2D(GL_TEXTURE_2D, 0, px0, y * g_scale, pw, g_scale, GL_RGBA, GL_UNSIGNED_BYTE, c.data());
  }
}

}  // namespace gx
