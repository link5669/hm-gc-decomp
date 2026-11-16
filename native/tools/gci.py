#!/usr/bin/env python3
"""Move Haunted Mansion saves between Dolphin (.gci) and the native port's card folder.

  gci.py import FILE.gci [CARD_DIR]   Dolphin save -> native (default ~/.local/share/hauntedmansion/card_a)
  gci.py export NAME OUT.gci [CARD_DIR]  native save NAME (e.g. Mansion1) -> .gci for Dolphin's GCI folder
"""
import os, struct, sys, time

META_MAGIC = 0x4D434131
META_FMT = '<9I4s2s2s33s3s'   # magic fileNo time iconAddr commentAddr iconFormat iconSpeed bannerFormat permission
                              # gameName company pad name pad2  (runtime/card.cpp struct Meta, host endian)

def card_dir(arg):
    if arg: return arg
    base = os.environ.get('XDG_DATA_HOME') or os.path.expanduser('~/.local/share')
    return os.path.join(base, 'hauntedmansion', 'card_a')

def used_file_numbers(d):
    nums = set()
    for f in os.listdir(d):
        if f.endswith('.meta'):
            m = struct.unpack(META_FMT, open(os.path.join(d, f), 'rb').read()[:struct.calcsize(META_FMT)])
            nums.add(m[1])
    return nums

def do_import(path, d):
    g = open(path, 'rb').read()
    hdr, data = g[:64], g[64:]
    game, company, banner = hdr[0:4], hdr[4:6], hdr[7]
    name = hdr[8:40].split(b'\0')[0]
    t, icon_addr = struct.unpack('>II', hdr[0x28:0x30])
    icon_fmt, icon_speed = struct.unpack('>HH', hdr[0x30:0x34])
    perm = hdr[0x34]
    blocks = struct.unpack('>H', hdr[0x38:0x3A])[0]
    comment = struct.unpack('>I', hdr[0x3C:0x40])[0]
    if game != b'GHYE' or company != b'6S':
        sys.exit('not a Haunted Mansion (GHYE6S) save: %r %r' % (game, company))
    if len(data) != blocks * 8192:
        sys.exit('size mismatch: %d bytes for %d blocks' % (len(data), blocks))
    os.makedirs(d, exist_ok=True)
    n = name.decode('ascii')
    old = os.path.join(d, n + '.meta')
    fno = None
    if os.path.exists(old):
        fno = struct.unpack(META_FMT, open(old, 'rb').read()[:struct.calcsize(META_FMT)])[1]
    if fno is None:
        used = used_file_numbers(d)
        fno = next(i for i in range(127) if i not in used)
    open(os.path.join(d, n + '.sav'), 'wb').write(data)
    meta = struct.pack(META_FMT, META_MAGIC, fno, t, icon_addr, comment, icon_fmt, icon_speed, banner, perm,
                       game, company, b'\0\0', name.ljust(33, b'\0'), b'\0\0\0')
    open(os.path.join(d, n + '.meta'), 'wb').write(meta)
    print('imported %s (%d blocks) into %s as file %d' % (n, blocks, d, fno))

def do_export(name, out, d):
    m = struct.unpack(META_FMT, open(os.path.join(d, name + '.meta'), 'rb').read()[:struct.calcsize(META_FMT)])
    _, fno, t, icon_addr, comment, icon_fmt, icon_speed, banner, perm, game, company, _, nm, _ = m
    data = open(os.path.join(d, name + '.sav'), 'rb').read()
    blocks = len(data) // 8192
    hdr = bytearray(64)
    hdr[0:4] = game; hdr[4:6] = company; hdr[6] = 0xFF; hdr[7] = banner
    hdr[8:40] = nm[:32]
    hdr[0x28:0x30] = struct.pack('>II', t, icon_addr)
    hdr[0x30:0x34] = struct.pack('>HH', icon_fmt, icon_speed)
    hdr[0x34] = perm; hdr[0x35] = 0
    hdr[0x36:0x3A] = struct.pack('>HH', 5, blocks)
    hdr[0x3A:0x3C] = b'\xff\xff'
    hdr[0x3C:0x40] = struct.pack('>I', comment)
    open(out, 'wb').write(bytes(hdr) + data)
    print('exported %s (%d blocks) to %s' % (name, blocks, out))

if __name__ == '__main__':
    a = sys.argv[1:]
    if len(a) >= 2 and a[0] == 'import': do_import(a[1], card_dir(a[2] if len(a) > 2 else None))
    elif len(a) >= 3 and a[0] == 'export': do_export(a[1], a[2], card_dir(a[3] if len(a) > 3 else None))
    else: sys.exit(__doc__)
