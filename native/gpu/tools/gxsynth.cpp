// gxsynth: writes small synthetic .gxcap test streams exercising the GPU module.
// usage: gxsynth <outdir>   -> writes <outdir>/synth_*.gxcap
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

typedef uint8_t u8;
typedef uint32_t u32;

struct Stream {
  std::vector<u8> f;    // fifo bytes
  std::vector<u8> ram;  // RAM image (first N bytes)
  Stream() { ram.resize(4u << 20); }
  void u8_(u8 v) { f.push_back(v); }
  void u16_(uint16_t v) { f.push_back(v >> 8); f.push_back(v); }
  void u32_(u32 v) { f.push_back(v >> 24); f.push_back(v >> 16); f.push_back(v >> 8); f.push_back(v); }
  void f32_(float x) { u32 v; memcpy(&v, &x, 4); u32_(v); }
  void bp(u8 reg, u32 v) { u8_(0x61); u32_((u32)reg << 24 | (v & 0xFFFFFF)); }
  void cp(u8 reg, u32 v) { u8_(0x08); u8_(reg); u32_(v); }
  void xf(uint16_t addr, std::vector<u32> vals) {
    u8_(0x10);
    u32_((u32)(vals.size() - 1) << 16 | addr);
    for (u32 v : vals) u32_(v);
  }
  void xff(uint16_t addr, std::vector<float> vals) {
    std::vector<u32> u;
    for (float x : vals) { u32 v; memcpy(&v, &x, 4); u.push_back(v); }
    xf(addr, u);
  }
  void w32(u32 a, u32 v) { ram[a] = v >> 24; ram[a + 1] = v >> 16; ram[a + 2] = v >> 8; ram[a + 3] = v; }
  void w16(u32 a, uint16_t v) { ram[a] = v >> 8; ram[a + 1] = v; }
  void wf(u32 a, float x) { u32 v; memcpy(&v, &x, 4); w32(a, v); }

  bool save(const std::string &path) {
    FILE *o = fopen(path.c_str(), "wb");
    if (!o) return false;
    fwrite("GXCAP001", 1, 8, o);
    auto rec = [&](u32 tag, const void *d, u32 n) { fwrite(&tag, 4, 1, o); fwrite(&n, 4, 1, o); fwrite(d, 1, n, o); };
    rec(0x534D4152, ram.data(), (u32)ram.size());
    u32 fr = 0;
    rec(0x454D5246, &fr, 4);
    // split the fifo at odd boundaries to exercise command reassembly
    size_t pos = 0, chunk = 7;
    while (pos < f.size()) {
      size_t n = std::min(chunk, f.size() - pos);
      rec(0x4F464946, f.data() + pos, (u32)n);
      pos += n;
      chunk = chunk * 3 % 997 + 1;
    }
    fclose(o);
    return true;
  }

