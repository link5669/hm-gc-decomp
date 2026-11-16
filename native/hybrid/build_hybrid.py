#!/usr/bin/env python3
"""Hybrid build: decomp units (LLVM IR from hmcc.py) -> GuestMem pass -> x86-64 objects + thunks, then the
recompiled code with those functions replaced (ppc2c --native-list), linked into $HM_OUT/cmake/hauntedmansion.

usage: build_hybrid.py [--units FILE] [--no-link] [-j N]
  units: native/hybrid/native.txt if present (one unit per line, e.g. auto/text_8016E084.c; '#' comments;
         a line 'all' = every unit with IR in build/hybrid/ir), else all.
  deny:  native/hybrid/deny.txt + $HM_NATIVE_DENY_BUILD (names, hex addresses, or hex ranges lo-hi; ',' or ' ' separated)
  HM_OUT (default build/native-hybrid), HM_BUILD (default build/GHYE6S)."""
import os, sys, re, json, struct, subprocess, shutil
from concurrent.futures import ThreadPoolExecutor
H = os.path.dirname(os.path.abspath(__file__))
N = os.path.dirname(H)
R = os.path.dirname(N)
sys.path.insert(0, H)
import symdb

B = os.environ.get('HM_BUILD', os.path.join(R, 'build/GHYE6S'))
O = os.environ.get('HM_OUT', os.path.join(R, 'build/native-hybrid'))
IR = os.path.join(R, 'build/hybrid/ir')
W = os.path.join(O, 'units')
BU = symdb.BU
DATA_BASE = 0x81800000
DATA_END = 0x82000000
LLVM = '/usr/lib/llvm-18/bin/'

def run(cmd, **kw):
    r = subprocess.run(cmd, capture_output=True, text=True, **kw)
    return r

def dol_reader(path):
    d = open(path, 'rb').read()
    offs = struct.unpack('>18I', d[0:72]); addrs = struct.unpack('>18I', d[72:144]); sizes = struct.unpack('>18I', d[144:216])
    secs = [(a, s, o) for o, a, s in zip(offs, addrs, sizes) if s]
    def read(a, n):
        for (sa, ss, so) in secs:
            if sa <= a and a + n <= sa + ss: return d[so + a - sa: so + a - sa + n]
        return None
    return read

def parse_deny(db, words):
    addrs, names = set(), set()
    for w in words:
        w = w.strip()
        if not w or w.startswith('#'): continue
        m = re.fullmatch(r'(?:0x)?([0-9A-Fa-f]{8})-(?:0x)?([0-9A-Fa-f]{8})', w)
        if m:
            lo, hi = int(m.group(1), 16), int(m.group(2), 16)
            addrs |= {a for a in db.funcs if lo <= a < hi}
        elif re.fullmatch(r'(?:0x)?[0-9A-Fa-f]{8}', w): addrs.add(int(w, 16))
        else: names.add(w)
    return addrs, names

def write_if_changed(path, text):
    if os.path.exists(path) and open(path).read() == text: return
    open(path, 'w').write(text)

