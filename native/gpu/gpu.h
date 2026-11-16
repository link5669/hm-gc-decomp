// GameCube GPU (Flipper GX) command-stream processor rendering with OpenGL 3.3 core.
// Contract between the runtime (CPU side) and the GPU module. C ABI.
#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

// ---- called by the runtime ----
// ram: guest main RAM (24 MiB, big-endian data). Guest physical address p maps to ram[p & 0x01FFFFFF].
// The GL context is current on the calling thread for every gpu_* call.
void gpu_init(uint8_t *ram, uint32_t ram_size);

// ---- GPU thread (optional; HM_GPU_THREAD=0 disables) ----
// gpu_thread_start: call before gpu_init, after releasing the GL context on the calling thread; on_start runs
// first on the GPU thread and must make the GL context current there. Returns 1 if a GPU thread runs.
// Afterwards every gpu_* call made from another thread is queued in stream order (FIFO data, present, ...);
// peek/debug_read_xfb wait for the result. gpu_cb_* callbacks are then invoked on the GPU thread.
int gpu_thread_start(void (*on_start)(void));
int gpu_on_gpu_thread(void);   // 1 on the GPU thread, or always when not threaded
// Runs fn(copy of arg[0..size)) on the GPU thread in stream order (immediately when not threaded).
void gpu_run(void (*fn)(void *), const void *arg, uint32_t size);
void gpu_sync(void);           // waits until everything queued so far has executed
void gpu_shutdown(void);

// Bytes of the GP command FIFO in stream order (any chunking; commands may span calls).
// Processes the stream synchronously: decodes CP/XF/BP loads, draws, display-list calls, EFB copies.
void gpu_fifo_write(const uint8_t *data, uint32_t len);

// Draws the most recent XFB image (the last EFB->XFB copy) scaled to fit a window of win_w x win_h
// pixels into GL framebuffer 0 (letterboxed, 4:3). The runtime calls SDL_GL_SwapWindow after it.
void gpu_present(int win_w, int win_h);

// Draws a CPU-written XFB from guest RAM (YUYV 4:2:2, bytes Y0 U Y1 V, BT.601 limited range) letterboxed
// 4:3 into framebuffer 0, like gpu_present. stride_pixels: pixels per row in RAM (>= width).
void gpu_present_ram_xfb(uint32_t xfb_phys, int width, int height, int stride_pixels, int win_w, int win_h);

// CPU access to the EFB through 0xC8000000 (GXPeekARGB/GXPokeARGB/GXPeekZ/GXPokeZ).
// x, y are EFB coordinates (0..639, 0..527). is_z selects Z (24-bit) instead of ARGB8888.
uint32_t gpu_efb_peek(int x, int y, int is_z);
void gpu_efb_poke(int x, int y, int is_z, uint32_t value);

// Internal resolution multiplier for the EFB (1 = 640x528 native). Set before gpu_init.
void gpu_set_scale(int scale);
// Change the internal resolution while running (applied at the next XFB copy), current scale,
// and the smoothed GPU time of a frame in ms (0 until measured; resets after a scale change).
void gpu_request_scale(int scale);
int gpu_get_scale(void);
float gpu_frame_gpu_ms(void);

// Target display aspect (4/3 = original). Other values widen the EFB (physical width = 640*scale*a/(4/3)),
// widen the perspective FOV, keep 2D shapes (except near-full-width ortho draws, which stretch), and
// gpu_present fills a window of that aspect. Takes effect at the next EFB->XFB copy. May be called every frame.
void gpu_set_aspect(float a);

// Debug/test helper: last XFB image as RGBA8 (top row first, host resolution). Pointer valid until the
// next call. Returns 0 if no XFB copy happened yet.
int gpu_debug_read_xfb(uint8_t **rgba, int *w, int *h);

// ---- implemented by the runtime, called by the GPU ----
void gpu_cb_draw_done(void);          // BP 0x45 (PE_DONE / GXSetDrawDone) finished
void gpu_cb_token(uint16_t token);    // BP 0x48 (PE_TOKEN_INT, GXSetDrawSync) token; BP 0x47 just sets the token
void gpu_cb_xfb_copy(uint32_t xfb_addr, uint32_t width, uint32_t height); // EFB->XFB copy done (frame end)

#ifdef __cplusplus
}
#endif