  // ---- higher level helpers mirroring the GX SDK register writes ----
  void init_common() {
    bp(0x00, 0);
    xf(0x1009, {1});           // 1 color channel
    xf(0x100e, {1}); xf(0x1010, {1});  // chan0 color/alpha: material from vertex, no lighting
    xf(0x103f, {0});
    xf(0x1018, {0 | 60 << 6 | 60 << 12 | 60 << 18 | 60u << 24});
    xf(0x1019, {60 | 60 << 6 | 60 << 12 | 60 << 18});
    load_posmtx(0, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0});
    load_posmtx(60, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0});
    // viewport 640x480, z 0..1
    xff(0x101a, {320.0f, -240.0f, 16777215.0f, 342.0f + 320.0f, 342.0f + 240.0f, 16777215.0f});
    ortho(0, 480, 0, 640, 0, 1);
    bp(0x20, 342 << 12 | 342);
    bp(0x21, (342 + 639) << 12 | (342 + 479));
    bp(0x59, 171 | 171 << 10);
    bp(0x40, 0x17);            // z test LEQUAL + update
    bp(0x41, 0x18 | 4 << 8 | 5 << 5);  // color+alpha update, src alpha / inv src alpha (blend off)
    bp(0x42, 0);
    bp(0x43, 0x40);            // RGB8_Z24, z comp loc
    bp(0xF3, 7 << 16 | 7 << 19);  // alpha test always
    bp(0xF6, 0 | 1 << 2); bp(0xF7, 2 | 3 << 2);  // swap table 0 identity
    bp(0xF8, 0 | 0 << 2); bp(0xF9, 0 | 3 << 2);
    bp(0xFA, 1 | 1 << 2); bp(0xFB, 1 | 3 << 2);
    bp(0xFC, 2 | 2 << 2); bp(0xFD, 2 | 3 << 2);
    // copy filter default (no AA, vfilter 0,0,21,22,21,0,0)
    bp(0x53, 0 | 0 << 6 | 21 << 12 | 22 << 18);
    bp(0x54, 21 | 0 << 6 | 0 << 12);
    bp(0x4F, 0x00 << 8 | 0x20); bp(0x50, 0x40 << 8 | 0x80);  // clear color (r=0x20 g=0x40 b=0x80)
    bp(0x51, 0xFFFFFF);
  }
  void load_posmtx(int row, std::vector<float> m) { xff(row * 4, m); }
  void ortho(float t, float b, float l, float r, float n, float fa) {
    xff(0x1020, {2.0f / (r - l), -(r + l) / (r - l), 2.0f / (t - b), -(t + b) / (t - b), -1.0f / (fa - n), -fa / (fa - n)});
    xf(0x1026, {1});
  }
  void persp(float fovy, float aspect, float n, float fa) {
    float ct = 1.0f / tanf(fovy * 0.5f * 3.14159265f / 180.0f);
    xff(0x1020, {ct / aspect, 0.0f, ct, 0.0f, -n / (fa - n), -(fa * n) / (fa - n)});
    xf(0x1026, {0});
  }
  // TEV stage 0..n: cc/ac raw
  void tev(int st, u32 cc, u32 ac) { bp(0xC0 + 2 * st, cc); bp(0xC1 + 2 * st, ac); }
  static u32 CC(u32 a, u32 b, u32 c, u32 d, u32 dest = 0) { return d | c << 4 | b << 8 | a << 12 | 1 << 19 | dest << 22; }
  static u32 AC(u32 a, u32 b, u32 c, u32 d, u32 dest = 0) { return d << 4 | c << 7 | b << 10 | a << 13 | 1 << 19 | dest << 22; }
  void genmode(int ntex, int nchan, int nstages) { bp(0x00, ntex | nchan << 4 | (nstages - 1) << 10); xf(0x103f, {(u32)ntex}); }
  void copy_disp(u32 addr, bool clear) {
    bp(0x49, 0); bp(0x4A, 639 | 479 << 10);
    bp(0x4D, 640 * 2 / 32);
    bp(0x4B, addr >> 5);
    bp(0x4E, 256);
    bp(0x52, 1 << 14 | (clear ? 1 << 11 : 0) | 3);
  }
  void copy_tex(int x, int y, int w, int h, u32 addr, int realfmt, bool clear, int stride, bool half = false) {
    bp(0x49, x | y << 10); bp(0x4A, (w - 1) | (h - 1) << 10);
    bp(0x4D, stride);
    bp(0x4B, addr >> 5);
    int field = ((realfmt & 7) << 1) | (realfmt >> 3);
    bp(0x52, (u32)field << 3 | (clear ? 1 << 11 : 0) | (realfmt < 4 ? 1 << 15 : 0) | (half ? 1 << 9 : 0));
  }
  void tex(int map, u32 addr, int w, int h, int fmt, u32 mode0 = 0x90, int tlut_off = 0, int tlut_fmt = 0) {
    int b = map < 4 ? 0x80 + map : 0xA0 + map - 4;
    bp(b, mode0); bp(b + 4, 0);
    bp(b + 8, (w - 1) | (h - 1) << 10 | fmt << 20);
    bp(b + 0x14, addr >> 5);
    bp(b + 0x18, tlut_off | tlut_fmt << 10);
  }
  void su(int tc, int w, int h) { bp(0x30 + 2 * tc, w - 1); bp(0x31 + 2 * tc, h - 1); }
  // VCD/VAT for: pos f32 xyz, [nrm f32], col0 rgba8, [tex0 f32 st]
  void vfmt(bool nrm, bool col, bool tex0) {
    cp(0x50, 1 << 9 | (nrm ? 1 << 11 : 0) | (col ? 1 << 13 : 0));
    cp(0x60, tex0 ? 1 : 0);
    cp(0x70, 1 | 4 << 1 | 4 << 10 | 1 << 13 | 5 << 14 | 1 << 21 | 4 << 22 | 1u << 30);
    cp(0x80, 0); cp(0x90, 0);
  }
  void begin(u8 prim, int n) { u8_(prim); u16_(n); }
  void v(float x, float y, float z) { f32_(x); f32_(y); f32_(-z); }  // eye looks down -z
  void c(u32 rgba) { u32_(rgba); }
  void t(float s, float tt) { f32_(s); f32_(tt); }
  void n3(float x, float y, float z) { f32_(x); f32_(y); f32_(z); }
};

