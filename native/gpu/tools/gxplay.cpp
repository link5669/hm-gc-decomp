// gxplay: replays a .gxcap capture through the GPU module and writes a PNG per XFB copy.
// usage: gxplay <file.gxcap> [-o outdir] [-scale n] [-max n]
#include <SDL.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include "../gpu.h"
#include "png.h"

static std::string g_out = ".";
static int g_xfb_count = 0, g_max = 1000000, g_frame = -1;
static bool g_save = true;
static uint8_t *g_ram;

extern "C" void gpu_cb_draw_done(void) {}
extern "C" void gpu_cb_token(uint16_t) {}
extern "C" void gpu_cb_xfb_copy(uint32_t addr, uint32_t w, uint32_t h) {
  int n = g_xfb_count++;
  if (getenv("HM_GXPLAY_DUMPXFB") && g_ram) {  // raw YUYV the GPU wrote to guest RAM
    char p[1024];
    snprintf(p, sizeof(p), "%s/xfb_%04d_%ux%u.yuyv", g_out.c_str(), n, w, h);
    if (FILE *o = fopen(p, "wb")) { fwrite(g_ram + (addr & 0x01FFFFFF), 1, (size_t)w * h * 2, o); fclose(o); }
  }
  if (!g_save || n >= g_max) return;
  uint8_t *px;
  int iw, ih;
  if (!gpu_debug_read_xfb(&px, &iw, &ih)) return;
  char path[1024];
  snprintf(path, sizeof(path), "%s/xfb_%04d.png", g_out.c_str(), n);
  pngw::write_png(path, px, iw, ih);
  printf("xfb copy %d (frame %d): addr %08x %ux%u -> %s (%dx%d)\n", n, g_frame, addr, w, h, path, iw, ih);
}

int main(int argc, char **argv) {
  const char *file = nullptr;
  int scale = 1;
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-o") && i + 1 < argc) g_out = argv[++i];
    else if (!strcmp(argv[i], "-scale") && i + 1 < argc) scale = atoi(argv[++i]);
    else if (!strcmp(argv[i], "-max") && i + 1 < argc) g_max = atoi(argv[++i]);
    else if (!strcmp(argv[i], "-nosave")) g_save = false;
    else file = argv[i];
  }
  if (!file) {
    fprintf(stderr, "usage: gxplay <file.gxcap> [-o outdir] [-scale n] [-max n] [-nosave]\n");
    return 1;
  }
  FILE *f = fopen(file, "rb");
  if (!f) { perror(file); return 1; }
  char magic[8];
  if (fread(magic, 1, 8, f) != 8 || memcmp(magic, "GXCAP001", 8)) {
    fprintf(stderr, "not a GXCAP001 file\n");
    return 1;
  }
  if (getenv("DISPLAY") == nullptr && getenv("WAYLAND_DISPLAY") == nullptr) SDL_setenv("SDL_VIDEODRIVER", "offscreen", 0);
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    return 1;
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_Window *win = SDL_CreateWindow("gxplay", 0, 0, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
  if (!win) { fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError()); return 1; }
  SDL_GLContext ctx = SDL_GL_CreateContext(win);
  if (!ctx) { fprintf(stderr, "SDL_GL_CreateContext: %s\n", SDL_GetError()); return 1; }
  SDL_GL_MakeCurrent(win, ctx);

  const uint32_t RAM = 24u << 20;
  std::vector<uint8_t> ram(RAM, 0);
  g_ram = ram.data();
  gpu_set_scale(scale);
  gpu_init(ram.data(), RAM);
  std::vector<uint8_t> buf;
  uint64_t fifo_bytes = 0;
  int records = 0;
  uint32_t t0 = SDL_GetTicks();
  for (;;) {
    uint32_t hdr[2];
    if (fread(hdr, 4, 2, f) != 2) break;
    buf.resize(hdr[1]);
    if (hdr[1] && fread(buf.data(), 1, hdr[1], f) != hdr[1]) { fprintf(stderr, "truncated record\n"); break; }
    records++;
    switch (hdr[0]) {
      case 0x534D4152:  // RAMS
        memcpy(ram.data(), buf.data(), hdr[1] < RAM ? hdr[1] : RAM);
        break;
      case 0x574D454D: {  // MEMW
        if (hdr[1] < 4) break;
        uint32_t a;
        memcpy(&a, buf.data(), 4);
        a &= 0x01FFFFFF;
        uint32_t n = hdr[1] - 4;
        if (a < RAM) memcpy(ram.data() + a, buf.data() + 4, (a + n <= RAM) ? n : RAM - a);
        break;
      }
      case 0x4F464946:  // FIFO
        gpu_fifo_write(buf.data(), hdr[1]);
        fifo_bytes += hdr[1];
        break;
      case 0x454D5246:  // FRME
        if (hdr[1] >= 4) memcpy(&g_frame, buf.data(), 4);
        break;
      default:
        fprintf(stderr, "unknown record %08x\n", hdr[0]);
    }
    if (g_xfb_count >= g_max) break;
  }
  printf("%d records, %llu fifo bytes, %d xfb copies, %u ms\n", records, (unsigned long long)fifo_bytes,
         g_xfb_count, SDL_GetTicks() - t0);
  gpu_shutdown();
  SDL_GL_DeleteContext(ctx);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
