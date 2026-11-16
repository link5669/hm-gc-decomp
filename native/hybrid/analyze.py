#!/usr/bin/env python3
"""Hybrid native port: which decomp functions can be compiled natively from C?

For every Matching unit in configure.py, list the functions its object defines (build/GHYE6S/src/<unit>.o),
then classify the unit's source:
  c / cpp            language
  asm                contains MWCC asm (functions or blocks) -> those functions stay recompiled
  virtual            C++ with virtual methods (MWCC vtable layout differs from clang's) -> needs the vtable shim
Writes native/hybrid/candidates.json and prints a summary (functions and code bytes per class).
"""
import json, os, re, subprocess, sys
from collections import Counter, defaultdict

R = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
BU = os.path.expanduser('~/.local/share/decompnet/toolchains/gc-wii-binutils/powerpc-eabi-')

def units():
    out = []
    for line in open(os.path.join(R, 'configure.py')):
        m = re.search(r'Object\((Matching|NonMatching|Equivalent\w*),\s*"([^"]+)"', line)
        if m: out.append((m.group(1), m.group(2)))
    return out

def defined_functions(obj):
    if not os.path.exists(obj): return []
    r = subprocess.run([BU + 'nm', '-S', '--defined-only', obj], capture_output=True, text=True)
    fs = []
    for l in r.stdout.splitlines():
        p = l.split()
        if len(p) == 4 and p[2] in 'Tt': fs.append((p[3], int(p[1], 16)))
    return fs

def classify(src):
    try: t = open(src, errors='replace').read()
    except OSError: return {'missing'}
    tags = set()
    tags.add('cpp' if src.endswith('.cpp') else 'c')
    if re.search(r'^\s*asm\b|\basm\s*\{|\basm\s+void|\basm\s+u32|__asm', t, re.M): tags.add('asm')
    if re.search(r'\bvirtual\b', t): tags.add('virtual')
    if re.search(r'\bclass\b|::', t): tags.add('methods')
    return tags

def main():
    elf_syms = {}
    nm = subprocess.run([BU + 'nm', '--defined-only', os.path.join(R, 'build/GHYE6S/main.elf')], capture_output=True, text=True).stdout
    for l in nm.splitlines():
        p = l.split()
        if len(p) == 3 and p[1] in 'Tt': elf_syms.setdefault(p[2], int(p[0], 16))
    cand = []
    stats = Counter(); bytes_ = Counter()
    for status, unit in units():
        src = os.path.join(R, 'src', unit)
        obj = os.path.join(R, 'build/GHYE6S/src', os.path.splitext(unit)[0] + '.o')
        fs = defined_functions(obj)
        tags = classify(src)
        cls = 'nonmatching' if status != 'Matching' else ('asm' if 'asm' in tags else ('virtual' if 'virtual' in tags else tags & {'c', 'cpp'} and sorted(tags & {'c', 'cpp'})[0]))
        for name, size in fs:
            addr = elf_syms.get(name)
            cand.append({'unit': unit, 'func': name, 'addr': addr, 'size': size, 'class': cls, 'tags': sorted(tags)})
            stats[cls] += 1; bytes_[cls] += size
    json.dump(cand, open(os.path.join(R, 'native/hybrid/candidates.json'), 'w'), indent=0)
    total = sum(bytes_.values())
    print('%-12s %8s %10s %6s' % ('class', 'funcs', 'bytes', '%code'))
    for k in sorted(stats, key=lambda k: -bytes_[k]):
        print('%-12s %8d %10d %5.1f%%' % (k, stats[k], bytes_[k], 100.0 * bytes_[k] / total))

if __name__ == '__main__':
    main()