static void colored(Stream &s) {
  s.init_common();
  s.genmode(0, 1, 1);
  s.bp(0x28, 7 | 7 << 3 | 0 << 7);  // no texture, color0
  s.tev(0, Stream::CC(15, 15, 15, 10), Stream::AC(7, 7, 7, 5));
  s.vfmt(false, true, false);
  // background clear by copy happens later; draw triangle + quad + strip
  s.begin(0x90, 3);  // triangles
  s.v(320, 40, 0.5f); s.c(0xFF0000FF);
  s.v(560, 400, 0.5f); s.c(0x00FF00FF);
  s.v(80, 400, 0.5f); s.c(0x0000FFFF);
  s.begin(0x80, 4);  // quad (front-ordering: clockwise on screen)
  s.v(20, 20, 0.2f); s.c(0xFFFFFFFF);
  s.v(120, 20, 0.2f); s.c(0xFFFF00FF);
  s.v(120, 120, 0.2f); s.c(0xFF00FFFF);
  s.v(20, 120, 0.2f); s.c(0x00FFFFFF);
  s.begin(0x98, 6);  // strip
  for (int i = 0; i < 6; i++) {
    s.v(400 + (i / 2) * 60.0f, 20 + (i & 1) * 60.0f, 0.3f);
    s.c(i & 1 ? 0xFF8000FF : 0x8000FFFF);
  }
  s.begin(0xA8, 2);  // line
  s.v(10, 460, 0); s.c(0xFFFFFFFF);
  s.v(630, 300, 0); s.c(0xFFFFFFFF);
  // culled quad (cull back, counter-clockwise => culled)
  s.bp(0x00, 0 | 1 << 4 | 1 << 14);
  s.begin(0x80, 4);
  s.v(500, 300, 0.1f); s.c(0xFF0000FF);
  s.v(500, 400, 0.1f); s.c(0xFF0000FF);
  s.v(600, 400, 0.1f); s.c(0xFF0000FF);
  s.v(600, 300, 0.1f); s.c(0xFF0000FF);
  s.copy_disp(0x00400000, true);
}

