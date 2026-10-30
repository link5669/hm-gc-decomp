# AGENTS.md: handoff notes for game-code decompilation

This is the matching decompilation of The Haunted Mansion (GameCube, GHYE6S). Read this before starting.

## Status and ownership

- Progress is in `build/GHYE6S/report.json`; `python3 tools/rea/finalize.py` prints the totals. The latest numbers are in `git log`. At handoff it was about 6,950 / 10,159 functions and about 27% of code.
- **You own the game code**: every `auto/text_*` unit EXCEPT the library units below.
- **Library units are owned by another agent. Do not edit them:**
  - `auto/text_800B2E70` (Dolphin SDK, `GC/1.2.5n`)
  - `auto/text_800E40A0` (MSL / Metrowerks runtime, `GC/2.0`)
  - `src/sdk/*` (SDK EXI/SI/DB units split out of text_800E40A0)
  - `auto/text_80273E10` (asm-heavy low-level SDK)
  - `auto/text_800DAA80` (MetroTRK)
  - `auto/text_802752DC` (RAD Bink, `ProDG/3.5`)

  If you need a symbol or declaration from one of them, declare it locally in your own unit.
- Game code compiles with **GC/1.3.2**, flags `-O4,p -inline auto` (see `configure.py`). Some units are C++ (`-Cpp_exceptions on`) and some also need `-use_lmw_stmw on`.

## Hard rules

1. `build/GHYE6S/main.dol` must stay **byte-identical**: `sha1sum -c config/GHYE6S/build.sha1` must say OK before every commit.
2. Commit in batches. End commit messages with the project's standard trailer (see existing commits).
3. On the machine set up by decomp.wtf (toolchains under `~/.local/share/decompnet`), never run bare `python3 configure.py`: it would switch `build.ninja` to downloaded tools under `build/`. ninja re-runs configure automatically when `configure.py` changes. If you must regenerate by hand:
   ```
   T=$HOME/.local/share/decompnet/toolchains
   ~/.local/share/uv/tools/decompnet/bin/python configure.py --wrapper $T/wibo/wibo --compilers $T/mwcc \
     --binutils $T/gc-wii-binutils --dtk $T/dtk/dtk --objdiff $T/objdiff-cli/objdiff-cli --sjiswrap $T/sjiswrap/sjiswrap.exe
   ```
   On any other machine, plain `python3 configure.py` (as in README.md) downloads the tools into `build/` and is correct; `ninja build/binutils` fetches objdump for the scripts.
4. Apply a candidate exactly once. Applying, then `git checkout`, then re-applying leaves untracked `.cpp` files and creates duplicate definitions. To roll back use `git checkout -- . && git clean -fdq -e 'zz_q*' src/`.
5. The judge writes temp files `src/auto/zz_*`. They are gitignored; never commit them.

## Tools (tools/decomp_agent/)

