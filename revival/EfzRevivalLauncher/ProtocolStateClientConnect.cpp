// Joining a host as a player.
#include "ProtocolStateClientConnect.h"
// OBJECT: 0x444660 0x445280
#include "ProtocolContext.h"
#include "ProtocolStateEnd.h"
#include "ProtocolStateSpecConnect.h"
#include "ProtocolStateTestDelay.h"
#include <cstdlib>

// FUNCTION: 0x444750
ProtocolStateClientConnect::ProtocolStateClientConnect()
    : inputMode_(0x80), outputMode_(0x80)
{
}

// FUNCTION: 0x444780
ProtocolStateClientConnect::~ProtocolStateClientConnect()
{
}

// FUNCTION: 0x444940
void ProtocolStateClientConnect::enter(ProtocolContext &context)
{
    Endpoint target = context.peers.target;
    console_ << "Connecting to \"" << target.address().to_string().data() << " on port "
             << target.port() << "\"\n";
    context.peers.clear();
    context.peers.add(target, 2);
    connected_ = false;
    context.startPingTimer(500);
    context.startResendTimer(500);
    context.startTimeoutTimer(5000);
}

// FUNCTION: 0x444d70
void ProtocolStateClientConnect::receiveConnectConfirm(ProtocolContext &context, int game,
                                                       int version, int player, int, int seed,
                                                       std::wstring name1, std::wstring name2,
                                                       bool practiceKeys, const Endpoint &from)
{
    if (context.peers.target.address() != from.address())
        return;
    connected_ = true;
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
    } else {
        context.peers.remove(context.peers.target);
        context.peers.target = from;
        context.peers.add(context.peers.target, 2);
        context.setPlayer(player);
        context.info.seed = seed;
        context.setPlayerName(name1, 0);
        context.setPlayerName(name2, 1);
        context.info.practiceKeys = context.info.practiceKeys && practiceKeys;
        context.sendConnectConfirm(1, from);
        context.peers.add(from, 3);
        context.switchState(std::unique_ptr<ProtocolStateTestDelay>(new ProtocolStateTestDelay()));
    }
}

// FUNCTION: 0x444be0
void ProtocolStateClientConnect::handleTimeout(ProtocolContext &context, const Endpoint &)
{
    console_ << "\nConnection timed out\n";
    context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
}

// FUNCTION: 0x444cc0
void ProtocolStateClientConnect::receiveChangeRole(ProtocolContext &context, int role,
                                                   const Endpoint &from)
{
    context.peers.remove(context.peers.target);
    context.peers.target = from;
    context.peers.add(context.peers.target, 2);
    connected_ = true;
    if (role == 2) {
        context.stopResendTimer();
        console_.clear();
        console_ << "Host already playing, join as a spectator?\n";
        console_ << 1 << ": Yes\n";
        console_ << 2 << ": No\n";
        context.startConsole(inputMode_, outputMode_);
    }
}

// FUNCTION: 0x444fe0
void ProtocolStateClientConnect::receiveDone(ProtocolContext &context, int player,
                                             const Endpoint &from)
{
    context.peers.remove(context.peers.target);
    context.peers.target = from;
    context.peers.add(context.peers.target, 2);
    connected_ = true;
    if (context.peers.target != from || player != 1)
        return;
    console_ << "Already playing, spectators have been disabled by the host\n";
    context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
}

// The hole punching server tells both sides where the other is; NAT may have mapped
// the other's port elsewhere, so each try goes to one of the next 10 ports.
// FUNCTION: 0x445140
void ProtocolStateClientConnect::receivePunch(ProtocolContext &context, const Endpoint &target,
                                              const Endpoint &)
{
    if (!connected_) {
        context.log << "Redirected to " << target << "\n";
        context.log.flush();
        static int redirects = 0;
        context.sendConnectRequest(1, Endpoint(target.address(), target.port() + redirects++));
        redirects %= 10;
    } else {
        context.log << "Requested hole punching to " << target << "\n";
        context.log.flush();
        static int punches = 0;
        context.sendPing(Endpoint(target.address(), target.port() + punches++));
        punches %= 10;
    }
}
// Folded with ProtocolStateSpecConnect::leave (0x446cd0).
void ProtocolStateClientConnect::leave(ProtocolContext &context)
{
    context.stopResendTimer();
    context.stopPingTimer();
    context.stopTimeoutTimer();
    context.stopConsole();
}

// FUNCTION: 0x444a60
void ProtocolStateClientConnect::handleCommand(ProtocolContext &context, std::string command)
{
    switch (atoi(command.c_str())) {
    case 1:
        context.switchState(std::unique_ptr<ProtocolStateSpecConnect>(new ProtocolStateSpecConnect()));
        break;
    case 2:
        context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
        break;
    default:
        context.startConsole(inputMode_, outputMode_);
        break;
    }
}

// FUNCTION: 0x444ba0
void ProtocolStateClientConnect::handleResendTimer(ProtocolContext &context)
{
    context.sendConnectRequest(1, context.peers.target);
    if (!connected_)
        context.sendPunch(context.peers.target, context.config.holePunchingServer);
}

// FUNCTION: 0x4450d0
void ProtocolStateClientConnect::receivePing(ProtocolContext &context, const Endpoint &from)
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