// textures of various formats
static void textures(Stream &s) {
  s.init_common();
  const int W = 32, H = 32;
  u32 base = 0x100000;
  // RGB565 checker gradient
  u32 a565 = base;
  for (int ty = 0; ty < H / 4; ty++)
    for (int tx = 0; tx < W / 4; tx++)
      for (int k = 0; k < 16; k++) {
        int x = tx * 4 + (k & 3), y = ty * 4 + (k >> 2);
        int r = x * 31 / (W - 1), g = ((x / 4 + y / 4) & 1) ? 63 : 0, b = y * 31 / (H - 1);
        s.w16(a565 + ((ty * (W / 4) + tx) * 16 + k) * 2, r << 11 | g << 5 | b);
      }
  // I8: diagonal gradient
  u32 ai8 = base + 0x1000;
  for (int ty = 0; ty < H / 4; ty++)
    for (int tx = 0; tx < W / 8; tx++)
      for (int k = 0; k < 32; k++) {
        int x = tx * 8 + (k & 7), y = ty * 4 + (k >> 3);
        s.ram[ai8 + (ty * (W / 8) + tx) * 32 + k] = (x + y) * 4;
      }
  // RGBA8: red/alpha ring
  u32 arg = base + 0x2000;
  for (int ty = 0; ty < H / 4; ty++)
    for (int tx = 0; tx < W / 4; tx++)
      for (int k = 0; k < 16; k++) {
        int x = tx * 4 + (k & 3), y = ty * 4 + (k >> 2);
        float d = sqrtf((x - 15.5f) * (x - 15.5f) + (y - 15.5f) * (y - 15.5f));
        u8 A = d < 14 ? 255 : 0, R = 255, G = (u8)(d * 16), B = 40;
        u32 t0 = arg + (ty * (W / 4) + tx) * 64;
        s.ram[t0 + 2 * k] = A; s.ram[t0 + 2 * k + 1] = R; s.ram[t0 + 32 + 2 * k] = G; s.ram[t0 + 32 + 2 * k + 1] = B;
      }
  // CMPR: each 4x4 block alternates two endpoint colors
  u32 acm = base + 0x4000;
  for (int i = 0; i < (W / 4) * (H / 4); i++) {
    u32 o = acm + i * 8;
    s.w16(o, 0xF800);   // red
    s.w16(o + 2, 0x001F);  // blue
    s.ram[o + 4] = 0x00; s.ram[o + 5] = 0x55; s.ram[o + 6] = 0xAA; s.ram[o + 7] = 0xFF;
  }
  // CI8 with RGB5A3 palette in TMEM: loaded from RAM
  u32 aci = base + 0x5000, apal = base + 0x6000;
  for (int ty = 0; ty < H / 4; ty++)
    for (int tx = 0; tx < W / 8; tx++)
      for (int k = 0; k < 32; k++) {
        int x = tx * 8 + (k & 7), y = ty * 4 + (k >> 3);
        s.ram[aci + (ty * (W / 8) + tx) * 32 + k] = (x / 4 + y / 4) & 7;
      }
  uint16_t pal[8] = {0xFC00, 0x83E0, 0x801F, 0xFFE0, 0x83FF, 0xFC1F, 0xFFFF, 0x8000};
  for (int i = 0; i < 256; i++) s.w16(apal + i * 2, pal[i & 7]);
  s.bp(0x64, apal >> 5);
  s.bp(0x65, ((0xC0000 - 0x80000) >> 9) | (256 / 16) << 10);

  s.genmode(1, 1, 1);
  s.xf(0x1040, {5 << 7});  // texgen0 from tex0, 2x4, matrix identity (row 60)
  s.bp(0x28, 0 | 0 << 3 | 1 << 6 | 0 << 7);
  s.tev(0, Stream::CC(15, 8, 10, 15), Stream::AC(7, 4, 5, 7));  // modulate
  s.bp(0x41, 0x18 | 1 | 4 << 8 | 5 << 5);                       // alpha blend on
  s.vfmt(false, true, true);
  struct T { u32 a; int fmt; int tl; } texs[5] = {{a565, 4, 0}, {ai8, 1, 0}, {arg, 6, 0}, {acm, 14, 0}, {aci, 9, 1}};
  for (int i = 0; i < 5; i++) {
    if (texs[i].tl) s.tex(0, texs[i].a, W, H, texs[i].fmt, 0x00, (0xC0000 - 0x80000) >> 9, 2);
    else s.tex(0, texs[i].a, W, H, texs[i].fmt, i == 1 ? 0x95 : 0x00);
    s.su(0, W, H);
    float x0 = 20 + i * 120.0f, y0 = 40, sz = 110;
    float rep = i == 1 ? 2.0f : 1.0f;
    s.begin(0x80, 4);
    s.v(x0, y0, 0.5f); s.c(0xFFFFFFFF); s.t(0, 0);
    s.v(x0 + sz, y0, 0.5f); s.c(0xFFFFFFFF); s.t(rep, 0);
    s.v(x0 + sz, y0 + sz, 0.5f); s.c(0xFFFFFFFF); s.t(rep, rep);
    s.v(x0, y0 + sz, 0.5f); s.c(0xFFFFFFFF); s.t(0, rep);
  }
  // render-to-texture: copy the first 128x128 of the EFB as RGB565 then draw it scaled below
  u32 cpy = 0x200000;
  s.copy_tex(0, 0, 256, 192, cpy, 4, false, 256 / 4);
  s.tex(0, cpy, 256, 192, 4, 0x90);
  s.su(0, 256, 192);
  s.begin(0x80, 4);
  s.v(20, 200, 0.5f); s.c(0xFFFFFFFF); s.t(0, 0);
  s.v(20 + 256, 200, 0.5f); s.c(0xFFFFFFFF); s.t(1, 0);
  s.v(20 + 256, 200 + 192, 0.5f); s.c(0xFFFFFFFF); s.t(1, 1);
  s.v(20, 200 + 192, 0.5f); s.c(0xFFFFFFFF); s.t(0, 1);
  // copy as I8 (intensity) half scale
  u32 cpy2 = 0x280000;
  s.copy_tex(0, 0, 256, 192, cpy2, 1, false, 128 / 8, true);
  s.tex(0, cpy2, 128, 96, 1, 0x90);
  s.su(0, 128, 96);
  s.begin(0x80, 4);
  s.v(320, 200, 0.5f); s.c(0xFFFFFFFF); s.t(0, 0);
  s.v(320 + 256, 200, 0.5f); s.c(0xFFFFFFFF); s.t(1, 0);
  s.v(320 + 256, 200 + 192, 0.5f); s.c(0xFFFFFFFF); s.t(1, 1);
  s.v(320, 200 + 192, 0.5f); s.c(0xFFFFFFFF); s.t(0, 1);
  s.copy_disp(0x00400000, true);
}

