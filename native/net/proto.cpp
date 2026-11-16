#include "proto.h"
#include <arpa/inet.h>
#include <errno.h>
#include <linux/sockios.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <cstdlib>

namespace hmnet {

uint64_t now_ms() {
    timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}
std::string env_str(const char *n, const char *def) { const char *v = getenv(n); return v && *v ? v : def; }
int env_int(const char *n, int def) { const char *v = getenv(n); return v && *v ? atoi(v) : def; }

void tcp_tune(int fd) {
    int one = 1;
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &one, sizeof one);
    setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &one, sizeof one);
}

int tcp_connect(const std::string &host, int port, std::string *err) {
    addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_UNSPEC; hints.ai_socktype = SOCK_STREAM;
    char ps[16]; snprintf(ps, sizeof ps, "%d", port);
    int r = getaddrinfo(host.c_str(), ps, &hints, &res);
    if (r) { if (err) *err = gai_strerror(r); return -1; }
    int fd = -1;
    for (addrinfo *a = res; a; a = a->ai_next) {
        fd = socket(a->ai_family, a->ai_socktype | SOCK_CLOEXEC, a->ai_protocol);
        if (fd < 0) continue;
        if (connect(fd, a->ai_addr, a->ai_addrlen) == 0) break;
        if (err) *err = strerror(errno);
        ::close(fd); fd = -1;
    }
    freeaddrinfo(res);
    if (fd >= 0) tcp_tune(fd);
    return fd;
}

int tcp_listen(int port, std::string *err) {
    int fd = socket(AF_INET6, SOCK_STREAM | SOCK_CLOEXEC, 0);
    bool v6 = fd >= 0;
    if (!v6) fd = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, 0);
    if (fd < 0) { if (err) *err = strerror(errno); return -1; }
    int one = 1, zero = 0;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof one);
    int r;
    if (v6) {
        setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &zero, sizeof zero);
        sockaddr_in6 a{}; a.sin6_family = AF_INET6; a.sin6_port = htons(port); a.sin6_addr = in6addr_any;
        r = bind(fd, (sockaddr *)&a, sizeof a);
    } else {
        sockaddr_in a{}; a.sin_family = AF_INET; a.sin_port = htons(port); a.sin_addr.s_addr = INADDR_ANY;
        r = bind(fd, (sockaddr *)&a, sizeof a);
    }
    if (r || listen(fd, 4)) { if (err) *err = strerror(errno); ::close(fd); return -1; }
    return fd;
}

bool parse_hostport(const std::string &s, std::string *host, int *port, int defport) {
    *port = defport;
    if (s.empty()) return false;
    if (s[0] == '[') {   // [v6]:port
        size_t e = s.find(']'); if (e == std::string::npos) return false;
        *host = s.substr(1, e - 1);
        if (e + 1 < s.size() && s[e + 1] == ':') *port = atoi(s.c_str() + e + 2);
        return true;
    }
    size_t c = s.rfind(':');
    if (c != std::string::npos && s.find(':') == c) { *host = s.substr(0, c); *port = atoi(s.c_str() + c + 1); }
    else *host = s;
    return *port > 0 && *port < 65536;
}

static bool wait_fd(int fd, short ev, int timeout_ms) {
    pollfd p{fd, ev, 0};
    for (;;) {
        int r = poll(&p, 1, timeout_ms);
        if (r < 0 && errno == EINTR) continue;
        return r > 0;
    }
}

static bool read_exact(int fd, void *p, size_t n, int first_timeout_ms) {
    uint8_t *b = (uint8_t *)p;
    int to = first_timeout_ms;
    while (n) {
        if (!wait_fd(fd, POLLIN, to)) return false;
        ssize_t r = ::recv(fd, b, n, 0);
        if (r < 0 && (errno == EINTR || errno == EAGAIN)) continue;
        if (r <= 0) return false;
        b += r; n -= (size_t)r; to = 10000;   // once a message started, give the rest 10 s
    }
    return true;
}

bool write_all(int fd, const void *p, size_t n) {
    const uint8_t *b = (const uint8_t *)p;
    while (n) {
        ssize_t r = ::send(fd, b, n, MSG_NOSIGNAL);
        if (r < 0 && errno == EINTR) continue;
        if (r <= 0) return false;
        b += r; n -= (size_t)r;
    }
    return true;
}

