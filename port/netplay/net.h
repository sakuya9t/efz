// Netplay's network layer: UDP sockets and EfzRevival 1.02h's datagrams.
//
// A datagram is a 2-byte header and one protobuf-lite message (protobuf 2.6.1's wire
// format, revival/EfzRevivalLauncher/EfzPackets.proto): byte 0 is 1 when the message
// is zlib-compressed, byte 1 its type (docs/revival.md, "The launcher's protocol").
// Revival compresses Init, Input, Sync and Palette, but reads byte 0 to decide, so
// this side sends every message uncompressed and inflates what it receives.
#ifndef EFZ_NETPLAY_NET_H
#define EFZ_NETPLAY_NET_H

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

namespace efz {
namespace net {

// The message types of byte 1.
enum MessageType {
    kInit = 0,
    kInput = 1,
    kPing = 2,
    kPong = 3,
    kSync = 4,
    kQuit = 5,
    kPalette = 6,
    kRedirect = 7,
    kChangeRole = 8,
    kDone = 9,
    kPunch = 10,
};

// The largest datagram either side sends (ProtocolContext::send's buffer).
const size_t kMaxPacket = 0x400;

// An IPv4 or IPv6 address and port (a sockaddr, kept as bytes so that this header needs
// no system headers).
struct Endpoint {
    unsigned char sa[128];
    int len = 0;

    bool Valid() const { return len > 0; }
    bool IsV6() const;
    uint16_t Port() const;
    void SetPort(uint16_t port);
    // The same address, whatever the port: Revival's peer table is keyed by address. An
    // IPv4 address and its IPv4-mapped IPv6 form are the same.
    bool SameAddress(const Endpoint& other) const;
    bool operator==(const Endpoint& other) const { return SameAddress(other) && Port() == other.Port(); }
    bool operator!=(const Endpoint& other) const { return !(*this == other); }
    // "1.2.3.4:10800", "[::1]:10800".
    std::string ToString() const;
};

// "host", "host:port", "1.2.3.4:port", "[v6]:port" or a bare IPv6 address, resolved
// (getaddrinfo: this can wait on DNS). The port is defaultPort when not given.
bool Resolve(const std::string& text, uint16_t defaultPort, Endpoint* out, std::string* error);
// This computer's IPv4 addresses on its networks (not loopback), for telling the other
// player where to connect.
std::vector<std::string> LocalAddresses();

// A non-blocking UDP socket.
class Socket {
public:
    Socket() = default;
    ~Socket() { Close(); }
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    // family: 4, 6, or 0 for IPv6 that also takes IPv4 (falling back to IPv4 alone).
    // port 0 binds any free port.
    bool Open(int family, uint16_t port, std::string* error);
    void Close();
    bool IsOpen() const { return fd_ != kNone; }
    uint16_t LocalPort() const;
    bool SendTo(const void* data, size_t size, const Endpoint& to);
    // The next datagram's size, or -1 when none is waiting.
    int Receive(void* buffer, size_t size, Endpoint* from);
    // Waits up to `ms` for a datagram; true if one is there.
    bool Wait(int ms);

private:
    static const intptr_t kNone = -1;
    intptr_t fd_ = kNone;
    bool v6_ = false;
};

// --- protobuf-lite's wire format, as much of it as the messages use.

// A message being built, its fields in number order (as protobuf writes them).
class Writer {
public:
    void Varint(int field, uint64_t value);
    // int32: a negative value is sign-extended to ten bytes, as protobuf does.
    void Int32(int field, int32_t value) { Varint(field, (uint64_t)(int64_t)value); }
    void Bytes(int field, const void* data, size_t size);
    const std::string& Data() const { return data_; }

private:
    void Raw(uint64_t value);
    std::string data_;
};

// A message received: each field's values, in the order they came.
class Reader {
public:
    bool Parse(const unsigned char* data, size_t size);
    bool Has(int field) const;
    // The last value of a varint field (as protobuf keeps for a scalar), or `otherwise`.
    uint64_t U64(int field, uint64_t otherwise = 0) const;
    uint32_t U32(int field, uint32_t otherwise = 0) const { return (uint32_t)U64(field, otherwise); }
    int32_t I32(int field, int32_t otherwise = 0) const { return (int32_t)U64(field, (uint64_t)(int64_t)otherwise); }
    // A bytes field's last value, or every value of a repeated one.
    std::string Bytes(int field) const;
    std::vector<std::string> RepeatedBytes(int field) const;

private:
    struct Field {
        int number;
        bool isBytes;
        uint64_t value;
        std::string bytes;
    };
    std::vector<Field> fields_;
};

// The datagram for a message: the header (uncompressed) and the message's bytes.
std::string Pack(MessageType type, const Writer& message);
// A datagram's type and message bytes, inflated if it was compressed; false if it is too
// short or doesn't inflate.
bool Unpack(const unsigned char* packet, size_t size, int* type, std::string* message);

// zlib's format (RFC 1950 around RFC 1951's deflate), as protobuf's GzipOutputStream
// writes it with ZLIB: false if `in` isn't that or would inflate past maxOut bytes.
bool Inflate(const unsigned char* in, size_t size, std::string* out, size_t maxOut);

} // namespace net
} // namespace efz

#endif
