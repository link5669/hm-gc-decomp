#!/usr/bin/env python3
"""ELF symbol database for the GuestMem pass: global symbols of main.elf (+ mp.elf) and per-FILE local symbols.
usage (library): load(main_elf, mp_elf) -> SymDB ; db.write_unit(unit_basename, path)"""
import subprocess, os, re
BU = os.environ.get('BINUTILS', os.path.expanduser('~/.local/share/decompnet/toolchains/gc-wii-binutils/powerpc-eabi-'))

def readelf(path):
    out = subprocess.run([BU + 'readelf', '-sW', path], capture_output=True, text=True, check=True).stdout
    for l in out.splitlines():
        p = l.split()
        if len(p) < 8 or not p[0].endswith(':') or not p[0][:-1].isdigit(): continue
        val = int(p[1], 16); sz = int(p[2], 16) if p[2].startswith('0x') else int(p[2])
        yield val, sz, p[3], p[4], p[6], p[7]

class SymDB:
    def __init__(self, main_elf, mp_elf=None):
        self.glob = {}      # name -> (addr, size, type)
        self.files = {}     # FILE name -> {name: (addr, size)}
        self.dupfiles = set()
        self.funcs = {}     # addr -> (name, size)  (main.elf FUNC symbols)
        for i, path in enumerate([main_elf] + ([mp_elf] if mp_elf else [])):
            cur = None
            for val, sz, typ, bind, ndx, name in readelf(path):
                if typ == 'FILE':
                    if i == 0:
                        if name in self.files: self.dupfiles.add(name)
                        cur = self.files.setdefault(name, {})
                    continue
                if typ == 'SECTION' or ndx == 'UND': continue
                if bind in ('GLOBAL', 'WEAK'):
                    self.glob.setdefault(name, (val, sz, typ))
                elif cur is not None and i == 0:
                    cur.setdefault(name, (val, sz))
                if i == 0 and typ == 'FUNC': self.funcs.setdefault(val, (name, sz))

    def write_globals(self, path):
        with open(path, 'w') as f:
            for n, (a, s, t) in self.glob.items(): f.write('G %s %x %x\n' % (n, a, s))

    def write_unit(self, unit_base, path):
        with open(path, 'w') as f:
            if unit_base not in self.dupfiles:
                for n, (a, s) in self.files.get(unit_base, {}).items(): f.write('L %s %x %x\n' % (n, a, s))
