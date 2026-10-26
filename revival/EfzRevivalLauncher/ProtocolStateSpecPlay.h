// Watching a match: efz.exe runs as a spectator with the inputs received from the
// host (or from the spectator it was redirected to), and passes them on to the
// spectators connecting to this one. 0x28 bytes.
#pragma once
#include "ProtocolState.h"

class ProtocolStateSpecPlay : public ProtocolState {
public:
    ProtocolStateSpecPlay();
    ~ProtocolStateSpecPlay();
    void enter(ProtocolContext &context);
    void leave(ProtocolContext &context);
    void receiveConnectRequest(ProtocolContext &context, int game, int version, int role,
                               std::wstring name, bool practiceKeys, const Endpoint &from);
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
};
