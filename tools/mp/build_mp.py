#!/usr/bin/env python3
"""Build the multiplayer mod on top of the decomp build.

The game is linked unchanged (no code moves). Mod code in src/mp/*.c is compiled with
MWCC, linked by GNU ld at a fixed address just past the game's original arena start
(game symbols resolved from main.elf), appended to main.dol as an extra text section,
and hooked in by rewriting single branch instructions listed in src/mp/hooks.txt.
The space is reserved by config/GHYE6S/ldscript_mp.tpl (between the game's data and the stack).

Usage: python3 tools/mp/build_mp.py [--out build/GHYE6S/main_mp.dol]
"""
import argparse, os, re, struct, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TC = os.path.expanduser("~/.local/share/decompnet/toolchains")
BU = f"{TC}/gc-wii-binutils/powerpc-eabi-"
MWCC = [f"{TC}/wibo/wibo", f"{TC}/mwcc/GC/2.6/mwcceppc.exe"]
CFLAGS = ("-nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off "
          "-O4,p -inline auto -use_lmw_stmw on -nosyspath -RTTI off -str reuse -sdata 0 -sdata2 0 -lang=c -maxerrors 3 "
          "-i src/mp -i tools/rea/ref/dolsdk2004/include -i tools/rea/ref/dolsdk2004/include/libc").split()
BLD = os.path.join(ROOT, "build/GHYE6S")
OUT = os.path.join(BLD, "mp")


def run(cmd, **kw):
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, **kw)
    if r.returncode:
        sys.exit(f"FAILED: {' '.join(cmd)}\n{r.stdout}\n{r.stderr}")
    return r.stdout


def elf_syms(elf):
    syms = {}
    for line in run([BU + "nm", elf]).splitlines():
        p = line.split()
        if len(p) == 3:
            syms[p[2]] = int(p[0], 16)
    return syms


def dol_parse(d):
    off = list(struct.unpack(">18I", d[0:72])); adr = list(struct.unpack(">18I", d[72:144]))
    sz = list(struct.unpack(">18I", d[144:216]))
    return off, adr, sz


def va2off(d, va):
    off, adr, sz = dol_parse(d)
    for i in range(18):
        if sz[i] and adr[i] <= va < adr[i] + sz[i]:
            return off[i] + va - adr[i]
    raise ValueError(f"{va:#x} not in DOL")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=os.path.join(BLD, "main_mp.dol"))
    a = ap.parse_args()
    os.makedirs(OUT, exist_ok=True)
    gsyms = elf_syms(os.path.join(BLD, "main.elf"))
    base = gsyms["_mp_reserve_start"]
    limit = gsyms["_mp_reserve_end"]

    objs = []
    for f in sorted(os.listdir(os.path.join(ROOT, "src/mp"))):
        if f.endswith(".c"):
            o = os.path.join(OUT, f[:-2] + ".o")
            run(MWCC + CFLAGS + os.environ.get("MP_CFLAGS", "").split() + ["-c", f"src/mp/{f}", "-o", o])
            objs.append(o)

    lds = os.path.join(OUT, "mp.ld")
    with open(lds, "w") as fp:
        fp.write(f"""SECTIONS {{
  . = {base:#x};
  mp_start = .;
  .mptext : {{ *(.init) *(.text) *(.text.*) }}
  .mpdata : {{ *(.rodata*) *(.data*) *(.sdata*) *(.sdata2*) *(.ctors) *(.dtors) }}
  .mpbss : {{ *(.bss*) *(.sbss*) *(COMMON) }}
  . = ALIGN(0x20);
  mp_end = .;
  /DISCARD/ : {{ *(.comment) *(extab*) *(extabindex*) *(.mwcats*) }}
}}
""")
    melf = os.path.join(OUT, "mp.elf")
    run([BU + "ld", "-T", lds, "--just-symbols=" + os.path.join(BLD, "main.elf"), "-o", melf] + objs)
    msyms = elf_syms(melf)
    blob_path = os.path.join(OUT, "mp.bin")
    run([BU + "objcopy", "-O", "binary", "-j", ".mptext", "-j", ".mpdata", melf, blob_path])
    blob = open(blob_path, "rb").read()
    end = msyms["mp_end"]
    if end > limit:
        sys.exit(f"mod too big: {end - base:#x} > reserve {limit - base:#x} (ldscript_mp.tpl)")
    blob = blob + b"\0" * (end - base - len(blob))  # bss zero-filled inside the section

    dol = bytearray(open(os.path.join(BLD, "main.dol"), "rb").read())
    off, adr, sz = dol_parse(dol)
    slot = next(i for i in range(7) if sz[i] == 0)
    foff = (len(dol) + 0x1F) & ~0x1F
    dol += b"\0" * (foff - len(dol)) + blob
    off[slot], adr[slot], sz[slot] = foff, base, len(blob)
    # bss end must not overlap: the game's .bss lives below base already
    dol[0:216] = struct.pack(">18I", *off) + struct.pack(">18I", *adr) + struct.pack(">18I", *sz)

    n = 0
    for line in open(os.path.join(ROOT, "src/mp/hooks.txt")):
        line = line.split("#")[0].strip()
        if not line:
            continue
        site, kind, sym = line.split()[:3]
        site = gsyms[site] if site in gsyms else int(site, 16)
        tgt = msyms.get(sym, gsyms.get(sym))
        if tgt is None:
            sys.exit(f"hook target {sym} not found")
        o = va2off(dol, site)
        old = struct.unpack(">I", dol[o:o + 4])[0]
        if kind == "word":  # data pointer (e.g. a vtable slot): replace with the mod symbol's address
            if len(line.split()) > 3 and int(line.split()[3], 16) != old:
                sys.exit(f"word at {site:#x} is {old:08x}, expected {line.split()[3]}")
            dol[o:o + 4] = struct.pack(">I", tgt)
            n += 1
            continue
        if kind == "call":  # replace any instruction (checked against an expected word) with a bl to a stub
            exp = int(line.split()[3], 16) if len(line.split()) > 3 else None
            if exp is not None and exp != old:
                sys.exit(f"call site {site:#x} is {old:08x}, expected {exp:08x}")
            kind = "bl"
        elif kind == "bl" and (old & 0xFC000003) != 0x48000001:
            sys.exit(f"hook site {site:#x} is not a bl ({old:08x})")
        rel = tgt - site
        assert -0x2000000 <= rel < 0x2000000
        ins = 0x48000000 | (rel & 0x03FFFFFC) | (1 if kind == "bl" else 0)
        dol[o:o + 4] = struct.pack(">I", ins)
        n += 1
    open(a.out, "wb").write(dol)
    print(f"mod at {base:#x}..{end:#x} ({end - base} bytes), {len(objs)} objs, {n} hooks -> {a.out}")


if __name__ == "__main__":
    main()
