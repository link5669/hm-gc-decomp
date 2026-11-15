# Multiplayer mod (branch `multiplayer`)

Build: `tools/mp/build.sh` -> `build/GHYE6S/main_mp.dol` (put it in an extracted disc's `sys/main.dol`).

How it works (no game code or data moves):
- `config/GHYE6S/ldscript_mp.tpl` reserves 0x30000 bytes between the game's last data section and the stack
  (`_mp_reserve_start`..`_mp_reserve_end`). The stack and arena start move up by that amount.
- `tools/mp/build_mp.py` compiles `src/mp/*.c` with MWCC GC/2.6 (`-sdata 0 -sdata2 0`), links them with GNU ld
  at `_mp_reserve_start` against the game's symbols (`main.elf`), appends the result to `main.dol` as a new text
  section, then rewrites the branch instructions listed in `src/mp/hooks.txt` to call into the mod.

## Playing co-op
- Plug in a second controller (port 2) and press START on it, in a menu or in game. If you're in a menu, a note says the
  join is pending. Once gameplay starts, the game world pauses and each player types a name on an on-screen keyboard
  with their own controller (stick/D-pad to move, A to type, B to delete, START when done).
- Player 2 then appears as a second Zeke (own body, lantern and controls) at the level's spawn point. Both players
  share the souls, health and other progress, so they work towards the same goal.
- Names are shown above each player's head. When the players are far apart (more than 9 units), the screen splits
  vertically: player 1 on the left, player 2 on the right. It merges again when they're within 6 units.
- Unplugging controller 2 ends co-op (player 2 stops moving).

## Building a disc image
`tools/mp/build.sh`, then extract your disc (e.g. `dtk vfs cp "<your disc>:" extracted/`, into `sys/` and `files/`),
copy `build/GHYE6S/main_mp.dol` to `extracted/sys/main.dol`, and run
`python3 tools/mp/mkiso.py extracted HauntedMansion_coop.iso`.

## Known limitations
- Player 2 starts at the level's spawn point rather than beside player 1.
- Enemies, events and the main camera still focus on player 1; player 2's camera copies player 1's camera angle.
- A debug build (`MP_CFLAGS=-DMP_DEBUG_AUTOJOIN tools/mp/build.sh`) auto-joins player 2 with default names; Z on
  controller 2 forces split screen.
