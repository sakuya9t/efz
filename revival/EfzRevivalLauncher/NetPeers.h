// The remote ends of a netplay session: every endpoint the launcher talks to, keyed by
// address, with its role flags and when it was last heard from, and the endpoint the
// launcher connects to (the host, for a client or spectator). 0x24 bytes.
//
// Flags: 1 receives the inputs (a spectator, or the opponent), 2 is a connected
// player or the host, 4 is the hole punching server; 3 is the opponent.
#pragma once
#include <boost/asio.hpp>
#include <windows.h>
#include <map>
#include <vector>

struct Peer {
    typedef boost::asio::ip::udp::endpoint Endpoint;

    Peer();
    Peer(const Endpoint &endpoint, int flags, DWORD lastSeen);
    ~Peer() {}

    Endpoint endpoint;  // 0x00
    int flags;          // 0x1c
    DWORD lastSeen;     // 0x20 timeGetTime()
};

class NetPeers {
public:
    typedef boost::asio::ip::udp::endpoint Endpoint;

    NetPeers(const Endpoint &target);
    ~NetPeers();
    void add(const Endpoint &endpoint, int flags);
    void clear();
    // Whether the peer has all the flags in mask; whether its flags are exactly flags.
    bool flagged(const Endpoint &endpoint, int mask);
    bool flaggedAs(const Endpoint &endpoint, int flags);
    std::vector<Endpoint> getFlagged(int mask);
    std::vector<Endpoint> getKnown();
    std::vector<Endpoint> getRole(int flags);
    // The peers not heard from for longer than timeout milliseconds.
    std::vector<Endpoint> getTimedOut(DWORD timeout);
    bool isKnown(const Endpoint &endpoint);
    void remove(const Endpoint &endpoint);
    // Records that the peer was heard from; false if it is unknown.
    bool touch(const Endpoint &endpoint);

    Endpoint target;                                        // 0x00
private:
    std::map<boost::asio::ip::address, Peer> peers_;        // 0x1c
};