// perspective + depth + lighting + display list with indexed arrays
static void lit(Stream &s) {
  s.init_common();
  s.persp(60, 4.0f / 3.0f, 1.0f, 100.0f);
  // light 0: white, at (10, 10, 10) in view space, no attenuation
  u32 L = 0x600;
  s.xf(L + 3, {0xFFFFFFFF});
  s.xff(L + 4, {1, 0, 0, 1, 0, 0, 10, 10, 10, 0, 0, -1});
  s.xf(0x100a, {0x202020FF});  // ambient
  s.xf(0x100c, {0xFFFFFFFF});
  // chan0 color: mat from vertex, lighting on, light0, diffuse clamp, attn none(spec off -> dir)
  s.xf(0x100e, {1 | 1 << 1 | 1 << 2 | 0 << 6 | 2 << 7 | 2 << 9});
  s.xf(0x1010, {1});
  s.genmode(0, 1, 1);
  s.bp(0x28, 7 | 7 << 3);
  s.tev(0, Stream::CC(15, 15, 15, 10), Stream::AC(7, 7, 7, 5));
  // sphere geometry in RAM as indexed arrays: positions s16 with shift 8? use f32 for simplicity
  const int SL = 24, ST = 16;
  u32 apos = 0x100000, anrm = 0x110000, acol = 0x120000, adl = 0x130000;
  int nv = 0;
  for (int i = 0; i <= ST; i++)
    for (int j = 0; j <= SL; j++) {
      float th = 3.14159265f * i / ST, ph = 2 * 3.14159265f * j / SL;
      float x = sinf(th) * cosf(ph), y = cosf(th), z = sinf(th) * sinf(ph);
      s.wf(apos + nv * 12, x); s.wf(apos + nv * 12 + 4, y); s.wf(apos + nv * 12 + 8, z);
      // normals s16, frac 14
      s.w16(anrm + nv * 6, (uint16_t)(int16_t)(x * 16384 * 0.999f));
      s.w16(anrm + nv * 6 + 2, (uint16_t)(int16_t)(y * 16384 * 0.999f));
      s.w16(anrm + nv * 6 + 4, (uint16_t)(int16_t)(z * 16384 * 0.999f));
      nv++;
    }
  s.w32(acol, 0xE0A040FF);
  s.w32(acol + 4, 0x40A0E0FF);
  // display list: strips per row, 16-bit indices
  std::vector<u8> dl;
  auto d8 = [&](u8 v) { dl.push_back(v); };
  auto d16 = [&](uint16_t v) { dl.push_back(v >> 8); dl.push_back(v); };
  for (int i = 0; i < ST; i++) {
    d8(0x98 | 1);  // strip, vat 1
    d16((SL + 1) * 2);
    for (int j = 0; j <= SL; j++) {
      for (int k = 0; k < 2; k++) {
        uint16_t idx = (i + k) * (SL + 1) + j;
        d16(idx); d16(idx); d8((i / 4) & 1);
      }
    }
  }
  while (dl.size() % 32) dl.push_back(0);
  memcpy(&s.ram[adl], dl.data(), dl.size());
  // vat 1: pos f32 xyz idx16, nrm s16 idx16, col0 rgba8 idx8
  s.cp(0x50, 3 << 9 | 3 << 11 | 2 << 13);
  s.cp(0x60, 0);
  s.cp(0x71, 1 | 4 << 1 | 0 << 9 | 3 << 10 | 1 << 13 | 5 << 14 | 1u << 30);
  s.cp(0x81, 0); s.cp(0x91, 0);
  s.cp(0xA0, apos); s.cp(0xB0, 12);
  s.cp(0xA1, anrm); s.cp(0xB1, 6);
  s.cp(0xA2, acol); s.cp(0xB2, 4);
  s.bp(0x00, 0 | 1 << 4 | 0 << 10 | 1 << 14);  // cull back
  // two spheres at different depths, overlapping
  float m1[12] = {1.2f, 0, 0, -0.8f, 0, 1.2f, 0, 0.2f, 0, 0, 1.2f, -5.0f};
  float m2[12] = {1.5f, 0, 0, 0.9f, 0, 1.5f, 0, -0.3f, 0, 0, 1.5f, -6.0f};
  for (int k = 0; k < 2; k++) {
    float *m = k ? m2 : m1;
    s.load_posmtx(0, std::vector<float>(m, m + 12));
    // normal matrix = upper 3x3 (uniform scale ok)
    s.xff(0x400, {m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]});
    s.u8_(0x40); s.u32_(adl); s.u32_((u32)dl.size());
  }
  s.copy_disp(0x00400000, true);
}

