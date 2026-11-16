#!/usr/bin/env python3
"""Static recompiler: Gekko (GameCube PowerPC) DOL -> C.

Each guest function becomes `void fn_XXXXXXXX(CPU *restrict c)` (see native/runtime/ppc.h).
Function boundaries come from ELF symbol tables (nm -S) of the decomp build plus the mod;
uncovered text ranges become functions too. Output: <out>/funcs.h, <out>/gen_NNN.c, <out>/table.c.

The output is derived from the user's game binary: it stays in build/, never in git.

usage: ppc2c.py --dol main_mp.dol --syms a.nm [--syms b.nm] --hle hle.txt --out build/native/gen
"""
import argparse, os, re, struct, sys
from collections import defaultdict

def sx16(v): return v - 0x10000 if v & 0x8000 else v
def sx(v, bits): return v - (1 << bits) if v & (1 << (bits - 1)) else v
def mask(mb, me):
    m = 0
    if mb <= me:
        for i in range(mb, me + 1): m |= 1 << (31 - i)
    else:
        for i in range(0, me + 1): m |= 1 << (31 - i)
        for i in range(mb, 32): m |= 1 << (31 - i)
    return m

class Dol:
    def __init__(self, path):
        d = open(path, 'rb').read()
        self.d = d
        off = struct.unpack('>18I', d[0:72]); adr = struct.unpack('>18I', d[72:144]); sz = struct.unpack('>18I', d[144:216])
        self.text = [(adr[i], sz[i], off[i]) for i in range(7) if sz[i]]
        self.data = [(adr[i], sz[i], off[i]) for i in range(7, 18) if sz[i]]
        self.entry = struct.unpack('>I', d[224:228])[0]
    def word(self, a):
        for (base, size, off) in self.text + self.data:
            if base <= a < base + size:
                return struct.unpack('>I', self.d[off + a - base: off + a - base + 4])[0]
        return None
    nocode = ()
    def in_text(self, a):
        return any(b <= a < b + s for (b, s, o) in self.text) and not any(lo <= a < hi for lo, hi in self.nocode)

SPR_NAMES = {1: 'xer', 8: 'lr', 9: 'ctr'}

class Func:
    def __init__(self, start, end, name):
        self.start, self.end, self.name = start, end, name
        self.entries = {start}   # extra external entry points get their own C function

def load_funcs(dol, symfiles, nocode=()):
    syms = {}
    for f in symfiles:
        for line in open(f):
            p = line.split()
            if len(p) == 4 and p[2] in 'TtWw':
                a, s = int(p[0], 16), int(p[1], 16)
                if s and dol.in_text(a):
                    if a not in syms or syms[a][0] < s: syms[a] = (s, p[3])
    starts = sorted(syms)
    funcs = []
    for (base, size, off) in dol.text:
        end_sec = base + size
        cur = base
        for a in [x for x in starts if base <= x < end_sec] + [end_sec]:
            if a > cur:
                # gap: make a function unless it is all zero padding
                if not any(lo <= cur < hi for lo, hi in nocode) and any(dol.word(x) not in (0, None) for x in range(cur, a, 4)):
                    funcs.append(Func(cur, a, 'gap_%08X' % cur))
            if a == end_sec: break
            s, n = syms[a]
            e = min(a + s, end_sec)
            funcs.append(Func(a, e, n))
            cur = e
    funcs.sort(key=lambda f: f.start)
    # clip overlaps
    for i in range(len(funcs) - 1):
        if funcs[i].end > funcs[i + 1].start: funcs[i].end = funcs[i + 1].start
    return [f for f in funcs if f.end > f.start]

