#!/usr/bin/env python3
"""vtshim: rewrite C++ polymorphic structs so clang's layout equals MWCC's (see DESIGN.md).

MWCC: vtable pointer after ALL of a class's own data members; vtable slot k at +8+4k.
Each polymorphic class becomes a plain struct: data members (original order), then `void **__vt;`
(only when no polymorphic base), then one inline non-virtual wrapper per virtual method calling __vt[2+k].
A non-virtual method of a derived class with the same name+arity as a base virtual reuses its slot.
Unsupported (class left untouched, reported through `rewrite(text).notes`): virtual/multiple inheritance
involving a polymorphic base, preprocessor lines inside a class body, varargs virtuals (wrapper omitted).
usage: python3 vtshim.py FILE.cpp   -> prints rewritten text
"""
import re, sys

class Result(str):
    notes = ()
    poly = ()

BUILTIN = {'int', 'char', 'short', 'long', 'float', 'double', 'void', 'bool'}
QUAL_IMPLIES_INT = {'unsigned', 'signed', 'long', 'short'}
QUAL = {'const', 'volatile', 'struct', 'class', 'enum', 'union', 'static', 'register'} | QUAL_IMPLIES_INT


def mask(t):
    """blank comments, string and char literals (same length)"""
    out = list(t); i = 0; n = len(t)
    while i < n:
        c = t[i]
        if c == '/' and i + 1 < n and t[i + 1] == '/':
            j = t.find('\n', i); j = n if j < 0 else j
            for k in range(i, j): out[k] = ' '
            i = j
        elif c == '/' and i + 1 < n and t[i + 1] == '*':
            j = t.find('*/', i + 2); j = n if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != '\n': out[k] = ' '
            i = j
        elif c in '"\'':
            j = i + 1
            while j < n and t[j] != c:
                if t[j] == '\\': j += 1
                if j < n and t[j] == '\n': break
                j += 1
            for k in range(i + 1, min(j, n)): out[k] = ' '
            i = j + 1
        else:
            i += 1
    return ''.join(out)


def match_brace(m, i):
    """m[i] == '{' -> index after matching '}'"""
    d = 0; n = len(m)
    while i < n:
        c = m[i]
        if c == '{': d += 1
        elif c == '}':
            d -= 1
            if d == 0: return i + 1
        i += 1
    return -1


def split_statements(m, s, e):
    """statements of a class body m[s:e]; yields (start, end, is_func_body)"""
    out = []; i = s; st = s; d = 0; paren_seen = False; eq_seen = False
    while i < e:
        c = m[i]
        if c in '([': d += 1
        elif c in ')]': d -= 1
        elif c == '{':
            head = m[st:i]
            kw = head.strip().split(None, 1)[0] if head.strip() else ''
            if d == 0 and '(' in head and not eq_seen and kw not in ('typedef', 'struct', 'union', 'enum', 'class'):
                j = match_brace(m, i)
                if j < 0 or j > e: j = e
                out.append((st, j, True)); i = j; st = j; paren_seen = eq_seen = False
                continue
            j = match_brace(m, i)
            if j < 0 or j > e: j = e
            i = j; continue
        elif c == ';' and d == 0:
            out.append((st, i + 1, False)); st = i + 1; paren_seen = eq_seen = False
        elif c == '=' and d == 0: eq_seen = True
        i += 1
    return out


def split_top(s, sep=','):
    out = []; d = 0; cur = ''
    for c in s:
        if c in '([<' and not (c == '<' and False): d += 1
        if c in ')]>': d -= 1
        if c == sep and d == 0: out.append(cur); cur = ''
        else: cur += c
    if cur.strip() or out: out.append(cur)
    return out


def parse_param(p, idx):
    """-> (type_str, name, decl_with_name_and_default)"""
    p = p.strip()
    default = ''
    m = re.search(r'\s*=\s*(.*)$', p)
    if m and '(' not in p[:m.start()].split('=')[0][-1:]:
        default = ' = ' + m.group(1); p = p[:m.start()].rstrip()
    fp = re.search(r'\(\s*([*&]+)\s*(\w*)\s*\)\s*[(\[]', p)
    if fp:
        name = fp.group(2) or '__a%d' % idx
        ty = p[:fp.start(2)] + p[fp.end(2):] if fp.group(2) else p
        decl = (p[:fp.start(2)] + name + p[fp.end(2):]) if not fp.group(2) else p
        decl = p[:fp.end(1)] + name + p[fp.end(2):] if not fp.group(2) else p
        return ty, name, decl + default
    arr = ''
    ma = re.search(r'(\[[^\]]*\])+\s*$', p)
    if ma: arr = ma.group(0); core = p[:ma.start()].rstrip()
    else: core = p
    mw = re.search(r'(\w+)\s*$', core)
    named = False
    if mw:
        before = core[:mw.start()].strip()
        last = mw.group(1)
        if before:
            bw = re.findall(r'\w+', before)
            if before[-1] in '*&': named = True
            elif last in BUILTIN or last in QUAL_IMPLIES_INT: named = False
            elif all(w in QUAL for w in bw):
                named = any(w in QUAL_IMPLIES_INT for w in bw) or any(w in BUILTIN for w in bw)
            else: named = not (last in QUAL)
        if arr and not before: named = False
    if named:
        name = mw.group(1)
        ty = core[:mw.start()].rstrip() + (' *' if arr else '')
        return ty, name, p + default
    name = '__a%d' % idx
    ty = core + (' *' if arr else '')
    return ty, name, core + ' ' + name + arr + default