static u32 fogf(float f) {
  u32 u; memcpy(&u, &f, 4);
  return ((u >> 12) & 0x7FF) | ((u >> 23) & 0xFF) << 11 | (u >> 31) << 19;
}

static void quad(Stream &s, float x, float y, float w, float h, float z, u32 cl, u32 cr) {
  s.begin(0x80, 4);
  s.v(x, y, z); s.c(cl); s.t(0, 0);
  s.v(x + w, y, z); s.c(cr); s.t(1, 0);
  s.v(x + w, y + h, z); s.c(cr); s.t(1, 1);
  s.v(x, y + h, z); s.c(cl); s.t(0, 1);
}

// TEV features: konst, multi-stage lerp, compare, alpha test, subtract, logic op, indirect, fog, dst alpha
static void tevtest(Stream &s) {
  s.init_common();
  s.vfmt(false, true, true);
  s.xf(0x1040, {5 << 7});
  // background
  s.genmode(1, 1, 1);
  s.bp(0x28, 7 | 7 << 3);
  s.tev(0, Stream::CC(15, 15, 15, 10), Stream::AC(7, 7, 7, 5));
  quad(s, 0, 0, 640, 480, 0.9f, 0x303030FF, 0x303030FF);
  // 1) two stages: konst then lerp to C0 by ras
  s.genmode(1, 1, 2);
  s.bp(0xE0, 255 | 0 << 12 | 1 << 23); s.bp(0xE1, 0 | 128 << 12 | 1 << 23);  // K0 = (255,128,0,0)
  s.bp(0xE2, 0 | 255 << 12); s.bp(0xE3, 255 | 0 << 12);                     // C0 = (0,0,255,255)
  s.bp(0xF6, (0 | 1 << 2) | 12 << 4 | 0 << 9);                              // stage0 kcsel K0
  s.bp(0x28, (7 | 7 << 3 | 0 << 7) | (7 | 7 << 3 | 0 << 7) << 12);
  s.tev(0, Stream::CC(15, 15, 15, 14), Stream::AC(7, 7, 7, 5));
  s.tev(1, Stream::CC(0, 2, 10, 15), Stream::AC(7, 7, 7, 0));
  quad(s, 20, 20, 180, 100, 0.5f, 0x000000FF, 0xFFFFFFFF);
  // 2) compare RGB8 GT: (ras > C1) ? 255 : 0 per channel
  s.genmode(1, 1, 1);
  s.bp(0xE4, 128 | 255 << 12); s.bp(0xE5, 128 | 128 << 12);  // C1 = 128 gray
  s.tev(0, 10 << 12 | 4 << 8 | 12 << 4 | 15 | 3 << 16 | 0 << 18 | 3 << 20 | 1 << 19, Stream::AC(7, 7, 7, 5));
  quad(s, 220, 20, 180, 100, 0.5f, 0x2060A0FF, 0xE0A060FF);
  // 3) alpha test: pass alpha > 128
  s.tev(0, Stream::CC(15, 15, 15, 10), Stream::AC(7, 7, 7, 5));
  s.bp(0xF3, 128 | 4 << 16 | 0 << 19 | 1 << 22);  // comp0 GREATER ref 128 OR never
  quad(s, 420, 20, 180, 100, 0.5f, 0x00FF0000, 0x00FF00FF);
  s.bp(0xF3, 7 << 16 | 7 << 19);
  // 4) subtract blend: white quad minus red -> cyan
  quad(s, 20, 140, 180, 100, 0.5f, 0xFFFFFFFF, 0xFFFFFFFF);
  s.bp(0x41, 0x18 | 1 << 11 | 1);
  s.bp(0x40, 0x0E);  // z always, no update
  quad(s, 60, 160, 100, 60, 0.4f, 0xFF0000FF, 0xFF0000FF);
  // 5) logic op invert over a gradient
  s.bp(0x41, 0x18);
  quad(s, 220, 140, 180, 100, 0.5f, 0xFF8000FF, 0x0080FFFF);
  s.bp(0x41, 0x18 | 2 | 10 << 12);
  quad(s, 260, 160, 100, 60, 0.4f, 0, 0);
  s.bp(0x41, 0x18);
  s.bp(0x40, 0x17);
  // 6) indirect warp: I8 sine map as offsets on an RGB565 checker
  {
    const int W = 32, H = 32;
    u32 achk = 0x100000, aind = 0x101000;
    for (int ty = 0; ty < H / 4; ty++)
      for (int tx = 0; tx < W / 4; tx++)
        for (int k = 0; k < 16; k++) {
          int x = tx * 4 + (k & 3), y = ty * 4 + (k >> 2);
          s.w16(achk + ((ty * (W / 4) + tx) * 16 + k) * 2, ((x / 4 + y / 4) & 1) ? 0xFFFF : 0x001F);
        }
    // IA8 indirect map: alpha(s offset) = sine, intensity(t offset) = 128
    for (int ty = 0; ty < H / 4; ty++)
      for (int tx = 0; tx < W / 4; tx++)
        for (int k = 0; k < 16; k++) {
          int y = ty * 4 + (k >> 2);
          u32 o = aind + ((ty * (W / 4) + tx) * 16 + k) * 2;
          s.ram[o] = (u8)(128 + 100 * sinf(y * 0.4f));
          s.ram[o + 1] = 128;
        }
    s.genmode(1, 1, 1);
    s.bp(0x00, 1 | 1 << 4 | 0 << 10 | 1 << 16);  // 1 ind stage
    s.tex(0, achk, W, H, 4, 0x05);
    s.tex(1, aind, W, H, 3, 0x05);
    s.su(0, W, H);
    s.bp(0x27, 1 | 0 << 3);   // ind stage 0: texmap1, texcoord0
    s.bp(0x25, 0);
    // ind matrix 0: [[0.5,0,0],[0,0.5,0]] (s.10 fixed) scale exp 17 -> 2^0
    s.bp(0x06, 512 | 0 << 11 | 1u << 22); s.bp(0x07, 0 | 512 << 11 | 0u << 22); s.bp(0x08, 0 | 0 << 11 | 1u << 22);
    s.bp(0x10, 0 | 0 << 2 | 3 << 4 | 1 << 9);  // bt 0, fmt8, bias ST, matrix 0
    s.bp(0x28, 0 | 0 << 3 | 1 << 6 | 0 << 7);
    s.tev(0, Stream::CC(15, 15, 15, 8), Stream::AC(7, 7, 7, 5));
    quad(s, 420, 140, 180, 100, 0.5f, 0xFFFFFFFF, 0xFFFFFFFF);
    s.bp(0x10, 0);
    s.bp(0x00, 1 | 1 << 4);
  }
  // 7) linear orthographic fog: fog = z (A=1, C=0), color = yellow; z gradient via 2 quads
  s.bp(0x28, 7 | 7 << 3);
  s.tev(0, Stream::CC(15, 15, 15, 10), Stream::AC(7, 7, 7, 5));
  s.bp(0xEE, fogf(1.0f)); s.bp(0xEF, 0x800000); s.bp(0xF0, 1);
  s.bp(0xF1, fogf(0.0f) | 1 << 20 | 2 << 21);
  s.bp(0xF2, 0xFFFF00);
  quad(s, 20, 260, 180, 100, 0.25f, 0x0000FFFF, 0x0000FFFF);
  quad(s, 220, 260, 180, 100, 0.75f, 0x0000FFFF, 0x0000FFFF);
  s.bp(0xF1, 0);
  // 8) RGBA6 + dst alpha: draw with constant dst alpha 0x40, then read back by blending with DSTALPHA
  s.bp(0x43, 0x41);
  s.bp(0x42, 0x40 | 1 << 8);
  quad(s, 420, 260, 180, 100, 0.5f, 0xFF0000FF, 0xFF0000FF);
  s.bp(0x42, 0);
  s.bp(0x41, 0x18 | 1 | 6 << 8 | 7 << 5);  // src*dstalpha + dst*(1-dstalpha)
  quad(s, 420, 260, 180, 100, 0.4f, 0x00FF00FF, 0x00FF00FF);
  s.bp(0x41, 0x18);
  s.bp(0x43, 0x40);
  s.copy_disp(0x00400000, true);
}

int main(int argc, char **argv) {
  std::string out = argc > 1 ? argv[1] : ".";
  { Stream s; colored(s); s.save(out + "/synth_colored.gxcap"); }
  { Stream s; textures(s); s.save(out + "/synth_textures.gxcap"); }
  { Stream s; lit(s); s.save(out + "/synth_lit.gxcap"); }
  { Stream s; tevtest(s); s.save(out + "/synth_tev.gxcap"); }
  printf("wrote synth_*.gxcap to %s\n", out.c_str());
  return 0;
}
