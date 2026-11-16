#!/usr/bin/env python3
"""Names of functions whose body contains MWCC inline asm (anywhere: src/, include dirs; also under #ifdef __MWERKS__,
where clang silently compiles them to nothing). The GuestMem pass keeps them (and their native callers) recompiled."""
import os, re, sys
FN = re.compile(r'\b(\w+)\s*\(([^;{}()]|\([^()]*\))*\)\s*(const\s*)?\{')
ASM = re.compile(r'\basm\s*\{|\basm\s*\(|\b__asm\b|^\s*asm\b', re.M)
KW = {'if', 'for', 'while', 'switch', 'return', 'sizeof', 'defined'}
def names(text):
    out = set()
    for m in ASM.finditer(text):
        # `asm void f(...)` / `asm u32 f(...)`: the name follows
        tail = re.match(r'\s*asm\s+[\w\s\*]*?(\w+)\s*\(', text[m.start():m.start() + 200])
        if tail and m.group(0).strip() == 'asm' and tail.group(1) not in KW: out.add(tail.group(1)); continue
        best = None
        for f in FN.finditer(text, max(0, m.start() - 20000), m.start()):
            if f.group(1) not in KW: best = f.group(1)
        if best: out.add(best)
    return out
def collect(roots):
    out = set()
    for r in roots:
        for dp, _, fs in os.walk(r):
            for f in fs:
                if f.endswith(('.c', '.cpp', '.h', '.hpp', '.inc')):
                    t = open(os.path.join(dp, f), errors='replace').read()
                    if 'asm' in t: out |= names(t)
    return out
if __name__ == '__main__':
    print('\n'.join(sorted(collect(sys.argv[1:]))))
