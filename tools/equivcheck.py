#!/usr/bin/env python3
"""Register-equivalence check of the built main.dol against the original.

Policy (2026-11-11): a function whose only difference from the original is WHICH
registers hold values counts as matched. Such functions are listed in
config/<version>/regequiv.txt and this script is the safety net that replaces the
plain sha1 check:

  a) both DOLs have the same size and section table, and every byte outside .text
     is identical, except register-number fields of C++ exception actions in the
     extab entries of listed functions (rule e);
  b) every differing .text word lies inside a function listed in regequiv.txt;
  c) in each such function every instruction pair has the same opcode and the same
     non-register fields (immediates, displacements, branch targets, condition bits);
  d) the register fields are explained by a renaming of LIVE RANGES. Both versions
     are analysed over the control-flow graph of the original (branches, and bctr
     through the original's jump tables): for every register the set of definitions
     that can reach each instruction is computed, where a definition is an
     (instruction, operand) position, the value a register has at function entry,
     or the write a call / an implicit result (cr0 of a record form, lmw, ...)
     makes. The function passes when
       - every register operand that is read is reached by exactly the same set of
         definition positions in both versions, and by the same register number
         when one of them is an entry value, a call result or an implicit write.
         So a value may sit in r29 in one region and in r30 in another, and two
         values that are live at the same time can never share a register in ours
         (the clobbered one would be reached by a different definition);
       - the two source operands of add, addc, adde, and, or, xor, nand, nor, eqv,
         mullw, mulhw(u), fadd(s), fmul(s) and the multiplicands of f(n)madd/f(n)msub
         may be exchanged (for the float ones this ignores which NaN payload is
         propagated when both operands are NaN);
       - at every call: r1, r2, r13, every argument register (r3-r10, f1-f8) written
         in the same basic block before the call, and every volatile register the
         callee may read (its live-in set over the whole original program;
         r3-r10, f1-f8, cr1 for indirect or undecodable callees) hold the same
         definitions in the same register number;
       - at every return: r3, every callee-saved register, r1, r2, r13 and any volatile
         register that some caller reads after the call do. r4 and f1 count as read
         (wYA 2026-11-12, Program.retuse) unless nothing can read them after the return:
         no caller reads them with its own instructions, no later callee has them among
         its inputs (any indirect callee has), no caller returns them on to such a reader,
         every caller is analysed code, and - when an indirect call site anywhere reads
         them after its call - the address of the function is not taken (no aligned
         word with its address in the DOL outside extabindex, no lis + addi/ori of one
         function that builds it);
       - implicitly used registers (CR logic, mfcr, stmw/lmw ranges) do.
     Copy forwarding (second try, only for a function that failed without it): a plain
     copy (mr / ori rA,rS,0 / fmr) is not a definition site, the copy holds the sites of
     its source. So `addi r3,..; mr r31,r3` and `addi r31,..; mr r3,r31` are the same
     (the value reaches r3 and r31 from the addi in both). When a site executes again,
     every register still holding its earlier value is marked stale and is never
     accepted this way. Entry values, call results and implicit results are forwarded
     as sites of their own per register (wYA 2026-11-12): `bl f; mr r31,r3` and
     `bl f; mr r30,r3` both hold "r3 after that call", so later reads of r31 / r30 agree.
     A value that is live across a call therefore has to be in a callee-saved
     register in ours as well, and results are read from the ABI registers.
     Assumptions: a callee does not interpret the caller's callee-saved registers
     (it only saves and restores them); a volatile register other than r3/r4/f1
     that a call leaves behind matters only when the caller reads it with its own
     instructions (for those, and for r3/r4/f1, a call is transparent for the
     registers the callee can return unchanged). Functions with an unresolved bctr,
     a call into the middle of another function, or unreachable code that differs
     are rejected, as is anything the decoder does not know.
  e) extab (since 2026-11-11, wUM): an exception action that destroys / deletes an object
     held in a register names that register (flag 0x80 on the first u16 operand, 0x40 on the
     second). The extab entry of a listed function may differ from the original ONLY in the
     u16 register operand of a DELETEPOINTER (0x0A) or DELETEPOINTERCOND (0x0B) action
     (decoded from the entry's PC ranges and action chains; an entry that is not fully
     understood must be byte-identical), and only if at every call inside the PC ranges that
     use the action the register in ours holds exactly the definitions (same(...) of rule d)
     the original's register holds there. The same equality is required for every other
     register operand of the function's actions even when it is unchanged. Everything else
     in extab and all of extabindex stays byte-identical.
  f) schedule (experimental, branch sched-equiv, wYA 2026-11-12): a function listed in
     config/<version>/schedequiv.txt may also have its instructions in a different order
     inside basic blocks, as long as our order only exchanges instructions that do not
     depend on each other (registers incl. CR/XER[CA]/FPSCR, memory unless provably
     disjoint; branches, calls, mtspr/mfspr, cache/sync instructions are barriers) and the
     function passes rule d) once our instructions are put back into the original order.
     See the comment above sched_info() for the exact rules.
  --strict uses the first version of rule d) instead: ONE renaming for the whole
     function (a bijection orig -> ours, separately for GPRs, FPRs and CR fields)
     that is the identity on every register visible across an ABI boundary:
       - r0, r1, r2, r13;
       - registers live at function entry (parameters; saving a callee-saved
         register to the stack frame is not counted as a read);
       - registers a callee may read at each call: the callee's own live-in set
         (computed over the whole original program; indirect/unknown callees read
         r3-r10, f1-f8, cr1; callee-saved registers the callee saves in its own
         frame are not inputs) plus every argument register written in the same basic
         block before the call;
       - r3/r4/f1 if anything may read them after a call before they are rewritten
         (results), and any other volatile register this function itself reads
         after a call;
       - r3 / f1 if the function writes them at all (results; also r4 when some
         caller reads r4 after calling the function);
       - registers used implicitly (cr0/cr1 of record forms, CR logic, mfcr/mtcrf);
     and it keeps volatile registers volatile, callee-saved registers callee-saved
     and the register range of stmw/lmw closed.
  Anything the decoder does not know is rejected.

Usage:
  python3 tools/equivcheck.py                 check build/<v>/main.dol (exit 1 on violation)
  python3 tools/equivcheck.py --strict ...    same, with the whole-function renaming rule
  python3 tools/equivcheck.py --selftest      the listed functions must pass, corrupted copies must fail
  python3 tools/equivcheck.py --list U ...    would these pass? U is a unit (auto/text_8002BDD4),
                                              unit:fn or a function name; compares
                                              build/<v>/src/<unit>.o with build/<v>/obj/<unit>.o
                                              and the original DOL, without linking.
Only the Python standard library is needed.
"""
import argparse
import bisect
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# register numbering inside bit masks: GPR n -> n, FPR n -> 32+n, CR field n -> 64+n
GP, FP, CRF = 0, 32, 64
RD, WR, SAVE = 1, 2, 4


def bits(base, regs):
    m = 0
    for r in regs:
        m |= 1 << (base + r)
    return m


VOL = bits(GP, [0] + list(range(3, 13))) | bits(FP, range(0, 14)) | bits(CRF, [0, 1, 5, 6, 7])
NONVOL = bits(GP, range(14, 32)) | bits(FP, range(14, 32)) | bits(CRF, [2, 3, 4])
FIXED = bits(GP, [0, 1, 2, 13])
ARGS_ALL = bits(GP, range(3, 11)) | bits(FP, range(1, 9)) | bits(CRF, [1])
ARGREGS = bits(GP, range(3, 11)) | bits(FP, range(1, 9))
ALLCR = bits(CRF, range(8))
CR0, CR1 = 1 << CRF, 1 << (CRF + 1)
R3, R4, F1 = 1 << 3, 1 << 4, 1 << (FP + 1)

X_DAB = {266, 10, 138, 40, 8, 136, 235, 75, 11, 491, 459}
X_DA = {234, 202, 232, 200, 104}
X_ASB = {28, 60, 444, 412, 316, 476, 124, 284, 24, 536, 792}
X_AS = {26, 954, 922, 824}
LOADX = {23, 87, 279, 343, 534, 790}
LOADUX = {55, 119, 311, 375}
STOREX = {151, 215, 407, 662, 918}
STOREUX = {183, 247, 439}
FLOADX = {535, 599}
FLOADUX = {567, 631}
FSTOREX = {663, 727, 983}
FSTOREUX = {695, 759}
CACHE = {86, 54, 278, 246, 1014, 470, 982}
CRLOG = {257, 449, 193, 225, 33, 289, 129, 417}

COMM_DAB = {266, 10, 138, 235, 75, 11}       # add addc adde mullw mulhw mulhwu
COMM_ASB = {28, 444, 316, 476, 124, 284}     # and or xor nand nor eqv
RETREGS = R3 | R4 | F1
VOLLIST = [b for b in range(96) if VOL >> b & 1]
KEEP = bits(GP, [1, 2, 13])

_memo = {}


def sext(v, n):
    return v - (1 << n) if v & (1 << (n - 1)) else v


def dec(w):
    """Decode one instruction word.

    Returns None when unknown, else a tuple
      (ops, use, defs, pin, kind, rel, cond, regmask, closed)
    ops:     ((base, shift, width, role), ...) for every renamable register field
    use/defs: implicit (non-renamable) reads / writes as masks
    pin:     registers that must keep their number because of this instruction
    kind:    '' | 'b' | 'bl' | 'bc' | 'ret' | 'bctr' | 'icall'
    rel:     branch displacement for b/bl/bc
    cond:    True when a branch/return can fall through
    regmask: instruction bits covered by ops
    closed:  N when the instruction is stmw/lmw rN (range rN..r31 must stay closed)
    """
    r = _memo.get(w)
    if r is None and w not in _memo:
        r = _memo[w] = _dec(w)
    return r


