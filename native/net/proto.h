// Online co-op wire protocol (shared by host and guest). TCP, one connection per guest.
// Every message: u32 length (little endian, counts type byte + payload), u8 type, payload.
#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <mutex>

namespace hmnet {

constexpr uint32_t MAGIC = 0x504E4D48;   // "HMNP"
constexpr uint16_t VERSION = 1;
constexpr uint32_t MAX_MSG = 8u << 20;
constexpr int DEFAULT_PORT = 7777;

enum MsgType : uint8_t { HELLO = 1, INPUT = 2, VIDEO = 3, AUDIO = 4, PING = 5, PONG = 6, BYE = 7 };

#pragma pack(push, 1)
struct Hello {            // both directions; the guest sends first, the host answers
    uint32_t magic;
    uint16_t version;
    uint8_t role;          // 0 = guest, 1 = host
    char room[16];         // session/room code ("" = none); the host rejects a mismatch
    char name[32];
};
struct Input {            // the guest's controller (GameCube PADStatus layout, host endian)
    uint16_t buttons;
    int8_t sx, sy, cx, cy;
    uint8_t tl, tr;
    uint8_t connected;
};
struct VideoHdr { uint32_t seq; uint32_t host_ms; uint16_t w, h; };   // + JPEG bytes
struct AudioHdr { uint32_t rate; uint16_t frames; int16_t pred[2]; uint8_t index[2]; };  // + frames bytes (L low nibble, R high)
struct Ping { uint64_t t_ms; };
#pragma pack(pop)

uint64_t now_ms();
std::string env_str(const char *name, const char *def);
int env_int(const char *name, int def);

// sockets
int tcp_connect(const std::string &host, int port, std::string *err);
int tcp_listen(int port, std::string *err);
void tcp_tune(int fd);                         // TCP_NODELAY, keepalive
bool parse_hostport(const std::string &s, std::string *host, int *port, int defport);
// relay preamble: "HMRELAY HOST <code>\n" / "HMRELAY JOIN <code>\n" -> "OK <code>\n" | "ERR <msg>\n"; hosts then wait for "PAIRED\n"
bool read_line(int fd, std::string *line, int timeout_ms);
bool write_all(int fd, const void *p, size_t n);

struct Conn {
    int fd = -1;
    std::mutex send_mu;
    bool send(uint8_t type, const void *a, size_t na, const void *b = nullptr, size_t nb = 0);
    bool recv(uint8_t *type, std::vector<uint8_t> *payload, int timeout_ms);   // false on error/EOF/timeout
    size_t unsent_bytes() const;               // kernel send queue (SIOCOUTQ)
    void close();
};

// IMA-ADPCM, stereo, 4:1
struct AdpcmState { int pred = 0, index = 0; };
void adpcm_encode(const int16_t *lr, int frames, AdpcmState st[2], uint8_t *out);
void adpcm_decode(const uint8_t *in, int frames, AdpcmState st[2], int16_t *lr);

}  // namespace hmnet
