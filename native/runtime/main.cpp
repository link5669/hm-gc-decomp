// Native Haunted Mansion: window, startup, frame presentation.
#include "rt.h"
#include "../gpu/gpu.h"
#include "../audio/audio.h"
#include "../net/net.h"   // [net] online co-op
#include <SDL.h>
#include <sys/mman.h>
#include <unistd.h>
#include <csignal>
#include "../gpu/tools/png.h"
#include <string>
#include <vector>
#include <algorithm>

extern "C" const u8 hm_dol[]; extern "C" const u8 hm_dol_end[];
extern "C" const u32 rt_entry_point;
void rt_init_calls();
void pad_device_event(const SDL_Event &e);

static SDL_Window *g_win;
static SDL_GLContext g_gl;
static u32 g_frames; static u64 g_fps_t0;
extern u32 g_vi_count;
static bool g_fullscreen;

void hw_poll_host() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) { LOG("quit\n"); audio_shutdown(); fflush(stderr); _exit(0); }
        if (e.type == SDL_KEYDOWN && !e.key.repeat) {
            SDL_Keycode k = e.key.keysym.sym;
            if (k == SDLK_F11 || (k == SDLK_RETURN && (e.key.keysym.mod & KMOD_ALT))) {
                g_fullscreen = !g_fullscreen;
                SDL_SetWindowFullscreen(g_win, g_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
            }
            if (k == SDLK_ESCAPE && g_fullscreen) { g_fullscreen = false; SDL_SetWindowFullscreen(g_win, 0); }
        }
        pad_device_event(e);
    }
    pad_poll_host();
}

// The GPU calls this after each EFB->XFB copy. Presentation happens at VI retrace (present_vi_frame),
// showing whatever frame buffer the VI scans out: a GPU copy, or a CPU-written XFB (Bink movies).
static u32 g_copy_addr[2]; static u64 g_copy_serial;
extern "C" __attribute__((weak)) void gpu_set_aspect(float) {}
extern "C" void gpu_cb_xfb_copy(uint32_t xfb, uint32_t w, uint32_t h) {
    g_copy_addr[g_copy_serial++ & 1] = xfb & 0x01FFFFFF;
}
static u64 xfb_sample_hash(u32 xfb, int w, int h) {
    u64 hsh = 1469598103934665603ull;
    size_t n = (size_t)w * h * 2;
    for (size_t i = 0; i < n; i += 997 * 4) { u32 v; memcpy(&v, RAM + ((xfb + i) & 0x01FFFFFC), 4); hsh = (hsh ^ v) * 1099511628211ull; }
    return hsh;
}

