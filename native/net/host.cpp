// Online co-op, host side: frame capture (async PBO), JPEG encode thread, audio capture, guest session.
#include "net.h"
#include "proto.h"
#include <SDL.h>
#include <GL/glcorearb.h>
#include <atomic>
#include <condition_variable>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <algorithm>
#include <netdb.h>
#include <sys/socket.h>
#include "third_party/stb_image_write.h"

using namespace hmnet;

// ---------------------------------------------------------------- config / args
static int g_mode;   // 0 off, 1 host, 2 guest
std::string g_net_relay, g_net_room, g_net_join, g_net_name;
int g_net_port = DEFAULT_PORT;

static std::string random_room() {
    static const char cs[] = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789";
    std::string s; srand((unsigned)(now_ms() ^ getpid()));
    for (int i = 0; i < 6; i++) s += cs[rand() % 32];
    return s;
}

int net_parse_args(int *argc, char **argv) {
    bool host = false, join = false;
    int o = 1;
    for (int i = 1; i < *argc; i++) {
        std::string a = argv[i];
        auto next = [&]() { return i + 1 < *argc ? std::string(argv[++i]) : std::string(); };
        if (a == "--host") { host = true; if (i + 1 < *argc && isdigit((unsigned char)argv[i + 1][0]) && !strchr(argv[i + 1], '.')) g_net_port = atoi(argv[++i]); }
        else if (a == "--join") { join = true; if (i + 1 < *argc && argv[i + 1][0] != '-') g_net_join = argv[++i]; }
        else if (a == "--relay") g_net_relay = next();
        else if (a == "--room") g_net_room = next();
        else if (a == "--name") g_net_name = next();
        else argv[o++] = argv[i];
    }
    *argc = o; argv[o] = nullptr;
    if (g_net_room.empty()) g_net_room = env_str("HM_NET_ROOM", "");
    for (auto &c : g_net_room) c = (char)toupper((unsigned char)c);
    if (g_net_name.empty()) g_net_name = env_str("HM_NET_NAME", env_str("USER", "player").c_str());
    // --relay alone or with --host = host via relay; --relay with --room (no --host) or --join = guest
    if (join || (!g_net_relay.empty() && !g_net_room.empty() && !host)) g_mode = 2;
    else if (host || !g_net_relay.empty()) g_mode = 1;
    if (g_mode == 1 && !g_net_relay.empty() && g_net_room.empty()) g_net_room = random_room();
    return g_mode;
}

// ---------------------------------------------------------------- shared host state
static std::atomic<bool> g_active{false};       // a guest session is running
static std::mutex g_mu;                          // guards the fields below
static NetPad g_pad; static bool g_pad_valid;
static std::string g_guest_name; static int g_rtt = -1;
static std::condition_variable g_wake;           // wakes the sender (new video / audio)

// video: GL thread -> encoder (raw RGBA) -> sender (JPEG); one slot each, newest wins
static std::mutex g_vmu; static std::condition_variable g_vcv;
static std::vector<uint8_t> g_raw; static int g_raw_w, g_raw_h; static bool g_raw_ready;
static std::vector<uint8_t> g_jpeg; static int g_jpeg_w, g_jpeg_h; static bool g_jpeg_ready;
static std::atomic<uint32_t> st_captured{0}, st_enc_drop{0}, st_net_drop{0}, st_sent{0};
static std::atomic<uint64_t> st_vbytes{0}, st_abytes{0}, st_cap_us{0}, st_cap_n{0}, st_enc_us{0};

// audio: audio thread -> sender
static std::mutex g_amu; static std::vector<int16_t> g_abuf; static int g_arate;

void net_audio_capture(const int16_t *lr, int frames, int rate) {
    if (!g_active.load(std::memory_order_relaxed)) return;
    std::lock_guard<std::mutex> g(g_amu);
    if (rate != g_arate) { g_abuf.clear(); g_arate = rate; }
    g_abuf.insert(g_abuf.end(), lr, lr + frames * 2);
    size_t maxs = (size_t)rate / 4 * 2;   // keep at most 250 ms (the link stalled)
    if (g_abuf.size() > maxs) g_abuf.erase(g_abuf.begin(), g_abuf.begin() + (g_abuf.size() - maxs));
}

