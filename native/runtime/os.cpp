// Guest threads as host fibers + exception (interrupt) delivery.
//
// The guest OS scheduler (OSThread.c) runs recompiled and unchanged. It switches threads with
// OSSaveContext (each call site is an inline setjmp, see recomp) and OSLoadContext (replaced here).
// A context (guest OSContext address) is bound to the fiber that last saved into it or was
// interrupted with it. Loading a context resumes that fiber at its resume point (the save call
// site or the interrupt checkpoint), or starts a new fiber for a fresh thread context.
#include "rt.h"
#include <ucontext.h>
#include <unordered_map>
#include <vector>
#include <sys/mman.h>

enum { CTX_GPR = 0x0, CTX_CR = 0x80, CTX_LR = 0x84, CTX_CTR = 0x88, CTX_XER = 0x8C, CTX_FPR = 0x90,
       CTX_FPSCR = 0x194, CTX_SRR0 = 0x198, CTX_SRR1 = 0x19C, CTX_MODE = 0x1A0, CTX_STATE = 0x1A2,
       CTX_GQR = 0x1A4, CTX_PSF = 0x1C8 };
static const u32 MSR_EE = 0x8000;
static const u32 RESUME_MARK = 0xFFFFFFF0;  // srr0 written into interrupted contexts

struct FpuState { FPR f[32]; double ps1[32]; u32 fpscr; };

struct Fiber {
    ucontext_t uc;
    void *stack = nullptr; size_t stack_size = 0;
    int id;
};
// A guest context bound to the fiber that will continue it, with the host resume point
// (an OSSaveContext call site or an interrupt checkpoint) and its FPU state.
struct CtxEnt {
    Fiber *f = nullptr;
    jmp_buf jb;
    FpuState fpu;
    bool has_jb = false;
};

static Fiber g_main_fiber;
static Fiber *g_cur = &g_main_fiber;
static std::unordered_map<u32, CtxEnt *> g_ctx;
static u32 g_switch_ctx;        // context the next resumed/started fiber loads
static int g_next_id = 1;
static u32 g_idle_ctx;
static u32 g_save_pending;
volatile int rt_irq_flag;

static CtxEnt *ent(u32 ctx) { auto &e = g_ctx[ctx]; if (!e) e = new CtxEnt(); return e; }

static void save_fpu(CPU *c, FpuState &s) { memcpy(s.f, c->f, sizeof s.f); memcpy(s.ps1, c->ps1, sizeof s.ps1); s.fpscr = c->fpscr; }
static void load_fpu(CPU *c, const FpuState &s) { memcpy(c->f, s.f, sizeof s.f); memcpy(c->ps1, s.ps1, sizeof s.ps1); c->fpscr = s.fpscr; }

static void cr_set(CPU *c, u32 v) { for (int i = 0; i < 8; i++) c->cr[i] = (v >> (28 - 4 * i)) & 15; }
static u32 cr_get(CPU *c) { u32 v = 0; for (int i = 0; i < 8; i++) v |= (u32)c->cr[i] << (28 - 4 * i); return v; }

static void regs_to_ctx(CPU *c, u32 ctx) {
    for (int i = 0; i < 32; i++) st32(ctx + CTX_GPR + 4 * i, c->r[i]);
    st32(ctx + CTX_CR, cr_get(c)); st32(ctx + CTX_LR, c->lr); st32(ctx + CTX_CTR, c->ctr);
    st32(ctx + CTX_XER, ((u32)c->so << 31) | ((u32)c->ov << 30) | ((u32)c->ca << 29) | (c->spr[1] & 0x7F));
    for (int i = 0; i < 8; i++) st32(ctx + CTX_GQR + 4 * i, c->gqr[i]);
}
static void ctx_to_regs(CPU *c, u32 ctx) {
    for (int i = 0; i < 32; i++) c->r[i] = ld32(ctx + CTX_GPR + 4 * i);
    cr_set(c, ld32(ctx + CTX_CR)); c->lr = ld32(ctx + CTX_LR); c->ctr = ld32(ctx + CTX_CTR);
    u32 x = ld32(ctx + CTX_XER); c->so = x >> 31; c->ov = (x >> 30) & 1; c->ca = (x >> 29) & 1; c->spr[1] = x & 0x7F;
    for (int i = 1; i < 8; i++) c->gqr[i] = ld32(ctx + CTX_GQR + 4 * i);
    c->msr = ld32(ctx + CTX_SRR1);
    st16(ctx + CTX_STATE, ld16(ctx + CTX_STATE) & ~2);
}

// continue context ctx on the current fiber: registers + FPU, then jump to its resume point
[[noreturn]] static void resume_here(CPU *c, u32 ctx) {
    CtxEnt *e = ent(ctx);
    if (!e->has_jb) rt_fatal("context %08X has no resume point", ctx);
    ctx_to_regs(c, ctx);
    load_fpu(c, e->fpu);
    e->has_jb = false;
    longjmp(e->jb, 1);
}

static void fiber_main();