def parse_func(txt):
    """txt: statement masked text (without body) -> dict or None"""
    i = txt.find('(')
    if i < 0: return None
    head = txt[:i]
    if re.search(r'\(\s*[*&]', txt[i:i + 4]) and head.strip() and not re.search(r'(\w|>)\s*$', head.strip()[-1:]):
        return None
    if re.match(r'\s*(typedef|friend|using)\b', txt): return None
    # name
    mn = re.search(r'(operator\s*(?:\(\s*\)|[^\s(]+)|~\s*\w+|\w+)\s*$', head)
    if not mn: return None
    name = re.sub(r'\s+', '', mn.group(1))
    # function pointer data member: `void (*fp)(int);` -> head has no name before '('
    if head.strip() == '' and name == '': return None
    # matching close paren
    d = 0; j = i
    while j < len(txt):
        if txt[j] == '(': d += 1
        elif txt[j] == ')':
            d -= 1
            if d == 0: break
        j += 1
    params = txt[i + 1:j]
    rest = txt[j + 1:]
    ret = head[:mn.start()]
    return dict(name=name, ret=ret, params=params, rest=rest)


class Cls:
    def __init__(self, name):
        self.name = name; self.poly = False; self.slots = []  # (name, arity)
        self.ok = True


def expand_funclike_macros(text):
    """function-like #defines (DV(n) virtual void n();) whose body (transitively) declares virtuals"""
    defs = {}
    for mt in re.finditer(r'^[ \t]*#[ \t]*define[ \t]+(\w+)\(([^)]*)\)[ \t]*((?:[^\n\\]|\\\n)*)', text, re.M):
        defs[mt.group(1)] = ([a.strip() for a in mt.group(2).split(',') if a.strip()], mt.group(3).replace('\\\n', ' '))
    if not any('virtual' in b or any(n in b for n in defs) for a, b in defs.values()): return text
    def vir(n, seen=()):
        a, b = defs[n]
        return 'virtual' in b or any(k in re.findall(r'\w+', b) and k not in seen and vir(k, seen + (n,)) for k in defs if k != n)
    names = [n for n in defs if vir(n)]
    if not names: return text
    parts = re.split(r'(^[ \t]*#[ \t]*define[^\n]*(?:\\\n[^\n]*)*)', text, flags=re.M)
    def expand(s, depth=0):
        if depth > 8: return s
        out = []; i = 0
        pat = re.compile(r'\b(%s)\s*\(' % '|'.join(map(re.escape, names)))
        while True:
            mt = pat.search(s, i)
            if not mt: out.append(s[i:]); break
            out.append(s[i:mt.start()])
            j = mt.end(); d = 1; args = []; cur = ''
            while j < len(s) and d:
                c = s[j]
                if c == '(': d += 1
                elif c == ')':
                    d -= 1
                    if d == 0: break
                if c == ',' and d == 1: args.append(cur.strip()); cur = ''
                else: cur += c
                j += 1
            args.append(cur.strip())
            params, body = defs[mt.group(1)]
            def sub(bs):
                m2 = {p: (args[k] if k < len(args) else '') for k, p in enumerate(params)}
                bs = re.sub(r'(\w+)\s*##\s*(\w+)', lambda x: ('\x00%s\x00%s' % (m2.get(x.group(1), x.group(1)), m2.get(x.group(2), x.group(2)))), bs)
                bs = re.sub(r'\b(\w+)\b', lambda x: m2.get(x.group(1), x.group(1)) if '\x00' not in x.group(0) else x.group(0), bs)
                return bs.replace('\x00', '')
            r = sub(body)
            out.append(expand(r, depth + 1)); i = j + 1
        return ''.join(out)
    for i in range(0, len(parts), 2): parts[i] = expand(parts[i])
    return ''.join(parts)


