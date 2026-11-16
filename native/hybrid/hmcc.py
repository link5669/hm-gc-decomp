#!/usr/bin/env python3
"""Front end: decomp unit -> LLVM IR (clang-18, powerpc-unknown-eabi, -O0).
usage: hmcc.py UNIT [UNIT...]        (UNIT = path relative to src/, e.g. auto/text_8002A860.cpp)
       hmcc.py --all [-j N]          (every Matching unit of candidates.json; writes build/hybrid/frontend.json)
IR goes to build/hybrid/ir/<unit>.ll ; the (vtshim-rewritten) source copy to build/hybrid/src/<unit>."""
import json, os, subprocess, sys, re
from concurrent.futures import ThreadPoolExecutor
H = os.path.dirname(os.path.abspath(__file__))
R = os.path.dirname(os.path.dirname(H))
OUT = os.path.join(R, 'build/hybrid')
sys.path.insert(0, H)
import vtshim

INCS = ['include', 'tools/rea/ref/dolsdk2004/include', 'tools/rea/ref/dolsdk2004/include/libc',
        'build/GHYE6S/include', 'src']
COMMON = ['clang-18', '--target=powerpc-unknown-eabi', '-O0', '-S', '-emit-llvm', '-ffreestanding',
          '-fno-builtin', '-fno-exceptions', '-fno-rtti', '-fno-threadsafe-statics', '-fno-short-enums',
          '-fno-discard-value-names', '-w', '-fdeclspec', '-Wno-implicit-function-declaration', '-Wno-error=implicit-function-declaration', '-Wno-implicit-int', '-Wno-error=int-conversion', '-Wno-error=incompatible-pointer-types', '-Wno-error=incompatible-function-pointer-types', '-Wno-error=return-type', '-ferror-limit=200', '-fno-strict-aliasing', '-fwrapv',
          '-DNDEBUG=1', '-DBUILD_VERSION=0', '-DVERSION_GHYE6S', '-D__HM_NATIVE__=1',
          '-include', os.path.join(H, 'include/mwcc_compat.h')]

def strip_asm_functions(t):
    """`asm RET name(args) { ... }` (MWCC asm functions) -> prototype only; those stay recompiled."""
    out = []; i = 0; n = 0
    pat = re.compile(r'^[ \t]*((?:(?:static|extern|inline|__declspec\([^)]*\)|__attribute__\(\([^)]*\)\))\s+)*)asm\s+([^{;]*?)\{', re.M)
    while True:
        mt = pat.search(t, i)
        if not mt: out.append(t[i:]); break
        out.append(t[i:mt.start()])
        d = 0; j = mt.end() - 1
        while j < len(t):
            if t[j] == '{': d += 1
            elif t[j] == '}':
                d -= 1
                if d == 0: break
            j += 1
        out.append('%s%s;' % (mt.group(1), mt.group(2).strip())); n += 1
        i = j + 1
    return ''.join(out)

def fix_declspec(t):
    t = strip_asm_functions(t)
    t = re.sub(r'__declspec\(\s*section\s+("[^"]*"|\w+)\s*\)', lambda m: '__attribute__((section(%s)))' % m.group(1), t)
    t = re.sub(r'__declspec\(\s*weak\s*\)', '__attribute__((weak))', t)
    # absolute-address variables: `volatile T name : 0xADDR;`
    t = re.sub(r'^((?:(?:volatile|const)\s+)*[\w ]+?)\s*(\*+)?\s*(\w+)((?:\[[^\]]*\])*)\s*:\s*(0x[0-9A-Fa-f]+)\s*;',
               lambda m: '#define %s (*(%s %s(*)%s)%s)' % (m.group(3), m.group(1), m.group(2) or '', m.group(4), m.group(5)) if m.group(4) else
                         '#define %s (*(%s %s*)%s)' % (m.group(3), m.group(1), m.group(2) or '', m.group(5)), t, flags=re.M)
    # MWCC accepts assignment to a cast lvalue: `#define cps ((unsigned char*)src)` used as lvalue
    t = re.sub(r'#define ([lc]p[sd]) \(\((unsigned (?:char|long)\s*\*)\)(\w+)\)', r'#define \1 (*(\2*)&\3)', t)
    t = re.sub(r'^(\s*)\(\(([\w ]+?) ?\*\)(\w+)\) = ([^;]+);', r'\1\3 = (__typeof__(\3))(\4);', t, flags=re.M)
    t = re.sub(r'\+\+\(\((\w+) \*\)\((\w+)\)\)', r'(\2 = (__typeof__(\2))((\1 *)\2 + 1))', t)
    t = re.sub(r'^(\s*)\((\w+) \*\)(\w+) \+= ([^;]+);', r'\1\3 = (__typeof__(\3))((\2 *)\3 + (\4));', t, flags=re.M)
    return t

