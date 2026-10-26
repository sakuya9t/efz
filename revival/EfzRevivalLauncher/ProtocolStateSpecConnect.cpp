// Joining a host as a spectator.
#include "ProtocolStateSpecConnect.h"
// OBJECT: 0x4465d0 0x4476a0
#include "ProtocolContext.h"
#include "ProtocolStateClientConnect.h"
#include "ProtocolStateEnd.h"
#include "ProtocolStateSpecPlay.h"
#include <cstdlib>

// FUNCTION: 0x446660
ProtocolStateSpecConnect::ProtocolStateSpecConnect()
    : inputMode_(0x80), outputMode_(0), requests_(0), waiting_(false), connected_(false)
{
}

// FUNCTION: 0x446690
ProtocolStateSpecConnect::~ProtocolStateSpecConnect()
{
}

// FUNCTION: 0x4466d0
void ProtocolStateSpecConnect::enter(ProtocolContext &context)
{
    Endpoint target = context.peers.target;
    console_ << "Connecting to \"" << target.address().to_string().data() << " on port "
             << target.port() << "\"\n";
    std::vector<Endpoint> hosts = context.peers.getFlagged(2);
    for (Endpoint host : hosts)
        context.peers.remove(host);
    context.peers.add(target, 2);
    context.startResendTimer(500);
    context.startPingTimer(1000);
    context.startTimeoutTimer(5000);
    if (!context.config.allowSpectating) {
        console_ << "Spectating has been disabled in EfzRevival.ini\n";
        context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
    }
}

// FUNCTION: 0x446cd0
void ProtocolStateSpecConnect::leave(ProtocolContext &context)
{
    context.stopResendTimer();
    context.stopPingTimer();
    context.stopTimeoutTimer();
    context.stopConsole();
}

// FUNCTION: 0x446900
void ProtocolStateSpecConnect::handleCommand(ProtocolContext &context, std::string command)
{
    switch (atoi(command.c_str())) {
    case 1:
        context.switchState(std::unique_ptr<ProtocolStateClientConnect>(new ProtocolStateClientConnect()));
        break;
    case 2:
        context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
        break;
    case 3:
        context.startResendTimer(500);
        waiting_ = true;
        console_ << "\nWaiting for game to begin\n";
        break;
    default:
        context.startConsole(inputMode_, outputMode_);
        break;
    }
}

// Asks every known host; after 10 unanswered requests per host, starts over with the
// one given on the command line.
// FUNCTION: 0x446a60
void ProtocolStateSpecConnect::handleResendTimer(ProtocolContext &context)
{
    std::vector<Endpoint> hosts = context.peers.getFlagged(2);
    for (Endpoint host : hosts) {
        requests_++;
        context.sendConnectRequest(2, host);
        if (!connected_)
            context.sendPunch(host, context.config.holePunchingServer);
    }
    if (requests_ >= hosts.size() * 10) {
        for (Endpoint host : hosts)
            context.peers.remove(host);
        context.peers.add(context.peers.target, 2);
    }
}

// FUNCTION: 0x446c00
void ProtocolStateSpecConnect::handleTimeout(ProtocolContext &context, const Endpoint &peer)
{
    if (context.peers.target == peer) {
        console_ << "Host timed out\n";
        context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
    }
}

// FUNCTION: 0x446d00
void ProtocolStateSpecConnect::receiveChangeRole(ProtocolContext &context, int role,
                                                 const Endpoint &from)
{
    if (from.address() == context.peers.target.address()) {
        if (from.port() != context.peers.target.port())
            context.peers.target = from;
    }
    connected_ = true;
    std::vector<Endpoint> hosts = context.peers.getRole(2);
    for (Endpoint host : hosts)
        context.peers.remove(host);
    context.peers.add(from, 2);
    if (role == 1) {
        if (!waiting_) {
            console_.clear();
            console_ << "Host not yet playing, join as a player?\n";
            console_ << 1 << ": Yes\n";
            console_ << 2 << ": No\n";
            console_ << 3 << ": Wait as a spectator for the game to begin.\n";
            context.stopResendTimer();
            context.startConsole(inputMode_, outputMode_);
        }
    } else if (role == 2) {
        if (!waiting_) {
            waiting_ = true;
            console_ << "\nWaiting for game to begin\n";
        }
    }
}

