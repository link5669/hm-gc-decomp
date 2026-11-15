// Memory card (SDK CARD API) HLE, backed by host files.
// Slot A holds a 59-block card (4 Mbit, 8 KiB sectors, ANSI); slot B is empty.
// Layout: $XDG_DATA_HOME|~/.local/share/hauntedmansion/card_a/<name>.sav (file data, multiple of 8 KiB)
//         and <name>.meta (fixed little-endian record with the CARDStat/dir fields + fileNo).
#include "rt.h"
#include <vector>
#include <string>
#include <ctime>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

enum { R_READY = 0, R_BUSY = -1, R_NOCARD = -3, R_NOFILE = -4, R_EXIST = -7, R_NOENT = -8, R_INSSPACE = -9,
       R_LIMIT = -11, R_NAMETOOLONG = -12, R_FATAL = -128 };
static const u32 SECTOR = 8192, USER_BLOCKS = 59, MAX_FILES = 127;

struct Meta {                       // on-disk record (host endian)
    u32 magic, fileNo, time, iconAddr, commentAddr, iconFormat, iconSpeed, bannerFormat, permission;
    u8 gameName[4], company[2], pad[2];
    char name[33]; u8 pad2[3];
};
static const u32 META_MAGIC = 0x4D434131;
static std::string g_dir;
static int g_last[2] = {R_READY, R_NOCARD};
struct Pending { u32 cb, chan; int result; };
static std::vector<Pending> g_pending;

static void ensure_dir() {
    if (!g_dir.empty()) return;
    std::string base;
    if (const char *x = getenv("XDG_DATA_HOME"); x && *x) base = x;
    else if (const char *h = getenv("HOME"); h && *h) base = std::string(h) + "/.local/share";
    else base = "/tmp";
    std::string p = base;
    for (const char *part : {"hauntedmansion", "card_a"}) { p += "/"; p += part; }
    std::string cur;
    for (size_t i = 0; i <= p.size(); i++) {
        if (i == p.size() || p[i] == '/') { if (!cur.empty()) mkdir(cur.c_str(), 0755); }
        if (i < p.size()) cur += p[i];
    }
    g_dir = p;
}
static std::string enc(const std::string &n) {
    std::string o; char b[4];
    for (unsigned char ch : n) { if (isalnum(ch) || ch == '_' || ch == '-' || ch == '.') o += (char)ch; else { snprintf(b, 4, "%%%02X", ch); o += b; } }
    if (!o.empty() && o[0] == '.') o = "%2E" + o.substr(1);
    return o;
}
static std::string path_of(const std::string &n, const char *ext) { ensure_dir(); return g_dir + "/" + enc(n) + ext; }
static std::vector<Meta> list_files() {
    ensure_dir();
    std::vector<Meta> v;
    if (DIR *d = opendir(g_dir.c_str())) {
        while (dirent *e = readdir(d)) {
            std::string n = e->d_name;
            if (n.size() < 5 || n.compare(n.size() - 5, 5, ".meta")) continue;
            FILE *f = fopen((g_dir + "/" + n).c_str(), "rb"); if (!f) continue;
            Meta m; if (fread(&m, sizeof m, 1, f) == 1 && m.magic == META_MAGIC) { m.name[32] = 0; v.push_back(m); }
            fclose(f);
        }
        closedir(d);
    }
    return v;
}
static bool find_name(const std::string &n, Meta &out) { for (auto &m : list_files()) if (n == m.name) { out = m; return true; } return false; }
static bool find_no(u32 no, Meta &out) { for (auto &m : list_files()) if (m.fileNo == no) { out = m; return true; } return false; }
static bool save_meta(const Meta &m) {
    FILE *f = fopen(path_of(m.name, ".meta").c_str(), "wb"); if (!f) return false;
    bool ok = fwrite(&m, sizeof m, 1, f) == 1; fclose(f); return ok;
}
static u64 data_size(const Meta &m) { struct stat st; return stat(path_of(m.name, ".sav").c_str(), &st) ? 0 : (u64)st.st_size; }
static u32 used_blocks() { u32 b = 0; for (auto &m : list_files()) b += (u32)(data_size(m) / SECTOR); return b; }
static std::string gstr(u32 a, bool &toolong) {
    std::string s; toolong = false;
    for (int i = 0; i < 64; i++) { u8 ch = ld8(a + i); if (!ch) return s; s += (char)ch; if (s.size() > 32) { toolong = true; return s; } }
    toolong = true; return s;
}
static int chk(u32 chan) { return chan > 1 ? R_FATAL : chan == 1 ? R_NOCARD : R_READY; }
static int ret(CPU *c, u32 chan, int r) { if (chan < 2) g_last[chan] = r; c->r[3] = (u32)r; return r; }
static void queue_cb(u32 cb, u32 chan, int result) {
    if (!cb) return;
    g_pending.push_back({cb, chan, result}); rt_irq_flag = 1;
}
extern "C" void rt_card_run_pending(CPU *RESTRICT c) {
    while (!g_pending.empty()) {
        Pending p = g_pending.front(); g_pending.erase(g_pending.begin());
        CPU *sv = new CPU(*c);
        c->msr &= ~0x8000u; c->r[3] = p.chan; c->r[4] = (u32)p.result;
        rt_call(c, p.cb);
        *c = *sv; delete sv;
    }
}

