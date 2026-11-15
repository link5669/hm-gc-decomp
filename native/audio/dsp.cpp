// DSP register block (0xCC005000): mailboxes, DSP_CR, ARAM controller + ARAM DMA, and the HLE
// microcode dispatcher (IROM boot loader, IPL init ucode, AX, CARD unlock) with the dsp_task.c
// task-switch protocol.
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>

#include "internal.h"

namespace hmaudio {

uint8_t *g_ram;
uint8_t *g_aram;
int g_log_level;

void log(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  fputs("[audio] ", stderr);
  vfprintf(stderr, fmt, ap);
  fputc('\n', stderr);
  va_end(ap);
}

#define LOGI(...) do { if (g_log_level >= 1) log(__VA_ARGS__); } while (0)
#define LOGD(...) do { if (g_log_level >= 2) log(__VA_ARGS__); } while (0)

namespace {

enum class UCode { ROM, INIT, AX, CARD };

struct Mail {
  uint32_t value;
  bool irq;        // raise the DSP interrupt when this mail becomes visible at the head
  bool irq_done;
  uint64_t at;     // visible from this time base value on
};

// AX microcode hashes (Dolphin's HashEctor over the IRAM image). 0xe2136399 is the one in this
// game's DSPCode.c (Dolphin SDK 2003, "newer GC AX": PB with LPF, compressor, DPL2 commands).
bool is_ax_crc(uint32_t crc) {
  switch (crc) {
  case 0xe2136399: case 0x07f88145: case 0x3ad3b7ac: case 0x3daf59b9: case 0x4e8a8b21:
    return true;
  default:
    return false;
  }
}
constexpr uint32_t CARD_CRC = 0x65d6cc6f;

struct State {
  uint16_t cr = CR_HALT | CR_INIT;
  uint64_t init_code_clear_tb = 0;
  uint32_t cpu_mbox = 0;        // CPU -> DSP
  uint32_t last_mail = 0;       // DSP -> CPU, as last latched
  std::deque<Mail> mails;

  UCode ucode = UCode::ROM;
  uint32_t ucode_crc = 0;
  bool line = false;

  // IROM boot loader parameters
  uint32_t rom_next = 0;
  uint32_t rom_iram_mram = 0, rom_iram_len = 0;

  // task-switch protocol (shared by AX and CARD once they yielded / finished)
  bool wait_task_mail = false;
  int ts_step = -1;
  uint32_t ts[10] = {};
  bool ax_initialized = false;

  int card_mails = 0;

