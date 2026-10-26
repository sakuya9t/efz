// Playing a match.
#include "ProtocolStatePlay.h"
// OBJECT: 0x445870 0x4465d0
#include "ProtocolContext.h"
#include "ProtocolStateEnd.h"
#include <algorithm>

// FUNCTION: 0x445a30
ProtocolStatePlay::ProtocolStatePlay()
    : ack_(0)
{
}

// FUNCTION: 0x445a50
ProtocolStatePlay::~ProtocolStatePlay()
{
}

// FUNCTION: 0x445b60
void ProtocolStatePlay::enter(ProtocolContext &context)
{
    console_.clear();
    context.provideInit(context.info);
    context.launch("efz.exe", "EfzRevival.dll", 0);
    context.startPingTimer(200);
    context.startGameTimer(200);
    context.startTimeoutTimer(1000);
    context.startResendTimer(80);
    context.startQueueEvent();
}

// FUNCTION: 0x445c60
void ProtocolStatePlay::handleGameTimer(ProtocolContext &context)
{
    if (!context.isGameRunning()) {
        context.log << "Efz died\n";
        context.sendQuitAll();
        console_ << "\nEfz died\n";
        context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
    }
}

// FUNCTION: 0x445d40
void ProtocolStatePlay::handleQueueEvent(ProtocolContext &context)
{
    int player = context.localPlayer;
    context.consumeInput(player);
    context.consumeLoadMatch();
    std::vector<Endpoint> peers = context.peers.getRole(3);
    for (Endpoint peer : peers)
        context.sendInput(ack_, 30, peer);
    ColorPalette palette;
    if (context.consumePalette(palette, player)) {
        context.sendPalette(palette, player, 3);
        context.sendPalette(palette, player, 1);
    }
    context.consumeSync();
}

// FUNCTION: 0x445ea0
void ProtocolStatePlay::handleResendTimer(ProtocolContext &context)
{
    if (context.debug()) {
        std::vector<Endpoint> peers = context.peers.getFlagged(2);
        for (Endpoint peer : peers)
            context.sendSyncRequest(10, peer);
    }
}

// FUNCTION: 0x445fa0
void ProtocolStatePlay::handleTimeout(ProtocolContext &context, const Endpoint &peer)
{
    if (context.peers.flagged(peer, 2)) {
        context.log << "Source " << peer << " died\n";
        console_ << "\nSource quit or timed out\n";
        context.sendQuitAll();
        context.peers.remove(peer);
        context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
    } else {
        context.log << peer << " died\n";
        context.peers.remove(peer);
    }
}

// FUNCTION: 0x4460e0
void ProtocolStatePlay::leave(ProtocolContext &context)
{
    context.stopPingTimer();
    context.stopTimeoutTimer();
    context.stopGameTimer();
    context.stopQueueEvent();
    context.stopResendTimer();
    context.closeGame();
}

// A spectator joining a match in progress is added, unless three are watching already:
// then it is sent to watch one of them at random.
// FUNCTION: 0x446130
void ProtocolStatePlay::receiveConnectRequest(ProtocolContext &context, int game, int version,
                                              int role, std::wstring, bool,
                                              const Endpoint &from)
{
    if (context.isValidGame(game) && context.isValidVersion(version)) {
        if (context.hosting && !context.config.allowSpectating)
            context.sendDone(1, from);
        if (role == 1) {
            context.log << "Already playing propose to spec\n";
            context.sendChangeRole(2, from);
        } else if (role == 2) {
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
        context.log << "Wrong game version\n";
        context.sendConnectConfirm(role, from);
    }
}

// FUNCTION: 0x446330
void ProtocolStatePlay::receiveInput(ProtocolContext &context, int ack, int frame,
                                     std::deque<FrameInput> inputs, const Endpoint &)
{
    ack_ = ack + 1;
    int player = context.remotePlayer;
    int next = frame;
    for (FrameInput input : inputs) {
        if (next == context.inputs[player].size())
            context.provideInput(input, player);
        next++;
    }
}

// Shared with ProtocolStateSpecPlay.
// FUNCTION: 0x446400
void ProtocolStatePlay::receiveInputAck(ProtocolContext &context, int frame, int count,
                                        const Endpoint &from)
{
    int last = std::min(context.inputs[0].size(), context.inputs[1].size()) - 1;
    if (frame <= last)
        context.sendInput(frame, count, from);
}

// FUNCTION: 0x446450
void ProtocolStatePlay::receivePalette(ProtocolContext &context, const ColorPalette &palette,
                                       int player, const Endpoint &)
{
    if (player != context.localPlayer) {
        context.providePalette(palette, player);
        context.sendPalette(palette, player, 1);
    }
}

// FUNCTION: 0x446480
void ProtocolStatePlay::receivePong(ProtocolContext &context, const Endpoint &from)
{
    if (context.peers.flaggedAs(from, 3))
        context.provideNet(context.ping);
}

// FUNCTION: 0x4464b0
void ProtocolStatePlay::receivePunch(ProtocolContext &context, const Endpoint &target,
                                     const Endpoint &)
{
    context.log << "Redirected to " << target << "\n";
    context.log.flush();
    static int redirects = 0;
    context.sendPing(Endpoint(target.address(), target.port() + redirects++));
    redirects %= 10;
}

// FUNCTION: 0x446550
void ProtocolStatePlay::receiveQuit(ProtocolContext &context, const Endpoint &from)
{
    context.log << "Recv quit from: " << from << "\n";
    handleTimeout(context, from);
}

// FUNCTION: 0x4465a0
void ProtocolStatePlay::receiveRedirect(ProtocolContext &context, const Endpoint &target,
                                        const Endpoint &)
{
    context.sendNatTraversal(target.port(), target.port() + 50, target);
}