// CARDStat offsets (same as __CARDUpdateStat)
static void calc_offsets(const Meta &m, u32 st) {
    u32 offset = m.iconAddr, flag = 0;
    st32(st + 0x3C, 0xFFFFFFFF); st32(st + 0x40, 0xFFFFFFFF);
    if (m.iconAddr == 0xFFFFFFFFu) { offset = 0; }
    switch (m.bannerFormat & 3) {
    case 1: st32(st + 0x3C, offset); st32(st + 0x40, offset + 0xC00); offset += 0xE00; break;
    case 2: st32(st + 0x3C, offset); offset += 0x1800; break;
    }
    for (int i = 0; i < 8; i++) {
        switch ((m.iconFormat >> (i * 2)) & 3) {
        case 1: st32(st + 0x44 + i * 4, offset); flag = 1; offset += 0x400; break;
        case 2: st32(st + 0x44 + i * 4, offset); offset += 0x800; break;
        default: st32(st + 0x44 + i * 4, 0xFFFFFFFF); break;
        }
    }
    if (flag) { st32(st + 0x64, offset); offset += 0x200; } else st32(st + 0x64, 0xFFFFFFFF);
    st32(st + 0x68, offset);
}

#define A(n) (c->r[n])
extern "C" {
static void card_selftest();
void hle_CARDInit(CPU *RESTRICT c) { VLOG("CARDInit\n"); if (getenv("HM_CARDTEST")) card_selftest(); }
void hle_CARDGetResultCode(CPU *RESTRICT c) { u32 ch = A(3); c->r[3] = ch < 2 ? (u32)g_last[ch] : (u32)R_FATAL; }
void hle_CARDProbe(CPU *RESTRICT c) { c->r[3] = A(3) == 0; }
void hle_CARDProbeEx(CPU *RESTRICT c) {
    u32 ch = A(3); int r = chk(ch);
    if (r == R_READY) { if (A(4)) st32(A(4), 4); if (A(5)) st32(A(5), SECTOR); }
    VLOG("CARDProbeEx(%u) = %d\n", ch, r); c->r[3] = (u32)r;
}
void hle_CARDMount(CPU *RESTRICT c) { u32 ch = A(3); VLOG("CARDMount(%u)\n", ch); ret(c, ch, chk(ch)); }
void hle_CARDUnmount(CPU *RESTRICT c) { u32 ch = A(3); VLOG("CARDUnmount(%u)\n", ch); ret(c, ch, chk(ch)); }
void hle_CARDCheck(CPU *RESTRICT c) { u32 ch = A(3); VLOG("CARDCheck(%u)\n", ch); ret(c, ch, chk(ch)); }
void hle_CARDGetSectorSize(CPU *RESTRICT c) {
    u32 ch = A(3); int r = chk(ch); if (r == R_READY) st32(A(4), SECTOR); c->r[3] = (u32)r;
}
void hle_CARDGetSerialNo(CPU *RESTRICT c) {
    u32 ch = A(3); int r = chk(ch); if (r == R_READY) st64(A(4), 0x0123456789ABCDEFull); c->r[3] = (u32)r;
}
void hle_CARDFreeBlocks(CPU *RESTRICT c) {
    u32 ch = A(3); int r = chk(ch);
    if (r == R_READY) {
        u32 used = used_blocks(), n = (u32)list_files().size();
        if (A(4)) st32(A(4), (used >= USER_BLOCKS ? 0 : USER_BLOCKS - used) * SECTOR);
        if (A(5)) st32(A(5), MAX_FILES - n);
    }
    VLOG("CARDFreeBlocks(%u) = %d\n", ch, r); c->r[3] = (u32)r;
}
void hle_CARDFormat(CPU *RESTRICT c) {
    u32 ch = A(3); int r = chk(ch);
    if (r == R_READY) for (auto &m : list_files()) { unlink(path_of(m.name, ".sav").c_str()); unlink(path_of(m.name, ".meta").c_str()); }
    VLOG("CARDFormat(%u) = %d\n", ch, r); ret(c, ch, r);
}
static int do_open(u32 ch, const Meta &m, u32 fi) {
    st32(fi, ch); st32(fi + 4, m.fileNo); st32(fi + 8, 0); st32(fi + 12, 0xFFFFFFFFu); st16(fi + 16, (u16)(m.fileNo + 5));
    return R_READY;
}
void hle_CARDOpen(CPU *RESTRICT c) {
    u32 ch = A(3); int r = chk(ch); Meta m;
    if (r == R_READY) {
        bool tl; std::string n = gstr(A(4), tl);
        r = tl ? R_NAMETOOLONG : !find_name(n, m) ? R_NOFILE : do_open(ch, m, A(5));
        VLOG("CARDOpen(%s) = %d\n", n.c_str(), r);
    }
    ret(c, ch, r);
}
void hle_CARDFastOpen(CPU *RESTRICT c) {
    u32 ch = A(3); int r = chk(ch); Meta m;
    if (r == R_READY) { r = (A(4) >= MAX_FILES) ? R_FATAL : !find_no(A(4), m) ? R_NOFILE : do_open(ch, m, A(5)); VLOG("CARDFastOpen(%u) = %d\n", A(4), r); }
    ret(c, ch, r);
}
void hle_CARDClose(CPU *RESTRICT c) { u32 fi = A(3); st32(fi, 0xFFFFFFFFu); c->r[3] = 0; }
void hle_CARDCreate(CPU *RESTRICT c) {
    u32 ch = A(3), size = A(5), fi = A(6); int r = chk(ch); Meta m;
    if (r == R_READY) {
        bool tl; std::string n = gstr(A(4), tl);
        auto files = list_files();
        if (tl) r = R_NAMETOOLONG;
        else if (size == 0 || size % SECTOR) r = R_FATAL;
        else if (find_name(n, m)) r = R_EXIST;
        else if (files.size() >= MAX_FILES || used_blocks() + size / SECTOR > USER_BLOCKS) r = R_INSSPACE;
        else {
            memset(&m, 0, sizeof m); m.magic = META_MAGIC; strncpy(m.name, n.c_str(), 32);
            for (m.fileNo = 0;; m.fileNo++) { bool used = false; for (auto &f : files) used |= f.fileNo == m.fileNo; if (!used) break; }
            for (int i = 0; i < 4; i++) m.gameName[i] = ld8(0x80000000 + i);
            for (int i = 0; i < 2; i++) m.company[i] = ld8(0x80000004 + i);
            m.iconAddr = 0xFFFFFFFFu; m.commentAddr = 0xFFFFFFFFu; m.permission = 0;
            m.time = (u32)(time(nullptr) - 946684800);
            int fd = open(path_of(n, ".sav").c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0 || ftruncate(fd, size) || !save_meta(m)) r = R_FATAL;
            if (fd >= 0) close(fd);
            if (r == R_READY) do_open(ch, m, fi);
        }
        VLOG("CARDCreate(%s,%u) = %d\n", n.c_str(), size, r);
    }
    ret(c, ch, r);
}
void hle_CARDDelete(CPU *RESTRICT c) {
    u32 ch = A(3); int r = chk(ch); Meta m;
    if (r == R_READY) {
        bool tl; std::string n = gstr(A(4), tl);
        if (tl) r = R_NAMETOOLONG; else if (!find_name(n, m)) r = R_NOFILE;
        else { unlink(path_of(m.name, ".sav").c_str()); unlink(path_of(m.name, ".meta").c_str()); }
        VLOG("CARDDelete(%s) = %d\n", n.c_str(), r);
    }
    ret(c, ch, r);
}
static int rw(bool write, u32 fi, u32 buf, u32 len, u32 off) {
    u32 ch = ld32(fi), no = ld32(fi + 4); Meta m;
    int r = chk(ch);
    if (r != R_READY) return r;
    if (!find_no(no, m)) return R_NOFILE;
    if (write ? ((len % SECTOR) || (off % SECTOR)) : ((len % 512) || (off % 512)) || (s32)len <= 0 || (s32)off < 0) return R_FATAL;
    if ((u64)off + len > data_size(m)) return R_LIMIT;
    int fd = open(path_of(m.name, ".sav").c_str(), O_RDWR); if (fd < 0) return R_FATAL;
    ssize_t n = write ? pwrite(fd, HP(buf), len, off) : pread(fd, HP(buf), len, off);
    close(fd);
    if (write) { m.time = (u32)(time(nullptr) - 946684800); save_meta(m); }
    return n == (ssize_t)len ? R_READY : R_FATAL;
}
void hle_CARDReadAsync(CPU *RESTRICT c) {
    u32 fi = A(3), cb = A(7); int r = rw(false, fi, A(4), A(5), A(6)); u32 ch = ld32(fi);
    VLOG("CARDRead(file %d, len %u, off %u) = %d\n", (int)ld32(fi + 4), A(5), A(6), r);
    if (r == R_READY) queue_cb(cb, ch, r); ret(c, ch < 2 ? ch : 0, r);
}
void hle_CARDRead(CPU *RESTRICT c) {
    u32 fi = A(3); u32 ch = ld32(fi); int r = rw(false, fi, A(4), A(5), A(6));
    VLOG("CARDReadSync(file %d, len %u, off %u) = %d\n", (int)ld32(fi + 4), A(5), A(6), r); ret(c, ch < 2 ? ch : 0, r);
}
void hle_CARDWriteAsync(CPU *RESTRICT c) {
    u32 fi = A(3), cb = A(7); u32 ch = ld32(fi); int r = rw(true, fi, A(4), A(5), A(6));
    VLOG("CARDWrite(file %d, len %u, off %u) = %d\n", (int)ld32(fi + 4), A(5), A(6), r);
    if (r == R_READY) queue_cb(cb, ch, r); ret(c, ch < 2 ? ch : 0, r);
}
void hle_CARDGetStatus(CPU *RESTRICT c) {
    u32 ch = A(3), no = A(4), st = A(5); int r = chk(ch); Meta m;
    if (r == R_READY) {
        if (no >= MAX_FILES) r = R_FATAL; else if (!find_no(no, m)) r = R_NOFILE;
        else {
            for (u32 i = 0; i < 0x6C; i += 4) st32(st + i, 0);
            for (int i = 0; i < 32; i++) st8(st + i, (u8)m.name[i]);
            st32(st + 0x20, (u32)data_size(m)); st32(st + 0x24, m.time);
            for (int i = 0; i < 4; i++) st8(st + 0x28 + i, m.gameName[i]);
            for (int i = 0; i < 2; i++) st8(st + 0x2C + i, m.company[i]);
            st8(st + 0x2E, (u8)m.bannerFormat); st32(st + 0x30, m.iconAddr); st16(st + 0x34, (u16)m.iconFormat);
            st16(st + 0x36, (u16)m.iconSpeed); st32(st + 0x38, m.commentAddr);
            calc_offsets(m, st);
        }
    }
    VLOG("CARDGetStatus(%u) = %d\n", no, r); ret(c, ch, r);
}
static int set_status(u32 ch, u32 no, u32 st) {
    int r = chk(ch); Meta m;
    if (r != R_READY) return r;
    u32 ia = ld32(st + 0x30), ca = ld32(st + 0x38);
    if (no >= MAX_FILES || (ia != 0xFFFFFFFFu && ia >= 512) || (ca != 0xFFFFFFFFu && (ca & 8191) > 8192 - 64)) return R_FATAL;
    if (!find_no(no, m)) return R_NOFILE;
    m.bannerFormat = ld8(st + 0x2E); m.iconAddr = ia; m.iconFormat = ld16(st + 0x34); m.iconSpeed = ld16(st + 0x36); m.commentAddr = ca;
    if (ia == 0xFFFFFFFFu) m.iconSpeed = (m.iconSpeed & ~3u) | 1;
    m.time = (u32)(time(nullptr) - 946684800);
    calc_offsets(m, st);
    return save_meta(m) ? R_READY : R_FATAL;
}
void hle_CARDSetStatus(CPU *RESTRICT c) { u32 ch = A(3); int r = set_status(ch, A(4), A(5)); VLOG("CARDSetStatus(%u) = %d\n", A(4), r); ret(c, ch, r); }
void hle_CARDSetStatusAsync(CPU *RESTRICT c) {
    u32 ch = A(3), cb = A(6); int r = set_status(ch, A(4), A(5)); VLOG("CARDSetStatusAsync(%u) = %d\n", A(4), r);
    if (r == R_READY) queue_cb(cb, ch, r); ret(c, ch, r);
}
}

