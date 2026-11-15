MEMORY
{
    text : origin = $ORIGIN
}

SECTIONS
{
    GROUP:
    {
        $SECTIONS
    } > text

    /* multiplayer mod: reserve 0x30000 bytes after the game's data for tools/mp/build_mp.py.
       It must lie outside the stack range [_stack_end, _stack_addr), which startup zero-fills,
       and below the arena. No game code or data moves. */
    _mp_reserve_start = ($LAST_SECTION_SYMBOL + SIZEOF($LAST_SECTION_NAME) + 0xff) & ~0xff;
    _mp_reserve_end = _mp_reserve_start + 0x30000;
    _stack_end = _mp_reserve_end;
    _stack_addr = (_stack_end + $STACKSIZE + 0x7) & ~0x7;
    _db_stack_addr = (_stack_addr + 0x2000);
    _db_stack_end = _stack_addr;
    __ArenaLo = (_db_stack_addr + 0x1f) & ~0x1f;
    __ArenaHi = 0x81700000;
}

FORCEACTIVE
{
    $FORCEACTIVE
}