def patched_headers():
    """copies of include/ headers whose declarations clang rejects (build/hybrid/inc, searched first)"""
    d = os.path.join(OUT, 'inc'); os.makedirs(d, exist_ok=True)
    s = open(os.path.join(R, 'include/musyx_priv.h'), errors='replace').read()
    s = s.replace('void *memcpy(void *, const void *, u32);', '/* memcpy: declared by <string.h> (size_t is unsigned int) */')
    open(os.path.join(d, 'musyx_priv.h'), 'w').write(s)
    return d

def prepare(unit):
    """source text after the MWCC-compat rewrites (declspec, abs vars, vtshim); raises Unsupported-like string via .fatal"""
    text = open(os.path.join(R, 'src', unit), errors='replace').read()
    text = fix_declspec(text)
    if unit.endswith('.cpp'): text = vtshim.rewrite(text)
    return text

def cmd_for(unit, srcfile, out):
    cpp = unit.endswith('.cpp')
    cmd = COMMON + (['-x', 'c++', '-std=gnu++98'] if cpp else ['-x', 'c', '-std=gnu99'])
    cmd += ['-I' + os.path.join(OUT, 'inc'), '-I' + os.path.dirname(os.path.join(R, 'src', unit))] + ['-I' + os.path.join(R, i) for i in INCS]
    return cmd + ['-o', out, srcfile]

CONFLICT = re.compile(r"^(?P<f>[^:\n]+):(?P<l>\d+):(?P<c>\d+): error: (?:conflicting types for '(?P<n1>\w+)'|redeclaration of '(?P<n2>\w+)' with a different type|functions that differ only in their return type cannot be overloaded|static declaration of '(?P<n3>\w+)' follows non-static declaration|conflicting types for '(?P<n4>\w+)')", re.M)

def declarator_end(lines, l, c):
    """(name, new_name_pos_end, q, is_def) for the declarator whose name starts at line l col c (1-based)"""
    line = lines[l - 1]
    mw = re.match(r'\w+', line[c - 1:])
    if not mw: return None
    name = mw.group(0); a = c - 1 + len(name)
    flat = line[a:] + '\n' + '\n'.join(lines[l:l + 40])
    d = 0; q = 0
    while q < len(flat):
        ch = flat[q]
        if ch in '([': d += 1
        elif ch in ')]':
            d -= 1
            if d == 0 and not re.match(r'\s*[\[(]', flat[q + 1:]): q += 1; break
        elif d == 0 and ch in ';={,': break
        q += 1
    if '\n' in flat[:q]: return None
    return name, a, q, bool(re.match(r'\s*(\n\s*)?\{', flat[q:]) or re.match(r'\s*(const\s*)?\{', flat[q:]))

def label_decl(lines, l, c, newname, symname):
    r = declarator_end(lines, l, c)
    if not r: return False
    name, a, q, isdef = r
    line = lines[l - 1]
    symname = re.sub(r'(__hm\d+)+$', '', symname)
    seg = re.sub(r'\s*__asm__\("[^"]*"\)', '', line[a:a + q])
    lines[l - 1] = line[:c - 1] + newname + seg + ' __asm__("%s")' % symname + line[a + q:]
    return True

def repair(text, stderr, dst):
    """MWCC accepts conflicting redeclarations that clang rejects. The declaration that is not a definition gets a
    private name bound to the same symbol (asm label) and the uses between it and the other declaration follow it;
    `static` after non-static is dropped. Returns new text or None."""
    lines = text.split('\n'); n = 0
    blocks = re.split(r'(?m)^(?=[^\s][^\n]*?:\d+:\d+: error: )', stderr)
    todo = []
    for blk in blocks:
        mt = re.match(r"([^:\n]+):(\d+):(\d+): error: ([^\n]*)", blk)
        if not mt or os.path.abspath(mt.group(1)) != os.path.abspath(dst): continue
        l, c, msg = int(mt.group(2)), int(mt.group(3)), mt.group(4)
        prev = re.search(r"^([^:\n]+):(\d+):(\d+): note: previous (?:declaration|definition)", blk, re.M)
        m1 = re.match(r"static declaration of '(\w+)' follows non-static", msg)
        if m1: todo.append((l, c, 'static', None)); continue
        if msg.startswith(('conflicting types for', 'redeclaration of', 'redefinition of', 'functions that differ only in their return type')):
            pv = (int(prev.group(2)), int(prev.group(3))) if prev and os.path.abspath(prev.group(1)) == os.path.abspath(dst) else None
            todo.append((l, c, 'conflict', pv))
    done = set()
    for l, c, kind, pv in sorted(todo, key=lambda x: (-x[0], -x[1])):
        if kind == 'static':
            line = lines[l - 1]; i = line.rfind('static', 0, c)
            if i >= 0: lines[l - 1] = line[:i] + line[i + 6:]; n += 1
            continue
        r = declarator_end(lines, l, c)
        if not r: continue
        name, a, q, isdef = r
        if (name, l) in done: continue
        pr = declarator_end(lines, pv[0], pv[1]) if pv else None
        if isdef and pv and pr and not pr[3]:      # rename the earlier prototype and the uses up to this definition
            pl, pc = pv
            if pl >= l: continue
            new = '%s__hm%d' % (re.sub(r'(__hm\d+)+$', '', name), pl)
            if not label_decl(lines, pl, pc, new, name): continue
            for k in range(pl, l - 1):
                lines[k] = re.sub(r'\b%s\b' % re.escape(name), new, lines[k])
            n += 1
        elif isdef and pv and pr and pr[3] and re.search(r'\b(inline|static)\b', lines[pv[0] - 1][:pv[1]]) and pv[0] < l:
            pl, pc = pv; nm0 = re.sub(r'(__hm\d+)+$', '', name); new = '%s__hm%d' % (nm0, pl)
            lines[pl - 1] = lines[pl - 1][:pc - 1] + new + lines[pl - 1][pc - 1 + len(name):]
            for k in range(pl, l - 1): lines[k] = re.sub(r'\b%s\b' % re.escape(name), new, lines[k])
            n += 1
        elif isdef and re.search(r'\b(inline|static)\b', lines[l - 1][:c]):   # private redefinition: new name, no symbol
            new = '%s__hm%d' % (re.sub(r'(__hm\d+)+$', '', name), l)
            lines[l - 1] = lines[l - 1][:c - 1] + new + lines[l - 1][a:]
            tail = '\n'.join(lines[l:])
            lines = lines[:l] + re.sub(r'\b%s\b' % re.escape(name), new, tail).split('\n')
            n += 1
        elif not isdef:       # rename this (later) declaration and everything after it
            new = '%s__hm%d' % (re.sub(r'(__hm\d+)+$', '', name), l)
            if not label_decl(lines, l, c, new, name): continue
            tail = '\n'.join(lines[l:])
            lines = lines[:l] + re.sub(r'\b%s\b' % re.escape(name), new, tail).split('\n')
            n += 1
    return '\n'.join(lines) if n else None