def expand_virtual_macros(text):
    text = expand_funclike_macros(text)
    """object-like #defines whose body declares virtuals are expanded textually (MWCC decomp uses them as V10 ...)"""
    defs = {}
    for mt in re.finditer(r'^[ \t]*#[ \t]*define[ \t]+(\w+)[ \t]+((?:[^\n\\]|\\\n)*)', text, re.M):
        body = mt.group(2).replace('\\\n', ' ')
        if re.search(r'\bvirtual\b', body) and not re.match(r'\(', body): defs[mt.group(1)] = body
    for n, b in defs.items():
        text = re.sub(r'(?<![\w#])%s\b(?!\s*\()' % re.escape(n),
                      lambda mm: b, re.sub(r'^([ \t]*#[ \t]*define[ \t]+%s\b)' % re.escape(n), r'\1', text, flags=re.M), count=0) if False else text
        parts = re.split(r'(^[ \t]*#[ \t]*define[^\n]*(?:\\\n[^\n]*)*)', text, flags=re.M)
        for i in range(0, len(parts), 2):
            parts[i] = re.sub(r'(?<![\w#])%s\b' % re.escape(n), lambda mm: b, parts[i])
        text = ''.join(parts)
    return text


def rewrite(text, notes=None):
    text = expand_virtual_macros(text)
    m = mask(text)
    classes = {}
    edits = []  # (start, end, replacement)
    nts = []
    impl_renames = []  # (Cls, name)
    pos_end = -1
    for mt in re.finditer(r'\b(struct|class)\s+(\w+)\s*(:[^{;]*)?\{', m):
        if mt.start() < pos_end: continue
        if re.search(r'(enum|typedef|template\s*<[^>]*>)\s*$', m[max(0, mt.start() - 40):mt.start()]):
            pass
        kw, name, bases = mt.group(1), mt.group(2), mt.group(3)
        bo = mt.end() - 1
        be = match_brace(m, bo)
        if be < 0: continue
        body_s, body_e = bo + 1, be - 1
        stmts = split_statements(m, body_s, body_e)
        c = Cls(name)
        # bases
        blist = []
        if bases:
            for b in split_top(bases[1:]):
                b = b.strip()
                virt = bool(re.search(r'\bvirtual\b', b))
                bn = re.sub(r'\b(public|private|protected|virtual)\b', '', b).strip()
                blist.append((bn, virt))
        poly_bases = [classes[b] for b, v in blist if b in classes and classes[b].poly]
        has_virtual = bool(re.search(r'\bvirtual\b', m[body_s:body_e]))
        if not has_virtual and not poly_bases:
            classes[name] = c
            continue  # not polymorphic; but may contain nested polymorphic classes: continue scanning inside
        pos_end = be
        if any(v for b, v in blist) or len(blist) > 1 and poly_bases:
            nts.append('%s: virtual/multiple inheritance' % name); c.ok = False; c.poly = True
            classes[name] = c; continue
        if re.search(r'\n\s*#', m[body_s:body_e]):
            nts.append('%s: preprocessor in body' % name); c.ok = False; c.poly = True
            classes[name] = c; continue
        c.poly = True
        base = poly_bases[0] if poly_bases else None
        slots = list(base.slots) if base else []
        keep = []; wrappers = []; vt_placed = False
        for (s, e, isbody) in stmts:
            tm = m[s:e]; to = text[s:e]
            while True:
                lab = re.match(r'\s*(public|private|protected)\s*:', tm)
                if not lab: break
                keep.append(to[:lab.end()]); s += lab.end(); tm = m[s:e]; to = text[s:e]
            if not tm.strip() or tm.strip() == ';':
                continue
            if isbody:
                fb = tm.rfind('{')  # approximate; use first top-level '{' after the params
                # find top-level '{'
                d = 0; k = 0
                for k, ch in enumerate(tm):
                    if ch == '(': d += 1
                    elif ch == ')': d -= 1
                    elif ch == '{' and d == 0: break
                decl_m = tm[:k]; body_o = to[k:]
            else:
                decl_m = tm.rstrip(';'); body_o = None
            f = parse_func(decl_m)
            isvirt = bool(re.match(r'\s*(?:inline\s+)?virtual\b', decl_m)) or bool(re.search(r'\bvirtual\b', decl_m[:decl_m.find('(')] if '(' in decl_m else ''))
            if isvirt and f is not None and not base and not vt_placed:
                keep.append('public: void **__vt;'); vt_placed = True
            if f is None or (f['name'] == name) or (f['name'].startswith('~') and not isvirt and not base):
                keep.append(re.sub(r'\bvirtual\b\s*', '', to, count=1) if isvirt and f is not None and f['name'].startswith('~') else to)
                if isvirt and f is not None and f['name'].startswith('~') and f['name'] != '~' + name:
                    pass
                if isvirt and f is not None and f['name'].startswith('~'):
                    key = ('~', 0)
                    if key not in slots: slots.append(key)
                continue
            params = [p for p in split_top(f['params']) if p.strip()]
            if len(params) == 1 and params[0].strip() == 'void': params = []
            key = (f['name'], len(params))
            if f['name'].startswith('~'): key = ('~', 0)
            if not isvirt and key not in slots:
                if re.match(r'\s*static\b', decl_m): keep.append(to); continue
                keep.append(to); continue
            if f['name'].startswith('~'):
                keep.append(re.sub(r'\bvirtual\b\s*', '', to, count=1))
                if key not in slots: slots.append(key)
                continue
            if re.match(r'\s*static\b', decl_m): keep.append(to); continue
            if key not in slots: slots.append(key)
            k = slots.index(key)
            ret = re.sub(r'\b(virtual|inline|static)\b', '', f['ret']).strip() or 'int'
            ret_o = ret
            # take original-text params (comments masked in m only; use original slice for names)
            pi = text.find('(', s + (len(decl_m) - len(decl_m.lstrip())) + decl_m.find('('))  # '(' position
            ps = [parse_param(p, n) for n, p in enumerate(params) if p.strip() != '...']
            const = ' const' if re.match(r'\s*const\b', f['rest']) else ''
            ptypes = ''.join(', ' + t for t, n, d in ps)
            args = ''.join(', ' + n for t, n, d in ps)
            if '...' in f['params']:
                nts.append('%s::%s: varargs virtual, declaration only' % (name, f['name']))
                wrappers.append('%s %s(%s)%s;' % (ret_o, f['name'], ', '.join(d for t, n, d in ps) + (', ' if ps else '') + '...', const))
                continue
            sig = ', '.join(d for t, n, d in ps)
            call = '((%s (*)(%s *%s))(((%s *)this)->__vt[%d]))((%s *)this%s)' % (ret_o, name, ptypes, name, 2 + k, name, args)
            ret_stmt = ('return ' if ret_o.strip() != 'void' else '') + call + ';'
            wrappers.append('%s %s(%s)%s { %s }' % (ret_o, f['name'], sig, const, ret_stmt))
            if body_o is not None:
                wrappers.append('%s %s__impl(%s)%s %s' % (ret_o, f['name'], sig, const, body_o))
            impl_renames.append((name, f['name'], ret_o, sig, const))
        extra = ''
        extra += ' public: ' + ' '.join(wrappers) if wrappers else ''
        new = text[mt.start():bo + 1] + ' ' + ' '.join(keep) + extra + ' }'
        c.slots = slots
        classes[name] = c
        edits.append((mt.start(), be, new))
    # out-of-class definitions of virtual methods: `Cls::name(` -> `Cls::name__impl(` + declaration in class
    if edits and impl_renames:
        want = {(cn, mn) for cn, mn, *_ in impl_renames}
        for cn, mn in want:
            pat = re.compile(r'\b%s\s*::\s*%s\s*\(' % (re.escape(cn), re.escape(mn)))
            for mt in pat.finditer(m):
                if any(a <= mt.start() < b for a, b, _ in edits): continue
                edits.append((mt.start(), mt.end(), '%s::%s__impl(' % (cn, mn)))
                # declare impl in class
        for i, (a, b, new) in enumerate(edits):
            if not new.startswith(('struct', 'class')): continue
            cn = re.match(r'(?:struct|class)\s+(\w+)', new).group(1)
            decls = ''
            for (c2, mn, ret, sig, const) in impl_renames:
                if c2 == cn and any(re.search(r'\b%s::%s__impl' % (cn, mn), e[2]) for e in edits):
                    if '%s__impl(' % mn in new: continue
                    decls += ' %s %s__impl(%s)%s;' % (ret, mn, sig, const)
            if decls: edits[i] = (a, b, new[:-1] + decls + ' }')
    out = text
    for a, b, new in sorted(edits, key=lambda x: -x[0]):
        out = out[:a] + new + out[b:]
    r = Result(out); r.notes = nts; r.poly = [n for n, c in classes.items() if c.poly]
    return r


if __name__ == '__main__':
    r = rewrite(open(sys.argv[1], errors='replace').read())
    sys.stdout.write(r)
    for n in r.notes: sys.stderr.write(n + '\n')
