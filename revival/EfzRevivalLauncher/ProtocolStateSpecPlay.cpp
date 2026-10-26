// Watching a match.
#include "ProtocolStateSpecPlay.h"
// OBJECT: 0x4476a0 0x448010
#include "ProtocolContext.h"
#include "ProtocolStateEnd.h"
#include "ProtocolStateSpecConnect.h"
#include <algorithm>

// FUNCTION: 0x447740
ProtocolStateSpecPlay::ProtocolStateSpecPlay()
{
}

// FUNCTION: 0x447760
ProtocolStateSpecPlay::~ProtocolStateSpecPlay()
{
}

// A spectator redirected to another keeps its running efz.exe.
// FUNCTION: 0x4477d0
void ProtocolStateSpecPlay::enter(ProtocolContext &context)
{
    console_.clear();
    if (!context.isGameRunning()) {
        context.log << "Launch initial Spec Efz\n";
        context.provideInit(context.info);
        context.launch("efz.exe", "EfzRevival.dll", 1);
    }
    context.startPingTimer(200);
    context.startGameTimer(200);
    context.startTimeoutTimer(1000);
    context.startResendTimer(64);
}

// FUNCTION: 0x4478c0
void ProtocolStateSpecPlay::handleGameTimer(ProtocolContext &context)
{
    if (!context.isGameRunning()) {
        context.log << "Efz died, quit\n";
        context.sendQuitAll();
        console_ << "\nEfz died\n";
        context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
    }
}

// Acknowledges the inputs received so far, which asks for the next 60 frames.
// FUNCTION: 0x4479a0
void ProtocolStateSpecPlay::handleResendTimer(ProtocolContext &context)
{
    context.consumeSync();
    std::vector<Endpoint> sources = context.peers.getFlagged(2);
    for (Endpoint source : sources) {
        context.sendInputAck(context.inputs[0].size(), 60, source);
        if (context.debug())
            context.sendSyncRequest(10, source);
    }
}

// FUNCTION: 0x447ab0
void ProtocolStateSpecPlay::handleTimeout(ProtocolContext &context, const Endpoint &peer)
{
    if (context.peers.flagged(peer, 2)) {
        context.log << "Source " << peer << " died, try reconnect\n";
        context.peers.remove(peer);
        context.switchState(std::unique_ptr<ProtocolStateSpecConnect>(new ProtocolStateSpecConnect()));
    } else {
        context.log << peer << " died\n";
        context.peers.remove(peer);
    }
}

// FUNCTION: 0x447bd0
void ProtocolStateSpecPlay::leave(ProtocolContext &context)
{
    context.stopPingTimer();
    context.stopTimeoutTimer();
    context.stopGameTimer();
    context.stopResendTimer();
}

// FUNCTION: 0x447c00
void ProtocolStateSpecPlay::receiveConnectRequest(ProtocolContext &context, int game,
                                                  int version, int role, std::wstring, bool,
                                                  const Endpoint &from)
{
    if (context.isValidGame(game) && context.isValidVersion(version)) {
        context.log << "Receive connect request from " << from << std::endl;
        if (role == 2) {
            std::vector<Endpoint> spectators = context.peers.getFlagged(1);
            if (spectators.size() >= 3 && !context.peers.flagged(from, 1)) {
                std::random_shuffle(spectators.begin(), spectators.end());
                Endpoint sink = spectators.front();
                context.log << "Already have sink, redirect " << from << " to " << sink << "\n";
                context.sendRedirect(sink, from);
            } else {
                context.log << "Free, add " << from << " as spectator\n";
                context.peers.add(from, 1);
                context.sendConnectConfirm(2, from);
            }
        }
    } else {
        context.sendConnectConfirm(role, from);
    }
}

// Folded with ProtocolStatePlay::receiveInputAck (0x446400).
void ProtocolStateSpecPlay::receiveInputAck(ProtocolContext &context, int frame, int count,
                                            const Endpoint &from)
{
    int last = std::min(context.inputs[0].size(), context.inputs[1].size()) - 1;
    if (frame <= last)
        context.sendInput(frame, count, from);
}

// Both players' inputs, alternating.
// FUNCTION: 0x447dd0
void ProtocolStateSpecPlay::receiveInput(ProtocolContext &context, int, int frame,
                                         std::deque<FrameInput> inputs, const Endpoint &)
{
    int next = frame;
    for (unsigned int i = 0; i < inputs.size(); i += 2) {
        if (next == context.inputs[0].size()) {
            context.provideInput(inputs[i], 0);
            context.provideInput(inputs[i + 1], 1);
        }
        next++;
    }
}

// FUNCTION: 0x447e80
void ProtocolStateSpecPlay::receivePalette(ProtocolContext &context, const ColorPalette &palette,
                                           int player, const Endpoint &)
{
    context.providePalette(palette, player);
    context.sendPalette(palette, player, 1);
}

// FUNCTION: 0x447eb0
void ProtocolStateSpecPlay::receivePunch(ProtocolContext &context, const Endpoint &target,
                                         const Endpoint &)
{
    context.log << "Redirected to " << target << "\n";
    context.log.flush();
    static int redirects = 0;
    context.sendPing(Endpoint(target.address(), target.port() + redirects++));
    redirects %= 10;
}

// FUNCTION: 0x447f50
void ProtocolStateSpecPlay::receiveQuit(ProtocolContext &context, const Endpoint &from)
{
    context.log << "Received quit from: " << from << "\n";
    handleTimeout(context, from);
}

// FUNCTION: 0x447fa0
void ProtocolStateSpecPlay::receiveRedirect(ProtocolContext &context, const Endpoint &target,
                                            const Endpoint &from)
{
    context.log << "Received redirect from " << from << ", send NAT traversal and wait for "
                << target << "\n";
    context.sendNatTraversal(target.port(), target.port() + 10, target);
}
