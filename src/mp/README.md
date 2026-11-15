# Multiplayer mod (branch `multiplayer`)

Build: `tools/mp/build.sh` -> `build/GHYE6S/main_mp.dol` (put it in an extracted disc's `sys/main.dol`).

How it works (no game code or data moves):
- `config/GHYE6S/ldscript_mp.tpl` reserves 0x30000 bytes between the game's last data section and the stack
  (`_mp_reserve_start`..`_mp_reserve_end`). The stack and arena start move up by that amount.
- `tools/mp/build_mp.py` compiles `src/mp/*.c` with MWCC GC/2.6 (`-sdata 0 -sdata2 0`), links them with GNU ld
  at `_mp_reserve_start` against the game's symbols (`main.elf`), appends the result to `main.dol` as a new text
  section, then rewrites the branch instructions listed in `src/mp/hooks.txt` to call into the mod.