static Fiber *new_fiber() {
    Fiber *f = new Fiber();
    f->id = g_next_id++;
    f->stack_size = 4 << 20;
    f->stack = mmap(nullptr, f->stack_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
    getcontext(&f->uc);
    f->uc.uc_stack.ss_sp = f->stack; f->uc.uc_stack.ss_size = f->stack_size; f->uc.uc_link = nullptr;
    makecontext(&f->uc, fiber_main, 0);
    return f;
}

[[noreturn]] static void switch_to(Fiber *f, u32 ctx) {
    Fiber *me = g_cur;
    g_switch_ctx = ctx;
    g_cur = f;
    VLOG("[fiber] %d -> %d ctx=%08X\n", me->id, f->id, ctx);
    swapcontext(&me->uc, &f->uc);
    // someone switched back to this fiber to continue g_switch_ctx
    resume_here(&g_cpu, g_switch_ctx);
}

static void fiber_main() {
    CPU *c = &g_cpu;
    u32 ctx = g_switch_ctx;
    if (ent(ctx)->has_jb) resume_here(c, ctx);   // (not expected for a fresh fiber)
    ctx_to_regs(c, ctx);
    u32 pc = ld32(ctx + CTX_SRR0), lr = c->lr;
    VLOG("[fiber] %d start pc=%08X r1=%08X lr=%08X\n", g_cur->id, pc, c->r[1], lr);
    rt_call(c, pc);
    rt_call(c, lr);   // thread function returned: continue at its LR (OSExitThread)
    rt_fatal("thread fiber %d returned from its exit function", g_cur->id);
}

extern "C" void hle_OSLoadContext(CPU *RESTRICT c) {
    u32 ctx = c->r[3];
    CtxEnt *e = ent(ctx);
    if (!e->f) {
        if (ld32(ctx + CTX_SRR0) == RESUME_MARK) rt_fatal("OSLoadContext: interrupted context %08X has no fiber", ctx);
        e->f = new_fiber();
        switch_to(e->f, ctx);
    }
    if (e->f == g_cur) resume_here(c, ctx);
    switch_to(e->f, ctx);
}

extern "C" jmp_buf *rt_save_jb(CPU *RESTRICT c) {
    g_save_pending = c->r[3];
    CtxEnt *e = ent(g_save_pending);
    return &e->jb;
}
extern "C" void rt_after_save(CPU *RESTRICT c) {
    CtxEnt *e = ent(g_save_pending);
    e->f = g_cur; e->has_jb = true;
    save_fpu(c, e->fpu);
}

// ---- interrupts ----
static u64 g_deliver_count[16];
u32 pi_debug_lines();
static void deliver(CPU *c, int exc) {
    if (g_deliver_count[exc] < 40) VLOG("[irq] exc %d lines=%X ctx=%08X lr=%08X\n", exc, pi_debug_lines(), ld32(0x800000D4), c->lr);
    if ((++g_deliver_count[exc] & 1023) == 0) VLOG("[irq] exc %d delivered %llu times\n", exc, (unsigned long long)g_deliver_count[exc]);
    u32 ctx = ld32(0x800000D4);
    regs_to_ctx(c, ctx);
    st32(ctx + CTX_SRR0, RESUME_MARK);
    st32(ctx + CTX_SRR1, c->msr);
    st16(ctx + CTX_STATE, ld16(ctx + CTX_STATE) | 2);
    CtxEnt *e = ent(ctx);
    // the context may already hold a resume point (e.g. its thread was saved at a call site);
    // an interrupt on it replaces that: this checkpoint is where its thread now is.
    e->f = g_cur; e->has_jb = true;
    save_fpu(c, e->fpu);
    if (!setjmp(e->jb)) {
        u32 handler = ld32(0x80003000 + 4 * exc);
        c->spr[26] = RESUME_MARK; c->spr[27] = c->msr;
        c->msr = (c->msr & ~(MSR_EE | 0x2000)) | 0x30;
        c->r[3] = exc; c->r[4] = ctx;
        if (!handler) rt_fatal("no handler for exception %d", exc);
        rt_call(c, handler);
        rt_fatal("exception %d handler returned", exc);
    }
    // resumed here: registers and FPU were loaded from ctx
}

extern "C" void rt_card_run_pending(CPU *RESTRICT c);
extern "C" void rt_irq_check(CPU *RESTRICT c) {
    for (;;) {
        rt_irq_flag = 0;
        ev_run_due();
        if (!(c->msr & MSR_EE)) return;
        rt_card_run_pending(c);
        if (irq_pending_pi_only()) { deliver(c, 4); return; }
        if (g_dec_pending) { g_dec_pending = false; deliver(c, 8); return; }
        // idle thread spinning with nothing pending: sleep until the next device event
        if (g_idle_ctx && ld32(0x800000D4) == g_idle_ctx) { ev_wait_until_next(); continue; }
        return;
    }
}

void os_init_main_fiber() {
    g_main_fiber.id = 0;
    g_idle_ctx = rt_sym("IdleContext");
    if (!g_idle_ctx) LOG("warning: IdleContext symbol not found (no idle sleeping)\n");
}

[[noreturn]] void os_run_entry(u32 entry) {
    CPU *c = &g_cpu;
    rt_call(c, entry);
    rt_fatal("entry point returned");
}