def compile_unit(unit):
    text = fix_declspec(open(os.path.join(R, 'src', unit), errors='replace').read())
    if unit.endswith('.cpp'):
        text = vtshim.rewrite(text)
        bad = [n for n in text.notes if 'inheritance' in n or 'preprocessor' in n]
        if bad: return 'vtshim unsupported: ' + bad[0]
    dst = os.path.join(OUT, 'src', unit)
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    ll = os.path.join(OUT, 'ir', unit + '.ll')
    os.makedirs(os.path.dirname(ll), exist_ok=True)
    for attempt in range(6):
        open(dst, 'w').write(text)
        r = subprocess.run(cmd_for(unit, dst, ll), capture_output=True, text=True, cwd=R)
        if r.returncode == 0: return 'ok'
        nt = repair(text, r.stderr, dst)
        if nt is None or nt == text: break
        text = nt
    if os.path.exists(ll): os.unlink(ll)
    errs = [l for l in r.stderr.splitlines() if 'error' in l]
    return (errs[0] if errs else r.stderr.strip().splitlines()[0] if r.stderr.strip() else 'fail')

def main():
    patched_headers()
    a = sys.argv[1:]
    j = 8
    if '-j' in a:
        i = a.index('-j'); j = int(a[i + 1]); del a[i:i + 2]
    if a and a[0] == '--all':
        cand = json.load(open(os.path.join(H, 'candidates.json')))
        units = sorted({c['unit'] for c in cand if c['class'] != 'nonmatching'})
        with ThreadPoolExecutor(j) as ex:
            res = dict(zip(units, ex.map(compile_unit, units)))
        json.dump(res, open(os.path.join(OUT, 'frontend.json'), 'w'), indent=0)
        report(cand, res)
    else:
        for u in a: print(u, compile_unit(u))

def report(cand, res):
    from collections import Counter, defaultdict
    byu = defaultdict(lambda: [0, 0, ''])
    for c in cand:
        if c['class'] == 'nonmatching': continue
        x = byu[c['unit']]; x[0] += 1; x[1] += c['size']; x[2] = c['class']
    tot = Counter(); ok = Counter(); fn = Counter(); fok = Counter(); un = Counter(); uok = Counter()
    for u, (n, b, cl) in byu.items():
        tot[cl] += b; fn[cl] += n; un[cl] += 1
        if res.get(u) == 'ok': ok[cl] += b; fok[cl] += n; uok[cl] += 1
    for cl in sorted(tot):
        print('%-8s units %4d/%4d funcs %5d/%5d bytes %8d/%8d (%.1f%%)' % (cl, uok[cl], un[cl], fok[cl], fn[cl], ok[cl], tot[cl], 100.0 * ok[cl] / tot[cl]))
    T = sum(tot.values()); O = sum(ok.values())
    print('TOTAL units %d/%d funcs %d/%d bytes %d/%d (%.1f%%)' % (sum(uok.values()), sum(un.values()), sum(fok.values()), sum(fn.values()), O, T, 100.0 * O / T))
    msgs = Counter()
    for u, r in res.items():
        if r != 'ok': msgs[re.sub(r'^.*?error: ', '', r)[:90]] += 1
    for m, n in msgs.most_common(25): print('%5d  %s' % (n, m))

if __name__ == '__main__': main()
