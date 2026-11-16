// GPU-side .gxcap recorder (HM_GPU_CAPTURE=<file>, HM_GPU_CAPTURE_AT=<xfb copy #>, HM_GPU_CAPTURE_FRAMES=<n>).
// Writes a RAM snapshot, a synthetic register/TMEM preamble, then each FIFO chunk preceded by MEMW records of
// every RAM range the GPU read while processing it, so gxplay replays the frames exactly.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "gx_internal.h"

namespace gx {

bool g_cap_active = false;
static FILE *s_f;
static int s_at = -1, s_frames = 2, s_xfb = 0, s_left = 0;
static std::vector<std::pair<u32, u32>> s_ranges;
static std::vector<u8> s_chunk;
static bool s_start_pending = false, s_done = false;

static void rec(u32 tag, const void *a, u32 n, const void *b = nullptr, u32 m = 0) {
  u32 len = n + m;
  fwrite(&tag, 4, 1, s_f);
  fwrite(&len, 4, 1, s_f);
  fwrite(a, 1, n, s_f);
  if (m) fwrite(b, 1, m, s_f);
}

void cap_read(u32 addr, u32 len) {
  if (!g_cap_active || !len) return;
  addr &= 0x01FFFFFF;
  if (addr >= g_ram_size) return;
  if (addr + (u64)len > g_ram_size) len = g_ram_size - addr;
  s_ranges.push_back({addr, addr + len});
}

static void put8(std::vector<u8> &f, u8 v) { f.push_back(v); }
static void put32(std::vector<u8> &f, u32 v) { for (int i = 3; i >= 0; i--) f.push_back(v >> (8 * i)); }

static void start() {
  const char *path = getenv("HM_GPU_CAPTURE");
  s_f = fopen(path, "wb");
  if (!s_f) return;
  fwrite("GXCAP001", 1, 8, s_f);
  // RAM snapshot with TMEM (TLUT area) parked at the top of RAM
  std::vector<u8> ram(g_ram, g_ram + g_ram_size);
  u32 tpark = g_ram_size - sizeof(tmem);
  memcpy(ram.data() + tpark, tmem, sizeof(tmem));
  rec(0x534D4152, ram.data(), (u32)ram.size());
  // register preamble
  std::vector<u8> f;
  auto cpw = [&](u8 r, u32 v) { put8(f, 0x08); put8(f, r); put32(f, v); };
  auto bpw = [&](u8 r, u32 v) { put8(f, 0x61); put32(f, (u32)r << 24 | (v & 0xFFFFFF)); };
  cpw(0x30, cp.matidx_a); cpw(0x40, cp.matidx_b); cpw(0x50, cp.vcd_lo); cpw(0x60, cp.vcd_hi);
  for (int i = 0; i < 8; i++) { cpw(0x70 + i, cp.vat_a[i]); cpw(0x80 + i, cp.vat_b[i]); cpw(0x90 + i, cp.vat_c[i]); }
  for (int i = 0; i < 16; i++) { cpw(0xA0 + i, cp.array_base[i]); cpw(0xB0 + i, cp.array_stride[i]); }
  for (u32 a = 0; a < 0x1058; a += 16) {
    if (a >= 0x680 && a < 0x1000) continue;
    u32 n = std::min<u32>(16, 0x1058 - a);
    put8(f, 0x10); put32(f, (n - 1) << 16 | a);
    for (u32 i = 0; i < n; i++) put32(f, xf[a + i]);
  }
  // TLUT area: load from the parked copy, 0x3FF lines (32 B) at a time
  for (u32 off = 0; off < sizeof(tmem); off += 0x3FF * 32 / 512 * 512) {
    u32 lines = std::min<u32>(0x3FF * 32 / 512 * 512, sizeof(tmem) - off) / 32;
    bpw(0x64, (tpark + off) >> 5);
    bpw(0x65, (off >> 9) | lines << 10);
  }
  for (int r = 0; r < 256; r++) {
    if (r == 0x45 || r == 0x47 || r == 0x48 || r == 0x52 || r == 0x64 || r == 0x65 || r == 0x66 || r == 0x67 ||
        r == 0xFE || r == 0xFF || (r >= 0xE0 && r <= 0xE7))
      continue;
    bpw(r, bp[r]);
  }
  bpw(0x64, bp[0x64]);
  for (int i = 0; i < 4; i++) {
    bpw(0xE0 + 2 * i, tev_konst[i][0] | 0x800000); bpw(0xE1 + 2 * i, tev_konst[i][1] | 0x800000);
    bpw(0xE0 + 2 * i, tev_color[i][0] & 0x7FFFFF); bpw(0xE1 + 2 * i, tev_color[i][1] & 0x7FFFFF);
  }
  const std::vector<u8> &pend = fifo_pending();  // partial command carried over from the previous chunk
  f.insert(f.end(), pend.begin(), pend.end());
  rec(0x4F464946, f.data(), (u32)f.size());
  s_left = s_frames;
  g_cap_active = true;
  fprintf(stderr, "[gpu] capture started at xfb copy %d -> %s\n", s_xfb, path);
}

void cap_fifo_begin(const u8 *data, u32 len) {
  if (s_start_pending) {
    s_start_pending = false;
    start();
  }
  if (!g_cap_active) return;
  s_ranges.clear();
  s_chunk.assign(data, data + len);
}

void cap_fifo_end() {
  if (!g_cap_active || !s_f) return;
  std::sort(s_ranges.begin(), s_ranges.end());
  std::vector<std::pair<u32, u32>> m;
  for (auto &r : s_ranges) {
    if (!m.empty() && r.first <= m.back().second + 64) m.back().second = std::max(m.back().second, r.second);
    else m.push_back(r);
  }
  for (auto &r : m) rec(0x574D454D, &r.first, 4, g_ram + r.first, r.second - r.first);
  rec(0x4F464946, s_chunk.data(), (u32)s_chunk.size());
}

void cap_xfb() {
  static bool init = false;
  if (!init) {
    init = true;
    if (getenv("HM_GPU_CAPTURE")) {
      s_at = getenv("HM_GPU_CAPTURE_AT") ? atoi(getenv("HM_GPU_CAPTURE_AT")) : 600;
      if (getenv("HM_GPU_CAPTURE_FRAMES")) s_frames = atoi(getenv("HM_GPU_CAPTURE_FRAMES"));
    }
  }
  s_xfb++;
  if (g_cap_active) {
    u32 fr = s_xfb;
    rec(0x454D5246, &fr, 4);
    if (--s_left <= 0) {
      g_cap_active = false;
      fclose(s_f);
      s_f = nullptr;
      s_done = true;
      fprintf(stderr, "[gpu] capture done\n");
    }
  } else if (s_at >= 0 && s_xfb == s_at) {
    s_start_pending = true;
  } else if (s_f == nullptr && !s_done && (s_xfb % 15) == 0 && getenv("HM_GPU_CAPTURE_TRIGGER") &&
             access(getenv("HM_GPU_CAPTURE_TRIGGER"), F_OK) == 0) {  // start when this file appears
    s_start_pending = true;
  }
}

}  // namespace gx
