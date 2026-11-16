// Runtime internals (C++ only).
#pragma once
#include "ppc.h"
#include <cstdio>
#include <cstdlib>
#include <string>

extern CPU g_cpu;
extern u8 *g_aram;              // 16 MiB (owned by audio module when present)

// logging
extern int g_log_level;
#define LOG(...) do { if (g_log_level >= 1) { fprintf(stderr, __VA_ARGS__); } } while (0)
#define VLOG(...) do { if (g_log_level >= 2) { fprintf(stderr, __VA_ARGS__); } } while (0)
[[noreturn]] void rt_fatal(const char *fmt, ...);
const char *rt_func_name(u32 addr, u32 *off);

// time base (40.5 MHz)
u64 tb_now();
void tb_set(u64 v);
static const u64 TB_HZ = 40500000ull;

// event scheduler (guest thread only)
enum EventId { EV_VI, EV_DEC, EV_DI, EV_AUDIO, EV_SI, EV_EXI, EV_GPU, EV_COUNT };
void ev_schedule(EventId id, u64 deadline_tb);
void ev_cancel(EventId id);
void ev_run_due();              // run events whose deadline passed
u64 ev_next_deadline();
void ev_wait_until_next();      // idle: block the host thread until the next deadline
void ev_start_timer_thread();

// interrupts
void pi_line(u32 bit, bool level);
bool irq_pending();             // PI cause & mask or decrementer
bool irq_pending_pi_only();
extern bool g_dec_pending;

// devices (hw.cpp)
void hw_init();
u32 hw_read(u32 addr, int size);
void hw_write(u32 addr, u32 v, int size);
void gp_write(u32 v, int size);   // write-gather pipe
void vi_event();
void di_event();
void hw_apply_gpu_events();   // PE draw-done/token raised by the GPU thread -> PE regs + PI lines (guest thread)
void hw_poll_host();            // SDL events, called at VI retrace

// disc
bool disc_open(const std::string &path);
bool disc_read(u64 off, void *dst, u32 len);
u64 disc_size();

// boot
void boot_setup_lowmem();
void dol_load(const u8 *dol, size_t size);

// threads/fibers (os.cpp)
void os_init_main_fiber();
[[noreturn]] void os_run_entry(u32 entry);

// HLE
void hle_init();
void pad_poll_host();

// symbols exported by the recompiler (table.c)
u32 rt_sym(const char *name);  // data/function address by name (0 if unknown)
