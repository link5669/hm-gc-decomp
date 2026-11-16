// Weak fallbacks so the runtime links before the module exists (bring-up only).
#include "rt.h"
#include "../gpu/gpu.h"
#include "../audio/audio.h"
#define W extern "C" __attribute__((weak))

static u16 dsp_regs[0x100];
static u32 ai_regs[8];
W void audio_init(uint8_t *) {}
W void audio_shutdown(void) {}
W void audio_set_capture(void (*)(const int16_t *, int, int)) {}   // [net]
// bring-up DSP: init ucode replies 0x80544348; DMA/reset complete instantly; mailboxes always empty
static bool mail_full = false;
W uint16_t audio_dsp_read16(uint32_t off) {
    u32 r = (off & 0x1FF) >> 1;
    if (r == 0 || r == 1) return 0;                 // CPU->DSP mailbox: consumed
    if (r == 2) return mail_full ? 0x8054 : 0x0054;
    if (r == 3) { mail_full = false; return 0x4348; }
    if (r == 5) return (dsp_regs[5] & ~0x601) | 0x20;
    if (r == 0xB) return 1;                          // ARAM ready
    return dsp_regs[r];
}
W void audio_dsp_write16(uint32_t off, uint16_t v) {
    u32 r = (off & 0x1FF) >> 1;
    u16 old = dsp_regs[r];
    dsp_regs[r] = v;
    if (r == 5 && (old & 4) && !(v & 4)) mail_full = true;   // un-halt -> ucode reply mail
}
W uint32_t audio_ai_read32(uint32_t off) { return ai_regs[(off & 0x1F) >> 2]; }
W void audio_ai_write32(uint32_t off, uint32_t v) { ai_regs[(off & 0x1F) >> 2] = v; }
W void audio_event(uint64_t) {}
