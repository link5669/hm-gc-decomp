// Hardware registers the recompiled SDK talks to: PI (interrupts, CPU FIFO), CP/PE (GPU FIFO + sync),
// VI (video timing / retrace interrupt), DI (DVD from the disc image), EXI (SRAM/RTC; no memory card),
// SI (inert: pads are HLE), MI, write-gather pipe. DSP/ARAM/AI go to the audio module.
#include "rt.h"
#include "../gpu/gpu.h"
#include "../audio/audio.h"
#include <ctime>

// ---------------- PI ----------------
static u32 pi_lines;    // level-triggered device lines
static u32 pi_mask;
static u32 pi_fifo_base, pi_fifo_end, pi_fifo_wp;
void pi_line(u32 bit, bool level) {
    if (level) pi_lines |= bit; else pi_lines &= ~bit;
    if (level && (pi_lines & pi_mask)) rt_irq_flag = 1;
}
extern "C" void rt_pi_line(uint32_t bit, int level) { pi_line(bit, level != 0); }
bool irq_pending_pi_only() { return (pi_lines & pi_mask) != 0; }
u32 pi_debug_lines() { return pi_lines; }
bool irq_pending() { return (pi_lines & pi_mask) || g_dec_pending; }

// ---------------- CP / PE / gather pipe ----------------
static u16 cp_regs[0x40];
static u16 pe_regs[0x20];
static u16 pe_token;
static u8 gp_buf[256]; static u32 gp_len;

static bool cp_linked() { return (cp_regs[1] & 0x11) == 0x11; }   // GP read enable + GP link enable
static void gp_flush() {
    if (!gp_len) return;
    u32 n = gp_len; gp_len = 0;
    gpu_fifo_write(gp_buf, n);
}
void gp_write(u32 v, int size) {
    u8 b[4];
    for (int i = 0; i < size; i++) b[i] = (u8)(v >> (8 * (size - 1 - i)));
    // into guest memory at the CPU FIFO write pointer
    for (int i = 0; i < size; i++) {
        u32 p = pi_fifo_wp & 0x03FFFFFF;
        RAM[p & 0x01FFFFFF] = b[i];
        p++;
        if (pi_fifo_end && p >= (pi_fifo_end & 0x03FFFFFF)) { p = pi_fifo_base & 0x03FFFFFF; pi_fifo_wp = p | 0x04000000; }
        else pi_fifo_wp = (pi_fifo_wp & 0x04000000) | p;
    }
    if (cp_linked()) {
        memcpy(gp_buf + gp_len, b, size); gp_len += size;
        if (gp_len >= 128) gp_flush();
    }
}
static void pe_update_lines() {
    u16 c = pe_regs[5];
    pi_line(0x200, (c & 1) && (c & 4));   // token
    pi_line(0x400, (c & 2) && (c & 8));   // finish
}
extern "C" void gpu_cb_draw_done(void) { pe_regs[5] |= 8; pe_update_lines(); }
extern "C" void gpu_cb_token(uint16_t token) { pe_token = token; pe_regs[5] |= 4; pe_update_lines(); }

static u32 cp_read(u32 off) {
    gp_flush();
    u32 r = (off & 0x7F) >> 1;
    switch (r) {
    case 0: return 0x0C | 0x02;                       // SR: GP idle, FIFO below low watermark
    case 0x1C: case 0x1D: return 0;                   // RW distance
    case 0x1E: case 0x1F: return cp_regs[0x1A + (r - 0x1E)]; // read ptr := write ptr (all consumed)
    }
    return cp_regs[r & 0x3F];
}
static void cp_write(u32 off, u16 v) {
    u32 r = (off & 0x7F) >> 1;
    cp_regs[r & 0x3F] = v;
    if (r == 1) { if (cp_linked()) {} pi_line(0x800, false); }
    if (r == 2) pi_line(0x800, false);  // clear
}
static u32 pe_read(u32 off) {
    gp_flush();
    u32 r = (off & 0x3F) >> 1;
    if (r == 7) return pe_token;
    if (r >= 8) return 0; // perf counters
    return pe_regs[r];
}
static void pe_write(u32 off, u16 v) {
    u32 r = (off & 0x3F) >> 1;
    if (r == 5) {
        u16 st = pe_regs[5] & 0xC;
        st &= ~(v & 0xC);   // write 1 to clear
        pe_regs[5] = (v & 3) | st;
        pe_update_lines();
        return;
    }
    pe_regs[r] = v;
}

