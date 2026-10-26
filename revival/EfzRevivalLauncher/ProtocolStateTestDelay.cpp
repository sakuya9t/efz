// Measuring the round trip and choosing the input delay.
#include "ProtocolStateTestDelay.h"
// OBJECT: 0x448010 0x44a5d0
#include "ProtocolContext.h"
#include "ProtocolStateEnd.h"
#include "ProtocolStatePlay.h"
#include <algorithm>
#include <cmath>
#include <numeric>

// Thunks whose link copies are other objects' (the same bytes as thunks here):
// FUNCTION: 0x4171e0 ??G?$_Deque_unchecked_iterator@V?$_Deque_val@U?$_Deque_simple_types@H@std@@@std@@@std@@QBEHABV?$_Deque_unchecked_const_iterator@V?$_Deque_val@U?$_Deque_simple_types@H@std@@@std@@@1@@Z
// FUNCTION: 0x4245a0 ?allocate@?$_Wrap_alloc@V?$allocator@H@std@@@std@@QAEPAHI@Z

// FUNCTION: 0x449390
ProtocolStateTestDelay::ProtocolStateTestDelay()
    : pongs_(0), minimum_(0)
{
    recommended_ = 0;
    chosen_ = false;
}

// FUNCTION: 0x4493c0
ProtocolStateTestDelay::~ProtocolStateTestDelay()
{
}

// Frames of a one-way trip at 64 frames a second, less what rollback absorbs.
// FUNCTION: 0x4495e0
int ProtocolStateTestDelay::computeMinimumDelay(float ping, float rollback)
{
    double frames = std::ceil(ping / (2 * (1000.0 / 64)));
    double delay = std::max(0.0, frames - rollback);
    return (int)delay;
}

// FUNCTION: 0x449650
int ProtocolStateTestDelay::computeRecommendedDelay(float ping, float rollback)
{
    float rollbackUsed = std::min(3.0f, rollback);
    int minimum = std::max(minimum_, 0);
    double frames = std::ceil(ping / (2 * (1000.0 / 64)));
    int delay = std::max(minimum, (int)std::ceil(frames - rollbackUsed));
    return rollback == rollbackUsed ? delay + 1 : delay;
}

// FUNCTION: 0x449710
void ProtocolStateTestDelay::enter(ProtocolContext &context)
{
    context.startPingTimer(200);
    context.startTimeoutTimer(1000);
    context.doAlert();
    console_ << "Measuring Delay\n";
}

// The opponent asking again is confirmed again; anyone else is turned away.
// FUNCTION: 0x449dd0
void ProtocolStateTestDelay::receiveConnectRequest(ProtocolContext &context, int, int, int role,
                                                   std::wstring name, bool, const Endpoint &from)
{
    switch (role) {
    case 1:
        if (context.peers.flagged(from, 3)) {
            context.log << "Received delay connect\n";
            context.sendConnectConfirm(1, from);
            break;
        }
    case 2:
        if (context.config.allowSpectating)
            context.sendChangeRole(2, from);
        else
            context.sendDone(1, from);
        break;
    }
}

// FUNCTION: 0x449cd0
bool ProtocolStateTestDelay::isValidDelay(const std::string &text)
{
    int delay;
    try {
        delay = std::stoi(text);
    } catch (std::exception e) {
        console_ << "\nInvalid delay\n";
        return false;
    }
    if (delay >= minimum_ && delay <= 20)
        return true;
    console_ << "\nDelay must be between " << minimum_ << " and 20\n";
    return false;
}

// FUNCTION: 0x44a4f0
void ProtocolStateTestDelay::suggestDelay(ProtocolContext &context)
{
    console_.clear();
    console_ << "The input delay can always be adjusted during the actual match.\nAverage Ping: "
             << context.ping.average << "\n" << "Min Ping: " << context.ping.minimum << "\n"
             << "Max Ping: " << context.ping.maximum << "\n" << "Recommended input delay: "
             << recommended_ << "\n" << "Enter the initial input delay (between ) " << minimum_
             << " and 20, none for recommended): ";
}