Copy them into a scratch dir and run from there. Scripts locate each other through `$DECOMP_SCRATCH`:
```
export DECOMP_SCRATCH=/tmp/decomp-scratch; mkdir -p $DECOMP_SCRATCH
cp tools/decomp_agent/* $DECOMP_SCRATCH/; cp $DECOMP_SCRATCH/game_skip.txt $DECOMP_SCRATCH/skip.txt
```
These scripts and the `tools/rea/*.py` ones hardcode the original checkout (`/home/mi/Decomp/hauntedmansion-ghye6s`) and
toolchain (`~/.local/share/decompnet/toolchains/...`). On another machine, sed those paths in your scratch copies to your
checkout and to `build/tools/{wibo,objdiff-cli,dtk}`, `build/compilers/` and `build/binutils/` (copy `apply_q.py`,
`finalize.py`, `c2cpp.py`, `link.py` and `layout.py` too, keeping finalize's state files in `tools/rea`).
| tool | purpose |
|---|---|
| `q.py UNIT FN cand.c [cpp]` | Local judge: compiles the candidate standalone (game flags) and diffs FN against the built object. Prints `MATCH` or a diff. Env `QV=<ver>` (bare, e.g. `1.3.2`, `2.0`), `QX=<extra flags>`. Parallel-safe. It compares relocation types, not symbol names: a candidate that calls the wrong function or ctor still prints `MATCH` (the layout check catches it later), so check names, especially in sibling copies. |
| `qa3.sh DIR LIST [jobs]` | Parallel judge over `fn unit` lines. Picks `DIR/FN.*`; a `.lmw` suffix adds `-use_lmw_stmw on`. Prints `ok …` / `FAIL …` lines. |
| `unitcheck.py UNIT FN cand.c [QV]` | Merges the candidate into a temp copy of the unit, as apply does, and compiles the whole unit. Catches declaration conflicts the standalone judge misses. Run it on every C match (it compiles `src/UNIT.c` with `-lang=c`, so it reports ERROR for C++ candidates; build those instead). |
| `dumpasm2.py N skip.txt` | Compact asm of the N smallest unmatched functions (excludes library units). Writes to stdout. |
| `applyres.sh res…` | Applies `ok FN UNIT path` lines through `tools/rea/apply_q.py`. FAIL lines go to skip.txt. |
| `addctors.py res…` | Adds the `.ctors` entry for sinit functions whose unit has `.ctors` in splits.txt. Without it the layout check fails. |
| `families.py` / `sibling.py` / `sibimm.py` | Groups unmatched functions by normalized asm; copies a matched sibling's source with symbols and immediates remapped. Large free wins. |
| `relocs.py` | Per-instruction relocation helper used by the above. |
| `ps.py FN` | REA saved pseudocode lookup. It needs `pseudo.json`, an index built from `tools/rea/rea/*.json`. Rebuild it or use the REA MCP tools directly. |
| `permdecl.py`, `perm.py` | Brute-force declaration-order permutations for register-allocation misses. |
| `voltry.py` | Retries failures with float externs made `volatile`. |

After applying: `ninja`, then remove the touched units from `tools/rea/c2cpp_rejected.txt` (finalize skips units listed there), then `python3 tools/rea/finalize.py` (converts, re-verifies from a clean build, links), then the sha check, then commit.

## Workflow loop

1. `python3 -I $DECOMP_SCRATCH/dumpasm2.py 60 $DECOMP_SCRATCH/skip.txt > batch.txt`. Small functions (<150 B) are mostly done; most of what is left is 150 to 1500 bytes. Use REA pseudocode for those.
2. Write candidates `DIR/FN.c` or `FN.cpp` (add `.lmw` if the target uses stmw/lmw). Make them self-contained: declare all prototypes and externs locally.
3. Run `qa3.sh DIR list`. Fix the failures in a second directory (`q.py` shows the diff).
4. Apply, then build, finalize, check the sha and commit, as above. Add the batch to skip.txt.
5. Every few batches re-run `families.py` + `sibling.py`; newly matched functions unlock siblings.

## Matching cookbook (GC/1.3.2)

- **Virtual calls**: vtable slot = (disp − 8) / 4. If the vptr is at offset N, model the class as `struct V { u8 pad[N]; virtual …; }`.
- **Register order**: the first-declared local tends to get r31, and parameter registers follow first use. Try permutations (`perm.py`). Reusing a parameter (`p = p->next`) reproduces register reuse. Declare all locals at the top for sequential loops.
- **Branches**: `beq x; b y` comes from a ternary or a single-case `switch`. Two compares on the same cr come from an inline helper with its own check.
- **Constants**: repeated reloads of the same float global mean `extern volatile f32`. A float kept in a register means the source used a local copy.
- **Copies**: interleaved load/store mean `__restrict` pointers. A two-word `lwz/lwz/stw/stw/lwz/stw` is a struct with an array member assigned by value. Use 12-byte struct copies (`T12`) for vec3-style copies.
- **Indexed fields**: `mulli; addi off; add base` or `add; lwz off(r)` means member-array indexing through a struct type (`((S*)p)->arr[i]`, `&(*(T**)(p+X))[i].field`), not manual `p+i*K+off`. Plain `arr[i]` reproduces `li r5,0; li r6,0; mr r4,r5` loop setups.
- **Masks**: `& 0xFB` gives `andi.`; `&= ~4` gives `rlwinm`. f32 vs double return types matter (`frsp` or not).
- **Epilogue tell**: `lwz r0,20(r1)` *before* the r30/r31 restores means the function returns a value.
- **Constructors / destructors**: write a base ctor call, vtable store and field inits as plain C. For `new T[n]` with `__ct__9CXXXFv/__dt__9CXXXFv` relocs use `struct CXXX { CXXX(); ~CXXX(); }`; extab layout may still differ.
- **Destructor pattern**: `if (p) { …; if (f > 0) __dl__FPv(p); } return p;` with `s16 f`. For C++ destructors with virtual calls take `u8 *p` and cast; typing the param as `V*` grows the frame.
- **Static initializers**: `__register_global_object` / `__construct_array` / cos-sinit families need `__declspec(section ".ctors") static void (*const ctor_X)(void) = fn_X;` (`addctors.py`).
- **Thunks**: `asm` functions with `nofralloc` (`addi r3,r3,-N; b tgt`).
- **Loop hoisting**: `#pragma opt_loop_invariants off` stops `p+K` being hoisted out of parse loops.
- **Forwarded parameters**: a temporary in r6/r7 while r4/r5 are never set before a call means the function passes its own parameters through (`fn_80272F28(p, a, b)` calls `fn_801AA960(x, a, b)`). Add the parameters.
- **Scheduling only**: identical instructions in a different order (e.g. a void function whose epilogue restores r31 before `lwz r0`) can need `#pragma scheduling off` … `#pragma scheduling reset` around the function.
- **Byte locals**: `u8` vs `s8`/`char`/`int` for a loaded byte changes register allocation even when the instructions are the same.

- **More GC/1.3.2 tricks that matched large game functions** (library agent, 2026-10-22):
  - In C++, `int` vs `s32` (`long`) on a parameter can change register coloring.
  - Unfolded arithmetic in the original (`mulli 3; slwi 2`) comes from a repeated block in an inline helper.
  - A float the original reloads at every use is `extern volatile f32`.
  - String pools with gaps: a padding array plus a dead static function holding the filler literals.
  - State-table switch walkers: tables as static arrays at their real offsets, and the loop written as
    `for (q = b + idx; t > 0; q++) { if (*q > t) break; t -= b[idx++]; }`.
  - Virtual calls that load through r12 only come out of C++ with real virtual classes.

## Linking units whose code already matches

Many NonMatching units have every function at 100% and only fail the unit check (functions plus section layout vs
`build/GHYE6S/obj/<unit>.o`, see `tools/rea/layout.py`) or the C++ conversion. Check these before decompiling new code:

- **extab garbage**: some actions (e.g. DELETEPOINTERCOND) end in two uninitialized bytes; the original has `b1 02` (or
  `b0 02`). Add `extab_padding=[0xB1, 0x02]` to the unit's `Object(...)`; the `mwcc_extab` rule (`dtk extab clean`)
  then reproduces them. dtk consumes the padding bytes once over the whole table, so with several such actions repeat
  the pair once per action (`extab_padding=[0xB1, 0x02, 0xB1, 0x02]`).
- **C units that need `-use_lmw_stmw on`**: `tools/rea/apply_q.py` drops the flag for `.c` candidates, so a C match
  that uses `stmw`/`lmw` silently fails in the build. Convert such units to C++ with both flags (24 units on
  2026-10-21 matched only this way).
- **Missing `.ctors`/`.dtors` entries** for static initializers (`addctors.py`).
- **C to C++ conversion**: any integer cast on an argument (`(int)(p)`, even `(s32)` on an `s32`, or an implicit
  conversion through an `int` prototype) changes register allocation and saved registers in C++ mode. Give callees
  pointer prototypes and keep argument types equal to parameter types. C++ also needs explicit casts for `void *`
  results (`__nw__FUl`, `NULL`), and calls through `(RT (*)())` casts need their parameter list.
- **12-byte copies** in C++ must be `struct { u32 v[3]; }` (a struct of three scalars is copied memberwise).
- **Comparisons are `bool`** in C++: `return a == b;` from an `s32` function becomes `cntlzw; extrwi`; use a `bool`
  return or `x ? 1 : 0`, and `bool` locals for stored comparisons.
- **Function order** in the object follows source order (asm thunks included).
- **Dead functions**: a function only referenced by its own unit (e.g. by its jump table) is dead-stripped once the
  unit links from C; add it to `force_active` in `config/GHYE6S/config.yml`.
- **Literals** the original takes from named `.sdata`/`.sdata2` objects must use those externs (`extern const f64
  lbl_X;`, `extern char lbl_X[6];`, sized so small-data addressing is used).
- **Jump table at 4 mod 8**: a unit whose `.data` (a switch jump table) starts at 4 mod 8 cannot link alone, since
  the linker 8-aligns each object's `.data`. When the object in front of it is the class vtable sitting in a
  synthetic `jt_*` data unit, move the vtable into the unit (shrink the `jt_*` range, extend the unit's `.data` in
  splits.txt) and define it in the source before the functions: `void *lbl_X[7] = { 0, 0, (void *)fn_A, ... };`.
  When it is another function's jump table, the two units were one TU and need merging.
- **Shared compiler constants**: two adjacent units that reference the same `.sdata2` int-to-float double (or a
  string pool in `.rodata`) were one TU. Merge them and give the merged unit that range.
- **Mislabeled switch cases**: when only the jump table differs, the case labels can be attached to the wrong
  blocks (e.g. globals shifted by one case); the code bytes still match.
- **A failed link leaves the old main.dol in place**, so `sha1sum -c` still says OK. Check that ninja exited 0
  before trusting the sha (or delete `build/GHYE6S/main.dol` first).
- **Linker hangs forever** (`mwldeppc` at 100% CPU; a normal link takes about 15 s): an object whose `.text` starts with
  a global function and a global label at offset 0 (e.g. `SystemCallVector` and `__OSSystemCallVectorStart` in
  OSSync). Make the function `scope:local` in symbols.txt. To find the culprit, link with `timeout` while leaving out
  one object at a time from `build/GHYE6S/main.elf.rsp`.

## Exception-table constructs (C++, GC/1.3.2)

The decoded extab in `build/GHYE6S/asm/<unit>.s` says which C++ construct the original used:

- **DELETEPOINTER** on the `new` result: `p = new C;` with `sizeof(C)` equal to the `__nw__FUl` size and a ctor
  (often inline) holding the code inside `if (p)`. A plain-named base ctor is called as `fn_X(this)` first in it; a
  mangled one (`__ct__9CXXXXFv`) comes from deriving from `struct CXXXX { CXXXX(); };` (empty bases take no space).
- **DESTROYBASE / DESTROYMEMBER / DESTROYMEMBERARRAY**: real base classes, member objects and member arrays whose
  destructors are the Dtor symbols. Actions only cover throwing calls after the subobject is built, so a missing
  action does not mean there is no destructor. Several DESTROYMEMBER at one offset = a union of class-type members.
- **DESTROYBASE at `0x8(SP)`** (`06 00 0008`) for `new Derived` with an inline ctor: `#pragma optEH2 on` for the file
  (or `throw()` on the callees inside the inlined ctor body). Without it GC/1.3.2 names the register (`06 80 001f`).
  Don't use the pragma where the original names a register: under it multi-call ctor bodies also get the stack form.
- **DESTROYLOCAL**: `__ct__9CX(&obj); … __dt__9CX(&obj, -1);` is a local `CX obj;`.
- **Plain vtable labels**: MWCC puts the vptr after the data members of the class that introduces it. For a vtable named
  `lbl_X`, store it from a holder: an empty base whose inline ctor stores `lbl_X` at the vptr offset (when stored before
  all member ctors), or a member `struct V { u8 *vt; V() { vt = lbl_X; } }` (when stored between base and members).
- **Plain-named destructors** (`dtor_XXXX`, `fn_XXXX`) in extab cannot be produced: MWCC has no aliasing. Rename them
  (symbols.txt + sources, as `tools/rea/cxx.py apply` does) to the mangled destructor of their class. A class's dtor
  sits right before its ctor in this binary (dtor address + size = ctor address), which tells you the class name.
- `__ct__9CXXXXFs` is the ctor of a class with a virtual base (hidden `short` in r4); MWCC mangles it `…Fv`.

## Known blockers (skip unless you crack them)

- **Inlined base ctor** `mr r30,r3; mr r0,r30; mr r31,r0` (e.g. `__ct__9C80155460Fv`, `80155E80`, `8020E5C0`). Inline ctors, multiple inheritance and member-object variants were all tried without success.
- **Member ctor held in r30** (e.g. `__ct__9C80064474Fv` family, `80239B40`, `8022F98C`).
- **Zero-then-assign** at +40/+44 after `fn_801EF9A0` (`li r3,0; lwz r4,8(q); stw r3,44; …`): e.g. `fn_801DEE18`, `801E812C`, `801DE80C`, `801E0384`, `801E7D14`.
- **Descriptor init / factory family** (about 20 functions near 0x8004–0x800B): they address the unit's own `.data` through a section-base register, so they need that data defined as statics in the same TU. The same goes for pooled string literals (`fn_80068D50`, `80046BB8`, `80267CF8`, …).
- **Local objects whose dtor is `dtor_XXXX`** (`fn_8012D774`, `80138AA8`, `8013EF3C`): need the dtor renamed (see "Plain-named destructors" above).
- **Symbol renames** (done): 41 plain-named ctors/dtors used by exception tables were renamed to mangled names (recorded in `tools/rea/renames.json`), which matched the `fn_8012CF08` family, `fn_80105B88` and 30 other units. `fn_80117DC4` matched without a rename (inline ctor/dtor calling the two literal names). 0x80118DE0 is now `__dt__9C80118E78Fv`, which freed `__dt__9C8011F770Fv` for `dtor_8011F6FC`. `fn_8013D770` still needs renames for its four member-array classes.
- **Switch jump tables** (data must match too): `fn_8012F7F8`, `8010CF00`, `801FA224`, `8021C124`. The others in the old list are linked (vtable moves, case relabeling, extab padding). Units whose jump table follows another function's jump table (`800447E8`, `800501FC`, `80052028`, `8008CA0C`, `80090C68`, `800919A4`) need merging with undecompiled neighbours.
- **Near misses (scheduling or register allocation only)**: `fn_80153D4C`, `8017CB04`, `801BB258`, `801BCA04`, `8016E4D4`, `801B2504`, `80191360`, `8019F53C`, `8019FCB0`, `801A0424`, `80158E34`, `801547BC`, `80149C68`, `80186960`, `8022202C`, `801DF270`, `8023C3F4`, `80213F6C`, `8021F4A4`, `80240948`, `801C9C40`, `8024973C`, `801F13F0`, `801C1774`, `8003C674`, `8003C778`, `801135BC`, `80112FD4`, `8010E280`, `80112190`, `80102730`, `800F9838`, `80112698`, `8011FA98`, `800FA69C`, `80071CE8`.
- **Factory `new` functions** (solved): real classes with an inline derived ctor storing the vtable label by hand, plus `#pragma optEH2 on` for the stack-slot DESTROYBASE (see above), matched 37 factories with base `C8024262C` and others.
- `fn_800F8410` only matches with GC/2.0; its unit would need a compiler switch.

## Coordination

**Claimed game functions (2026-10-22):** the library agent now also works on game code, but only on the functions in
`tools/decomp_agent/claimed_by_library_agent.txt`: units whose only unmatched functions are 1,000 bytes or larger
(352 functions), extended on 2026-10-23 to 500 bytes or larger. Re-run the awk line below after pulling. Your `dumpasm2.py` loop works up from the smallest, so add that file's names to your skip.txt
(`awk '!/^#/{print $2}' tools/decomp_agent/claimed_by_library_agent.txt >> $DECOMP_SCRATCH/skip.txt`) and the two
loops won't overlap. Pull often: both agents commit to `main`.

The library-unit agent works in this repo too and commits its own batches. Commit only your own units: `git add` specific paths rather than `-A`. If a library unit shows up as modified in `git status`, leave it alone.

**Absorbed units (2026-10-30):** `text_80268290` was merged into `text_80268178.cpp` (one TU, namespace-wrapped, with `-use_lmw_stmw on`; `fn_80268290` is in `force_active`). The `text_80268290` unit no longer exists.