def main():
    a = sys.argv[1:]
    j = os.cpu_count() or 8
    if '-j' in a: i = a.index('-j'); j = int(a[i + 1]); del a[i:i + 2]
    nolink = '--no-link' in a
    ufile = os.path.join(H, 'native.txt')
    if '--units' in a: ufile = a[a.index('--units') + 1]
    os.makedirs(W, exist_ok=True)
    # tools
    so = os.path.join(O, 'GuestMem.so')
    newer = lambda a, b: os.path.exists(a) and os.path.getmtime(a) >= os.path.getmtime(b)
    if not newer(so, os.path.join(H, 'pass/GuestMem.cpp')):
        r = run([os.path.join(H, 'pass/build.sh'), so])
        if r.returncode: sys.exit('pass build failed:\n' + r.stderr)
    hmrt = os.path.join(O, 'hmrt.bc')
    if not newer(hmrt, os.path.join(H, 'pass/hmrt.c')): r = run(['clang-18', '--target=x86_64-pc-linux-gnu', '-O2', '-fwrapv', '-ffp-contract=off', '-fno-math-errno',
             '-emit-llvm', '-c', os.path.join(H, 'pass/hmrt.c'), '-o', hmrt])
    if not os.path.exists(hmrt): sys.exit('hmrt failed')
    # symbols, entries, deny
    db = symdb.SymDB(os.path.join(B, 'main.elf'), os.path.join(B, 'mp/mp.elf'))
    gsyms = os.path.join(W, 'globals.syms'); db.write_globals(gsyms + '.tmp'); write_if_changed(gsyms, open(gsyms + '.tmp').read())
    nm = os.path.join(O, 'main.nm'); mpnm = os.path.join(O, 'mp.nm')
    open(nm, 'w').write(run([BU + 'nm', '-S', '--defined-only', os.path.join(B, 'main.elf')]).stdout)
    open(mpnm, 'w').write(run([BU + 'nm', '-S', '--defined-only', os.path.join(B, 'mp/mp.elf')]).stdout)
    # recompiled entry points: every function start ppc2c will emit (from its funcs.h of a plain run)
    gen0 = os.path.join(O, 'gen0')
    ppc2c = [sys.executable, os.path.join(N, 'recomp/ppc2c.py'), '--dol', os.path.join(B, 'main_mp.dol'),
             '--syms', nm, '--syms', mpnm, '--hle', os.path.join(N, 'recomp/hle.txt')]
    objd = run([BU + 'objdump', '-h', os.path.join(B, 'mp/mp.elf')]).stdout
    mpdata = [l.split()[3] for l in objd.splitlines() if len(l.split()) > 3 and l.split()[1] == '.mpdata'][0]
    mpend = [l.split()[0] for l in run([BU + 'nm', os.path.join(B, 'mp/mp.elf')]).stdout.splitlines() if l.endswith(' mp_end')][0]
    ppc2c += ['--nocode', '%s-%s' % (mpdata, mpend), '--export', 'IdleContext']
    if not os.path.exists(os.path.join(gen0, 'funcs.h')):
        r = run(ppc2c + ['--out', gen0])
        if r.returncode: sys.exit('ppc2c failed:\n' + r.stderr)
    entries = os.path.join(W, 'entries.txt')
    write_if_changed(entries, ''.join(m.group(1) + '\n' for m in (re.match(r'void fn_([0-9A-F]{8})\(', l) for l in open(os.path.join(gen0, 'funcs.h'))) if m))
    deny_words = []
    df = os.path.join(H, 'deny.txt')
    if os.path.exists(df): deny_words += [l.split('#')[0] for l in open(df)]
    deny_words += re.split(r'[,\s]+', os.environ.get('HM_NATIVE_DENY_BUILD', ''))
    daddr, dname = parse_deny(db, deny_words)
    # HLE-replaced functions stay with their host implementation
    nocall = set()
    for l in open(os.path.join(N, 'recomp/hle.txt')):
        p = l.split('#')[0].split()
        if len(p) < 2: continue
        s = p[1]
        ad = int(s[3:], 16) if re.fullmatch(r'fn_[0-9A-Fa-f]{8}', s) else (int(s, 16) if re.fullmatch(r'[0-9A-Fa-f]{8}', s) else (db.glob.get(s) or (None,))[0])
        if ad is None: continue
        if p[0] in ('replace', 'savectx'): daddr.add(ad)
        if p[0] == 'savectx': nocall.add(ad)
    # functions the co-op mod patched in main_mp.dol stay recompiled (their decomp C is the unpatched code)
    rd0 = dol_reader(os.path.join(B, 'main.dol')); rd1 = dol_reader(os.path.join(B, 'main_mp.dol'))
    patched = 0
    for ad, (name, sz) in db.funcs.items():
        if sz and rd0(ad, sz) != rd1(ad, sz): daddr.add(ad); patched += 1
    deny = os.path.join(W, 'deny.txt')
    write_if_changed(deny, ''.join('%08X\n' % ad for ad in sorted(daddr)) + ''.join(n + '\n' for n in sorted(dname)))
    nocallf = os.path.join(W, 'nocall.txt')
    open(nocallf, 'w').write(''.join('%08X\n' % x for x in sorted(nocall)))
    hostf = os.path.join(W, 'host.txt')
    open(hostf, 'w').write('\n'.join(re.findall(r'hmh_(\w+)\(', open(os.path.join(H, 'pass/hmrt.c')).read())) + '\n')
    # units
    units = []
    allu = sorted(os.path.relpath(os.path.join(dp, f), IR)[:-3] for dp, _, fs in os.walk(IR) for f in fs if f.endswith('.ll'))
    if os.path.exists(ufile):
        for l in open(ufile):
            l = l.split('#')[0].strip()
            if l == 'all': units += allu
            elif l: units.append(l)
    else: units = allu
    units = [u for u in dict.fromkeys(units) if os.path.exists(os.path.join(IR, u + '.ll'))]
    uid = lambda u: re.sub(r'\W', '_', u)
    deps = [so, hmrt, entries, deny, gsyms]
    def fresh(u, out):
        return all(newer(out, x) for x in deps + [os.path.join(IR, u + '.ll')])
    def pass_run(u, base, measure=False):
        d = os.path.join(W, uid(u))
        if measure and fresh(u, d + '.meta'): return None
        env = dict(os.environ, GM_SYMS=gsyms + ':' + d + '.syms', GM_ENTRIES=entries, GM_DENY=deny, GM_HOST=hostf, GM_NOCALL=nocallf,
                   GM_DATA='%08X' % base, GM_UNIT=uid(u), GM_META=d + '.meta')
        if not os.path.exists(d + '.syms'): db.write_unit(os.path.basename(u), d + '.syms')
        r = run([LLVM + 'opt', '-load-pass-plugin=' + so, '-passes=guestmem', os.path.join(IR, u + '.ll'), '-o', d + '.pass.bc'], env=env)
        if r.returncode: return 'pass crashed: ' + (r.stderr.strip().splitlines() or ['?'])[0][:200]
        return None
    print('units: %d, deny: %d addresses (%d mod-patched)' % (len(units), len(daddr), patched))
    # step 1: measure the private data each unit needs; step 2: place it and translate for real
    with ThreadPoolExecutor(j) as ex: errs = dict(zip(units, ex.map(lambda u: pass_run(u, DATA_BASE, True), units)))
    bases = {}; cur = DATA_BASE
    for u in units:
        if errs[u]: continue
        sz = 0
        for l in open(os.path.join(W, uid(u) + '.meta')):
            if l.startswith('blob '): sz = int(l.split()[2])
        bases[u] = cur; cur += (sz + 31) & ~31
    if cur > DATA_END: sys.exit('reserved data region overflow: %08X' % cur)
    def compile_unit(u):
        d = os.path.join(W, uid(u))
        bf = d + '.base'
        if fresh(u, d + '.o') and os.path.exists(bf) and open(bf).read() == '%08X' % bases[u]: return None
        e = pass_run(u, bases[u])
        if e: return e
        for cmd in ([LLVM + 'llvm-link', '--only-needed', '--internalize', d + '.pass.bc', hmrt, '-o', d + '.link.bc'],
                    [LLVM + 'opt', '-O2', d + '.link.bc', '-o', d + '.opt.bc'],
                    [LLVM + 'llc', '-O2', '-relocation-model=pic', '-filetype=obj', d + '.opt.bc', '-o', d + '.o']):
            r = run(cmd)
            if r.returncode: return '%s failed: %s' % (os.path.basename(cmd[0]), (r.stderr.strip().splitlines() or ['?'])[0][:200])
        open(bf, 'w').write('%08X' % bases[u])
        return None
    ok = [u for u in units if not errs[u]]
    with ThreadPoolExecutor(j) as ex: errs.update(dict(zip(ok, ex.map(compile_unit, ok))))
    # collect
    natives = {}; fails = []; blobs = []; objs = []; warns = 0
    sizes = {a: s for a, (n, s) in db.funcs.items()}
    for u in units:
        if errs[u]: fails.append((u, '-', errs[u])); continue
        objs.append(os.path.join(W, uid(u) + '.o'))
        for l in open(os.path.join(W, uid(u) + '.meta')):
            p = l.rstrip('\n').split(' ', 3)
            if p[0] == 'native':
                ad = int(p[1], 16)
                if ad in natives: continue
                natives[ad] = (p[2], p[3], u)
            elif p[0] == 'fail': fails.append((u, p[2], p[3] if len(p) > 3 else ''))
            elif p[0] == 'blob': blobs.append((int(p[1], 16), int(p[2]), p[3]))
            elif p[0] == 'warn': warns += 1
    natives = {ad: v for ad, v in natives.items() if ad not in daddr}
    with open(os.path.join(O, 'native_funcs.txt'), 'w') as f:
        for ad in sorted(natives): f.write('%08X %s %s %s\n' % (ad, natives[ad][0], natives[ad][1], natives[ad][2]))
    with open(os.path.join(O, 'native_fails.txt'), 'w') as f:
        for u, n, why in fails: f.write('%s %s %s\n' % (u, n, why))
    nat_sorted = sorted(natives)
    with open(os.path.join(O, 'hm_native.c'), 'w') as f:
        f.write('// generated by native/hybrid/build_hybrid.py: private data of the native units, runtime switches\n'
                '#include <string.h>\n#include <stdlib.h>\n#include <stdio.h>\n')
        for (_, _, s_) in blobs: f.write('extern const unsigned char %s[];\n' % s_)
        f.write('static const struct { unsigned addr, size; const unsigned char *data; } blobs[] = {\n')
        for (ad, sz, s_) in blobs: f.write('  {0x%08X, %d, %s},\n' % (ad, sz, s_))
        f.write('  {0, 0, 0}};\n#define NNAT %d\nstatic const unsigned nat_addr[NNAT + 1] = {\n' % len(nat_sorted))
        for ad in nat_sorted: f.write('0x%08X,\n' % ad)
        f.write('0};\nunsigned char hm_native_off[NNAT + 1];\n'
                '// HM_NATIVE_DENY="lo-hi,addr,..." (hex): those functions run recompiled; HM_NATIVE_ONLY: everything else does\n'
                'static void parse(const char *e, unsigned char v) {\n'
                '  while (e && *e) { char *x; unsigned lo = strtoul(e, &x, 16), hi = lo + 1; if (x == e) { e++; continue; }\n'
                '    if (*x == \'-\') hi = strtoul(x + 1, &x, 16);\n'
                '    for (int i = 0; i < NNAT; i++) if (nat_addr[i] >= lo && nat_addr[i] < hi) hm_native_off[i] = v;\n'
                '    e = x; }\n}\n'
                'void hm_native_init(void) {\n'
                '  for (int i = 0; blobs[i].size; i++) memcpy((unsigned char *)0x200000000ULL + (blobs[i].addr & 0x01FFFFFF), blobs[i].data, blobs[i].size);\n'
                '  if (getenv("HM_NATIVE_ONLY")) { memset(hm_native_off, 1, NNAT); parse(getenv("HM_NATIVE_ONLY"), 0); }\n'
                '  parse(getenv("HM_NATIVE_DENY"), 1);\n'
                '  int n = 0; for (int i = 0; i < NNAT; i++) n += !hm_native_off[i];\n'
                '  fprintf(stderr, "[hybrid] %d of %d native functions enabled\\n", n, NNAT);\n}\n')
    nb = sum(sizes.get(ad, 0) for ad in natives)
    from collections import Counter
    why = Counter(re.sub(r'(0x)?[0-9A-Fa-f]{8}|\b\w*fn_\w+|@\S+|%\S+|global \S+', '#', w)[:70] for _, _, w in fails)
    print('native functions: %d (%d bytes of guest code), failed: %d, warnings: %d' % (len(natives), nb, len(fails), warns))
    for w, n in why.most_common(15): print('  %5d %s' % (n, w))
    if nolink: return
    # recompiled code with native functions replaced, then link
    nl = os.path.join(O, 'native_list.txt')
    with open(nl, 'w') as f:
        for ad in nat_sorted: f.write('%08X\n' % ad)
    r = run(ppc2c + ['--out', os.path.join(O, 'gen'), '--native-list', nl])
    if r.returncode: sys.exit('ppc2c failed:\n' + r.stderr)
    allo = os.path.join(O, 'native_all.o')   # one relocatable object (the command line can't hold thousands)
    lst = os.path.join(O, 'native_objs.txt'); open(lst, 'w').write('\n'.join(objs) + '\n')
    r = run(['ld', '-r', '-o', allo, '@' + lst])
    if r.returncode: sys.exit('ld -r failed:\n' + r.stderr[-3000:])
    extra = ';'.join([allo, os.path.join(O, 'hm_native.c')])
    r = run(['cmake', '-S', N, '-B', os.path.join(O, 'cmake'), '-G', 'Ninja', '-DHM_GEN_DIR=' + os.path.join(O, 'gen'),
             '-DHM_DOL=' + os.path.join(B, 'main_mp.dol'), '-DHM_EXTRA_SRC=' + extra] + os.environ.get('CMAKE_ARGS', '').split())
    if r.returncode: sys.exit('cmake failed:\n' + r.stdout[-2000:] + r.stderr[-2000:])
    r = subprocess.run(['ninja', '-C', os.path.join(O, 'cmake')] + os.environ.get('NINJA_ARGS', '').split())
    if r.returncode: sys.exit('ninja failed')
    print(os.path.join(O, 'cmake/hauntedmansion'))

if __name__ == '__main__':
    main()
