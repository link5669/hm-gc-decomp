// Standalone test for hmaudio: drives the module the way the game's SDK does (OS audio init,
// ARInit size probe, DSPInit + __DSP_boot_task with the game's AX ucode from DSPCode.c,
// AXOut's double-buffered frame loop with one looping PCM16 voice from ARAM and one one-shot
// voice), checks mails / interrupts / the rendered buffers, and dumps the AI output to a WAV.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "audio.h"

// ---------------------------------------------------------------- fake runtime
static uint64_t g_now = 1000000;
static uint64_t g_deadline = UINT64_MAX;
static uint32_t g_lines = 0;
extern "C" void rt_pi_line(uint32_t bit, int level) {
  if (level) g_lines |= bit;
  else g_lines &= ~bit;
}
extern "C" uint64_t rt_tb_now(void) { return g_now; }
extern "C" void rt_schedule_audio(uint64_t d) { g_deadline = d; }

static void advance(uint64_t ticks) {
  uint64_t target = g_now + ticks;
  while (g_deadline <= target) {
    if (g_deadline > g_now) g_now = g_deadline;
    g_deadline = UINT64_MAX;
    audio_event(g_now);
  }
  g_now = target;
}

static int g_fail = 0;
#define CHECK(c, ...) do { if (!(c)) { printf("FAIL %s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n"); g_fail++; } } while (0)

// ---------------------------------------------------------------- guest helpers
static uint8_t *ram;
static void w16(uint32_t a, uint16_t v) { a &= 0x1FFFFFF; ram[a] = v >> 8; ram[a + 1] = (uint8_t)v; }
static void w32(uint32_t a, uint32_t v) { w16(a, v >> 16); w16(a + 2, (uint16_t)v); }
static uint16_t r16(uint32_t a) { a &= 0x1FFFFFF; return (uint16_t)((ram[a] << 8) | ram[a + 1]); }
static uint32_t r32(uint32_t a) { return ((uint32_t)r16(a) << 16) | r16(a + 2); }

static uint16_t dsp_r(int reg) { return audio_dsp_read16(0x5000 + reg * 2); }
static void dsp_w(int reg, uint16_t v) { audio_dsp_write16(0x5000 + reg * 2, v); }
static void dsp_w32(int reg, uint32_t v) { dsp_w(reg, v >> 16); dsp_w(reg + 1, (uint16_t)v); }

static void send_mail(uint32_t m) {
  dsp_w(0, m >> 16);
  dsp_w(1, (uint16_t)m);
  CHECK(!(dsp_r(0) & 0x8000), "to-DSP mailbox still full after %08x", m);
}
static bool mail_ready() { return dsp_r(2) & 0x8000; }
static uint32_t read_mail() { uint32_t hi = dsp_r(2); return (hi << 16) | dsp_r(3); }

static void aram_dma(bool to_mram, uint32_t mm, uint32_t ar, uint32_t len) {
  dsp_w32(16, mm);
  dsp_w32(18, ar);
  dsp_w32(20, (to_mram ? 0x80000000u : 0) | len);
  while (dsp_r(5) & 0x200) {}
}

// ---------------------------------------------------------------- guest memory layout
constexpr uint32_t UCODE = 0x80100000;
constexpr uint32_t SPB = 0x80200000;
constexpr uint32_t PB1 = 0x80201000, PB2 = 0x80201100;
constexpr uint32_t CL[2] = {0x80202000, 0x80202400};
constexpr uint32_t SBUF = 0x80203000;
constexpr uint32_t OUTB[2] = {0x80204000, 0x80204400};
constexpr uint32_t AUXW = 0x80206000, AUXR = 0x80206800;
constexpr uint32_t COMP = 0x80207000;
constexpr uint32_t STAGE = 0x80300000;
constexpr uint32_t SINE_AR = 0x10000, SINE_N = 3200;   // byte address / samples
constexpr uint32_t SHOT_AR = 0x20000, SHOT_N = 500;

// ---------------------------------------------------------------- AXOut / AXCL model
static uint32_t cl_out[2];
static uint32_t last_cl_out = 0;
static int cl_pos = 0, out_frame = 0, dsp_ready = 0;
static int frames_sent = 0, aid_ints = 0, dsp_ints = 0;