// FUNCTION: 0x446f10
void ProtocolStateSpecConnect::receiveConnectConfirm(ProtocolContext &context, int game,
                                                     int version, int player, int role, int seed,
                                                     std::wstring name1, std::wstring name2,
                                                     bool practiceKeys, const Endpoint &from)
{
    if (role != 2)
        return;
    context.log << "Receive connect confirm " << from << "\n";
    if (!context.isValidGame(game))
        return;
    if (!context.isValidVersion(version)) {
        context.doAlert();
        if (context.isUpdateAvailable(version)) {
            console_.clear();
            console_ << "New version available, please update\n\n";
            context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
        } else {
            console_.clear();
            console_ << "Remote is using a deprecated version\n\n";
            context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
        }
        context.log << "Wrong game or version\n";
        return;
    }
    if (from.address() == context.peers.target.address()) {
        if (from.port() != context.peers.target.port())
            context.peers.target = from;
    }
    connected_ = true;
    std::vector<Endpoint> hosts = context.peers.getRole(2);
    for (Endpoint host : hosts)
        context.peers.remove(host);
    context.peers.add(from, 2);
    context.setPlayer(player);
    context.info.seed = seed;
    context.setPlayerName(name1, 0);
    context.setPlayerName(name2, 1);
    context.info.practiceKeys = context.info.practiceKeys && practiceKeys;
    context.switchState(std::unique_ptr<ProtocolStateSpecPlay>(new ProtocolStateSpecPlay()));
}

// FUNCTION: 0x447260
void ProtocolStateSpecConnect::receiveDone(ProtocolContext &context, int player,
                                           const Endpoint &from)
{
    if (context.peers.target != from || player != 1)
        return;
    console_ << "Spectators have been disabled by the host\n";
    context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
}

// FUNCTION: 0x447330
void ProtocolStateSpecConnect::receivePing(ProtocolContext &context, const Endpoint &from)
{
    if (!connected_) {
        if (from.address() == context.peers.target.address()) {
            context.peers.remove(context.peers.target);
            context.peers.target = from;
        }
        context.peers.add(from, 2);
        connected_ = true;
    }
}

// FUNCTION: 0x4473a0
void ProtocolStateSpecConnect::receivePunch(ProtocolContext &context, const Endpoint &target,
                                            const Endpoint &)
{
    if (!connected_) {
        context.log << "Redirected to " << target << "\n";
        context.log.flush();
        static int redirects = 0;
        context.sendConnectRequest(2, Endpoint(target.address(), target.port() + redirects++));
        redirects %= 10;
    } else {
        context.log << "Requested hole punching to " << target << "\n";
        context.log.flush();
        static int punches = 0;
        context.sendPing(Endpoint(target.address(), target.port() + punches++));
        punches %= 10;
    }
}

// The host has enough spectators and sends this one to watch another spectator.
// FUNCTION: 0x4474e0
void ProtocolStateSpecConnect::receiveRedirect(ProtocolContext &context, const Endpoint &target,
                                               const Endpoint &from)
{
    if (context.peers.flaggedAs(from, 2)) {
        std::vector<Endpoint> hosts = context.peers.getRole(2);
        for (Endpoint host : hosts)
            context.peers.remove(host);
        context.log << "Redirected to " << target << " send from " << target.port() << "\n";
        Endpoint sink = target;
        context.peers.add(sink, 2);
        context.log << "Send connect request to " << sink << "\n";
        connected_ = false;
        context.sendPunch(target, context.config.holePunchingServer);
        context.sendConnectRequest(2, sink);
    }
}
