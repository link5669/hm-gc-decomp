// GP command FIFO parser and vertex loader.
#include <cstdio>
#include <cstdarg>
#include "gx_internal.h"

namespace gx {

static std::vector<u8> s_pending;  // bytes of an incomplete command carried between writes
static int s_dl_depth = 0;

void logf(const char *fmt, ...) {
  static int count = 0;
  if (count > 2000) return;
  count++;
  va_list ap;
  va_start(ap, fmt);
  fprintf(stderr, "[gpu] ");
  vfprintf(stderr, fmt, ap);
  fputc('\n', stderr);
  va_end(ap);
}

void fifo_reset() {
  s_pending.clear();
  s_dl_depth = 0;
}

// ---------------- vertex format ----------------
struct AttrFmt {
  int type;   // 0 none 1 direct 2 idx8 3 idx16
  int cnt;    // element count flag
  int fmt;    // component format
  int shift;  // fractional bits
};

static int comp_size(int fmt) {
  static const int s[8] = {1, 1, 2, 2, 4, 0, 0, 0};
  return s[fmt & 7];
}
static int color_size(int fmt) {
  static const int s[8] = {2, 3, 4, 2, 3, 4, 0, 0};
  return s[fmt & 7];
}

struct VtxDesc {
  bool pnmtx;
  bool texmtx[8];
  AttrFmt pos, nrm, col[2], tex[8];
  bool nrm_idx3;
};

static void get_desc(int vat, VtxDesc &d) {
  u32 lo = cp.vcd_lo, hi = cp.vcd_hi;
  u32 a = cp.vat_a[vat], b = cp.vat_b[vat], c = cp.vat_c[vat];
  d.pnmtx = lo & 1;
  for (int i = 0; i < 8; i++) d.texmtx[i] = (lo >> (1 + i)) & 1;
  d.pos = {(int)bits(lo, 9, 2), (int)bits(a, 0, 1), (int)bits(a, 1, 3), (int)bits(a, 4, 5)};
  d.nrm = {(int)bits(lo, 11, 2), (int)bits(a, 9, 1), (int)bits(a, 10, 3), 0};
  d.col[0] = {(int)bits(lo, 13, 2), (int)bits(a, 13, 1), (int)bits(a, 14, 3), 0};
  d.col[1] = {(int)bits(lo, 15, 2), (int)bits(a, 17, 1), (int)bits(a, 18, 3), 0};
  d.nrm_idx3 = bits(a, 31, 1);
  int tcnt[8], tfmt[8], tsh[8];
  tcnt[0] = bits(a, 21, 1); tfmt[0] = bits(a, 22, 3); tsh[0] = bits(a, 25, 5);
  tcnt[1] = bits(b, 0, 1); tfmt[1] = bits(b, 1, 3); tsh[1] = bits(b, 4, 5);
  tcnt[2] = bits(b, 9, 1); tfmt[2] = bits(b, 10, 3); tsh[2] = bits(b, 13, 5);
  tcnt[3] = bits(b, 18, 1); tfmt[3] = bits(b, 19, 3); tsh[3] = bits(b, 22, 5);
  tcnt[4] = bits(b, 27, 1); tfmt[4] = bits(b, 28, 3); tsh[4] = bits(c, 0, 5);
  tcnt[5] = bits(c, 5, 1); tfmt[5] = bits(c, 6, 3); tsh[5] = bits(c, 9, 5);
  tcnt[6] = bits(c, 14, 1); tfmt[6] = bits(c, 15, 3); tsh[6] = bits(c, 18, 5);
  tcnt[7] = bits(c, 23, 1); tfmt[7] = bits(c, 24, 3); tsh[7] = bits(c, 27, 5);
  for (int i = 0; i < 8; i++) d.tex[i] = {(int)bits(hi, 2 * i, 2), tcnt[i], tfmt[i], tsh[i]};
}

static int idx_size(int type) { return type == 2 ? 1 : type == 3 ? 2 : 0; }

static u32 desc_size(const VtxDesc &d) {
  u32 s = 0;
  if (d.pnmtx) s++;
  for (int i = 0; i < 8; i++) s += d.texmtx[i];
  if (d.pos.type == 1) s += comp_size(d.pos.fmt) * (d.pos.cnt ? 3 : 2);
  else s += idx_size(d.pos.type);
  if (d.nrm.type == 1) s += comp_size(d.nrm.fmt) * 3 * (d.nrm.cnt ? 3 : 1);
  else if (d.nrm.type >= 2) s += idx_size(d.nrm.type) * ((d.nrm.cnt && d.nrm_idx3) ? 3 : 1);
  for (int i = 0; i < 2; i++) {
    if (d.col[i].type == 1) s += color_size(d.col[i].fmt);
    else s += idx_size(d.col[i].type);
  }
  for (int i = 0; i < 8; i++) {
    if (d.tex[i].type == 1) s += comp_size(d.tex[i].fmt) * (d.tex[i].cnt ? 2 : 1);
    else s += idx_size(d.tex[i].type);
  }
  return s;
}

u32 vertex_size(int vat) {
  VtxDesc d;
  get_desc(vat, d);
  return desc_size(d);
}

static inline float read_comp(const u8 *&p, int fmt, float scale) {
  switch (fmt) {
    case 0: return (float)(*p++) * scale;
    case 1: return (float)(int8_t)(*p++) * scale;
    case 2: { float v = (float)be16(p) * scale; p += 2; return v; }
    case 3: { float v = (float)(int16_t)be16(p) * scale; p += 2; return v; }
    default: { float v = bef(p); p += 4; return v; }
  }
}

static void read_color(const u8 *p, int fmt, u8 *o) {
  switch (fmt) {
    case 0: {  // RGB565
      u16 v = be16(p);
      u32 r = v >> 11, g = (v >> 5) & 63, b = v & 31;
      o[0] = (r << 3) | (r >> 2); o[1] = (g << 2) | (g >> 4); o[2] = (b << 3) | (b >> 2); o[3] = 255;
      break;
    }
    case 1: o[0] = p[0]; o[1] = p[1]; o[2] = p[2]; o[3] = 255; break;
    case 2: o[0] = p[0]; o[1] = p[1]; o[2] = p[2]; o[3] = 255; break;
    case 3: {  // RGBA4
      u16 v = be16(p);
      o[0] = (v >> 12) * 17; o[1] = ((v >> 8) & 15) * 17; o[2] = ((v >> 4) & 15) * 17; o[3] = (v & 15) * 17;
      break;
    }
    case 4: {  // RGBA6
      u32 v = (u32)p[0] << 16 | (u32)p[1] << 8 | p[2];
      u32 c[4] = {(v >> 18) & 63, (v >> 12) & 63, (v >> 6) & 63, v & 63};
      for (int i = 0; i < 4; i++) o[i] = (c[i] << 2) | (c[i] >> 4);
      break;
    }
    default: o[0] = p[0]; o[1] = p[1]; o[2] = p[2]; o[3] = p[3]; break;
  }
}

static const u8 *attr_ptr(const u8 *&p, int type, int arr, u32 sub = 0) {
  u32 idx;
  if (type == 2) idx = *p++;
  else { idx = be16(p); p += 2; }
  u32 addr = cp.array_base[arr] + idx * cp.array_stride[arr] + sub;
  static const u8 zeros[64] = {};
  if (!ram_ok(addr, 48)) return zeros;
  return ram_ptr(addr);
}

void decode_vertices(int vat, const u8 *src, u32 count, Vertex *out, VtxComponents &comp) {
  VtxDesc d;
  get_desc(vat, d);
  comp.has_nrm = d.nrm.type ? (d.nrm.cnt ? 2 : 1) : 0;
  comp.has_col = (d.col[0].type ? 1 : 0) | (d.col[1].type ? 2 : 0);
  comp.has_tc = 0;
  for (int i = 0; i < 8; i++)
    if (d.tex[i].type) comp.has_tc |= 1 << i;

  u32 ma = xf[XF_MATIDX_A], mb = xf[XF_MATIDX_B];
  u8 defidx[9] = {(u8)bits(ma, 0, 6),  (u8)bits(ma, 6, 6),  (u8)bits(ma, 12, 6),
                  (u8)bits(ma, 18, 6), (u8)bits(ma, 24, 6), (u8)bits(mb, 0, 6),
                  (u8)bits(mb, 6, 6),  (u8)bits(mb, 12, 6), (u8)bits(mb, 18, 6)};
  float pscale = 1.0f / (float)(1u << d.pos.shift);
  float nscale8 = 1.0f / 64.0f, nscale16 = 1.0f / 16384.0f;
  float nsc = 1.0f;
  switch (d.nrm.fmt) {
    case 0: nsc = 1.0f / 128.0f; break;
    case 1: nsc = nscale8; break;
    case 2: nsc = 1.0f / 32768.0f; break;
    case 3: nsc = nscale16; break;
    default: nsc = 1.0f;
  }
  float tscale[8];
  for (int i = 0; i < 8; i++) tscale[i] = 1.0f / (float)(1u << d.tex[i].shift);

  const u8 *p = src;
  for (u32 n = 0; n < count; n++) {
    Vertex &v = out[n];
    memset(&v, 0, sizeof(v));
    for (int i = 0; i < 9; i++) v.midx[i] = defidx[i];
    v.col[0][0] = v.col[0][1] = v.col[0][2] = v.col[0][3] = 255;
    v.col[1][0] = v.col[1][1] = v.col[1][2] = v.col[1][3] = 255;
    if (d.pnmtx) v.midx[0] = *p++ & 63;
    for (int i = 0; i < 8; i++)
      if (d.texmtx[i]) v.midx[1 + i] = *p++ & 63;
    // position
    if (d.pos.type) {
      const u8 *q = d.pos.type == 1 ? p : attr_ptr(p, d.pos.type, 0);
      const u8 *q0 = q;
      v.pos[0] = read_comp(q, d.pos.fmt, pscale);
      v.pos[1] = read_comp(q, d.pos.fmt, pscale);
      v.pos[2] = d.pos.cnt ? read_comp(q, d.pos.fmt, pscale) : 0.0f;
      if (d.pos.type == 1) p += (q - q0);
    }
    // normal / NBT
    if (d.nrm.type) {
      int nv = d.nrm.cnt ? 3 : 1;
      float *dst[3] = {v.nrm, v.bin, v.tan};
      if (d.nrm.type == 1) {
        for (int k = 0; k < nv; k++)
          for (int j = 0; j < 3; j++) dst[k][j] = read_comp(p, d.nrm.fmt, nsc);
      } else if (d.nrm.cnt && d.nrm_idx3) {
        int cs = comp_size(d.nrm.fmt);
        for (int k = 0; k < 3; k++) {
          const u8 *q = attr_ptr(p, d.nrm.type, 1, k * 3 * cs);
          for (int j = 0; j < 3; j++) dst[k][j] = read_comp(q, d.nrm.fmt, nsc);
        }
      } else {
        const u8 *q = attr_ptr(p, d.nrm.type, 1);
        for (int k = 0; k < nv; k++)
          for (int j = 0; j < 3; j++) dst[k][j] = read_comp(q, d.nrm.fmt, nsc);
      }
    }
    // colors
    for (int c = 0; c < 2; c++) {
      if (!d.col[c].type) continue;
      if (d.col[c].type == 1) {
        read_color(p, d.col[c].fmt, v.col[c]);
        p += color_size(d.col[c].fmt);
      } else {
        read_color(attr_ptr(p, d.col[c].type, 2 + c), d.col[c].fmt, v.col[c]);
      }
    }
    // texcoords
    for (int t = 0; t < 8; t++) {
      if (!d.tex[t].type) continue;
      const u8 *q = d.tex[t].type == 1 ? p : attr_ptr(p, d.tex[t].type, 4 + t);
      const u8 *q0 = q;
      v.tc[t][0] = read_comp(q, d.tex[t].fmt, tscale[t]);
      v.tc[t][1] = d.tex[t].cnt ? read_comp(q, d.tex[t].fmt, tscale[t]) : 0.0f;
      if (d.tex[t].type == 1) p += (q - q0);
    }
  }
}

// ---------------- command parser ----------------
static void load_indexed(int which, u32 v) {
  u32 idx = v >> 16;
  u32 size = ((v >> 12) & 15) + 1;
  u32 addr = v & 0xFFF;
  int arr = 12 + which;
  u32 src = cp.array_base[arr] + idx * cp.array_stride[arr];
  if (!ram_ok(src, size * 4)) return;
  const u8 *p = ram_ptr(src);
  for (u32 i = 0; i < size; i++) xf_write(addr + i, be32(p + 4 * i));
}

static void run_dl(u32 addr, u32 size);

// Parses commands from p[0..n). Returns the number of bytes consumed (complete commands only).
static size_t run(const u8 *p, size_t n) {
  size_t i = 0;
  while (i < n) {
    u8 op = p[i];
    size_t rem = n - i;
    const u8 *c = p + i;
    if (op == 0x00) { i++; continue; }
    if (op == 0x08) {
      if (rem < 6) break;
      cp_write(c[1], be32(c + 2));
      i += 6;
      continue;
    }
    if (op == 0x10) {
      if (rem < 5) break;
      u32 hdr = be32(c + 1);
      u32 cnt = (hdr >> 16) + 1;
      u32 addr = hdr & 0xFFFF;
      if (rem < 5 + 4 * (size_t)cnt) break;
      for (u32 k = 0; k < cnt; k++) xf_write(addr + k, be32(c + 5 + 4 * k));
      i += 5 + 4 * cnt;
      continue;
    }
    if (op == 0x20 || op == 0x28 || op == 0x30 || op == 0x38) {
      if (rem < 5) break;
      load_indexed((op - 0x20) >> 3, be32(c + 1));
      i += 5;
      continue;
    }
    if (op == 0x40) {
      if (rem < 9) break;
      run_dl(be32(c + 1), be32(c + 5));
      i += 9;
      continue;
    }
    if (op == 0x48 || op == 0x44) { i++; continue; }
    if (op == 0x61) {
      if (rem < 5) break;
      u32 v = be32(c + 1);
      bp_write(v >> 24, v & 0xFFFFFF);
      i += 5;
      continue;
    }
    if (op >= 0x80 && op < 0xC0) {
      if (rem < 3) break;
      int vat = op & 7;
      int prim = (op >> 3) & 7;
      u32 cnt = be16(c + 1);
      u32 vs = vertex_size(vat);
      size_t need = 3 + (size_t)cnt * vs;
      if (rem < need) break;
      if (cnt) {
        static std::vector<Vertex> verts;
        if (verts.size() < cnt) verts.resize(cnt);
        VtxComponents comp;
        decode_vertices(vat, c + 3, cnt, verts.data(), comp);
        add_primitive(prim, verts.data(), cnt, comp);
      }
      i += need;
      continue;
    }
    static int unk = 0;
    if (unk++ < 20) logf("unknown fifo opcode %02x", op);
    i++;
  }
  return i;
}

static void run_dl(u32 addr, u32 size) {
  if (s_dl_depth > 8) return;
  if (!ram_ok(addr, size)) {
    logf("CALL_DL out of range %08x %x", addr, size);
    return;
  }
  // copy: the display list may be modified by a nested copy (EFB copy writes RAM)
  std::vector<u8> buf(ram_ptr(addr), ram_ptr(addr) + size);
  s_dl_depth++;
  run(buf.data(), buf.size());
  s_dl_depth--;
}

void fifo_feed(const u8 *data, u32 len) {
  if (s_pending.empty()) {
    size_t used = run(data, len);
    if (used < len) s_pending.assign(data + used, data + len);
    return;
  }
  s_pending.insert(s_pending.end(), data, data + len);
  size_t used = run(s_pending.data(), s_pending.size());
  s_pending.erase(s_pending.begin(), s_pending.begin() + used);
}

}  // namespace gx
