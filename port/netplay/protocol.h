// Netplay's protocol: EfzRevival 1.02h's launcher (revival/EfzRevivalLauncher/), in the
// game's process. ProtocolContext and its states (HostConnect, ClientConnect, TestDelay,
// Play, End) become one class driven by Poll, once a frame: its timers are times to
// check, its console is the netplay screens (netplay.cpp), and the shared-memory queues
// to EfzRevival.dll are members the session (session.cpp) reads and writes directly.
//
// The launcher is a process of its own, so it answers a ping at once whatever the game
// is doing. Here a thread of the socket's does that: it takes each datagram as it comes,
// answers pings, and leaves the rest, with the time it came, for Poll. Without it the
// round trips would include the game's frame and its fades and loads, which hold the
// game's thread for half a second, and the input delay that follows from them would be
// that much longer.
//
// What the launcher does that this doesn't: spectating (a spectator is told that the
// host doesn't allow it, as Revival's AllowSpectating = false does), the hole-punching
// server and NAT traversal (the host's port must be reachable), and custom palettes
// (received ones are ignored, none are sent).
#ifndef EFZ_NETPLAY_PROTOCOL_H
#define EFZ_NETPLAY_PROTOCOL_H

#include <stdint.h>
#include <atomic>
#include <deque>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "net.h"

namespace efz {
namespace netplay {

// EfzRevival 1.02h's version, sent in MessageInit (REVIVAL_VERSION): 1.02.
const int kRevivalVersion = 102;
const uint16_t kDefaultPort = 10800;

// One player's input for one frame (SharedData.h): the controls, and the function keys
// (F4-F8 bits 0-4, Esc bit 5).
struct FrameInput {
    char first;
    char second;
};

// The record of a frame both sides compare (SharedData.h's SyncBlock), sent as its 0x40
// bytes: the layout is Revival's.
struct SyncBlock {
    int32_t frame;
    int32_t state;     // the scene
    uint32_t fpuCW;    // the x87 control word, as _controlfp_s gives it
    int16_t stateP1;   // the players' actions, in a fight
    int16_t stateP2;
    FrameInput inputP1;
    FrameInput inputP2;
    int32_t pad14;
    double p1x, p1y, p2x, p2y;
    uint32_t rng;      // the random generator's state
    uint32_t pad3c;

    bool Same(const SyncBlock& o) const;
    std::string ToString() const;
};
static_assert(sizeof(SyncBlock) == 0x40, "Revival's SyncBlock is 0x40 bytes");

// Round trips in milliseconds (SharedData.h's PingStats).
struct PingStats {
    int minimum = 1000000; // lowest ever
    int average = 0;       // of the last 20
    int last = 0;
    int maximum = 0;       // highest of the last 20
};

struct Settings {
    bool host = true;
    std::string address;    // to join: host[:port]
    uint16_t port = kDefaultPort;
    std::string name = "Player";
    int side = 0;           // the host's: 0 P1, 1 P2, anything else at random
    int maxRollback = 4;    // MaxRollback, at most 9
    bool practiceKeys = false;
    // For tests: every datagram this side sends waits this long first, plus up to
    // `jitterMs` more at random, as on a slow link (so that the rollback runs on one
    // machine too).
    int lagMs = 0;
    int jitterMs = 0;
};

class Protocol {
public:
    enum Phase {
        kIdle,
        kHosting,       // waiting for a player (HostConnect)
        kJoining,       // asking the host (ClientConnect)
        kMeasuring,     // pinging (TestDelay, before the 21st reply)
        kChoosing,      // the delay to start with is the player's to pick
        kWaiting,       // picked; waiting for the opponent's
        kPlaying,       // Play
        kEnded,         // End: `message` says why
    };

    ~Protocol() { Close(); }

    bool Start(const Settings& settings, std::string* error);
    // Receives what came and runs the timers. Every frame.
    void Poll();
    // The player leaves: Quit to everyone, then End.
    void Quit(const std::string& why);
    void Close();

    Phase phase = kIdle;
    // What the launcher's console would say now: for the netplay screen.
    std::string message;

    // TestDelay: the delays the measurement allows and suggests; ChooseDelay is typing one.
    int minimumDelay = 0;
    int recommendedDelay = 0;
    void ChooseDelay(int delay);

    // What the launcher gives the game (GameInfo): set once Play starts.
    int localPlayer = 0;
    int remotePlayer = 1;
    int delay = 0;
    int rollback = 4;
    uint32_t seed = 0;
    bool practiceKeys = false;
    std::string names[2]; // UTF-8, P1's and P2's