// FUNCTION: 0x449c00
void ProtocolStateTestDelay::handleTimeout(ProtocolContext &context, const Endpoint &peer)
{
    if (context.peers.flagged(peer, 3)) {
        console_ << "\nRemote timed out\n";
        context.switchState(std::unique_ptr<ProtocolStateEnd>(new ProtocolStateEnd()));
    }
}

// A line with only Enter takes the recommended delay.
// FUNCTION: 0x4498e0
void ProtocolStateTestDelay::handleCommand(ProtocolContext &context, std::string command)
{
    if (command.compare(std::string("\r\n")) == 0) {
        context.info.delay = recommended_;
        chosen_ = true;
        std::vector<Endpoint> peers = context.peers.getFlagged(2);
        for (Endpoint peer : peers)
            context.sendDone(0, peer);
        context.startResendTimer(100);
        console_ << "Waiting for remote player\n";
    } else if (isValidDelay(command)) {
        context.info.delay = std::stoi(command);
        chosen_ = true;
        std::vector<Endpoint> peers = context.peers.getFlagged(2);
        for (Endpoint peer : peers)
            context.sendDone(0, peer);
        context.startResendTimer(100);
        console_ << "Waiting for remote player\n";
    } else {
        console_ << "Enter the input delay to use: ";
        context.startConsole(ENABLE_PROCESSED_INPUT | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT |
                             ENABLE_EXTENDED_FLAGS, ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
    }
}
// FUNCTION: 0x449b10
void ProtocolStateTestDelay::handleResendTimer(ProtocolContext &context)
{
    std::vector<Endpoint> peers = context.peers.getFlagged(2);
    for (Endpoint peer : peers)
        context.sendDone(0, peer);
}

// FUNCTION: 0x449da0
void ProtocolStateTestDelay::leave(ProtocolContext &context)
{
    context.stopPingTimer();
    context.stopTimeoutTimer();
    context.stopConsole();
    context.stopResendTimer();
}

// FUNCTION: 0x449e70
void ProtocolStateTestDelay::receiveDone(ProtocolContext &context, int player, const Endpoint &)
{
    if (player == 0 && chosen_) {
        std::vector<Endpoint> peers = context.peers.getFlagged(2);
        for (Endpoint peer : peers)
            context.sendDone(0, peer);
        context.switchState(std::unique_ptr<ProtocolStatePlay>(new ProtocolStatePlay()));
    }
}

// Inputs mean the opponent has started already.
// FUNCTION: 0x449fd0
void ProtocolStateTestDelay::receiveInput(ProtocolContext &context, int, int,
                                          std::deque<FrameInput> inputs, const Endpoint &from)
{
    receiveDone(context, 0, from);
}

// After 20 replies: the ping is the 90th percentile of the round trips, the average
// that of the ones below it.
// FUNCTION: 0x44a030
void ProtocolStateTestDelay::receivePong(ProtocolContext &context, const Endpoint &from)
{
    if (!context.peers.flagged(from, 3))
        return;
    if (pongs_ == 20) {
        minimum_ = computeMinimumDelay(context.ping.average, context.info.rollback);
        std::deque<int> sorted(context.pings.size());
        std::copy(context.pings.begin(), context.pings.end(), sorted.begin());
        std::sort(sorted.begin(), sorted.end());
        int index = (int)std::min(std::max(0.0, sorted.size() * 0.9 - 1.0), sorted.size() - 1.0);
        context.ping.maximum = sorted[index];
        context.ping.average = std::accumulate(sorted.begin(), sorted.begin() + index, 0) / index;
        recommended_ = computeRecommendedDelay(sorted[index], context.info.rollback);
        suggestDelay(context);
        context.startConsole(ENABLE_PROCESSED_INPUT | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT |
                             ENABLE_EXTENDED_FLAGS, ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
    }
    pongs_++;
}

// FUNCTION: 0x44a260
void ProtocolStateTestDelay::receivePunch(ProtocolContext &context, const Endpoint &target,
                                          const Endpoint &)
{
    context.log << "Redirected to " << target << "\n";
    context.log.flush();
    static int redirects = 0;
    context.sendPing(Endpoint(target.address(), target.port() + redirects++));
    redirects %= 10;
}
