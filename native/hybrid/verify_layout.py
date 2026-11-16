#!/usr/bin/env python3
"""Check vtshim: sizeof of every polymorphic class under MWCC (original source) vs clang (rewritten source).
usage: verify_layout.py [-j N] [UNIT...]   (default: every unit with polymorphic classes)  -> prints mismatches"""
import os, re, subprocess, sys, json
from concurrent.futures import ThreadPoolExecutor
H = os.path.dirname(os.path.abspath(__file__)); R = os.path.dirname(os.path.dirname(H))
sys.path.insert(0, H)
import vtshim, hmcc
T = os.path.expanduser('~/.local/share/decompnet/toolchains')
W = os.path.join(R, 'build/hybrid/verify'); os.makedirs(W, exist_ok=True)

def mw_cflags(unit):
    return ['-nodefaults', '-proc', 'gekko', '-align', 'powerpc', '-enum', 'int', '-fp', 'hardware', '-Cpp_exceptions', 'off',
            '-O4,p', '-inline', 'auto', '-RTTI', 'off', '-str', 'reuse', '-multibyte', '-lang=c++', '-DNDEBUG=1', '-DBUILD_VERSION=0',
            '-i', 'include', '-i', 'tools/rea/ref/dolsdk2004/include', '-i', 'tools/rea/ref/dolsdk2004/include/libc', '-i', 'build/GHYE6S/include',
            '-i', 'src/' + os.path.dirname(unit)]

def probes(names):
    return '\n'.join('extern "C" unsigned long hmsz_%d(void) { return sizeof(%s); }' % (i, n) for i, n in enumerate(names)) + '\n'

def sizes_from_asm(txt, n):
    out = {}
    for m in re.finditer(r'<hmsz_(\d+)>:\n(?:.*\n){0,3}?.*?\tli\s+r3,(-?\d+)', txt):
        out[int(m.group(1))] = int(m.group(2))
    return out

def check(unit):
    src = open(os.path.join(R, 'src', unit), errors='replace').read()
    r = vtshim.rewrite(src)
    names = sorted(set(r.poly))
    if not names: return unit, None, 'nopoly'
    pr = probes(names)
    base = os.path.join(W, unit.replace('/', '_'))
    # MWCC on original + probes (sizeof of classes known by vtshim; skip ones MWCC cannot see)
    res = {}
    for n in list(names):
        pass
    open(base + '.mw.cpp', 'w').write(src + '\n' + pr)
    p = subprocess.run([T + '/wibo/wibo', T + '/mwcc/GC/1.3.2/mwcceppc.exe'] + mw_cflags(unit) + ['-c', base + '.mw.cpp', '-o', base + '.mw.o'], capture_output=True, text=True, cwd=R)
    if p.returncode: return unit, None, 'mwcc: ' + (p.stdout + p.stderr).strip().splitlines()[0:1].__str__()[:120]
    dis = subprocess.run([T + '/gc-wii-binutils/powerpc-eabi-objdump', '-d', base + '.mw.o'], capture_output=True, text=True).stdout
    mw = sizes_from_asm(dis, len(names))
    # clang on rewritten + probes
    ptxt = hmcc.prepare(unit) + '\n' + pr
    cp = base + '.cl.cpp'; open(cp, 'w').write(ptxt)
    cmd = hmcc.cmd_for(unit, cp, base + '.cl.ll')
    q = subprocess.run(cmd, capture_output=True, text=True, cwd=R)
    if q.returncode: return unit, None, 'clang: ' + ([l for l in q.stderr.splitlines() if 'error' in l] or ['?'])[0][-100:]
    ll = open(base + '.cl.ll').read()
    cl = {}
    for m in re.finditer(r'define[^\n]*@hmsz_(\d+)\(\)[^\n]*\{\n(?:[^\n]*\n)*?\s+ret i32 (-?\d+)', ll):
        cl[int(m.group(1))] = int(m.group(2))
    bad = [(names[i], mw.get(i), cl.get(i)) for i in range(len(names)) if mw.get(i) is None or mw.get(i) != cl.get(i)]
    return unit, bad, len(names)

if __name__ == '__main__':
    a = sys.argv[1:]; j = 8
    if '-j' in a:
        i = a.index('-j'); j = int(a[i + 1]); del a[i:i + 2]
    if not a:
        a = sorted({c['unit'] for c in json.load(open(os.path.join(H, 'candidates.json'))) if c['class'] == 'virtual'})
    tot = nb = ns = ne = 0; errs = {}
    with ThreadPoolExecutor(j) as ex:
        for unit, bad, info in ex.map(check, a):
            if bad is None: errs[unit] = info; ne += 1; continue
            tot += info; ns += 1
            if bad: nb += 1; print('MISMATCH', unit, bad[:4])
    print('units checked', ns, 'classes', tot, 'units with mismatch', nb, 'units not checkable', ne)
    json.dump(errs, open(os.path.join(W, 'errors.json'), 'w'), indent=0)
