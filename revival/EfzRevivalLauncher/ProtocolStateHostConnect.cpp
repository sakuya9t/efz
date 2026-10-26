// Waiting for a player to join.
#include "ProtocolStateHostConnect.h"
// OBJECT: 0x445300 0x445870
#include "ProtocolContext.h"
#include "ProtocolStateEnd.h"
#include "ProtocolStateTestDelay.h"
#include <cstdlib>

// FUNCTION: 0x4453b0
ProtocolStateHostConnect::ProtocolStateHostConnect()
{
}

// FUNCTION: 0x4453d0
ProtocolStateHostConnect::~ProtocolStateHostConnect()
{
}

// FUNCTION: 0x445410
void ProtocolStateHostConnect::enter(ProtocolContext &context)
{
    Endpoint local = context.peers.target;
    console_ << "Hosting using UDP " << (local.address().is_v4() ? "IPv4" : "IPv6")
             << " on port " << local.port() << "\n";
    console_ << "Press 2 to cancel.\n";
    context.hosting = true;
    context.peers.clear();
    context.startConsole(ENABLE_EXTENDED_FLAGS, 0);
    context.sendPing(context.config.holePunchingServer);
}

// FUNCTION: 0x4455b0
void ProtocolStateHostConnect::leave(ProtocolContext &context)
{
    context.stopConsole();
}

// FUNCTION: 0x4454e0
void ProtocolStateHostConnect::handleCommand(ProtocolContext &context, std::string command)
{
    switch (atoi(command.c_str())) {
    case 2:
        context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
        break;
    default:
        context.startConsole(ENABLE_EXTENDED_FLAGS, 0);
        break;
    }
}

// FUNCTION: 0x4455c0
void ProtocolStateHostConnect::receiveConnectRequest(ProtocolContext &context, int game,
                                                     int version, int role, std::wstring name,
                                                     bool practiceKeys, const Endpoint &from)
{
    if (!context.isValidGame(game))
        return;
    if (!context.isValidVersion(version)) {
        if (context.isUpdateAvailable(version)) {
            context.doAlert();
            console_.clear();
            console_ << "New version available, please update\n" << "\n";
            context.sendConnectConfirm(role, from);
            context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
        } else {
            context.sendConnectConfirm(role, from);
        }
        return;
    }
    switch (role) {
    case 1:
        context.info.practiceKeys = context.info.practiceKeys && practiceKeys;
        context.setPlayerName(context.name, context.localPlayer);
        context.setPlayerName(name, context.remotePlayer);
        context.peers.add(from, 3);
        context.sendConnectConfirm(1, from);
        context.switchState(std::unique_ptr<ProtocolStateTestDelay>(new ProtocolStateTestDelay()));
        break;
    case 2:
        if (context.config.allowSpectating)
            context.sendChangeRole(1, from);
        else
            context.sendDone(1, from);
        break;
    }
}

// FUNCTION: 0x4457d0
void ProtocolStateHostConnect::receivePunch(ProtocolContext &context, const Endpoint &target,
                                            const Endpoint &)
{
    context.log << "Redirected to " << target << "\n";
    context.log.flush();
    static int redirects = 0;
    context.sendPing(Endpoint(target.address(), target.port() + redirects++));
    redirects %= 10;
}
