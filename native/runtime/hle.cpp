// High-level replacements for a few SDK functions: OSReport/OSPanic (host stderr) and PAD (SDL input).
#include "rt.h"
#include <SDL.h>
#include <string>
#include <vector>

// ---- guest printf ----
static std::string guest_format(CPU *c, u32 fmt, int first_gpr) {
    std::string out;
    int gi = first_gpr, fi = 1;
    auto next_int = [&]() -> u32 { return gi <= 10 ? c->r[gi++] : 0; };
    auto next_dbl = [&]() -> double { return fi <= 8 ? c->f[fi++].d : 0.0; };
    for (int n = 0; n < 4096; n++) {
        char ch = (char)ld8(fmt++);
        if (!ch) break;
        if (ch != '%') { out += ch; continue; }
        std::string spec = "%";
        char t;
        for (;;) {
            t = (char)ld8(fmt++);
            if (!t) return out;
            if (strchr("diouxXcspfFeEgGn%", t)) break;
            if (t != 'l' && t != 'h') spec += t;
        }
        char buf[512];
        switch (t) {
        case '%': out += '%'; continue;
        case 's': {
            u32 p = next_int(); std::string s;
            for (int k = 0; p && k < 1024; k++) { char x = (char)ld8(p + k); if (!x) break; s += x; }
            snprintf(buf, sizeof buf, (spec + "s").c_str(), s.c_str()); break;
        }
        case 'f': case 'F': case 'e': case 'E': case 'g': case 'G':
            snprintf(buf, sizeof buf, (spec + t).c_str(), next_dbl()); break;
        case 'c': snprintf(buf, sizeof buf, (spec + "c").c_str(), (int)next_int()); break;
        case 'p': snprintf(buf, sizeof buf, "0x%08x", next_int()); break;
        case 'n': next_int(); buf[0] = 0; break;
        default: snprintf(buf, sizeof buf, (spec + t).c_str(), next_int()); break;
        }
        out += buf;
    }
    return out;
}
static bool g_report = getenv("HM_REPORT") != nullptr;
extern "C" void hle_OSReport(CPU *RESTRICT c) {
    if (g_report) { std::string s = guest_format(c, c->r[3], 4); fputs(s.c_str(), stderr); }
}
extern "C" void hle_OSPanic(CPU *RESTRICT c) {
    std::string s = guest_format(c, c->r[5], 6);
    std::string file;
    for (u32 p = c->r[3]; p && file.size() < 200; p++) { char x = (char)ld8(p); if (!x) break; file += x; }
    rt_fatal("OSPanic %s:%d: %s", file.c_str(), c->r[4], s.c_str());
}

// ---- pads ----
enum { B_LEFT = 1, B_RIGHT = 2, B_DOWN = 4, B_UP = 8, B_Z = 0x10, B_R = 0x20, B_L = 0x40, B_A = 0x100, B_B = 0x200, B_X = 0x400, B_Y = 0x800, B_START = 0x1000 };
struct PadState { u16 buttons; s8 sx, sy, cx, cy; u8 tl, tr; bool connected; };
static PadState g_pads[4];
static SDL_GameController *g_ctrl[4];

static void open_controllers() {
    int n = 0;
    for (int i = 0; i < SDL_NumJoysticks() && n < 4; i++) {
        if (!SDL_IsGameController(i)) continue;
        SDL_GameController *gc = SDL_GameControllerOpen(i);
        if (gc) { LOG("pad: controller %d = %s\n", n, SDL_GameControllerName(gc)); g_ctrl[n++] = gc; }
    }
}