bool net_remote_pad(NetPad *out) {
    if (!g_active.load(std::memory_order_relaxed)) return false;
    std::lock_guard<std::mutex> g(g_mu);
    if (!g_pad_valid) return false;
    *out = g_pad;
    return true;
}

const char *net_status() {
    static thread_local char buf[160];
    buf[0] = 0;
    if (g_mode != 1) return buf;
    std::lock_guard<std::mutex> g(g_mu);
    if (g_active) snprintf(buf, sizeof buf, "guest connected (%s, %d ms)", g_guest_name.c_str(), g_rtt);
    else if (!g_net_relay.empty()) snprintf(buf, sizeof buf, "room %s: waiting for guest", g_net_room.c_str());
    else snprintf(buf, sizeof buf, "hosting on port %d", g_net_port);
    return buf;
}

// ---------------------------------------------------------------- capture (GL thread)
#define GLF(X) X(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers) X(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer) \
  X(PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffers) X(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer) \
  X(PFNGLRENDERBUFFERSTORAGEPROC, glRenderbufferStorage) X(PFNGLFRAMEBUFFERRENDERBUFFERPROC, glFramebufferRenderbuffer) \
  X(PFNGLBLITFRAMEBUFFERPROC, glBlitFramebuffer) X(PFNGLGENBUFFERSPROC, glGenBuffers) X(PFNGLBINDBUFFERPROC, glBindBuffer) \
  X(PFNGLBUFFERDATAPROC, glBufferData) X(PFNGLMAPBUFFERRANGEPROC, glMapBufferRange) X(PFNGLUNMAPBUFFERPROC, glUnmapBuffer) \
  X(PFNGLFENCESYNCPROC, glFenceSync) X(PFNGLCLIENTWAITSYNCPROC, glClientWaitSync) X(PFNGLDELETESYNCPROC, glDeleteSync) \
  X(PFNGLREADPIXELSPROC, glReadPixels) X(PFNGLGETINTEGERVPROC, glGetIntegerv) X(PFNGLISENABLEDPROC, glIsEnabled) \
  X(PFNGLENABLEPROC, glEnable) X(PFNGLDISABLEPROC, glDisable) X(PFNGLPIXELSTOREIPROC, glPixelStorei)
#define DECL(T, n) static T n##_;
GLF(DECL)

static void encoder_thread() {
    std::vector<uint8_t> raw, out;
    int quality = env_int("HM_NET_QUALITY", 65);
    for (;;) {
        int w, h;
        {
            std::unique_lock<std::mutex> l(g_vmu);
            g_vcv.wait(l, [] { return g_raw_ready; });
            raw.swap(g_raw); w = g_raw_w; h = g_raw_h; g_raw_ready = false;
        }
        uint64_t t0 = SDL_GetPerformanceCounter();
        out.clear();
        stbi_write_jpg_to_func([](void *ctx, void *d, int n) { auto *v = (std::vector<uint8_t> *)ctx; v->insert(v->end(), (uint8_t *)d, (uint8_t *)d + n); },
                               &out, w, h, 4, raw.data(), quality);
        st_enc_us += (SDL_GetPerformanceCounter() - t0) * 1000000 / SDL_GetPerformanceFrequency();
        {
            std::lock_guard<std::mutex> l(g_vmu);
            if (g_jpeg_ready) st_net_drop++;   // sender did not take the previous one
            g_jpeg.swap(out); g_jpeg_w = w; g_jpeg_h = h; g_jpeg_ready = true;
        }
        g_wake.notify_all();
    }
}