void present_vi_frame(u32 xfb, int w, int h) {
    static u64 last_serial, last_hash; static u32 last_addr; static bool hash_valid;
    xfb &= 0x01FFFFFF;
    bool gpu_frame = g_copy_serial && (xfb == g_copy_addr[0] || xfb == g_copy_addr[1] || xfb == 0);
    if (gpu_frame && xfb && w > 0 && h > 0) {
        // a GPU copy went to this buffer; if the CPU has written over it since (Bink), show RAM instead
        if (g_copy_serial != last_serial || xfb != last_addr) hash_valid = false;
        u64 hs = xfb_sample_hash(xfb, w, h);
        if (!hash_valid) { last_hash = hs; hash_valid = true; }
        else if (hs != last_hash) gpu_frame = false;
    }
    if (gpu_frame && g_copy_serial == last_serial && xfb == last_addr) return;   // nothing new
    int ww, wh; SDL_GL_GetDrawableSize(g_win, &ww, &wh);
    {   // widescreen: render at the window's aspect unless HM_ASPECT forces one (e.g. 4:3, 16:9, 1.78)
        static float forced = -1;
        if (forced < 0) {
            forced = 0;
            if (const char *a = getenv("HM_ASPECT")) { float x = 0, y = 0; if (sscanf(a, "%f:%f", &x, &y) == 2 && y > 0) forced = x / y; else forced = (float)atof(a); }
        }
        float asp = forced > 0 ? forced : (wh > 0 ? (float)ww / wh : 4.0f / 3.0f);
        if (asp < 4.0f / 3.0f) asp = 4.0f / 3.0f;
        gpu_set_aspect(asp);
    }
    if (gpu_frame) gpu_present(ww, wh);
    else if (xfb && w > 0 && h > 0) gpu_present_ram_xfb(xfb, w, h, w, ww, wh);
    else return;
    net_capture_frame(ww, wh);   // [net] stream this frame to a connected guest
    last_serial = g_copy_serial; last_addr = xfb;
    SDL_GL_SwapWindow(g_win);
    g_frames++;
    static u32 total; total++;
    static const char *shotdir = getenv("HM_SHOTDIR");
    static int every = getenv("HM_SHOTEVERY") ? atoi(getenv("HM_SHOTEVERY")) : 60;
    extern volatile bool g_shot_request;
    bool req = g_shot_request; g_shot_request = false;
    if (shotdir && (total % every == 0 || req)) {
        uint8_t *px; int pw, ph;
        if (gpu_frame && gpu_debug_read_xfb(&px, &pw, &ph)) {
            char path[512]; snprintf(path, sizeof path, "%s/f%05u.png", shotdir, g_vi_count);
            pngw::write_png(path, px, pw, ph);
        } else if (!gpu_frame) {   // CPU XFB: convert here for the screenshot
            std::vector<u8> rgba((size_t)w * h * 4);
            for (int y = 0; y < h; y++) for (int x = 0; x < w; x += 2) {
                const u8 *p = RAM + ((xfb + (y * w + x) * 2) & 0x01FFFFFF);
                int Y0 = p[0], U = p[1] - 128, Y1 = p[2], V = p[3] - 128;
                for (int k = 0; k < 2; k++) {
                    double Yv = 1.164 * ((k ? Y1 : Y0) - 16);
                    int r = (int)(Yv + 1.596 * V), g = (int)(Yv - 0.392 * U - 0.813 * V), b = (int)(Yv + 2.017 * U);
                    u8 *o = &rgba[((size_t)y * w + x + k) * 4];
                    o[0] = std::clamp(r, 0, 255); o[1] = std::clamp(g, 0, 255); o[2] = std::clamp(b, 0, 255); o[3] = 255;
                }
            }
            char path[512]; snprintf(path, sizeof path, "%s/f%05u.png", shotdir, g_vi_count);
            pngw::write_png(path, rgba.data(), w, h);
        }
    }
    u64 now = SDL_GetTicks64();
    if (now - g_fps_t0 >= 1000) {
        char t[256]; snprintf(t, sizeof t, "The Haunted Mansion  (%u fps)  %s", (unsigned)(g_frames * 1000 / (now - g_fps_t0)), net_status());   // [net] status
        SDL_SetWindowTitle(g_win, t);
        if (getenv("HM_FPS")) LOG("%s\n", t);
        g_frames = 0; g_fps_t0 = now;
    }
}

static std::string find_disc(int argc, char **argv) {
    if (argc > 1) return argv[1];
    if (const char *e = getenv("HM_DISC")) return e;
    std::vector<std::string> cands;
    if (const char *h = getenv("HOME")) {
        cands.push_back(std::string(h) + "/.local/share/hauntedmansion/game.iso");
    }
    char exe[4096]; ssize_t n = readlink("/proc/self/exe", exe, sizeof exe - 1);
    if (n > 0) { exe[n] = 0; std::string d(exe); d = d.substr(0, d.rfind('/')); cands.push_back(d + "/game.iso"); }
    for (auto &c : cands) if (access(c.c_str(), R_OK) == 0) return c;
    return "";
}

static void dump_guest(int) {
    CPU *c = &g_cpu; u32 off;
    fprintf(stderr, "[guest] lr=%08X (%s+0x%X) r1=%08X r3=%08X msr=%08X ctx=%08X\n", c->lr, rt_func_name(c->lr, &off), off, c->r[1], c->r[3], c->msr, ld32(0x800000D4));
    u32 sp = c->r[1];
    for (int i = 0; i < 20 && ISRAM(sp) && sp; i++) {
        u32 next = ld32(sp); if (!ISRAM(next) || next <= sp) break;
        u32 lr = ld32(next + 4);
        fprintf(stderr, "  #%d %08X %s+0x%X\n", i, lr, rt_func_name(lr, &off), off);
        sp = next;
    }
}