// ---------------- VI ----------------
static u16 vi_regs[0x80];
void present_vi_frame(u32 xfb, int w, int h);
static u64 vi_frame_start;
static const u64 VI_FIELD_TB = TB_HZ * 1001 / 60000;  // 59.94 Hz
static u32 vi_lines_per_field() { u32 v = vi_regs[0] & 0x3FF; return v ? v * 2 + 1 : 525; } // VTR (approx)
static void vi_update_line() {
    bool any = false;
    for (int i = 0; i < 4; i++) { u16 hi = vi_regs[0x18 + 2 * i]; if ((hi & 0x8000) && (hi & 0x1000)) any = true; }
    pi_line(0x100, any);
}
u32 g_vi_count;
void vi_event() {
    g_vi_count++;
    gp_flush();
    vi_frame_start = tb_now();
    // DI0: retrace interrupt. DI1 likewise if enabled. (DI2/DI3 = light gun position, unused)
    for (int i = 0; i < 2; i++) if (vi_regs[0x18 + 2 * i] & 0x1000) vi_regs[0x18 + 2 * i] |= 0x8000;
    VLOG("VI: di0=%04X di1=%04X lines=%X mask=%X\n", vi_regs[0x18], vi_regs[0x1A], pi_lines, pi_mask);
    vi_update_line();
    {   // scan-out: top-field frame buffer address, width (words per line * 16), height (active lines)
        u32 tfbl = ((u32)vi_regs[0x0E] << 16) | vi_regs[0x0F];
        u32 addr = (tfbl & 0x10000000) ? ((tfbl & 0xFFFFFF) << 5) : (tfbl & 0xFFFFFF);
        int w = ((vi_regs[0x24] >> 8) & 0x7F) * 16;
        int acv = (vi_regs[0x00] >> 4) & 0x3FF;
        bool progressive = vi_regs[0x01] & 4;   // DCR NIN
        int h = progressive ? acv : acv * 2;
        { static int n; if ((n++ % 60) == 0) VLOG("VI scanout %08X %dx%d tfbl=%08X\n", addr, w, h, tfbl); }
        present_vi_frame(addr, w, h);
    }
    hw_poll_host();
    ev_schedule(EV_VI, vi_frame_start + VI_FIELD_TB);
}
static u32 vi_read(u32 off) {
    u32 r = (off & 0xFF) >> 1;
    if (r == 0x16 || r == 0x17) {   // VCT / HCT current position
        u64 el = tb_now() - vi_frame_start;
        u32 lines = 263;
        u32 line = (u32)(el * lines / VI_FIELD_TB) + 1; if (line > lines) line = lines;
        u32 h = (u32)((el * lines % VI_FIELD_TB) * 858 / VI_FIELD_TB) + 1;
        return r == 0x16 ? line : h;
    }
    return vi_regs[r & 0x7F];
}
static void vi_write(u32 off, u16 v) {
    u32 r = (off & 0xFF) >> 1;
    vi_regs[r & 0x7F] = v;
    if (r >= 0x18 && r <= 0x1F) vi_update_line();
}

