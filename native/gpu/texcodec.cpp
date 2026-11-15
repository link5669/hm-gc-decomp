// Texture decoding (GX tiled formats -> RGBA8), EFB-copy encoding, hashing.
#include <algorithm>
#include "gx_internal.h"

namespace gx {

// ---------------- hashing ----------------
u64 hash64(const u8 *p, size_t n, u64 seed) {
  u64 h = 0x9E3779B97F4A7C15ull ^ (seed * 0xFF51AFD7ED558CCDull) ^ n;
  size_t i = 0;
  for (; i + 8 <= n; i += 8) {
    u64 v;
    memcpy(&v, p + i, 8);
    h ^= v * 0xC2B2AE3D27D4EB4Full;
    h = (h << 31 | h >> 33) * 0x9E3779B97F4A7C15ull;
  }
  for (; i < n; i++) h = (h ^ p[i]) * 0x100000001B3ull;
  h ^= h >> 29;
  h *= 0xBF58476D1CE4E5B9ull;
  h ^= h >> 32;
  return h;
}

// ---------------- format info ----------------
static void tile_dims(int fmt, int &tw, int &th, int &bpp) {
  switch (fmt) {
    case TF_I4: case TF_CI4: case TF_CMPR: tw = 8; th = 8; bpp = 4; break;
    case TF_I8: case TF_IA4: case TF_CI8: tw = 8; th = 4; bpp = 8; break;
    case TF_RGBA8: tw = 4; th = 4; bpp = 32; break;
    default: tw = 4; th = 4; bpp = 16; break;
  }
}

u32 tex_data_size(int fmt, int w, int h) {
  int tw, th, bpp;
  tile_dims(fmt, tw, th, bpp);
  u32 bw = (w + tw - 1) / tw, bh = (h + th - 1) / th;
  return bw * bh * (tw * th * bpp / 8);
}

static inline u32 c5(u32 v) { return (v << 3) | (v >> 2); }
static inline u32 c6(u32 v) { return (v << 2) | (v >> 4); }
static inline u32 c4(u32 v) { return v * 17; }
static inline u32 c3(u32 v) { return (v << 5) | (v << 2) | (v >> 1); }

static inline void put(u8 *d, u32 r, u32 g, u32 b, u32 a) { d[0] = r; d[1] = g; d[2] = b; d[3] = a; }

static inline void dec565(u8 *d, u16 v) { put(d, c5(v >> 11), c6((v >> 5) & 63), c5(v & 31), 255); }
static inline void dec5a3(u8 *d, u16 v) {
  if (v & 0x8000) put(d, c5((v >> 10) & 31), c5((v >> 5) & 31), c5(v & 31), 255);
  else put(d, c4((v >> 8) & 15), c4((v >> 4) & 15), c4(v & 15), c3((v >> 12) & 7));
}
static inline void decIA8(u8 *d, u16 v) {  // high byte A, low byte I
  u32 a = v >> 8, i = v & 255;
  put(d, i, i, i, a);
}
static inline void dec_tlut(u8 *d, const u8 *tlut, u32 idx, int tf) {
  u16 v = be16(tlut + 2 * idx);
  if (tf == 0) decIA8(d, v);
  else if (tf == 1) dec565(d, v);
  else dec5a3(d, v);
}

void tex_decode(u8 *dst, const u8 *src, int w, int h, int fmt, const u8 *tlut, int tf) {
  int tw, th, bpp;
  tile_dims(fmt, tw, th, bpp);
  int bw = (w + tw - 1) / tw, bh = (h + th - 1) / th;
  const u8 *s = src;
  for (int by = 0; by < bh; by++)
    for (int bx = 0; bx < bw; bx++) {
      if (fmt == TF_CMPR) {
        for (int sub = 0; sub < 4; sub++) {
          int ox = bx * 8 + (sub & 1) * 4, oy = by * 8 + (sub >> 1) * 4;
          u16 c0 = be16(s), c1 = be16(s + 2);
          u8 pal[4][4];
          dec565(pal[0], c0);
          dec565(pal[1], c1);
          if (c0 > c1) {
            for (int k = 0; k < 3; k++) {
              pal[2][k] = (pal[1][k] * 3 + pal[0][k] * 5) >> 3;
              pal[3][k] = (pal[0][k] * 3 + pal[1][k] * 5) >> 3;
            }
            pal[2][3] = pal[3][3] = 255;
          } else {
            for (int k = 0; k < 3; k++) pal[2][k] = pal[3][k] = (pal[0][k] + pal[1][k]) / 2;
            pal[2][3] = 255;
            pal[3][3] = 0;
          }
          for (int y = 0; y < 4; y++) {
            u8 line = s[4 + y];
            for (int x = 0; x < 4; x++) {
              int px = ox + x, py = oy + y;
              if (px < w && py < h) memcpy(dst + 4 * (py * w + px), pal[(line >> (6 - 2 * x)) & 3], 4);
            }
          }
          s += 8;
        }
        continue;
      }
      if (fmt == TF_RGBA8) {
        for (int y = 0; y < 4; y++)
          for (int x = 0; x < 4; x++) {
            int px = bx * 4 + x, py = by * 4 + y;
            int k = y * 4 + x;
            if (px < w && py < h) put(dst + 4 * (py * w + px), s[2 * k + 1], s[32 + 2 * k], s[32 + 2 * k + 1], s[2 * k]);
          }
        s += 64;
        continue;
      }
      for (int y = 0; y < th; y++)
        for (int x = 0; x < tw; x++) {
          int px = bx * tw + x, py = by * th + y;
          int k = y * tw + x;
          u8 tmp[4];
          u8 *d = (px < w && py < h) ? dst + 4 * (py * w + px) : tmp;
          switch (fmt) {
            case TF_I4: { u32 v = (s[k >> 1] >> ((k & 1) ? 0 : 4)) & 15; v = c4(v); put(d, v, v, v, v); break; }
            case TF_I8: { u32 v = s[k]; put(d, v, v, v, v); break; }
            case TF_IA4: { u32 v = s[k]; u32 i = c4(v & 15), a = c4(v >> 4); put(d, i, i, i, a); break; }
            case TF_IA8: decIA8(d, be16(s + 2 * k)); break;
            case TF_RGB565: dec565(d, be16(s + 2 * k)); break;
            case TF_RGB5A3: dec5a3(d, be16(s + 2 * k)); break;
            case TF_CI4: dec_tlut(d, tlut, (s[k >> 1] >> ((k & 1) ? 0 : 4)) & 15, tf); break;
            case TF_CI8: dec_tlut(d, tlut, s[k], tf); break;
            case TF_CI14: dec_tlut(d, tlut, be16(s + 2 * k) & 0x3FFF, tf); break;
            default: put(d, 255, 0, 255, 255); break;
          }
        }
      s += tw * th * bpp / 8;
    }
}

void tex_encode(u8 *dst, const u8 *rgba, int w, int h, int fmt, u32 stride, int copy_fmt) {
  (void)copy_fmt;
  int tw, th, bpp;
  tile_dims(fmt, tw, th, bpp);
  int bw = (w + tw - 1) / tw, bh = (h + th - 1) / th;
  u32 tbytes = tw * th * bpp / 8;
  for (int by = 0; by < bh; by++)
    for (int bx = 0; bx < bw; bx++) {
      u8 *t = dst + by * stride + bx * tbytes;
      if (fmt == TF_RGBA8) {
        for (int k = 0; k < 16; k++) {
          int px = std::min(bx * 4 + (k & 3), w - 1), py = std::min(by * 4 + (k >> 2), h - 1);
          const u8 *c = rgba + 4 * (py * w + px);
          t[2 * k] = c[3]; t[2 * k + 1] = c[0]; t[32 + 2 * k] = c[1]; t[32 + 2 * k + 1] = c[2];
        }
        continue;
      }
      if (bpp == 4) memset(t, 0, tbytes);
      for (int k = 0; k < tw * th; k++) {
        int px = std::min(bx * tw + (k % tw), w - 1), py = std::min(by * th + (k / tw), h - 1);
        const u8 *c = rgba + 4 * (py * w + px);
        switch (fmt) {
          case TF_I4: t[k >> 1] |= (c[0] >> 4) << ((k & 1) ? 0 : 4); break;
          case TF_I8: t[k] = c[0]; break;
          case TF_IA4: t[k] = (c[3] & 0xF0) | (c[0] >> 4); break;
          case TF_IA8: t[2 * k] = c[3]; t[2 * k + 1] = c[0]; break;
          case TF_RGB565: {
            u16 v = (c[0] >> 3) << 11 | (c[1] >> 2) << 5 | (c[2] >> 3);
            t[2 * k] = v >> 8; t[2 * k + 1] = v & 255;
            break;
          }
          case TF_RGB5A3: {
            u16 v;
            if (c[3] >= 0xE0) v = 0x8000 | (c[0] >> 3) << 10 | (c[1] >> 3) << 5 | (c[2] >> 3);
            else v = (c[3] >> 5) << 12 | (c[0] >> 4) << 8 | (c[1] >> 4) << 4 | (c[2] >> 4);
            t[2 * k] = v >> 8; t[2 * k + 1] = v & 255;
            break;
          }
          default: break;
        }
      }
    }
}

}  // namespace gx
