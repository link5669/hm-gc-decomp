# Multiplayer mod (branch `multiplayer`)

Build: `tools/mp/build.sh` -> `build/GHYE6S/main_mp.dol` (put it in an extracted disc's `sys/main.dol`).

How it works (no game code or data moves):
- `config/GHYE6S/ldscript_mp.tpl` reserves 0x30000 bytes between the game's last data section and the stack
  (`_mp_reserve_start`..`_mp_reserve_end`). The stack and arena start move up by that amount.
- `tools/mp/build_mp.py` compiles `src/mp/*.c` with MWCC GC/2.6 (`-sdata 0 -sdata2 0`), links them with GNU ld
  at `_mp_reserve_start` against the game's symbols (`main.elf`), appends the result to `main.dol` as a new text
  section, then rewrites the branch instructions listed in `src/mp/hooks.txt` to call into the mod.

## Playing co-op
- Plug in a second controller (port 2) and press START on it, in a menu or in game. Once gameplay starts, the game
  pauses and each player types a name on an on-screen keyboard with their own controller (stick/D-pad to move, A to
  type, B to delete, START when done).
- Player 2 appears next to player 1 as a second Zeke with his own body, animation, lantern, camera and controls (same
  buttons as player 1). Both players act separately but share the ghosts-needed / ghosts-found totals.
- Each player has their own health and lives. Player 2's bar and lives are at the bottom right. When knocked out,
  player 2 loses a life and comes back next to player 1 (no game over). Out of lives: START rejoins with 3 lives.
- Names are shown above each player's head. If either player is not visible on the shared screen, the screen splits
  vertically (player 1 left, player 2 right, each with their own follow camera); it merges again once both are
  comfortably visible.
- Unplugging controller 2 ends co-op (player 2 stops).

## Building a disc image
`tools/mp/build.sh`, then extract your disc (e.g. `dtk vfs cp "<your disc>:" extracted/`, into `sys/` and `files/`),
copy `build/GHYE6S/main_mp.dol` to `extracted/sys/main.dol`, and run
`python3 tools/mp/mkiso.py extracted HauntedMansion_coop.iso`.

## Known limitations
- Enemies, scripted events and level triggers still focus on player 1 (they track the game's single "player").
- Not tested yet: catching ghosts as player 2, level transitions through doors, player 1 game over with player 2 in.
- A debug build (`MP_CFLAGS=-DMP_DEBUG_AUTOJOIN tools/mp/build.sh`) auto-joins player 2 with default names; Z on
  controller 2 forces split screen, D-pad up teleports player 2 to player 1, D-pad down knocks player 2 out.
