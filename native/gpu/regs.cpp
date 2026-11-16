// CP / XF / BP register writes.
#include "gx_internal.h"

namespace gx {

CPRegs cp;
u32 xf[0x1058];
u32 bp[256];
u8 tmem[0x80000];
u32 tev_color[4][2], tev_konst[4][2];  // [reg][0=RA,1=BG]
static u32 s_bp_mask = 0xFFFFFF;

void cp_write(u8 reg, u32 val) {
  switch (reg & 0xF0) {
    case 0x30: cp.matidx_a = val; break;
    case 0x40: cp.matidx_b = val; break;
    case 0x50: cp.vcd_lo = val; break;
    case 0x60: cp.vcd_hi = val; break;
    case 0x70: cp.vat_a[reg & 7] = val; break;
    case 0x80: cp.vat_b[reg & 7] = val; break;
    case 0x90: cp.vat_c[reg & 7] = val; break;
    case 0xA0: cp.array_base[reg & 15] = val & 0x03FFFFFF; break;
    case 0xB0: cp.array_stride[reg & 15] = val & 0xFF; break;
    default: break;
  }
}

void xf_write(u32 addr, u32 val) {
  if (addr >= 0x1058) return;
  if (addr >= 0x680 && addr < 0x1000) return;
  if (xf[addr] == val) return;
  flush_batch();
  xf[addr] = val;
}

// BP registers that do not influence how primitives are drawn (no flush needed on change).
static bool bp_no_render(u8 r) {
  if (r >= 0x01 && r <= 0x04) return true;    // copy filter sample pattern
  if (r == 0x0F || r == 0x23 || r == 0x24) return true;
  if (r >= 0x44 && r <= 0x58) return true;    // field mask, draw done, tokens, copy params, bbox
  if (r == 0x60 || r == 0x61 || r == 0x62 || r == 0x63 || r == 0x64 || r == 0x66 || r == 0x67 || r == 0x68)
    return true;
  if (r == 0xFE || r == 0xFF) return true;
  return false;
}

void bp_write(u8 reg, u32 val) {
  val &= 0xFFFFFF;
  if (reg == 0xFE) {
    s_bp_mask = val;
    return;
  }
  u32 old = bp[reg];
  u32 nv = (old & ~s_bp_mask) | (val & s_bp_mask);
  s_bp_mask = 0xFFFFFF;
  bool trigger = (reg == 0x45 || reg == 0x47 || reg == 0x48 || reg == 0x52 || reg == 0x65);
  if (!trigger && nv == old) return;
  if (!bp_no_render(reg) && nv != old) flush_batch();
  bp[reg] = nv;
  if (reg >= 0xE0 && reg <= 0xE7) {
    int r = (reg - 0xE0) >> 1, half = reg & 1;
    if (nv & 0x800000) tev_konst[r][half] = nv;
    else tev_color[r][half] = nv;
    return;
  }
  switch (reg) {
    case 0x45:
      flush_batch();
      gpu_cb_draw_done();
      break;
    case 0x47: break;
    case 0x48:
      flush_batch();
      gpu_cb_token((u16)(nv & 0xFFFF));
      break;
    case 0x52: efb_copy(nv); break;
    case 0x65:
      flush_batch();
      tlut_load();
      break;
    default: break;
  }
}

void tlut_load() {
  u32 addr = (bp[0x64] & 0x1FFFFF) << 5;
  u32 tm = (bp[0x65] & 0x3FF) << 9;
  u32 bytes = ((bp[0x65] >> 10) & 0x7FF) * 32;
  if (tm >= sizeof(tmem)) return;
  if (tm + bytes > sizeof(tmem)) bytes = sizeof(tmem) - tm;
  if (!ram_ok(addr, bytes)) return;
  cap_read(addr, bytes);
  memcpy(tmem + tm, ram_ptr(addr), bytes);
}

}  // namespace gx
