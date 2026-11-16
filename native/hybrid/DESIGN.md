# Hybrid native port: decomp C/C++ compiled natively, recompiled code as fallback

Goal: run as much of the game as possible from the decomp's own C/C++ (compiled for x86-64), and use the
static recompilation (native/recomp) only for what the decomp can't provide yet (asm units, non-matching
units, functions that fail to build or validate). Both kinds run side by side, function by function.

## Why not just compile the decomp with gcc
The decomp's C assumes the GameCube memory model: 32-bit pointers, big-endian data, MWCC struct layout,
and it is full of raw casts (`*(u32 *)(p + 0x6c)`). Recompiled code, the GPU and the audio DSP share the same
big-endian guest RAM. So native code must keep *guest* data layout and addresses exactly.

## Pipeline (per decomp unit)
1. `vtshim.py`: source rewrite for C++ polymorphic structs (51.5% of game code uses them). MWCC places the
   vtable pointer at the position of the first `virtual` declaration among the data members (`{int x;
   virtual v(); int y;}`: x 0, vptr 4, y 8; virtuals first: vptr at 0; with a non-polymorphic base, right
   after the base — checked by compiling test classes with MWCC) and its vtable starts with an 8-byte
   header (slot k at +8+4k). verify_layout.py: 2462/2463 virtual units have MWCC's sizes. Each polymorphic
   struct becomes a plain struct with an explicit `void **__vt` at that position, and each virtual method an inline function that calls
   `__vt[2 + k]`. Inheritance: a derived class reuses the base's `__vt` and continues the slot numbering.
2. `clang --target=powerpc-unknown-eabi -O0 -emit-llvm` with `include/` shims for MWCC intrinsics
   (`__cntlzw`, `__fabs`, `__frsqrte`, `__lhbrx`, `__sync`, `OSRoundUp32B`...). This gives the exact
   big-endian ILP32 struct layout (field offsets are folded into byte GEPs by the PPC data layout).
3. `GuestMem` LLVM pass (pass/GuestMem.cpp), run before optimization:
   - pointers stay 32-bit guest addresses (held in i32);
   - every load/store becomes a call to the inline guest accessors (`hm_ld32` ... like recompiled code:
     RAM fast path with byte swap, MMIO / ARAM-VM / locked cache slow path);
   - globals: names found in main.elf map to their real guest addresses (the DOL's data is already in
     guest RAM); module-private constants (string literals, jump tables, static locals not in the ELF) go to
     a reserved guest region (0x81800000+, above the game's 24 MiB) initialised at startup;
   - address-taken locals live on the guest stack (r1), others stay in host registers;
   - calls: native -> native are direct; native -> recompiled marshal arguments into `CPU` registers per
     the PowerPC EABI (r3-r10, f1-f8, sret/byval as clang lowered them) and call `fn_XXXXXXXX`; calls through
     function pointers go through `rt_call`.
   Then `opt -O2` and `llc` for x86-64.
4. Thunks: for each native function `fn_X` the recompiled `fn_X(CPU *)` entry becomes a thunk that reads
   arguments from the guest registers, calls the native implementation and writes the result back, so
   recompiled callers, function-pointer tables (rt_call) and the GPU/OS paths all reach the native code.

## Selection and validation
`analyze.py` lists every function of every Matching unit (from the decomp's per-unit objects) and its class
(c / cpp / virtual / asm). A function is native when its unit builds through the pipeline; a per-function
denylist and `HM_NATIVE_ONLY` / `HM_NATIVE_DENY` (address ranges) allow bisecting. Validation: the smoke test,
the 26-area warp tour and screenshot comparison against the all-recompiled build; failures are bisected
down to a function, which is then fixed (or denylisted) with a note.

Current split (analyze.py): virtual C++ 51.5% of code, plain C++ 31.0%, C 12.5%, asm 5.0% (stays recompiled).
