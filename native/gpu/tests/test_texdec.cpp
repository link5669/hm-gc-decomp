// Unit tests for texture decoding / encoding (no GL needed).
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "../gx_internal.h"

using namespace gx;
static int fails = 0;
#define CHECK(c, ...)                         \
  do {                                        \
    if (!(c)) {                               \
      printf("FAIL %s:%d: ", __FILE__, __LINE__); \
      printf(__VA_ARGS__);                    \
      printf("\n");                           \
      fails++;                                \
    }                                         \
  } while (0)

static void px(const std::vector<u8> &img, int w, int x, int y, u8 *o) { memcpy(o, &img[4 * (y * w + x)], 4); }

int main() {
  // RGB565: 4x4 tile, pixel (1,0) = pure green
  {
    u8 src[32] = {};
    src[2] = 0x07; src[3] = 0xE0;  // pixel 1
    src[30] = 0xF8; src[31] = 0x1F;  // pixel 15: magenta
    std::vector<u8> d(4 * 16);
    tex_decode(d.data(), src, 4, 4, TF_RGB565, nullptr, 0);
    u8 c[4];
    px(d, 4, 1, 0, c);
    CHECK(c[0] == 0 && c[1] == 255 && c[2] == 0 && c[3] == 255, "565 green %d %d %d %d", c[0], c[1], c[2], c[3]);
    px(d, 4, 3, 3, c);
    CHECK(c[0] == 255 && c[1] == 0 && c[2] == 255, "565 magenta");
  }
  // I4: 8x8 tile, first byte 0xF0 -> pixel0=255, pixel1=0
  {
    u8 src[32] = {0xF0, 0x8F};
    std::vector<u8> d(4 * 64);
    tex_decode(d.data(), src, 8, 8, TF_I4, nullptr, 0);
    CHECK(d[0] == 255 && d[4] == 0 && d[8] == 0x88 && d[12] == 255, "I4");
  }
  // RGBA8: AR then GB planes
  {
    u8 src[64] = {};
    src[0] = 0x80; src[1] = 0x11; src[32] = 0x22; src[33] = 0x33;
    std::vector<u8> d(4 * 16);
    tex_decode(d.data(), src, 4, 4, TF_RGBA8, nullptr, 0);
    CHECK(d[0] == 0x11 && d[1] == 0x22 && d[2] == 0x33 && d[3] == 0x80, "RGBA8");
  }
  // RGB5A3 both modes
  {
    u8 src[32] = {0xFC, 0x00, 0x3F, 0x00};  // opaque red; translucent (a=3) red=15
    std::vector<u8> d(4 * 16);
    tex_decode(d.data(), src, 4, 4, TF_RGB5A3, nullptr, 0);
    CHECK(d[0] == 255 && d[1] == 0 && d[3] == 255, "5A3 opaque");
    CHECK(d[4] == 255 && d[7] == ((3 << 5) | (3 << 2) | (3 >> 1)), "5A3 alpha %d", d[7]);
  }
  // IA8: A first
  {
    u8 src[32] = {0x40, 0xC0};
    std::vector<u8> d(4 * 16);
    tex_decode(d.data(), src, 4, 4, TF_IA8, nullptr, 0);
    CHECK(d[0] == 0xC0 && d[3] == 0x40, "IA8");
  }
  // CMPR: c0 > c1 -> 4 colors
  {
    u8 src[32] = {0xF8, 0x00, 0x00, 0x1F, 0x1B, 0, 0, 0};  // red, blue; row0 indices 0,1,2,3
    std::vector<u8> d(4 * 64);
    tex_decode(d.data(), src, 8, 8, TF_CMPR, nullptr, 0);
    CHECK(d[0] == 255 && d[2] == 0, "CMPR c0");
    CHECK(d[4] == 0 && d[6] == 255, "CMPR c1");
    CHECK(d[8] == (255 * 5 >> 3) && d[10] == (255 * 3 >> 3), "CMPR c2 %d %d", d[8], d[10]);
  }
  // CI8 with RGB565 TLUT
  {
    u8 src[32] = {0, 1};
    u8 tl[512] = {};
    tl[2] = 0xF8; tl[3] = 0x00;
    std::vector<u8> d(4 * 32);
    tex_decode(d.data(), src, 8, 4, TF_CI8, tl, 1);
    CHECK(d[0] == 0 && d[4] == 255 && d[5] == 0, "CI8");
  }
  // encode/decode round trip for all copy texture formats
  {
    const int W = 16, H = 8;
    std::vector<u8> rgba(W * H * 4);
    for (int i = 0; i < W * H * 4; i++) rgba[i] = (u8)(i * 37 + 11);
    int fmts[] = {TF_I4, TF_I8, TF_IA4, TF_IA8, TF_RGB565, TF_RGB5A3, TF_RGBA8};
    for (int f : fmts) {
      // canonicalize source to the decoded form of the format by encode->decode->encode->decode
      std::vector<u8> enc(tex_data_size(f, W, H)), dec(W * H * 4), enc2(enc.size()), dec2(dec.size());
      int tw = (f == TF_I4) ? 8 : (f == TF_I8 || f == TF_IA4) ? 8 : 4;
      int tb = (f == TF_RGBA8) ? 64 : 32;
      u32 stride = (W / tw) * tb;
      tex_encode(enc.data(), rgba.data(), W, H, f, stride, 0);
      tex_decode(dec.data(), enc.data(), W, H, f, nullptr, 0);
      tex_encode(enc2.data(), dec.data(), W, H, f, stride, 0);
      CHECK(enc == enc2, "encode roundtrip fmt %d", f);
      tex_decode(dec2.data(), enc2.data(), W, H, f, nullptr, 0);
      CHECK(dec == dec2, "decode roundtrip fmt %d", f);
    }
  }
  printf(fails ? "%d FAILURES\n" : "all texture tests passed\n", fails);
  return fails ? 1 : 0;
}

namespace gx {
u8 *g_ram;
u32 g_ram_size;
}
