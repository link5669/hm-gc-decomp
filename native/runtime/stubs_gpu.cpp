// Weak fallbacks so the runtime links before the module exists (bring-up only).
#include "rt.h"
#include "../gpu/gpu.h"
#include "../audio/audio.h"
#define W extern "C" __attribute__((weak))

static u64 g_fifo_bytes;
W void gpu_init(uint8_t *, uint32_t) {}
W void gpu_shutdown(void) {}
W void gpu_fifo_write(const uint8_t *, uint32_t len) { g_fifo_bytes += len; }
W void gpu_present(int, int) {}
W uint32_t gpu_efb_peek(int, int, int) { return 0; }
W void gpu_efb_poke(int, int, int, uint32_t) {}
W void gpu_set_scale(int) {}