  // ARAM controller
  uint16_t ar_info = 0, ar_mode = 1, ar_refresh = 156;
  uint32_t ar_mm = 0, ar_ar = 0, ar_cnt = 0;
  uint16_t misc[0x100] = {};    // unmodelled registers (plain storage)
} S;

uint32_t hash_ector(uint32_t addr, uint32_t len) {
  uint32_t crc = 0;
  for (uint32_t i = 0; i < len; i++) {
    uint8_t b = ram_ok(addr + i, 1) ? *ram_ptr(addr + i) : 0;
    crc ^= b;
    crc = (crc << 3) | (crc >> 29);
  }
  return crc;
}

void update_line() {
  bool on = ((S.cr >> 1) & S.cr & (CR_DSP | CR_ARAM | CR_AID)) != 0;
  if (on != S.line) {
    S.line = on;
    rt_pi_line(0x40, on ? 1 : 0);
  }
}

bool halted() { return (S.cr & CR_HALT) != 0; }

// Raise the DSP interrupt for a head mail that has become visible.
void service_mails(uint64_t now) {
  if (S.mails.empty()) return;
  Mail &m = S.mails.front();
  if (m.irq && !m.irq_done && m.at <= now) {
    m.irq_done = true;
    dsp_raise(CR_DSP);
  }
}

void set_rom() {
  dsp_clear_mails();
  S.ucode = UCode::ROM;
  S.ucode_crc = 0;
  S.rom_next = 0;
  S.wait_task_mail = false;
  S.ts_step = -1;
  dsp_push_mail(0x8071FEED, false);
}

// Start the ucode whose IRAM image is at `iram` in main RAM.
void start_ucode(uint32_t iram, uint32_t len, bool resume) {
  uint32_t crc = hash_ector(iram, len);
  S.wait_task_mail = false;
  S.ts_step = -1;
  if (crc == CARD_CRC) {
    LOGI("ucode CARD (crc %08x)", crc);
    S.ucode = UCode::CARD;
    S.ucode_crc = crc;
    S.card_mails = 0;
    dsp_push_mail(0xDCD10000, true);
    return;
  }
  if (!is_ax_crc(crc))
    log("unknown ucode crc %08x (iram %08x len %x), treating it as AX", crc, iram, len);
  S.ucode = UCode::AX;
  S.ucode_crc = crc;
  if (resume && S.ax_initialized) {
    LOGI("ucode AX resume (crc %08x)", crc);
    dsp_push_mail(0xDCD10001, true);
  } else {
    LOGI("ucode AX init (crc %08x)", crc);
    ax_reset();
    S.ax_initialized = true;
    dsp_push_mail(0xDCD10000, true);
  }
}

void rom_mail(uint32_t mail) {
  if (S.rom_next == 0) {
    if ((mail >> 16) != 0x80F3) dsp_push_mail(0xFEEE0000 | (mail & 0xFFFF), false);
    else S.rom_next = mail;
    return;
  }
  uint32_t param = S.rom_next;
  S.rom_next = 0;
  switch (param) {
  case 0x80F3A001: S.rom_iram_mram = mail; break;
  case 0x80F3A002: S.rom_iram_len = mail & 0xFFFF; break;
  case 0x80F3B002: case 0x80F3C002: break;  // DRAM length / IRAM destination: not needed for HLE
  case 0x80F3D001: start_ucode(S.rom_iram_mram, S.rom_iram_len, false); break;
  default: break;
  }
}

// CDD1xxxx task-control mails after DCD10002 (yield) / DCD10003 (done).
void task_mail(uint32_t mail) {
  if (S.ts_step >= 0) {
    S.ts[S.ts_step++] = mail;
    if (S.ts_step == 10) {
      // 0..2: DRAM save of the current task (ignored), 3..5: next IRAM mram/len/dst,
      // 6: start vector, 7..9: zero (init) or DRAM restore mram/len/dst (resume).
      S.ts_step = -1;
      start_ucode(S.ts[3], S.ts[4] & 0xFFFF, S.ts[7] != 0);
    }
    return;
  }
  switch (mail & 0xFFFF) {
  case 0x0000:  // resume
    dsp_push_mail(0xDCD10001, true);
    S.wait_task_mail = false;
    break;
  case 0x0001:  // a new task follows (10 mails)
    S.ts_step = 0;
    break;
  case 0x0002:  // reset to the IROM
    LOGI("task reset -> ROM");
    set_rom();
    break;
  case 0x0003:  // continue
    S.wait_task_mail = false;
    break;
  default:
    LOGI("unknown task mail %08x", mail);
    break;
  }
}

void dsp_receive(uint32_t mail) {
  LOGD("CPU -> DSP %08x", mail);
  switch (S.ucode) {
  case UCode::ROM: rom_mail(mail); break;
  case UCode::INIT: break;
  case UCode::AX:
    if (S.wait_task_mail || S.ts_step >= 0) task_mail(mail);
    else if (ax_mail(mail)) S.wait_task_mail = true;
    break;
  case UCode::CARD:
    if (S.wait_task_mail || S.ts_step >= 0) {
      task_mail(mail);
    } else if (++S.card_mails == 2) {  // 0xFF000000, work area address
      // The unlock computation itself is not emulated (the memory card side accepts anything).
      dsp_push_mail(0xDCD10003, true, 2000);
      S.wait_task_mail = true;
    }
    break;
  }
}

void cr_write(uint16_t v) {
  uint64_t now = rt_tb_now();
  if (v & CR_RESET) {
    LOGI("DSP reset");
    ai_dsp_reset();
    set_rom();
  }
  bool init_falling = (S.cr & CR_INIT) && !(v & CR_INIT);
  uint16_t status = S.cr & (CR_AID | CR_ARAM | CR_DSP);
  status &= (uint16_t)~(v & (CR_AID | CR_ARAM | CR_DSP));   // write 1 to acknowledge
  uint16_t keep = S.cr & CR_INIT_CODE;
  S.cr = (uint16_t)((v & (CR_HALT | CR_AID_MASK | CR_ARAM_MASK | CR_DSP_MASK | CR_INIT)) | status | keep);
  if (init_falling) {
    // The IPL "init" ucode: answers 0x80544348 and holds DSPInitCode for a moment.
    dsp_clear_mails();
    S.ucode = UCode::INIT;
    S.wait_task_mail = false;
    S.ts_step = -1;
    dsp_push_mail(0x80544348, false);
    S.cr |= CR_INIT_CODE;
    S.init_code_clear_tb = now + 130;
  }
  update_line();
  service_mails(now);
}

uint16_t cr_read() {
  if ((S.cr & CR_INIT_CODE) && rt_tb_now() >= S.init_code_clear_tb) S.cr &= ~CR_INIT_CODE;
  return S.cr;
}

uint16_t mail_hi() {
  uint64_t now = rt_tb_now();
  if (halted()) return (uint16_t)((S.last_mail & 0x7FFFFFFF) >> 16);  // nothing new while halted
  if (!S.mails.empty() && S.mails.front().at <= now) S.last_mail = S.mails.front().value;
  return (uint16_t)(S.last_mail >> 16);
}

uint16_t mail_lo() {
  uint64_t now = rt_tb_now();
  if (!halted() && !S.mails.empty() && S.mails.front().at <= now) {
    S.last_mail = S.mails.front().value;
    S.mails.pop_front();
    LOGD("DSP -> CPU %08x", S.last_mail);
    if (!S.mails.empty()) {
      Mail &n = S.mails.front();
      if (n.at < now) n.at = now;
      service_mails(now);
      reschedule();
    }
  }
  S.last_mail &= 0x7FFFFFFF;
  return (uint16_t)S.last_mail;
}

void aram_dma() {
  uint32_t mm = S.ar_mm & 0x03FFFFFF;
  uint32_t ar = S.ar_ar & 0x03FFFFFF;
  uint32_t cnt = S.ar_cnt & 0x7FFFFFFF;
  bool to_mram = (S.ar_cnt & 0x80000000) != 0;
  LOGD("ARAM DMA %s mm %08x ar %08x len %x", to_mram ? "ARAM->MRAM" : "MRAM->ARAM", mm, ar, cnt);
  for (uint32_t i = 0; i < cnt; i++) {
    uint32_t a = ar + i, m = mm + i;
    if (to_mram) {
      if (ram_ok(m, 1)) *ram_ptr(m) = a < ARAM_SIZE ? g_aram[a] : 0;
    } else if (a < ARAM_SIZE) {
      g_aram[a] = ram_ok(m, 1) ? *ram_ptr(m) : 0;
    }
  }
  S.ar_mm += cnt;
  S.ar_ar += cnt;
  S.ar_cnt &= 0x80000000;
  dsp_raise(CR_ARAM);   // completes immediately (DMA busy bit never reads as set)
}

void set_hi(uint32_t &r, uint16_t v, uint16_t mask) { r = (r & 0x0000FFFF) | ((uint32_t)(v & mask) << 16); }
void set_lo(uint32_t &r, uint16_t v, uint16_t mask) { r = (r & 0xFFFF0000) | (v & mask); }

} // namespace

void dsp_raise(uint16_t bit) {
  S.cr |= bit & (CR_AID | CR_ARAM | CR_DSP);
  update_line();
}

void dsp_push_mail(uint32_t mail, bool irq, uint64_t delay_tb) {
  uint64_t now = rt_tb_now();
  Mail m{mail, irq, false, now + delay_tb};
  if (!S.mails.empty() && m.at < S.mails.back().at) m.at = S.mails.back().at;
  S.mails.push_back(m);
  service_mails(now);
  reschedule();
}

void dsp_clear_mails() { S.mails.clear(); }

void reschedule() {
  uint64_t now = rt_tb_now();
  uint64_t d = ai_next_deadline(now);
  if (!S.mails.empty()) {
    const Mail &m = S.mails.front();
    if (m.irq && !m.irq_done && m.at < d) d = m.at;
  }
  if (d != UINT64_MAX) rt_schedule_audio(d);
}

} // namespace hmaudio

