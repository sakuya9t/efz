// Joining a host as a player: send connection requests (and hole punching requests
// through the server) until the host confirms, then test the delay. If the host is
// already playing, offer to spectate instead. 0x34 bytes.
#pragma once
#include "ProtocolState.h"

class ProtocolStateClientConnect : public ProtocolState {
public:
    ProtocolStateClientConnect();
    ~ProtocolStateClientConnect();
    void enter(ProtocolContext &context);
    void leave(ProtocolContext &context);
    void receiveConnectConfirm(ProtocolContext &context, int game, int version, int player,
                               int role, int seed, std::wstring name1, std::wstring name2,
                               bool practiceKeys, const Endpoint &from);
    void receiveChangeRole(ProtocolContext &context, int role, const Endpoint &from);
    void receivePing(ProtocolContext &context, const Endpoint &from);
    void receiveDone(ProtocolContext &context, int player, const Endpoint &from);
    void receivePunch(ProtocolContext &context, const Endpoint &target, const Endpoint &from);
    void handleTimeout(ProtocolContext &context, const Endpoint &peer);
    void handleResendTimer(ProtocolContext &context);
    void handleCommand(ProtocolContext &context, std::string command);

private:
    DWORD inputMode_;   // 0x28 console modes for the question asked
    DWORD outputMode_;  // 0x2c
    bool connected_;    // 0x30 the host answered
};