void pad_poll_host() {
    static bool inited;
    if (!inited) { inited = true; open_controllers(); }
    memset(g_pads, 0, sizeof g_pads);
    // Player 1: keyboard (same layout as the Dolphin setup: X=A Z=B C=X S=Y D=Z Enter=Start arrows, Q/W = L/R,
    // I/J/K/L = C-stick, T/F/G/H = D-pad) plus the first controller. Player 2: second controller
    // (or the first one, when only one is connected and HM_P2_PAD0 is set).
    const u8 *k = SDL_GetKeyboardState(nullptr);
    PadState &p = g_pads[0];
    p.connected = true;
    int x = 0, y = 0;
    if (k[SDL_SCANCODE_LEFT]) x -= 1; if (k[SDL_SCANCODE_RIGHT]) x += 1;
    if (k[SDL_SCANCODE_UP]) y += 1; if (k[SDL_SCANCODE_DOWN]) y -= 1;
    int mag = (k[SDL_SCANCODE_LSHIFT] || k[SDL_SCANCODE_RSHIFT]) ? 50 : 100;
    p.sx = (s8)(x * mag); p.sy = (s8)(y * mag);
    int cx = 0, cy = 0;
    if (k[SDL_SCANCODE_J]) cx -= 100; if (k[SDL_SCANCODE_L]) cx += 100; if (k[SDL_SCANCODE_I]) cy += 100; if (k[SDL_SCANCODE_K]) cy -= 100;
    p.cx = (s8)cx; p.cy = (s8)cy;
    if (k[SDL_SCANCODE_X]) p.buttons |= B_A;
    if (k[SDL_SCANCODE_Z]) p.buttons |= B_B;
    if (k[SDL_SCANCODE_C]) p.buttons |= B_X;
    if (k[SDL_SCANCODE_S]) p.buttons |= B_Y;
    if (k[SDL_SCANCODE_D]) p.buttons |= B_Z;
    if (k[SDL_SCANCODE_RETURN]) p.buttons |= B_START;
    if (k[SDL_SCANCODE_Q]) { p.buttons |= B_L; p.tl = 255; }
    if (k[SDL_SCANCODE_W]) { p.buttons |= B_R; p.tr = 255; }
    if (k[SDL_SCANCODE_T]) p.buttons |= B_UP; if (k[SDL_SCANCODE_G]) p.buttons |= B_DOWN;
    if (k[SDL_SCANCODE_F]) p.buttons |= B_LEFT; if (k[SDL_SCANCODE_H]) p.buttons |= B_RIGHT;

    static const bool p2_pad0 = getenv("HM_P2_PAD0") != nullptr;
    for (int i = 0; i < 4; i++) {
        SDL_GameController *gc = g_ctrl[i];
        if (!gc) continue;
        int slot = i;
        if (p2_pad0) slot = i + 1;
        if (slot > 3) continue;
        PadState &q = g_pads[slot];
        q.connected = true;
        auto ax = [&](SDL_GameControllerAxis a) { return SDL_GameControllerGetAxis(gc, a); };
        auto bt = [&](SDL_GameControllerButton b) { return SDL_GameControllerGetButton(gc, b) != 0; };
        auto st = [](int v, bool inv) { int r = v / 300; if (inv) r = -r; if (r > 100) r = 100; if (r < -100) r = -100; if (r > -12 && r < 12) r = 0; return (s8)r; };
        s8 lx = st(ax(SDL_CONTROLLER_AXIS_LEFTX), false), ly = st(ax(SDL_CONTROLLER_AXIS_LEFTY), true);
        s8 rx = st(ax(SDL_CONTROLLER_AXIS_RIGHTX), false), ry = st(ax(SDL_CONTROLLER_AXIS_RIGHTY), true);
        if (lx || ly) { q.sx = lx; q.sy = ly; }
        if (rx || ry) { q.cx = rx; q.cy = ry; }
        int tl = ax(SDL_CONTROLLER_AXIS_TRIGGERLEFT) / 128, tr = ax(SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / 128;
        if (tl > q.tl) q.tl = (u8)tl; if (tr > q.tr) q.tr = (u8)tr;
        if (tl > 200) q.buttons |= B_L; if (tr > 200) q.buttons |= B_R;
        if (bt(SDL_CONTROLLER_BUTTON_A)) q.buttons |= B_A;
        if (bt(SDL_CONTROLLER_BUTTON_B)) q.buttons |= B_B;
        if (bt(SDL_CONTROLLER_BUTTON_X)) q.buttons |= B_X;
        if (bt(SDL_CONTROLLER_BUTTON_Y)) q.buttons |= B_Y;
        if (bt(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) q.buttons |= B_Z;
        if (bt(SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) { q.buttons |= B_L; q.tl = 255; }
        if (bt(SDL_CONTROLLER_BUTTON_START)) q.buttons |= B_START;
        if (bt(SDL_CONTROLLER_BUTTON_DPAD_UP)) q.buttons |= B_UP;
        if (bt(SDL_CONTROLLER_BUTTON_DPAD_DOWN)) q.buttons |= B_DOWN;
        if (bt(SDL_CONTROLLER_BUTTON_DPAD_LEFT)) q.buttons |= B_LEFT;
        if (bt(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) q.buttons |= B_RIGHT;
    }
    // test hook: HM_AUTOPRESS=frames:mask,... (debug only)
}

void pad_device_event(const SDL_Event &e) {
    if (e.type == SDL_CONTROLLERDEVICEADDED || e.type == SDL_CONTROLLERDEVICEREMOVED) {
        for (auto &g : g_ctrl) if (g) { SDL_GameControllerClose(g); g = nullptr; }
        open_controllers();
    }
}

static u32 g_autopress_frame;
extern u32 g_vi_count;
// HM_SCRIPT="300:A 420:A 600:S 700:D*30" : at PADRead call N press buttons (A B X Y Z S=start U D L R; *n = hold n reads, default 4)
struct ScriptEv { u32 f, hold; u16 b; int pad; s8 sx, sy; };
static s8 g_script_sx[4], g_script_sy[4];
static bool g_script_pad[4];
static u16 script_buttons(u32 frame, int pad) {
    static std::vector<ScriptEv> ev; static bool parsed;
    if (!parsed) {
        parsed = true;
        const char *s = getenv("HM_SCRIPT");
        while (s && *s) {
            while (*s == ' ' || *s == ',') s++;
            if (!*s) break;
            u32 f = strtoul(s, (char **)&s, 10); if (*s == ':') s++;
            int pad = 0;
            if (*s == 'p' && s[1] >= '1' && s[1] <= '4' && s[2] == ':') { pad = s[1] - '1'; s += 3; }
            g_script_pad[pad] = true;
            u16 b = 0; u32 hold = 4; s8 sx = 0, sy = 0;
            while (*s && *s != ' ' && *s != ',' && *s != '*') {
                switch (*s) { case '^': sy = 100; break; case 'v': sy = -100; break; case '<': sx = -100; break; case '>': sx = 100; break; case 'A': b |= B_A; break; case 'B': b |= B_B; break; case 'X': b |= B_X; break; case 'Y': b |= B_Y; break;
                case 'Z': b |= B_Z; break; case 'S': b |= B_START; break; case 'U': b |= B_UP; break; case 'D': b |= B_DOWN; break;
                case 'L': b |= B_LEFT; break; case 'R': b |= B_RIGHT; break; }
                s++;
            }
            if (*s == '*') { s++; hold = strtoul(s, (char **)&s, 10); }
            ev.push_back({f, hold, b, pad, sx, sy});
        }
    }
    u16 b = 0;
    g_script_sx[pad] = g_script_sy[pad] = 0;
    for (auto &e : ev) if (e.pad == pad && frame >= e.f && frame < e.f + e.hold) { b |= e.b; if (e.sx) g_script_sx[pad] = e.sx; if (e.sy) g_script_sy[pad] = e.sy; }
    if (b && getenv("HM_SCRIPT_LOG")) LOG("[script] frame %u buttons %04X\n", frame, b);
    return b;
}
extern "C" void hle_PADRead(CPU *RESTRICT c) {
    u32 st = c->r[3];
    u32 motor = 0;
    g_autopress_frame++;
    for (int i = 0; i < 4; i++, st += 12) {
        PadState &p = g_pads[i];
        for (int b = 0; b < 12; b++) st8(st + b, 0);
        if (i > 0 && !p.connected) { script_buttons(g_vi_count, i); if (g_script_pad[i]) p.connected = true; }
        if (!p.connected) { st8(st + 10, (u8)-1); continue; }
        u16 buttons = p.buttons;
        buttons |= script_buttons(g_vi_count, i);
        if (const char *ap = getenv("HM_AUTOSTART")) {  // press Start periodically (testing)
            int every = atoi(ap); if (every > 0 && i == 0 && (g_autopress_frame % every) < 3) buttons |= B_START;
        }
        st16(st + 0, buttons);
        st8(st + 2, (u8)(g_script_sx[i] ? g_script_sx[i] : p.sx)); st8(st + 3, (u8)(g_script_sy[i] ? g_script_sy[i] : p.sy)); st8(st + 4, (u8)p.cx); st8(st + 5, (u8)p.cy);
        st8(st + 6, p.tl); st8(st + 7, p.tr);
        st8(st + 10, 0);
        motor |= 0x80000000u >> i;
    }
    c->r[3] = motor;
}
extern "C" void hle_PADInit(CPU *RESTRICT c) { c->r[3] = 1; }
extern "C" void hle_PADReset(CPU *RESTRICT c) { c->r[3] = 1; }
extern "C" void hle_PADRecalibrate(CPU *RESTRICT c) { c->r[3] = 1; }
extern "C" void hle_PADControlMotor(CPU *RESTRICT c) { }
extern "C" void hle_return0(CPU *RESTRICT c) { c->r[3] = 0; }
extern "C" void hle_return1(CPU *RESTRICT c) { c->r[3] = 1; }
extern "C" void hle_nop(CPU *RESTRICT c) { }
