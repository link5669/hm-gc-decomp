# Multiplayer mod (branch `multiplayer`)

Build: `tools/mp/build.sh` -> `build/GHYE6S/main_mp.dol` (put it in an extracted disc's `sys/main.dol`). The script
uses the decomp.wtf toolchains when present, else the tools plain `configure.py` downloads into `build/`.

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
- Names are shown above each player's head. In co-op the screen is always split vertically (player 1 left, player 2
  right) and each player has his own camera:
  - player 1 keeps the game's camera, exactly as in single player (C stick, lock-on, cutscenes);
  - player 2 has an orbit camera of his own: the C stick of controller 2 turns it (left/right) and raises or lowers it
    (up/down), it drifts behind him while he walks sideways, the game's "camera behind me" request puts it behind him,
    and it uses the game's wall test (it rises above the player instead of going through walls).
  Player 2's stick is relative to player 2's camera: the camera globals the Player update reads (written by player 1's
  camera) are swapped for player 2's camera around his update, so turning one camera never changes where the other
  player walks. The debug menu (Z + START) has "SCREEN": always split (default) or the older shared screen that only
  splits when a player leaves it (player 2 then moves relative to the shared camera while it is shared).
- Cutscenes (the game camera in scripted mode) belong to player 1 and play in his pane. Player 2 keeps playing in his
  own pane: messages sent to his Player actor from outside his own update are dropped while a cutscene runs (so the
  script does not freeze him or walk him to player 1's mark), and he does not fire walk-in triggers / loading zones
  until it is over. If he is ever left without control while player 1 has it, control comes back after 3 s.
  `MP_CFLAGS=-DMP_CUTSCENE_PAUSE_P2` builds the previous behaviour (player 2 hidden and paused during cutscenes).
- Rooms: when either player walks into a loading zone (player 2's body is registered in the level's collision pass,
  and walk-in triggers accept both players), both go: player 2 is placed next to player 1 in the new room (on a free
  spot, checked with the game's wall test) and keeps their lives and health. Game over / quitting to the title ends
  co-op on the title screen; the next game starts player 2 fresh.
- Unplugging controller 2 ends co-op (player 2 stops).

## Building a disc image
`tools/mp/build.sh`, then extract your disc (e.g. `dtk vfs cp "<your disc>:" extracted/`, into `sys/` and `files/`),
copy `build/GHYE6S/main_mp.dol` to `extracted/sys/main.dol`, and run
`python3 tools/mp/mkiso.py extracted HauntedMansion_coop.iso`.

## Known limitations
- Enemies, scripted events and level triggers still focus on player 1 (they track the game's single "player").
- Not verified yet: catching ghosts / hurting enemies as player 2 (enemies only came for player 1 in testing).
- Camera metrics (debug): `MP_CFLAGS="-DMP_DEBUG_AUTOJOIN -DMP_DEBUG_CAM"` logs visibility/split/turn-rate stats.
- A debug build (`MP_CFLAGS=-DMP_DEBUG_AUTOJOIN tools/mp/build.sh`) auto-joins player 2 with default names; Z on
  controller 2 teleports player 1 to player 2, D-pad up teleports player 2 to player 1, D-pad down knocks player 2 out,
  D-pad left knocks player 1 out, D-pad right teleports player 2 to the next test actor, X loads the Ballroom.