// ---------------- DI ----------------
static u32 di_regs[10];   // SR CVR CMD0 CMD1 CMD2 MAR LEN CR IMM CFG
static bool di_busy;
static void di_update_line() {
    u32 sr = di_regs[0], cvr = di_regs[1];
    bool l = ((sr & 0x04) && (sr & 0x02)) || ((sr & 0x10) && (sr & 0x08)) || ((sr & 0x40) && (sr & 0x20)) || ((cvr & 4) && (cvr & 2));
    pi_line(0x4, l);
}
static void di_execute() {
    u32 cmd = di_regs[2] >> 24;
    u32 mar = di_regs[5] & 0x03FFFFE0, len = di_regs[6];
    switch (cmd) {
    case 0xA8: {   // read
        u64 off = (u64)di_regs[3] << 2;
        u32 n = len;
        if (!disc_read(off, RAM + (mar & 0x01FFFFFF), n)) LOG("DI: read past end %llx+%x\n", (unsigned long long)off, n);
        di_regs[5] = mar + n; di_regs[6] = 0;
        VLOG("DI read %08llX len %X -> %08X\n", (unsigned long long)off, n, mar);
        break;
    }
    case 0x12: {   // inquiry: drive info
        u8 info[0x20] = {0, 0, 0, 0, 0x20, 0x02, 0x04, 0x02, 0x61};
        memcpy(RAM + (mar & 0x01FFFFFF), info, len < 0x20 ? len : 0x20);
        di_regs[5] = mar + len; di_regs[6] = 0;
        break;
    }
    case 0xAB: case 0xE3: case 0xE4: case 0xE1: break;
    case 0xE0: di_regs[8] = 0; break;     // request error: none
    case 0xE2: di_regs[8] = 0; break;     // audio status
    default: LOG("DI: unknown command %08X\n", di_regs[2]); break;
    }
    di_busy = true;
    ev_schedule(EV_DI, tb_now() + TB_HZ / 5000);   // 200 us
}
void di_event() {
    if (!di_busy) return;
    di_busy = false;
    di_regs[7] &= ~1u;     // TSTART done
    di_regs[0] |= 0x10;    // TCINT
    di_update_line();
}
static u32 di_read(u32 off) { u32 r = (off & 0x3F) >> 2; return r < 10 ? di_regs[r] : 0; }
static void di_write(u32 off, u32 v) {
    u32 r = (off & 0x3F) >> 2;
    if (r == 0) {  // SR: mask bits writable, int bits write-1-to-clear
        u32 ints = di_regs[0] & 0x54; ints &= ~(v & 0x54);
        di_regs[0] = (v & 0x2B) | ints; di_update_line(); return;
    }
    if (r == 1) { u32 ints = di_regs[1] & 4; ints &= ~(v & 4); di_regs[1] = (v & 2) | ints; di_update_line(); return; }
    if (r < 10) di_regs[r] = v;
    if (r == 7 && (v & 1)) di_execute();
}

