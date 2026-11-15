// Audio interface: AI DMA (DSP block 0x5030..0x503A, played at the AIDFR rate and signalled
// with the DSP_CR AID bit), the AI register block (0x6C00: control, volume, stream sample
// counter, interrupt timing -> PI line 0x20) and the host output (SDL2 queue + optional WAV dump).
#include <SDL.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "internal.h"

namespace hmaudio {
namespace {

enum : uint32_t {
  AICR_PSTAT = 1u << 0, AICR_AISFR = 1u << 1, AICR_INTMSK = 1u << 2, AICR_INT = 1u << 3,
  AICR_INTVLD = 1u << 4, AICR_SCRESET = 1u << 5, AICR_AIDFR = 1u << 6,
};

struct State {
  // AI DMA registers + engine
  uint32_t dma_start = 0;   // 0x5030/0x5032
  uint16_t dma_ctrl = 0;    // 0x5036: bit 15 enable, 14..0 length in 32-byte blocks
  uint16_t dma_blen = 0;    // 0x5034 (unused by the hardware model)
  bool dma_on = false;
  uint32_t dma_cur = 0;
  uint32_t dma_left = 0;
  uint64_t dma_next = 0;    // time base at which the current 32-byte block has been played

  // AI registers
  uint32_t cr = 0;
  uint32_t vol = 0;
  uint32_t scnt_base = 0;
  uint64_t scnt_t0 = 0;
  uint32_t it = 0;
  bool it_fired = false;
  bool line = false;
} S;

uint32_t dsp_rate() { return (S.cr & AICR_AIDFR) ? 32000 : 48000; }
uint32_t stream_rate() { return (S.cr & AICR_AISFR) ? 48000 : 32000; }
uint64_t block_period() { return 8 * TB_HZ / dsp_rate(); }  // 8 stereo frames per block

// ---------------------------------------------------------------- host output
struct Output {
  bool sdl = false;
  SDL_AudioDeviceID dev = 0;
  SDL_AudioStream *stream = nullptr;
  uint32_t stream_in_rate = 0;
  bool started = false;
  FILE *wav = nullptr;
  uint32_t wav_rate = 0;
  uint64_t wav_bytes = 0;
  std::vector<int16_t> tmp;
} O;

constexpr int DEV_RATE = 48000;

void wav_header(FILE *f, uint32_t rate, uint32_t bytes) {
  auto u32 = [&](uint32_t v) { uint8_t b[4] = {(uint8_t)v, (uint8_t)(v >> 8), (uint8_t)(v >> 16), (uint8_t)(v >> 24)}; fwrite(b, 1, 4, f); };
  auto u16 = [&](uint16_t v) { uint8_t b[2] = {(uint8_t)v, (uint8_t)(v >> 8)}; fwrite(b, 1, 2, f); };
  fwrite("RIFF", 1, 4, f); u32(36 + bytes); fwrite("WAVEfmt ", 1, 8, f);
  u32(16); u16(1); u16(2); u32(rate); u32(rate * 4); u16(4); u16(16);
  fwrite("data", 1, 4, f); u32(bytes);
}

void out_open() {
  if (const char *w = getenv("HM_AUDIO_WAV")) {
    O.wav = fopen(w, "wb");
    if (O.wav) wav_header(O.wav, 32000, 0);
    else log("cannot open WAV dump %s", w);
  }
  const char *mute = getenv("HM_AUDIO_MUTE");
  if (mute && *mute && *mute != '0') return;
  if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
    log("SDL audio init failed: %s", SDL_GetError());
    return;
  }
  SDL_AudioSpec want{}, have{};
  want.freq = DEV_RATE;
  want.format = AUDIO_S16SYS;
  want.channels = 2;
  want.samples = 512;
  O.dev = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
  if (!O.dev) {
    log("SDL_OpenAudioDevice failed: %s", SDL_GetError());
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    return;
  }
  O.sdl = true;
}

void out_close() {
  if (O.sdl) {
    SDL_CloseAudioDevice(O.dev);
    if (O.stream) SDL_FreeAudioStream(O.stream);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
  }
  if (O.wav) {
    fseek(O.wav, 0, SEEK_SET);
    wav_header(O.wav, O.wav_rate ? O.wav_rate : 32000, (uint32_t)O.wav_bytes);
    fclose(O.wav);
  }
  O = Output();
}

// frames: interleaved host-endian L R
void out_push(const int16_t *lr, int frames, uint32_t rate) {
  if (O.wav) {
    if (!O.wav_rate) O.wav_rate = rate;
    for (int i = 0; i < frames * 2; i++) {
      uint8_t b[2] = {(uint8_t)lr[i], (uint8_t)((uint16_t)lr[i] >> 8)};
      fwrite(b, 1, 2, O.wav);
    }
    O.wav_bytes += (uint64_t)frames * 4;
  }
  if (!O.sdl) return;
  if (!O.stream || O.stream_in_rate != rate) {
    if (O.stream) SDL_FreeAudioStream(O.stream);
    O.stream = SDL_NewAudioStream(AUDIO_S16SYS, 2, (int)rate, AUDIO_S16SYS, 2, DEV_RATE);
    O.stream_in_rate = rate;
    if (!O.stream) return;
  }
  SDL_AudioStreamPut(O.stream, lr, frames * 4);
  int avail = SDL_AudioStreamAvailable(O.stream);
  if (avail <= 0) return;
  O.tmp.resize((size_t)avail / 2);
  int got = SDL_AudioStreamGet(O.stream, O.tmp.data(), avail);
  if (got <= 0) return;
  const uint32_t queued = SDL_GetQueuedAudioSize(O.dev);
  const uint32_t max_q = DEV_RATE * 4 / 6;   // ~170 ms: drop when the guest runs ahead
  if (queued < max_q) SDL_QueueAudio(O.dev, O.tmp.data(), (uint32_t)got);
  if (!O.started && SDL_GetQueuedAudioSize(O.dev) >= (uint32_t)DEV_RATE * 4 / 25) {  // 40 ms primed
    SDL_PauseAudioDevice(O.dev, 0);
    O.started = true;
  }
}

// ---------------------------------------------------------------- AI DMA engine
void dma_play_block() {
  int16_t lr[16];
  for (int i = 0; i < 8; i++) {
    // AI DMA data: big-endian 16-bit pairs, right channel first
    int16_t r = (int16_t)ram_r16(S.dma_cur + i * 4);
    int16_t l = (int16_t)ram_r16(S.dma_cur + i * 4 + 2);
    lr[2 * i] = l;
    lr[2 * i + 1] = r;
  }
  out_push(lr, 8, dsp_rate());
}

void dma_reload() {
  S.dma_cur = S.dma_start;
  S.dma_left = S.dma_ctrl & 0x7FFF;
}

void dma_advance(uint64_t now) {
  if (!S.dma_on) return;
  const uint64_t per = block_period();
  if (now > S.dma_next + TB_HZ / 5) S.dma_next = now - per;  // far behind (stall): don't replay
  while (S.dma_next <= now) {
    dma_play_block();
    if (S.dma_left) {
      S.dma_left--;
      S.dma_cur += 32;
    }
    if (S.dma_left == 0) {
      dma_reload();
      dsp_raise(CR_AID);
    }
    S.dma_next += per;
  }
}

// ---------------------------------------------------------------- AI stream counter
uint32_t scnt(uint64_t now) {
  if (!(S.cr & AICR_PSTAT)) return S.scnt_base;
  return S.scnt_base + (uint32_t)((now - S.scnt_t0) * stream_rate() / TB_HZ);
}

void scnt_rebase(uint64_t now, uint32_t v) {
  S.scnt_base = v;
  S.scnt_t0 = now;
  S.it_fired = false;
}

void ai_update_line() {
  bool on = (S.cr & AICR_INT) && (S.cr & AICR_INTMSK);
  if (on != S.line) {
    S.line = on;
    rt_pi_line(0x20, on ? 1 : 0);
  }
}

uint64_t it_deadline() {
  if (!(S.cr & AICR_PSTAT) || S.it_fired) return UINT64_MAX;
  uint32_t dist = S.it - S.scnt_base;
  return S.scnt_t0 + ((uint64_t)dist * TB_HZ + stream_rate() - 1) / stream_rate();
}

void stream_service(uint64_t now) {
  uint64_t d = it_deadline();
  if (d != UINT64_MAX && now >= d) {
    S.it_fired = true;
    S.cr |= AICR_INT;
    ai_update_line();
  }
}

} // namespace