int main(int argc, char **argv) {
    signal(SIGUSR1, dump_guest);
    if (const char *l = getenv("HM_LOG")) g_log_level = atoi(l);
    void *ram = mmap(RAM, 0x02000000, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
    if (ram != RAM) { fprintf(stderr, "cannot map guest RAM at %p\n", RAM); return 1; }

    int net_mode = net_parse_args(&argc, argv);   // [net] --host/--join/--relay/--room
    if (net_mode == 2) return net_client_main();  // [net] guest: thin client, no disc
    std::string disc = find_disc(argc, argv);
    if (disc.empty() || !disc_open(disc)) {
        const char *msg = "Put your copy of the game (GHYE6S disc image, .iso) at ~/.local/share/hauntedmansion/game.iso,\n"
                          "or pass its path as the first argument.";
        fprintf(stderr, "%s\n", msg);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "The Haunted Mansion", msg, nullptr);
        return 1;
    }

    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) != 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError()); return 1;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    int scale = 2;
    if (getenv("HM_SCALE")) scale = atoi(getenv("HM_SCALE"));
    else {   // auto: render at least at the monitor's native height (supersampled when above it)
        SDL_DisplayMode dm;
        if (SDL_GetDesktopDisplayMode(0, &dm) == 0 && dm.h > 0) scale = (dm.h + 479) / 480;
        if (scale < 2) scale = 2;
        if (scale > 6) scale = 6;
    }
    g_win = SDL_CreateWindow("The Haunted Mansion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720,
                             SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | (getenv("HM_HIDDEN") ? SDL_WINDOW_HIDDEN : 0));
    if (!g_win) { fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError()); return 1; }
    g_gl = SDL_GL_CreateContext(g_win);
    if (!g_gl) { fprintf(stderr, "GL context: %s\n", SDL_GetError()); return 1; }
    SDL_GL_SetSwapInterval(0);
    if (getenv("HM_FULLSCREEN")) { g_fullscreen = true; SDL_SetWindowFullscreen(g_win, SDL_WINDOW_FULLSCREEN_DESKTOP); }

    rt_init_calls();
    if (getenv("HM_TEST_DIV")) {   // self-test of recompiled 64-bit division helpers
        CPU *c = &g_cpu;
        u64 tests[][2] = {{1000000000000ull, 40500ull}, {123456789ull, 7ull}, {0x100000000ull, 3}, {5, 10}};
        for (auto &t : tests) {
            c->r[3] = t[0] >> 32; c->r[4] = (u32)t[0]; c->r[5] = t[1] >> 32; c->r[6] = (u32)t[1]; c->r[1] = 0x80300000;
            rt_call(c, rt_sym("__div2i"));
            u64 q = ((u64)c->r[3] << 32) | c->r[4];
            printf("div %llu / %llu = %llu (expect %llu)\n", (unsigned long long)t[0], (unsigned long long)t[1], (unsigned long long)q, (unsigned long long)(t[0] / t[1]));
        }
        return 0;
    }
    dol_load(hm_dol, hm_dol_end - hm_dol);
    boot_setup_lowmem();
    tb_set(0x100000ull);
    gpu_set_scale(scale);
    gpu_init(RAM, 0x01800000);
    audio_init(RAM);
    audio_set_capture(net_audio_capture);   // [net]
    net_host_start();                       // [net]
    hw_init();
    os_init_main_fiber();
    ev_start_timer_thread();
    g_fps_t0 = SDL_GetTicks64();

    CPU *c = &g_cpu;
    memset(c, 0, sizeof *c);
    c->msr = 0x00002032;   // FP | IR | DR | RI (EE off until OSInit enables it)
    c->spr[1008] = 0x0011C464; c->spr[1009] = 0x80000000; c->spr[920] = 0xE0000000;
    LOG("starting at %08X, disc %s\n", rt_entry_point, disc.c_str());
    os_run_entry(rt_entry_point);
}
