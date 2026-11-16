// Device event scheduler. Deadlines are guest time-base values; a host timer thread raises rt_irq_flag
// when the earliest deadline passes (and every 2 ms as a heartbeat), and the guest thread runs due
// events at its next checkpoint.
#include "rt.h"
#include "../audio/audio.h"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>

static u64 g_deadline[EV_COUNT];
static bool g_active[EV_COUNT];
static std::mutex g_mu;
static std::condition_variable g_cv;
static std::atomic<u64> g_next{~0ull};

void dec_event();

static void recompute() {
    u64 n = ~0ull;
    for (int i = 0; i < EV_COUNT; i++) if (g_active[i] && g_deadline[i] < n) n = g_deadline[i];
    g_next = n;
}
void ev_schedule(EventId id, u64 t) {
    std::lock_guard<std::mutex> l(g_mu);
    g_deadline[id] = t; g_active[id] = true; recompute();
    g_cv.notify_all();
}
void ev_cancel(EventId id) { std::lock_guard<std::mutex> l(g_mu); g_active[id] = false; recompute(); }
u64 ev_next_deadline() { return g_next; }
extern "C" void rt_schedule_audio(uint64_t t) { ev_schedule(EV_AUDIO, t); }

void ev_run_due() {
    for (;;) {
        u64 now = tb_now();
        int id = -1;
        {
            std::lock_guard<std::mutex> l(g_mu);
            u64 best = ~0ull;
            for (int i = 0; i < EV_COUNT; i++) if (g_active[i] && g_deadline[i] <= now && g_deadline[i] < best) { best = g_deadline[i]; id = i; }
            if (id < 0) return;
            g_active[id] = false; recompute();
        }
        switch (id) {
        case EV_VI: vi_event(); break;
        case EV_DEC: dec_event(); break;
        case EV_DI: di_event(); break;
        case EV_AUDIO: audio_event(now); break;
        case EV_GPU: hw_apply_gpu_events(); break;
        default: break;
        }
    }
}

void ev_wait_until_next() {
    std::unique_lock<std::mutex> l(g_mu);
    u64 n = g_next, now = tb_now();
    if (n <= now) return;
    u64 ns = (n - now) * 2000 / 81;
    if (ns > 20000000) ns = 20000000;
    g_cv.wait_for(l, std::chrono::nanoseconds(ns));
}

static void timer_main() {
    for (;;) {
        u64 n = g_next, now = tb_now();
        rt_irq_flag = 1;   // heartbeat: lets the guest notice due events and idle-sleep
        u64 wait_ns = n > now ? (n - now) * 2000 / 81 : 0;
        if (wait_ns > 2000000) wait_ns = 2000000;
        if (wait_ns < 50000) wait_ns = 50000;
        std::unique_lock<std::mutex> l(g_mu);
        g_cv.wait_for(l, std::chrono::nanoseconds(wait_ns));
        if (g_next <= tb_now()) rt_irq_flag = 1;
    }
}
void ev_start_timer_thread() { std::thread(timer_main).detach(); }