void ai_reset() {
  out_close();
  S = State();
  out_open();
}

void ai_shutdown() { out_close(); }

void ai_dsp_reset() {
  dma_advance(rt_tb_now());
  S.dma_ctrl = 0;
  S.dma_on = false;
}

void ai_service(uint64_t now) {
  dma_advance(now);
  stream_service(now);
}

uint64_t ai_next_deadline(uint64_t now) {
  uint64_t d = UINT64_MAX;
  if (S.dma_on) {
    // next reload (the AID interrupt) happens when the last remaining block has been played
    uint64_t n = S.dma_left ? S.dma_left - 1 : 0;
    d = S.dma_next + n * block_period();
  }
  uint64_t t = it_deadline();
  if (t < d) d = t;
  if (d != UINT64_MAX && d <= now) d = now + 1;
  return d;
}

void ai_dma_write16(uint32_t off, uint16_t v) {
  uint64_t now = rt_tb_now();
  dma_advance(now);
  switch (off) {
  case 0x5030: S.dma_start = (S.dma_start & 0xFFFF) | ((uint32_t)(v & 0x03FF) << 16); break;
  case 0x5032: S.dma_start = (S.dma_start & 0xFFFF0000) | (v & 0xFFE0); break;
  case 0x5034: S.dma_blen = v; break;
  case 0x5036: {
    bool was = (S.dma_ctrl & 0x8000) != 0;
    S.dma_ctrl = v;
    if (!was && (v & 0x8000)) {
      S.dma_on = true;
      dma_reload();
      S.dma_next = now + block_period();
      dsp_raise(CR_AID);   // the AI latched the buffer: the CPU may queue the next one
    } else if (was && !(v & 0x8000)) {
      S.dma_on = false;
    }
    break;
  }
  default: break;
  }
  reschedule();
}

