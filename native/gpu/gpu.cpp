// C ABI entry points (gpu.h).
#include <SDL.h>
#include "glfuncs.h"
#include "gx_internal.h"

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

extern "C" {

void gpu_set_scale(int scale) { s_req_scale = scale < 1 ? 1 : scale; }

void gpu_init(uint8_t *ram, uint32_t ram_size) {
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
  gx::render_init(s_req_scale);
  s_inited = true;
}

void gpu_shutdown(void) {
  if (!s_inited) return;
  gx::flush_batch();
  gx::texcache_shutdown();
  gx::shader_shutdown();
  gx::render_shutdown();
  s_inited = false;
}

void gpu_fifo_write(const uint8_t *data, uint32_t len) {
  gx::g_epoch++;  // guest RAM may have changed since the last call
  gx::fifo_feed(data, len);
}

void gpu_present(int win_w, int win_h) { gx::present(win_w, win_h); }

void gpu_present_ram_xfb(uint32_t xfb_phys, int width, int height, int stride_pixels, int win_w, int win_h) {
  gx::present_ram_xfb(xfb_phys, width, height, stride_pixels, win_w, win_h);
}

uint32_t gpu_efb_peek(int x, int y, int is_z) { return gx::efb_peek(x, y, is_z); }
void gpu_efb_poke(int x, int y, int is_z, uint32_t value) { gx::efb_poke(x, y, is_z, value); }

// Extra (debug/test): reads the last XFB image as RGBA8, top row first. Returns 0 if none yet.
int gpu_debug_read_xfb(uint8_t **rgba, int *w, int *h) {
  static std::vector<uint8_t> buf;
  if (!gx::read_xfb(buf, *w, *h)) return 0;
  *rgba = buf.data();
  return 1;
}

}  // extern "C"

namespace gx {
u8 *g_ram;
u32 g_ram_size;
}
