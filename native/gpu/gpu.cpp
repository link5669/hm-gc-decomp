// C ABI entry points (gpu.h).
#include <SDL.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include "glfuncs.h"
#include "gx_internal.h"
#include "gputhread.h"

#define HMGL_DEF(type, name) type hgl_##name;
HMGL_FUNCS(HMGL_DEF)
#undef HMGL_DEF

bool hmgl_load(void *(*getproc)(const char *)) {
  bool ok = true;
#define HMGL_LOAD(type, name)                                     \
  hgl_##name = (type)getproc("gl" #name);                         \
  if (!hgl_##name) {                                              \
    gx::logf("missing GL function gl%s", #name);                  \
    ok = false;                                                   \
  }
  HMGL_FUNCS(HMGL_LOAD)
#undef HMGL_LOAD
  return ok;
}

static int s_req_scale = 1;
static bool s_inited = false;

namespace gx {
void fifo_write_impl(const u8 *data, u32 len) {
  ProfScope ps(g_prof.fifo);
  g_epoch++;  // guest RAM may have changed since the last call
  cap_fifo_begin(data, len);
  fifo_feed(data, len);
  cap_fifo_end();
}
}  // namespace gx

extern "C" {

// Starts the GPU thread (unless HM_GPU_THREAD=0). on_start runs first on that thread (make the GL
// context current there). Returns 1 if threaded. Call before gpu_init.
int gpu_thread_start(void (*on_start)(void)) { return gx::thr_start(on_start) ? 1 : 0; }
int gpu_on_gpu_thread(void) { return !gx::thr_remote(); }
void gpu_run(void (*fn)(void *), const void *arg, uint32_t size) {
  if (!gx::thr_remote()) { fn((void *)arg); return; }
  gx::thr_push(2, &fn, sizeof(fn), arg, size);
}
void gpu_sync(void) { gx::thr_sync(); }

void gpu_set_scale(int scale) {
  if (gx::thr_remote()) { gx::thr_post([scale] { gpu_set_scale(scale); }); return; }
  s_req_scale = scale < 1 ? 1 : scale;
}
void gpu_set_aspect(float a) {
  if (gx::thr_remote()) { gx::thr_post([a] { gx::set_aspect(a); }); return; }
  gx::set_aspect(a);
}
void gpu_request_scale(int scale) {
  if (gx::thr_remote()) { gx::thr_post([scale] { gpu_request_scale(scale); }); return; }
  if (s_inited) gx::request_scale(scale); else s_req_scale = scale;
}
int gpu_get_scale(void) { return gx::g_scale; }
float gpu_frame_gpu_ms(void) { return gx::g_frame_gpu_ms; }

void gpu_init(uint8_t *ram, uint32_t ram_size) {
  if (gx::thr_remote()) {
    gx::thr_post([ram, ram_size] { gpu_init(ram, ram_size); });
    gx::thr_sync();
    return;
  }
  gx::g_ram = ram;
  gx::g_ram_size = ram_size;
  if (!hmgl_load([](const char *n) { return SDL_GL_GetProcAddress(n); })) gx::logf("GL loader incomplete");
  memset(gx::xf, 0, sizeof(gx::xf));
  memset(gx::bp, 0, sizeof(gx::bp));
  gx::cp = gx::CPRegs();
  gx::bp[0x41] = 0x18;  // color/alpha update on
  gx::bp[0x40] = 0x17;
  gx::bp[0x21] = (527u) | (639u << 12);
  gx::fifo_reset();
  gx::texcache_init();
  if (const char *e = getenv("HM_ASPECT")) {  // temporary until the runtime calls gpu_set_aspect
    float a = 0, b = 0;
    if (sscanf(e, "%f:%f", &a, &b) == 2 && b > 0) a /= b;
    else a = (float)atof(e);
    if (a > 0) gx::set_aspect(a);
  }
  gx::render_init(s_req_scale);
  s_inited = true;
}

void gpu_shutdown(void) {
  if (gx::thr_remote()) {
    gx::thr_post([] { gpu_shutdown(); });
    gx::thr_sync();
    return;
  }
  if (!s_inited) return;
  gx::flush_batch();
  gx::texcache_shutdown();
  gx::shader_shutdown();
  gx::render_shutdown();
  s_inited = false;
}

void gpu_fifo_write(const uint8_t *data, uint32_t len) {
  if (gx::thr_remote()) { gx::thr_push(1, data, len, nullptr, 0); return; }
  gx::fifo_write_impl(data, len);
}

void gpu_present(int win_w, int win_h) {
  if (gx::thr_remote()) { gx::thr_post([win_w, win_h] { gpu_present(win_w, win_h); }); return; }
  gx::ProfScope ps(gx::g_prof.present);
  gx::gpu_timer(2);
  gx::present(win_w, win_h);
  gx::gpu_timer(0);
}

void gpu_present_ram_xfb(uint32_t xfb_phys, int width, int height, int stride_pixels, int win_w, int win_h) {
  if (gx::thr_remote()) {
    gx::thr_post([=] { gpu_present_ram_xfb(xfb_phys, width, height, stride_pixels, win_w, win_h); });
    return;
  }
  gx::present_ram_xfb(xfb_phys, width, height, stride_pixels, win_w, win_h);
}

uint32_t gpu_efb_peek(int x, int y, int is_z) {
  if (gx::thr_remote()) {
    uint32_t r = 0, *rp = &r;
    gx::thr_post([=] { *rp = gx::efb_peek(x, y, is_z); });
    gx::thr_sync();
    return r;
  }
  return gx::efb_peek(x, y, is_z);
}
void gpu_efb_poke(int x, int y, int is_z, uint32_t value) {
  if (gx::thr_remote()) { gx::thr_post([=] { gx::efb_poke(x, y, is_z, value); }); return; }
  gx::efb_poke(x, y, is_z, value);
}

// Extra (debug/test): reads the last XFB image as RGBA8, top row first. Returns 0 if none yet.
int gpu_debug_read_xfb(uint8_t **rgba, int *w, int *h) {
  if (gx::thr_remote()) {
    int r = 0, *rp = &r;
    gx::thr_post([=] { *rp = gpu_debug_read_xfb(rgba, w, h); });
    gx::thr_sync();
    return r;
  }
  static std::vector<uint8_t> buf;
  if (!gx::read_xfb(buf, *w, *h)) return 0;
  *rgba = buf.data();
  return 1;
}

}  // extern "C"

namespace gx {
Prof g_prof;
bool g_prof_on = getenv("HM_GPU_PROF") != nullptr;
double now_ms() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1e3 + ts.tv_nsec * 1e-6;
}
// GPU timer queries (profiling only): one query at a time, results collected a few frames later.
struct TQ { unsigned q; int slot; };
static std::vector<TQ> s_tq_pending;
static std::vector<unsigned> s_tq_free;
static int s_tq_slot = -1;
void gpu_timer(int slot) {
  if (!g_prof_on) return;
  if (s_tq_slot >= 0) glEndQuery(GL_TIME_ELAPSED);
  s_tq_slot = slot;
  if (slot < 0) return;
  unsigned q;
  if (!s_tq_free.empty()) { q = s_tq_free.back(); s_tq_free.pop_back(); }
  else glGenQueries(1, &q);
  glBeginQuery(GL_TIME_ELAPSED, q);
  s_tq_pending.push_back({q, slot});
  if (s_tq_pending.size() > 64) {  // collect old results
    size_t n = s_tq_pending.size() - 32;
    for (size_t i = 0; i < n; i++) {
      GLuint64 ns = 0;
      glGetQueryObjectui64v(s_tq_pending[i].q, GL_QUERY_RESULT, &ns);
      g_prof.gpu[s_tq_pending[i].slot] += ns * 1e-6;
      s_tq_free.push_back(s_tq_pending[i].q);
    }
    s_tq_pending.erase(s_tq_pending.begin(), s_tq_pending.begin() + n);
  }
}

void prof_frame() {
  if (!g_prof_on) return;
  static double t0 = now_ms();
  double t = now_ms();
  if (g_prof.xfbs < 60) return;
  double n = g_prof.xfbs;
  fprintf(stderr, "[gpu prof] GPU ms/frame: draws %.2f xfbcopy %.2f present %.2f\n", g_prof.gpu[0] / n,
          g_prof.gpu[1] / n, g_prof.gpu[2] / n);
  fprintf(stderr, "[gpu prof] %.1f ms/frame wall | fifo %.2f (flush %.2f texget %.2f copy %.2f readback %.2f) present %.2f | per frame: %.0f draws %.1f copies %.1f uploads %.2f compiles\n",
          (t - t0) / n, g_prof.fifo / n, g_prof.flush / n, g_prof.texget / n, g_prof.copy / n, g_prof.readback / n,
          g_prof.present / n, g_prof.draws / n, g_prof.copies / n, g_prof.uploads / n, g_prof.compiles / n);
  g_prof = Prof();
  t0 = t;
}
u8 *g_ram;
u32 g_ram_size;
}