// HM_CARDTEST=1: exercise create/write/read/status/delete through the HLE entry points (scratch RAM at the top of MEM1, restored).
static void card_selftest() {
    CPU t; memset(&t, 0, sizeof t);
    const u32 B = 0x817FE000; u8 save[0x1000]; memcpy(save, HP(B), sizeof save);
    const char *nm = "HMTEST"; for (int i = 0; i < 7; i++) st8(B + i, nm[i]);
    u32 fi = B + 0x100, buf = B + 0x200, st = B + 0x800;
    for (int i = 0; i < 64; i++) st8(buf + i, i + 1);
    auto call = [&](void (*f)(CPU *), u32 a3, u32 a4 = 0, u32 a5 = 0, u32 a6 = 0, u32 a7 = 0) {
        t.r[3] = a3; t.r[4] = a4; t.r[5] = a5; t.r[6] = a6; t.r[7] = a7; f(&t); return (int)t.r[3]; };
    int r1 = call(hle_CARDMount, 0), r2 = call(hle_CARDCreate, 0, B, 8192, fi);
    int r3 = call(hle_CARDWriteAsync, fi, buf, 8192, 0), r4 = call(hle_CARDClose, fi);
    int r5 = call(hle_CARDOpen, 0, B, fi);
    for (int i = 0; i < 64; i++) st8(buf + i, 0);
    int r6 = call(hle_CARDRead, fi, buf, 512, 0), r7 = call(hle_CARDGetStatus, 0, ld32(fi + 4), st);
    fprintf(stderr, "CARDTEST mount=%d create=%d write=%d close=%d open=%d read=%d(buf[5]=%u) status=%d len=%u del=", r1, r2, r3, r4, r5, r6, ld8(buf + 5), r7, ld32(st + 0x20));
    int r8 = call(hle_CARDDelete, 0, B); fprintf(stderr, "%d\n", r8);
    memcpy(HP(B), save, sizeof save);
}
