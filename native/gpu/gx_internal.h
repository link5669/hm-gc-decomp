// Internal shared state of the GX processor.
#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include "gpu.h"

namespace gx {

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int32_t s32;
typedef uint64_t u64;

// ---- guest memory ----
extern u8 *g_ram;
extern u32 g_ram_size;
inline u8 *ram_ptr(u32 addr) { return g_ram + (addr & 0x01FFFFFF); }
inline bool ram_ok(u32 addr, u32 len) {
  u32 a = addr & 0x01FFFFFF;
  return a + (u64)len <= g_ram_size;
}
inline u32 be32(const u8 *p) { return (u32)p[0] << 24 | (u32)p[1] << 16 | (u32)p[2] << 8 | p[3]; }
inline u16 be16(const u8 *p) { return (u16)(p[0] << 8 | p[1]); }
inline float bef(const u8 *p) { u32 v = be32(p); float f; memcpy(&f, &v, 4); return f; }
inline float u2f(u32 v) { float f; memcpy(&f, &v, 4); return f; }
inline u32 bits(u32 v, int lo, int n) { return (v >> lo) & ((1u << n) - 1); }
inline s32 sbits(u32 v, int lo, int n) { return (s32)(v << (32 - lo - n)) >> (32 - n); }

// ---- register files ----
struct CPRegs {
  u32 matidx_a = 0, matidx_b = 0;
  u32 vcd_lo = 0, vcd_hi = 0;
  u32 vat_a[8] = {}, vat_b[8] = {}, vat_c[8] = {};
  u32 array_base[16] = {}, array_stride[16] = {};
};
extern CPRegs cp;
extern u32 xf[0x1058];  // XF memory + registers (raw words; floats are bit patterns)
extern u32 bp[256];
extern u8 tmem[0x80000];
extern u32 tev_color[4][2], tev_konst[4][2];  // TLUT area of TMEM, indexed by (offset << 9)

// XF register addresses
enum {
  XF_NUMCOLORS = 0x1009, XF_AMB0 = 0x100a, XF_MAT0 = 0x100c, XF_CHAN0_COLOR = 0x100e,
  XF_CHAN0_ALPHA = 0x1010, XF_DUALTEX = 0x1012, XF_MATIDX_A = 0x1018, XF_MATIDX_B = 0x1019,
  XF_VIEWPORT = 0x101a, XF_PROJ = 0x1020, XF_NUMTEXGENS = 0x103f, XF_TEXMTXINFO = 0x1040,
  XF_POSTMTXINFO = 0x1050,
};

// ---- decoded vertex (fed to the GL vertex shader) ----
struct Vertex {
  float pos[3];
  float nrm[3];
  float bin[3];
  float tan[3];
  float tc[8][2];
  u8 col[2][4];
  u8 midx[12];  // [0]=pos/normal matrix row, [1..8]=tex matrix rows
};
static_assert(sizeof(Vertex) == 132, "vertex layout");

enum PrimClass { PC_TRI = 0, PC_LINE = 1, PC_POINT = 2 };

// vertex component presence for the current batch (affects the vertex shader)
struct VtxComponents {
  u8 has_nrm;   // 0 none, 1 N, 2 NBT
  u8 has_col;   // bit0 col0, bit1 col1
  u8 has_tc;    // bit n
};

// ---- fifo / vertex loader ----
void fifo_reset();
const std::vector<u8> &fifo_pending();
void fifo_feed(const u8 *data, u32 len);
u32 vertex_size(int vat);
// Decodes `count` vertices from src (vat format) into out. Returns false on bad format.
// Returns the number of vertices written: vertices whose position index is all ones (0xFF / 0xFFFF) are
// skipped (removed from the stream), as on hardware.
u32 decode_vertices(int vat, const u8 *src, u32 count, Vertex *out, VtxComponents &comp);

// ---- register writes ----
void cp_write(u8 reg, u32 val);
void xf_write(u32 addr, u32 val);
void bp_write(u8 reg, u32 val);

// ---- render ----
bool render_init(int scale);
void render_shutdown();
void flush_batch();
void add_primitive(int prim, const Vertex *v, u32 count, const VtxComponents &comp);
void efb_copy(u32 trigger);
void present(int w, int h);
void set_aspect(float a);
void present_ram_xfb(u32 addr, int w, int h, int stride, int ww, int wh);
u32 efb_peek(int x, int y, int is_z);
void efb_poke(int x, int y, int is_z, u32 v);
bool read_xfb(std::vector<u8> &rgba, int &w, int &h);
extern int g_scale;
extern u32 g_epoch;  // increments when guest RAM may have changed

// ---- textures ----
// decoded texture formats
enum TexFmt { TF_I4 = 0, TF_I8 = 1, TF_IA4 = 2, TF_IA8 = 3, TF_RGB565 = 4, TF_RGB5A3 = 5, TF_RGBA8 = 6,
              TF_CI4 = 8, TF_CI8 = 9, TF_CI14 = 10, TF_CMPR = 14 };
u32 tex_data_size(int fmt, int w, int h);
// Decodes one mip level to RGBA8 (row-major, top row first). tlut: TLUT entries (big-endian u16).
void tex_decode(u8 *dst, const u8 *src, int w, int h, int fmt, const u8 *tlut, int tlut_fmt);
// Encodes RGBA8 pixels (already converted to the copy format's decoded form) into the tiled
// texture layout of `tex_fmt` (decoded texture format equivalent). stride_bytes: bytes per row of tiles.
void tex_encode(u8 *dst, const u8 *rgba, int w, int h, int tex_fmt, u32 stride_bytes, int copy_fmt);
u64 hash64(const u8 *p, size_t n, u64 seed = 0);

struct BoundTex {
  unsigned gltex = 0;
  int w = 1, h = 1;          // guest texel dimensions (for coordinate normalization)
  int wrap_s = 0, wrap_t = 0, minf = 0, magf = 0;  // GL enums
  float bias = 0, minlod = 0, maxlod = 0;
};
void texcache_init();
void texcache_shutdown();
// Resolves texmap n from the current BP state into a GL texture.
BoundTex texcache_get(int n);
// EFB copy textures. The GL texture is the source of truth; the RAM image is written back asynchronously
// (pending until copies_resolve). While pending, the entry stays valid as long as the RAM there is unchanged.
void texcache_register_copy(u32 addr, unsigned gltex, int w, int h, int tex_fmt, u32 bytes, u32 serial);
bool texcache_copy_pending(u32 addr, u32 serial);  // still current and RAM untouched by the CPU?
void texcache_copy_resolved(u32 addr);              // RAM image written; rehash
void copies_resolve(bool wait_all);                 // render.cpp: finish async write-backs
void copies_resolve_addr(u32 addr);
void tlut_load();
void texcache_gc();

// ---- shaders ----
struct ShaderKey {
  std::string bytes;
};
struct Program {
  unsigned prog = 0;
  int u_posmem, u_nrmmem, u_postmem, u_lcol, u_lcos, u_ldist, u_lpos, u_ldir, u_matamb;
  int u_proj, u_vpscale, u_vpoff, u_ptsize;
  int u_colors, u_kcolors, u_alpharef, u_texdim, u_tcscale, u_indmtx, u_indscale, u_fogcol, u_fogf, u_fogi,
      u_dstalpha;
  std::vector<std::vector<u8>> ucache;  // last uploaded uniform values, indexed by location
};
void shader_key(std::string &key, const VtxComponents &comp, int prim);
Program *shader_get(const std::string &key);
void shader_shutdown();
unsigned compile_program(const char *vs, const char *fs, bool dual_source);

void logf(const char *fmt, ...);

// Dual-source output (separate blend alpha) is only needed when destination alpha replaces the written
// alpha while blending uses the source alpha. Intel GPUs run dual-source shaders at half rate (SIMD8).
inline bool need_dual_source() {
  u32 bm = bp[0x41];
  if (!((bp[0x42] >> 8) & 1) || !(bm & 1) || ((bm >> 11) & 1)) return false;
  u32 s = bits(bm, 8, 3), d = bits(bm, 5, 3);
  return s == 4 || s == 5 || d == 4 || d == 5;
}

// ---- profiling (HM_GPU_PROF=1) ----
struct Prof {
  double fifo, flush, texget, readback, copy, present;
  u32 draws, copies, xfbs, uploads, compiles;
  double gpu[4];  // GPU ms: frame draws+tex copies, xfb copy, present, (unused)
};
void gpu_timer(int slot);  // switch the running GPU timer query to slot (-1 = stop)
extern Prof g_prof;
extern bool g_prof_on;
double now_ms();
struct ProfScope {
  double *acc, t0;
  explicit ProfScope(double &a) : acc(g_prof_on ? &a : nullptr), t0(g_prof_on ? now_ms() : 0) {}
  ~ProfScope() { if (acc) *acc += now_ms() - t0; }
};
void prof_frame();
void request_scale(int s);
extern float g_frame_gpu_ms;
extern int g_scale;

// ---- capture (capture.cpp) ----
extern bool g_cap_active;
void cap_read(u32 addr, u32 len);
void cap_fifo_begin(const u8 *data, u32 len);
void cap_fifo_end();
void cap_xfb();

}  // namespace gx