// ---------------- EXI ----------------
struct ExiChan { u32 cpr, mar, len, cr, data; int dev; u32 cmd; bool have_cmd; u32 pos; };
static ExiChan exi[3];
static u8 sram[64];
static void sram_init() {
    memset(sram, 0, sizeof sram);
    sram[0x11] = 0;      // ntd (video mode)
    sram[0x12] = 0;      // language English
    sram[0x13] = 0x2C;   // flags (stereo etc., like Dolphin)
    u16 sum = 0, inv = 0;
    for (int i = 0x0C; i < 0x14; i += 2) { u16 w = (sram[i] << 8) | sram[i + 1]; sum += w; inv += (u16)~w; }
    sram[0] = sum >> 8; sram[1] = sum; sram[2] = inv >> 8; sram[3] = inv;
}
static u32 rtc_now() { return (u32)(time(nullptr) - 946684800); }  // seconds since 2000-01-01
static void exi_update_lines() {
    bool l = false;
    for (int i = 0; i < 3; i++) { u32 c = exi[i].cpr; if (((c & 1) && (c & 2)) || ((c & 4) && (c & 8)) || ((c & 0x400) && (c & 0x800))) l = true; }
    pi_line(0x10, l);
}
static u8 exi_dev_byte(ExiChan &e, int ch, bool write, u8 wv) {
    // only channel 0 device 1 (RTC/SRAM/IPL ROM) is present
    if (!(ch == 0 && e.dev == 1)) return 0xFF;
    u32 a = e.cmd & 0x7FFFFFFF;
    if (a >= 0x20000000 && a < 0x20000100) { // RTC (4 bytes)
        u32 r = rtc_now(); u8 v = (u8)(r >> (24 - 8 * (e.pos & 3))); e.pos++; return v;
    }
    if (a >= 0x20000100 && a < 0x20001000) {  // SRAM
        u32 o = ((a - 0x20000100) >> 6) + e.pos; e.pos++;
        if (o < 64) { if (write) { sram[o] = wv; return 0; } return sram[o]; }
        return 0;
    }
    if (a < 0x20000000) { e.pos++; return 0; } // IPL ROM: not available
    e.pos++; return 0;
}
static void exi_transfer(int ch) {
    ExiChan &e = exi[ch];
    bool dma = e.cr & 2; int rw = (e.cr >> 2) & 3;  // 0 read, 1 write, 2 rw
    if (!dma) {
        int n = ((e.cr >> 4) & 3) + 1;
        if (!e.have_cmd && rw == 1 && n == 4) { e.cmd = e.data; e.have_cmd = true; e.pos = 0; }
        else {
            u32 out = 0;
            for (int i = 0; i < n; i++) {
                u8 wv = (u8)(e.data >> (24 - 8 * i));
                u8 r = exi_dev_byte(e, ch, rw != 0 && (e.cmd & 0x80000000), wv);
                out |= (u32)r << (24 - 8 * i);
            }
            if (rw != 1) e.data = out;
        }
    } else {
        u32 mar = e.mar & 0x03FFFFE0;
        for (u32 i = 0; i < e.len; i++) {
            u8 *p = RAM + ((mar + i) & 0x01FFFFFF);
            if (rw == 1) exi_dev_byte(e, ch, (e.cmd & 0x80000000) != 0, *p);
            else *p = exi_dev_byte(e, ch, false, 0);
        }
    }
    e.cr &= ~1u;
    e.cpr |= 8;  // TCINT
    exi_update_lines();
}
static u32 exi_read(u32 off) {
    int ch = (off & 0xFF) / 0x14, r = ((off & 0xFF) % 0x14) / 4;
    if (ch > 2) return 0;
    ExiChan &e = exi[ch];
    switch (r) {
    case 0: return (e.cpr & ~0x1000u) | ((ch == 0 || ch == 2) ? 0 : 0);  // EXT (memory card present) = 0
    case 1: return e.mar; case 2: return e.len; case 3: return e.cr; case 4: return e.data;
    }
    return 0;
}
static void exi_write(u32 off, u32 v) {
    int ch = (off & 0xFF) / 0x14, r = ((off & 0xFF) % 0x14) / 4;
    if (ch > 2) return;
    ExiChan &e = exi[ch];
    switch (r) {
    case 0: {
        u32 ints = e.cpr & 0x80A; ints &= ~(v & 0x80A);
        int olddev = e.dev;
        e.cpr = (v & 0x37F5) | ints;
        u32 cs = (v >> 7) & 7;
        e.dev = cs & 1 ? 0 : cs & 2 ? 1 : cs & 4 ? 2 : -1;
        if (e.dev != olddev) { e.have_cmd = false; e.pos = 0; }
        exi_update_lines();
        break;
    }
    case 1: e.mar = v; break; case 2: e.len = v; break;
    case 3: e.cr = v; if (v & 1) exi_transfer(ch); break;
    case 4: e.data = v; break;
    }
}

// ---------------- SI (inert) / MI / misc ----------------
static u32 si_regs[0x40];
static u16 mi_regs[0x40];

void hw_init() {
    sram_init();
    pi_mask = 0;
    pe_regs[5] = 0;
    di_regs[1] = 0;   // cover closed
    ev_schedule(EV_VI, tb_now() + VI_FIELD_TB);
}