bool read_line(int fd, std::string *line, int timeout_ms) {
    line->clear();
    for (;;) {
        char c;
        if (!read_exact(fd, &c, 1, timeout_ms)) return false;
        if (c == '\n') return true;
        if (line->size() > 200) return false;
        *line += c;
    }
}

bool Conn::send(uint8_t type, const void *a, size_t na, const void *b, size_t nb) {
    std::lock_guard<std::mutex> g(send_mu);
    if (fd < 0) return false;
    uint8_t hdr[5]; uint32_t len = (uint32_t)(1 + na + nb);
    memcpy(hdr, &len, 4); hdr[4] = type;   // x86: little endian
    if (na + nb < 1400) {   // small: one send (TCP_NODELAY would otherwise emit several packets)
        uint8_t buf[1408]; memcpy(buf, hdr, 5); if (na) memcpy(buf + 5, a, na); if (nb) memcpy(buf + 5 + na, b, nb);
        return write_all(fd, buf, 5 + na + nb);
    }
    return write_all(fd, hdr, 5) && (!na || write_all(fd, a, na)) && (!nb || write_all(fd, b, nb));
}

bool Conn::recv(uint8_t *type, std::vector<uint8_t> *payload, int timeout_ms) {
    uint8_t hdr[5];
    if (fd < 0 || !read_exact(fd, hdr, 5, timeout_ms)) return false;
    uint32_t len; memcpy(&len, hdr, 4);
    if (len < 1 || len > MAX_MSG) return false;
    *type = hdr[4];
    payload->resize(len - 1);
    return len == 1 || read_exact(fd, payload->data(), len - 1, 10000);
}

size_t Conn::unsent_bytes() const {
    int n = 0;
    if (fd < 0 || ioctl(fd, SIOCOUTQ, &n) < 0) return 0;
    return (size_t)n;
}

void Conn::close() {
    std::lock_guard<std::mutex> g(send_mu);
    if (fd >= 0) { shutdown(fd, SHUT_RDWR); ::close(fd); fd = -1; }
}

// ---- IMA-ADPCM ----
static const int16_t kStep[89] = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 19, 21, 23, 25, 28, 31, 34, 37, 41, 45, 50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
    130, 143, 157, 173, 190, 209, 230, 253, 279, 307, 337, 371, 408, 449, 494, 544, 598, 658, 724, 796, 876, 963, 1060,
    1166, 1282, 1411, 1552, 1707, 1878, 2066, 2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358, 5894, 6484,
    7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899, 15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767};
static const int8_t kIdx[16] = {-1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8};

static inline int dec_nib(AdpcmState &s, int n) {
    int step = kStep[s.index];
    int d = step >> 3;
    if (n & 4) d += step; if (n & 2) d += step >> 1; if (n & 1) d += step >> 2;
    s.pred += (n & 8) ? -d : d;
    if (s.pred > 32767) s.pred = 32767; if (s.pred < -32768) s.pred = -32768;
    s.index += kIdx[n]; if (s.index < 0) s.index = 0; if (s.index > 88) s.index = 88;
    return s.pred;
}
static inline int enc_nib(AdpcmState &s, int x) {
    int step = kStep[s.index], diff = x - s.pred, n = 0;
    if (diff < 0) { n = 8; diff = -diff; }
    if (diff >= step) { n |= 4; diff -= step; }
    if (diff >= step >> 1) { n |= 2; diff -= step >> 1; }
    if (diff >= step >> 2) n |= 1;
    dec_nib(s, n);   // track the decoder exactly
    return n;
}
void adpcm_encode(const int16_t *lr, int frames, AdpcmState st[2], uint8_t *out) {
    for (int i = 0; i < frames; i++) out[i] = (uint8_t)(enc_nib(st[0], lr[2 * i]) | enc_nib(st[1], lr[2 * i + 1]) << 4);
}
void adpcm_decode(const uint8_t *in, int frames, AdpcmState st[2], int16_t *lr) {
    for (int i = 0; i < frames; i++) { lr[2 * i] = (int16_t)dec_nib(st[0], in[i] & 15); lr[2 * i + 1] = (int16_t)dec_nib(st[1], in[i] >> 4); }
}

}  // namespace hmnet
