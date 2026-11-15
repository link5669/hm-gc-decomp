// Disc image access and the boot state the IPL + apploader leave behind.
#include "rt.h"
#include <cstdio>
#include <mutex>

static FILE *g_disc;
static u64 g_disc_size;
static std::mutex g_disc_mu;

bool disc_open(const std::string &path) {
    g_disc = fopen(path.c_str(), "rb");
    if (!g_disc) return false;
    fseeko(g_disc, 0, SEEK_END); g_disc_size = ftello(g_disc);
    u8 id[6]; fseeko(g_disc, 0, SEEK_SET);
    if (fread(id, 1, 6, g_disc) != 6 || memcmp(id, "GHYE6S", 6) != 0) {
        fprintf(stderr, "%s is not a Haunted Mansion (GHYE6S) disc image\n", path.c_str());
        fclose(g_disc); g_disc = nullptr; return false;
    }
    return true;
}
u64 disc_size() { return g_disc_size; }
bool disc_read(u64 off, void *dst, u32 len) {
    std::lock_guard<std::mutex> l(g_disc_mu);
    if (off >= g_disc_size) { memset(dst, 0, len); return false; }
    fseeko(g_disc, off, SEEK_SET);
    size_t n = fread(dst, 1, len, g_disc);
    if (n < len) memset((u8 *)dst + n, 0, len - n);
    return n == len;
}

static u32 be32(const u8 *p) { return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]; }

void dol_load(const u8 *dol, size_t size) {
    for (int i = 0; i < 18; i++) {
        u32 off = be32(dol + 4 * i), adr = be32(dol + 72 + 4 * i), sz = be32(dol + 144 + 4 * i);
        if (!sz) continue;
        if (off + sz > size) rt_fatal("DOL section %d out of range", i);
        memcpy(HP(adr), dol + off, sz);
    }
    u32 bss = be32(dol + 216), bss_sz = be32(dol + 220);
    // .bss is cleared by __start (__init_data), but do it anyway
    (void)bss; (void)bss_sz;
}

void boot_setup_lowmem() {
    u8 hdr[0x440], bi2[0x2000];
    disc_read(0, hdr, sizeof hdr);
    disc_read(0x440, bi2, sizeof bi2);
    memcpy(HP(0x80000000), hdr, 0x20);              // disc ID / maker / version
    st32(0x80000020, 0x0D15EA5E);                    // booted from bootrom
    st32(0x80000024, 1);
    st32(0x80000028, 0x01800000);                    // 24 MiB
    st32(0x8000002C, 1);                             // console type: retail (HW2)
    st32(0x800000CC, 0);                             // NTSC
    st32(0x800000D0, 0x01000000);                    // ARAM size
    st32(0x800000EC, 0x81800000);                    // simulated mem top (debug)
    st32(0x800000F0, 0x01800000);
    st32(0x800000F8, 0x09A7EC80);                    // bus clock 162 MHz
    st32(0x800000FC, 0x1CF7C580);                    // CPU clock 486 MHz
    st32(0x80000300, 0x4C000064); st32(0x80000800, 0x4C000064); st32(0x80000C00, 0x4C000064);  // rfi stubs
    // FST and BI2 at the top of memory, like the apploader
    u32 fst_off = be32(hdr + 0x424), fst_size = be32(hdr + 0x428), fst_max = be32(hdr + 0x42C);
    u32 fst_addr = (0x81800000 - fst_max) & ~31u;
    disc_read(fst_off, HP(fst_addr), fst_size);
    u32 bi2_addr = (fst_addr - 0x2000) & ~31u;
    memcpy(HP(bi2_addr), bi2, 0x2000);
    st32(0x80000038, fst_addr);
    st32(0x8000003C, fst_max);
    st32(0x800000F4, bi2_addr);
    st32(0x80000034, bi2_addr);                      // arena hi
    st16(0x800030E6, 0x0000);
    st32(0x800030D8, 0xFFFFFFFF);
    LOG("boot: FST %08X (%X bytes), BI2 %08X\n", fst_addr, fst_size, bi2_addr);
}
