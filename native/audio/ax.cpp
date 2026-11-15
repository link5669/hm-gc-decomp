// HLE of the AX DSP microcode (Dolphin SDK 2003 variant, IRAM hash 0xe2136399).
// Command lists (AXCL.c), voice parameter blocks (AXVPB.c AXPB, 0xF4 bytes incl. the LPF),
// sample decoding through the DSP accelerator (ADPCM / PCM8 / PCM16 from ARAM), sample-rate
// conversion, volume envelope, LPF, mixing to main/AUX A/AUX B (L/R/S), AUX callback round trip,
// compressor, and the final interleaved 16-bit output. One frame = 5 ms = 160 samples at 32 kHz.
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "internal.h"

namespace hmaudio {
namespace {

constexpr int SPMS = 32;            // samples per millisecond (AX always mixes at 32 kHz)
constexpr int FRAME = 5 * SPMS;     // 160

// ---- parameter block, field order identical to AXVPB.c's AXPB ----
struct VolData { uint16_t vol, delta; };
struct PB {
  uint16_t next_hi, next_lo, this_hi, this_lo;
  uint16_t src_type, coef_select, mixer_control, running, is_stream;
  // mixer: L, R, AuxA L, AuxA R, AuxB L, AuxB R, AuxB S, S, AuxA S
  VolData main_l, main_r, auxa_l, auxa_r, auxb_l, auxb_r, auxb_s, main_s, auxa_s;
  uint16_t itd_on, itd_hi, itd_lo, itd_shl, itd_shr, itd_tshl, itd_tshr;
  uint16_t upd_num[5], upd_hi, upd_lo;
  int16_t dpop_l, dpop_auxa_l, dpop_auxb_l, dpop_r, dpop_auxa_r, dpop_auxb_r, dpop_s, dpop_auxa_s, dpop_auxb_s;
  int16_t ve_vol, ve_delta;
  uint16_t fir[3];
  uint16_t loop_flag, format, loop_hi, loop_lo, end_hi, end_lo, cur_hi, cur_lo;
  int16_t coefs[16];
  uint16_t gain, pred_scale;
  int16_t yn1, yn2;
  uint16_t ratio_hi, ratio_lo, frac;
  int16_t last[4];
  uint16_t loop_ps;
  int16_t loop_yn1, loop_yn2;
  uint16_t lpf_on;
  int16_t lpf_yn1;
  uint16_t lpf_a0;
  int16_t lpf_b0;
  uint16_t loop_counter;
  uint16_t pad[24];
};
static_assert(sizeof(PB) == 0xF4, "AXPB size");
static_assert(offsetof(PB, main_l) == 0x12 && offsetof(PB, itd_on) == 0x36, "AXPB mix/itd");
static_assert(offsetof(PB, upd_num) == 0x44 && offsetof(PB, ve_vol) == 0x64, "AXPB upd/ve");
static_assert(offsetof(PB, loop_flag) == 0x6E && offsetof(PB, coefs) == 0x7E, "AXPB addr/adpcm");
static_assert(offsetof(PB, ratio_hi) == 0xA6 && offsetof(PB, loop_ps) == 0xB4, "AXPB src/loop");
static_assert(offsetof(PB, lpf_on) == 0xBA, "AXPB lpf");
constexpr int PB_WORDS = sizeof(PB) / 2;

inline uint32_t hilo(uint16_t hi, uint16_t lo) { return ((uint32_t)hi << 16) | lo; }

void read_pb(uint32_t addr, PB &pb) {
  uint16_t *w = reinterpret_cast<uint16_t *>(&pb);
  for (int i = 0; i < PB_WORDS; i++) w[i] = ram_r16(addr + 2 * i);
}
void write_pb(uint32_t addr, const PB &pb) {
  const uint16_t *w = reinterpret_cast<const uint16_t *>(&pb);
  for (int i = 0; i < PB_WORDS; i++) ram_w16(addr + 2 * i, w[i]);
}

inline int16_t clamp16(int64_t v) { return (int16_t)std::clamp<int64_t>(v, -32768, 32767); }

// ---- mixer_control bits of this ucode generation ----
enum : uint32_t {
  M_L = 1u << 0, M_R = 1u << 1, M_S = 1u << 2, M_MAIN_RAMP = 1u << 3,
  M_AL = 1u << 4, M_AR = 1u << 5, M_A_LR_RAMP = 1u << 6, M_AS = 1u << 7, M_AS_RAMP = 1u << 8,
  M_BL = 1u << 9, M_BR = 1u << 10, M_B_LR_RAMP = 1u << 11, M_BS = 1u << 12, M_BS_RAMP = 1u << 13,
};

// ---- DSP accelerator (ARAM sample fetch + ADPCM / PCM decode, loop handling) ----
struct Accel {
  uint32_t start, end, cur;
  uint16_t fmt;
  int16_t gain, yn1, yn2;
  uint16_t ps;
  bool stopped;
  PB *pb;

