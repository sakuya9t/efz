// Before a match: ping the opponent 20 times, recommend an input delay from the round
// trip times (EFZ runs at 64 frames a second; rollback covers MaxRollback frames of it)
// and ask the player for one. Either side may answer; each sends MessageDone (player
// 0) when its player has chosen, and the match starts when both have. 0x38 bytes.
#pragma once
#include "ProtocolState.h"

class ProtocolStateTestDelay : public ProtocolState {
public:
    ProtocolStateTestDelay();
    ~ProtocolStateTestDelay();
    void enter(ProtocolContext &context);
    void leave(ProtocolContext &context);
    void receiveConnectRequest(ProtocolContext &context, int game, int version, int role,
                               std::wstring name, bool practiceKeys, const Endpoint &from);
    void receivePong(ProtocolContext &context, const Endpoint &from);
    void receiveInput(ProtocolContext &context, int ack, int frame,
                      std::deque<FrameInput> inputs, const Endpoint &from);
    void receiveDone(ProtocolContext &context, int player, const Endpoint &from);
    void receivePunch(ProtocolContext &context, const Endpoint &target, const Endpoint &from);
    void handleTimeout(ProtocolContext &context, const Endpoint &peer);
    void handleResendTimer(ProtocolContext &context);
    void handleCommand(ProtocolContext &context, std::string command);

private:
    // The delay that rollback alone cannot hide, and the one recommended.
    int computeMinimumDelay(float ping, float rollback);
    int computeRecommendedDelay(float ping, float rollback);
    bool isValidDelay(const std::string &text);
    void suggestDelay(ProtocolContext &context);

    int pongs_;         // 0x28
    int recommended_;   // 0x2c
    bool chosen_;       // 0x30
    int minimum_;       // 0x34
};