void net_capture_frame(int ww, int wh) {
    if (g_mode != 1 || !g_active.load(std::memory_order_relaxed) || ww <= 0 || wh <= 0) return;
    static bool inited, ok;
    static int fps_cap = env_int("HM_NET_FPS", 30);
    static uint64_t last_t;
    if (!inited) {
        inited = ok = true;
#define LOAD(T, n) n##_ = (T)SDL_GL_GetProcAddress(#n); if (!n##_) ok = false;
        GLF(LOAD)
        if (!ok) fprintf(stderr, "[net] GL functions missing, video capture disabled\n");
    }
    if (!ok) return;
    uint64_t t0 = SDL_GetPerformanceCounter();
    struct Slot { GLuint pbo = 0; GLsync fence = nullptr; int w = 0, h = 0; };
    static Slot slots[3]; static int next_slot;
    static GLuint fbo, rb; static int ow, oh;
    GLint prev_read = 0, prev_draw = 0, prev_pack = 0, prev_rb = 0, prev_align = 4;
    glGetIntegerv_(GL_READ_FRAMEBUFFER_BINDING, &prev_read); glGetIntegerv_(GL_DRAW_FRAMEBUFFER_BINDING, &prev_draw);
    glGetIntegerv_(GL_PIXEL_PACK_BUFFER_BINDING, &prev_pack); glGetIntegerv_(GL_RENDERBUFFER_BINDING, &prev_rb);
    glGetIntegerv_(GL_PACK_ALIGNMENT, &prev_align);
    // 1. harvest finished readbacks (never wait)
    for (int k = 0; k < 3; k++) {
        Slot &s = slots[(next_slot + k) % 3];
        if (!s.fence) continue;
        GLenum r = glClientWaitSync_(s.fence, 0, 0);
        if (r != GL_ALREADY_SIGNALED && r != GL_CONDITION_SATISFIED) continue;
        glDeleteSync_(s.fence); s.fence = nullptr;
        glBindBuffer_(GL_PIXEL_PACK_BUFFER, s.pbo);
        size_t n = (size_t)s.w * s.h * 4;
        if (void *p = glMapBufferRange_(GL_PIXEL_PACK_BUFFER, 0, n, GL_MAP_READ_BIT)) {
            std::unique_lock<std::mutex> l(g_vmu);
            if (g_raw_ready) st_enc_drop++;   // encoder still busy with an older frame: replace it
            g_raw.resize(n); memcpy(g_raw.data(), p, n); g_raw_w = s.w; g_raw_h = s.h; g_raw_ready = true;
            l.unlock(); g_vcv.notify_one();
            glUnmapBuffer_(GL_PIXEL_PACK_BUFFER);
        }
    }
    // 2. start a new readback: downscale-blit the default framebuffer into a small FBO, read it into a PBO
    uint64_t now = now_ms();
    Slot &s = slots[next_slot];
    if (!s.fence && (fps_cap <= 0 || now - last_t >= (uint64_t)(1000 / fps_cap) - 2)) {
        last_t = now;
        int tw = env_int("HM_NET_W", 960), th = env_int("HM_NET_H", 0);
        if (th <= 0) th = (int)((int64_t)tw * wh / ww);
        tw &= ~1; th &= ~1;
        if (!fbo) { glGenFramebuffers_(1, &fbo); glGenRenderbuffers_(1, &rb); for (auto &x : slots) glGenBuffers_(1, &x.pbo); }
        if (tw != ow || th != oh) {
            ow = tw; oh = th;
            glBindRenderbuffer_(GL_RENDERBUFFER, rb);
            glRenderbufferStorage_(GL_RENDERBUFFER, GL_RGBA8, ow, oh);
            glBindFramebuffer_(GL_DRAW_FRAMEBUFFER, fbo);
            glFramebufferRenderbuffer_(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rb);
        }
        GLboolean sc = glIsEnabled_(GL_SCISSOR_TEST);
        if (sc) glDisable_(GL_SCISSOR_TEST);
        glBindFramebuffer_(GL_READ_FRAMEBUFFER, 0);
        glBindFramebuffer_(GL_DRAW_FRAMEBUFFER, fbo);
        glBlitFramebuffer_(0, 0, ww, wh, 0, oh, ow, 0, GL_COLOR_BUFFER_BIT, GL_LINEAR);   // flipped: rows come out top-down
        glBindFramebuffer_(GL_READ_FRAMEBUFFER, fbo);
        glBindBuffer_(GL_PIXEL_PACK_BUFFER, s.pbo);
        if (s.w != ow || s.h != oh) { glBufferData_(GL_PIXEL_PACK_BUFFER, (GLsizeiptr)ow * oh * 4, nullptr, GL_STREAM_READ); s.w = ow; s.h = oh; }
        glPixelStorei_(GL_PACK_ALIGNMENT, 4);
        glReadPixels_(0, 0, ow, oh, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        s.fence = glFenceSync_(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
        if (sc) glEnable_(GL_SCISSOR_TEST);
        next_slot = (next_slot + 1) % 3;
        st_captured++;
    }
    glBindBuffer_(GL_PIXEL_PACK_BUFFER, prev_pack); glBindRenderbuffer_(GL_RENDERBUFFER, prev_rb);
    glBindFramebuffer_(GL_READ_FRAMEBUFFER, prev_read); glBindFramebuffer_(GL_DRAW_FRAMEBUFFER, prev_draw);
    glPixelStorei_(GL_PACK_ALIGNMENT, prev_align);
    st_cap_us += (SDL_GetPerformanceCounter() - t0) * 1000000 / SDL_GetPerformanceFrequency();
    st_cap_n++;
}

// ---------------------------------------------------------------- session
static void sender_thread(Conn *c, std::atomic<bool> *stop) {
    AdpcmState ast[2];
    std::vector<int16_t> pcm; std::vector<uint8_t> abytes, jpeg;
    uint32_t seq = 0;
    uint64_t last_ping = 0, last_stat = now_ms(), t_start = now_ms();
    const size_t max_unsent = (size_t)env_int("HM_NET_MAXQ", 192) * 1024;
    uint64_t s_v0 = 0, s_a0 = 0, s_cap_us0 = 0, s_cap_n0 = 0, s_enc0 = 0; uint32_t s_sent0 = 0, s_cnt0 = 0;
    while (!*stop) {
        {
            std::unique_lock<std::mutex> l(g_mu);
            g_wake.wait_for(l, std::chrono::milliseconds(5));
        }
        uint64_t now = now_ms();
        // audio: 10 ms chunks
        int rate = 0;
        {
            std::lock_guard<std::mutex> g(g_amu);
            rate = g_arate;
            size_t chunk = rate ? (size_t)rate / 100 : 0;
            if (chunk && g_abuf.size() >= chunk * 2) {
                size_t n = g_abuf.size() / (chunk * 2) * chunk * 2;
                pcm.assign(g_abuf.begin(), g_abuf.begin() + n);
                g_abuf.erase(g_abuf.begin(), g_abuf.begin() + n);
            } else pcm.clear();
        }
        for (size_t off = 0; off < pcm.size(); off += (size_t)rate / 100 * 2) {
            int frames = rate / 100;
            AudioHdr h{(uint32_t)rate, (uint16_t)frames, {(int16_t)ast[0].pred, (int16_t)ast[1].pred}, {(uint8_t)ast[0].index, (uint8_t)ast[1].index}};
            abytes.resize(frames);
            adpcm_encode(pcm.data() + off, frames, ast, abytes.data());
            if (!c->send(AUDIO, &h, sizeof h, abytes.data(), abytes.size())) return;
            st_abytes += sizeof h + abytes.size() + 5;
        }
        // video: newest encoded frame, skipped while the socket is backed up
        bool have = false; int w = 0, h = 0;
        {
            std::lock_guard<std::mutex> l(g_vmu);
            if (g_jpeg_ready) { jpeg.swap(g_jpeg); w = g_jpeg_w; h = g_jpeg_h; g_jpeg_ready = false; have = true; }
        }
        if (have) {
            if (c->unsent_bytes() > max_unsent) st_net_drop++;
            else {
                VideoHdr vh{seq++, (uint32_t)(now - t_start), (uint16_t)w, (uint16_t)h};
                if (!c->send(VIDEO, &vh, sizeof vh, jpeg.data(), jpeg.size())) return;
                st_vbytes += sizeof vh + jpeg.size() + 5; st_sent++;
            }
        }
        if (now - last_ping >= 1000) {
            last_ping = now; Ping p{now};
            if (!c->send(PING, &p, sizeof p)) return;
        }
        if (now - last_stat >= 5000) {
            double dt = (now - last_stat) / 1000.0;
            uint32_t sent = st_sent, cnt = st_captured; uint64_t capn = st_cap_n - s_cap_n0;
            int rtt; { std::lock_guard<std::mutex> g(g_mu); rtt = g_rtt; }
            fprintf(stderr, "[net] host: video %.1f fps %.0f kbit/s (%.1f KB/frame, encode %.1f ms), audio %.0f kbit/s, rtt %d ms, "
                            "capture %.0f us/present, dropped enc %u net %u\n",
                    (sent - s_sent0) / dt, (st_vbytes - s_v0) * 8 / 1000.0 / dt,
                    sent > s_sent0 ? (st_vbytes - s_v0) / 1024.0 / (sent - s_sent0) : 0.0,
                    cnt > s_cnt0 ? (st_enc_us - s_enc0) / 1000.0 / (cnt - s_cnt0) : 0.0,
                    (st_abytes - s_a0) * 8 / 1000.0 / dt, rtt, capn ? (double)(st_cap_us - s_cap_us0) / capn : 0.0,
                    st_enc_drop.load(), st_net_drop.load());
            last_stat = now; s_v0 = st_vbytes; s_a0 = st_abytes; s_sent0 = sent; s_cnt0 = cnt; s_cap_us0 = st_cap_us; s_cap_n0 = st_cap_n; s_enc0 = st_enc_us;
        }
    }
}

static void run_session(int fd, const std::string &peer) {
    Conn c; c.fd = fd;
    uint8_t type; std::vector<uint8_t> pl;
    auto bye = [&](const char *why) { c.send(BYE, why, strlen(why)); fprintf(stderr, "[net] rejected %s: %s\n", peer.c_str(), why); c.close(); };
    if (!c.recv(&type, &pl, 10000) || type != HELLO || pl.size() < sizeof(Hello)) return bye("bad handshake");
    Hello h; memcpy(&h, pl.data(), sizeof h);
    h.room[sizeof h.room - 1] = 0; h.name[sizeof h.name - 1] = 0;
    if (h.magic != MAGIC || h.role != 0) return bye("not a guest");
    if (h.version != VERSION) return bye("protocol version mismatch");
    if (g_active) return bye("a guest is already connected");
    std::string room = h.room; for (auto &ch : room) ch = (char)toupper((unsigned char)ch);
    if (!g_net_room.empty() && room != g_net_room) return bye("wrong room code");
    Hello r{}; r.magic = MAGIC; r.version = VERSION; r.role = 1;
    snprintf(r.room, sizeof r.room, "%s", g_net_room.c_str()); snprintf(r.name, sizeof r.name, "%s", g_net_name.c_str());
    if (!c.send(HELLO, &r, sizeof r)) { c.close(); return; }
    {
        std::lock_guard<std::mutex> g(g_mu);
        g_guest_name = h.name; g_rtt = -1; g_pad_valid = false;
    }
    { std::lock_guard<std::mutex> g(g_amu); g_abuf.clear(); }
    g_active = true;
    fprintf(stderr, "[net] guest connected (%s from %s)\n", h.name, peer.c_str());
    std::atomic<bool> stop{false};
    std::thread snd(sender_thread, &c, &stop);
    std::string why = "connection lost";
    while (c.recv(&type, &pl, 15000)) {
        if (type == INPUT && pl.size() >= sizeof(Input)) {
            Input in; memcpy(&in, pl.data(), sizeof in);
            std::lock_guard<std::mutex> g(g_mu);
            g_pad = {in.buttons, in.sx, in.sy, in.cx, in.cy, in.tl, in.tr};
            g_pad_valid = in.connected != 0;
        } else if (type == PING) c.send(PONG, pl.data(), pl.size());
        else if (type == PONG && pl.size() >= sizeof(Ping)) {
            Ping p; memcpy(&p, pl.data(), sizeof p);
            std::lock_guard<std::mutex> g(g_mu); g_rtt = (int)(now_ms() - p.t_ms);
        } else if (type == BYE) { why = "guest left: " + std::string(pl.begin(), pl.end()); break; }
    }
    g_active = false;
    stop = true; g_wake.notify_all();
    c.close();
    snd.join();
    { std::lock_guard<std::mutex> g(g_mu); g_pad_valid = false; }
    fprintf(stderr, "[net] guest disconnected (%s, %s)\n", h.name, why.c_str());
}

static void listen_thread() {
    std::string err;
    int lfd = tcp_listen(g_net_port, &err);
    if (lfd < 0) { fprintf(stderr, "[net] cannot listen on port %d: %s\n", g_net_port, err.c_str()); return; }
    fprintf(stderr, "[net] hosting on port %d%s%s\n", g_net_port, g_net_room.empty() ? "" : ", room ", g_net_room.c_str());
    for (;;) {
        sockaddr_storage sa; socklen_t sl = sizeof sa;
        int fd = accept4(lfd, (sockaddr *)&sa, &sl, SOCK_CLOEXEC);
        if (fd < 0) { usleep(100000); continue; }
        tcp_tune(fd);
        char hbuf[NI_MAXHOST] = "?", pbuf[NI_MAXSERV] = "";
        getnameinfo((sockaddr *)&sa, sl, hbuf, sizeof hbuf, pbuf, sizeof pbuf, NI_NUMERICHOST | NI_NUMERICSERV);
        std::string peer = std::string(hbuf) + ":" + pbuf;
        if (g_active) { std::thread([fd, peer] { run_session(fd, peer); }).detach(); continue; }   // gets "busy"
        std::thread(run_session, fd, peer).detach();
    }
}

static void relay_thread() {
    std::string rh; int rp;
    if (!parse_hostport(g_net_relay, &rh, &rp, 7778)) { fprintf(stderr, "[net] bad --relay %s\n", g_net_relay.c_str()); return; }
    int backoff = 1;
    for (;;) {
        std::string err, line;
        int fd = tcp_connect(rh, rp, &err);
        if (fd < 0) { fprintf(stderr, "[net] relay %s: %s (retry in %d s)\n", g_net_relay.c_str(), err.c_str(), backoff); sleep(backoff); backoff = std::min(backoff * 2, 30); continue; }
        std::string pre = "HMRELAY HOST " + g_net_room + "\n";
        if (!write_all(fd, pre.data(), pre.size()) || !read_line(fd, &line, 10000) || line.compare(0, 3, "OK ") != 0) {
            fprintf(stderr, "[net] relay refused: %s\n", line.c_str()); close(fd); sleep(backoff); backoff = std::min(backoff * 2, 30); continue;
        }
        backoff = 1;
        fprintf(stderr, "[net] relay %s: room code %s (guests: --relay %s --room %s)\n", g_net_relay.c_str(), line.c_str() + 3, g_net_relay.c_str(), line.c_str() + 3);
        // wait for a guest (the relay sends "WAIT" keepalives)
        bool paired = false;
        while (read_line(fd, &line, 120000)) { if (line == "PAIRED") { paired = true; break; } }
        if (!paired) { close(fd); continue; }
        run_session(fd, "relay");
    }
}

void net_host_start() {
    if (g_mode != 1) return;
    std::thread(encoder_thread).detach();
    if (!g_net_relay.empty()) std::thread(relay_thread).detach();
    else std::thread(listen_thread).detach();
}
