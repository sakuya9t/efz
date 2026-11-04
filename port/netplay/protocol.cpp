// Netplay's protocol (protocol.h): the launcher's ProtocolContext and states, from
// revival/EfzRevivalLauncher/ProtocolContext.cpp and ProtocolState*.cpp.
#include "protocol.h"

#include <SDL3/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <numeric>

#include "../log.h"

namespace efz {
namespace netplay {

namespace {

uint32_t Now()
{
    return (uint32_t)SDL_GetTicks();
}

// A name as the messages carry it, UTF-16 (Windows' wchar_t), from UTF-8 and back. The
// launcher keeps at most 20 characters of a received name and stops at its first zero.
std::string Utf16Bytes(const std::string& utf8, size_t pad)
{
    std::string out;
    size_t i = 0;
    while (i < utf8.size()) {
        unsigned c = (unsigned char)utf8[i];
        uint32_t cp;
        int more = c < 0x80 ? 0 : c < 0xe0 ? 1 : c < 0xf0 ? 2 : 3;
        cp = more == 0 ? c : more == 1 ? c & 0x1f : more == 2 ? c & 0x0f : c & 0x07;
        for (int k = 0; k < more && i + 1 + k < utf8.size(); k++)
            cp = cp << 6 | ((unsigned char)utf8[i + 1 + k] & 0x3f);
        i += 1 + more;
        if (cp >= 0x10000) {
            cp -= 0x10000;
            uint16_t hi = (uint16_t)(0xd800 + (cp >> 10)), lo = (uint16_t)(0xdc00 + (cp & 0x3ff));
            out.push_back((char)(hi & 0xff));
            out.push_back((char)(hi >> 8));
            out.push_back((char)(lo & 0xff));
            out.push_back((char)(lo >> 8));
        } else {
            out.push_back((char)(cp & 0xff));
            out.push_back((char)(cp >> 8));
        }
    }
    if (pad)
        out.resize(pad, 0);
    return out;
}

std::string Utf8FromUtf16(const std::string& bytes)
{
    std::string out;
    size_t units = 0;
    for (size_t i = 0; i + 1 < bytes.size() && units < 20; i += 2, units++) {
        uint32_t cp = (unsigned char)bytes[i] | (unsigned char)bytes[i + 1] << 8;
        if (cp == 0)
            break;
        if (cp >= 0xd800 && cp < 0xdc00 && i + 3 < bytes.size()) {
            uint32_t lo = (unsigned char)bytes[i + 2] | (unsigned char)bytes[i + 3] << 8;
            cp = 0x10000 + ((cp - 0xd800) << 10) + (lo - 0xdc00);
            i += 2;
        }
        if (cp < 0x80) {
            out.push_back((char)cp);
        } else if (cp < 0x800) {
            out.push_back((char)(0xc0 | cp >> 6));
            out.push_back((char)(0x80 | (cp & 0x3f)));
        } else if (cp < 0x10000) {
            out.push_back((char)(0xe0 | cp >> 12));
            out.push_back((char)(0x80 | (cp >> 6 & 0x3f)));
            out.push_back((char)(0x80 | (cp & 0x3f)));
        } else {
            out.push_back((char)(0xf0 | cp >> 18));
            out.push_back((char)(0x80 | (cp >> 12 & 0x3f)));
            out.push_back((char)(0x80 | (cp >> 6 & 0x3f)));
            out.push_back((char)(0x80 | (cp & 0x3f)));
        }
    }
    return out.empty() ? "None" : out;
}

const char* PhaseName(Protocol::Phase p)
{
    static const char* const names[] = {"idle",    "hosting", "joining", "measuring",
                                        "choosing", "waiting", "playing", "ended"};
    return names[p];
}

} // namespace

// --- SyncBlock

bool SyncBlock::Same(const SyncBlock& o) const
{
    return frame == o.frame && fpuCW == o.fpuCW && state == o.state && stateP1 == o.stateP1 &&
           stateP2 == o.stateP2 && inputP1.first == o.inputP1.first &&
           inputP1.second == o.inputP1.second && inputP2.first == o.inputP2.first &&
           inputP2.second == o.inputP2.second && rng == o.rng && p1x == o.p1x && p1y == o.p1y &&
           p2x == o.p2x && p2y == o.p2y;
}

std::string SyncBlock::ToString() const
{
    char text[320];
    snprintf(text, sizeof(text),
             "Frame %d FpuCW 0x%X State %d StateP1 %d StateP2 %d P1 input %d %d P2 input %d %d "
             "Rng %u P1 pos %.17g %.17g P2 pos %.17g %.17g",
             frame, fpuCW, state, stateP1, stateP2, inputP1.first, inputP1.second, inputP2.first,
             inputP2.second, rng, p1x, p1y, p2x, p2y);
    return text;
}

// --- Timers and peers

void Protocol::Timer::Start(uint32_t ms)
{
    interval = ms;
    next = Now() + ms;
    on = true;
}

bool Protocol::Timer::Due(uint32_t now)
{
    if (!on || (int32_t)(now - next) < 0)
        return false;
    next = now + interval;
    return true;
}

Protocol::Peer* Protocol::FindPeer(const net::Endpoint& e)
{
    for (Peer& p : peers_)
        if (p.endpoint.SameAddress(e))
            return &p;
    return nullptr;
}

void Protocol::AddPeer(const net::Endpoint& e, int flags)
{
    if (Peer* p = FindPeer(e)) {
        p->endpoint = e;
        p->flags = flags;
        p->lastSeen = Now();
        return;
    }
    peers_.push_back(Peer{e, flags, Now()});
}

void Protocol::RemovePeer(const net::Endpoint& e)
{
    peers_.erase(std::remove_if(peers_.begin(), peers_.end(),
                                [&](const Peer& p) { return p.endpoint.SameAddress(e); }),
                 peers_.end());
}

bool Protocol::Flagged(const net::Endpoint& e, int mask)
{
    Peer* p = FindPeer(e);
    return p && (p->flags & mask) >= mask;
}

bool Protocol::FlaggedAs(const net::Endpoint& e, int flags)
{
    Peer* p = FindPeer(e);
    return p && p->flags == flags;
}

std::vector<net::Endpoint> Protocol::GetFlagged(int mask)
{
    std::vector<net::Endpoint> out;
    for (const Peer& p : peers_)
        if ((p.flags & mask) >= mask)
            out.push_back(p.endpoint);
    return out;
}

std::vector<net::Endpoint> Protocol::GetRole(int flags)
{
    std::vector<net::Endpoint> out;
    for (const Peer& p : peers_)
        if (p.flags == flags)
            out.push_back(p.endpoint);
    return out;
}

// --- Starting, states

bool Protocol::Start(const Settings& settings, std::string* error)
{
    Close();
    settings_ = settings;
    peers_.clear();
    pings_.clear();
    delayed_.clear();
    localSyncs_.clear();
    remoteSyncs_.clear();
    inputs[0].clear();
    inputs[1].clear();
    ping = PingStats();
    sessionPing = PingStats();
    desyncFrame = -1;
    checkedFrame = -1;
    pongs_ = 0;
    chosen_ = false;
    ack_ = 0;
    connected_ = false;
    seed = Now();
    rollback = std::min(abs(settings.maxRollback), 9);
    practiceKeys = settings.practiceKeys;
    delay = 0;
    // setPlayer: 0 or 1, else a side at random.
    localPlayer = settings.side == 0 || settings.side == 1 ? settings.side : rand() % 2;
    remotePlayer = (localPlayer + 1) % 2;
    names[0] = "Player1";
    names[1] = "Player2";
    if (settings.host) {
        if (!socket_.Open(0, settings.port, error))
            return false;
        target_ = net::Endpoint();
        hosting_ = true;
        StartThread();
        LogInfo("net", "hosting on UDP port %u, as P%d", socket_.LocalPort(), localPlayer + 1);
        message = "Waiting for a player on UDP port " + std::to_string(socket_.LocalPort());
        SwitchTo(kHosting);
    } else {
        if (!net::Resolve(settings.address, settings.port, &target_, error))
            return false;
        // Any free port: two games on one machine can't share the host's.
        if (!socket_.Open(target_.IsV6() ? 6 : 4, 0, error))
            return false;
        hosting_ = false;
        StartThread();
        LogInfo("net", "joining %s from UDP port %u", target_.ToString().c_str(),
                socket_.LocalPort());
        message = "Connecting to " + target_.ToString();
        AddPeer(target_, 2);
        SwitchTo(kJoining);
    }
    return true;
}

void Protocol::SwitchTo(Phase next)
{
    // The old state's leave: its timers stop.
    pingTimer_.Stop();
    timeoutTimer_.Stop();
    resendTimer_.Stop();
    LogInfo("net", "%s -> %s", PhaseName(phase), PhaseName(next));
    phase = next;
    switch (next) {
    case kJoining:
        pingTimer_.Start(500);
        resendTimer_.Start(500);
        timeoutTimer_.Start(5000);
        SendConnectRequest(1, target_);
        break;
    case kMeasuring:
        message = "Measuring the connection to " + target_.ToString();
        pingTimer_.Start(200);
        timeoutTimer_.Start(1000);
        break;
    case kPlaying:
        // Play's enter: the launcher gives the game its GameInfo and starts it.
        message = "Playing";
        LogInfo("net", "playing as P%d against %s (%s), delay %d, rollback %d, seed %u",
                localPlayer + 1, names[remotePlayer].c_str(), target_.ToString().c_str(), delay,
                rollback, seed);
        pingTimer_.Start(200);
        timeoutTimer_.Start(1000);
        resendTimer_.Start(80);
        break;
    case kEnded:
        StopThread();
        socket_.Close();
        break;
    default:
        break;
    }
}

void Protocol::End(const std::string& why)
{
    if (phase == kEnded)
        return;
    message = why;
    LogInfo("net", "the session ends: %s", why.c_str());
    if (phase == kPlaying)
        LogInfo("net", "sync records: %d made here, %d from %s, compared to frame %d, %s",
                (int)localSyncs_.size(), (int)remoteSyncs_.size(), target_.ToString().c_str(),
                checkedFrame,
                desyncFrame < 0 ? "all the same"
                                : ("different from frame " + std::to_string(desyncFrame)).c_str());
    FlushDelayed(true);
    SwitchTo(kEnded);
}

void Protocol::Quit(const std::string& why)
{
    if (phase == kIdle || phase == kEnded)
        return;
    SendQuitAll();
    End(why);
}

void Protocol::Close()
{
    StopThread();
    socket_.Close();
    phase = kIdle;
}

void Protocol::ChooseDelay(int chosen)
{
    if (phase != kChoosing)
        return;
    delay = std::max(minimumDelay, std::min(chosen, 20));
    chosen_ = true;
    SendDoneToPlayers();
    resendTimer_.Start(100);
    message = "Waiting for " + names[remotePlayer];
    phase = kWaiting;
    LogInfo("net", "input delay %d chosen", delay);
}

// --- Poll

void Protocol::Poll()
{
    if (phase == kIdle || phase == kEnded)
        return;
    FlushDelayed(false);
    std::deque<Incoming> got;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        got.swap(inbox_);
    }
    for (const Incoming& in : got) {
        Handle((const unsigned char*)in.packet.data(), in.packet.size(), in.from, in.at,
               in.ponged);
        if (phase == kEnded)
            return;
    }
    uint32_t now = Now();
    if (pingTimer_.Due(now)) {
        for (const net::Endpoint& e : GetFlagged(2))
            SendPing(e);
    }
    if (resendTimer_.Due(now)) {
        if (phase == kJoining) {
            SendConnectRequest(1, target_);
        } else if (phase == kWaiting) {
            SendDoneToPlayers();
        } else if (phase == kPlaying) {
            // Revival asks for the opponent's sync records only with Debug = 1; they are
            // cheap, and a desync is worth knowing about, so always.
            for (const net::Endpoint& e : GetFlagged(2))
                SendSyncRequest(10, e);
        }
    }
    if (timeoutTimer_.Due(now)) {
        std::vector<net::Endpoint> silent;
        for (const Peer& p : peers_)
            if (now - p.lastSeen > 8000)
                silent.push_back(p.endpoint);
        for (const net::Endpoint& e : silent) {
            ReceiveTimeout(e);
            if (phase == kEnded)
                return;
        }
    }
}

void Protocol::ReceiveTimeout(const net::Endpoint& peer)
{
    switch (phase) {
    case kJoining:
        End("No answer from " + target_.ToString());
        break;
    case kMeasuring:
    case kChoosing:
    case kWaiting:
        if (Flagged(peer, 3))
            End(names[remotePlayer] + " stopped answering");
        break;
    case kPlaying:
        if (Flagged(peer, 2)) {
            LogInfo("net", "%s is gone", peer.ToString().c_str());
            SendQuitAll();
            RemovePeer(peer);
            End(names[remotePlayer] + " quit or the connection was lost");
        } else {
            RemovePeer(peer);
        }
        break;
    default:
        break;
    }
}

// --- Receiving (Network::handlePacket, then ProtocolContext's receive* and the state's)

void Protocol::Handle(const unsigned char* packet, size_t size, const net::Endpoint& from,
                      uint32_t at, bool ponged)
{
    int type;
    std::string body;
    if (!net::Unpack(packet, size, &type, &body)) {
        LogDebug("net", "a datagram from %s that isn't Revival's", from.ToString().c_str());
        return;
    }
    if (Peer* p = FindPeer(from))
        p->lastSeen = at;
    net::Reader m;
    if (!m.Parse((const unsigned char*)body.data(), body.size())) {
        LogDebug("net", "a message of type %d from %s doesn't parse", type,
                 from.ToString().c_str());
        return;
    }
    switch (type) {
    case net::kInit: {
        std::string name1 = m.Has(7) ? Utf8FromUtf16(m.Bytes(7)) : "None";
        std::string name2 = m.Has(8) ? Utf8FromUtf16(m.Bytes(8)) : "None";
        bool keys = m.Has(9) && m.U64(9) != 0;
        if (m.U32(1) == 0) {
            if (!Flagged(from, 2)) {
                LogDebug("net", "discard connect from %s", from.ToString().c_str());
                break;
            }
            ReceiveConnectConfirm(m.U32(2), m.U32(3), m.U32(5), m.U32(6), name1, name2, keys, from);
        } else {
            ReceiveConnectRequest(m.U32(2), m.U32(3), m.U32(4), name1, keys, from);
        }
        break;
    }
    case net::kInput: {
        std::vector<FrameInput> got;
        for (const std::string& b : m.RepeatedBytes(5)) {
            FrameInput in = {0, 0};
            if (b.size() >= 2) {
                in.first = b[0];
                in.second = b[1];
            }
            got.push_back(in);
        }
        // An acknowledgement (f1 = 1) is a spectator's: none here.
        if (m.U32(1) == 0 && Flagged(from, 2))
            ReceiveInput(m.I32(2, -1), (int)m.U32(3), got, from);
        break;
    }
    case net::kPing: {
        if (!ponged) {
            net::Writer pong;
            pong.Varint(3, m.U32(3));
            Send(net::kPong, pong, from);
        }
        // ClientConnect's receivePing: the host answers at last.
        if (phase == kJoining && !connected_) {
            if (from.SameAddress(target_)) {
                RemovePeer(target_);
                target_ = from;
            }
            AddPeer(from, 2);
            connected_ = true;
        }
        break;
    }
    case net::kPong:
        if (Flagged(from, 2))
            UpdatePing((int)(at - m.U32(3)));
        ReceivePong(from);
        break;
    case net::kSync: {
        if (m.U32(1) == 0) {
            if (!Flagged(from, 2))
                break;
            for (const std::string& b : m.RepeatedBytes(4)) {
                SyncBlock block;
                memset(&block, 0, sizeof(block));
                memcpy(&block, b.data(), std::min(b.size(), sizeof(block)));
                if (block.frame == (int)remoteSyncs_.size()) {
                    remoteSyncs_.push_back(block);
                    CheckSync(block.frame);
                }
            }
        } else if (Flagged(from, 1)) {
            SendSync((int)m.U32(2), 0, (int)m.U32(3), from);
        }
        break;
    }
    case net::kQuit:
        if (FindPeer(from) && phase == kPlaying) {
            LogInfo("net", "quit from %s", from.ToString().c_str());
            ReceiveTimeout(from);
        } else if (FindPeer(from) && (phase == kMeasuring || phase == kChoosing || phase == kWaiting)) {
            // Not in Revival (its TestDelay waits for the timeout): the opponent left.
            End(names[remotePlayer] + " left");
        }
        break;
    case net::kDone:
        if (Flagged(from, 2))
            ReceiveDone((int)m.U32(1), from);
        break;
    case net::kChangeRole:
        // ClientConnect: the host plays already (2) or takes spectators (1).
        if (phase == kJoining && from == target_) {
            connected_ = true;
            if (m.U32(1) == 2)
                End("The host is already playing a match");
        }
        break;
    case net::kPalette:
    case net::kRedirect:
    case net::kPunch:
        break;
    default:
        break;
    }
}

void Protocol::ReceiveConnectRequest(int game, int version, int role, const std::string& name,
                                     bool keys, const net::Endpoint& from)
{
    switch (phase) {
    case kHosting:
        if (game != 0)
            return;
        if (version != kRevivalVersion) {
            // The client learns the version from the confirmation and gives up.
            SendConnectConfirm(role, from);
            LogWarn("net", "%s has EfzRevival version %d, this is %d", from.ToString().c_str(),
                    version, kRevivalVersion);
            if (version > kRevivalVersion)
                End("A newer EfzRevival tried to join: " + from.ToString());
            return;
        }
        if (role == 1) {
            practiceKeys = practiceKeys && keys;
            names[localPlayer] = settings_.name;
            names[remotePlayer] = name;
            target_ = from;
            AddPeer(from, 3);
            SendConnectConfirm(1, from);
            LogInfo("net", "%s (%s) joins", name.c_str(), from.ToString().c_str());
            SwitchTo(kMeasuring);
        } else {
            SendDone(1, from); // no spectators
        }
        break;
    case kMeasuring:
    case kChoosing:
    case kWaiting:
        if (role == 1 && Flagged(from, 3)) {
            SendConnectConfirm(1, from);
            break;
        }
        SendDone(1, from);
        break;
    case kPlaying:
        if (game != 0 || version != kRevivalVersion) {
            SendConnectConfirm(role, from);
            break;
        }
        // Already playing, and no spectators.
        SendDone(1, from);
        break;
    default:
        break;
    }
}

void Protocol::ReceiveConnectConfirm(int game, int version, int player, uint32_t hostSeed,
                                     const std::string& name1, const std::string& name2,
                                     bool keys, const net::Endpoint& from)
{
    if (phase != kJoining || !from.SameAddress(target_))
        return;
    connected_ = true;
    if (game != 0)
        return;
    if (version != kRevivalVersion) {
        End(version > kRevivalVersion
                ? "The host has a newer EfzRevival (version " + std::to_string(version) + ")"
                : "The host has an older EfzRevival (version " + std::to_string(version) + ")");
        return;
    }
    RemovePeer(target_);
    target_ = from;
    AddPeer(target_, 2);
    localPlayer = player == 1 ? 1 : 0;
    remotePlayer = 1 - localPlayer;
    seed = hostSeed;
    names[0] = name1;
    names[1] = name2;
    practiceKeys = practiceKeys && keys;
    SendConnectConfirm(1, from);
    AddPeer(from, 3);
    LogInfo("net", "joined %s (%s) as P%d", names[remotePlayer].c_str(), from.ToString().c_str(),
            localPlayer + 1);
    SwitchTo(kMeasuring);
}

void Protocol::ReceiveDone(int player, const net::Endpoint& from)
{
    switch (phase) {
    case kJoining:
        RemovePeer(target_);
        target_ = from;
        AddPeer(target_, 2);
        connected_ = true;
        if (player == 1)
            End("The host is already playing, and takes no spectators");
        break;
    case kWaiting:
        if (player == 0 && chosen_) {
            SendDoneToPlayers();
            SwitchTo(kPlaying);
        }
        break;
    default:
        break;
    }
}

void Protocol::ReceiveInput(int ack, int frame, const std::vector<FrameInput>& got,
                            const net::Endpoint& from)
{
    if (phase == kMeasuring || phase == kChoosing || phase == kWaiting) {
        // The opponent has started already: as its Done.
        ReceiveDone(0, from);
        if (phase != kPlaying)
            return;
    }
    if (phase != kPlaying)
        return;
    ack_ = ack + 1;
    std::vector<FrameInput>& remote = inputs[remotePlayer];
    int next = frame;
    for (const FrameInput& in : got) {
        if (next == (int)remote.size())
            remote.push_back(in);
        next++;
    }
}

// TestDelay's: after 20 replies, the 90th percentile of the round trips is the ping, the
// average that of the ones below it, and the delay is suggested from them.
void Protocol::ReceivePong(const net::Endpoint& from)
{
    if (phase == kPlaying) {
        if (FlaggedAs(from, 3))
            sessionPing = ping;
        return;
    }
    if (phase != kMeasuring || !Flagged(from, 3))
        return;
    if (pongs_ == 20) {
        // computeMinimumDelay: a one-way trip in frames at 64 a second, less the rollback.
        double frames = ceil((float)ping.average / (2 * (1000.0 / 64)));
        minimumDelay = (int)std::max(0.0, frames - rollback);
        std::vector<int> sorted(pings_.begin(), pings_.end());
        std::sort(sorted.begin(), sorted.end());
        int index = (int)std::min(std::max(0.0, sorted.size() * 0.9 - 1.0), sorted.size() - 1.0);
        ping.maximum = sorted[index];
        ping.average = index > 0 ? std::accumulate(sorted.begin(), sorted.begin() + index, 0) / index
                                 : sorted[0];
        // computeRecommendedDelay
        float used = std::min(3.0f, (float)rollback);
        int minimum = std::max(minimumDelay, 0);
        double worst = ceil((float)sorted[index] / (2 * (1000.0 / 64)));
        int suggested = std::max(minimum, (int)ceil(worst - used));
        recommendedDelay = std::min(20, (float)rollback == used ? suggested + 1 : suggested);
        LogInfo("net", "ping average %d, min %d, max %d: delay at least %d, %d recommended",
                ping.average, ping.minimum, ping.maximum, minimumDelay, recommendedDelay);
        message = "Choose the input delay";
        phase = kChoosing;
    }
    pongs_++;
}

void Protocol::UpdatePing(int rtt)
{
    pings_.push_back(rtt);
    while (pings_.size() > 20)
        pings_.pop_front();
    ping.average = std::accumulate(pings_.begin(), pings_.end(), 0) / (int)pings_.size();
    ping.last = rtt;
    ping.minimum = std::min(ping.minimum, rtt);
    ping.maximum = *std::max_element(pings_.begin(), pings_.end());
}

bool Protocol::CheckSync(int frame)
{
    if ((int)localSyncs_.size() <= frame || (int)remoteSyncs_.size() <= frame)
        return false;
    const SyncBlock& a = localSyncs_[frame];
    const SyncBlock& b = remoteSyncs_[frame];
    bool same = a.Same(b);
    checkedFrame = frame;
    if (same && frame > 0 && frame % 1024 == 0)
        LogInfo("net", "frames 0-%d: both sides' sync records agree", frame);
    if (!same) {
        if (desyncFrame < 0) {
            desyncFrame = frame;
            LogError("net", "desync at frame %d", frame);
        }
        LogError("net", "frame %d differs:\n  here  %s\n  there %s", frame, a.ToString().c_str(),
                 b.ToString().c_str());
    }
    return same;
}

void Protocol::AddLocalSync(const SyncBlock& block)
{
    if (block.frame == (int)localSyncs_.size()) {
        localSyncs_.push_back(block);
        CheckSync(block.frame);
    }
}

void Protocol::SendInputs()
{
    if (phase != kPlaying)
        return;
    for (const net::Endpoint& e : GetRole(3))
        SendInputPlayer(ack_, 30, e);
}

// --- Sending

void Protocol::Send(net::MessageType type, const net::Writer& message, const net::Endpoint& to)
{
    std::string packet = net::Pack(type, message);
    if (packet.size() >= net::kMaxPacket) {
        LogError("net", "message type %d too large (%u bytes)", type, (unsigned)packet.size());
        return;
    }
    if (settings_.lagMs > 0 || settings_.jitterMs > 0) {
        uint32_t wait = settings_.lagMs + (settings_.jitterMs > 0 ? rand() % (settings_.jitterMs + 1) : 0);
        // In order, as a link delays them: never before the one sent last.
        uint32_t due = Now() + wait;
        std::lock_guard<std::mutex> lock(mutex_);
        if (!delayed_.empty() && (int32_t)(delayed_.back().due - due) > 0)
            due = delayed_.back().due;
        delayed_.push_back(Delayed{due, to, packet});
        return;
    }
    if (!socket_.SendTo(packet.data(), packet.size(), to))
        LogDebug("net", "can't send to %s", to.ToString().c_str());
}

void Protocol::StartThread()
{
    StopThread();
    {
        std::lock_guard<std::mutex> lock(mutex_);
        inbox_.clear();
    }
    stopThread_ = false;
    thread_ = std::thread([this] { ThreadMain(); });
}

void Protocol::StopThread()
{
    if (!thread_.joinable())
        return;
    stopThread_ = true;
    thread_.join();
}

// The socket's thread: every datagram into the inbox with the time it came, a ping
// answered first (ProtocolContext::receivePing's reply), and Settings::lagMs's waiting
// datagrams sent when due.
void Protocol::ThreadMain()
{
    static unsigned char buffer[0x10000];
    while (!stopThread_) {
        if (socket_.Wait(2)) {
            net::Endpoint from;
            int n;
            while (!stopThread_ && (n = socket_.Receive(buffer, sizeof(buffer), &from)) >= 0) {
                Incoming in;
                in.at = Now();
                in.from = from;
                in.packet.assign((const char*)buffer, (size_t)n);
                in.ponged = false;
                int type;
                std::string body;
                net::Reader m;
                if (n >= 2 && buffer[1] == net::kPing && net::Unpack(buffer, (size_t)n, &type, &body) &&
                    m.Parse((const unsigned char*)body.data(), body.size())) {
                    net::Writer pong;
                    pong.Varint(3, m.U32(3));
                    Send(net::kPong, pong, from);
                    in.ponged = true;
                }
                std::lock_guard<std::mutex> lock(mutex_);
                // A flood is dropped rather than kept: the game reads the inbox each frame.
                if (inbox_.size() < 4096)
                    inbox_.push_back(std::move(in));
            }
        }
        FlushDelayed(false);
    }
}

void Protocol::FlushDelayed(bool all)
{
    std::lock_guard<std::mutex> lock(mutex_);
    uint32_t now = Now();
    while (!delayed_.empty() && (all || (int32_t)(now - delayed_.front().due) >= 0)) {
        socket_.SendTo(delayed_.front().packet.data(), delayed_.front().packet.size(),
                       delayed_.front().to);
        delayed_.pop_front();
    }
}

// The host's answer: the version, the client's side, the seed, both names.
void Protocol::SendConnectConfirm(int role, const net::Endpoint& to)
{
    net::Writer m;
    m.Varint(1, 0);
    m.Varint(2, 0);
    m.Varint(3, kRevivalVersion);
    m.Varint(4, role);
    m.Varint(5, remotePlayer);
    m.Varint(6, seed);
    std::string n1 = Utf16Bytes(names[0], 128), n2 = Utf16Bytes(names[1], 128);
    m.Bytes(7, n1.data(), n1.size());
    m.Bytes(8, n2.data(), n2.size());
    m.Varint(9, practiceKeys);
    Send(net::kInit, m, to);
}

void Protocol::SendConnectRequest(int role, const net::Endpoint& to)
{
    net::Writer m;
    m.Varint(1, 1);
    m.Varint(2, 0);
    m.Varint(3, kRevivalVersion);
    m.Varint(4, role);
    m.Varint(5, localPlayer);
    m.Varint(6, 0);
    std::string name = Utf16Bytes(settings_.name.substr(0, 20), 0);
    m.Bytes(7, name.data(), name.size());
    m.Varint(9, practiceKeys);
    Send(net::kInit, m, to);
}

void Protocol::SendDone(int player, const net::Endpoint& to)
{
    net::Writer m;
    m.Varint(1, player);
    Send(net::kDone, m, to);
}

void Protocol::SendDoneToPlayers()
{
    for (const net::Endpoint& e : GetFlagged(2))
        SendDone(0, e);
}

// The local inputs from `frame` on, at most `count`, with the last remote frame received.
void Protocol::SendInputPlayer(int frame, int count, const net::Endpoint& to)
{
    const std::vector<FrameInput>& local = inputs[localPlayer];
    if (frame < 0 || frame >= (int)local.size())
        return;
    count = std::min(std::min(count, 60), (int)local.size() - frame);
    net::Writer m;
    m.Varint(1, 0);
    m.Int32(2, (int32_t)inputs[remotePlayer].size() - 1);
    m.Varint(3, (uint32_t)frame);
    for (int i = frame; i < frame + count; i++)
        m.Bytes(5, &local[i], 2);
    Send(net::kInput, m, to);
}

void Protocol::SendPing(const net::Endpoint& to)
{
    net::Writer m;
    m.Varint(3, Now());
    Send(net::kPing, m, to);
}

void Protocol::SendQuit(const net::Endpoint& to)
{
    net::Writer m;
    m.Varint(1, 0);
    Send(net::kQuit, m, to);
}

void Protocol::SendQuitAll()
{
    for (const Peer& p : peers_)
        SendQuit(p.endpoint);
}

// The local sync records from frame - before to frame + after.
void Protocol::SendSync(int frame, int before, int after, const net::Endpoint& to)
{
    if (localSyncs_.empty())
        return;
    int first = std::max(0, frame - before);
    int last = std::min((int)localSyncs_.size() - 1, frame + after);
    if (last < first)
        return;
    net::Writer m;
    m.Varint(1, 0);
    for (int i = first; i <= last; i++)
        m.Bytes(4, &localSyncs_[i], sizeof(SyncBlock));
    Send(net::kSync, m, to);
}

void Protocol::SendSyncRequest(int count, const net::Endpoint& to)
{
    net::Writer m;
    m.Varint(1, 1);
    m.Varint(2, (uint32_t)(checkedFrame + 1));
    m.Varint(3, (uint32_t)count);
    Send(net::kSync, m, to);
}

} // namespace netplay
} // namespace efz
