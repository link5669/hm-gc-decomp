// DSP (AX microcode HLE) + ARAM + AI (audio interface) for the native port. C ABI.
// The audio module owns the DSP register block (0xCC005000..0xCC0051FF, 16-bit registers incl. mailboxes,
// DSP control/status, ARAM DMA) and the AI block (0xCC006C00..0xCC006C1F, 32-bit registers).
#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

// ram: guest main RAM (24 MiB, big-endian data), guest physical p -> ram[p & 0x01FFFFFF].
void audio_init(uint8_t *ram);
void audio_shutdown(void);

// MMIO from the CPU. off = address & 0xFFFF (e.g. 0x5000 + reg, 0x6C00 + reg).
// 32-bit accesses to the DSP block arrive as two 16-bit accesses (high half first, at off and off+2).
uint16_t audio_dsp_read16(uint32_t off);
void audio_dsp_write16(uint32_t off, uint16_t v);
uint32_t audio_ai_read32(uint32_t off);
void audio_ai_write32(uint32_t off, uint32_t v);

// [net] capture hook: called with every block of mixed output (interleaved L R, host endian), even when muted.
void audio_set_capture(void (*cb)(const int16_t *lr, int frames, int rate));

// Called by the runtime (on the guest CPU thread) when a deadline requested with rt_schedule passes.
void audio_event(uint64_t now_tb);

// ---- provided by the runtime ----
// PI interrupt lines: bit 0x40 = DSP (AI/ARAM/DSP-int), 0x20 = AI (streaming). level 1 = asserted.
void rt_pi_line(uint32_t bit, int level);
uint64_t rt_tb_now(void);                    // guest time base, 40.5 MHz (OSGetTime units)
void rt_schedule_audio(uint64_t deadline_tb); // ensure audio_event is called at/after this time (replaces earlier request)

#ifdef __cplusplus
}
#endif