uint16_t ai_dma_read16(uint32_t off) {
  dma_advance(rt_tb_now());
  switch (off) {
  case 0x5030: return (uint16_t)(S.dma_start >> 16);
  case 0x5032: return (uint16_t)S.dma_start;
  case 0x5034: return S.dma_blen;
  case 0x5036: return S.dma_ctrl;
  case 0x503A: return (uint16_t)(S.dma_left ? S.dma_left - 1 : 0);
  default: return 0;
  }
}

} // namespace hmaudio

using namespace hmaudio;

extern "C" uint32_t audio_ai_read32(uint32_t off) {
  uint64_t now = rt_tb_now();
  ai_service(now);
  switch (off & 0xFFFF) {
  case 0x6C00: return S.cr;
  case 0x6C04: return S.vol;
  case 0x6C08: return scnt(now);
  case 0x6C0C: return S.it;
  default: return 0;
  }
}

extern "C" void audio_ai_write32(uint32_t off, uint32_t v) {
  uint64_t now = rt_tb_now();
  ai_service(now);
  switch (off & 0xFFFF) {
  case 0x6C00: {
    uint32_t cnt = scnt(now);
    if ((v ^ S.cr) & AICR_AIDFR) {
      // DMA rate change: keep the current block's remaining time proportional
      dma_advance(now);
    }
    uint32_t keep_int = S.cr & AICR_INT;
    if (v & AICR_INT) keep_int = 0;   // write 1 to clear
    bool pstat_change = ((v ^ S.cr) & AICR_PSTAT) != 0;
    bool rate_change = ((v ^ S.cr) & AICR_AISFR) != 0;
    S.cr = (v & (AICR_PSTAT | AICR_AISFR | AICR_INTMSK | AICR_INTVLD | AICR_AIDFR)) | keep_int;
    if (v & AICR_SCRESET) scnt_rebase(now, 0);
    else if (pstat_change || rate_change) { scnt_rebase(now, cnt); S.it_fired = false; }
    ai_update_line();
    break;
  }
  case 0x6C04: S.vol = v; break;   // streaming (DTK) volume: no stream source is emulated
  case 0x6C08: scnt_rebase(now, v); break;
  case 0x6C0C: S.it = v; S.it_fired = false; break;
  default: break;
  }
  stream_service(now);
  reschedule();
}