    // Both players' inputs, a frame each, shared with the session: it appends the local
    // player's, Poll the remote one's.
    std::vector<FrameInput> inputs[2];
    // The round trips: `ping` as measured, `sessionPing` as the session last got it (the
    // launcher's Net queue, refreshed on each reply in Play).
    PingStats ping;
    PingStats sessionPing;

    // Play's handleQueueEvent, after each of the session's updates: the local inputs the
    // opponent hasn't acknowledged, and the session's sync records checked.
    void SendInputs();
    // The session's sync record of a frame, in order (the Sync queue).
    void AddLocalSync(const SyncBlock& block);
    // The first frame on which the two sides' records differed, or -1.
    int desyncFrame = -1;
    int checkedFrame = -1; // syncFrame: the last frame compared

    const net::Endpoint& Opponent() const { return target_; }
    uint16_t LocalPort() const { return socket_.LocalPort(); }

private:
    struct Peer {
        net::Endpoint endpoint;
        int flags;      // 1 gets inputs, 2 a player or the host, 3 the opponent
        uint32_t lastSeen;
    };
    struct Timer {
        uint32_t interval = 0;
        uint32_t next = 0;
        bool on = false;
        void Start(uint32_t ms);
        void Stop() { on = false; }
        bool Due(uint32_t now);
    };

    // NetPeers
    Peer* FindPeer(const net::Endpoint& e);
    void AddPeer(const net::Endpoint& e, int flags);
    void RemovePeer(const net::Endpoint& e);
    bool Flagged(const net::Endpoint& e, int mask);
    bool FlaggedAs(const net::Endpoint& e, int flags);
    std::vector<net::Endpoint> GetFlagged(int mask);
    std::vector<net::Endpoint> GetRole(int flags);

    void SwitchTo(Phase next);
    void End(const std::string& why);
    // A datagram that came at t (pinged: the thread answered it, a ping).
    void Handle(const unsigned char* packet, size_t size, const net::Endpoint& from, uint32_t at,
                bool ponged);
    void Send(net::MessageType type, const net::Writer& message, const net::Endpoint& to);
    void UpdatePing(int rtt);
    bool CheckSync(int frame);

    void SendConnectConfirm(int role, const net::Endpoint& to);
    void SendConnectRequest(int role, const net::Endpoint& to);
    void SendDone(int player, const net::Endpoint& to);
    void SendDoneToPlayers();
    void SendInputPlayer(int frame, int count, const net::Endpoint& to);
    void SendPing(const net::Endpoint& to);
    void SendQuit(const net::Endpoint& to);
    void SendQuitAll();
    void SendSync(int frame, int before, int after, const net::Endpoint& to);
    void SendSyncRequest(int count, const net::Endpoint& to);

    void ReceiveConnectRequest(int game, int version, int role, const std::string& name,
                               bool practiceKeys, const net::Endpoint& from);
    void ReceiveConnectConfirm(int game, int version, int player, uint32_t seed,
                               const std::string& name1, const std::string& name2,
                               bool practiceKeys, const net::Endpoint& from);
    void ReceiveDone(int player, const net::Endpoint& from);
    void ReceiveInput(int ack, int frame, const std::vector<FrameInput>& inputs,
                      const net::Endpoint& from);
    void ReceivePong(const net::Endpoint& from);
    void ReceiveTimeout(const net::Endpoint& peer);

    Settings settings_;
    net::Socket socket_;
    net::Endpoint target_;      // NetPeers::target: the host, or the address hosted on
    std::vector<Peer> peers_;
    bool hosting_ = false;
    bool connected_ = false;    // ClientConnect's
    int pongs_ = 0;             // TestDelay's
    bool chosen_ = false;
    int ack_ = 0;               // Play's: the first local frame the opponent lacks
    std::deque<int> pings_;
    std::vector<SyncBlock> localSyncs_;
    std::vector<SyncBlock> remoteSyncs_;
    Timer pingTimer_, timeoutTimer_, resendTimer_;
    // Settings::lagMs: datagrams waiting to go, in the order they were sent.
    struct Delayed {
        uint32_t due;
        net::Endpoint to;
        std::string packet;
    };
    std::deque<Delayed> delayed_;
    void FlushDelayed(bool all);

    // The socket's thread, and what it received for Poll. mutex_ guards inbox_ and
    // delayed_.
    struct Incoming {
        uint32_t at;
        net::Endpoint from;
        std::string packet;
        bool ponged;
    };
    std::deque<Incoming> inbox_;
    std::mutex mutex_;
    std::thread thread_;
    std::atomic<bool> stopThread_{false};
    void StartThread();
    void StopThread();
    void ThreadMain();
};

} // namespace netplay
} // namespace efz

#endif
