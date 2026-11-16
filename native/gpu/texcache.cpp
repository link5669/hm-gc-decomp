// Texture cache: guest textures -> GL textures (content hashed), EFB-copy textures.
#include <unordered_map>
#include <algorithm>
#include "glfuncs.h"
#include "gx_internal.h"

namespace gx {

// ---------------- cache ----------------
struct CacheEntry {
  unsigned tex = 0;
  u64 hash = 0, tlut_hash = 0;
  u32 epoch = ~0u;
  u32 bytes = 0;
  int levels = 1;
  u32 last_use = 0;
};
struct CopyEntry {
  unsigned tex = 0;
  int w = 0, h = 0, fmt = 0;
  u32 bytes = 0;
  u64 hash = 0;
  u32 epoch = ~0u;
  bool valid = false;
  bool pending = false;  // RAM write-back not done yet; hash = RAM content before the copy
  u32 serial = 0;
};
static std::unordered_map<u64, CacheEntry> s_cache;
static std::unordered_map<u32, CopyEntry> s_copies;
static u32 s_use_counter = 0;
static std::vector<u8> s_decbuf;

void texcache_init() {}

// Content hash for cache validation: full for small data, sampled (64 x 512 B + ends) for large.
static u64 data_hash(const u8 *p, u32 n) {
  if (n <= 65536) return hash64(p, n);
  u64 h = hash64(p, 512) ^ hash64(p + n - 512, 512, 1);
  u32 step = (n - 512) / 64;
  for (u32 i = 1; i < 64; i++) h = h * 31 + hash64(p + i * step, 512, i);
  return h;
}

void texcache_shutdown() {
  for (auto &e : s_cache) glDeleteTextures(1, &e.second.tex);
  for (auto &e : s_copies) glDeleteTextures(1, &e.second.tex);
  s_cache.clear();
  s_copies.clear();
}

void texcache_register_copy(u32 addr, unsigned gltex, int w, int h, int tex_fmt, u32 bytes, u32 serial) {
  addr &= 0x01FFFFFF;
  CopyEntry &e = s_copies[addr];
  if (e.tex && e.tex != gltex) glDeleteTextures(1, &e.tex);
  e.tex = gltex;
  e.w = w;
  e.h = h;
  e.fmt = tex_fmt;
  e.bytes = bytes;
  e.hash = ram_ok(addr, bytes) ? data_hash(ram_ptr(addr), bytes) : 0;
  e.epoch = g_epoch;
  e.valid = true;
  e.pending = true;
  e.serial = serial;
}

bool texcache_copy_pending(u32 addr, u32 serial) {
  auto it = s_copies.find(addr & 0x01FFFFFF);
  if (it == s_copies.end()) return false;
  CopyEntry &e = it->second;
  if (!e.valid || !e.pending || e.serial != serial) return false;
  u64 hh = ram_ok(addr, e.bytes) ? data_hash(ram_ptr(addr), e.bytes) : 0;
  if (hh != e.hash) {  // the CPU overwrote the destination meanwhile: the copy is stale
    e.valid = false;
    return false;
  }
  return true;
}

void texcache_copy_resolved(u32 addr) {
  auto it = s_copies.find(addr & 0x01FFFFFF);
  if (it == s_copies.end()) return;
  CopyEntry &e = it->second;
  e.pending = false;
  e.hash = ram_ok(addr, e.bytes) ? data_hash(ram_ptr(addr), e.bytes) : 0;
  e.epoch = g_epoch;
}


void texcache_gc() {
  if (s_cache.size() < 1500) return;
  for (auto it = s_cache.begin(); it != s_cache.end();) {
    if (s_use_counter - it->second.last_use > 20000) {
      glDeleteTextures(1, &it->second.tex);
      it = s_cache.erase(it);
    } else {
      ++it;
    }
  }
}

static int gl_wrap(u32 m) {
  switch (m & 3) {
    case 0: return GL_CLAMP_TO_EDGE;
    case 1: return GL_REPEAT;
    case 2: return GL_MIRRORED_REPEAT;
    default: return GL_REPEAT;
  }
}

BoundTex texcache_get(int n) {
  ProfScope ps(g_prof.texget);
  u32 base = n < 4 ? 0x80 + n : 0xA0 + (n - 4);
  u32 mode0 = bp[base], mode1 = bp[base + 4], img0 = bp[base + 8], img3 = bp[base + 0x14];
  u32 tlutr = bp[base + 0x18];
  BoundTex bt;
  int w = bits(img0, 0, 10) + 1, h = bits(img0, 10, 10) + 1, fmt = bits(img0, 20, 4);
  u32 addr = (img3 & 0xFFFFFF) << 5;
  bt.w = w;
  bt.h = h;
  bt.wrap_s = gl_wrap(bits(mode0, 0, 2));
  bt.wrap_t = gl_wrap(bits(mode0, 2, 2));
  bt.magf = bits(mode0, 4, 1) ? GL_LINEAR : GL_NEAREST;
  u32 mip = bits(mode0, 5, 2);
  bool minlin = bits(mode0, 7, 1);
  bt.bias = sbits(mode0, 9, 8) / 32.0f;
  bt.minlod = bits(mode1, 0, 8) / 16.0f;
  bt.maxlod = bits(mode1, 8, 8) / 16.0f;
  int maxlev = 1;
  {
    int m = std::max(w, h);
    while ((1 << (maxlev - 1)) < m) maxlev++;
  }
  int levels = 1;
  if (mip) levels = std::min(maxlev, (int)((bits(mode1, 8, 8) + 15) / 16) + 1);
  if (levels < 1) levels = 1;
  if (mip == 0) bt.minf = minlin ? GL_LINEAR : GL_NEAREST;
  else if (mip == 1) bt.minf = minlin ? GL_LINEAR_MIPMAP_NEAREST : GL_NEAREST_MIPMAP_NEAREST;
  else bt.minf = minlin ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR;

  u32 pa = addr & 0x01FFFFFF;
  // EFB copy at this address?
  auto ci = s_copies.find(pa);
  if (ci != s_copies.end()) cap_read(pa, ci->second.bytes);
  if (ci != s_copies.end() && ci->second.valid && ci->second.fmt == fmt && ci->second.w == w && ci->second.h == h) {
    CopyEntry &e = ci->second;
    if (e.epoch != g_epoch) {
      u64 hh = ram_ok(pa, e.bytes) ? data_hash(ram_ptr(pa), e.bytes) : 0;
      if (hh != e.hash) e.valid = false;
      else e.epoch = g_epoch;
    }
    if (e.valid) {
      bt.gltex = e.tex;
      bt.maxlod = 0;
      bt.minlod = 0;
      if (bt.minf != GL_NEAREST) bt.minf = GL_LINEAR;
      return bt;
    }
  }
  if (ci != s_copies.end() && ci->second.valid && ci->second.pending) copies_resolve_addr(pa);  // RAM decode needs it

  // total data size for all levels
  u32 total = 0;
  for (int l = 0; l < levels; l++) total += tex_data_size(fmt, std::max(1, w >> l), std::max(1, h >> l));
  bool ci_fmt = fmt == TF_CI4 || fmt == TF_CI8 || fmt == TF_CI14;
  u32 tlut_off = (tlutr & 0x3FF) << 9;
  int tlut_fmt = bits(tlutr, 10, 2);
  u32 tlut_bytes = fmt == TF_CI4 ? 32 : fmt == TF_CI8 ? 512 : 32768;
  if (tlut_off + tlut_bytes > sizeof(tmem)) tlut_off = 0;
  u64 key = ((u64)pa << 32) ^ ((u64)fmt << 24) ^ ((u64)w << 12) ^ (u64)h ^ ((u64)levels << 60) ^
            (ci_fmt ? ((u64)tlut_off << 20 ^ (u64)tlut_fmt << 58) : 0);
  CacheEntry &e = s_cache[key];
  e.last_use = ++s_use_counter;
  cap_read(pa, total);
  if (!ram_ok(pa, total)) {
    bt.gltex = 0;
    return bt;
  }
  bool need = !e.tex;
  if (e.epoch != g_epoch || need) {
    u64 hh = data_hash(ram_ptr(pa), total);
    u64 th = ci_fmt ? hash64(tmem + tlut_off, tlut_bytes, tlut_fmt) : 0;
    if (hh != e.hash || th != e.tlut_hash) need = true;
    e.hash = hh;
    e.tlut_hash = th;
    e.epoch = g_epoch;
  } else if (ci_fmt) {
    u64 th = hash64(tmem + tlut_off, tlut_bytes, tlut_fmt);
    if (th != e.tlut_hash) { need = true; e.tlut_hash = th; }
  }
  if (need) {
    g_prof.uploads++;
    if (!e.tex) glGenTextures(1, &e.tex);
    glActiveTexture(GL_TEXTURE0 + 9);
    glBindTexture(GL_TEXTURE_2D, e.tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    const u8 *src = ram_ptr(pa);
    for (int l = 0; l < levels; l++) {
      int lw = std::max(1, w >> l), lh = std::max(1, h >> l);
      s_decbuf.resize((size_t)lw * lh * 4);
      tex_decode(s_decbuf.data(), src, lw, lh, fmt, tmem + tlut_off, tlut_fmt);
      glTexImage2D(GL_TEXTURE_2D, l, GL_RGBA8, lw, lh, 0, GL_RGBA, GL_UNSIGNED_BYTE, s_decbuf.data());
      src += tex_data_size(fmt, lw, lh);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, levels - 1);
    e.levels = levels;
  }
  bt.gltex = e.tex;
  return bt;
}

}  // namespace gx