using namespace hmaudio;

extern "C" void audio_init(uint8_t *ram) {
  const char *lv = getenv("HM_AUDIO_LOG");
  g_log_level = lv ? atoi(lv) : 0;
  g_ram = ram;
  if (!g_aram) g_aram = (uint8_t *)calloc(1, ARAM_SIZE);
  else memset(g_aram, 0, ARAM_SIZE);
  S = State();
  set_rom();
  ax_load_coefs();
  ai_reset();
  update_line();
}

extern "C" void audio_shutdown(void) {
  ai_shutdown();
  free(g_aram);
  g_aram = nullptr;
}

extern "C" uint16_t audio_dsp_read16(uint32_t off) {
  off &= 0xFFFF;
  switch (off) {
  case 0x5000: return (uint16_t)(S.cpu_mbox >> 16);
  case 0x5002: return (uint16_t)S.cpu_mbox;
  case 0x5004: return mail_hi();
  case 0x5006: return mail_lo();
  case 0x500A: return cr_read();
  case 0x5012: return S.ar_info;
  case 0x5016: return S.ar_mode;
  case 0x501A: return S.ar_refresh;
  case 0x5020: return (uint16_t)(S.ar_mm >> 16);
  case 0x5022: return (uint16_t)S.ar_mm;
  case 0x5024: return (uint16_t)(S.ar_ar >> 16);
  case 0x5026: return (uint16_t)S.ar_ar;
  case 0x5028: return (uint16_t)(S.ar_cnt >> 16);
  case 0x502A: return (uint16_t)S.ar_cnt;
  case 0x5030: case 0x5032: case 0x5036: case 0x503A: return ai_dma_read16(off);
  default: return S.misc[(off >> 1) & 0xFF];
  }
}

