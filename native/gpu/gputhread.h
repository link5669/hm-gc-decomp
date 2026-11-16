// GPU thread plumbing (gputhread.cpp).
#pragma once
#include <new>
#include <type_traits>
namespace gx {
bool thr_active();
bool thr_on_gpu();
bool thr_start(void (*on_start)(void));
void thr_push(u32 type, const void *a, u32 na, const void *b, u32 nb);
void thr_sync();
// true if the caller must hand the call to the GPU thread
inline bool thr_remote() { return thr_active() && !thr_on_gpu(); }
// Posts a trivially copyable callable to the GPU thread (runs in stream order).
template <class F> void thr_post(const F &f) {
  static_assert(std::is_trivially_copyable<F>::value, "posted callables must be trivially copyable");
  void (*tramp)(void *) = [](void *p) {
    alignas(16) unsigned char tmp[sizeof(F)];
    memcpy(tmp, p, sizeof(F));
    (*reinterpret_cast<F *>(tmp))();
  };
  thr_push(2, &tramp, sizeof(tramp), &f, sizeof(F));
}
}  // namespace gx