  uint8_t aram8(uint32_t a) const { return g_aram[a & ARAM_MASK]; }

  void setup(PB &p) {
    pb = &p;
    start = hilo(p.loop_hi, p.loop_lo) & 0x3FFFFFFF;
    end = hilo(p.end_hi, p.end_lo) & 0x3FFFFFFF;
    cur = hilo(p.cur_hi, p.cur_lo) & 0xBFFFFFFF;
    fmt = p.format;
    yn1 = p.yn1;
    yn2 = p.yn2;
    stopped = false;
    gain = (int16_t)p.gain;
    ps = p.pred_scale & 0x7F;
  }

  uint16_t raw() const {
    switch (fmt & 3) {
    case 0: { uint8_t b = aram8(cur >> 1); return (cur & 1) ? (b & 0xF) : (b >> 4); }
    case 1: return aram8(cur);
    case 2: return (uint16_t)((aram8(cur * 2) << 8) | aram8(cur * 2 + 1));
    default: return 0;
    }
  }

  void end_reached() {
    if (pb->loop_flag) {
      ps = pb->loop_ps & 0x7F;
      if (pb->is_stream != 1) {
        yn1 = pb->loop_yn1;
        yn2 = pb->loop_yn2;
      } else {
        pb->loop_counter++;
      }
      stopped = false;
    } else {
      pb->running = 0;
    }
  }

