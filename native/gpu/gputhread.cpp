// GPU thread (HM_GPU_THREAD, default on): the guest thread appends FIFO bytes and posted calls to a
// single-producer/single-consumer ring; the GPU thread owns the GL context and executes them in order.
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <cstdio>
#include "gx_internal.h"
#include "gputhread.h"

namespace gx {

static bool s_threaded = false;
static std::thread::id s_tid;
static u8 *s_ring;
static const u64 RING = 32ull << 20;
static std::atomic<u64> s_w{0}, s_r{0};
static std::atomic<u64> s_done{0};
static u64 s_seq = 0;  // producer side
static std::mutex s_mu;
static std::condition_variable s_cv_cons, s_cv_prod;
static std::atomic<bool> s_cons_wait{false}, s_prod_wait{false};
static std::atomic<u64> s_notifies{0};
enum { R_FIFO = 1, R_CALL = 2 };

bool thr_active() { return s_threaded; }
bool thr_on_gpu() { return std::this_thread::get_id() == s_tid; }

static void ring_copy_in(u64 pos, const void *src, u64 n) {
  u64 o = pos % RING, k = std::min(n, RING - o);
  memcpy(s_ring + o, src, k);
  if (n > k) memcpy(s_ring, (const u8 *)src + k, n - k);
}
static void ring_copy_out(void *dst, u64 pos, u64 n) {
  u64 o = pos % RING, k = std::min(n, RING - o);
  memcpy(dst, s_ring + o, k);
  if (n > k) memcpy((u8 *)dst + k, s_ring, n - k);
}

void thr_push(u32 type, const void *a, u32 na, const void *b, u32 nb) {
  u32 hdr[2] = {type, na + nb};
  u64 total = (8 + (u64)na + nb + 7) & ~7ull;
  u64 w = s_w.load(std::memory_order_relaxed);
  if (total > RING / 2) { logf("ring record too large (%llu)", (unsigned long long)total); return; }
  while (RING - (w - s_r.load(std::memory_order_acquire)) < total) {
    std::unique_lock<std::mutex> l(s_mu);
    s_prod_wait = true;
    if (RING - (w - s_r.load(std::memory_order_acquire)) < total) s_cv_prod.wait_for(l, std::chrono::milliseconds(2));
    s_prod_wait = false;
  }
  ring_copy_in(w, hdr, 8);
  if (na) ring_copy_in(w + 8, a, na);
  if (nb) ring_copy_in(w + 8 + na, b, nb);
  s_w.store(w + total, std::memory_order_release);
  if (s_cons_wait.load()) {
    s_notifies++;
    std::lock_guard<std::mutex> l(s_mu);
    s_cv_cons.notify_one();
  }
}

static void mark_done(void *p) {
  s_done.store(*(u64 *)p, std::memory_order_release);
  std::lock_guard<std::mutex> l(s_mu);
  s_cv_prod.notify_all();
}

void thr_sync() {
  if (!s_threaded || thr_on_gpu()) return;
  u64 seq = ++s_seq;
  void (*fn)(void *) = mark_done;
  thr_push(R_CALL, &fn, sizeof(fn), &seq, sizeof(seq));
  while (s_done.load(std::memory_order_acquire) < seq) {
    std::unique_lock<std::mutex> l(s_mu);
    s_prod_wait = true;
    if (s_done.load(std::memory_order_acquire) < seq) s_cv_prod.wait_for(l, std::chrono::milliseconds(1));
    s_prod_wait = false;
  }
}

void fifo_write_impl(const u8 *data, u32 len);

static void gpu_thread_main(void (*on_start)(void)) {
  s_tid = std::this_thread::get_id();
  if (on_start) on_start();
  std::vector<u8> buf(1 << 16);
  for (;;) {
    u64 r = s_r.load(std::memory_order_relaxed);
    if (r == s_w.load(std::memory_order_acquire)) {
      // brief spin before sleeping: the guest usually sends more within microseconds
      bool got = false;
      for (int i = 0; i < 2000 && !got; i++) got = r != s_w.load(std::memory_order_acquire);
      if (!got) {
        std::unique_lock<std::mutex> l(s_mu);
        s_cons_wait = true;
        while (r == s_w.load(std::memory_order_acquire)) s_cv_cons.wait_for(l, std::chrono::milliseconds(5));
        s_cons_wait = false;
      }
      continue;
    }
    u32 hdr[2];
    ring_copy_out(hdr, r, 8);
    u64 total = (8 + (u64)hdr[1] + 7) & ~7ull;
    if (buf.size() < hdr[1]) buf.resize(hdr[1]);
    ring_copy_out(buf.data(), r + 8, hdr[1]);
    s_r.store(r + total, std::memory_order_release);
    if (s_prod_wait.load()) {
      std::lock_guard<std::mutex> l(s_mu);
      s_cv_prod.notify_all();
    }
    static double busy = 0, t_last = now_ms();
    static u64 nrec = 0;
    double t0 = g_prof_on ? now_ms() : 0;
    nrec++;
    if (hdr[0] == R_FIFO) {
      fifo_write_impl(buf.data(), hdr[1]);
    } else if (hdr[0] == R_CALL) {
      void (*fn)(void *);
      memcpy(&fn, buf.data(), sizeof(fn));
      fn(buf.data() + sizeof(fn));
    }
    if (g_prof_on) {
      double t1 = now_ms();
      busy += t1 - t0;
      if (t1 - t_last > 2000) {
        fprintf(stderr, "[gpu thread] busy %.0f%% records %llu/s notifies %llu/s\n", busy * 100 / (t1 - t_last),
                (unsigned long long)(nrec * 1000 / (t1 - t_last)), (unsigned long long)(s_notifies.exchange(0) * 1000 / (t1 - t_last)));
        busy = 0; nrec = 0; t_last = t1;
      }
    }
  }
}

bool thr_start(void (*on_start)(void)) {
  const char *e = getenv("HM_GPU_THREAD");
  if (e && atoi(e) == 0) return false;
  s_ring = (u8 *)malloc(RING);
  s_threaded = true;
  std::thread(gpu_thread_main, on_start).detach();
  return true;
}

}  // namespace gx