static void build_cl(uint32_t out) {
  cl_out[cl_pos] = out;
  uint32_t a = CL[cl_pos];
  auto put = [&](uint16_t v) { w16(a, v); a += 2; };
  auto put32 = [&](uint32_t v) { put(v >> 16); put((uint16_t)v); };
  put(0x00); put32(SPB);
  put(0x07); put32(SBUF);
  put(0x02); put32(PB1);
  put(0x03);
  put(0x04); put32(AUXW); put32(AUXR);
  put(0x12); put(0x8000); put(10); put32(COMP);
  put(0x0E); put32(SBUF); put32(out);
  put(0x0F);
}

static void new_frame() {
  uint32_t cl = CL[cl_pos];
  last_cl_out = cl_out[cl_pos];
  cl_pos ^= 1;
  send_mail(0xBABE0180);
  send_mail(cl);
  frames_sent++;
  build_cl(OUTB[out_frame]);
  out_frame ^= 1;
  dsp_w32(24, OUTB[out_frame]);                       // AIInitDMA
  dsp_w(27, (uint16_t)((dsp_r(27) & 0x8000) | (640 >> 5)));
}

static std::vector<int16_t> rendered_l, rendered_r;  // what the DSP wrote, in frame order
static std::vector<int32_t> aux_l;

static void service_interrupts() {
  for (int guard = 0; guard < 16 && (g_lines & 0x40); guard++) {
    uint16_t cr = dsp_r(5);
    if ((cr & 0x08) && (cr & 0x10)) {                 // __AIDHandler
      dsp_w(5, (uint16_t)((cr & ~0xA0) | 0x08));
      aid_ints++;
      if (dsp_ready == 1) { dsp_ready = 0; new_frame(); }
      else dsp_ready = 2;
      continue;
    }
    if ((cr & 0x80) && (cr & 0x100)) {                // __DSPHandler
      dsp_w(5, (uint16_t)((cr & ~0x28) | 0x80));
      dsp_ints++;
      CHECK(mail_ready(), "DSP interrupt without mail");
      uint32_t m = read_mail();
      if (m == 0xDCD10002) {
        // the frame just rendered went to the output buffer named in the list that was sent
        uint32_t lr = last_cl_out;
        for (int i = 0; i < 160; i++) {
          rendered_r.push_back((int16_t)r16(lr + i * 4));
          rendered_l.push_back((int16_t)r16(lr + i * 4 + 2));
          aux_l.push_back((int32_t)r32(AUXW + i * 4));
        }
        send_mail(0xCDD10003);
        if (dsp_ready == 2) { dsp_ready = 0; new_frame(); }
        else dsp_ready = 1;
      } else {
        CHECK(false, "unexpected mail %08x", m);
      }
      continue;
    }
    if ((cr & 0x20) && (cr & 0x40)) { dsp_w(5, (uint16_t)((cr & ~0x88) | 0x20)); continue; }
    break;
  }
}