extern "C" void audio_dsp_write16(uint32_t off, uint16_t v) {
  off &= 0xFFFF;
  switch (off) {
  case 0x5000:
    S.cpu_mbox = (S.cpu_mbox & 0xFFFF) | ((uint32_t)v << 16);
    break;
  case 0x5002:
    S.cpu_mbox = (S.cpu_mbox & 0xFFFF0000) | v;
    dsp_receive(S.cpu_mbox);
    S.cpu_mbox &= 0x7FFFFFFF;   // taken by the DSP at once
    break;
  case 0x5004: case 0x5006: break;  // read-only
  case 0x500A: cr_write(v); break;
  case 0x5012: S.ar_info = v & 0x7F; break;
  case 0x5016: break;
  case 0x501A: S.ar_refresh = v & 0x7FF; break;
  case 0x5020: set_hi(S.ar_mm, v, 0x03FF); break;
  case 0x5022: set_lo(S.ar_mm, v, 0xFFE0); break;
  case 0x5024: set_hi(S.ar_ar, v, 0x03FF); break;
  case 0x5026: set_lo(S.ar_ar, v, 0xFFE0); break;
  case 0x5028: set_hi(S.ar_cnt, v, 0x83FF); break;
  case 0x502A: set_lo(S.ar_cnt, v, 0xFFE0); aram_dma(); break;
  case 0x5030: case 0x5032: case 0x5034: case 0x5036: case 0x503A: ai_dma_write16(off, v); break;
  default: S.misc[(off >> 1) & 0xFF] = v; break;
  }
}

extern "C" void audio_event(uint64_t now_tb) {
  service_mails(now_tb);
  ai_service(now_tb);
  reschedule();
}
