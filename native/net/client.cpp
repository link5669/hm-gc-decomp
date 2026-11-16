// Online co-op, guest side: thin client (no disc). Shows the host's video, plays its audio, sends our pad.
#include "net.h"
#include "proto.h"
#include <SDL.h>
#include <atomic>
#include <condition_variable>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <algorithm>
#include "third_party/stb_image.h"

using namespace hmnet;
extern std::string g_net_relay, g_net_room, g_net_join, g_net_name;
void pad_device_event(const SDL_Event &e);

namespace {
Conn g_c;
std::atomic<bool> g_quit{false};
std::atomic<int> g_rtt{-1};
std::string g_bye;
// stats
std::atomic<uint64_t> st_vbytes{0}, st_abytes{0}, st_dec_us{0};
std::atomic<uint32_t> st_vrecv{0}, st_vdec{0}, st_shown{0}, st_adrop{0}, st_aunder{0};
std::atomic<uint32_t> st_lat_sum{0}, st_lat_n{0};
// jpeg -> decoder -> main
std::mutex g_jmu; std::condition_variable g_jcv; std::vector<uint8_t> g_jpeg; bool g_jready;
std::mutex g_fmu; std::vector<uint8_t> g_rgb; int g_fw, g_fh; bool g_fready;
// audio
SDL_AudioDeviceID g_adev; int g_arate; bool g_astarted;
bool g_amute;
int g_target_ms = 60;

void audio_packet(const uint8_t *p, size_t n) {
    if (n < sizeof(AudioHdr)) return;
    AudioHdr h; memcpy(&h, p, sizeof h);
    if (n < sizeof h + h.frames || !h.rate) return;
    st_abytes += n + 5;
    AdpcmState st[2]; st[0].pred = h.pred[0]; st[1].pred = h.pred[1]; st[0].index = std::min<int>(h.index[0], 88); st[1].index = std::min<int>(h.index[1], 88);
    static std::vector<int16_t> pcm; pcm.resize((size_t)h.frames * 2);
    adpcm_decode(p + sizeof h, h.frames, st, pcm.data());
    if (g_amute) return;
    if ((int)h.rate != g_arate) {
        if (g_adev) SDL_CloseAudioDevice(g_adev);
        SDL_AudioSpec want{}, have{};
        want.freq = (int)h.rate; want.format = AUDIO_S16SYS; want.channels = 2; want.samples = 256;
        g_adev = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
        g_arate = (int)h.rate; g_astarted = false;
        if (!g_adev) { fprintf(stderr, "[net] audio: %s\n", SDL_GetError()); g_amute = true; return; }
    }
    uint32_t bps = (uint32_t)g_arate * 4, q = SDL_GetQueuedAudioSize(g_adev);
    if (g_astarted && q == 0) { st_aunder++; SDL_PauseAudioDevice(g_adev, 1); g_astarted = false; }   // underrun: re-prime
    if (q > bps * (uint32_t)g_target_ms * 2 / 1000) { st_adrop++; return; }                          // too far behind: drop
    SDL_QueueAudio(g_adev, pcm.data(), (uint32_t)pcm.size() * 2);
    if (!g_astarted && SDL_GetQueuedAudioSize(g_adev) >= bps * (uint32_t)g_target_ms / 1000) { SDL_PauseAudioDevice(g_adev, 0); g_astarted = true; }
}

void recv_thread() {
    uint8_t type; std::vector<uint8_t> pl;
    uint64_t t0_host = 0, t0_local = 0;   // host clock offset estimate for one-way latency (min-filtered)
    while (!g_quit && g_c.recv(&type, &pl, 15000)) {
        if (type == VIDEO && pl.size() > sizeof(VideoHdr)) {
            st_vrecv++; st_vbytes += pl.size() + 5;
            VideoHdr vh; memcpy(&vh, pl.data(), sizeof vh);
            uint64_t now = now_ms();
            // track arrival jitter: (local - host) relative to the minimum seen so far
            if (!t0_local || (int64_t)(now - t0_local) - (int64_t)(vh.host_ms - t0_host) < 0) { t0_local = now; t0_host = vh.host_ms; }
            st_lat_sum += (uint32_t)((now - t0_local) - (vh.host_ms - t0_host)); st_lat_n++;
            std::lock_guard<std::mutex> l(g_jmu);
            g_jpeg.assign(pl.begin() + sizeof vh, pl.end()); g_jready = true;
            g_jcv.notify_one();
        } else if (type == AUDIO) audio_packet(pl.data(), pl.size());
        else if (type == PING) g_c.send(PONG, pl.data(), pl.size());
        else if (type == PONG && pl.size() >= sizeof(Ping)) { Ping p; memcpy(&p, pl.data(), sizeof p); g_rtt = (int)(now_ms() - p.t_ms); }
        else if (type == BYE) { g_bye.assign(pl.begin(), pl.end()); break; }
    }
    if (!g_quit) fprintf(stderr, "[net] disconnected from host%s%s\n", g_bye.empty() ? "" : ": ", g_bye.c_str());
    g_quit = true;
    g_jcv.notify_all();
}

void decode_thread() {
    std::vector<uint8_t> j;
    while (!g_quit) {
        {
            std::unique_lock<std::mutex> l(g_jmu);
            g_jcv.wait(l, [] { return g_jready || g_quit; });
            if (g_quit) return;
            j.swap(g_jpeg); g_jready = false;
        }
        uint64_t t0 = SDL_GetPerformanceCounter();
        int w, h, n;
        uint8_t *px = stbi_load_from_memory(j.data(), (int)j.size(), &w, &h, &n, 3);
        if (!px) continue;
        st_dec_us += (SDL_GetPerformanceCounter() - t0) * 1000000 / SDL_GetPerformanceFrequency();
        st_vdec++;
        {
            std::lock_guard<std::mutex> l(g_fmu);
            g_rgb.assign(px, px + (size_t)w * h * 3); g_fw = w; g_fh = h; g_fready = true;
        }
        stbi_image_free(px);
    }
}

// HM_NET_SCRIPT="5000:S 92000:S*200 ..." : ms after connecting, buttons as HM_SCRIPT (A B X Y Z S U D L R ^ v < >), *n = hold n ms (default 100)
struct Ev { uint64_t t, hold; uint16_t b; int8_t sx, sy; };
std::vector<Ev> parse_script() {
    std::vector<Ev> ev;
    const char *s = getenv("HM_NET_SCRIPT");
    while (s && *s) {
        while (*s == ' ' || *s == ',') s++;
        if (!*s) break;
        Ev e{strtoull(s, (char **)&s, 10), 100, 0, 0, 0};
        if (*s == ':') s++;
        for (; *s && *s != ' ' && *s != ',' && *s != '*'; s++) switch (*s) {
            case 'A': e.b |= 0x100; break; case 'B': e.b |= 0x200; break; case 'X': e.b |= 0x400; break; case 'Y': e.b |= 0x800; break;
            case 'Z': e.b |= 0x10; break; case 'S': e.b |= 0x1000; break; case 'U': e.b |= 8; break; case 'D': e.b |= 4; break;
            case 'L': e.b |= 1; break; case 'R': e.b |= 2; break; case '^': e.sy = 100; break; case 'v': e.sy = -100; break;
            case '<': e.sx = -100; break; case '>': e.sx = 100; break; }
        if (*s == '*') { s++; e.hold = strtoull(s, (char **)&s, 10); }
        ev.push_back(e);
    }
    return ev;
}

bool connect_host() {
    std::string err, host; int port;
    int fd;
    if (!g_net_relay.empty()) {
        if (!parse_hostport(g_net_relay, &host, &port, 7778)) { fprintf(stderr, "[net] bad --relay\n"); return false; }
        fd = tcp_connect(host, port, &err);
        if (fd < 0) { fprintf(stderr, "[net] relay %s: %s\n", g_net_relay.c_str(), err.c_str()); return false; }
        std::string pre = "HMRELAY JOIN " + g_net_room + "\n", line;
        if (!write_all(fd, pre.data(), pre.size()) || !read_line(fd, &line, 15000) || line.compare(0, 2, "OK") != 0) {
            fprintf(stderr, "[net] relay: %s\n", line.empty() ? "no answer" : line.c_str()); close(fd); return false;
        }
    } else {
        if (!parse_hostport(g_net_join, &host, &port, DEFAULT_PORT)) { fprintf(stderr, "[net] usage: --join HOST[:PORT]\n"); return false; }
        fd = tcp_connect(host, port, &err);
        if (fd < 0) { fprintf(stderr, "[net] connect %s:%d: %s\n", host.c_str(), port, err.c_str()); return false; }
    }
    g_c.fd = fd;
    Hello h{}; h.magic = MAGIC; h.version = VERSION; h.role = 0;
    snprintf(h.room, sizeof h.room, "%s", g_net_room.c_str()); snprintf(h.name, sizeof h.name, "%s", g_net_name.c_str());
    g_c.send(HELLO, &h, sizeof h);
    uint8_t type; std::vector<uint8_t> pl;
    if (!g_c.recv(&type, &pl, 15000)) { fprintf(stderr, "[net] no answer from host\n"); return false; }
    if (type == BYE) { fprintf(stderr, "[net] host refused: %.*s\n", (int)pl.size(), (const char *)pl.data()); return false; }
    if (type != HELLO || pl.size() < sizeof(Hello)) { fprintf(stderr, "[net] bad handshake\n"); return false; }
    Hello r; memcpy(&r, pl.data(), sizeof r); r.name[sizeof r.name - 1] = 0;
    if (r.magic != MAGIC || r.version != VERSION) { fprintf(stderr, "[net] protocol version mismatch\n"); return false; }
    fprintf(stderr, "[net] connected to host %s (you are player 2)\n", r.name);
    return true;
}
}  // namespace