class Gen:
    def __init__(self, dol, funcs, hle):
        self.dol, self.funcs, self.hle = dol, funcs, hle
        self.fstart = {f.start: f for f in funcs}
        self.starts = [f.start for f in funcs]
        self.unk = defaultdict(int)
        self.warn = []
        import bisect; self.bisect = bisect
        # data words pointing into text: jump-table / mid-function targets
        self.dataptr = defaultdict(set)
        for (base, size, off) in dol.data:
            for a in range(base, base + size, 4):
                w = dol.word(a)
                if w and (w & 3) == 0 and dol.in_text(w):
                    f = self.func_at(w)
                    if f: self.dataptr[f.start].add(w)

    def func_at(self, a):
        i = self.bisect.bisect_right(self.starts, a) - 1
        if i >= 0 and self.funcs[i].start <= a < self.funcs[i].end: return self.funcs[i]
        return None

    def fname(self, a): return 'fn_%08X' % a

    # ---- pass 1: find external entry points (b/bl into the middle of a function)
    def scan_entries(self):
        for f in self.funcs:
            for pc in range(f.start, f.end, 4):
                ins = self.dol.word(pc); op = ins >> 26
                if op == 18:
                    t = (sx(ins & 0x3FFFFFC, 26) + (0 if ins & 2 else pc)) & 0xFFFFFFFF
                    lk = ins & 1
                    if lk or not (f.start <= t < f.end):
                        g = self.func_at(t)
                        if g and t != g.start: g.entries.add(t)
                elif op == 16:
                    t = (sx16(ins & 0xFFFC) + (0 if ins & 2 else pc)) & 0xFFFFFFFF
                    if not (f.start <= t < f.end):
                        g = self.func_at(t)
                        if g and t != g.start: g.entries.add(t)

    def all_entries(self):
        return sorted(e for f in self.funcs for e in f.entries)

    # ---- per-function code generation
    def gen_func(self, f, entry):
        lines = []
        body, labels = self.gen_body(f)
        name = self.fname(entry)
        if entry in self.hle:
            return 'void %s(CPU *RESTRICT c) { %s(c); }\n' % (name, self.hle[entry])
        out = ['void %s(CPU *RESTRICT c) {' % name, '  u32 ea; (void)ea; u64 t64; (void)t64; double fa, fb; (void)fa; (void)fb;']
        if entry != f.start:
            out.append('  goto L_%08X;' % entry)
            labels.add(entry)
        for (pc, code) in body:
            if pc in labels: out.append('L_%08X:;' % pc)
            out.append('  ' + code if code else '')
        out.append('}')
        return '\n'.join(x for x in out if x != '') + '\n'

    def gen_body(self, f):
        labels = set()
        body = []
        jt = sorted(self.dataptr.get(f.start, ()))
        self.cur = f
        for pc in range(f.start, f.end, 4):
            ins = self.dol.word(pc)
            code = self.ins(pc, ins, f, labels, jt)
            body.append((pc, code))
        # fall through off the end
        last = self.dol.word(f.end - 4)
        if not self.is_terminal(last):
            nxt = self.func_at(f.end)
            if nxt and nxt.start == f.end:
                body.append((f.end, '%s(c); return;' % self.fname(f.end)))
            else:
                body.append((f.end, 'rt_unimpl(c, 0x%08X, 0); return;' % f.end))
        return body, labels

    def is_terminal(self, ins):
        op = ins >> 26
        if op == 18 and not (ins & 1): return True
        if op == 19:
            xo = (ins >> 1) & 0x3FF; bo = (ins >> 21) & 31
            if xo in (16, 528) and (bo & 0x14) == 0x14 and not (ins & 1): return True
            if xo == 50: return True
        return False

    def br_to(self, pc, t, f, labels, cond=None):
        """code for a branch to t (no link)"""
        if f.start <= t < f.end:
            labels.add(t)
            chk = 'CHK(c); ' if t <= pc else ''
            s = '%sgoto L_%08X;' % (chk, t)
        else:
            g = self.func_at(t)
            if g is None:
                self.warn.append('branch to non-code %08X at %08X' % (t, pc))
                s = 'rt_unimpl(c, 0x%08X, 0x%08X); return;' % (pc, t)
            else:
                s = '%s(c); return;' % self.fname(t)
        return s if cond is None else 'if (%s) { %s }' % (cond, s)

    def call(self, pc, t):
        g = self.func_at(t)
        if g is None:
            self.warn.append('call to non-code %08X at %08X' % (t, pc))
            return 'rt_unimpl(c, 0x%08X, 0x%08X);' % (pc, t)
        if t in self.save_ctx:
            return ('c->lr = 0x%08X; if (setjmp(*rt_save_jb(c))) { c->r[3] = 1; } else { %s(c); rt_after_save(c); }'
                    % (pc + 4, self.fname(t)))
        return 'c->lr = 0x%08X; %s(c);' % (pc + 4, self.fname(t))

    def bcond(self, ins):
        bo = (ins >> 21) & 31; bi = (ins >> 16) & 31
        conds = []
        pre = ''
        if not (bo & 4):
            pre = 'c->ctr--; '
            conds.append('c->ctr == 0' if bo & 2 else 'c->ctr != 0')
        if not (bo & 16):
            conds.append(('CRBIT(c, %d)' if bo & 8 else '!CRBIT(c, %d)') % bi)
        return pre, (' && '.join(conds) if conds else None)

    def ins(self, pc, ins, f, labels, jt):
        op = ins >> 26
        rd = (ins >> 21) & 31; ra = (ins >> 16) & 31; rb = (ins >> 11) & 31; rc_ = (ins >> 6) & 31
        simm = sx16(ins & 0xFFFF); uimm = ins & 0xFFFF
        Rc = ins & 1
        R = lambda n: 'c->r[%d]' % n
        RA0 = lambda: '0' if ra == 0 else R(ra)
        cr0 = lambda v: ' c->cr[0] = cmp_s((s32)(%s), 0, c->so);' % v
        F = lambda n: 'c->f[%d].d' % n
        P1 = lambda n: 'c->ps1[%d]' % n
        U = lambda: self.unimpl(pc, ins)
        if ins == 0: return 'rt_unimpl(c, 0x%08X, 0); return;' % pc
        if op == 7: return '%s = (u32)((s32)%s * %d);' % (R(rd), R(ra), simm)
        if op == 8: return 't64 = (u64)(u32)~%s + (u32)%d + 1; %s = (u32)t64; c->ca = (u8)(t64 >> 32);' % (R(ra), simm, R(rd))
        if op == 10:
            return 'c->cr[%d] = cmp_u(%s, 0x%X, c->so);' % (rd >> 2, R(ra), uimm)
        if op == 11:
            return 'c->cr[%d] = cmp_s((s32)%s, %d, c->so);' % (rd >> 2, R(ra), simm)
        if op in (12, 13):
            s = 't64 = (u64)%s + (u32)%d; %s = (u32)t64; c->ca = (u8)(t64 >> 32);' % (R(ra), simm, R(rd))
            if op == 13: s += cr0(R(rd))
            return s
        if op == 14: return '%s = %s + %d;' % (R(rd), RA0(), simm) if ra else '%s = %d;' % (R(rd), simm)
        if op == 15: return '%s = %s + 0x%X;' % (R(rd), RA0(), (simm << 16) & 0xFFFFFFFF) if ra else '%s = 0x%X;' % (R(rd), (simm << 16) & 0xFFFFFFFF)
        if op == 16:
            t = (sx16(ins & 0xFFFC) + (0 if ins & 2 else pc)) & 0xFFFFFFFF
            pre, cond = self.bcond(ins)
            if ins & 1:  # bcl
                if t == pc + 4: return pre + 'c->lr = 0x%08X;' % (pc + 4)
                return pre + 'if (%s) { %s }' % (cond or '1', self.call(pc, t))
            return pre + self.br_to(pc, t, f, labels, cond)
        if op == 17: return 'rt_sc(c, 0x%08X);' % pc
        if op == 18:
            t = (sx(ins & 0x3FFFFFC, 26) + (0 if ins & 2 else pc)) & 0xFFFFFFFF
            if ins & 1: return self.call(pc, t)
            return self.br_to(pc, t, f, labels)
        if op == 19: return self.op19(pc, ins, f, labels, jt)
        if op in (20, 21, 23):
            sh = rb; mb = (ins >> 6) & 31; me = (ins >> 1) & 31; m = mask(mb, me)
            rot = 'rotl(%s, %d)' % (R(rd), sh) if op != 23 else 'rotl(%s, %s)' % (R(rd), R(rb))
            if op == 21 and op != 23:
                if sh == 0: rot = R(rd)
            if op == 20: s = '%s = (%s & 0x%X) | (%s & 0x%X);' % (R(ra), rot, m, R(ra), (~m) & 0xFFFFFFFF)
            else: s = '%s = %s & 0x%X;' % (R(ra), rot, m)
            if Rc: s += cr0(R(ra))
            return s
        if op == 24: return '%s = %s | 0x%X;' % (R(ra), R(rd), uimm)
        if op == 25: return '%s = %s | 0x%X;' % (R(ra), R(rd), uimm << 16)
        if op == 26: return '%s = %s ^ 0x%X;' % (R(ra), R(rd), uimm)
        if op == 27: return '%s = %s ^ 0x%X;' % (R(ra), R(rd), uimm << 16)
        if op == 28: return '%s = %s & 0x%X;' % (R(ra), R(rd), uimm) + cr0(R(ra))
        if op == 29: return '%s = %s & 0x%X;' % (R(ra), R(rd), uimm << 16) + cr0(R(ra))
        if op == 31: return self.op31(pc, ins)
        # D-form loads/stores
        ea = '(%s + %d)' % (RA0(), simm) if ra else '(u32)%d' % simm
        upd = lambda: ' %s = ea;' % R(ra)
        if op in (32, 33, 34, 35, 40, 41, 42, 43):
            ld = {32: 'ld32(ea)', 33: 'ld32(ea)', 34: 'ld8(ea)', 35: 'ld8(ea)', 40: 'ld16(ea)', 41: 'ld16(ea)',
                  42: '(u32)(s32)(s16)ld16(ea)', 43: '(u32)(s32)(s16)ld16(ea)'}[op]
            s = 'ea = %s; %s = %s;' % (ea, R(rd), ld)
            if op & 1: s += upd()
            return s
        if op in (36, 37, 38, 39, 44, 45):
            st = {36: 'st32', 37: 'st32', 38: 'st8', 39: 'st8', 44: 'st16', 45: 'st16'}[op]
            cast = {'st32': '', 'st8': '(u8)', 'st16': '(u16)'}[st]
            s = 'ea = %s; %s(ea, %s%s);' % (ea, st, cast, R(rd))
            if op & 1: s += upd()
            return s
        if op == 46:
            return 'ea = %s; for (int i = %d; i < 32; i++, ea += 4) c->r[i] = ld32(ea);' % (ea, rd)
        if op == 47:
            return 'ea = %s; for (int i = %d; i < 32; i++, ea += 4) st32(ea, c->r[i]);' % (ea, rd)
        if op in (48, 49):
            s = 'ea = %s; %s = %s = (double)ldf32(ea);' % (ea, F(rd), P1(rd))
            if op & 1: s += upd()
            return s
        if op in (50, 51):
            s = 'ea = %s; c->f[%d].u = ld64(ea);' % (ea, rd)
            if op & 1: s += upd()
            return s
        if op in (52, 53):
            s = 'ea = %s; stf32(ea, (float)%s);' % (ea, F(rd))
            if op & 1: s += upd()
            return s
        if op in (54, 55):
            s = 'ea = %s; st64(ea, c->f[%d].u);' % (ea, rd)
            if op & 1: s += upd()
            return s
        if op in (56, 57, 60, 61):
            d12 = sx(ins & 0xFFF, 12); w = (ins >> 15) & 1; i = (ins >> 12) & 7
            e = '(%s + %d)' % (RA0(), d12) if ra else '(u32)%d' % d12
            s = 'ea = %s; %s' % (e, self.psq(op in (56, 57), rd, w, i))
            if op in (57, 61): s += upd()
            return s
        if op == 59: return self.op59(pc, ins)
        if op == 63: return self.op63(pc, ins)
        if op == 4: return self.op4(pc, ins)
        if op == 3: return 'rt_trap(c, 0x%08X);' % pc  # twi
        return U()

    def psq(self, load, r, w, i):
        # inline fast path for unquantized (float) GQRs, the common case; quantized types go to the runtime
        if load:
            fast = ('{ c->f[%d].d = (double)ldf32(ea); c->ps1[%d] = 1.0; }' % (r, r)) if w else \
                   ('{ c->f[%d].d = (double)ldf32(ea); c->ps1[%d] = (double)ldf32(ea + 4); }' % (r, r))
            return 'if (likely(!(c->gqr[%d] & 0x70000))) %s else rt_psq_l(c, ea, %d, %d, %d);' % (i, fast, r, w, i)
        fast = ('stf32(ea, (float)c->f[%d].d);' % r) if w else \
               ('{ stf32(ea, (float)c->f[%d].d); stf32(ea + 4, (float)c->ps1[%d]); }' % (r, r))
        return 'if (likely(!(c->gqr[%d] & 0x7))) %s else rt_psq_st(c, ea, %d, %d, %d);' % (i, fast, r, w, i)

    def unimpl(self, pc, ins):
        self.unk['%08X' % ins] += 1
        return 'rt_unimpl(c, 0x%08X, 0x%08X);' % (pc, ins)

    def op19(self, pc, ins, f, labels, jt):
        xo = (ins >> 1) & 0x3FF
        bt = (ins >> 21) & 31; ba = (ins >> 16) & 31; bb = (ins >> 11) & 31
        if xo == 16:  # bclr
            pre, cond = self.bcond(ins)
            if ins & 1:  # blrl
                return pre + 'if (%s) { u32 t = c->lr; c->lr = 0x%08X; rt_call(c, t); }' % (cond or '1', pc + 4)
            return pre + ('if (%s) return;' % cond if cond else 'return;')
        if xo == 528:  # bcctr
            pre, cond = self.bcond(ins)
            if ins & 1:
                return pre + 'if (%s) { c->lr = 0x%08X; rt_call(c, c->ctr); }' % (cond or '1', pc + 4)
            # jump table within the function, else indirect tail call
            cases = [t for t in jt if f.start <= t < f.end]
            sw = ''
            if cases:
                for t in cases: labels.add(t)
                sw = 'switch (c->ctr) { %s default: break; } ' % ' '.join('case 0x%08X: goto L_%08X;' % (t, t) for t in cases)
            s = sw + 'rt_call(c, c->ctr); return;'
            return pre + ('if (%s) { %s }' % (cond, s) if cond else s)
        if xo == 0: return 'c->cr[%d] = c->cr[%d];' % (bt >> 2, ba >> 2)
        crops = {257: '%s & %s', 449: '%s | %s', 193: '%s ^ %s', 225: '!(%s & %s)', 33: '!(%s | %s)',
                 289: '!(%s ^ %s)', 129: '%s & !%s', 417: '%s | !%s'}
        if xo in crops:
            e = crops[xo] % ('CRBIT(c, %d)' % ba, 'CRBIT(c, %d)' % bb)
            return 'SETCRBIT(c, %d, (%s) & 1);' % (bt, e)
        if xo == 150: return ';'  # isync
        if xo == 50: return 'rt_rfi(c, 0x%08X); return;' % pc
        return self.unimpl(pc, ins)

    def op31(self, pc, ins):
        xo = (ins >> 1) & 0x3FF
        rd = (ins >> 21) & 31; ra = (ins >> 16) & 31; rb = (ins >> 11) & 31; Rc = ins & 1
        R = lambda n: 'c->r[%d]' % n
        RA0 = '0' if ra == 0 else R(ra)
        cr0 = lambda v: (' c->cr[0] = cmp_s((s32)(%s), 0, c->so);' % v) if Rc else ''
        ea = '(%s + %s)' % (RA0, R(rb)) if ra else R(rb)
        xo9 = xo & 0x1FF
        oe = (ins >> 10) & 1
        arith = {266: '%s = %s + %s;', 40: '%s = %s - %s;'}
        if xo9 in (266, 40, 10, 8, 138, 136, 202, 200, 234, 232, 104, 235, 491, 459, 75, 11) and xo9 == (xo & 0x1FF):
            if oe: return self.unimpl(pc, ins)
            a, b, d = R(ra), R(rb), R(rd)
            if xo9 == 266: s = '%s = %s + %s;' % (d, a, b)
            elif xo9 == 40: s = '%s = %s - %s;' % (d, b, a)
            elif xo9 == 10: s = 't64 = (u64)%s + %s; %s = (u32)t64; c->ca = (u8)(t64 >> 32);' % (a, b, d)
            elif xo9 == 8: s = 't64 = (u64)(u32)~%s + %s + 1; %s = (u32)t64; c->ca = (u8)(t64 >> 32);' % (a, b, d)
            elif xo9 == 138: s = 't64 = (u64)%s + %s + c->ca; %s = (u32)t64; c->ca = (u8)(t64 >> 32);' % (a, b, d)
            elif xo9 == 136: s = 't64 = (u64)(u32)~%s + %s + c->ca; %s = (u32)t64; c->ca = (u8)(t64 >> 32);' % (a, b, d)
            elif xo9 == 202: s = 't64 = (u64)%s + c->ca; %s = (u32)t64; c->ca = (u8)(t64 >> 32);' % (a, d)
            elif xo9 == 200: s = 't64 = (u64)(u32)~%s + c->ca; %s = (u32)t64; c->ca = (u8)(t64 >> 32);' % (a, d)
            elif xo9 == 234: s = 't64 = (u64)%s + c->ca + 0xFFFFFFFFull; %s = (u32)t64; c->ca = (u8)(t64 >> 32);' % (a, d)
            elif xo9 == 232: s = 't64 = (u64)(u32)~%s + c->ca + 0xFFFFFFFFull; %s = (u32)t64; c->ca = (u8)(t64 >> 32);' % (a, d)
            elif xo9 == 104: s = '%s = (u32)-(s32)%s;' % (d, a)
            elif xo9 == 235: s = '%s = (u32)((s32)%s * (s32)%s);' % (d, a, b)
            elif xo9 == 491: s = '%s = divw_(%s, %s);' % (d, a, b)
            elif xo9 == 459: s = '%s = divwu_(%s, %s);' % (d, a, b)
            elif xo9 == 75: s = '%s = (u32)(((s64)(s32)%s * (s32)%s) >> 32);' % (d, a, b)
            elif xo9 == 11: s = '%s = (u32)(((u64)%s * %s) >> 32);' % (d, a, b)
            return s + cr0(d)
        S, A, B = R(rd), R(ra), R(rb)
        logic = {28: '%s & %s', 444: '%s | %s', 316: '%s ^ %s', 476: '~(%s & %s)', 124: '~(%s | %s)', 284: '~(%s ^ %s)',
                 60: '%s & ~%s', 412: '%s | ~%s'}
        if xo in logic: return '%s = %s;' % (A, logic[xo] % (S, B)) + cr0(A)
        if xo == 24: return '%s = (%s & 0x20) ? 0 : (%s << (%s & 31));' % (A, B, S, B) + cr0(A)
        if xo == 536: return '%s = (%s & 0x20) ? 0 : (%s >> (%s & 31));' % (A, B, S, B) + cr0(A)
        if xo == 792:
            return ('{ u32 n = %s & 0x3F; s32 v = (s32)%s; if (n >= 32) { %s = (u32)(v >> 31); c->ca = v < 0; } '
                    'else { %s = (u32)(v >> n); c->ca = (v < 0) && n && ((u32)v & ((1u << n) - 1)); } }' % (B, S, A, A)) + cr0(A)
        if xo == 824:
            n = rb
            if n == 0: return '%s = %s; c->ca = 0;' % (A, S) + cr0(A)
            return ('{ s32 v = (s32)%s; %s = (u32)(v >> %d); c->ca = (v < 0) && ((u32)v & 0x%X); }' % (S, A, n, (1 << n) - 1)) + cr0(A)
        if xo == 26: return '%s = %s ? __builtin_clz(%s) : 32;' % (A, S, S) + cr0(A)
        if xo == 922: return '%s = (u32)(s32)(s16)%s;' % (A, S) + cr0(A)
        if xo == 954: return '%s = (u32)(s32)(s8)%s;' % (A, S) + cr0(A)
        if xo == 0: return 'c->cr[%d] = cmp_s((s32)%s, (s32)%s, c->so);' % (rd >> 2, A, B)
        if xo == 32: return 'c->cr[%d] = cmp_u(%s, %s, c->so);' % (rd >> 2, A, B)
        # indexed loads/stores
        ldx = {23: 'ld32(ea)', 55: 'ld32(ea)', 87: 'ld8(ea)', 119: 'ld8(ea)', 279: 'ld16(ea)', 311: 'ld16(ea)',
               343: '(u32)(s32)(s16)ld16(ea)', 375: '(u32)(s32)(s16)ld16(ea)', 20: 'ld32(ea)',
               534: '__builtin_bswap32(ld32(ea))', 790: '(u32)__builtin_bswap16(ld16(ea))'}
        if xo in ldx:
            s = 'ea = %s; %s = %s;' % (ea, S, ldx[xo])
            if xo in (55, 119, 311, 375): s += ' %s = ea;' % A
            return s
        stx = {151: ('st32', ''), 183: ('st32', ''), 215: ('st8', '(u8)'), 247: ('st8', '(u8)'), 407: ('st16', '(u16)'),
               439: ('st16', '(u16)'), 662: ('st32', '__builtin_bswap32'), 918: ('st16', '(u16)__builtin_bswap16')}
        if xo in stx:
            fn, cast = stx[xo]
            s = 'ea = %s; %s(ea, %s(%s));' % (ea, fn, cast, S)
            if xo in (183, 247, 439): s += ' %s = ea;' % A
            return s
        if xo == 150: return 'ea = %s; st32(ea, %s); c->cr[0] = 2 | c->so;' % (ea, S)  # stwcx.
        if xo in (535, 567):
            s = 'ea = %s; c->f[%d].d = c->ps1[%d] = (double)ldf32(ea);' % (ea, rd, rd)
            return s + (' %s = ea;' % A if xo == 567 else '')
        if xo in (599, 631):
            s = 'ea = %s; c->f[%d].u = ld64(ea);' % (ea, rd)
            return s + (' %s = ea;' % A if xo == 631 else '')
        if xo in (663, 695):
            s = 'ea = %s; stf32(ea, (float)c->f[%d].d);' % (ea, rd)
            return s + (' %s = ea;' % A if xo == 695 else '')
        if xo in (727, 759):
            s = 'ea = %s; st64(ea, c->f[%d].u);' % (ea, rd)
            return s + (' %s = ea;' % A if xo == 759 else '')
        if xo == 983: return 'ea = %s; st32(ea, (u32)c->f[%d].u);' % (ea, rd)
        if xo == 1014: return 'rt_dcbz(%s);' % ea
        if xo in (54, 86, 470, 982, 278, 246, 598, 854, 306, 566): return ';'  # cache/sync/tlb
        if xo == 19: return '%s = ((u32)c->cr[0]<<28)|((u32)c->cr[1]<<24)|((u32)c->cr[2]<<20)|((u32)c->cr[3]<<16)|((u32)c->cr[4]<<12)|((u32)c->cr[5]<<8)|((u32)c->cr[6]<<4)|(u32)c->cr[7];' % S
        if xo == 144:
            crm = (ins >> 12) & 0xFF
            return ' '.join('c->cr[%d] = (%s >> %d) & 15;' % (i, S, 28 - 4 * i) for i in range(8) if crm & (0x80 >> i))
        if xo == 83: return '%s = c->msr;' % S
        if xo == 146: return 'rt_mtmsr(c, %s);' % S
        if xo in (339, 467):
            spr = ((ins >> 16) & 31) | (((ins >> 11) & 31) << 5)
            if xo == 339:
                if spr == 8: return '%s = c->lr;' % S
                if spr == 9: return '%s = c->ctr;' % S
                if spr == 1: return '%s = ((u32)c->so << 31) | ((u32)c->ov << 30) | ((u32)c->ca << 29) | (c->spr[1] & 0x7F);' % S
                if 912 <= spr <= 919: return '%s = c->gqr[%d];' % (S, spr - 912)
                return '%s = rt_mfspr(c, %d);' % (S, spr)
            if spr == 8: return 'c->lr = %s;' % S
            if spr == 9: return 'c->ctr = %s;' % S
            if spr == 1: return 'c->so = (%s >> 31) & 1; c->ov = (%s >> 30) & 1; c->ca = (%s >> 29) & 1; c->spr[1] = %s & 0x7F;' % (S, S, S, S)
            if 912 <= spr <= 919: return 'c->gqr[%d] = %s;' % (spr - 912, S)
            return 'rt_mtspr(c, %d, %s);' % (spr, S)
        if xo == 371:
            tbr = ((ins >> 16) & 31) | (((ins >> 11) & 31) << 5)
            return '%s = rt_mftb(c, %d);' % (S, 1 if tbr == 269 else 0)
        if xo in (595, 210, 242, 659): return ';' if xo in (210, 242) else '%s = 0;' % S  # segment regs
        if xo == 4: return 'rt_trap(c, 0x%08X);' % pc
        if xo == 512: return 'c->cr[%d] = (c->so << 3) | (c->ov << 2) | (c->ca << 1); c->so = c->ov = c->ca = 0;' % (rd >> 2)
        if xo == 597:  # lswi
            n = rb or 32
            return 'ea = %s; { int n = %d, r = %d; while (n > 0) { u32 w = 0; for (int k = 0; k < 4; k++) { w <<= 8; if (n > 0) { w |= ld8(ea++); n--; } } c->r[r] = w; r = (r + 1) & 31; } }' % (RA0, n, rd)
        if xo == 725:  # stswi
            n = rb or 32
            return 'ea = %s; { int n = %d, r = %d; while (n > 0) { u32 w = c->r[r]; for (int k = 0; k < 4 && n > 0; k++, n--) st8(ea++, (u8)(w >> (24 - 8 * k))); r = (r + 1) & 31; } }' % (RA0, n, rd)
        return self.unimpl(pc, ins)

    def fcr1(self, ins):
        return ' c->cr[1] = (c->fpscr >> 28) & 15;' if ins & 1 else ''

    def op59(self, pc, ins):
        xo = (ins >> 1) & 31
        d, a, b, cc = (ins >> 21) & 31, (ins >> 16) & 31, (ins >> 11) & 31, (ins >> 6) & 31
        F = lambda n: 'c->f[%d].d' % n
        ex = {18: '%s / %s' % (F(a), F(b)), 20: '%s - %s' % (F(a), F(b)), 21: '%s + %s' % (F(a), F(b)),
              22: 'sqrt(%s)' % F(b), 24: '1.0 / %s' % F(b), 25: '%s * %s' % (F(a), F(cc)),
              28: 'fma(%s, %s, -%s)' % (F(a), F(cc), F(b)), 29: 'fma(%s, %s, %s)' % (F(a), F(cc), F(b)),
              30: '-fma(%s, %s, -%s)' % (F(a), F(cc), F(b)), 31: '-fma(%s, %s, %s)' % (F(a), F(cc), F(b))}
        if xo in ex:
            return 'c->f[%d].d = c->ps1[%d] = rs(%s);' % (d, d, ex[xo]) + self.fcr1(ins)
        return self.unimpl(pc, ins)

    def op63(self, pc, ins):
        d, a, b, cc = (ins >> 21) & 31, (ins >> 16) & 31, (ins >> 11) & 31, (ins >> 6) & 31
        F = lambda n: 'c->f[%d].d' % n
        xo5 = (ins >> 1) & 31; xo = (ins >> 1) & 0x3FF
        ex = {18: '%s / %s' % (F(a), F(b)), 20: '%s - %s' % (F(a), F(b)), 21: '%s + %s' % (F(a), F(b)),
              22: 'sqrt(%s)' % F(b), 25: '%s * %s' % (F(a), F(cc)), 26: 'frsqrte_(%s)' % F(b),
              28: 'fma(%s, %s, -%s)' % (F(a), F(cc), F(b)), 29: 'fma(%s, %s, %s)' % (F(a), F(cc), F(b)),
              30: '-fma(%s, %s, -%s)' % (F(a), F(cc), F(b)), 31: '-fma(%s, %s, %s)' % (F(a), F(cc), F(b)),
              23: '(%s >= 0.0) ? %s : %s' % (F(a), F(cc), F(b))}
        if xo5 in ex and (xo5 >= 18):
            return 'c->f[%d].d = %s;' % (d, ex[xo5]) + self.fcr1(ins)
        if xo in (0, 32): return 'c->cr[%d] = cmp_f(%s, %s);' % (d >> 2, F(a), F(b))
        if xo == 12: return 'c->f[%d].d = c->ps1[%d] = rs(%s);' % (d, d, F(b)) + self.fcr1(ins)
        if xo == 15: return 'c->f[%d].u = fctiwz_(%s);' % (d, F(b)) + self.fcr1(ins)
        if xo == 14: return 'c->f[%d].u = fctiw_(%s);' % (d, F(b)) + self.fcr1(ins)
        if xo == 40: return 'c->f[%d].u = c->f[%d].u ^ 0x8000000000000000ull;' % (d, b) + self.fcr1(ins)
        if xo == 72: return 'c->f[%d].u = c->f[%d].u;' % (d, b) + self.fcr1(ins)
        if xo == 136: return 'c->f[%d].u = c->f[%d].u | 0x8000000000000000ull;' % (d, b) + self.fcr1(ins)
        if xo == 264: return 'c->f[%d].u = c->f[%d].u & 0x7FFFFFFFFFFFFFFFull;' % (d, b) + self.fcr1(ins)
        if xo == 583: return 'c->f[%d].u = 0xFFF8000000000000ull | c->fpscr;' % d
        if xo == 711:
            fm = (ins >> 17) & 0xFF; m = 0
            for i in range(8):
                if fm & (0x80 >> i): m |= 0xF << (28 - 4 * i)
            return 'c->fpscr = (c->fpscr & ~0x%Xu) | ((u32)c->f[%d].u & 0x%Xu);' % (m, b, m)
        if xo == 38: return 'c->fpscr |= 0x%Xu;' % (0x80000000 >> d)
        if xo == 70: return 'c->fpscr &= ~0x%Xu;' % (0x80000000 >> d)
        if xo == 134:
            imm = (ins >> 12) & 15; sh = 28 - 4 * (d >> 2)
            return 'c->fpscr = (c->fpscr & ~(0xFu << %d)) | (%du << %d);' % (sh, imm, sh)
        if xo == 64:
            return 'c->cr[%d] = (c->fpscr >> %d) & 15;' % (d >> 2, 28 - 4 * (a >> 2))
        return self.unimpl(pc, ins)

    def op4(self, pc, ins):
        d, a, b, cc = (ins >> 21) & 31, (ins >> 16) & 31, (ins >> 11) & 31, (ins >> 6) & 31
        xo6 = (ins >> 1) & 0x3F; xo5 = (ins >> 1) & 31; xo = (ins >> 1) & 0x3FF
        A0, A1 = 'c->f[%d].d' % a, 'c->ps1[%d]' % a
        B0, B1 = 'c->f[%d].d' % b, 'c->ps1[%d]' % b
        C0, C1 = 'c->f[%d].d' % cc, 'c->ps1[%d]' % cc
        def set2(e0, e1, single=True):
            r = (lambda e: 'rs(%s)' % e) if single else (lambda e: e)
            return '{ double t0 = %s, t1 = %s; c->f[%d].d = t0; c->ps1[%d] = t1; }' % (r(e0), r(e1), d, d)
        if xo6 in (6, 7, 38, 39):
            w = (ins >> 10) & 1; i = (ins >> 7) & 7
            ea = '(c->r[%d] + c->r[%d])' % (a, b) if a else 'c->r[%d]' % b
            s = 'ea = %s; %s' % (ea, self.psq(xo6 in (6, 38), d, w, i))
            if xo6 in (38, 39): s += ' c->r[%d] = ea;' % a
            return s
        five = {10: (lambda: set2('%s + %s' % (A0, B1), C1)),
                11: (lambda: set2(C0, '%s + %s' % (A0, B1))),
                12: (lambda: set2('%s * %s' % (A0, C0), '%s * %s' % (A1, C0))),
                13: (lambda: set2('%s * %s' % (A0, C1), '%s * %s' % (A1, C1))),
                14: (lambda: set2('fma(%s, %s, %s)' % (A0, C0, B0), 'fma(%s, %s, %s)' % (A1, C0, B1))),
                15: (lambda: set2('fma(%s, %s, %s)' % (A0, C1, B0), 'fma(%s, %s, %s)' % (A1, C1, B1))),
                18: (lambda: set2('%s / %s' % (A0, B0), '%s / %s' % (A1, B1))),
                20: (lambda: set2('%s - %s' % (A0, B0), '%s - %s' % (A1, B1))),
                21: (lambda: set2('%s + %s' % (A0, B0), '%s + %s' % (A1, B1))),
                23: (lambda: set2('(%s >= 0.0) ? %s : %s' % (A0, C0, B0), '(%s >= 0.0) ? %s : %s' % (A1, C1, B1), False)),
                24: (lambda: set2('1.0 / %s' % B0, '1.0 / %s' % B1)),
                25: (lambda: set2('%s * %s' % (A0, C0), '%s * %s' % (A1, C1))),
                26: (lambda: set2('frsqrte_(%s)' % B0, 'frsqrte_(%s)' % B1)),
                28: (lambda: set2('fma(%s, %s, -%s)' % (A0, C0, B0), 'fma(%s, %s, -%s)' % (A1, C1, B1))),
                29: (lambda: set2('fma(%s, %s, %s)' % (A0, C0, B0), 'fma(%s, %s, %s)' % (A1, C1, B1))),
                30: (lambda: set2('-fma(%s, %s, -%s)' % (A0, C0, B0), '-fma(%s, %s, -%s)' % (A1, C1, B1))),
                31: (lambda: set2('-fma(%s, %s, %s)' % (A0, C0, B0), '-fma(%s, %s, %s)' % (A1, C1, B1)))}
        if xo5 in five: return five[xo5]() + self.fcr1(ins)
        if xo in (0, 32): return 'c->cr[%d] = cmp_f(%s, %s);' % (d >> 2, A0, B0)
        if xo in (64, 96): return 'c->cr[%d] = cmp_f(%s, %s);' % (d >> 2, A1, B1)
        if xo == 40: return set2('-%s' % B0, '-%s' % B1, False)
        if xo == 72: return set2(B0, B1, False)
        if xo == 136: return set2('-fabs(%s)' % B0, '-fabs(%s)' % B1, False)
        if xo == 264: return set2('fabs(%s)' % B0, 'fabs(%s)' % B1, False)
        if xo == 528: return set2(A0, B0, False)
        if xo == 560: return set2(A0, B1, False)
        if xo == 592: return set2(A1, B0, False)
        if xo == 624: return set2(A1, B1, False)
        if xo == 1014: return 'rt_dcbz(%s);' % ('(c->r[%d] + c->r[%d])' % (a, b) if a else 'c->r[%d]' % b)
        return self.unimpl(pc, ins)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--dol', required=True)
    ap.add_argument('--syms', action='append', required=True)
    ap.add_argument('--hle', required=True)
    ap.add_argument('--out', required=True)
    ap.add_argument('--per-file', type=int, default=120)
    ap.add_argument('--export', action='append', default=[], help='symbol names to export to rt_data_syms')
    ap.add_argument('--nocode', action='append', default=[], help='hex range lo-hi inside a text section that is data')
    a = ap.parse_args()
    dol = Dol(a.dol)
    nocode = [tuple(int(x, 16) for x in r.split('-')) for r in a.nocode]
    dol.nocode = nocode
    funcs = load_funcs(dol, a.syms, nocode)
    names = {}
    for f in funcs: names[f.name] = f.start
    hle, save_ctx = {}, set()
    for line in open(a.hle):
        line = line.split('#')[0].split()
        if not line: continue
        kind, sym = line[0], line[1]
        addr = int(sym, 16) if re.fullmatch(r'[0-9A-Fa-f]{8}', sym) else names.get(sym)
        if addr is None: sys.exit('hle: unknown symbol %s' % sym)
        if kind == 'replace': hle[addr] = line[2]
        elif kind == 'savectx': save_ctx.add(addr)
    g = Gen(dol, funcs, hle)
    g.save_ctx = save_ctx
    g.scan_entries()
    os.makedirs(a.out, exist_ok=True)
    entries = g.all_entries()
    with open(os.path.join(a.out, 'funcs.h'), 'w') as fp:
        fp.write('#pragma once\n#include "ppc.h"\n')
        for e in entries: fp.write('void fn_%08X(CPU *RESTRICT c);\n' % e)
        for v in sorted(set(hle.values())): fp.write('void %s(CPU *RESTRICT c);\n' % v)
    n = 0; nf = 0
    chunk = []
    def flush():
        nonlocal n, chunk
        if not chunk: return
        with open(os.path.join(a.out, 'gen_%03d.c' % n), 'w') as fp:
            fp.write('#include "funcs.h"\n')
            fp.write(''.join(chunk))
        n += 1; chunk = []
    for f in funcs:
        for e in sorted(f.entries):
            chunk.append('// %s%s\n' % (f.name, '' if e == f.start else ' +0x%X' % (e - f.start)))
            chunk.append(g.gen_func(f, e))
            nf += 1
        if len(chunk) >= a.per_file * 2: flush()
    flush()
    with open(os.path.join(a.out, 'table.c'), 'w') as fp:
        fp.write('#include "funcs.h"\n#include <stddef.h>\n')
        fp.write('const struct { u32 addr; GuestFn fn; } rt_func_table[] = {\n')
        for e in entries: fp.write('  {0x%08X, fn_%08X},\n' % (e, e))
        fp.write('};\nconst size_t rt_func_count = %d;\n' % len(entries))
        fp.write('const u32 rt_entry_point = 0x%08X;\n' % dol.entry)
        fp.write('const struct { u32 addr; const char *name; } rt_func_names[] = {\n')
        for f in funcs: fp.write('  {0x%08X, "%s"},\n' % (f.start, f.name.replace('"', '')))
        fp.write('};\nconst size_t rt_func_name_count = %d;\n' % len(funcs))
        exp = {}
        for f in a.syms:
            for line in open(f):
                p = line.split()
                if len(p) >= 3 and p[-1] in a.export: exp[p[-1]] = int(p[0], 16)
        fp.write('const struct { u32 addr; const char *name; } rt_data_syms[] = {\n')
        for nm_, v in sorted(exp.items()): fp.write("  {0x%08X, \"%s\"},\n" % (v, nm_))
        fp.write('  {0, 0}};\nconst size_t rt_data_sym_count = %d;\n' % len(exp))
        missing = set(a.export) - set(exp)
        if missing: print('export: not found:', sorted(missing))
    print('%d functions, %d C functions, %d files' % (len(funcs), nf, n))
    if g.unk:
        print('unimplemented encodings:', len(g.unk), sorted(g.unk.items(), key=lambda x: -x[1])[:20])
    for w in g.warn[:30]: print('warn:', w)
    if len(g.warn) > 30: print('... %d warnings' % len(g.warn))

if __name__ == '__main__':
    main()
