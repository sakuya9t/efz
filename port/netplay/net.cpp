// Netplay's network layer (net.h): sockets, addresses, protobuf's wire format and zlib's
// inflate.
#include "net.h"

#include <stdlib.h>
#include <string.h>
#include <algorithm>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#ifndef SIO_UDP_CONNRESET
#define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR, 12)
#endif
typedef int socklen_t;
#else
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace efz {
namespace net {

namespace {

#ifdef _WIN32
bool StartSockets(std::string* error)
{
    static bool started = false;
    if (started)
        return true;
    WSADATA data;
    int r = WSAStartup(MAKEWORD(2, 2), &data);
    if (r != 0) {
        if (error)
            *error = "Winsock didn't start (" + std::to_string(r) + ")";
        return false;
    }
    started = true;
    return true;
}

std::string LastError()
{
    return "error " + std::to_string(WSAGetLastError());
}

void CloseFd(intptr_t fd)
{
    closesocket((SOCKET)fd);
}
#else
bool StartSockets(std::string*)
{
    return true;
}

std::string LastError()
{
    return strerror(errno);
}

void CloseFd(intptr_t fd)
{
    close((int)fd);
}
#endif

const sockaddr* Sa(const Endpoint& e)
{
    return (const sockaddr*)e.sa;
}

// The IPv4 address an endpoint stands for, if it is IPv4 or IPv4-mapped IPv6.
bool AsV4(const Endpoint& e, uint32_t* addr)
{
    if (Sa(e)->sa_family == AF_INET) {
        memcpy(addr, &((const sockaddr_in*)e.sa)->sin_addr, 4);
        return true;
    }
    if (Sa(e)->sa_family == AF_INET6) {
        const unsigned char* b = (const unsigned char*)&((const sockaddr_in6*)e.sa)->sin6_addr;
        static const unsigned char mapped[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xff, 0xff};
        if (memcmp(b, mapped, 12) == 0) {
            memcpy(addr, b + 12, 4);
            return true;
        }
    }
    return false;
}

} // namespace

// --- Endpoint

bool Endpoint::IsV6() const
{
    return len > 0 && Sa(*this)->sa_family == AF_INET6;
}

uint16_t Endpoint::Port() const
{
    if (len <= 0)
        return 0;
    if (Sa(*this)->sa_family == AF_INET6)
        return ntohs(((const sockaddr_in6*)sa)->sin6_port);
    return ntohs(((const sockaddr_in*)sa)->sin_port);
}

void Endpoint::SetPort(uint16_t port)
{
    if (len <= 0)
        return;
    if (Sa(*this)->sa_family == AF_INET6)
        ((sockaddr_in6*)sa)->sin6_port = htons(port);
    else
        ((sockaddr_in*)sa)->sin_port = htons(port);
}

bool Endpoint::SameAddress(const Endpoint& other) const
{
    if (len <= 0 || other.len <= 0)
        return false;
    uint32_t a, b;
    bool a4 = AsV4(*this, &a), b4 = AsV4(other, &b);
    if (a4 || b4)
        return a4 && b4 && a == b;
    return memcmp(&((const sockaddr_in6*)sa)->sin6_addr,
                  &((const sockaddr_in6*)other.sa)->sin6_addr, 16) == 0;
}

std::string Endpoint::ToString() const
{
    if (len <= 0)
        return "(none)";
    char host[INET6_ADDRSTRLEN + 1] = "?";
    uint32_t v4;
    if (AsV4(*this, &v4)) {
        inet_ntop(AF_INET, &v4, host, sizeof(host));
        return std::string(host) + ":" + std::to_string(Port());
    }
    inet_ntop(AF_INET6, (void*)&((const sockaddr_in6*)sa)->sin6_addr, host, sizeof(host));
    return "[" + std::string(host) + "]:" + std::to_string(Port());
}

bool Resolve(const std::string& textIn, uint16_t defaultPort, Endpoint* out, std::string* error)
{
    if (!StartSockets(error))
        return false;
    std::string text = textIn;
    while (!text.empty() && (text.back() == ' ' || text.back() == '\t'))
        text.pop_back();
    size_t start = text.find_first_not_of(" \t");
    text = start == std::string::npos ? "" : text.substr(start);
    std::string host = text, port;
    if (!text.empty() && text[0] == '[') {
        size_t close = text.find(']');
        if (close == std::string::npos) {
            *error = "missing ] in the address";
            return false;
        }
        host = text.substr(1, close - 1);
        if (close + 1 < text.size()) {
            if (text[close + 1] != ':') {
                *error = "expected :port after ]";
                return false;
            }
            port = text.substr(close + 2);
        }
    } else if (text.find(':') != std::string::npos &&
               text.find(':') == text.rfind(':')) {
        host = text.substr(0, text.find(':'));
        port = text.substr(text.find(':') + 1);
    }
    if (host.empty()) {
        *error = "no address";
        return false;
    }
    long portNumber = defaultPort;
    if (!port.empty()) {
        char* end = nullptr;
        portNumber = strtol(port.c_str(), &end, 10);
        if (*end != 0 || portNumber < 1 || portNumber > 65535) {
            *error = "the port must be a number from 1 to 65535";
            return false;
        }
    }
    addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    addrinfo* list = nullptr;
    int r = getaddrinfo(host.c_str(), nullptr, &hints, &list);
    if (r != 0 || !list) {
        *error = "can't find the address " + host;
        return false;
    }
    // IPv4 first: what a player types is mostly that, and every host takes it.
    addrinfo* pick = list;
    for (addrinfo* a = list; a; a = a->ai_next) {
        if (a->ai_family == AF_INET) {
            pick = a;
            break;
        }
    }
    memset(out, 0, sizeof(*out));
    memcpy(out->sa, pick->ai_addr, pick->ai_addrlen);
    out->len = (int)pick->ai_addrlen;
    out->SetPort((uint16_t)portNumber);
    freeaddrinfo(list);
    return true;
}

std::vector<std::string> LocalAddresses()
{
    std::vector<std::string> out;
    std::string error;
    if (!StartSockets(&error))
        return out;
#ifdef _WIN32
    char host[256];
    if (gethostname(host, sizeof(host)) != 0)
        return out;
    addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    addrinfo* list = nullptr;
    if (getaddrinfo(host, nullptr, &hints, &list) != 0)
        return out;
    for (addrinfo* a = list; a; a = a->ai_next) {
        char text[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &((sockaddr_in*)a->ai_addr)->sin_addr, text, sizeof(text));
        if (strncmp(text, "127.", 4) != 0 && strncmp(text, "169.254.", 8) != 0 &&
            std::find(out.begin(), out.end(), text) == out.end())
            out.push_back(text);
    }
    freeaddrinfo(list);
#else
    ifaddrs* list = nullptr;
    if (getifaddrs(&list) != 0)
        return out;
    for (ifaddrs* a = list; a; a = a->ifa_next) {
        if (!a->ifa_addr || a->ifa_addr->sa_family != AF_INET)
            continue;
        char text[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &((sockaddr_in*)a->ifa_addr)->sin_addr, text, sizeof(text));
        if (strncmp(text, "127.", 4) != 0 && strncmp(text, "169.254.", 8) != 0 &&
            std::find(out.begin(), out.end(), text) == out.end())
            out.push_back(text);
    }
    freeifaddrs(list);
#endif
    return out;
}

// --- Socket

bool Socket::Open(int family, uint16_t port, std::string* error)
{
    Close();
    if (!StartSockets(error))
        return false;
    bool dual = family == 0;
    v6_ = family != 4;
    intptr_t fd = (intptr_t)socket(v6_ ? AF_INET6 : AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#ifdef _WIN32
    if ((SOCKET)fd == INVALID_SOCKET)
        fd = kNone;
#endif
    if (fd < 0 && dual) {
        // No IPv6 here: IPv4 alone.
        v6_ = false;
        fd = (intptr_t)socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#ifdef _WIN32
        if ((SOCKET)fd == INVALID_SOCKET)
            fd = kNone;
#endif
    }
    if (fd < 0) {
        *error = "can't open a UDP socket: " + LastError();
        return false;
    }
    if (v6_) {
        int only = dual ? 0 : 1;
        setsockopt((decltype(socket(0, 0, 0)))fd, IPPROTO_IPV6, IPV6_V6ONLY, (const char*)&only,
                   sizeof(only));
    }
    sockaddr_storage local;
    memset(&local, 0, sizeof(local));
    socklen_t localLen;
    if (v6_) {
        sockaddr_in6* a = (sockaddr_in6*)&local;
        a->sin6_family = AF_INET6;
        a->sin6_addr = in6addr_any;
        a->sin6_port = htons(port);
        localLen = sizeof(sockaddr_in6);
    } else {
        sockaddr_in* a = (sockaddr_in*)&local;
        a->sin_family = AF_INET;
        a->sin_addr.s_addr = htonl(INADDR_ANY);
        a->sin_port = htons(port);
        localLen = sizeof(sockaddr_in);
    }
    if (bind((decltype(socket(0, 0, 0)))fd, (const sockaddr*)&local, localLen) != 0) {
        *error = "can't use UDP port " + std::to_string(port) + ": " + LastError();
        CloseFd(fd);
        return false;
    }
#ifdef _WIN32
    u_long on = 1;
    ioctlsocket((SOCKET)fd, FIONBIO, &on);
    // Windows reports an ICMP "port unreachable" as an error on the next receive: a peer
    // not listening yet isn't one.
    BOOL report = FALSE;
    DWORD bytes = 0;
    WSAIoctl((SOCKET)fd, SIO_UDP_CONNRESET, &report, sizeof(report), nullptr, 0, &bytes, nullptr,
             nullptr);
#else
    fcntl((int)fd, F_SETFL, fcntl((int)fd, F_GETFL) | O_NONBLOCK);
#endif
    fd_ = fd;
    return true;
}

void Socket::Close()
{
    if (fd_ != kNone)
        CloseFd(fd_);
    fd_ = kNone;
}

uint16_t Socket::LocalPort() const
{
    if (fd_ == kNone)
        return 0;
    Endpoint e;
    socklen_t len = sizeof(e.sa);
    if (getsockname((decltype(socket(0, 0, 0)))fd_, (sockaddr*)e.sa, &len) != 0)
        return 0;
    e.len = (int)len;
    return e.Port();
}

bool Socket::SendTo(const void* data, size_t size, const Endpoint& toIn)
{
    if (fd_ == kNone || toIn.len <= 0)
        return false;
    Endpoint to = toIn;
    // An IPv4 peer from an IPv6 socket: its IPv4-mapped address.
    if (v6_ && !to.IsV6()) {
        sockaddr_in6 a;
        memset(&a, 0, sizeof(a));
        a.sin6_family = AF_INET6;
        a.sin6_port = ((const sockaddr_in*)toIn.sa)->sin_port;
        unsigned char* b = (unsigned char*)&a.sin6_addr;
        b[10] = b[11] = 0xff;
        memcpy(b + 12, &((const sockaddr_in*)toIn.sa)->sin_addr, 4);
        memset(&to, 0, sizeof(to));
        memcpy(to.sa, &a, sizeof(a));
        to.len = sizeof(a);
    }
    int sent = (int)sendto((decltype(socket(0, 0, 0)))fd_, (const char*)data, (int)size, 0,
                           (const sockaddr*)to.sa, (socklen_t)to.len);
    return sent == (int)size;
}

bool Socket::Wait(int ms)
{
    if (fd_ == kNone)
        return false;
    fd_set read;
    FD_ZERO(&read);
    FD_SET((decltype(socket(0, 0, 0)))fd_, &read);
    timeval tv;
    tv.tv_sec = ms / 1000;
    tv.tv_usec = (ms % 1000) * 1000;
    return select((int)fd_ + 1, &read, nullptr, nullptr, &tv) > 0;
}

int Socket::Receive(void* buffer, size_t size, Endpoint* from)
{
    if (fd_ == kNone)
        return -1;
    for (;;) {
        socklen_t len = sizeof(from->sa);
        int n = (int)recvfrom((decltype(socket(0, 0, 0)))fd_, (char*)buffer, (int)size, 0,
                              (sockaddr*)from->sa, &len);
        if (n >= 0) {
            from->len = (int)len;
            return n;
        }
#ifdef _WIN32
        int e = WSAGetLastError();
        // Too large for the buffer (not Revival's): dropped. A reset is the ICMP that
        // SIO_UDP_CONNRESET should have hidden.
        if (e == WSAEMSGSIZE || e == WSAECONNRESET)
            continue;
#else
        if (errno == EINTR)
            continue;
#endif
        return -1;
    }
}

// --- protobuf's wire format

void Writer::Raw(uint64_t value)
{
    while (value >= 0x80) {
        data_.push_back((char)(value | 0x80));
        value >>= 7;
    }
    data_.push_back((char)value);
}

void Writer::Varint(int field, uint64_t value)
{
    Raw((uint64_t)field << 3 | 0);
    Raw(value);
}

void Writer::Bytes(int field, const void* data, size_t size)
{
    Raw((uint64_t)field << 3 | 2);
    Raw(size);
    data_.append((const char*)data, size);
}

bool Reader::Parse(const unsigned char* p, size_t size)
{
    fields_.clear();
    size_t i = 0;
    auto varint = [&](uint64_t* v) {
        *v = 0;
        for (int shift = 0; shift < 64; shift += 7) {
            if (i >= size)
                return false;
            unsigned char b = p[i++];
            *v |= (uint64_t)(b & 0x7f) << shift;
            if (!(b & 0x80))
                return true;
        }
        return false;
    };
    while (i < size) {
        uint64_t key;
        if (!varint(&key))
            return false;
        Field f;
        f.number = (int)(key >> 3);
        f.isBytes = false;
        f.value = 0;
        switch (key & 7) {
        case 0:
            if (!varint(&f.value))
                return false;
            break;
        case 1: // 64-bit: none of Revival's messages has one
            if (i + 8 > size)
                return false;
            i += 8;
            continue;
        case 2: {
            uint64_t len;
            if (!varint(&len) || len > size - i)
                return false;
            f.isBytes = true;
            f.bytes.assign((const char*)p + i, (size_t)len);
            i += (size_t)len;
            break;
        }
        case 5:
            if (i + 4 > size)
                return false;
            i += 4;
            continue;
        default:
            return false;
        }
        fields_.push_back(f);
    }
    return true;
}

bool Reader::Has(int field) const
{
    for (const Field& f : fields_)
        if (f.number == field)
            return true;
    return false;
}

uint64_t Reader::U64(int field, uint64_t otherwise) const
{
    uint64_t v = otherwise;
    for (const Field& f : fields_)
        if (f.number == field && !f.isBytes)
            v = f.value;
    return v;
}

std::string Reader::Bytes(int field) const
{
    std::string v;
    for (const Field& f : fields_)
        if (f.number == field && f.isBytes)
            v = f.bytes;
    return v;
}

std::vector<std::string> Reader::RepeatedBytes(int field) const
{
    std::vector<std::string> v;
    for (const Field& f : fields_)
        if (f.number == field && f.isBytes)
            v.push_back(f.bytes);
    return v;
}

std::string Pack(MessageType type, const Writer& message)
{
    std::string packet;
    packet.push_back(0);
    packet.push_back((char)type);
    packet += message.Data();
    return packet;
}

bool Unpack(const unsigned char* packet, size_t size, int* type, std::string* message)
{
    if (size < 2)
        return false;
    *type = packet[1];
    if (packet[0] == 0) {
        message->assign((const char*)packet + 2, size - 2);
        return true;
    }
    return Inflate(packet + 2, size - 2, message, 0x10000);
}

// --- zlib's inflate: the stored, fixed and dynamic blocks of RFC 1951, after the two
// header bytes of RFC 1950, as Mark Adler's puff.c reads them.

namespace {

struct Bits {
    const unsigned char* in;
    size_t size;
    size_t pos;
    uint32_t buffer;
    int count;
    bool error;

    int Take(int need)
    {
        uint32_t v = buffer;
        while (count < need) {
            if (pos >= size) {
                error = true;
                return 0;
            }
            v |= (uint32_t)in[pos++] << count;
            count += 8;
        }
        buffer = v >> need;
        count -= need;
        return (int)(v & ((1u << need) - 1));
    }
};

struct Huffman {
    short count[16];
    short symbol[288];
};

// The canonical code for `n` symbols of the given lengths: 0 if complete, more if
// incomplete, negative if over-subscribed.
int Build(Huffman* h, const short* length, int n)
{
    for (int len = 0; len < 16; len++)
        h->count[len] = 0;
    for (int s = 0; s < n; s++)
        h->count[length[s]]++;
    if (h->count[0] == n)
        return 0;
    int left = 1;
    for (int len = 1; len < 16; len++) {
        left <<= 1;
        left -= h->count[len];
        if (left < 0)
            return left;
    }
    short offs[16];
    offs[1] = 0;
    for (int len = 1; len < 15; len++)
        offs[len + 1] = offs[len] + h->count[len];
    for (int s = 0; s < n; s++)
        if (length[s] != 0)
            h->symbol[offs[length[s]]++] = (short)s;
    return left;
}

int Decode(Bits* b, const Huffman* h)
{
    int code = 0, first = 0, index = 0;
    for (int len = 1; len < 16; len++) {
        code |= b->Take(1);
        if (b->error)
            return -1;
        int count = h->count[len];
        if (code - count < first)
            return h->symbol[index + (code - first)];
        index += count;
        first += count;
        first <<= 1;
        code <<= 1;
    }
    return -1;
}

const short kLengthBase[29] = {3,  4,  5,  6,  7,  8,  9,  10, 11,  13,  15,  17,  19,  23, 27,
                               31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258};
const short kLengthExtra[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2,
                                2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
const short kDistBase[30] = {1,   2,   3,   4,   5,   7,    9,    13,   17,   25,
                             33,  49,  65,  97,  129, 193,  257,  385,  513,  769,
                             1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577};
const short kDistExtra[30] = {0, 0, 0, 0, 1, 1, 2, 2, 3,  3,  4,  4,  5,  5,  6,
                              6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};

bool Codes(Bits* b, std::string* out, size_t maxOut, const Huffman* lengths, const Huffman* dists)
{
    for (;;) {
        int symbol = Decode(b, lengths);
        if (symbol < 0)
            return false;
        if (symbol < 256) {
            if (out->size() >= maxOut)
                return false;
            out->push_back((char)symbol);
            continue;
        }
        if (symbol == 256)
            return true;
        symbol -= 257;
        if (symbol >= 29)
            return false;
        int len = kLengthBase[symbol] + b->Take(kLengthExtra[symbol]);
        int d = Decode(b, dists);
        if (d < 0 || d >= 30)
            return false;
        size_t dist = (size_t)(kDistBase[d] + b->Take(kDistExtra[d]));
        if (b->error || dist > out->size() || out->size() + len > maxOut)
            return false;
        size_t from = out->size() - dist;
        for (int i = 0; i < len; i++)
            out->push_back((*out)[from + i]);
    }
}

bool Stored(Bits* b, std::string* out, size_t maxOut)
{
    b->buffer = 0;
    b->count = 0;
    if (b->pos + 4 > b->size)
        return false;
    unsigned len = b->in[b->pos] | b->in[b->pos + 1] << 8;
    unsigned nlen = b->in[b->pos + 2] | b->in[b->pos + 3] << 8;
    b->pos += 4;
    if (len != (~nlen & 0xffff) || b->pos + len > b->size || out->size() + len > maxOut)
        return false;
    out->append((const char*)b->in + b->pos, len);
    b->pos += len;
    return true;
}

bool Fixed(Bits* b, std::string* out, size_t maxOut)
{
    static Huffman lengths, dists;
    static bool built = false;
    if (!built) {
        short l[288];
        int s = 0;
        for (; s < 144; s++) l[s] = 8;
        for (; s < 256; s++) l[s] = 9;
        for (; s < 280; s++) l[s] = 7;
        for (; s < 288; s++) l[s] = 8;
        Build(&lengths, l, 288);
        for (s = 0; s < 30; s++) l[s] = 5;
        Build(&dists, l, 30);
        built = true;
    }
    return Codes(b, out, maxOut, &lengths, &dists);
}

bool Dynamic(Bits* b, std::string* out, size_t maxOut)
{
    static const short order[19] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
    int nlen = b->Take(5) + 257;
    int ndist = b->Take(5) + 1;
    int ncode = b->Take(4) + 4;
    if (b->error || nlen > 286 || ndist > 30)
        return false;
    short length[320];
    int i = 0;
    for (; i < ncode; i++)
        length[order[i]] = (short)b->Take(3);
    for (; i < 19; i++)
        length[order[i]] = 0;
    Huffman lencode, distcode;
    if (b->error || Build(&lencode, length, 19) != 0)
        return false;
    for (i = 0; i < nlen + ndist;) {
        int symbol = Decode(b, &lencode);
        if (symbol < 0)
            return false;
        if (symbol < 16) {
            length[i++] = (short)symbol;
            continue;
        }
        short value = 0;
        int repeat;
        if (symbol == 16) {
            if (i == 0)
                return false;
            value = length[i - 1];
            repeat = 3 + b->Take(2);
        } else if (symbol == 17) {
            repeat = 3 + b->Take(3);
        } else {
            repeat = 11 + b->Take(7);
        }
        if (b->error || i + repeat > nlen + ndist)
            return false;
        while (repeat--)
            length[i++] = value;
    }
    if (length[256] == 0)
        return false;
    int err = Build(&lencode, length, nlen);
    if (err < 0 || (err > 0 && nlen != lencode.count[0] + lencode.count[1]))
        return false;
    err = Build(&distcode, length + nlen, ndist);
    if (err < 0 || (err > 0 && ndist != distcode.count[0] + distcode.count[1]))
        return false;
    return Codes(b, out, maxOut, &lencode, &distcode);
}

} // namespace

bool Inflate(const unsigned char* in, size_t size, std::string* out, size_t maxOut)
{
    out->clear();
    if (size < 2 || (in[0] & 0x0f) != 8 || ((in[0] << 8) | in[1]) % 31 != 0 || (in[1] & 0x20))
        return false;
    Bits b = {in, size, 2, 0, 0, false};
    int last;
    do {
        last = b.Take(1);
        int type = b.Take(2);
        if (b.error)
            return false;
        bool ok = type == 0 ? Stored(&b, out, maxOut)
                  : type == 1 ? Fixed(&b, out, maxOut)
                  : type == 2 ? Dynamic(&b, out, maxOut)
                              : false;
        if (!ok || b.error)
            return false;
    } while (!last);
    // The Adler-32 of what was inflated, when the stream has it.
    if (b.pos + 4 <= size) {
        uint32_t a = 1, s = 0;
        for (unsigned char c : *out) {
            a = (a + c) % 65521;
            s = (s + a) % 65521;
        }
        const unsigned char* t = in + b.pos;
        uint32_t stored = (uint32_t)t[0] << 24 | t[1] << 16 | t[2] << 8 | t[3];
        if (stored != (s << 16 | a))
            return false;
    }
    return true;
}

} // namespace net
} // namespace efz