u32 hw_read(u32 a, int size) {
    if ((a >> 24) == 0xC8) {   // EFB
        gp_flush();
        u32 x = (a >> 2) & 0x3FF, y = (a >> 12) & 0x3FF; bool z = (a >> 22) & 1;
        return gpu_efb_peek(x, y, z);
    }
    if ((a >> 24) != 0xCC) { LOG("read%d from unmapped %08X\n", size * 8, a); return 0; }
    u32 off = a & 0xFFFF;
    u32 blk = off >> 12;
    u32 v = 0;
    switch (blk) {
    case 0x0: v = cp_read(off); if (size == 4) v = (v << 16) | cp_read(off + 2); break;
    case 0x1: v = pe_read(off); if (size == 4) v = (v << 16) | pe_read(off + 2); break;
    case 0x2: v = vi_read(off); if (size == 4) v = (v << 16) | vi_read(off + 2); break;
    case 0x3: {
        u32 r = (off & 0xFF) >> 2;
        switch (r) {
        case 0: v = pi_lines | 0x10000; break;   // reset switch not pressed
        case 1: v = pi_mask; break;
        case 3: v = pi_fifo_base; break; case 4: v = pi_fifo_end; break; case 5: v = pi_fifo_wp; break;
        case 0xB: v = 0x246500B1; break;          // flipper revision
        default: v = 0; break;
        }
        if (size == 2) v = (off & 2) ? (v & 0xFFFF) : (v >> 16);
        break;
    }
    case 0x4: v = mi_regs[(off & 0x7F) >> 1]; if (size == 4) v = (v << 16) | mi_regs[((off + 2) & 0x7F) >> 1]; break;
    case 0x5: v = audio_dsp_read16(off); if (size == 4) v = (v << 16) | audio_dsp_read16(off + 2); break;
    case 0x6: {
        u32 sub = off & 0xFC00;
        if (sub == 0x6000) v = di_read(off);
        else if (sub == 0x6400) v = si_regs[(off & 0xFF) >> 2];
        else if (sub == 0x6800) v = exi_read(off);
        else if (sub == 0x6C00) v = audio_ai_read32(off);
        if (size == 2) v = (off & 2) ? (v & 0xFFFF) : (v >> 16);
        else if (size == 1) v = (v >> (24 - 8 * (off & 3))) & 0xFF;
        break;
    }
    default: LOG("read%d from %08X\n", size * 8, a);
    }
    return v;
}

void hw_write(u32 a, u32 v, int size) {
    if ((a >> 24) == 0xC8) {
        gp_flush();
        u32 x = (a >> 2) & 0x3FF, y = (a >> 12) & 0x3FF; bool z = (a >> 22) & 1;
        gpu_efb_poke(x, y, z, v);
        return;
    }
    if ((a >> 24) != 0xCC) { LOG("write%d %08X to unmapped %08X\n", size * 8, v, a); return; }
    u32 off = a & 0xFFFF;
    if (off >= 0x8000 && off < 0x9000) { gp_write(v, size); return; }
    u32 blk = off >> 12;
    switch (blk) {
    case 0x0: if (size == 4) { cp_write(off, v >> 16); cp_write(off + 2, (u16)v); } else cp_write(off, (u16)v); break;
    case 0x1: if (size == 4) { pe_write(off, v >> 16); pe_write(off + 2, (u16)v); } else pe_write(off, (u16)v); break;
    case 0x2: if (size == 4) { vi_write(off, v >> 16); vi_write(off + 2, (u16)v); } else vi_write(off, (u16)v); break;
    case 0x3: {
        u32 r = (off & 0xFF) >> 2;
        switch (r) {
        case 0: if (v & 2) pi_lines &= ~2u; break;  // ack reset switch
        case 1: pi_mask = v; if (pi_lines & pi_mask) rt_irq_flag = 1; break;
        case 3: pi_fifo_base = v; break;
        case 4: pi_fifo_end = v; break;
        case 5: pi_fifo_wp = v; break;
        case 9: break;   // reset: DVD reset etc
        default: break;
        }
        break;
    }
    case 0x4: if (size == 4) { mi_regs[(off & 0x7F) >> 1] = v >> 16; mi_regs[((off + 2) & 0x7F) >> 1] = (u16)v; } else mi_regs[(off & 0x7F) >> 1] = (u16)v; break;
    case 0x5: if (size == 4) { audio_dsp_write16(off, v >> 16); audio_dsp_write16(off + 2, (u16)v); } else audio_dsp_write16(off, (u16)v); break;
    case 0x6: {
        u32 sub = off & 0xFC00;
        if (size != 4) LOG("write%d to %08X\n", size * 8, a);
        if (sub == 0x6000) di_write(off, v);
        else if (sub == 0x6400) si_regs[(off & 0xFF) >> 2] = v;
        else if (sub == 0x6800) exi_write(off, v);
        else if (sub == 0x6C00) audio_ai_write32(off, v);
        break;
    }
    default: LOG("write%d %08X to %08X\n", size * 8, v, a);
    }
}
