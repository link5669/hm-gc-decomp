// Internal shared state of the audio module (DSP HLE + ARAM + AI).
#pragma once
#include <cstdint>
#include <cstddef>

#include "audio.h"

namespace hmaudio {

constexpr uint32_t RAM_SIZE = 24u << 20;
constexpr uint32_t ARAM_SIZE = 16u << 20;
constexpr uint32_t ARAM_MASK = ARAM_SIZE - 1;
constexpr uint64_t TB_HZ = 40500000;

extern uint8_t *g_ram;
extern uint8_t *g_aram;

void log(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
extern int g_log_level; // 0 = errors only, 1 = info, 2 = debug

// ---- guest main RAM (big-endian), out-of-range accesses read 0 / are dropped ----
inline bool ram_ok(uint32_t a, uint32_t len) {
  uint32_t o = a & 0x01FFFFFF;
  return o + (uint64_t)len <= RAM_SIZE;
}
inline uint8_t *ram_ptr(uint32_t a) { return g_ram + (a & 0x01FFFFFF); }
inline uint16_t ram_r16(uint32_t a) {
  if (!ram_ok(a, 2)) return 0;
  const uint8_t *p = ram_ptr(a);
  return (uint16_t)((p[0] << 8) | p[1]);
}
inline uint32_t ram_r32(uint32_t a) {
  if (!ram_ok(a, 4)) return 0;
  const uint8_t *p = ram_ptr(a);
  return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) | ((uint32_t)p[2] << 8) | p[3];
}
inline void ram_w16(uint32_t a, uint16_t v) {
  if (!ram_ok(a, 2)) return;
  uint8_t *p = ram_ptr(a);
  p[0] = (uint8_t)(v >> 8);
  p[1] = (uint8_t)v;
}
inline void ram_w32(uint32_t a, uint32_t v) {
  if (!ram_ok(a, 4)) return;
  uint8_t *p = ram_ptr(a);
  p[0] = (uint8_t)(v >> 24);
  p[1] = (uint8_t)(v >> 16);
  p[2] = (uint8_t)(v >> 8);
  p[3] = (uint8_t)v;
}

// ---- DSP interface (dsp.cpp) ----
enum : uint16_t {
  CR_RESET = 0x0001,
  CR_ASSERT_INT = 0x0002,
  CR_HALT = 0x0004,
  CR_AID = 0x0008,
  CR_AID_MASK = 0x0010,
  CR_ARAM = 0x0020,
  CR_ARAM_MASK = 0x0040,
  CR_DSP = 0x0080,
  CR_DSP_MASK = 0x0100,
  CR_DMA_BUSY = 0x0200,
  CR_INIT_CODE = 0x0400,
  CR_INIT = 0x0800,
};
void dsp_raise(uint16_t status_bit);          // set CR_AID/CR_ARAM/CR_DSP and update PI line 0x40
void dsp_push_mail(uint32_t mail, bool irq, uint64_t delay_tb = 0);
void dsp_clear_mails();
void reschedule();                            // recompute the next audio_event deadline

// ---- AX microcode HLE (ax.cpp) ----
void ax_reset();
// Handles a mail while the AX ucode waits for a command list. Returns true when the ucode then
// yields (frame done, DCD10002 pushed) and the next mail is a task-control mail.
bool ax_mail(uint32_t mail);
void ax_load_coefs();

// ---- AI (ai.cpp) ----
void ai_reset();
void ai_shutdown();
void ai_dma_write16(uint32_t off, uint16_t v);   // 0x5030..0x503A
uint16_t ai_dma_read16(uint32_t off);
void ai_dsp_reset();                             // DSP reset clears the AI DMA control
void ai_service(uint64_t now);                   // advance AI DMA + stream counter to `now`
uint64_t ai_next_deadline(uint64_t now);         // UINT64_MAX if nothing pending

} // namespace hmaudio