int net_client_main() {
    g_amute = getenv("HM_AUDIO_MUTE") && *getenv("HM_AUDIO_MUTE") != '0';
    g_target_ms = env_int("HM_NET_AUDIO_MS", 60);
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) != 0) { fprintf(stderr, "SDL_Init: %s\n", SDL_GetError()); return 1; }
    if (!connect_host()) { if (!getenv("HM_HIDDEN")) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "The Haunted Mansion", "Could not connect to the host (see terminal).", nullptr); return 1; }
    SDL_Window *win = SDL_CreateWindow("The Haunted Mansion (online, player 2)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720,
                                       SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | (getenv("HM_HIDDEN") ? SDL_WINDOW_HIDDEN : 0));
    if (!win) { fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError()); return 1; }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) ren = SDL_CreateRenderer(win, -1, 0);
    if (!ren) { fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError()); return 1; }
    bool fullscreen = getenv("HM_FULLSCREEN") != nullptr;
    if (fullscreen) SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);
    std::thread rt(recv_thread), dt(decode_thread);
    SDL_Texture *tex = nullptr; int tw = 0, th = 0;
    std::vector<uint8_t> rgb; bool redraw = true;
    auto script = parse_script();
    Input last{}; uint64_t last_send = 0, last_ping = 0, last_stat = now_ms(), t_conn = now_ms();
    uint64_t s_v0 = 0, s_a0 = 0, s_d0 = 0; uint32_t s_r0 = 0, s_dec0 = 0, s_sh0 = 0, s_l0 = 0, s_ln0 = 0;
    while (!g_quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) g_quit = true;
            if (e.type == SDL_KEYDOWN && !e.key.repeat) {
                SDL_Keycode k = e.key.keysym.sym;
                if (k == SDLK_F11 || (k == SDLK_RETURN && (e.key.keysym.mod & KMOD_ALT))) { fullscreen = !fullscreen; SDL_SetWindowFullscreen(win, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0); }
                if (k == SDLK_ESCAPE && fullscreen) { fullscreen = false; SDL_SetWindowFullscreen(win, 0); }
            }
            if (e.type == SDL_WINDOWEVENT) redraw = true;
            pad_device_event(e);
        }
        uint64_t now = now_ms();
        // input: local player 1 mapping -> remote player 2
        NetPad p{}; pad_local_p1(&p);
        Input in{p.buttons, p.sx, p.sy, p.cx, p.cy, p.tl, p.tr, 1};
        for (auto &ev : script) if (now - t_conn >= ev.t && now - t_conn < ev.t + ev.hold) {
            if (!(last.buttons & ev.b)) fprintf(stderr, "[net] script: t=%llu ms buttons %04X\n", (unsigned long long)(now - t_conn), ev.b);
            in.buttons |= ev.b; if (ev.sx) in.sx = ev.sx; if (ev.sy) in.sy = ev.sy;
        }
        if (memcmp(&in, &last, sizeof in) != 0 || now - last_send >= 50) {
            if (!g_c.send(INPUT, &in, sizeof in)) break;
            last = in; last_send = now;
        }
        if (now - last_ping >= 1000) { last_ping = now; Ping pg{now}; g_c.send(PING, &pg, sizeof pg); }
        // video
        {
            std::lock_guard<std::mutex> l(g_fmu);
            if (g_fready) {
                rgb.swap(g_rgb); g_fready = false; redraw = true;
                if (g_fw != tw || g_fh != th) {
                    if (tex) SDL_DestroyTexture(tex);
                    tw = g_fw; th = g_fh;
                    tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, tw, th);
                }
                if (tex) SDL_UpdateTexture(tex, nullptr, rgb.data(), tw * 3);
                st_shown++;
            }
        }
        if (redraw) {
            redraw = false;
            int ow, oh; SDL_GetRendererOutputSize(ren, &ow, &oh);
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); SDL_RenderClear(ren);
            if (tex && tw && th) {   // letterbox, aspect-correct
                SDL_Rect d; double s = std::min((double)ow / tw, (double)oh / th);
                d.w = (int)(tw * s); d.h = (int)(th * s); d.x = (ow - d.w) / 2; d.y = (oh - d.h) / 2;
                SDL_RenderCopy(ren, tex, nullptr, &d);
            }
            SDL_RenderPresent(ren);
        }
        if (now - last_stat >= 5000) {
            double dt = (now - last_stat) / 1000.0;
            uint32_t r = st_vrecv, dc = st_vdec, sh = st_shown, ls = st_lat_sum, ln = st_lat_n;
            uint32_t aq = g_adev ? SDL_GetQueuedAudioSize(g_adev) : 0;
            fprintf(stderr, "[net] guest: video recv %.1f fps %.0f kbit/s, decoded %.1f fps (%.1f ms), shown %.1f fps, jitter %.0f ms, "
                            "audio %.0f kbit/s queue %u ms (drops %u, underruns %u), rtt %d ms\n",
                    (r - s_r0) / dt, (st_vbytes - s_v0) * 8 / 1000.0 / dt, (dc - s_dec0) / dt,
                    dc > s_dec0 ? (st_dec_us - s_d0) / 1000.0 / (dc - s_dec0) : 0.0, (sh - s_sh0) / dt,
                    ln > s_ln0 ? (double)(ls - s_l0) / (ln - s_ln0) : 0.0,
                    (st_abytes - s_a0) * 8 / 1000.0 / dt, g_arate ? aq * 1000 / (g_arate * 4) : 0, st_adrop.load(), st_aunder.load(), g_rtt.load());
            char t[128]; snprintf(t, sizeof t, "The Haunted Mansion (online, player 2)  RTT %d ms", g_rtt.load());
            SDL_SetWindowTitle(win, t);
            last_stat = now; s_v0 = st_vbytes; s_a0 = st_abytes; s_d0 = st_dec_us; s_r0 = r; s_dec0 = dc; s_sh0 = sh; s_l0 = ls; s_ln0 = ln;
        }
        SDL_Delay(4);   // ~120-250 Hz input sampling
    }
    g_quit = true;
    g_c.send(BYE, "quit", 4);
    g_c.close();
    g_jcv.notify_all();
    rt.join(); dt.join();
    if (g_adev) SDL_CloseAudioDevice(g_adev);
    SDL_Quit();
    return 0;
}