def _dec(w):
    op = w >> 26
    ops = []
    use = defs = pin = 0
    kind = ''
    rel = 0
    cond = False
    closed = None
    A = (w >> 16) & 31

    def g(sh, role):
        ops.append((GP, sh, 5, role))

    def f(sh, role):
        ops.append((FP, sh, 5, role))

    def c(sh, role):
        ops.append((CRF, sh, 3, role))

    def a0():
        if A:
            g(16, RD)

    def rc(bit):
        nonlocal defs, pin
        if w & 1:
            defs |= bit
            pin |= bit

    def bcond():
        # BO/BI of a conditional branch; returns True when the condition is used
        bo = (w >> 21) & 31
        if not bo & 16:
            c(18, RD)
        return (bo & 0x14) != 0x14

    if op in (7, 8, 12, 13):
        g(21, WR)
        g(16, RD)
        if op == 13:
            defs |= CR0
            pin |= CR0
    elif op in (10, 11):
        c(23, WR)
        g(16, RD)
    elif op in (14, 15):
        g(21, WR)
        a0()
    elif op == 16:
        if w & 3:
            return None  # absolute or conditional call
        cond = bcond()
        kind = 'bc'
        rel = sext(w & 0xFFFC, 16)
    elif op == 18:
        if w & 2:
            return None
        kind = 'bl' if w & 1 else 'b'
        rel = sext(w & 0x03FFFFFC, 26)
    elif op == 19:
        xo = (w >> 1) & 1023
        if xo == 16:
            cond = bcond()
            if w & 1:
                if cond:
                    return None
                kind = 'icall'
            else:
                kind = 'ret'
        elif xo == 528:
            cond = bcond()
            if cond:
                return None
            kind = 'icall' if w & 1 else 'bctr'
        elif xo == 0:
            c(23, WR)
            c(18, RD)
        elif xo in CRLOG:
            m = 0
            for sh in (21, 16, 11):
                m |= 1 << (CRF + ((w >> sh) & 31) // 4)
            use |= m
            pin |= m
        elif xo == 150:
            pass
        else:
            return None
    elif op == 20:
        g(16, RD | WR)
        g(21, RD)
        rc(CR0)
    elif op == 21:
        g(16, WR)
        g(21, RD)
        rc(CR0)
    elif op == 23:
        g(16, WR)
        g(21, RD)
        g(11, RD)
        rc(CR0)
    elif 24 <= op <= 29:
        g(16, WR)
        g(21, RD)
        if op >= 28:
            defs |= CR0
            pin |= CR0
    elif op == 31:
        xo = (w >> 1) & 1023
        x9 = xo & 511
        if xo in (0, 32):
            c(23, WR)
            g(16, RD)
            g(11, RD)
        elif x9 in X_DAB and not (xo >= 512 and x9 in (75, 11)):
            g(21, WR)
            g(16, RD)
            g(11, RD)
            rc(CR0)
        elif x9 in X_DA:
            g(21, WR)
            g(16, RD)
            rc(CR0)
        elif xo in X_ASB:
            g(16, WR)
            g(21, RD)
            g(11, RD)
            rc(CR0)
        elif xo in X_AS:
            g(16, WR)
            g(21, RD)
            rc(CR0)
        elif xo in LOADX:
            g(21, WR)
            a0()
            g(11, RD)
        elif xo in LOADUX:
            g(21, WR)
            g(16, RD | WR)
            g(11, RD)
        elif xo in STOREX:
            g(21, RD)
            a0()
            g(11, RD)
        elif xo in STOREUX:
            g(21, RD)
            g(16, RD | WR)
            g(11, RD)
        elif xo in FLOADX:
            f(21, WR)
            a0()
            g(11, RD)
        elif xo in FLOADUX:
            f(21, WR)
            g(16, RD | WR)
            g(11, RD)
        elif xo in FSTOREX:
            f(21, RD)
            a0()
            g(11, RD)
        elif xo in FSTOREUX:
            f(21, RD)
            g(16, RD | WR)
            g(11, RD)
        elif xo in (339, 83, 371):  # mfspr mfmsr mftb
            g(21, WR)
        elif xo in (467, 146):  # mtspr mtmsr
            g(21, RD)
        elif xo == 19:  # mfcr
            g(21, WR)
            use |= ALLCR
            pin |= ALLCR
        elif xo == 144:  # mtcrf
            g(21, RD)
            use |= ALLCR
            pin |= ALLCR
        elif xo in CACHE:
            a0()
            g(11, RD)
        elif xo == 598:
            pass
        else:
            return None
    elif 32 <= op <= 45:
        load = op < 36 or 40 <= op <= 43
        if load:
            g(21, WR)
        elif op == 36 and A == 1 and ((w >> 21) & 31) >= 14:
            g(21, SAVE)  # callee-saved register stored into the frame
        else:
            g(21, RD)
        if op & 1:
            g(16, RD | WR)
        else:
            a0()
    elif op in (46, 47):
        closed = (w >> 21) & 31
        a0()
        rng = bits(GP, range(closed, 32))
        if op == 46:
            defs |= rng
        elif closed < 14 or A != 1:  # not a prologue save
            use |= rng
            pin |= rng
    elif 48 <= op <= 55:
        if op < 52:
            f(21, WR)
        elif op == 54 and A == 1 and ((w >> 21) & 31) >= 14:
            f(21, SAVE)
        else:
            f(21, RD)
        if op & 1:
            g(16, RD | WR)
        else:
            a0()
    elif op in (56, 57, 60, 61):  # psq_l psq_lu psq_st psq_stu
        if op < 60:
            f(21, WR)
        elif op == 60 and A == 1 and ((w >> 21) & 31) >= 14:
            f(21, SAVE)
        else:
            f(21, RD)
        if op & 1:
            g(16, RD | WR)
        else:
            a0()
    elif op in (59, 63):
        x5 = (w >> 1) & 31
        xo = (w >> 1) & 1023
        if x5 in (18, 20, 21):
            f(21, WR)
            f(16, RD)
            f(11, RD)
            rc(CR1)
        elif x5 == 25:
            f(21, WR)
            f(16, RD)
            f(6, RD)
            rc(CR1)
        elif x5 in (28, 29, 30, 31) or (x5 == 23 and op == 63):
            f(21, WR)
            f(16, RD)
            f(11, RD)
            f(6, RD)
            rc(CR1)
        elif (x5 == 24 and op == 59) or (x5 == 26 and op == 63):
            f(21, WR)
            f(11, RD)
            rc(CR1)
        elif op == 59:
            return None
        elif xo in (0, 32):
            c(23, WR)
            f(16, RD)
            f(11, RD)
        elif xo in (12, 14, 15, 40, 72, 136, 264):
            f(21, WR)
            f(11, RD)
            rc(CR1)
        elif xo == 583:
            f(21, WR)
            rc(CR1)
        elif xo == 711:
            f(11, RD)
            rc(CR1)
        elif xo in (70, 38):
            rc(CR1)
        else:
            return None
    else:
        return None
    regmask = 0
    for _, sh, wd, _r in ops:
        regmask |= ((1 << wd) - 1) << sh
    return (tuple(ops), use, defs, pin, kind, rel, cond, regmask, closed)


def comm(w):
    """Indexes (into dec(w).ops) of two source operands that may be exchanged, else None."""
    op = w >> 26
    if op == 31:
        xo = (w >> 1) & 1023
        x9 = xo & 511
        if xo in COMM_ASB or (x9 in COMM_DAB and not (xo >= 512 and x9 in (75, 11))):
            return (1, 2)
    elif op in (59, 63):
        x5 = (w >> 1) & 31
        if x5 in (21, 25):          # fadd A,B / fmul A,C
            return (1, 2)
        if x5 in (28, 29, 30, 31):  # fmsub fmadd fnmsub fnmadd: A*C
            return (1, 3)
    return None


def regbits(mask):
    out = []
    b = 0
    while mask:
        if mask & 1:
            out.append(b)
        mask >>= 1
        b += 1
    return out


class Fn:
    """Control flow and register use of one function of the ORIGINAL program."""

    def __init__(self, name, addr, words, read32=None):
        self.name = name
        self.addr = addr
        self.words = words
        n = self.n = len(words)
        self.opaque = None
        self.use = [0] * n
        self.xuse = [0] * n  # reads by the instruction itself
        self.defs = [0] * n
        self.succ = [()] * n
        self.call = {}      # index -> target address (None = indirect)
        self.rets = set()   # indexes of blr
        self.bctr = set()
        self.pin = 0
        self.saved = 0      # callee-saved registers the function stores into its frame
        self.closed = []
        self.leader = set([0])
        self.livein = ARGS_ALL
        self.live = None
        self.web = None
        self.rd = None
        end = addr + 4 * n
        for i, w in enumerate(words):
            d = dec(w)
            if d is None:
                self.opaque = 'unknown instruction %08x at %08x' % (w, addr + 4 * i)
                return
            ops, use, defs, pin, kind, rel, cond, _m, closed = d
            for base, sh, wd, role in ops:
                b = 1 << (base + ((w >> sh) & ((1 << wd) - 1)))
                if role & RD:
                    use |= b
                if role & WR:
                    defs |= b
                if role & SAVE:
                    self.saved |= b
            self.pin |= pin
            if closed is not None:
                self.closed.append(closed)
                if w >> 26 == 47 and not d[1]:
                    self.saved |= bits(GP, range(closed, 32))
            self.xuse[i] = use
            nxt = (i + 1,) if i + 1 < n else None
            t = addr + 4 * i + rel
            if kind == '':
                succ = nxt
            elif kind == 'bl':
                self.call[i] = t
                defs |= VOL
                succ = nxt
            elif kind == 'icall':
                self.call[i] = None
                defs |= VOL
                succ = nxt
            elif kind == 'b':
                if addr <= t < end:
                    succ = ((t - addr) // 4,)
                    self.leader.add(succ[0])
                else:
                    self.call[i] = t  # tail call
                    self.rets.add(i)
                    succ = ()
                self.leader.add(i + 1)
            elif kind == 'bc':
                if not addr <= t < end:
                    self.opaque = 'conditional branch out of the function at %08x' % (addr + 4 * i)
                    return
                ti = (t - addr) // 4
                self.leader.add(ti)
                self.leader.add(i + 1)
                succ = (ti,) + nxt if cond and nxt else (ti,) if not cond else None
            elif kind == 'ret':
                self.rets.add(i)
                self.leader.add(i + 1)
                succ = nxt if cond else ()
            elif self._jumptable(i, read32):
                succ = self._jumptable(i, read32)
                self.leader.update(succ)
                self.leader.add(i + 1)
            else:  # bctr: unknown jump table or indirect tail call
                self.bctr.add(i)
                self.rets.add(i)
                use |= ARGS_ALL
                self.leader.add(i + 1)
                succ = ()
            if succ is None:
                self.opaque = 'falls off the end at %08x' % (addr + 4 * i)
                return
            self.use[i] = use
            self.defs[i] = defs
            self.succ[i] = succ

    def _jumptable(self, i, read32):
        """Targets of 'lis rA; addi rA,rA; ...; lwzx rT,rA,rB; mtctr rT; bctr', else None."""
        w = self.words
        if read32 is None or i < 4 or (w[i - 1] & 0xFC1FFFFF) != 0x7C0903A6:
            return None
        t = (w[i - 1] >> 21) & 31
        x = w[i - 2]
        if x >> 26 != 31 or (x >> 1) & 1023 != 23 or (x >> 21) & 31 != t:
            return None
        a = (x >> 16) & 31
        lo = hi = None
        for k in range(i - 3, max(i - 10, -1), -1):
            d = dec(w[k])
            if d is None or d[4]:
                return None
            wr = (w[k] >> 21) & 31 if w[k] >> 26 in (14, 15) else None
            if lo is None:
                if w[k] >> 26 == 14 and wr == a and (w[k] >> 16) & 31 == a:
                    lo = sext(w[k] & 0xFFFF, 16)
                elif any(base == GP and role & WR and (w[k] >> sh) & 31 == a for base, sh, _w, role in d[0]):
                    return None
            else:
                if w[k] >> 26 == 15 and wr == a and (w[k] >> 16) & 31 == 0:
                    hi = w[k] & 0xFFFF
                    break
                elif any(base == GP and role & WR and (w[k] >> sh) & 31 == a for base, sh, _w, role in d[0]):
                    return None
            if k in self.leader:
                break  # the address must be built in the block of the bctr
        if hi is None:
            return None
        tbl = ((hi << 16) + lo) & 0xFFFFFFFF
        end = self.addr + 4 * self.n
        out = []
        while len(out) < 4096:
            v = read32(tbl + 4 * len(out))
            if v is None or v & 3 or not self.addr <= v < end:
                break
            out.append((v - self.addr) // 4)
        return tuple(sorted(set(out))) or None

    def liveness(self, livein_of, r4ret, explicit=False):
        """Backward liveness; returns live-in masks per instruction.

        Default: every read that may happen (callees included). explicit=True:
        only reads by this function's own instructions."""
        n = self.n
        live = [0] * n
        defs, succ, call = self.defs, self.succ, self.call
        if explicit:
            use, retuse, cu = self.xuse, 0, {}
        else:
            use = self.use
            retuse = R4 if self.addr in r4ret else 0
            cu = {i: (ARGS_ALL if t is None else livein_of(t)) for i, t in call.items()}
        any_live = 0
        changed = True
        while changed:
            changed = False
            for i in range(n - 1, -1, -1):
                out = 0
                for s in succ[i]:
                    out |= live[s]
                if i in self.rets:
                    if i not in call:
                        out |= retuse
                    if i in self.bctr:
                        out |= any_live
                new = use[i] | (out & ~defs[i])
                if i in cu:
                    new |= cu[i]
                if new != live[i]:
                    live[i] = new
                    any_live |= new
                    changed = True
        if not explicit:
            self.live = live
            self.calluse = cu
        return live

    def passthru(self, thru_of):
        """Volatile registers that may still hold their entry value at a return."""
        n = self.n
        succ, call = self.succ, self.call
        kill = self.defs[:]
        for i, t in call.items():
            kill[i] = VOL & ~thru_of(t)
        unt = [0] * n
        unt[0] = VOL
        changed = True
        while changed:
            changed = False
            for i in range(n):
                m = unt[i]
                if m:
                    out = m & ~kill[i]
                    for s in succ[i]:
                        if out & ~unt[s]:
                            unt[s] |= out
                            if s <= i:
                                changed = True
        res = 0
        for i in self.rets:
            res |= (unt[i] & thru_of(call[i])) if i in call else unt[i]
        return res

    def xlive(self, retuse, thru_of, cin=None):
        """Liveness for reads by this function's own instructions (and by its callers
        after the return: retuse), where a call only redefines what the callee cannot
        pass through. cin: index of a call -> registers the callee may read (counted as
        read at the call)."""
        n = self.n
        succ, use = self.succ, self.xuse[:]
        if cin:
            for i, m in cin.items():
                use[i] |= m
        for i, w in enumerate(self.words):
            # crclr/crset (crxor/creqv b,b,b): the old CR field is not really an input
            if w >> 26 == 19 and (w >> 1) & 1023 in (193, 289) and \
                    (w >> 21) & 31 == (w >> 16) & 31 == (w >> 11) & 31:
                use[i] &= ~ALLCR
            elif w >> 26 == 31 and (w >> 1) & 1023 == 144:   # mtcrf does not read the CR
                use[i] &= ~ALLCR
        kill = self.defs[:]
        for i, t in self.call.items():
            kill[i] = VOL & ~thru_of(t)
        isret = [False] * n
        for i in self.rets:
            isret[i] = True
        live = [0] * n
        changed = True
        while changed:
            changed = False
            for i in range(n - 1, -1, -1):
                out = retuse if isret[i] else 0
                for s in succ[i]:
                    out |= live[s]
                new = use[i] | (out & ~kill[i])
                if new != live[i]:
                    live[i] = new
                    changed = True
        return live

    def liveout(self, i, live=None):
        live = live or self.live
        out = 0
        for s in self.succ[i]:
            out |= live[s]
        return out


def find_sda(dol):
    """{13: _SDA_BASE_, 2: _SDA2_BASE_} from the one `lis; ori` pair per register in the
    start-up code (__init_registers), {} when that is not unambiguous."""
    secs = getattr(dol, 'secs', None)
    if not secs:
        return {}
    out = {}
    _off, a, size, _t = secs[0]
    ws = dol.words(a, size) or []
    for r in (2, 13):
        hit = [(ws[i] & 0xFFFF) << 16 | ws[i + 1] & 0xFFFF for i in range(len(ws) - 1)
               if ws[i] == 15 << 26 | r << 21 | ws[i] & 0xFFFF and
               ws[i + 1] == 24 << 26 | r << 21 | r << 16 | ws[i + 1] & 0xFFFF]
        if len(hit) != 1:
            return {}
        out[r] = hit[0]
    return out


class Program:
    """Whole-program analysis of the original DOL."""

    def __init__(self, dol, syms):
        self.dol = dol
        self.fns = {}
        self.byname = {}
        for name, addr, size in syms:
            words = dol.words(addr, size)
            if words is None:
                continue
            fn = Fn(name, addr, words, dol.read32)
            self.fns[addr] = fn
            self.byname[name] = fn
        self.r4ret = set()
        self.indirect_r4 = False
        self.strict = False
        self.thru = None
        self.xin = {}
        self.starts = None
        self.sda = find_sda(dol)
        self._solve()

    def containing(self, t):
        """Start address of the function that contains address t, else None."""
        if t is None:
            return None
        if self.starts is None:
            self.starts = sorted(self.fns)
        k = bisect.bisect_right(self.starts, t) - 1
        if k >= 0 and t < self.starts[k] + 4 * self.fns[self.starts[k]].n:
            return self.starts[k]
        return None

    def livein_of(self, t):
        fn = self.fns.get(t)
        return fn.livein if fn is not None else ARGS_ALL

    def _solve(self):
        fns = self.fns
        callers = {}
        for fn in fns.values():
            if fn.opaque:
                fn.livein = ARGS_ALL
                continue
            fn.livein = 0
            for t in fn.call.values():
                if t is not None:
                    callers.setdefault(t, set()).add(fn.addr)
        dirty = set(a for a, fn in fns.items() if not fn.opaque)
        while dirty:
            todo = sorted(dirty)
            dirty = set()
            for a in todo:
                fn = fns[a]
                live = fn.liveness(self.livein_of, self.r4ret)
                # A callee-saved register the callee saves itself is the caller's to keep,
                # not an input: a read-before-write of it is an uninitialised variable.
                if live[0] & ~fn.saved != fn.livein:
                    fn.livein = live[0] & ~fn.saved
                    dirty |= callers.get(a, set())
                for i, t in fn.call.items():
                    if i in fn.rets:  # tail call: our caller's use of r4 is the callee's
                        r4 = a in self.r4ret
                    else:
                        r4 = bool(fn.liveout(i) & R4)
                    if r4:
                        if t is None:
                            self.indirect_r4 = True
                        elif t not in self.r4ret:
                            self.r4ret.add(t)
                            if t in fns and not fns[t].opaque:
                                dirty.add(t)

    # ---- per-live-range check ------------------------------------------------

    def thru_of(self, t):
        return self.thru.get(t, VOL) if t is not None else VOL

    def _solve_webs(self):
        """Whole-program facts for check_webs: thru[f] = volatile registers f may
        return with their entry value; retx[f] = volatile registers some caller
        reads with its own instructions after calling f."""
        if self.thru is not None:
            return
        fns = self.fns
        thru = self.thru = {}
        callers = {}
        for a, fn in fns.items():
            thru[a] = VOL if fn.opaque else 0
            if not fn.opaque:
                for t in fn.call.values():
                    if t is not None:
                        callers.setdefault(t, set()).add(a)
        live_fns = set(a for a, fn in fns.items() if not fn.opaque)
        dirty = set(live_fns)
        while dirty:
            todo = sorted(dirty)
            dirty = set()
            for a in todo:
                m = fns[a].passthru(self.thru_of)
                if m != thru[a]:
                    thru[a] = m
                    dirty |= callers.get(a, set()) & live_fns
        # r3/r4/f1 after a return (wYA 2026-11-12): besides the caller's own instructions a later
        # callee may read them as arguments (cin), and so may callers this analysis does not see.
        # Only a function whose address is taken somewhere can be reached by an indirect call.
        self.taken, unk = self._taken()
        retx = self.retx = dict.fromkeys(fns, 0)
        for t in unk:
            t = t if t in fns else self.containing(t)
            if t is not None:
                retx[t] = RETREGS
        cins = {}
        for a in live_fns:
            fn = fns[a]
            if fn.call:
                cins[a] = {i: self.inputs_of(t) & RETREGS for i, t in fn.call.items()}
        self.ind_retx = 0
        dirty = set(live_fns)
        while dirty:
            todo = sorted(dirty)
            dirty = set()
            ind0 = self.ind_retx
            for a in todo:
                fn = fns[a]
                if not fn.call:
                    continue
                ru = self.retuse(a)
                live = fn.xlive(ru, self.thru_of, cins[a])
                for i, t in fn.call.items():
                    m = (ru if i in fn.rets else fn.liveout(i, live)) & VOL
                    if not m:
                        continue
                    if t not in fns:
                        t = self.containing(t)    # entry in the middle of a function (_savegpr_NN)
                    if t is None:
                        self.ind_retx |= m
                    elif m & ~retx[t]:
                        retx[t] |= m
                        if t in live_fns:
                            dirty.add(t)
            if self.ind_retx != ind0:
                dirty = set(live_fns)

    def retuse(self, a):
        """Volatile registers that may be read after function a returns, before they are
        written again. What is read after indirect calls counts in full only for a function
        that can be called indirectly."""
        if a in self.taken:
            return self.retx[a] | self.ind_retx
        return self.retx[a] | (self.ind_retx & ~RETREGS)

    def _taken(self):
        """(functions whose address may be taken, targets of calls from code that is not
        analysed). Address taken: a 4-aligned word with the value of a function start in any
        section of the DOL (code included; extabindex, whose first words are function starts
        that are only looked up, is skipped when its range is known), or a function start that
        a `lis` and an `addi` / `ori` of ONE function (or of one gap between functions) can
        build together. Without section information every function counts as taken."""
        fns = self.fns
        secs = getattr(self.dol, 'secs', None)
        if not secs:
            return set(fns), set()
        taken, unk = set(), set()
        skip = getattr(self, 'noscan', ())
        for _off, a, size, _t in secs:
            ws = self.dol.words(a, size & ~3) or ()
            for k, v in enumerate(ws):
                if v in fns and not any(lo <= a + 4 * k < hi for lo, hi in skip):
                    taken.add(v)
        wins = []                                  # (address, words, analysed)
        for _off, a, size, text in secs:
            if not text:
                continue
            end = a + (size & ~3)
            cur = a
            for s in [x for x in sorted(fns) if a <= x < end] + [end]:
                if s > cur:
                    wins.append((cur, self.dol.words(cur, s - cur) or (), False))
                if s < end:
                    wins.append((s, fns[s].words, not fns[s].opaque))
                    cur = max(cur, s + 4 * fns[s].n)
        for a, ws, known in wins:
            his, add, ori = set(), set(), set()
            for k, w in enumerate(ws):
                op = w >> 26
                if op == 15:
                    his.add(w & 0xFFFF)
                elif op == 14:
                    add.add(sext(w & 0xFFFF, 16))
                elif op == 24:
                    ori.add(w & 0xFFFF)
                elif not known and op in (16, 18) and not w & 2:
                    rel = sext(w & 0x03FFFFFC, 26) if op == 18 else sext(w & 0xFFFC, 16)
                    if not a <= a + 4 * k + rel < a + 4 * len(ws):
                        unk.add(a + 4 * k + rel)
            for h in his:
                for lo in add:
                    if ((h << 16) + lo) & 0xFFFFFFFF in fns:
                        taken.add(((h << 16) + lo) & 0xFFFFFFFF)
                for lo in ori:
                    if h << 16 | lo in fns:
                        taken.add(h << 16 | lo)
        return taken, unk

    def unsupported(self, fn):
        """Why the per-live-range check cannot analyse this function, else None."""
        if fn.opaque:
            return fn.opaque
        if fn.bctr:
            return 'indirect jump without a recognised jump table at %08x' % (fn.addr + 4 * min(fn.bctr))
        for i, t in sorted(fn.call.items()):
            if t is not None and t not in self.fns:
                return 'call or branch to an address that is not a function start at %08x' % (fn.addr + 4 * i)
        return None

    def inputs_of(self, t):
        """Registers a callee may read: its live-in set (a call inside it redefines the
        volatile registers) plus what its own instructions read of the registers that
        its callees can pass through."""
        if t not in self.fns or self.fns[t].opaque:
            return ARGS_ALL
        m = self.xin.get(t)
        if m is None:
            m = self.xin[t] = self.fns[t].xlive(0, self.thru_of)[0] & VOL
        return self.fns[t].livein | m

    def _webinfo(self, fn):
        """Position-only data of the original function, cached."""
        if fn.web is not None:
            return fn.web
        n = fn.n
        starts = sorted(l for l in fn.leader if l < n)
        blocks = [(s, e) for s, e in zip(starts, starts[1:] + [n])]
        bidx = {s: k for k, s in enumerate(starts)}
        bsucc = [[bidx[t] for t in fn.succ[e - 1]] for _s, e in blocks]
        iuse = [0] * n
        idef = [0] * n
        for i, w in enumerate(fn.words):
            d = dec(w)
            u, df = d[1], d[2]
            if w >> 26 == 47:                                  # stmw reads its range
                u |= bits(GP, range(d[8], 32))
            if w >> 26 == 19 and (w >> 1) & 1023 in CRLOG:     # CR logic rewrites the field of BT
                df |= 1 << (CRF + ((w >> 21) & 31) // 4)
            if w >> 26 == 31 and (w >> 1) & 1023 == 144:       # mtcrf writes the selected fields
                u &= ~ALLCR
                df |= bits(CRF, [k for k in range(8) if w & (1 << (19 - k))])
            iuse[i], idef[i] = u, df
        fn.web = (blocks, bsucc, iuse, idef)
        return fn.web

    def _effects(self, fn, words, idef):
        """Per instruction: [(state index, def-site bit, kills)]. State index r is the
        register in the pass-through model, r+96 in the model where a call redefines
        every volatile register."""
        eff = []
        for i, w in enumerate(words):
            e = []
            for k, (base, sh, wd, role) in enumerate(dec(w)[0]):
                if role & WR:
                    r = base + ((w >> sh) & ((1 << wd) - 1))
                    b = 1 << (1 + 8 * i + k)
                    e.append((r, b, True))
                    e.append((r + 96, b, True))
            ib = 1 << (8 * i + 8)
            for r in regbits(idef[i]):
                e.append((r, ib, True))
                e.append((r + 96, ib, True))
            if i in fn.call and i not in fn.rets:
                th = self.thru_of(fn.call[i])
                for r in VOLLIST:
                    e.append((r, ib, not (th >> r) & 1))
                    e.append((r + 96, ib, True))
            eff.append(e)
        return eff

    @staticmethod
    def _rdflow(eff, blocks, bsucc, uord=None):
        """Reaching definitions at the start of every basic block. uord: the order in which
        the instructions (their indexes) run when that is not the index order."""
        summ = []
        for s, e in blocks:
            d = {}
            for i in (uord[s:e] if uord else range(s, e)):
                for idx, bit, kill in eff[i]:
                    if kill:
                        d[idx] = (bit, True)
                    else:
                        g = d.get(idx)
                        d[idx] = (g[0] | bit, g[1]) if g else (bit, False)
            summ.append(d)
        IN = [None] * len(blocks)
        IN[0] = [1] * 192          # bit 0: the value the register has at entry
        work = [0]
        inw = {0}
        while work:
            b = work.pop()
            inw.discard(b)
            out = IN[b][:]
            for idx, (g, k) in summ[b].items():
                out[idx] = g if k else out[idx] | g
            for t in bsucc[b]:
                cur = IN[t]
                ch = False
                if cur is None:
                    IN[t] = out[:]
                    ch = True
                else:
                    for idx in range(192):
                        v = out[idx]
                        if v & ~cur[idx]:
                            cur[idx] |= v
                            ch = True
                if ch and t not in inw:
                    work.append(t)
                    inw.add(t)
        return IN

    @staticmethod
    def _fwdstep(F, eff_i, cp, i, W):
        """One instruction of the copy-forwarding model. F[r] holds the definition sites a
        register's value comes from, but a plain copy (mr rD,rS) hands on the sites of rS
        instead of being a site itself. When a site executes again, every register that
        holds its earlier value gets the extra 'stale' bit (site shifted up by W).
        A value that no instruction operand produces - the value a register has at entry,
        what a call leaves in it, an implicit result - is a site of its own PER REGISTER
        (wYA 2026-11-12): bit IB + r for the entry value of register r, IB + 96*(i+1) + r
        for register r after instruction i, with IB = 2*W + 8. So a copy of r3 after a call
        is "the r3 of that call" in whatever register it sits. These get one common stale
        bit (IB + 96*(n+1)) when instruction i runs again."""
        grp = 0x7F << (8 * i + 1)
        ib = 1 << (8 * i + 8)
        IB = 2 * W + 8
        own = IB + 96 * (i + 1)
        idm = ((1 << 96) - 1) << own
        stb = 1 << (IB + 96 * ((W - 16) // 8 + 1))
        for r in range(96):
            v = F[r]
            if v & grp:
                F[r] = v = v | ((v & grp) << W)
            if v & idm:
                F[r] = v | stb
        val = F[cp[1]] if cp else 0
        for idx, bit, kill in eff_i:
            if idx < 96:
                if bit == ib:
                    bit = 1 << (own + idx)
                if cp and idx == cp[0]:
                    F[idx] = val
                else:
                    F[idx] = bit if kill else F[idx] | bit

    def _fwdflow(self, eff, cps, blocks, bsucc, W, uord=None):
        """Copy-forwarded definition sets at the start of every basic block."""
        IN = [None] * len(blocks)
        IN[0] = [1 << (2 * W + 8 + r) for r in range(96)]
        work = [0]
        inw = {0}
        while work:
            b = work.pop()
            inw.discard(b)
            out = IN[b][:]
            for i in (uord[blocks[b][0]:blocks[b][1]] if uord else range(*blocks[b])):
                self._fwdstep(out, eff[i], cps[i], i, W)
            for t in bsucc[b]:
                cur = IN[t]
                if cur is None:
                    IN[t] = out[:]
                    ch = True
                else:
                    ch = False
                    for r in range(96):
                        if out[r] & ~cur[r]:
                            cur[r] |= out[r]
                            ch = True
                if ch and t not in inw:
                    work.append(t)
                    inw.add(t)
        return IN

    def check(self, fn, ours, xpairs=None):
        """Compare the function with our words. xpairs: extab register operands, see
        extab_pairs. Returns (ok, text)."""
        if self.strict:
            if xpairs and any(a != b for v in xpairs.values() for a, b in v):
                return False, 'extab register operands differ (not supported with --strict)'
            return self.check_strict(fn, ours)
        return self.check_webs(fn, ours, xpairs)

    def check_webs(self, fn, ours, xpairs=None, uord=None):
        """Per-live-range equivalence (see the module docstring). A function that fails is
        tried once more with copy forwarding (see _fwdflow), and then with copy forwarding
        where a plain copy may also read another register than the original's copy does
        (mode 2: the copy is not checked itself; a value that may come from a copy is then
        only ever compared through the forwarded sites, never through the copy's position)."""
        ok, text = self._check_webs(fn, ours, False, xpairs, uord)
        if not ok and ('different value' in text or 'implicit use' in text or 'extab' in text):
            for mode in (True, 2):
                ok2, text2 = self._check_webs(fn, ours, mode, xpairs, uord)
                if ok2:
                    return ok2, text2
        return ok, text

    def _check_webs(self, fn, ours, fwd, xpairs=None, uord=None):
        """ours: our instructions at the positions of their counterparts in the original.
        uord (rule f, second form): the order in which OURS runs them, as a list of those
        positions (a permutation inside every basic block); None = the same order. The
        definitions that reach an instruction are then computed for the original in its
        order and for ours in our order, a definition site being the position of the
        instruction in the original for both."""
        orig = fn.words
        n = fn.n
        if len(ours) != n:
            return False, 'length differs'
        xdiff = bool(xpairs) and any(a != b for v in xpairs.values() for a, b in v)
        if uord is not None and uord == list(range(n)):
            uord = None
        if ours == orig and not xdiff and uord is None:
            return True, 'exact'
        why = self.unsupported(fn)
        if why:
            return False, why
        self._solve_webs()
        RO, RU, CPS = [], [], []
        for i, (wo, wu) in enumerate(zip(orig, ours)):
            do, du = dec(wo), dec(wu)
            at = '%08x' % (fn.addr + 4 * i)
            if du is None or (wo ^ wu) & ~do[7] & 0xFFFFFFFF:
                return False, 'non-register field differs at %s (%08x vs %08x)' % (at, wo, wu)
            if [(b, sh, bool(r & WR), bool(r & (RD | SAVE))) for b, sh, _w, r in do[0]] != \
               [(b, sh, bool(r & WR), bool(r & (RD | SAVE))) for b, sh, _w, r in du[0]]:
                return False, 'operand form differs at %s (r0 as base)' % at
            ro = [b + ((wo >> sh) & ((1 << wd) - 1)) for b, sh, wd, _r in do[0]]
            ru = [b + ((wu >> sh) & ((1 << wd) - 1)) for b, sh, wd, _r in do[0]]
            for regs, w in ((ro, wo), (ru, wu)):
                wr = [r for r, o in zip(regs, do[0]) if o[3] & WR]
                if len(wr) != len(set(wr)):
                    return False, 'instruction writes one register twice at %s' % at
            if wo >> 26 in (56, 57) and ro[0] != ru[0]:
                # psq_l writes both halves of the register; the model only follows one value
                return False, 'psq_l into a different register at %s' % at
            RO.append(ro)
            RU.append(ru)
            cp = None
            if copy_of(wo) and copy_of(wu):
                kw = [k for k, o in enumerate(do[0]) if o[3] & WR]
                kr = [k for k, o in enumerate(do[0]) if o[3] & RD]
                if len(kw) == 1 and kr:
                    cp = (kw[0], kr[0])
            CPS.append(cp)
        blocks, bsucc, iuse, idef = self._webinfo(fn)
        if fn.rd is None:
            eo = self._effects(fn, orig, idef)
            fn.rd = self._rdflow(eo, blocks, bsucc), eo
        INO, EO = fn.rd
        EU = self._effects(fn, ours, idef)
        INU = self._rdflow(EU, blocks, bsucc, uord)
        idmask = ((1 << (8 * (n + 1))) - 1) // 255     # entry + every implicit/call def site
        cpmask = 0                                     # mode 2: the sites of the plain copies
        if fwd:
            cpo = [(RO[i][c[0]], RO[i][c[1]]) if c and RO[i][c[0]] != RO[i][c[1]] else None
                   for i, c in enumerate(CPS)]
            cpu = [(RU[i][c[0]], RU[i][c[1]]) if c and RU[i][c[0]] != RU[i][c[1]] else None
                   for i, c in enumerate(CPS)]
            FW = 8 * n + 16
            fstale = (1 << (2 * FW + 8)) - (1 << FW) | 1 << (2 * FW + 8 + 96 * (n + 1))
            if fwd == 2:
                for i, c in enumerate(CPS):
                    if cpo[i] and cpu[i]:
                        cpmask |= 1 << (1 + 8 * i + c[0])
            FIO = self._fwdflow(EO, cpo, blocks, bsucc, FW)
            FIU = self._fwdflow(EU, cpu, blocks, bsucc, FW, uord)
        retv = R3 | self.retuse(fn.addr)
        moved = {}
        swaps = 0
        for b, (s, e) in enumerate(blocks):
            if INO[b] is None:
                if orig[s:e] != ours[s:e]:
                    return False, 'differs in unreachable code at %08x' % (fn.addr + 4 * s)
                continue
            so, su = INO[b][:], INU[b][:]

            if fwd:
                fo, fu = FIO[b][:], FIU[b][:]
            snaps = None
            if uord and uord[s:e] != list(range(s, e)):
                # our state in front of every instruction, in the order we run them
                snaps = {}
                for i in uord[s:e]:
                    snaps[i] = (su[:], fu[:] if fwd else None)
                    for idx, bit, kill in EU[i]:
                        su[idx] = bit if kill else su[idx] | bit
                    if fwd:
                        self._fwdstep(fu, EU[i], cpu[i], i, FW)

            def same(a, c, off=0):
                x = so[a + off]
                if x == su[c + off] and (a == c or not x & idmask) and not x & cpmask:
                    return True
                if fwd and not off:
                    # copy-forwarded definitions: equal, none possibly stale
                    x, y = fo[a], fu[c]
                    return x == y and not x & fstale
                return False

            written = 0
            for i in range(s, e):
                at = '%08x' % (fn.addr + 4 * i)
                wo = orig[i]
                ops = dec(wo)[0]
                ro, ru = RO[i], RU[i]
                if snaps:
                    su, fu = snaps[i]
                if xpairs and i in xpairs:
                    for a, c in xpairs[i]:
                        if not same(a, c):
                            return False, 'extab names %s for the object the original keeps in %s at the call at %s' % (
                                rname2(c), rname2(a), at)
                rd = [k for k, o in enumerate(ops) if o[3] & (RD | SAVE)]
                if fwd == 2 and cpo[i] and cpu[i]:
                    rd = []                 # a plain copy: its readers are checked instead
                bad = [k for k in rd if not same(ro[k], ru[k])]
                if bad:
                    cp = comm(wo)
                    sw = {cp[0]: cp[1], cp[1]: cp[0]} if cp else {}
                    if cp and all(same(ro[k], ru[sw.get(k, k)]) for k in rd):
                        swaps += 1
                    else:
                        k = bad[0]
                        return False, 'operand reads a different value at %s (%s vs %s)' % (
                            at, rname2(ro[k]), rname2(ru[k]))
                for r in regbits(iuse[i]):
                    if not same(r, r):
                        return False, 'implicit use of %s differs at %s' % (rname2(r), at)
                hard = soft = 0
                if i in fn.call:
                    cu = self.inputs_of(fn.call[i])
                    hard = (cu & RETREGS) | written | KEEP
                    soft = cu & ~hard & ~NONVOL
                    written = 0
                    if i in fn.rets:
                        hard |= NONVOL | (retv & self.thru_of(fn.call[i]))
                    what = 'call'
                elif i in fn.rets:
                    hard = retv | NONVOL | KEEP
                    what = 'return'
                else:
                    for k, o in enumerate(ops):
                        if o[3] & WR:
                            written |= (1 << ro[k] | 1 << ru[k]) & ARGREGS
                for r in regbits(hard):
                    if not same(r, r):
                        return False, '%s holds a different value at the %s at %s' % (rname2(r), what, at)
                for r in regbits(soft):
                    if not same(r, r, 96):
                        return False, '%s (callee input) holds a different value at the call at %s' % (rname2(r), at)
                for k, o in enumerate(ops):
                    if o[3] & WR and ro[k] != ru[k]:
                        key = (ro[k], ru[k])
                        moved[key] = moved.get(key, 0) + 1
                for idx, bit, kill in EO[i]:
                    so[idx] = bit if kill else so[idx] | bit
                if fwd:
                    self._fwdstep(fo, EO[i], cpo[i], i, FW)
                if snaps:
                    continue
                for idx, bit, kill in EU[i]:
                    su[idx] = bit if kill else su[idx] | bit
                if fwd:
                    self._fwdstep(fu, EU[i], cpu[i], i, FW)
        txt = ' '.join('%s->%s(%d)' % (rname2(o), rname2(u), c) for (o, u), c in sorted(moved.items()))
        if swaps:
            txt += ' +%d commutative swap(s)' % swaps
        if xdiff:
            txt += ' +extab operands renamed'
        return True, 'regequiv ' + (txt.strip() or 'reads renamed only')

    def check_strict(self, fn, ours):
        """Whole-function renaming (the 2026-11-11 rule). Returns (ok, text)."""
        orig = fn.words
        if len(ours) != len(orig):
            return False, 'length differs'
        if ours == orig:
            return True, 'exact'
        if fn.opaque:
            return False, fn.opaque
        maps = {GP: {}, FP: {}, CRF: {}}
        inv = {GP: {}, FP: {}, CRF: {}}
        ours_defs = 0
        orig_defs = 0
        for i, (wo, wu) in enumerate(zip(orig, ours)):
            at = '%08x' % (fn.addr + 4 * i)
            ops, _u, idf, _p, _k, _r, _c, regmask, _cl = dec(wo)
            if (wo ^ wu) & ~regmask & 0xFFFFFFFF:
                return False, 'non-register field differs at %s (%08x vs %08x)' % (at, wo, wu)
            for base, sh, wd, role in ops:
                m = (1 << wd) - 1
                o = (wo >> sh) & m
                u = (wu >> sh) & m
                if maps[base].setdefault(o, u) != u or inv[base].setdefault(u, o) != o:
                    return False, 'no consistent renaming (%s at %s)' % (rname(base, o), at)
                if role & WR:
                    orig_defs |= 1 << (base + o)
                    ours_defs |= 1 << (base + u)
            orig_defs |= idf
            ours_defs |= idf
        # registers that must keep their number
        live = fn.liveness(self.livein_of, self.r4ret)
        xlive = fn.liveness(None, None, explicit=True)
        why = {}

        def pin(mask, reason):
            b = 0
            while mask:
                if mask & 1:
                    why.setdefault(b, reason)
                mask >>= 1
                b += 1

        pin(FIXED, 'reserved register')
        pin(fn.pin, 'implicit use')
        pin(live[0], 'live at entry')
        written = 0
        for i in range(fn.n):
            if i in fn.leader:
                written = 0
            if i in fn.call:
                at = '%08x' % (fn.addr + 4 * i)
                pin(fn.calluse[i], 'read by callee at ' + at)
                pin(written, 'argument set up before call at ' + at)
                written = 0
                if i not in fn.rets:
                    # a volatile register read after a call holds a result: r3/r4/f1 when
                    # anything (a later callee included) may read it, any other one
                    # only when this function itself reads it
                    pin(fn.liveout(i) & (R3 | R4 | F1), 'result read after call at ' + at)
                    pin(fn.liveout(i, xlive) & VOL, 'read after call at ' + at)
            else:
                written |= fn.defs[i] & ARGREGS
        ret = R3 | F1
        if self.indirect_r4 or fn.addr in self.r4ret:
            ret |= R4
        pin((orig_defs | ours_defs) & ret, 'return value')
        moved = []
        for base in (GP, FP, CRF):
            for o, u in sorted(maps[base].items()):
                if o == u:
                    continue
                moved.append('%s->%s' % (rname(base, o), rname(base, u)))
                for x in (o, u):
                    if base + x in why:
                        return False, '%s->%s but %s is pinned (%s)' % (
                            rname(base, o), rname(base, u), rname(base, x), why[base + x])
                bo, bu = 1 << (base + o), 1 << (base + u)
                if bool(bo & NONVOL) != bool(bu & NONVOL) or bool(bo & VOL) != bool(bu & VOL):
                    return False, '%s->%s crosses volatile/callee-saved' % (rname(base, o), rname(base, u))
                if base == GP:
                    for n in fn.closed:
                        if (o >= n) != (u >= n):
                            return False, '%s->%s leaves the stmw/lmw r%d range' % (
                                rname(base, o), rname(base, u), n)
        if not moved:
            return False, 'differs but no register renamed'
        return True, 'regequiv ' + ' '.join(moved)


def rname2(r):
    return rname(r & ~31 if r < CRF else CRF, r & 31 if r < CRF else r - CRF)


def rname(base, n):
    return {GP: 'r', FP: 'f', CRF: 'cr'}[base] + str(n)


# ---- extab (C++ exception tables) ------------------------------------------
# Entry: u16 flags, u16 0, then ranges {u32 start (bytes from the function), u16 size (WORDS),
# u16 action offset (from the entry start)} ended by a u32 0, then the actions. An action starts
# with a byte (bit 0x80 = last of its chain, low 7 bits = type) and a flags byte (0x80: the first
# u16 operand is a register number, 0x40: the second one). Sizes in bytes of the types seen in
# the original (6209 of 6413 entries tile exactly with them); register operands: (offset, flag bit).
EXSZ = {2: 8, 6: 12, 7: 12, 8: 16, 10: 8, 11: 12}
EXREG = {2: ((2, 0x80),), 6: ((2, 0x80),), 7: ((2, 0x80),), 8: ((2, 0x80), (4, 0x40)),
         10: ((2, 0x80),), 11: ((2, 0x80), (4, 0x40))}
EXVARY = (10, 11)      # only these may differ between original and ours


def extab_fields(ent):
    """Register operands of one extab entry (bytes). None when the entry is not fully understood
    (no operand may then differ), else {offset: (mayvary, [(pc_start, pc_end)])}."""
    n = len(ent)
    if n < 8:
        return {}
    p, rngs = 4, []
    while True:
        if p + 4 > n:
            return None
        if ent[p:p + 4] == b'\0\0\0\0':
            break
        if p + 8 > n:
            return None
        st, sz, ao = struct.unpack('>IHH', ent[p:p + 8])
        rngs.append((st, st + 4 * sz, ao))
        p += 8
    out = {}
    for st, en, ao in rngs:
        q = ao
        while True:
            if q + 2 > n:
                return None
            a, fl = ent[q], ent[q + 1]
            t = a & 0x7F
            if t not in EXSZ or q + EXSZ[t] > n:
                return None
            for off, bit in EXREG.get(t, ()):
                if fl & bit:
                    v = out.setdefault(q + off, (t in EXVARY, []))
                    v[1].append((st, en))
            q += EXSZ[t]
            if a & 0x80:
                break
    return out


def extab_pairs(fn, ent_o, ent_u):
    """Compare the extab entries of fn. Returns (pairs, why): pairs maps an instruction index
    to [(orig reg, our reg)] that must hold the same definitions there; why is not None when the
    entries differ in more than the register operands that may vary."""
    if len(ent_o) != len(ent_u):
        return None, 'extab entry size differs'
    diff = [i for i in range(len(ent_o)) if ent_o[i] != ent_u[i]]
    fields = extab_fields(ent_o)
    if fields is None:
        return {}, ('extab entry of %s is not understood but differs' % fn.name) if diff else None
    covered = set()
    pairs = {}
    for off, (vary, rngs) in fields.items():
        ro, ru = struct.unpack('>HH', ent_o[off:off + 2] + ent_u[off:off + 2])
        if ro >= 32:
            return None, 'extab register operand %d at +%#x' % (ro, off)
        if ro != ru:
            if not vary or ru >= 32:
                return None, 'extab operand at +%#x differs (r%d vs %d)' % (off, ro, ru)
            covered.update((off, off + 1))
        for st, en in rngs:
            for i in range(st // 4, (en + 3) // 4):
                if i in fn.call:
                    pairs.setdefault(i, set()).add((ro, ru))
    for i in diff:
        if i not in covered:
            return None, 'extab byte +%#x differs outside the register operands that may vary' % i
    return {i: sorted(v) for i, v in pairs.items()}, None


class Dol:
    def __init__(self, path):
        self.data = d = open(path, 'rb').read()
        h = struct.unpack('>54I', d[:0xD8])
        self.header = d[:0x100]
        self.secs = [(h[i], h[18 + i], h[36 + i], i < 7) for i in range(18) if h[36 + i]]
        self.bss = struct.unpack('>2I', d[0xD8:0xE0])

    def find(self, addr):
        for off, a, size, _t in self.secs:
            if a <= addr < a + size:
                return off + addr - a
        return None

    def read32(self, addr):
        off = self.find(addr)
        return struct.unpack('>I', self.data[off:off + 4])[0] if off is not None else None

    def words(self, addr, size):
        off = self.find(addr)
        if off is None or size % 4 or self.find(addr + size - 4) != off + size - 4:
            return None
        return list(struct.unpack('>%dI' % (size // 4), self.data[off:off + size]))


def load_syms(path):
    out = []
    rx = re.compile(r'^(\S+) = \.(?:text|init):0x([0-9A-Fa-f]+); // type:function size:0x([0-9A-Fa-f]+)')
    for line in open(path):
        m = rx.match(line)
        if m:
            out.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16)))
    out.sort(key=lambda s: s[1])
    return out


def load_allow(path):
    if not os.path.exists(path):
        return []
    return [l.split('#')[0].strip() for l in open(path) if l.split('#')[0].strip()]


def extab_ranges(P):
    """(extab start, end, extabindex start, end) from the splits of the unit list."""
    lo, hi = {}, {}
    for line in open(P['splits']):
        m = re.match(r'\s+(extab|extabindex)\s+start:0x([0-9A-Fa-f]+) end:0x([0-9A-Fa-f]+)', line)
        if m:
            k = m.group(1)
            lo[k] = min(lo.get(k, 1 << 40), int(m.group(2), 16))
            hi[k] = max(hi.get(k, 0), int(m.group(3), 16))
    return lo['extab'], hi['extab'], lo['extabindex'], hi['extabindex']


class Extab:
    """The extab entries of the ORIGINAL and of ours, per function (see extab_pairs)."""

    def __init__(self, orig, ours, P):
        self.orig, self.ours = orig, ours
        self.a0, self.a1, ia, ib = extab_ranges(P)
        self.fn_x = {}              # function address -> extab entry address
        xs = set()
        for a in range(ia, ib, 12):
            f, _sz, x = struct.unpack('>3I', orig.data[orig.find(a):orig.find(a) + 12])
            if self.a0 <= x < self.a1:
                self.fn_x.setdefault(f, x)
                xs.add(x)
        self.xs = sorted(xs) + [self.a1]
        self.x_fns = {}
        for f, x in self.fn_x.items():
            self.x_fns.setdefault(x, []).append(f)

    def entry_of(self, a):
        k = bisect.bisect_right(self.xs, a) - 1
        return self.xs[k] if 0 <= k < len(self.xs) - 1 else None

    def bytes_of(self, dol, x):
        n = self.xs[bisect.bisect_right(self.xs, x)] - x
        off = dol.find(x)
        return dol.data[off:off + n]


def check_dol(args, P):
    orig = Dol(P['orig'])
    if not os.path.exists(P['dol']):
        print('FAIL: %s not built' % P['dol'])
        return 1
    ours = Dol(P['dol'])
    if len(orig.data) != len(ours.data) or orig.header != ours.header:
        print('FAIL: DOL size or section table differs')
        return 1
    text = max((s for s in orig.secs if s[3]), key=lambda s: s[2])
    toff, taddr, tsize, _ = text
    bad = 0
    exd = {}        # extab entry address -> True, for entries with differing bytes
    if orig.data[:toff] != ours.data[:toff] or orig.data[toff + tsize:] != ours.data[toff + tsize:]:
        ex = Extab(orig, ours, P)
        exoff = orig.find(ex.a0)
        for i in range(0, len(orig.data), 4):
            if not toff <= i < toff + tsize and orig.data[i:i + 4] != ours.data[i:i + 4]:
                if exoff is not None and exoff <= i < exoff + ex.a1 - ex.a0 and ex.entry_of(ex.a0 + i - exoff):
                    exd[ex.entry_of(ex.a0 + i - exoff)] = True
                    continue
                print('FAIL: byte difference outside .text at file offset 0x%x' % i)
                bad += 1
                if bad >= 10:
                    break
        if bad:
            return 1
    else:
        ex = None
    if orig.data == ours.data:
        print('OK: main.dol is byte-identical to the original')
        return 0
    syms = load_syms(P['syms'])
    starts = [s[1] for s in syms]
    allow = set(load_allow(P['allow']))
    sallow = set(load_allow(P['sallow']))
    allow |= sallow
    n = tsize // 4
    wo = struct.unpack('>%dI' % n, orig.data[toff:toff + tsize])
    wu = struct.unpack('>%dI' % n, ours.data[toff:toff + tsize])
    touched = {}
    for i in range(n):
        if wo[i] != wu[i]:
            a = taddr + 4 * i
            k = bisect.bisect_right(starts, a) - 1
            if k < 0 or a >= syms[k][1] + syms[k][2]:
                print('FAIL: difference at %08x outside any function' % a)
                bad += 1
            else:
                touched[syms[k][0]] = touched.get(syms[k][0], 0) + 1
    prog = Program(orig, syms)
    prog.noscan = [extab_ranges(P)[2:]]
    prog.strict = args.strict
    npass = nsched = 0
    for x in sorted(exd):               # functions whose extab entry differs must be listed, and are checked
        for f in ex.x_fns.get(x, ()):
            fn = prog.fns.get(f)
            if fn is None or fn.name not in allow:
                print('FAIL extab entry %08x differs, function %s is not listed in %s' % (
                    x, fn.name if fn else '%08x' % f, os.path.relpath(P['allow'], ROOT)))
                bad += 1
            else:
                touched.setdefault(fn.name, 0)
    for name, cnt in sorted(touched.items()):
        fn = prog.byname[name]
        if name not in allow:
            print('FAIL %s: %d differing words, not listed in %s' % (name, cnt, os.path.relpath(P['allow'], ROOT)))
            bad += 1
            continue
        xpairs = None
        if ex is not None and fn.addr in ex.fn_x:
            x = ex.fn_x[fn.addr]
            xpairs, why = extab_pairs(fn, ex.bytes_of(orig, x), ex.bytes_of(ours, x))
            if why:
                print('FAIL %s: %s' % (name, why))
                bad += 1
                continue
        if name in sallow and not args.strict:
            ok, text_ = check_sched(prog, fn, ours.words(fn.addr, 4 * fn.n), xpairs)
        else:
            ok, text_ = prog.check(fn, ours.words(fn.addr, 4 * fn.n), xpairs)
        print('%s %s: %s' % ('PASS' if ok else 'FAIL', name, text_))
        if ok and text_.startswith('schedequiv'):
            nsched += 1
        if ok:
            npass += 1
        else:
            bad += 1
    for name in sorted(allow - set(touched)):
        print('note %s: listed in %s but exact (or unknown); entry can be removed' % (
            name, 'schedequiv.txt' if name in sallow else 'regequiv.txt'))
    if bad:
        print('FAIL: %d violation(s)' % bad)
        return 1
    if nsched:
        print('OK: main.dol is register/schedule-equivalent to the original (%d function(s) differ by register '
              'renaming only, %d also by instruction order inside basic blocks)' % (npass - nsched, nsched))
        return 0
    print('OK: main.dol is register-equivalent to the original (%d function(s) differ by register renaming only)' % npass)
    return 0


# ---- schedule equivalence (experimental, branch sched-equiv) ---------------
#
# f) A function listed in config/<version>/schedequiv.txt may, in addition to rule d), have
#    its instructions in a different ORDER inside basic blocks. check_sched() looks for a
#    permutation of our instructions, block by block (the blocks of the original; every
#    branch, call and return keeps its position), such that
#      1. the permuted function passes rule d) against the original (same instructions at
#         the same positions up to live-range renaming, ABI rules at calls and returns), and
#      2. the permutation only exchanges instructions of OURS that do not depend on each
#         other, i.e. our order and the permuted order are two topological orders of the
#         dependency graph of our block (sched_dag), built from the concrete registers:
#         - registers (GPR, FPR, CR fields, XER[CA], FPSCR class/condition bits): a read
#           stays after the write it sees and before the next write; a write whose value
#           is read (or is the last one in the block) stays after every earlier write;
#         - memory: a store stays ordered with every other load/store unless both use the
#           same base register holding the same value (no write to it in between) with
#           non-overlapping [off, off+size) (this covers two different stack slots);
#           indexed accesses never count as disjoint. In a function that builds a
#           hardware address (lis 0xCC00/0xCD00/0xE000) loads keep their order too;
#         - barriers keep their position and nothing crosses them: branches, calls,
#           returns, mtspr/mfspr (mflr, mtctr, ...), mfmsr/mtmsr, mftb, mfcr/mtcrf, CR
#           logic, isync/sync, the cache instructions, OE forms, mffs/mtfsf/mtfsb, record
#           forms of float instructions. (lmw/stmw were barriers until 2026-11-12; now
#           they are a load / store of 4*(32-r) bytes that reads / writes r..r31.)
#      Second form (wYA 2026-11-12, _check_sched with regs=False): when no such permutation
#      exists because ours and the original use their registers differently AND run in
#      another order, the registers are left out of the graph and rule d) is applied with
#      the reaching definitions of ours taken in our own order.
#    Two orders of the same dependency graph compute the same registers and memory, and
#    the permuted function is the original up to rule d), so ours is equivalent.

CA, FPC, FPCC, BAR = 96, 97, 98, 99       # XER[CA], FPSCR[C], FPSCR[FPCC], "everything"
CA_WR9 = {8, 10, 136, 138, 234, 202, 232, 200}
CA_RD9 = {136, 138, 234, 202, 232, 200}
MEMSZ = {32: 4, 33: 4, 34: 1, 35: 1, 36: 4, 37: 4, 38: 1, 39: 1, 40: 2, 41: 2, 42: 2, 43: 2, 44: 2, 45: 2,
         48: 4, 49: 4, 50: 8, 51: 8, 52: 4, 53: 4, 54: 8, 55: 8, 56: 8, 57: 8, 60: 8, 61: 8}
HWHI = {0xCC00, 0xCD00, 0xE000}
_smemo = {}


def sched_info(w):
    """What matters for reordering: (reads, writes, barrier, mem) or None when unknown.
    reads/writes are frozensets of resources (register numbers as in the masks, CA, FPC,
    FPCC); mem is None or (is_store, base, off, size) with base = GPR number, -1 for an
    absolute address, None for an unknown (indexed) address."""
    r = _smemo.get(w)
    if r is None and w not in _smemo:
        r = _smemo[w] = _sched_info(w)
    return r


def _sched_info(w):
    d = dec(w)
    if d is None:
        return None
    ops, use, defs, _pin, kind, _rel, _cond, _m, _closed = d
    rd, wr = set(regbits(use)), set(regbits(defs))
    for base, sh, wd, role in ops:
        r = base + ((w >> sh) & ((1 << wd) - 1))
        if role & (RD | SAVE):
            rd.add(r)
        if role & WR:
            wr.add(r)
    op = w >> 26
    xo = (w >> 1) & 1023
    x9 = xo & 511
    A = (w >> 16) & 31
    bar = kind != ''
    mem = None
    if op in (8, 12, 13):
        wr.add(CA)
    elif op == 19:
        if xo != 0:                       # everything but mcrf: branches, CR logic, isync
            bar = True
    elif op == 31:
        if xo in (0, 32):
            pass
        elif (x9 in X_DAB and not (xo >= 512 and x9 in (75, 11))) or x9 in X_DA:
            if xo >= 512:                 # OE form: XER[OV,SO]
                bar = True
            if x9 in CA_WR9:
                wr.add(CA)
            if x9 in CA_RD9:
                rd.add(CA)
        elif xo in (792, 824):
            wr.add(CA)
        elif xo in LOADX or xo in LOADUX or xo in FLOADX or xo in FLOADUX:
            mem = (False, None, 0, 0)
        elif xo in STOREX or xo in STOREUX or xo in FSTOREX or xo in FSTOREUX:
            mem = (True, None, 0, 0)
        elif xo in (339, 83, 371, 467, 146, 19, 144, 598) or xo in CACHE:
            bar = True
    elif 32 <= op <= 45:
        mem = (not (op < 36 or 40 <= op <= 43), A if A else -1, sext(w & 0xFFFF, 16), MEMSZ[op])
    elif op in (46, 47):                  # lmw / stmw: a load / store of 4*(32-r) bytes
        first = (w >> 21) & 31
        if op == 47:
            rd.update(range(first, 32))   # also in a prologue, where dec() does not count them
        mem = (op == 47, A if A else -1, sext(w & 0xFFFF, 16), 4 * (32 - first))
    elif 48 <= op <= 55:
        mem = (op >= 52, A if A else -1, sext(w & 0xFFFF, 16), MEMSZ[op])
    elif op in (56, 57, 60, 61):
        mem = (op >= 60, A if A else -1, sext(w & 0xFFF, 12), MEMSZ[op])
    elif op in (59, 63):
        x5 = xo & 31
        if x5 in (18, 20, 21, 25, 28, 29, 30, 31) or (x5 == 24 and op == 59) or (x5 == 26 and op == 63):
            wr.update((FPC, FPCC))
            if w & 1:
                bar = True
        elif x5 == 23 and op == 63:       # fsel: no FPSCR
            if w & 1:
                bar = True
        elif xo in (0, 32):               # fcmpu fcmpo
            wr.add(FPCC)
        elif xo == 12:                    # frsp
            wr.update((FPC, FPCC))
            if w & 1:
                bar = True
        elif xo in (14, 15):              # fctiw(z): FPRF undefined, keep it in place
            rd.update((FPC, FPCC))
            wr.update((FPC, FPCC))
            if w & 1:
                bar = True
        elif xo in (40, 72, 136, 264):    # fneg fmr fnabs fabs
            if w & 1:
                bar = True
        else:                             # mffs mtfsf mtfsb0/1
            bar = True
    return (frozenset(rd), frozenset(wr), bar, mem)


SCHED_RELAX = ('global', 'pointer')       # memory rules beyond "same base": see SchedCtx


class SchedCtx:
    """Facts about one function (OUR words) that the memory rules of sched_dag need.

    hw:       the function builds a hardware address (loads keep their order)
    frame:    per instruction, True when r1 is this function's own frame pointer there:
              the function allocates its frame with one `stwu r1,-N(r1)` and r1 is written
              by nothing else but `addi r1,r1,N` / `lwz r1,0(r1)` (forward dataflow over the
              control-flow graph; None when anything else happens). An r1-based access is an
              OWN-FRAME access when it lies inside [0, N) there.
    Rule 'global' (wYA 2026-11-12): an own-frame access is disjoint from an access to a
      global: base r13 / r2 (never written in the function; the address must lie in a section
      of the DOL or in its bss range, the stack is in neither), or a base register that holds,
      from a lis / lis+addi in the same block, a constant address inside those ranges. Before
      linking (--list): an @sda21 access, or @l(rX) with rX from a relocated lis @ha.
    Rule 'pointer': an own-frame access is disjoint from an access through ANY other base
      (also indexed) when no frame address can exist outside r1: in the original and in ours
      r1 appears only as the base of displacement loads/stores (lmw/stmw included), in the
      `stwu r1,-N(r1)` of the prologue and in `addi r1,r1,N` / `lwz r1,0(r1)`.
    Accesses at or above N (the caller's frame, stack parameters, the LR slot) and negative
    offsets get neither rule."""

    def __init__(self, prog=None, fn=None, orig=(), ours=(), rel=None, relax=None):
        self.relax = SCHED_RELAX if relax is None else relax
        self.rel = rel
        self.hw = any(w >> 26 == 15 and (w & 0xFFFF) in HWHI for ws in (orig, ours) for w in ws)
        self.frame = None
        self.size = 0
        self.noescape = False
        self.sda = {}
        self.dol = getattr(prog, 'dol', None)
        if fn is None or not self.relax:
            return
        self._frame(fn, ours)
        if self.frame is None:
            return
        self.noescape = not (self._escapes(orig) or self._escapes(ours))
        sda = getattr(prog, 'sda', None) or {}
        for r in (2, 13):
            if r in sda and not any((1 << r) & self._wmask(w) for w in ours):
                self.sda[r] = sda[r]

    @staticmethod
    def _wmask(w):
        si = sched_info(w)
        m = 0
        for r in (si[1] if si else range(32)):
            if r < 32:
                m |= 1 << r
        return m

    def _frame(self, fn, ours):
        n = len(ours)
        st = [None] * n
        st[0] = False
        size = None
        work = [0]
        while work:
            i = work.pop()
            w = ours[i]
            cur = st[i]
            if self._wmask(w) & 2:
                if w >> 16 == 0x9421 and w & 0x8000 and not cur and size in (None, 0x10000 - (w & 0xFFFF)):
                    size = 0x10000 - (w & 0xFFFF)
                    cur = True
                elif cur and (w == 0x38210000 | size or w == 0x80210000) and size < 0x8000:
                    cur = False
                else:
                    return
            for t in fn.succ[i]:
                if st[t] is None:
                    st[t] = cur
                    work.append(t)
                elif st[t] != cur:
                    return
        if size:
            self.frame, self.size = st, size

    @staticmethod
    def _escapes(words):
        for w in words:
            d = dec(w)
            if d is None:
                return True
            op = w >> 26
            for base, sh, _wd, role in d[0]:
                if base != GP or (w >> sh) & 31 != 1:
                    continue
                if sh == 16 and (32 <= op <= 57 or op in (60, 61)):
                    continue                              # base of a displacement load/store
                if w >> 16 == 0x9421 or w >> 16 == 0x3821 or w == 0x80210000:
                    continue                              # stwu r1,-N(r1) / addi r1,r1,N / lwz r1,0(r1)
                return True
        return False

    def isglobal(self, addr, size):
        d = self.dol
        if d is None:
            return False
        for _off, a, sz, _t in d.secs:
            if a <= addr and addr + size <= a + sz:
                return True
        b = getattr(d, 'bss', None)
        return bool(b) and b[0] <= addr and addr + size <= b[0] + b[1]


def sched_dag(words, s, e, hw, rel=None, regs=True):
    """Dependency graph of the block words[s:e]: (preds, barriers) with preds[p] = set of
    block positions that must stay before p; None when an instruction is unknown."""
    m = e - s
    cx = hw if isinstance(hw, SchedCtx) else None
    if cx:
        hw = cx.hw
    preds = [set() for _ in range(m)]
    events = {}
    mems = []
    ver = {}
    bars = []
    const = {}                            # register -> constant it holds ('G': a relocated address)
    for p in range(m):
        w = words[s + p]
        si = sched_info(w)
        if si is None:
            return None
        rd, wr, bar, mem = si
        cls = None                        # 'G' global, 'F' own frame, 'P' any other base but r1
        if mem and cx and cx.frame is not None:
            _st, base, off, size = mem
            rl = rel.get(s + p) if rel else None
            if base == 1:
                if not rl and cx.frame[s + p] and 0 <= off and off + size <= cx.size:
                    cls = 'F'
            else:
                cls = 'P'
                if rl:
                    if any(x[0] == 109 for x in rl[2]) or \
                            (const.get(base) == 'G' and all(x[0] == 4 for x in rl[2])):
                        cls = 'G'
                elif base in cx.sda:
                    if cx.isglobal((cx.sda[base] + off) & 0xFFFFFFFF, size):
                        cls = 'G'
                elif base is not None and isinstance(const.get(base), int):
                    if cx.isglobal((const[base] + off) & 0xFFFFFFFF, size):
                        cls = 'G'
        for r in rd:
            if regs or r >= 96:
                events.setdefault(r, []).append((p, False))
        events.setdefault(BAR, []).append((p, False))
        if mem:
            st, base, off, size = mem
            if rel and s + p in rel:      # displacement not known before linking
                base = None
            key = None if base is None else (base, ver.get(base, 0))
            for q, st2, key2, off2, size2, cls2 in mems:
                if not (st or st2 or hw):
                    continue
                if key is not None and key == key2 and (off + size <= off2 or off2 + size2 <= off):
                    continue
                if cls and cls2 and 'F' in (cls, cls2) and cls != cls2:
                    if 'G' in (cls, cls2) and 'global' in cx.relax:
                        continue
                    if cx.noescape and 'pointer' in cx.relax:
                        continue
                preds[p].add(q)
            mems.append((p, st, key, off, size, cls))
        const_a = const.get((w >> 16) & 31)
        for r in wr:
            if regs or r >= 96:
                events.setdefault(r, []).append((p, True))
            ver[r] = ver.get(r, 0) + 1
            const.pop(r, None)
        if w >> 26 == 15 and not (w >> 16) & 31:                      # lis
            rl = rel.get(s + p) if rel else None
            const[(w >> 21) & 31] = ('G' if all(x[0] in (5, 6) for x in rl[2]) else None) if rl else \
                (w & 0xFFFF) << 16
        elif w >> 26 == 14 and (w >> 16) & 31:                        # addi rD,rA,imm
            rl = rel.get(s + p) if rel else None
            v = None
            if rl:
                v = 'G' if const_a == 'G' and all(x[0] == 4 for x in rl[2]) else None
            elif isinstance(const_a, int):
                v = (const_a + sext(w & 0xFFFF, 16)) & 0xFFFFFFFF
            if v is not None:
                const[(w >> 21) & 31] = v
        if bar:
            const = {}
            events[BAR].append((p, True))
            bars.append(p)
            mems = []                     # everything before is ordered through the barrier
    for res, ev in events.items():
        if res != BAR and bars:
            # a barrier (a call, ...) may read anything: the value a register has there is live
            ev = sorted(ev + [(b, False) for b in bars])
        live = [False] * len(ev)
        lastw = None
        for k, (p, isw) in enumerate(ev):
            if isw:
                lastw = k
            elif lastw is not None:
                live[lastw] = True
        if lastw is not None:
            live[lastw] = True
        cur = None
        readers = []
        dead = []
        for k, (p, isw) in enumerate(ev):
            if not isw:
                if cur is not None and cur != p:
                    preds[p].add(cur)
                readers.append(p)
            else:
                for q in readers:
                    if q != p:
                        preds[p].add(q)
                if live[k]:
                    preds[p].update(dead)
                    if cur is not None:
                        preds[p].add(cur)
                    cur, readers, dead = p, [], []
                else:
                    dead.append(p)
    return preds, bars


def sched_keys(words, s, e, rel):
    """Per instruction: (non-register bits, operand layout, relocation types/addends)."""
    out = []
    for i in range(s, e):
        w = words[i]
        rk = None
        if rel and i in rel:
            w &= ~rel[i][0]
            rk = rel[i][1]
        d = dec(w)
        if d is None:
            return None
        out.append((w & ~d[7] & 0xFFFFFFFF,
                    tuple((b, sh, bool(r & WR), bool(r & (RD | SAVE))) for b, sh, _w, r in d[0]), rk))
    return out


def sched_sigs(words, keys, s, e, rel):
    """Order- and register-independent labels of the instructions of a block, from the
    def-use structure inside the block: per instruction (finest, ..., coarsest)."""
    m = e - s
    srcs = []                # per instruction: [(slot, def position or None, def slot or class)]
    cons = [[] for _ in range(m)]
    lastdef = {}
    lastslots = [[] for _ in range(m)]
    argmark = [[] for _ in range(m)]     # values an ABI boundary sees: (slot, register)
    since = -1
    cpair = []
    for p in range(m):
        w = words[s + p]
        if rel and s + p in rel:
            w &= ~rel[s + p][0]
        ops = dec(w)[0]
        rd, wr, _bar, _mem = sched_info(w)
        cp = comm(w)
        cpair.append(cp)
        if dec(w)[4] in ('bl', 'icall', 'ret', 'b', 'bctr'):
            for r, (dp, ds) in lastdef.items():
                if dp > since and ds < 100 and ((1 << r) & (ARGREGS | NONVOL)):
                    argmark[dp].append((ds, r))
            since = p
        lst = []
        seen = set()
        for k, (b, sh, wd, role) in enumerate(ops):
            if role & (RD | SAVE):
                r = b + ((w >> sh) & ((1 << wd) - 1))
                seen.add(r)
                slot = cp[0] if cp and k in cp else k
                ld = lastdef.get(r)
                if ld is None:
                    lst.append((slot, None, r if r in (1, 2, 13) else 200 + b))
                else:
                    lst.append((slot, ld[0], ld[1]))
                    cons[ld[0]].append((ld[1], p, slot))
        for r in sorted(rd - seen):
            ld = lastdef.get(r)
            if ld is None:
                lst.append((100 + r, None, r))
            else:
                lst.append((100 + r, ld[0], ld[1]))
                cons[ld[0]].append((ld[1], p, 100 + r))
        srcs.append(lst)
        seen = set()
        for k, (b, sh, wd, role) in enumerate(ops):
            if role & WR:
                r = b + ((w >> sh) & ((1 << wd) - 1))
                seen.add(r)
                lastdef[r] = (p, k)
        for r in wr - seen:
            lastdef[r] = (p, 100 + r)
    for p, slot in lastdef.values():
        lastslots[p].append(slot)

    def back(L):
        out = []
        for p in range(m):
            out.append(hash((keys[p], tuple(sorted(
                (slot, -1, c) if dp is None else (slot, L[dp], c) for slot, dp, c in srcs[p])))))
        return out

    def fwd(Bv):
        return [hash((Bv[p], tuple(sorted((ds, Bv[c], cs) for ds, c, cs in cons[p])),
                      tuple(sorted(lastslots[p])), tuple(sorted(argmark[p])))) for p in range(m)]

    B = []
    for p in range(m):       # defs come first, so one pass in order
        B.append(hash((keys[p], tuple(sorted(
            (slot, -1, c) if dp is None else (slot, B[dp], c) for slot, dp, c in srcs[p])))))
    F = fwd(B)
    B2 = back(F)
    F2 = fwd(B2)
    return [(F2[p], B2[p], B[p], hash(keys[p])) for p in range(m)]


def rel_compat(a, b, symaddr):
    """Relocations of ours / of the original at one instruction: None when they cannot be
    the same, else the number of targets that could not be compared by name."""
    if [(x[0], x[3]) for x in a] != [(x[0], x[3]) for x in b]:
        return None
    loose = 0
    for (_ty, na, ba, _ad), (_ty2, nb, _bb, _ad2) in zip(a, b):
        if na != nb:
            aa, ab = symaddr.get(na, ()), symaddr.get(nb, ())
            if ba != 0 and len(aa) == 1 and len(ab) == 1:
                if aa != ab:
                    return None
            else:
                loose += 1
    return loose


def sched_match(orig, ours, s, e, hw, rel=None, symaddr=None, regs=True):
    """A permutation perm (perm[j] = position in our block of the instruction that goes to
    position j of the original block) that respects the dependencies of OUR block:
    (perm, preds, bars, loose) or (None, reason, None, 0)."""
    orel, urel = rel if rel else (None, None)
    ko, ku = sched_keys(orig, s, e, orel), sched_keys(ours, s, e, urel)
    if ko is None or ku is None:
        return None, 'unknown instruction', None, 0
    cnt = {}
    for k in ko:
        cnt[k] = cnt.get(k, 0) + 1
    for k in ku:
        cnt[k] = cnt.get(k, 0) - 1
    if any(cnt.values()):
        return None, 'the block does not hold the same instructions', None, 0
    dag = sched_dag(ours, s, e, hw, urel, regs)
    if dag is None:
        return None, 'unknown instruction', None, 0
    preds, bars = dag
    so, su = sched_sigs(orig, ko, s, e, orel), sched_sigs(ours, ku, s, e, urel)
    m = e - s
    idx = [{} for _ in range(4)]
    for k in range(m):
        for lv in range(4):
            idx[lv].setdefault(su[k][lv], []).append(k)
    placed = [False] * m
    perm = []
    loose = 0
    for j in range(m):
        pick = None
        blocked = False
        for lv in range(4):
            first = None
            for k in idx[lv].get(so[j][lv], ()):
                if placed[k] or ko[j] != ku[k]:
                    continue
                if rel and (s + j in orel or s + k in urel):
                    if rel_compat(urel[s + k][2], orel[s + j][2], symaddr) is None:
                        continue
                if any(not placed[q] for q in preds[k]):
                    blocked = True
                    continue
                # among equally labelled candidates: the same word, then the same position
                rank = (0 if ours[s + k] == orig[s + j] else 1, 0 if k == j else 1, k)
                if first is None or rank < first:
                    first = rank
            if first is not None:
                pick = first[2]
                break
        if pick is None:
            return None, ('the order differs across a dependency' if blocked else
                          'no counterpart for the instruction') + ' at +0x%x' % (4 * (s + j)), None, 0
        if rel and s + j in orel:
            loose += rel_compat(urel[s + pick][2], orel[s + j][2], symaddr)
        placed[pick] = True
        perm.append(pick)
    return perm, preds, bars, loose


def check_sched(prog, fn, ours, xpairs=None, rel=None, relax=None):
    """Rule f): (ok, text). rel (object files only) = (orel, urel), index -> (mask of the
    relocated bits, ((type, addend), ...), relocations); the relocated bits of our words
    are then taken from the original after the instructions have been paired."""
    orig = fn.words
    n = fn.n
    if len(ours) != n:
        return False, 'length differs'
    if rel is None:
        ok, text = prog.check_webs(fn, ours, xpairs)
        if ok:
            return ok, text
    why = prog.unsupported(fn)
    if why:
        return False, why
    blocks = prog._webinfo(fn)[0]
    hw = SchedCtx(prog, fn, orig, ours, rel[1] if rel else None, relax)
    ok, text = _check_sched(prog, fn, ours, xpairs, rel, blocks, hw, True)
    if not ok:
        # second form (wYA 2026-11-12): registers by reaching definitions instead of by the
        # dependency graph of our register numbers, see _check_sched
        ok2, text2 = _check_sched(prog, fn, ours, xpairs, rel, blocks, hw, False)
        if ok2:
            return ok2, text2
    return ok, text


def _check_sched(prog, fn, ours, xpairs, rel, blocks, hw, regs):
    """One attempt of rule f). regs=True: our order and the original order must be two
    orders of the dependency graph of OUR block including our register numbers, and our
    instructions in the original order must pass rule d).
    regs=False: the graph only holds what rule d) does not follow (memory, XER[CA], the
    FPSCR bits, barriers). The registers are checked by rule d) itself with the reaching
    definitions of ours computed in OUR order (Program._check_webs with uord): every read
    must see the definitions the original's read sees, a definition being named by the
    position of its instruction in the original. So ours may reuse one register where the
    original keeps two values in two registers at once, and the other way round; a read
    that our order moves across a write of its register sees another definition and fails."""
    orig = fn.words
    n = fn.n
    new = list(ours)
    uord = list(range(n))
    moved = nb = loose = 0
    for s, e in blocks:
        if rel is None and orig[s:e] == ours[s:e]:
            continue
        perm, preds, bars, lo = sched_match(orig, ours, s, e, hw, rel, getattr(prog, 'symaddr', None), regs)
        if perm is None:
            return False, 'sched: %s (block %08x-%08x)' % (preds, fn.addr + 4 * s, fn.addr + 4 * e)
        # independent re-check of what sched_match promises
        m = e - s
        if sorted(perm) != list(range(m)):
            return False, 'sched: internal error (not a permutation)'
        pos = [0] * m
        for j, k in enumerate(perm):
            pos[k] = j
        if any(pos[q] >= pos[k] for k in range(m) for q in preds[k]) or any(pos[k] != k for k in bars):
            return False, 'sched: internal error (dependency not respected)'
        loose += lo
        for j, k in enumerate(perm):
            uord[s + k] = s + j
            w = ours[s + k]
            if rel and s + j in rel[0]:
                mask = rel[0][s + j][0]
                w = (w & ~mask) | (orig[s + j] & mask)
            new[s + j] = w
        d = sum(1 for j, k in enumerate(perm) if j != k)
        if d:
            moved += d
            nb += 1
    ok, text = prog.check_webs(fn, new, xpairs, None if regs else uord)
    if not ok:
        return False, ('sched: after reordering %d instruction(s): ' % moved if moved else '') + text
    if loose:
        text += ' [%d local relocation target(s) not compared by name]' % loose
    if not moved:
        return True, text
    return True, 'schedequiv %d instruction(s) reordered in %d block(s)%s; %s' % (
        moved, nb, '' if regs else ' (registers by reaching definitions)', text)


def obj_rel(prog, name, mine, tgt):
    """Our raw words and the relocation tables of both objects for check_sched:
    (words, (orel, urel)) or (None, reason)."""
    fn = prog.byname.get(name)
    m = mine.func(name)
    t = tgt.func(name)
    if fn is None or m is None or t is None:
        return None, 'missing'
    mw, mr = m
    tw, tr = t
    if len(mw) != fn.n or len(tw) != fn.n:
        return None, 'size differs (%d vs %d bytes)' % (4 * len(mw), 4 * fn.n)
    out = []
    for r in (tr, mr):
        d = {}
        for i, lst in r.items():
            mask = 0
            for ty, _n, _b, _a in lst:
                if ty not in RELMASK:
                    return None, 'unsupported relocation type %d' % ty
                mask |= RELMASK[ty]
            d[i] = (mask, tuple((x[0], x[3]) for x in lst), lst)
        out.append(d)
    return list(mw), tuple(out)


# ---- --list: object files -------------------------------------------------

RELMASK = {4: 0xFFFF, 5: 0xFFFF, 6: 0xFFFF, 10: 0x03FFFFFC, 11: 0xFFFC, 109: 0x001FFFFF}


class Obj:
    def __init__(self, path):
        d = self.d = open(path, 'rb').read()
        shoff, = struct.unpack('>I', d[0x20:0x24])
        shentsize, shnum, _ = struct.unpack('>3H', d[0x2E:0x34])
        self.sh = [struct.unpack('>10I', d[shoff + i * shentsize:shoff + i * shentsize + 40]) for i in range(shnum)]
        self.funcs = {}
        self.syms = []
        for s in self.sh:
            if s[1] == 2:
                stro = self.sh[s[6]][4]
                for o in range(s[4], s[4] + s[5], 16):
                    nm, val, size, info, _oth, shndx = struct.unpack('>3I2BH', d[o:o + 16])
                    name = d[stro + nm:d.index(b'\0', stro + nm)].decode('latin1')
                    self.syms.append((name, info >> 4, shndx, val))
                    if info & 15 == 2 and size:
                        self.funcs[name] = (shndx, val, size)
        self.rel = {}
        for s in self.sh:
            if s[1] == 4:
                r = self.rel.setdefault(s[7], {})
                for o in range(s[4], s[4] + s[5], 12):
                    off, info, add = struct.unpack('>IIi', d[o:o + 12])
                    r.setdefault(off & ~3, []).append((info & 255, info >> 8, add))

    def func(self, name):
        if name not in self.funcs:
            return None
        shndx, val, size = self.funcs[name]
        base = self.sh[shndx][4] + val
        words = list(struct.unpack('>%dI' % (size // 4), self.d[base:base + size]))
        rels = {}
        for off, lst in self.rel.get(shndx, {}).items():
            if val <= off < val + size:
                rels[(off - val) // 4] = sorted(
                    (t, self.syms[s][0], self.syms[s][1], add) for t, s, add in lst)
        return words, rels


def load_units(P):
    units = []  # (unit, start, end)
    cur = None
    for line in open(P['splits']):
        if line and not line[0].isspace() and line.rstrip().endswith(':'):
            cur = os.path.splitext(line.rstrip()[:-1])[0]
        m = re.match(r'\s+\.text\s+start:0x([0-9A-Fa-f]+) end:0x([0-9A-Fa-f]+)', line)
        if m and cur:
            units.append((cur, int(m.group(1), 16), int(m.group(2), 16)))
    return units


def load_program(args, P):
    prog = Program(Dol(P['orig']), load_syms(P['syms']))
    prog.noscan = [extab_ranges(P)[2:]]
    prog.strict = args.strict
    prog.symaddr = {}
    for line in open(P['syms']):
        m = re.match(r'^(\S+) = [^:]+:0x([0-9A-Fa-f]+);', line)
        if m:
            prog.symaddr.setdefault(m.group(1), set()).add(int(m.group(2), 16))
    return prog


def list_mode(args, P):
    prog = load_program(args, P)
    units = load_units(P)
    rc = 0
    for arg in args.list:
        unit, _, only = arg.partition(':')
        if not only and unit in prog.byname:
            only = unit
            a = prog.byname[unit].addr
            unit = next((u for u, s, e in units if s <= a < e), None)
            if unit is None:
                print('FAIL %s: no unit' % only)
                rc = 1
                continue
        want = set(only.split(',')) if only else None
        try:
            mine = Obj(os.path.join(P['build'], 'src', unit + '.o'))
            tgt = Obj(os.path.join(P['build'], 'obj', unit + '.o'))
        except OSError as e:
            print('FAIL %s: %s' % (unit, e))
            rc = 1
            continue
        res = {'exact': 0, 'regequiv': 0, 'schedequiv': 0, 'fail': 0}
        names = sorted(tgt.funcs, key=lambda k: tgt.funcs[k][1])
        for name in names:
            if want and name not in want:
                continue
            ok, text_ = list_one(prog, name, mine, tgt)
            key = 'fail' if not ok else 'exact' if text_.startswith('exact') else \
                'schedequiv' if text_.startswith('schedequiv') else 'regequiv'
            res[key] += 1
            if key != 'exact' or want or args.verbose:
                print('%s %s %s: %s' % ('PASS' if ok else 'FAIL', unit, name, text_))
        if not want:
            verdict = 'QUALIFIES-SCHED' if not res['fail'] and res['schedequiv'] else \
                'QUALIFIES' if not res['fail'] and res['regequiv'] else \
                'EXACT' if not res['fail'] else 'NO'
            print('UNIT %s: %s (%d exact, %d regequiv, %s%d fail)' % (
                unit, verdict, res['exact'], res['regequiv'],
                '%d schedequiv, ' % res['schedequiv'] if res['schedequiv'] else '', res['fail']))
        if res['fail']:
            rc = 1
    return rc


def list_one(prog, name, mine, tgt, sched=True):
    ours, text_, loose = obj_words(prog, name, mine, tgt)
    if ours is not None:
        ok, text_ = prog.check(prog.byname[name], ours)
        if ok and loose:
            text_ += ' [%d local relocation target(s) not compared by name]' % loose
    else:
        ok = False
    if ok or not sched or prog.strict or name not in prog.byname or text_.startswith(('size', 'missing', 'not a')):
        return ok, text_
    raw, rel = obj_rel(prog, name, mine, tgt)       # rule f): instruction order inside blocks
    if raw is None:
        return False, text_
    ok2, text2 = check_sched(prog, prog.byname[name], raw, None, rel)
    if ok2:
        return ok2, text2
    return False, text_ + (' / ' + text2 if text2.startswith('sched') else '')


def obj_words(prog, name, mine, tgt):
    """Our words of the function with the relocated fields taken from the original:
    (words, None, loose) or (None, reason, 0)."""
    fn = prog.byname.get(name)
    if fn is None:
        return None, 'not a function in symbols.txt', 0
    m = mine.func(name)
    t = tgt.func(name)
    if m is None:
        return None, 'missing in our object', 0
    mw, mr = m
    tw, tr = t
    if len(mw) != fn.n or len(tw) != fn.n:
        return None, 'size differs (%d vs %d bytes)' % (4 * len(mw), 4 * fn.n), 0
    if sorted(mr) != sorted(tr):
        return None, 'relocations at different places', 0
    loose = 0
    ours = list(mw)
    for i in mr:
        a, b = mr[i], tr[i]
        if [(x[0], x[3]) for x in a] != [(x[0], x[3]) for x in b]:
            return None, 'relocation type/addend differs at +0x%x' % (4 * i), 0
        mask = 0
        for (ty, na, ba, _ad), (_ty, nb, bb, _ad2) in zip(a, b):
            if ty not in RELMASK:
                return None, 'unsupported relocation type %d' % ty, 0
            mask |= RELMASK[ty]
            if na != nb:
                aa, ab = prog.symaddr.get(na, ()), prog.symaddr.get(nb, ())
                if ba != 0 and len(aa) == 1 and len(ab) == 1:
                    if aa != ab:
                        return None, 'relocation target differs at +0x%x (%s vs %s)' % (4 * i, na, nb), 0
                else:
                    loose += 1
        ours[i] = (ours[i] & ~mask) | (fn.words[i] & mask)
    return ours, None, loose


# ---- --selftest -----------------------------------------------------------

# passed the whole-function rule on 2026-11-11; must keep passing
SELFTEST = ['fn_8019A7D0', 'fn_800F8274', 'fn_8013213C', 'fn_801E26B0', 'fn_8020FAA8', 'fn_8026E4C4']


def copy_of(w):
    """True for a plain register copy: or rA,rS,rS / ori rA,rS,0 / fmr (no record form)."""
    op = w >> 26
    if op == 31:
        return (w >> 1) & 1023 == 444 and not w & 1 and (w >> 21) & 31 == (w >> 11) & 31
    if op == 24:
        return w & 0xFFFF == 0
    if op == 63:
        return (w >> 1) & 1023 == 72 and not w & 1
    return False


def swap_class(w):
    """Name of a non-commutative two-source instruction, else None."""
    op = w >> 26
    xo = (w >> 1) & 1023
    if op == 31:
        if xo in (0, 32):
            return 'cmpw'
        if xo & 511 in (40, 8, 136):
            return 'subf'
        if xo & 511 in (491, 459):
            return 'divw'
        if xo in (60, 412, 24, 536, 792):
            return 'andc/orc/shift'
    elif op in (59, 63):
        if (w >> 1) & 31 == 18:
            return 'fdiv'
        if (w >> 1) & 31 == 20:
            return 'fsub'
        if op == 63 and xo in (0, 32):
            return 'fcmp'
    return None


def setfield(w, sh, wd, v):
    m = ((1 << wd) - 1) << sh
    return (w & ~m) | (v << sh)


def mutations(fn, ours):
    """Corrupted copies of `ours`: yields (kind, index, word). Every kind except
    'commutative' changes the meaning of the function."""
    seen = set()
    todo = [0]
    while todo:                                   # reachable instructions
        i = todo.pop()
        if i not in seen:
            seen.add(i)
            todo.extend(fn.succ[i])
    for i in sorted(seen):
        w = ours[i]
        ops = dec(fn.words[i])[0]
        reg = [(w >> sh) & ((1 << wd) - 1) for _b, sh, wd, _r in ops]
        rd = [k for k, o in enumerate(ops) if o[3] & (RD | SAVE)]
        for k in rd:                              # read a different register
            _b, sh, wd, _r = ops[k]
            r = reg[k]
            yield 'operand', i, setfield(w, sh, wd, r + 1 if r + 1 < 1 << wd else r - 1)
        pure = [k for k in rd if not ops[k][3] & WR]
        cls = swap_class(fn.words[i])
        cp = comm(fn.words[i])
        pair = cp if cp else (pure[0], pure[1]) if cls and len(pure) == 2 else None
        if pair and reg[pair[0]] != reg[pair[1]]:
            a, b = pair
            x = setfield(setfield(w, ops[a][1], ops[a][2], reg[b]), ops[b][1], ops[b][2], reg[a])
            yield ('commutative' if cp else 'swap ' + cls), i, x
    leaders = fn.leader
    for i in sorted(fn.call):                     # move an argument to another register
        if i in fn.rets or i not in seen:
            continue
        j = i - 1
        while j >= 0 and j not in fn.call:
            wo = fn.words[j]
            hit = [(k, o) for k, o in enumerate(dec(wo)[0]) if o[3] & WR and
                   (1 << (o[0] + ((wo >> o[1]) & 31))) & ARGREGS]
            if hit:
                k, (_b, sh, wd, _r) = hit[0]
                r = (ours[j] >> sh) & 31
                yield 'call argument', j, setfield(ours[j], sh, wd, r + 1 if r < 8 else r - 1)
                break
            if j in leaders:
                break
            j -= 1


def synth_tests():
    """Hand-made functions for the copy-forwarding rule: (name, target, ours, must pass)."""
    def addi(d, a, i): return 14 << 26 | d << 21 | a << 16 | i
    def mr(d, sr): return 31 << 26 | sr << 21 | d << 16 | sr << 11 | 444 << 1
    def add(d, a, b): return 31 << 26 | d << 21 | a << 16 | b << 11 | 266 << 1
    def cmpwi(a, i): return 11 << 26 | a << 16 | i
    def subf(d, a, b): return 31 << 26 | d << 21 | a << 16 | b << 11 | 40 << 1
    def bl(off): return 18 << 26 | (off & 0x3FFFFFC) | 1
    def bc(bo, bi, off): return 16 << 26 | bo << 21 | bi << 16 | (off & 0xFFFC)
    blr = 0x4E800020
    g = 0x1000
    ret = [mr(3, 31), blr]
    cases = [
        # the result of an addi is copied: either register may take the address
        ('copy order', [addi(3, 4, 8), mr(31, 3), bl(g - 0x2008), mr(3, 31), blr],
                       [addi(31, 4, 8), mr(3, 31), bl(g - 0x2008), mr(3, 31), blr], True),
        ('copy order, other reader', [addi(3, 4, 8), mr(31, 3), bl(g - 0x2008), mr(3, 31), blr],
                                     [addi(31, 4, 8), mr(3, 31), bl(g - 0x2008), mr(3, 30), blr], False),
        ('copy order, wrong value', [addi(3, 4, 8), mr(31, 3), bl(g - 0x2008), mr(3, 31), blr],
                                    [addi(31, 4, 9), mr(3, 31), bl(g - 0x2008), mr(3, 31), blr], False),
        # reading the copy after its source was redefined is not reading the source
        ('stale copy (straight)', [addi(5, 4, 1), mr(6, 5), addi(5, 4, 2), add(3, 6, 6), blr],
                                  [addi(5, 4, 1), mr(6, 5), addi(5, 4, 2), add(3, 5, 5), blr], False),
        # same inside a loop: the copy is older than the last execution of the source's site
        ('stale copy (loop)', [addi(5, 4, 1), cmpwi(3, 0), bc(12, 2, 12), mr(6, 5), cmpwi(4, 5), bc(4, 2, -20),
                               add(3, 6, 6), blr],
                              [addi(5, 4, 1), cmpwi(3, 0), bc(12, 2, 12), mr(6, 5), cmpwi(4, 5), bc(4, 2, -20),
                               add(3, 5, 5), blr], False),
        ('copy of a copy', [addi(3, 4, 8), mr(31, 3), mr(30, 31), bl(g - 0x200C), mr(3, 30), blr],
                           [addi(30, 4, 8), mr(31, 30), mr(3, 31), bl(g - 0x200C), mr(3, 30), blr], True),
        # call results and entry values are sites per register (wYA 2026-11-12)
        ('copies of call results in other registers',
         [bl(g - 0x2000), mr(5, 3), mr(6, 4), subf(3, 5, 6), blr],
         [bl(g - 0x2000), mr(6, 3), mr(5, 4), subf(3, 6, 5), blr], True),
        ('copies of call results exchanged',
         [bl(g - 0x2000), mr(5, 3), mr(6, 4), subf(3, 5, 6), blr],
         [bl(g - 0x2000), mr(6, 3), mr(5, 4), subf(3, 5, 6), blr], False),
        ('copy of another call result',
         [bl(g - 0x2000), mr(5, 3), addi(3, 5, 1), blr],
         [bl(g - 0x2000), mr(5, 4), addi(3, 5, 1), blr], False),
        ('copy of the result of another call',
         [bl(g - 0x2000), mr(5, 3), mr(6, 3), addi(3, 5, 1), blr],
         [bl(g - 0x2000), mr(5, 3), mr(6, 3), addi(3, 6, 1), blr], True),
        ('copies of entry values made in the other order',
         [mr(5, 3), mr(6, 4), subf(3, 5, 6), blr],
         [mr(5, 4), mr(6, 3), subf(3, 6, 5), blr], True),
        ('copies of entry values exchanged',
         [mr(5, 3), mr(6, 4), subf(3, 5, 6), blr],
         [mr(5, 4), mr(6, 3), subf(3, 5, 6), blr], False),
        ('copy of another entry value returned', [mr(3, 5), blr], [mr(3, 4), blr], False),
        ('copy into another argument register', [mr(3, 31), bl(g - 0x2004), blr],
                                                [mr(4, 31), bl(g - 0x2004), blr], False),
        ('copy of another register into the argument', [mr(3, 31), bl(g - 0x2004), blr],
                                                       [mr(3, 30), bl(g - 0x2004), blr], False),
        ('argument copies through exchanged temporaries',
         [mr(11, 3), mr(12, 4), mr(3, 12), mr(4, 11), bl(g - 0x2010), blr],
         [mr(12, 3), mr(11, 4), mr(3, 11), mr(4, 12), bl(g - 0x2010), blr], True),
        ('argument copies, values exchanged',
         [mr(11, 3), mr(12, 4), mr(3, 12), mr(4, 11), bl(g - 0x2010), blr],
         [mr(12, 3), mr(11, 4), mr(3, 12), mr(4, 11), bl(g - 0x2010), blr], False),
        ('entry value read after its register was reused',
         [mr(5, 3), addi(3, 4, 1), add(3, 3, 5), blr],
         [mr(5, 3), addi(3, 4, 1), add(3, 3, 3), blr], False),
    ]
    out = []
    for name, tgt, ours, want in cases:
        out.append((name, tgt, ours, want))
    return out


class _Fake:
    def __init__(self, mem, secs=None):
        self.mem = mem
        if secs:
            self.secs = secs

    def words(self, addr, size):
        return [self.mem.get(addr + 4 * k, 0) for k in range(size // 4)]

    def read32(self, addr):
        return self.mem.get(addr)


def extab_synth():
    """Hand-made extab cases (wUM): returns the number of problems."""
    def li(d, i): return 14 << 26 | d << 21 | i
    def mr(d, sr): return 31 << 26 | sr << 21 | d << 16 | sr << 11 | 444 << 1
    def add(d, a, b): return 31 << 26 | d << 21 | a << 16 | b << 11 | 266 << 1
    def bl(at): return 18 << 26 | ((0x1000 - at) & 0x3FFFFFC) | 1
    blr = 0x4E800020
    A = 0x2000
    orig = [bl(A), mr(30, 3), li(31, 1), bl(A + 12), add(3, 30, 31), li(30, 0), li(31, 0), blr]
    swap = [bl(A), mr(31, 3), li(30, 1), bl(A + 12), add(3, 31, 30), li(30, 0), li(31, 0), blr]

    def entry(typ=0x8B, flags=0x40, cond=8, reg=30, pad=b'\xb1\x02'):
        # one range: words 1..3 (the call at word 3), then the action chain
        h = struct.pack('>HHIHH', 0x5008, 0, 4, 3, 0x10) + b'\0\0\0\0'
        if typ & 0x7F == 11:
            return h + struct.pack('>BBHH', typ, flags, cond, reg) + pad + b'\0\0\0\0'
        return h + struct.pack('>BBH', typ, flags, reg) + b'\0\0\0\0'
    prog = Program(_Fake({0x1000: blr, **{A + 4 * k: w for k, w in enumerate(orig)}}),
                   [('g', 0x1000, 4), ('f', A, 4 * len(orig))])
    prog.strict = False
    fn = prog.byname['f']
    cases = [
        # (name, our code, original entry, our entry, must pass)
        ('extab rename, consistent', swap, entry(), entry(reg=31), True),
        ('extab rename, wrong register', swap, entry(), entry(reg=30), False),
        ('extab rename, register of the other object', orig, entry(), entry(reg=31), False),
        ('extab rename, unchanged and consistent', orig, entry(), entry(), True),
        ('extab unchanged but object moved', swap, entry(), entry(), False),
        ('extab rename, flags byte changed', swap, entry(), entry(reg=31, flags=0x60), False),
        ('extab rename, cond operand changed', swap, entry(), entry(reg=31, cond=12), False),
        ('extab rename, padding changed', swap, entry(), entry(reg=31, pad=b'\x06\x6c'), False),
        ('extab rename, action type changed', swap, entry(), entry(typ=0x8A, reg=31), False),
        ('extab rename, register out of range', swap, entry(), entry(reg=0x1f1f), False),
        ('extab rename, DESTROYLOCAL operand', swap, entry(0x82, 0x80), entry(0x82, 0x80, reg=31), False),
        ('extab rename, DELETEPOINTER operand', swap, entry(0x8A, 0x80), entry(0x8A, 0x80, reg=31), True),
    ]
    bad = 0
    for name, ours, eo, eu, want in cases:
        pairs, why = extab_pairs(fn, eo, eu)
        ok, text_ = (False, why) if why else prog.check(fn, ours, pairs)
        print('%s synthetic %s: %s' % ('ok  ' if ok == want else 'FAIL', name, text_))
        if ok != want:
            bad += 1
    return bad


def ret_synth():
    """Hand-made programs for the r4/f1-at-return rule (Program.retuse): returns the number
    of problems. The function under test leaves a temporary in r4 (f1) in the original and in
    r5 (f3) in ours; that is fine exactly when nothing can read r4 (f1) after it returns."""
    def li(d, i): return 14 << 26 | d << 21 | (i & 0xFFFF)
    def mr(d, sr): return 31 << 26 | sr << 21 | d << 16 | sr << 11 | 444 << 1
    def fmr(d, b): return 63 << 26 | d << 21 | b << 11 | 72 << 1
    def mtctr(sr): return 31 << 26 | sr << 21 | 9 << 16 | 467 << 1
    blr, bctrl = 0x4E800020, 0x4E800421
    F, H, G, K = 0x1100, 0x1200, 0x1300, 0x1400

    def bl(at, to, lk=1): return 18 << 26 | ((to - at) & 0x3FFFFFC) | lk
    gpr = ([li(4, 1), li(3, 2), blr], [li(5, 1), li(3, 2), blr])
    fpr = ([fmr(1, 2), li(3, 2), blr], [fmr(3, 2), li(3, 2), blr])
    cases = [
        # (name, (original f, our f), other functions, data words, must pass)
        ('nobody reads r4', gpr, {H: [bl(H, F), li(3, 0), blr]}, [], True),
        ('no caller at all', gpr, {}, [], True),
        ('caller reads r4', gpr, {H: [bl(H, F), mr(3, 4), blr]}, [], False),
        ('later callee reads r4', gpr, {H: [bl(H, F), bl(H + 4, G), blr], G: [mr(3, 4), blr]}, [], False),
        ('later callee does not read r4', gpr, {H: [bl(H, F), bl(H + 4, G), blr], G: [li(3, 0), blr]}, [], True),
        ('caller hands r4 on to its caller', gpr,
         {H: [bl(H, F), blr], K: [bl(K, H), mr(3, 4), blr]}, [], False),
        ('tail call, the caller of the caller reads r4', gpr,
         {H: [bl(H, F, 0)], K: [bl(K, H), mr(3, 4), blr]}, [], False),
        ('indirect call site reads r4, address of f in data', gpr,
         {K: [mtctr(5), bctrl, mr(3, 4), blr]}, [F], False),
        ('indirect call site reads r4, address of f not taken', gpr,
         {K: [mtctr(5), bctrl, mr(3, 4), blr]}, [], True),
        ('indirect call site reads r4, address of f built by lis/addi', gpr,
         {K: [mtctr(5), bctrl, mr(3, 4), blr], G: [15 << 26 | 5 << 21, 14 << 26 | 5 << 21 | 5 << 16 | F, blr]}, [], False),
        ('indirect call site reads r4, address of f built by lis/ori', gpr,
         {K: [mtctr(5), bctrl, mr(3, 4), blr], G: [15 << 26 | 5 << 21, 24 << 26 | 5 << 21 | 5 << 16 | F, blr]}, [], False),
        ('indirect call after f (the callee may read r4)', gpr, {H: [bl(H, F), mtctr(5), bctrl, blr]}, [], False),
        ('caller that is not analysed', gpr, {H: [0x44000002, bl(H + 4, F), blr]}, [], False),
        ('nobody reads f1', fpr, {H: [bl(H, F), li(3, 0), blr]}, [], True),
        ('caller reads f1', fpr, {H: [bl(H, F), fmr(2, 1), blr]}, [], False),
        ('later callee reads f1', fpr, {H: [bl(H, F), bl(H + 4, G), blr], G: [fmr(2, 1), blr]}, [], False),
    ]
    bad = 0
    for name, (tgt, ours), others, data, want in cases:
        mem = {}
        syms = [('f', F, 4 * len(tgt))]
        for k, w in enumerate(tgt):
            mem[F + 4 * k] = w
        for a, ws in others.items():
            syms.append(('x%x' % a, a, 4 * len(ws)))
            for k, w in enumerate(ws):
                mem[a + 4 * k] = w
        for k, w in enumerate(data):
            mem[0x3000 + 4 * k] = w
        prog = Program(_Fake(mem, [(0, 0x1000, 0x1000, True), (0, 0x3000, 0x100, False)]), sorted(syms, key=lambda s: s[1]))
        prog.strict = False
        ok, text_ = prog.check(prog.byname['f'], ours)
        print('%s synthetic return %s: %s' % ('ok  ' if ok == want else 'FAIL', name, text_))
        if ok != want:
            bad += 1
    return bad


def synth_run():
    """Run the hand-made cases; returns the number of problems."""
    bad = extab_synth() + ret_synth()
    for name, tgt, ours, want in synth_tests():
        mem = {0x1000: 0x4E800020}
        for k, w in enumerate(tgt):
            mem[0x2000 + 4 * k] = w
        prog = Program(_Fake(mem), [('g', 0x1000, 4), ('f', 0x2000, 4 * len(tgt))])
        prog.strict = False
        ok, text_ = prog.check(prog.byname['f'], ours)
        print('%s synthetic %s: %s' % ('ok  ' if ok == want else 'FAIL', name, text_))
        if ok != want:
            bad += 1
    # unit test of the stale marking: a copy made before the source's site ran again is stale
    F = [0] * 96
    W = 100
    Program._fwdstep(F, [(5, 1 << 1, True)], None, 0, W)
    Program._fwdstep(F, [(6, 1 << 9, True)], (6, 5), 1, W)
    fresh = F[6] == F[5] == 2 and not F[6] >> W
    Program._fwdstep(F, [(5, 1 << 1, True)], None, 0, W)
    stale = F[5] == 2 and F[6] == 2 | 2 << W
    print('%s synthetic stale marking' % ('ok  ' if fresh and stale else 'FAIL'))
    # the same for a call result: instruction 0 is a call that leaves a value in r3
    F = [1 << (2 * W + 8 + r) for r in range(96)]
    own, stb = 1 << (2 * W + 8 + 96 + 3), 1 << (2 * W + 8 + 96 * ((W - 16) // 8 + 1))
    Program._fwdstep(F, [(3, 1 << 8, True)], None, 0, W)
    Program._fwdstep(F, [(6, 1 << 9, True)], (6, 3), 1, W)
    fresh2 = F[6] == F[3] == own
    Program._fwdstep(F, [(3, 1 << 8, True)], None, 0, W)
    stale2 = F[3] == own and F[6] == own | stb
    print('%s synthetic stale marking of a call result' % ('ok  ' if fresh2 and stale2 else 'FAIL'))
    return bad + (0 if fresh and stale else 1) + (0 if fresh2 and stale2 else 1)


def _benign_copy_alias(words, i, old, new):
    """Independent check used only by the self-test: True if `new` differs from `old`
    in exactly one GPR source field (rA or rB), and the register it now names held a
    plain copy (`or rX,rY,rY`, i.e. mr rX,rY) of the replaced register, made earlier in
    straight-line code (no branch targets/branches in between, only bl calls) with
    neither register redefined since; callee-saved registers (r14-r31) survive bl."""
    diff = old ^ new
    op0 = old >> 26
    logical = op0 == 31 and (old >> 1) & 0x3ff in (28, 60, 124, 284, 316, 412, 444, 476)
    srcs = (21, 11) if logical else (16, 11)  # source-register fields (rS/rB vs rA/rB)
    for sh in srcs:
        if diff == (0x1f << sh) & diff and diff >> sh & 0x1f:
            break
    else:
        return False
    if diff & ~(0x1f << sh):
        return False
    a, b = (old >> sh) & 0x1f, (new >> sh) & 0x1f   # replaced reg a by b
    if a < 14 or b < 14:
        return False                          # only callee-saved regs survive calls
    for j in range(i - 1, -1, -1):
        w = words[j]
        op = w >> 26
        if op in (16, 18) and not (op == 18 and w & 1):   # bc / b (not bl): control flow
            return False
        if op == 19:                          # bclr/bcctr etc
            return False
        if op == 31 and (w >> 1) & 0x3ff == 444 and (w >> 16) & 0x1f == b \
                and (w >> 21) & 0x1f == a and (w >> 11) & 0x1f == a:
            return True                       # mr b,a found, nothing redefined since
        # which GPR (if any) does this instruction write? be conservative: unknown -> stop
        if op in (7, 8, 12, 13, 14, 15, 32, 34, 40, 42):          # D-form: rD in bits 21-25
            dst = {(w >> 21) & 0x1f}
        elif op in (33, 35, 41, 43):                              # update loads: rD and rA
            dst = {(w >> 21) & 0x1f, (w >> 16) & 0x1f}
        elif op in (20, 21, 23, 24, 25, 26, 27, 28, 29):          # rlw*, ori/xori/andi: rA
            dst = {(w >> 16) & 0x1f}
        elif op in (36, 37, 38, 39, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 10, 11):
            dst = {(w >> 16) & 0x1f} if op in (37, 39, 45, 47, 49, 51, 53, 55) else set()
        elif op == 18:                                            # bl: clobbers volatiles only
            dst = set()
        elif op == 31:
            xo = (w >> 1) & 0x3ff
            if xo in (28, 60, 124, 284, 316, 412, 444, 476, 24, 536, 792, 824, 26, 922, 954):
                dst = {(w >> 16) & 0x1f}                          # logical/shift: rA
            elif xo in (0, 32, 151, 183, 215, 247, 407, 439, 663, 695, 727, 759, 918, 662, 534, 790):
                dst = {(w >> 16) & 0x1f} if xo in (183, 247, 439, 695, 759) else set()  # cmp/stores
            else:
                dst = {(w >> 21) & 0x1f}                          # arithmetic, loads: rD
        else:
            return False
        if dst & {a, b}:
            return False
    return False


# ---- self-test of rule f) -------------------------------------------------

# schedule-only pairs found on 2026-11-12 (objects of NonMatching or linked units); must keep passing
SCHED_SELFTEST = ['fn_80207510', 'fn_80272028', 'fn_801C9F7C', 'fn_8016AB80', 'fn_80264E0C', 'fn_8022F544']


def sched_synth():
    """Hand-made cases for rule f): returns the number of problems."""
    def li(d, i): return 14 << 26 | d << 21 | (i & 0xFFFF)
    def addi(d, a, i): return 14 << 26 | d << 21 | a << 16 | (i & 0xFFFF)
    def addic(d, a, i): return 12 << 26 | d << 21 | a << 16 | (i & 0xFFFF)
    def mr(d, sr): return 31 << 26 | sr << 21 | d << 16 | sr << 11 | 444 << 1
    def add(d, a, b): return 31 << 26 | d << 21 | a << 16 | b << 11 | 266 << 1
    def addze(d, a): return 31 << 26 | d << 21 | a << 16 | 202 << 1
    def subf(d, a, b): return 31 << 26 | d << 21 | a << 16 | b << 11 | 40 << 1
    def srawi(a, sr, n): return 31 << 26 | sr << 21 | a << 16 | n << 11 | 824 << 1
    def lwz(d, off, a): return 32 << 26 | d << 21 | a << 16 | (off & 0xFFFF)
    def lhz(d, off, a): return 40 << 26 | d << 21 | a << 16 | (off & 0xFFFF)
    def stw(sr, off, a): return 36 << 26 | sr << 21 | a << 16 | (off & 0xFFFF)
    def lwzx(d, a, b): return 31 << 26 | d << 21 | a << 16 | b << 11 | 23 << 1
    def fadds(d, a, b): return 59 << 26 | d << 21 | a << 16 | b << 11 | 21 << 1
    def fmr(d, b): return 63 << 26 | d << 21 | b << 11 | 72 << 1
    def cmpwi(a, i): return 11 << 26 | a << 16 | (i & 0xFFFF)
    def cmpw(cr, a, b): return 31 << 26 | cr << 23 | a << 16 | b << 11
    def bc(bo, bi, off): return 16 << 26 | bo << 21 | bi << 16 | (off & 0xFFFC)
    def bl(at): return 18 << 26 | ((0x1000 - at) & 0x3FFFFFC) | 1
    def mtctr(sr): return 31 << 26 | sr << 21 | 9 << 16 | 467 << 1
    def lis(d, i): return 15 << 26 | d << 21 | (i & 0xFFFF)
    blr = 0x4E800020
    A = 0x2000
    cases = [
        # (name, original, ours, must pass)
        ('independent li swapped', [li(4, 1), li(5, 2), add(3, 4, 5), blr],
                                   [li(5, 2), li(4, 1), add(3, 4, 5), blr], True),
        ('swap plus rename', [li(5, 1), li(6, 2), add(3, 5, 6), blr],
                             [li(7, 2), li(8, 1), add(3, 8, 7), blr], True),
        ('swap plus rename, values exchanged', [li(5, 1), li(6, 2), subf(3, 5, 6), blr],
                                               [li(7, 2), li(8, 1), subf(3, 7, 8), blr], False),
        ('RAW pair swapped', [addi(4, 3, 1), addi(5, 4, 2), add(3, 4, 5), blr],
                             [addi(5, 4, 2), addi(4, 3, 1), add(3, 4, 5), blr], False),
        ('WAR pair swapped', [addi(5, 4, 2), li(4, 1), add(3, 4, 5), blr],
                             [li(4, 1), addi(5, 4, 2), add(3, 4, 5), blr], False),
        ('WAW pair swapped', [li(4, 1), cmpwi(3, 0), li(4, 2), add(3, 4, 4), blr],
                             [li(4, 2), cmpwi(3, 0), li(4, 1), add(3, 4, 4), blr], False),
        ('load above aliasing store', [stw(4, 0, 5), lwz(6, 0, 7), add(3, 6, 6), blr],
                                      [lwz(6, 0, 7), stw(4, 0, 5), add(3, 6, 6), blr], False),
        ('store above possibly aliasing load', [lwz(6, 0, 7), stw(4, 0, 5), add(3, 6, 6), blr],
                                               [stw(4, 0, 5), lwz(6, 0, 7), add(3, 6, 6), blr], False),
        ('two stores, different bases', [stw(4, 0, 5), stw(6, 0, 7), li(3, 0), blr],
                                        [stw(6, 0, 7), stw(4, 0, 5), li(3, 0), blr], False),
        ('load / store, distinct stack slots', [stw(4, 8, 1), lwz(6, 12, 1), mr(3, 6), blr],
                                               [lwz(6, 12, 1), stw(4, 8, 1), mr(3, 6), blr], True),
        ('load / store, overlapping stack slots', [stw(4, 8, 1), lhz(6, 10, 1), mr(3, 6), blr],
                                                  [lhz(6, 10, 1), stw(4, 8, 1), mr(3, 6), blr], False),
        ('load / store, same base, disjoint', [stw(4, 8, 5), lwz(6, 12, 5), mr(3, 6), blr],
                                              [lwz(6, 12, 5), stw(4, 8, 5), mr(3, 6), blr], True),
        ('indexed load above store', [stw(4, 8, 5), lwzx(6, 5, 7), mr(3, 6), blr],
                                     [lwzx(6, 5, 7), stw(4, 8, 5), mr(3, 6), blr], False),
        ('two loads swapped', [lwz(4, 0, 5), lwz(6, 0, 7), add(3, 4, 6), blr],
                              [lwz(6, 0, 7), lwz(4, 0, 5), add(3, 4, 6), blr], True),
        ('two loads swapped, hardware address in the function',
         [lis(5, 0xCC00), lwz(4, 0, 5), lwz(6, 0, 7), add(3, 4, 6), blr],
         [lis(5, 0xCC00), lwz(6, 0, 7), lwz(4, 0, 5), add(3, 4, 6), blr], False),
        ('across a call', [mr(31, 3), bl(A + 4), li(30, 2), add(3, 31, 30), blr],
                          [li(30, 2), bl(A + 4), mr(31, 3), add(3, 31, 30), blr], False),
        ('call moved', [li(30, 2), bl(A + 4), li(31, 3), add(3, 31, 30), blr],
                       [li(30, 2), li(31, 3), bl(A + 8), add(3, 31, 30), blr], False),
        ('across a block boundary', [cmpwi(3, 0), li(4, 1), bc(12, 2, 8), li(5, 2), li(6, 3), add(3, 4, 6), blr],
                                    [cmpwi(3, 0), li(4, 1), bc(12, 2, 8), li(6, 3), li(5, 2), add(3, 4, 6), blr], False),
        ('across a branch', [cmpwi(3, 0), li(4, 1), bc(12, 2, 8), li(5, 2), add(3, 4, 5), blr],
                            [cmpwi(3, 0), bc(12, 2, 12), li(4, 1), li(5, 2), add(3, 4, 5), blr], False),
        ('compare below its independent neighbour', [cmpwi(3, 0), li(4, 1), bc(12, 2, 8), li(4, 2), mr(3, 4), blr],
                                                    [li(4, 1), cmpwi(3, 0), bc(12, 2, 8), li(4, 2), mr(3, 4), blr], True),
        ('operand changed', [li(4, 1), li(5, 2), add(3, 4, 5), blr],
                            [li(5, 2), li(4, 1), add(3, 4, 4), blr], False),
        ('immediate changed', [li(4, 1), li(5, 2), add(3, 4, 5), blr],
                              [li(5, 3), li(4, 1), add(3, 4, 5), blr], False),
        ('instruction duplicated', [li(4, 1), li(5, 2), add(3, 4, 5), blr],
                                   [li(5, 2), li(5, 2), add(3, 4, 5), blr], False),
        ('carry read moved above its writer', [addic(4, 3, 1), addze(5, 6), add(3, 4, 5), blr],
                                              [addze(5, 6), addic(4, 3, 1), add(3, 4, 5), blr], False),
        ('last carry writer changed', [srawi(4, 3, 1), srawi(5, 3, 2), add(3, 4, 5), blr],
                                      [srawi(5, 3, 2), srawi(4, 3, 1), add(3, 4, 5), blr], False),
        ('dead carry writers swapped', [srawi(4, 3, 1), srawi(5, 3, 2), addic(6, 3, 3), add(3, 4, 5), blr],
                                       [srawi(5, 3, 2), srawi(4, 3, 1), addic(6, 3, 3), add(3, 4, 5), blr], True),
        ('last FPSCR writer changed', [fadds(3, 1, 2), fadds(4, 2, 2), fadds(1, 3, 4), fmr(2, 1), fadds(5, 1, 1), blr],
                                      [fadds(3, 1, 2), fadds(4, 2, 2), fadds(5, 1, 1), fmr(2, 1), fadds(1, 3, 4), blr], False),
        ('float adds swapped, last one kept', [fadds(3, 1, 2), fadds(4, 2, 2), fadds(1, 3, 4), blr],
                                              [fadds(4, 2, 2), fadds(3, 1, 2), fadds(1, 3, 4), blr], True),
        ('writes of an argument register before a call', [li(3, 1), li(3, 2), bl(A + 8), li(3, 0), blr],
                                                         [li(3, 2), li(3, 1), bl(A + 8), li(3, 0), blr], False),
        ('dead write moved below the live one', [li(5, 1), li(5, 2), add(3, 5, 5), blr],
                                                [li(5, 2), li(5, 1), add(3, 5, 5), blr], False),
        ('across mtctr', [li(4, 1), mtctr(3), li(5, 2), add(3, 4, 5), blr],
                         [li(5, 2), mtctr(3), li(4, 1), add(3, 4, 5), blr], False),
        ('CR field renamed and compare moved', [cmpw(0, 3, 4), li(5, 1), bc(12, 2, 8), li(5, 2), mr(3, 5), blr],
                                               [li(5, 1), cmpw(1, 3, 4), bc(12, 6, 8), li(5, 2), mr(3, 5), blr], True),
    ]
    # memory rules of SchedCtx: frame of 16 bytes, "sections" 0x4000-0x5000, r13 = 0x4800
    stwu, pop = 0x9421FFF0, 0x38210010
    G = ('global',)
    for name, a, b, tail, want, relax in [
        ('frame store / SDA load', stw(4, 8, 1), lwz(5, -0x100, 13), [], True, G),
        ('frame load / SDA store', lwz(5, 8, 1), stw(4, -0x100, 13), [], True, G),
        ('frame store / SDA load, rule off', stw(4, 8, 1), lwz(5, -0x100, 13), [], False, ()),
        ('store above the frame / SDA load', stw(4, 20, 1), lwz(5, -0x100, 13), [], False, G),
        ('store across the frame end / SDA load', stw(4, 14, 1), lwz(5, -0x100, 13), [], False, G),
        ('store below the frame / SDA load', stw(4, -4, 1), lwz(5, -0x100, 13), [], False, G),
        ('frame store / r13 load outside the sections', stw(4, 8, 1), lwz(5, 0x7000, 13), [], False, G),
        ('frame store / pointer load, global rule only', stw(4, 8, 1), lwz(5, 0, 6), [], False, G),
    ]:
        pre = [stwu]
        post = [add(3, 5, 5), pop, blr]
        cases.append(('memory: ' + name, pre + [a, b] + post, pre + [b, a] + post, want, relax))
    cases += [
        ('memory: frame store / lis-based global load',
         [stwu, lis(6, 0), stw(4, 8, 1), lwz(5, 0x4100, 6), add(3, 5, 5), pop, blr],
         [stwu, lis(6, 0), lwz(5, 0x4100, 6), stw(4, 8, 1), add(3, 5, 5), pop, blr], True, G),
        ('memory: frame store / lis+addi-based global load',
         [stwu, lis(6, 0), addi(6, 6, 0x4100), stw(4, 8, 1), lwz(5, 4, 6), add(3, 5, 5), pop, blr],
         [stwu, lis(6, 0), addi(6, 6, 0x4100), lwz(5, 4, 6), stw(4, 8, 1), add(3, 5, 5), pop, blr], True, G),
        ('memory: frame store / lis-based load outside the sections',
         [stwu, lis(6, 1), stw(4, 8, 1), lwz(5, 0x4100, 6), add(3, 5, 5), pop, blr],
         [stwu, lis(6, 1), lwz(5, 0x4100, 6), stw(4, 8, 1), add(3, 5, 5), pop, blr], False, G),
        ('memory: lis-based register changed before the load',
         [stwu, lis(6, 0), add(6, 6, 7), stw(4, 8, 1), lwz(5, 0x4100, 6), add(3, 5, 5), pop, blr],
         [stwu, lis(6, 0), add(6, 6, 7), lwz(5, 0x4100, 6), stw(4, 8, 1), add(3, 5, 5), pop, blr], False, G),
        ('memory: r1 store / SDA load without a frame',
         [stw(4, 8, 1), lwz(5, -0x100, 13), add(3, 5, 5), blr],
         [lwz(5, -0x100, 13), stw(4, 8, 1), add(3, 5, 5), blr], False, G),
        ('memory: r1 store / SDA load after the frame was released',
         [stwu, pop, stw(4, 8, 1), lwz(5, -0x100, 13), add(3, 5, 5), blr],
         [stwu, pop, lwz(5, -0x100, 13), stw(4, 8, 1), add(3, 5, 5), blr], False, G),
        ('memory: r1 changed by something else than the prologue',
         [stwu, addi(1, 1, -8), stw(4, 8, 1), lwz(5, -0x100, 13), add(3, 5, 5), addi(1, 1, 8), pop, blr],
         [stwu, addi(1, 1, -8), lwz(5, -0x100, 13), stw(4, 8, 1), add(3, 5, 5), addi(1, 1, 8), pop, blr], False, G),
        ('memory: r13 written in the function',
         [stwu, stw(4, 8, 1), lwz(5, -0x100, 13), add(3, 5, 5), addi(13, 13, 0), pop, blr],
         [stwu, lwz(5, -0x100, 13), stw(4, 8, 1), add(3, 5, 5), addi(13, 13, 0), pop, blr], False, G),
    ]
    stmw, lmw = 47 << 26 | 30 << 21 | 1 << 16 | 0x58, 46 << 26 | 30 << 21 | 1 << 16 | 0x58
    big, unbig = 0x9421FFA0, 0x38210060
    cases += [
        # second form: other registers AND another order
        ('reuse of one register where the original has two',
         [li(7, 1), li(8, 2), stw(7, 0, 6), stw(8, 4, 6), li(3, 0), blr],
         [li(7, 1), stw(7, 0, 6), li(7, 2), stw(7, 4, 6), li(3, 0), blr], True),
        ('two registers where the original reuses one',
         [li(7, 1), stw(7, 0, 6), li(7, 2), stw(7, 4, 6), li(3, 0), blr],
         [li(7, 1), li(8, 2), stw(7, 0, 6), stw(8, 4, 6), li(3, 0), blr], True),
        ('reuse of one register, values exchanged',
         [li(7, 1), li(8, 2), stw(7, 0, 6), stw(8, 4, 6), li(3, 0), blr],
         [li(7, 2), stw(7, 0, 6), li(7, 1), stw(7, 4, 6), li(3, 0), blr], False),
        ('reuse of one register, read after the second write',
         [li(7, 1), li(8, 2), stw(7, 0, 6), stw(8, 4, 6), li(3, 0), blr],
         [li(7, 1), li(7, 2), stw(7, 0, 6), stw(7, 4, 6), li(3, 0), blr], False),
        ('reuse of one register, aliasing stores in another order',
         [li(7, 1), li(8, 2), stw(7, 0, 6), stw(8, 0, 9), li(3, 0), blr],
         [li(7, 2), stw(7, 0, 9), li(7, 1), stw(7, 0, 6), li(3, 0), blr], False),
        ('reuse of one register across a call',
         [li(7, 1), li(8, 2), stw(7, 0, 31), bl(A + 12), stw(8, 4, 31), li(3, 0), blr],
         [li(7, 1), stw(7, 0, 31), li(7, 2), bl(A + 12), stw(7, 4, 31), li(3, 0), blr], False),
        ('reuse of one register, result register differs',
         [li(7, 1), li(8, 2), stw(7, 0, 6), stw(8, 4, 6), mr(3, 8), blr],
         [li(7, 1), stw(7, 0, 6), li(7, 2), stw(7, 4, 6), mr(3, 8), blr], False),
        ('reuse of one register, loop carries the other value',
         [li(7, 1), li(8, 2), stw(7, 0, 6), stw(8, 4, 6), cmpwi(3, 0), addi(3, 8, 0), bc(4, 2, -24), blr],
         [li(7, 1), stw(7, 0, 6), li(7, 2), stw(7, 4, 6), cmpwi(3, 0), addi(3, 8, 0), bc(4, 2, -24), blr], False),
        # lmw / stmw are a load / store, not a barrier
        ('stack parameter loaded above stmw',
         [big, stmw, lwz(5, 0x68, 1), mr(3, 5), lmw, unbig, blr],
         [big, lwz(5, 0x68, 1), stmw, mr(3, 5), lmw, unbig, blr], True),
        ('load from the stmw area above stmw',
         [big, stmw, lwz(5, 0x5c, 1), mr(3, 5), lmw, unbig, blr],
         [big, lwz(5, 0x5c, 1), stmw, mr(3, 5), lmw, unbig, blr], False),
        ('write of a saved register above stmw',
         [big, stmw, li(31, 0), mr(3, 31), lmw, unbig, blr],
         [big, li(31, 0), stmw, mr(3, 31), lmw, unbig, blr], False),
        ('read of a saved register below lmw',
         [big, stmw, li(31, 0), mr(3, 31), lmw, unbig, blr],
         [big, stmw, li(31, 0), lmw, mr(3, 31), unbig, blr], False),
        ('load of a stack parameter below lmw',
         [big, stmw, li(31, 0), lwz(3, 0x68, 1), lmw, unbig, blr],
         [big, stmw, li(31, 0), lmw, lwz(3, 0x68, 1), unbig, blr], True),
    ]
    GP_ = ('global', 'pointer')
    for name, pre, a, b, want, relax in [
        ('frame store / pointer load', [], stw(4, 8, 1), lwz(5, 0, 6), True, GP_),
        ('frame load / pointer store', [], lwz(5, 8, 1), stw(4, 0, 6), True, GP_),
        ('frame store / indexed load', [], stw(4, 8, 1), lwzx(5, 6, 7), True, GP_),
        ('frame store / pointer load, rule off', [], stw(4, 8, 1), lwz(5, 0, 6), False, G),
        ('store above the frame / pointer load', [], stw(4, 20, 1), lwz(5, 0, 6), False, GP_),
        ('store across the frame end / pointer load', [], stw(4, 14, 1), lwz(5, 0, 6), False, GP_),
        ('frame address taken (addi r3,r1,8), pointer load above the stack store',
         [addi(3, 1, 8)], stw(4, 8, 1), lwz(5, 0, 3), False, GP_),
        ('frame address taken, another pointer', [addi(7, 1, 8)], stw(4, 8, 1), lwz(5, 0, 6), False, GP_),
        ('frame address taken, SDA load still free', [addi(7, 1, 8)], stw(4, 8, 1), lwz(5, -0x100, 13), True, GP_),
        ('r1 copied (mr r7,r1)', [mr(7, 1)], stw(4, 8, 1), lwz(5, 0, 6), False, GP_),
        ('r1 added (add r7,r1,r6)', [add(7, 1, 6)], stw(4, 8, 1), lwz(5, 0, 6), False, GP_),
        ('r1 stored (stw r1,0(r6))', [stw(1, 0, 6)], stw(4, 8, 1), lwz(5, 0, 7), False, GP_),
        ('r1 as index (lwzx r7,r1,r6)', [lwzx(7, 1, 6)], stw(4, 8, 1), lwz(5, 0, 6), False, GP_),
        ('two pointers, no frame access', [], stw(4, 8, 6), lwz(5, 0, 7), False, GP_),
    ]:
        pre = [stwu] + pre
        post = [add(3, 5, 5), pop, blr]
        cases.append(('memory: ' + name, pre + [a, b] + post, pre + [b, a] + post, want, relax))
    cases += [
        ('memory: r1 store / pointer load without a frame',
         [stw(4, 8, 1), lwz(5, 0, 6), add(3, 5, 5), blr],
         [lwz(5, 0, 6), stw(4, 8, 1), add(3, 5, 5), blr], False, GP_),
        ('memory: frame address taken in another block',
         [stwu, cmpwi(3, 0), bc(12, 2, 8), addi(7, 1, 8), stw(4, 8, 1), lwz(5, 0, 6), add(3, 5, 5), pop, blr],
         [stwu, cmpwi(3, 0), bc(12, 2, 8), addi(7, 1, 8), lwz(5, 0, 6), stw(4, 8, 1), add(3, 5, 5), pop, blr], False, GP_),
    ]
    bad = 0
    for case in cases:
        name, tgt, ours, want = case[:4]
        relax = case[4] if len(case) > 4 else None
        mem = {0x1000: blr}
        for k, w in enumerate(tgt):
            mem[A + 4 * k] = w
        prog = Program(_Fake(mem), [('g', 0x1000, 4), ('f', A, 4 * len(tgt))])
        prog.strict = False
        prog.dol.secs = [(0, 0x4000, 0x1000, False)]
        prog.sda = {13: 0x4800, 2: 0x4400}
        ok, text_ = check_sched(prog, prog.byname['f'], ours, None, None, relax)
        if ok and want and not text_.startswith('schedequiv'):
            ok = False
        print('%s synthetic sched %s: %s' % ('ok  ' if ok == want else 'FAIL', name, text_))
        if ok != want:
            bad += 1
    return bad


_ST_PURE31 = {266, 40, 444, 28, 316, 235, 24, 536, 954, 922, 26, 124, 476}


def _st_rw(w):
    """Independent of sched_info: (reads, writes, class) of one instruction for the mutation
    tests; class 'pure' = no hidden state and no memory, 'load', 'store', or None."""
    d = dec(w)
    rd, wr = d[1], d[2]
    for base, sh, wd, role in d[0]:
        b = 1 << (base + ((w >> sh) & ((1 << wd) - 1)))
        if role & (RD | SAVE):
            rd |= b
        if role & WR:
            wr |= b
    op = w >> 26
    cls = None
    if d[4] == '' and not d[1] and not d[2]:
        if op in (14, 15, 24, 25, 26, 27, 21) and not (op == 21 and w & 1):
            cls = 'pure'
        elif op == 31 and not w & 1 and (w >> 1) & 1023 in _ST_PURE31:
            cls = 'pure'
        elif op == 63 and not w & 1 and (w >> 1) & 1023 in (72, 40):
            cls = 'pure'
        elif op in (32, 34, 40, 42, 48, 50):
            cls = 'load'
        elif op in (36, 38, 44, 52, 54):
            cls = 'store'
    return rd, wr, cls


def _st_frame(words):
    """Independent of SchedCtx, for the mutation tests: (index of the only stwu r1,-N(r1),
    index of the first later write to r1, N, frame address may escape, registers written by
    a lis or reached by any write to r2/r13); N = 0 when the frame is not that simple."""
    wr1 = [i for i, w in enumerate(words) if _st_rw(w)[1] & 2]
    size = lo = 0
    hi = len(words)
    if wr1 and words[wr1[0]] >> 16 == 0x9421 and words[wr1[0]] & 0x8000:
        lo = wr1[0]
        size = 0x10000 - (words[lo] & 0xFFFF)
        if len(wr1) > 1:
            hi = wr1[1]
        if any(words[i] != 0x38210000 | size for i in wr1[1:]):
            size = 0
    esc = False
    lisreg = set()
    for w in words:
        op = w >> 26
        rd, wr, _c = _st_rw(w)
        if op == 15:
            lisreg.add((w >> 21) & 31)
        for r in (2, 13):
            if wr >> r & 1:
                lisreg.add(r)
        if (rd | wr) & 2:
            base_only = op in MEMSZ or op in (46, 47)
            if w >> 16 in (0x9421, 0x3821):
                continue
            if not base_only or (w >> 21) & 31 == 1 and op not in (48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 60, 61):
                esc = True
    for _pass in range(3):                    # addi from a lis register: may be a global address too
        for w in words:
            if w >> 26 == 14 and (w >> 16) & 31 in lisreg:
                lisreg.add((w >> 21) & 31)
    return lo, hi, size, esc, lisreg


def sched_mutations(fn, words, sda=None, glob=None):
    """Reorderings of `words` (compared against fn): yields (kind, mutated words, must pass)."""
    n = fn.n
    sda = sda or {}
    oracle = None
    seen = set()
    todo = [0]
    while todo:
        i = todo.pop()
        if i not in seen:
            seen.add(i)
            todo.extend(fn.succ[i])
    hw = any(w >> 26 == 15 and (w & 0xFFFF) in (0xCC00, 0xCD00, 0xE000) for w in words)
    info = [_st_rw(w) for w in words]

    def swapped(a, b):
        m = list(words)
        m[a], m[b] = m[b], m[a]
        return m

    def indep(a, b):
        (r1, w1, _c1), (r2, w2, _c2) = info[a], info[b]
        return not (w1 & (r2 | w2)) and not (w2 & r1)

    for i in range(n - 1):
        if i not in seen or words[i] == words[i + 1]:
            continue
        (r1, w1, c1), (r2, w2, c2) = info[i], info[i + 1]
        k1, k2 = dec(words[i])[4], dec(words[i + 1])[4]
        if i + 1 in fn.leader:
            if k1 == '' and k2 == '' and c1 and c2 and indep(i, i + 1):
                yield 'sched boundary', swapped(i, i + 1), False
            continue
        if k1 == '' and k2 == '' and w1 & r2 & ~(FIXED & ~1):
            yield 'sched RAW', swapped(i, i + 1), False
        elif c1 and c2 and indep(i, i + 1):
            if c1 == 'pure' and c2 == 'pure':
                yield 'sched independent', swapped(i, i + 1), True
            elif c1 == c2 == 'load':
                if not hw:
                    yield 'sched load/load', swapped(i, i + 1), True
            elif 'pure' not in (c1, c2):
                a, b = words[i], words[i + 1]
                A1, A2 = (a >> 16) & 31, (b >> 16) & 31
                sz = lambda x: {32: 4, 34: 1, 36: 4, 38: 1, 40: 2, 42: 2, 44: 2, 48: 4, 50: 8, 52: 4, 54: 8}[x >> 26]
                o1, o2 = sext(a & 0xFFFF, 16), sext(b & 0xFFFF, 16)
                if A1 == A2 and A1:
                    if o1 + sz(a) <= o2 or o2 + sz(b) <= o1:
                        yield 'sched disjoint memory', swapped(i, i + 1), True
                    else:
                        yield 'sched aliasing memory', swapped(i, i + 1), False
                elif 1 not in (A1, A2):
                    yield 'sched aliasing memory', swapped(i, i + 1), False
                else:                 # an r1 slot against another base: the rules of SchedCtx
                    x, y = (a, b) if A1 == 1 else (b, a)
                    ox, B = sext(x & 0xFFFF, 16), (y >> 16) & 31
                    if oracle is None:
                        oracle = _st_frame(words)
                    lo, hi, size, esc, lisreg = oracle
                    if esc and B not in (2, 13) and B not in lisreg:
                        yield 'sched escaped frame/pointer', swapped(i, i + 1), False
                    elif size and lo < i and i + 1 < hi and 0 <= ox and ox + sz(x) <= size and \
                            B in sda and B not in lisreg and glob((sda[B] + sext(y & 0xFFFF, 16)) & 0xFFFFFFFF):
                        yield 'sched frame/global', swapped(i, i + 1), True
                    elif size and lo < i and i + 1 < hi and 0 <= ox and ox + sz(x) <= size and \
                            not esc and B not in (2, 13) and B not in lisreg:
                        yield 'sched frame/pointer', swapped(i, i + 1), 'pointer' in SCHED_RELAX
        if k2 in ('bl', 'icall') and i + 2 < n and i + 2 not in fn.leader and k1 == '' and \
                dec(words[i + 2])[4] == '' and words[i] != words[i + 2]:
            yield 'sched across call', swapped(i, i + 2), False
            yield 'sched call moved', swapped(i, i + 1), False


def sched_selftest(args, P, prog, units):
    """Self-test of rule f): returns the number of problems."""
    bad = sched_synth()
    names = list(dict.fromkeys(SCHED_SELFTEST + load_allow(P['sallow'])))
    real = []
    for name in names:                            # (a) real schedule-only pairs
        fn = prog.byname.get(name)
        unit = next((u for u, s, e in units if fn and s <= fn.addr < e), None)
        try:
            mine = Obj(os.path.join(P['build'], 'src', unit + '.o'))
            tgt = Obj(os.path.join(P['build'], 'obj', unit + '.o'))
        except (OSError, TypeError) as e:
            print('skip %s: no objects (%s)' % (name, e))
            continue
        ok, text_ = list_one(prog, name, mine, tgt)
        print('%s %s: %s' % ('PASS' if ok else 'FAIL', name, text_))
        if not ok:
            bad += 1
        elif text_.startswith('schedequiv'):
            raw, rel = obj_rel(prog, name, mine, tgt)
            real.append((fn, raw, rel))
        elif name in SCHED_SELFTEST:
            print('note %s: no longer differs by instruction order' % name)
    print('selftest: %d schedule-equivalent function(s) pass' % len(real))
    if len(real) < 3:
        bad += 1
        print('FAIL selftest: fewer than 3 real schedule-only pairs')
    tot, good = {}, {}

    def run(kind, fn, mut, want, rel=None):
        nonlocal bad
        ok, text_ = check_sched(prog, fn, mut, None, rel)
        tot[kind] = tot.get(kind, 0) + 1
        if ok == want:
            good[kind] = good.get(kind, 0) + 1
        else:
            bad += 1
            print('FAIL selftest: %s %s in %s: %s' % (kind, 'accepted' if ok else 'rejected', fn.name, text_))

    # (b) corrupted copies of the real pairs: an operand, an immediate, a dependent pair
    for fn, raw, rel in real:
        urel = rel[1]
        cnt = {}
        for i in range(fn.n):
            if i in urel or dec(raw[i]) is None:
                continue
            w = raw[i]
            ops = dec(w)[0]
            for k, (_b, sh, wd, role) in enumerate(ops):
                if role & RD and not role & WR and cnt.get('o', 0) < 12 and i % 3 == 0:
                    r = (w >> sh) & ((1 << wd) - 1)
                    x = setfield(w, sh, wd, r + 1 if r + 1 < 1 << wd else r - 1)
                    if dec(x) is not None and not _benign_copy_alias(raw, i, w, x):
                        cnt['o'] = cnt.get('o', 0) + 1
                        mut = list(raw)
                        mut[i] = x
                        run('sched pair, operand', fn, mut, False, rel)
                    break
            if w >> 26 in (14, 32, 36, 48, 52) and cnt.get('i', 0) < 12 and i % 3 == 1:
                cnt['i'] = cnt.get('i', 0) + 1
                mut = list(raw)
                mut[i] = w ^ 4
                run('sched pair, immediate', fn, mut, False, rel)
        c = 0
        for kind, mut, want in sched_mutations(fn, raw):
            if not want and c < 16 and kind in ('sched RAW', 'sched across call', 'sched call moved',
                                                'sched aliasing memory', 'sched boundary'):
                # the relocations stay at their instruction
                if any(i in urel for i in range(fn.n) if mut[i] != raw[i]):
                    continue
                c += 1
                run('sched pair, ' + kind[6:], fn, mut, False, rel)
    # (c) originals as their own counterpart, reordered
    want_n = {'sched RAW': 40, 'sched independent': 40, 'sched load/load': 20, 'sched disjoint memory': 20,
              'sched aliasing memory': 40, 'sched boundary': 20, 'sched across call': 40, 'sched call moved': 40,
              'sched frame/global': 10, 'sched escaped frame/pointer': 20, 'sched frame/pointer': 10}
    scanned = 0
    for a in sorted(prog.fns)[::5]:
        fn = prog.fns[a]
        if not 8 <= fn.n <= 300 or prog.unsupported(fn):
            continue
        if all(tot.get(k, 0) >= v for k, v in want_n.items()) or scanned >= 400:
            break
        scanned += 1
        per = {}
        for kind, mut, want in sched_mutations(fn, fn.words, prog.sda, lambda a: SchedCtx(prog).isglobal(a, 8)):
            if tot.get(kind, 0) >= 2 * want_n.get(kind, 20) or per.get(kind, 0) >= 2:
                continue
            per[kind] = per.get(kind, 0) + 1
            run(kind, fn, mut, want)
    for kind in sorted(set(tot) | set(want_n)):
        n = tot.get(kind, 0)
        acc = kind in ('sched independent', 'sched load/load', 'sched disjoint memory', 'sched frame/global') or \
            (kind == 'sched frame/pointer' and 'pointer' in SCHED_RELAX)
        print('selftest %-28s %5d of %5d %s' % (kind + ':', good.get(kind, 0), n, 'accepted' if acc else 'rejected'))
        if n < 5 and kind in want_n:
            bad += 1
            print('FAIL selftest: too few %s cases' % kind)
    return bad


def _benign_copy_eq(fn, words, i, old, new):
    """Independent check used only by the self-test, for copies made in another block: True
    if `new` differs from `old` in one GPR that is read, and on EVERY path to instruction i
    the two registers are known to be equal because one was copied from the other (mr /
    ori rA,rS,0) and neither was written since (a call writes the volatile registers).
    A forward must-analysis over the control-flow graph, on the decoder only."""
    d = dec(old)
    if d is None or dec(new) is None:
        return False
    pair = None
    for base, sh, wd, role in d[0]:
        x, y = (old >> sh) & ((1 << wd) - 1), (new >> sh) & ((1 << wd) - 1)
        if x != y:
            if pair or base != GP or not role & RD or role & WR:
                return False
            pair = frozenset((x, y))
    if not pair or (old ^ new) & ~d[7] & 0xFFFFFFFF:
        return False
    n = len(words)
    state = [None] * n                     # set of frozenset({x, y}) known equal before i
    state[0] = frozenset()
    work = [0]
    while work:
        j = work.pop()
        w = words[j]
        dj = dec(w)
        if dj is None:
            return False
        wr = set(r for r in regbits(dj[2]) if r < 32)
        for base, sh, wd, role in dj[0]:
            if base == GP and role & WR:
                wr.add((w >> sh) & 31)
        if j in fn.call:
            wr.update(regbits(VOL & 0xFFFFFFFF))
        out = set(p for p in state[j] if not p & wr)
        if copy_of(w) and w >> 26 in (31, 24) and (w >> 16) & 31 != (w >> 21) & 31:
            out.add(frozenset(((w >> 16) & 31, (w >> 21) & 31)))
        out = frozenset(out)
        for t_ in fn.succ[j]:
            new_ = out if state[t_] is None else state[t_] & out
            if new_ != state[t_]:
                state[t_] = new_
                work.append(t_)
    return state[i] is not None and pair in state[i]


def selftest(args, P):
    prog = load_program(args, P)
    prog.strict = False
    units = load_units(P)
    bad = synth_run()
    names = list(dict.fromkeys(SELFTEST + load_allow(P['allow']) + args.selftest))
    bases = []
    npos = 0
    for name in names:                            # (a) known-good pairs
        fn = prog.byname.get(name)
        unit = next((u for u, s, e in units if fn and s <= fn.addr < e), None)
        try:
            mine = Obj(os.path.join(P['build'], 'src', unit + '.o'))
            tgt = Obj(os.path.join(P['build'], 'obj', unit + '.o'))
        except (OSError, TypeError) as e:
            print('skip %s: no objects (%s)' % (name, e))
            continue
        ours, why, _loose = obj_words(prog, name, mine, tgt)
        ok, text_ = prog.check(fn, ours) if ours is not None else (False, why)
        print('%s %s: %s' % ('PASS' if ok else 'FAIL', name, text_))
        if not ok:
            bad += 1
        elif text_ != 'exact':
            npos += 1
            bases.append((fn, ours, 15))
    print('selftest: %d register-equivalent function(s) pass' % npos)
    # originals as their own (exact) counterpart: plenty of every instruction kind
    want = {'swap subf': 30, 'swap fdiv': 30, 'swap cmpw': 30, 'call argument': 30, 'commutative': 30, 'operand': 30}
    for a in sorted(prog.fns)[::7]:
        fn = prog.fns[a]
        if 8 <= fn.n <= 600 and not prog.unsupported(fn):
            bases.append((fn, fn.words, 2))
    tot, rej, reasons = {}, {}, {}
    for fn, ours, cap in bases:
        if cap == 2 and all(tot.get(k, 0) >= n for k, n in want.items()):
            break
        by = {}
        for kind, i, x in mutations(fn, ours):
            if x != ours[i] and (cap != 2 or tot.get(kind, 0) < 2 * want.get(kind, 30)):
                by.setdefault(kind, []).append((i, x))
        picked = [(kind, i, x) for kind, lst in sorted(by.items())
                  for i, x in lst[::max(1, len(lst) // cap)][:cap]]
        for kind, i, x in picked:
            mut = list(ours)
            mut[i] = x
            ok, text_ = prog.check(fn, mut)
            tot[kind] = tot.get(kind, 0) + 1
            if kind == 'commutative':
                if ok:
                    rej[kind] = rej.get(kind, 0) + 1
                else:
                    bad += 1
                    print('FAIL selftest: commutative swap rejected in %s at %08x: %s' % (fn.name, fn.addr + 4 * i, text_))
            elif not ok:
                rej[kind] = rej.get(kind, 0) + 1
                key = re.sub(r'\b(at|vs) [0-9a-f]{8}|\b[rf]\d+\b|\bcr\d\b|\(.*\)', '', text_).strip()
                reasons[key] = reasons.get(key, 0) + 1
            elif kind == 'operand' and (_benign_copy_alias(ours, i, ours[i], x) or
                                        _benign_copy_eq(fn, ours, i, ours[i], x)):
                # the "corrupted" operand names a register that provably holds a plain copy
                # (mr) of the original operand at this point, so the program is unchanged;
                # verified by an independent straight-line scan, not by the checker itself
                rej[kind] = rej.get(kind, 0) + 1
                reasons['benign copy alias'] = reasons.get('benign copy alias', 0) + 1
            else:
                bad += 1
                print('FAIL selftest: %s corruption accepted in %s at %08x (%08x -> %08x): %s' % (
                    kind, fn.name, fn.addr + 4 * i, ours[i], x, text_))
    for kind in sorted(set(tot) | set(want)):
        n = tot.get(kind, 0)
        print('selftest %-16s %5d of %5d %s' % (kind + ':', rej.get(kind, 0), n,
                                              'accepted' if kind == 'commutative' else 'rejected'))
        if n < min(want.get(kind, 1), 5):
            bad += 1
            print('FAIL selftest: too few %s cases' % kind)
    if args.verbose:
        for key, n in sorted(reasons.items(), key=lambda kv: -kv[1]):
            print('  %5d  %s' % (n, key))
    bad += sched_selftest(args, P, prog, units)
    print('selftest: %s' % ('FAILED (%d problem(s))' % bad if bad else 'OK'))
    return 1 if bad else 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--version', default='GHYE6S')
    ap.add_argument('--dol', help='built DOL (default build/<version>/main.dol)')
    ap.add_argument('--list', nargs='+', metavar='UNIT', help='report whether units/functions would pass')
    ap.add_argument('--strict', action='store_true', help='whole-function renaming only (the first version of the rule)')
    ap.add_argument('--selftest', nargs='*', metavar='FN', help='self-test (extra functions that must pass)')
    ap.add_argument('-v', '--verbose', action='store_true', help='--list: also print exact functions')
    args = ap.parse_args()
    v = args.version
    P = {
        'build': os.path.join(ROOT, 'build', v),
        'dol': args.dol or os.path.join(ROOT, 'build', v, 'main.dol'),
        'orig': os.path.join(ROOT, 'orig', v, 'sys', 'main.dol'),
        'syms': os.path.join(ROOT, 'config', v, 'symbols.txt'),
        'splits': os.path.join(ROOT, 'config', v, 'splits.txt'),
        'allow': os.path.join(ROOT, 'config', v, 'regequiv.txt'),
        'sallow': os.path.join(ROOT, 'config', v, 'schedequiv.txt'),
    }
    if args.selftest is not None:
        sys.exit(selftest(args, P))
    sys.exit(list_mode(args, P) if args.list else check_dol(args, P))


if __name__ == '__main__':
    main()
