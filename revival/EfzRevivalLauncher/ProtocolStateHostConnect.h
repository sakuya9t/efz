// Hosting: wait for a player (or spectators) to connect, then test the delay.
// 0x28 bytes.
#pragma once
#include "ProtocolState.h"

class ProtocolStateHostConnect : public ProtocolState {
public:
    ProtocolStateHostConnect();
    ~ProtocolStateHostConnect();
    void enter(ProtocolContext &context);
    void leave(ProtocolContext &context);
    void receiveConnectRequest(ProtocolContext &context, int game, int version, int role,
                               std::wstring name, bool practiceKeys, const Endpoint &from);
    void receivePunch(ProtocolContext &context, const Endpoint &target, const Endpoint &from);
    void handleCommand(ProtocolContext &context, std::string command);
};