static std::vector<uint16_t> load_ucode() {
  std::vector<uint16_t> w;
  FILE *f = fopen(HM_DSPCODE_C, "rb");
  if (!f) return w;
  std::string s;
  char buf[4096];
  size_t n;
  while ((n = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, n);
  fclose(f);
  size_t p = s.find('{'), e = s.find("};", p);
  for (size_t i = p; i < e; i++)
    if (s[i] == '0' && s[i + 1] == 'x') { w.push_back((uint16_t)strtoul(&s[i], nullptr, 16)); i += 5; }
  return w;
}

static void write_pb(uint32_t a, uint32_t next, uint16_t mixer, uint32_t ar_samp, uint32_t n, bool loop) {
  for (int i = 0; i < 0xF4; i += 2) w16(a + i, 0);
  w32(a + 0x00, next);
  w32(a + 0x04, a);
  w16(a + 0x08, 1);            // linear SRC
  w16(a + 0x0C, mixer);
  w16(a + 0x0E, 1);            // running
  w16(a + 0x12, 0x8000);       // main L
  w16(a + 0x16, 0x4000);       // main R
  w16(a + 0x1A, 0x2000);       // aux A L
  w16(a + 0x64, 0x7FFF);       // envelope volume
  w16(a + 0x6E, loop ? 1 : 0);
  w16(a + 0x70, 0x0A);         // PCM16
  w32(a + 0x72, ar_samp);      // loop start
  w32(a + 0x76, ar_samp + n - 1);
  w32(a + 0x7A, ar_samp);
  w16(a + 0x9E, 0x0800);       // gain 1.0
  w16(a + 0xA6, 1);            // ratio 1.0
}

int main(int argc, char **argv) {
  const char *wav = argc > 1 ? argv[1] : "audio_test.wav";
  setenv("HM_AUDIO_WAV", wav, 1);
  setenv("HM_AUDIO_MUTE", "1", 0);
  ram = (uint8_t *)calloc(1, 24 << 20);
  audio_init(ram);

  // ---- __OSInitAudioSystem
  dsp_w(9, 0x43);
  dsp_w(5, 0x8AC);
  dsp_w(5, dsp_r(5) | 1);
  CHECK(!(dsp_r(5) & 1), "reset bit stuck");
  dsp_w(0, 0);
  CHECK(!(read_mail() & 0x80000000), "mail visible while halted");
  for (int k = 0; k < 2; k++) {
    dsp_w32(16, 0x1000000); dsp_w32(18, 0); dsp_w32(20, 0x20);
    uint16_t r = dsp_r(5);
    CHECK(r & 0x20, "ARAM DMA did not complete");
    dsp_w(5, r);
    CHECK(!(dsp_r(5) & 0x20), "ARAM status not acked");
  }
  dsp_w(5, dsp_r(5) & ~0x800);
  CHECK(dsp_r(5) & 0x400, "DSPInitCode not set");
  int spins = 0;
  while (dsp_r(5) & 0x400) { advance(10); spins++; }
  dsp_w(5, dsp_r(5) & ~4);
  while (!mail_ready()) advance(10);
  uint32_t m = read_mail();
  CHECK(m == 0x80544348, "init ucode mail %08x", m);
  dsp_w(5, dsp_r(5) | 4);
  dsp_w(5, 0x8AC);
  dsp_w(5, dsp_r(5) | 1);

  // ---- OS interrupt unmask (AI/ARAM/DSP mask bits), AIInit-ish: DSP rate 32 kHz
  dsp_w(5, dsp_r(5) | 0x150);
  audio_ai_write32(0x6C00, 0x40 | 0x20);
  // AI stream sample counter must advance while playing (__AI_SRC_INIT spins on it)
  audio_ai_write32(0x6C00, audio_ai_read32(0x6C00) | 1);
  uint32_t c0 = audio_ai_read32(0x6C08);
  advance(40500);  // 1 ms
  uint32_t c1 = audio_ai_read32(0x6C08);
  CHECK(c1 - c0 >= 31 && c1 - c0 <= 33, "stream counter advanced %u in 1 ms", c1 - c0);
  audio_ai_write32(0x6C00, audio_ai_read32(0x6C00) & ~1u);

  // ---- ARInit: __ARChecksize first probe (no expansion beyond the 16 MiB)
  while (!(dsp_r(11) & 1)) {}
  for (int i = 0; i < 8; i++) { w32(STAGE + i * 4, 0xDEADBEEF); w32(STAGE + 0x20 + i * 4, 0); }
  aram_dma(false, STAGE, 0x1000000, 0x20);
  aram_dma(true, STAGE + 0x20, 0x1000000, 0x20);
  CHECK(r32(STAGE + 0x20) != 0xDEADBEEF, "ARAM mirrors beyond 16 MiB");
  aram_dma(false, STAGE, 0x0, 0x20);
  aram_dma(true, STAGE + 0x20, 0x0, 0x20);
  CHECK(r32(STAGE + 0x20) == 0xDEADBEEF, "ARAM round trip failed");
  CHECK(g_lines & 0x40, "ARAM interrupt line not raised");
  service_interrupts();
  CHECK(!(g_lines & 0x40), "ARAM interrupt line not cleared by ack");

  // ---- samples into ARAM
  std::vector<int16_t> sine(SINE_N), shot(SHOT_N);
  for (uint32_t i = 0; i < SINE_N; i++) sine[i] = (int16_t)lround(20000 * sin(2 * M_PI * i / 80.0));
  for (uint32_t i = 0; i < SHOT_N; i++) shot[i] = (int16_t)(i * 7);
  for (uint32_t i = 0; i < SINE_N; i++) w16(STAGE + i * 2, (uint16_t)sine[i]);
  aram_dma(false, STAGE, SINE_AR, SINE_N * 2);
  for (uint32_t i = 0; i < SHOT_N; i++) w16(STAGE + i * 2, (uint16_t)shot[i]);
  aram_dma(false, STAGE, SHOT_AR, (SHOT_N * 2 + 31) & ~31u);
  service_interrupts();

  // ---- DSPInit + DSPAddTask -> __DSP_boot_task
  uint16_t t = dsp_r(5);
  dsp_w(5, (uint16_t)((t & ~0xA8) | 0x800));
  dsp_w(5, dsp_r(5) & ~0xAC);
  while (!mail_ready()) advance(10);
  m = read_mail();
  CHECK(m == 0x8071FEED, "IROM mail %08x", m);
  std::vector<uint16_t> uc = load_ucode();
  CHECK(uc.size() == 3936, "DSPCode.c parse: %zu words", uc.size());
  for (size_t i = 0; i < uc.size(); i++) w16(UCODE + i * 2, uc[i]);
  uint32_t boot[] = {0x80F3A001, UCODE, 0x80F3C002, 0, 0x80F3A002, (uint32_t)uc.size() * 2,
                     0x80F3B002, 0, 0x80F3D001, 0x10};
  for (uint32_t b : boot) send_mail(b);
  advance(100);
  CHECK(g_lines & 0x40, "no DSP interrupt after boot");
  t = dsp_r(5);
  CHECK(t & 0x80, "DSP status bit not set");
  dsp_w(5, (uint16_t)((t & ~0x28) | 0x80));
  m = read_mail();
  CHECK(m == 0xDCD10000, "AX init mail %08x", m);
  CHECK(!(g_lines & 0x40), "line still up after DSP ack");

  // ---- AX: SPB, PBs, compressor table, AUX return buffer
  for (int i = 0; i < 0x40; i += 2) w16(SPB + i, 0);
  write_pb(PB1, PB2, 0x0003 | 0x0010, SINE_AR / 2, SINE_N, true);
  write_pb(PB2, 0, 0x0000, SHOT_AR / 2, SHOT_N, false);
  for (int i = 0; i < 21 * 160; i++) w16(COMP + i * 2, 0x8000);

  // __AXOutInit (mode 0)
  out_frame = 0;
  build_cl(OUTB[1]);
  dsp_ready = 1;
  dsp_w32(24, OUTB[0]);
  dsp_w(27, 640 >> 5);
  dsp_w(27, dsp_r(27) | 0x8000);   // AIStartDMA

  // run 1 s of guest time
  for (int step = 0; step < 4050; step++) {
    advance(10000);
    service_interrupts();
  }

  // ---- checks
  printf("frames %d, AID ints %d, DSP ints %d, init spins %d\n", frames_sent, aid_ints, dsp_ints, spins);
  CHECK(aid_ints >= 198 && aid_ints <= 202, "AID interrupts per second: %d", aid_ints);
  CHECK(frames_sent >= 198 && frames_sent <= 202, "frames per second: %d", frames_sent);
  size_t n = rendered_l.size();
  int bad = 0;
  for (size_t i = 0; i < n; i++) {
    int32_t in = i >= 3 ? sine[(i - 3) % SINE_N] : 0;
    int32_t v = (in * 0x7FFF) >> 15;
    int32_t el = (v * 0x8000) >> 15, er = (v * 0x4000) >> 15, ea = (v * 0x2000) >> 15;
    if (rendered_l[i] != el || rendered_r[i] != er || aux_l[i] != ea) {
      if (bad < 5) printf("  sample %zu: L %d/%d R %d/%d auxA %d/%d\n", i, rendered_l[i], el, rendered_r[i], er, aux_l[i], ea);
      bad++;
    }
  }
  CHECK(n >= 160 * 198 && bad == 0, "rendered %zu samples, %d mismatches", n, bad);
  CHECK(r16(PB2 + 0x0E) == 0, "one-shot voice still running");
  uint32_t cur = r32(PB1 + 0x7A);
  uint32_t played = (uint32_t)frames_sent * 160;  // ratio 1.0: one input sample per output
  CHECK(cur == SINE_AR / 2 + played % SINE_N, "looping voice cur %08x expected %08x", cur,
        SINE_AR / 2 + played % SINE_N);

  audio_shutdown();
  FILE *f = fopen(wav, "rb");
  long sz = 0;
  if (f) { fseek(f, 0, SEEK_END); sz = ftell(f); fclose(f); }
  printf("WAV %s: %ld bytes (%.3f s at 32 kHz)\n", wav, sz, (sz - 44) / 128000.0);
  CHECK(sz > 44 + 128000 * 9 / 10, "WAV too short");
  printf(g_fail ? "FAILED (%d)\n" : "PASS\n", g_fail);
  return g_fail ? 1 : 0;
}
