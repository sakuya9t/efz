// A match between two players: efz.exe runs with EfzRevival.dll, which gives the local
// inputs through shared memory; they go to the opponent (and the spectators), and the
// opponent's come back the same way. Spectators that connect are added, or redirected
// to another spectator when there are enough. 0x2c bytes.
#pragma once
#include "ProtocolState.h"

class ProtocolStatePlay : public ProtocolState {
public:
    ProtocolStatePlay();
    ~ProtocolStatePlay();
    void enter(ProtocolContext &context);
    void leave(ProtocolContext &context);
    void receiveConnectRequest(ProtocolContext &context, int game, int version, int role,
                               std::wstring name, bool practiceKeys, const Endpoint &from);
    void receivePong(ProtocolContext &context, const Endpoint &from);
    void receiveInputAck(ProtocolContext &context, int frame, int count, const Endpoint &from);
    void receiveInput(ProtocolContext &context, int ack, int frame,
                      std::deque<FrameInput> inputs, const Endpoint &from);
    void receiveQuit(ProtocolContext &context, const Endpoint &from);
    void receivePalette(ProtocolContext &context, const ColorPalette &palette, int player,
                        const Endpoint &from);
    void receiveRedirect(ProtocolContext &context, const Endpoint &target, const Endpoint &from);
    void receivePunch(ProtocolContext &context, const Endpoint &target, const Endpoint &from);
    void handleTimeout(ProtocolContext &context, const Endpoint &peer);
    void handleResendTimer(ProtocolContext &context);
    void handleGameTimer(ProtocolContext &context);
    void handleQueueEvent(ProtocolContext &context);

private:
    int ack_;   // 0x28 the first frame the opponent has not acknowledged
};