  int16_t sample() {
    if (stopped) return 0;
    const uint32_t decode = (fmt >> 2) & 3, gscale = (fmt >> 4) & 3;
    int16_t rs = (decode == 1 || decode == 3) ? 0 : (int16_t)raw();  // MMIO input: unused by AX
    const int ci = (ps >> 4) & 7;
    const int32_t c1 = pb->coefs[ci * 2], c2 = pb->coefs[ci * 2 + 1];
    int16_t out;
    uint32_t step = 2;
    if (decode == 0) {  // ADPCM
      int32_t nib = rs & 0xF;
      if (nib >= 8) nib -= 16;
      int32_t v = nib * (1 << (ps & 0xF)) +((0x400 + c1 * yn1 + c2 * yn2) >> 11);
      out = clamp16(v);
      yn2 = yn1;
      yn1 = out;
      cur += 1;
      if ((end & 0xF) == 0 && cur == end) {
        cur = start + 1;
      } else if ((end & 0xF) == 1 && cur == end - 1) {
        cur = start;
      } else if ((cur & 0xF) == 0) {
        ps = aram8((cur & ~0xFu) >> 1) & 0x7F;
        cur += 2;
        step += 2;
      }
    } else {  // PCM
      int sh = gscale == 0 ? 11 : gscale == 1 ? 0 : gscale == 2 ? 16 : 0;
      int32_t v = (((int32_t)gain * rs) >> sh) + ((c1 * yn1) >> sh) + ((c2 * yn2) >> sh);
      out = (int16_t)v;
      yn2 = yn1;
      yn1 = out;
      if (decode != 1) cur += 1;
    }
    if (cur == end + step - 1) {
      cur = start;
      stopped = true;
      end_reached();
    }
    cur &= 0xBFFFFFFF;
    return out;
  }
};

// ---- polyphase SRC coefficients: 4 tables (coef_select) x 128 phases x 4 taps ----
int16_t g_coefs[4 * 128 * 4];

void gen_coefs() {
  const double cutoff[4] = {1.0, 0.85, 0.7, 0.55};
  for (int t = 0; t < 4; t++) {
    for (int p = 0; p < 128; p++) {
      double frac = p / 128.0, c[4], sum = 0;
      for (int j = 0; j < 4; j++) {
        double d = j - (1.0 + frac);  // interpolate between the 2nd and 3rd newest-oldest taps
        double x = M_PI * cutoff[t] * d;
        double s = std::fabs(d) < 1e-9 ? 1.0 : std::sin(x) / x;
        double wx = M_PI * d / 2.0;
        double w = std::fabs(d) >= 2.0 ? 0.0 : (std::fabs(d) < 1e-9 ? 1.0 : std::sin(wx) / wx);
        c[j] = s * w;
        sum += c[j];
      }
      for (int j = 0; j < 4; j++)
        g_coefs[(t * 128 + p) * 4 + j] = (int16_t)std::clamp(std::lround(c[j] / sum * 32767.0), -32768L, 32767L);
    }
  }
}

// ---- the ucode state ----
enum class MState { CmdListSize, CmdListAddr };
struct AX {
  MState st = MState::CmdListSize;
  uint16_t cl_size = 0;
  uint16_t cl[1024];
  int32_t buf[9][FRAME];   // main L R S, auxA L R S, auxB L R S
  uint32_t comp_pos = 0;
} A;

enum { ML, MR, MS, AL, AR, AS, BL, BR, BS };

void copy_cl(uint32_t addr, uint32_t words) {
  if (words > 1024) {
    log("AX command list at %08x too large (%u)", addr, words);
    words = 1024;
  }
  for (uint32_t i = 0; i < words; i++) A.cl[i] = ram_r16(addr + 2 * i);
}

void up32(uint32_t addr, const int32_t *src, int n) {
  for (int i = 0; i < n; i++) ram_w32(addr + 4 * i, (uint32_t)src[i]);
}
int32_t rd32(uint32_t addr, int i) { return (int32_t)ram_r32(addr + 4 * i); }

void cmd_setup(uint32_t addr) {
  for (int c = 0; c < 9; c++) {
    int32_t v = (int32_t)hilo(ram_r16(addr + c * 6), ram_r16(addr + c * 6 + 2));
    int16_t d = (int16_t)ram_r16(addr + c * 6 + 4);
    for (int j = 0; j < FRAME; j++) A.buf[c][j] = v ? v + j * d : 0;
  }
}

// Resampler: same tap/history conventions as the ucode (4-sample history in the PB).
template <class F>
uint32_t resample(F next, int16_t *out, int count, int16_t *last, uint32_t pos, uint32_t ratio, int type,
                  const int16_t *coefs) {
  if (type == 2) {  // no conversion
    for (int i = 0; i < count; i++) out[i] = next();
    for (int i = 0; i < 4; i++) last[i] = out[count - 4 + i];
    return pos;
  }
  int16_t h[4] = {last[0], last[1], last[2], last[3]};
  uint32_t idx = 4;
  for (int i = 0; i < count; i++) {
    pos += ratio;
    while (pos >= 0x10000) {
      h[idx++ & 3] = next();
      pos -= 0x10000;
    }
    int16_t s0 = h[idx & 3], s1 = h[(idx + 1) & 3], s2 = h[(idx + 2) & 3], s3 = h[(idx + 3) & 3];
    if (type == 0) {
      const int16_t *c = coefs + (((pos & 0xFFFF) >> 9) << 2);
      int64_t v = ((int64_t)s0 * c[0] + (int64_t)s1 * c[1] + (int64_t)s2 * c[2] + (int64_t)s3 * c[3]) >> 15;
      out[i] = clamp16(v);
    } else {
      uint16_t f = pos & 0xFFFF;
      if (f) out[i] = (int16_t)(((int32_t)s0 * (uint16_t)(0x10000 - f) + (int32_t)s1 * f) >> 16);
      else out[i] = s0;
    }
  }
  // history: oldest first, newest last
  for (int i = 0; i < 4; i++) last[i] = h[(idx + i) & 3];
  return pos;
}

void mix(int32_t *out, const int16_t *in, int n, VolData &vd, int16_t &dpop, bool on, bool ramp) {
  if (!on) return;
  uint16_t vol = vd.vol;
  const uint16_t delta = ramp ? vd.delta : 0;
  for (int i = 0; i < n; i++) {
    int16_t s = clamp16(((int64_t)in[i] * vol) >> 15);
    out[i] += s;
    vol = (uint16_t)(vol + delta);
    dpop = s;
  }
  vd.vol = vol;
}

void process_voice_ms(PB &pb, int32_t *const *b) {
  if (pb.running != 1) return;
  int16_t s[SPMS];
  Accel acc;
  acc.setup(pb);
  const int16_t *coefs = g_coefs + (pb.coef_select & 3) * 0x200;
  uint32_t pos = resample([&] { return acc.sample(); }, s, SPMS, pb.last, pb.frac,
                          hilo(pb.ratio_hi, pb.ratio_lo), pb.src_type, coefs);
  pb.frac = (uint16_t)pos;
  pb.cur_hi = (uint16_t)(acc.cur >> 16);
  pb.cur_lo = (uint16_t)acc.cur;
  pb.yn1 = acc.yn1;
  pb.yn2 = acc.yn2;
  pb.pred_scale = acc.ps;

  for (int i = 0; i < SPMS; i++) {
    s[i] = clamp16(((int32_t)s[i] * (int32_t)pb.ve_vol) >> 15);
    pb.ve_vol = (int16_t)(pb.ve_vol + pb.ve_delta);
  }
  if (pb.lpf_on) {
    for (int i = 0; i < SPMS; i++)
      pb.lpf_yn1 = s[i] = clamp16(((int32_t)pb.lpf_a0 * s[i] + (int32_t)pb.lpf_b0 * pb.lpf_yn1) >> 15);
  }
  const uint32_t mc = pb.mixer_control;
  const bool mr = mc & M_MAIN_RAMP, ar = mc & M_A_LR_RAMP, br = mc & M_B_LR_RAMP;
  mix(b[ML], s, SPMS, pb.main_l, pb.dpop_l, mc & M_L, mr);
  mix(b[MR], s, SPMS, pb.main_r, pb.dpop_r, mc & M_R, mr);
  mix(b[MS], s, SPMS, pb.main_s, pb.dpop_s, mc & M_S, mr);
  mix(b[AL], s, SPMS, pb.auxa_l, pb.dpop_auxa_l, mc & M_AL, ar);
  mix(b[AR], s, SPMS, pb.auxa_r, pb.dpop_auxa_r, mc & M_AR, ar);
  mix(b[AS], s, SPMS, pb.auxa_s, pb.dpop_auxa_s, mc & M_AS, mc & M_AS_RAMP);
  mix(b[BL], s, SPMS, pb.auxb_l, pb.dpop_auxb_l, mc & M_BL, br);
  mix(b[BR], s, SPMS, pb.auxb_r, pb.dpop_auxb_r, mc & M_BR, br);
  mix(b[BS], s, SPMS, pb.auxb_s, pb.dpop_auxb_s, mc & M_BS, mc & M_BS_RAMP);
  // Initial time delay (ITD, pb.itd_*) is not emulated.
}

void cmd_process(uint32_t pb_addr) {
  for (int guard = 0; pb_addr && guard < 256; guard++) {
    PB pb;
    read_pb(pb_addr, pb);
    // parameter updates: up to 32 (offset, value) pairs spread over the 5 ms
    uint16_t upd[64];
    uint32_t ua = hilo(pb.upd_hi, pb.upd_lo);
    for (int i = 0; i < 64; i++) upd[i] = ram_r16(ua + 2 * i);
    uint16_t nums[5];
    memcpy(nums, pb.upd_num, sizeof(nums));
    uint32_t first = 0;
    for (int ms = 0; ms < 5; ms++) {
      uint32_t n = nums[ms];
      if (first < 32 && n <= 32 - first) {
        for (uint32_t i = first; i < first + n; i++) {
          uint16_t off = upd[2 * i], val = upd[2 * i + 1];
          if (off < PB_WORDS) reinterpret_cast<uint16_t *>(&pb)[off] = val;
        }
      }
      first += n;
      int32_t *b[9];
      for (int c = 0; c < 9; c++) b[c] = A.buf[c] + ms * SPMS;
      process_voice_ms(pb, b);
    }
    write_pb(pb_addr, pb);
    pb_addr = hilo(pb.next_hi, pb.next_lo);
  }
}

// AUX A / AUX B: send the aux bus to the CPU (write_addr, 3 x 160 s32), then add what the CPU
// returned for the previous frames (read_addr, L R S) into main.
void cmd_mix_aux(int aux, uint32_t write_addr, uint32_t read_addr) {
  int base = aux ? BL : AL;
  if (write_addr)
    for (int c = 0; c < 3; c++) up32(write_addr + c * FRAME * 4, A.buf[base + c], FRAME);
  for (int c = 0; c < 3; c++)
    for (int i = 0; i < FRAME; i++) A.buf[ML + c][i] += rd32(read_addr + c * FRAME * 4, i);
}

void cmd_output(uint32_t s_addr, uint32_t lr_addr) {
  up32(s_addr, A.buf[MS], FRAME);
  for (int i = 0; i < FRAME; i++) {
    ram_w16(lr_addr + i * 4 + 0, (uint16_t)clamp16(A.buf[MR][i]));
    ram_w16(lr_addr + i * 4 + 2, (uint16_t)clamp16(A.buf[ML][i]));
  }
}

void cmd_compressor(uint16_t threshold, uint16_t release, uint32_t table) {
  bool hit = false;
  for (int i = 0; i < FRAME && !hit; i++)
    hit = std::abs(A.buf[ML][i]) > (int)threshold || std::abs(A.buf[MR][i]) > (int)threshold;
  uint32_t entry;
  if (hit) {
    entry = A.comp_pos;       // attack ramp chosen by the previous state
    A.comp_pos = release;
  } else if (A.comp_pos) {
    A.comp_pos--;
    entry = 11 + A.comp_pos;  // release ramps follow the 11 attack ramps
  } else {
    return;
  }
  uint32_t a = table + entry * FRAME * 2;
  for (int i = 0; i < FRAME; i++) {
    uint16_t c = ram_r16(a + 2 * i);
    A.buf[ML][i] = (int32_t)(((int64_t)A.buf[ML][i] * c) >> 15);
    A.buf[MR][i] = (int32_t)(((int64_t)A.buf[MR][i] * c) >> 15);
  }
}

void run_cmdlist() {
  uint32_t i = 0;
  auto w = [&]() -> uint16_t { return i < 1024 ? A.cl[i++] : 0x0F; };
  auto a32 = [&]() -> uint32_t { uint16_t h = w(); return hilo(h, w()); };
  uint32_t pb_addr = 0;
  for (int guard = 0; guard < 4096; guard++) {
    uint16_t cmd = w();
    switch (cmd) {
    case 0x00: cmd_setup(a32()); break;
    case 0x01: {  // download main/auxA/auxB (3 x L R S) and mix with volumes
      uint32_t a = a32();
      uint16_t vol[3] = {w(), w(), w()};
      for (int bus = 0; bus < 3; bus++)
        for (int c = 0; c < 3; c++)
          for (int k = 0; k < FRAME; k++)
            A.buf[bus * 3 + c][k] += (int32_t)(((int64_t)rd32(a, c * FRAME + k) * vol[bus]) >> 15);
      break;
    }
    case 0x02: pb_addr = a32(); break;
    case 0x03: cmd_process(pb_addr); break;
    case 0x04: case 0x05: { uint32_t wa = a32(); uint32_t ra = a32(); cmd_mix_aux(cmd - 4, wa, ra); break; }
    case 0x06: {  // upload main L R S
      uint32_t a = a32();
      for (int c = 0; c < 3; c++) up32(a + c * FRAME * 4, A.buf[ML + c], FRAME);
      break;
    }
    case 0x07: case 0x11: {  // main L/R from a mono (surround) buffer; 0x11: L inverted
      uint32_t a = a32();
      for (int k = 0; k < FRAME; k++) {
        int32_t v = rd32(a, k);
        A.buf[ML][k] = cmd == 0x11 ? -v : v;
        A.buf[MR][k] = v;
        A.buf[MS][k] = 0;
      }
      break;
    }
    case 0x08: i += 10; break;
    case 0x09: cmd_mix_aux(1, 0, a32()); break;
    case 0x0A: case 0x0B: case 0x0C: break;
    case 0x0D: { uint32_t a = a32(); uint16_t n = w(); copy_cl(a, n); i = 0; break; }
    case 0x0E: { uint32_t sa = a32(); uint32_t lr = a32(); cmd_output(sa, lr); break; }
    case 0x0F: return;
    case 0x10: {  // DPL2: upload AUX B L/R, replace them with the CPU's and add to main L/R
      uint32_t ul = a32(), dl = a32();
      up32(ul, A.buf[BL], FRAME);
      up32(ul + FRAME * 4, A.buf[BR], FRAME);
      for (int k = 0; k < FRAME; k++) {
        int32_t l = rd32(dl, k), r = rd32(dl, FRAME + k);
        A.buf[BL][k] = l; A.buf[ML][k] += l;
        A.buf[BR][k] = r; A.buf[MR][k] += r;
      }
      break;
    }
    case 0x12: { uint16_t th = w(); uint16_t fr = w(); cmd_compressor(th, fr, a32()); break; }
    case 0x13: {  // DPL2: upload AUX A L R S + AUX B S, download main L, main R, AUX B L, AUX B R
      uint32_t up_a = a32(), up_bs = a32();
      uint32_t dl[4];
      for (auto &d : dl) d = a32();
      for (int c = 0; c < 3; c++) up32(up_a + c * FRAME * 4, A.buf[AL + c], FRAME);
      up32(up_bs, A.buf[BS], FRAME);
      const int dst[4] = {ML, MR, BL, BR};
      for (int j = 0; j < 4; j++)
        for (int k = 0; k < FRAME; k++) A.buf[dst[j]][k] += rd32(dl[j], k);
      break;
    }
    default:
      log("AX: unknown command %04x at %u", cmd, i - 1);
      return;
    }
  }
}

} // namespace

void ax_load_coefs() {
  gen_coefs();
  // Optional: the real DSP ROM table (0x800 big-endian s16) if the user supplies one.
  if (const char *p = getenv("HM_DSP_COEF")) {
    if (FILE *f = fopen(p, "rb")) {
      uint8_t raw[0x1000];
      if (fread(raw, 1, sizeof(raw), f) == sizeof(raw)) {
        for (int i = 0; i < 0x800; i++) g_coefs[i] = (int16_t)((raw[2 * i] << 8) | raw[2 * i + 1]);
        log("using SRC coefficients from %s", p);
      }
      fclose(f);
    }
  }
}

void ax_reset() {
  A.st = MState::CmdListSize;
  A.cl_size = 0;
  memset(A.buf, 0, sizeof(A.buf));
  A.comp_pos = 0;
}

bool ax_mail(uint32_t mail) {
  if (A.st == MState::CmdListSize) {
    if ((mail >> 16) == 0xBABE) {
      A.cl_size = (uint16_t)mail;
      A.st = MState::CmdListAddr;
    } else {
      log("AX: unexpected mail %08x (expected BABExxxx)", mail);
    }
    return false;
  }
  copy_cl(mail, A.cl_size);
  run_cmdlist();
  A.st = MState::CmdListSize;
  // Frame done: yield to the CPU's task manager. A small delay stands in for DSP run time.
  dsp_push_mail(0xDCD10002, true, 2000);
  return true;
}

} // namespace hmaudio
