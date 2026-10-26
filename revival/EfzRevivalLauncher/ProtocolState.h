// A state of the netplay protocol. ProtocolContext owns the current state, forwards
// every received message, timer and console command to it, and switches states with
// setState. The defaults ignore everything.
//
// The vtable (0x49a89c, 25 slots) is in declaration order; each state's functions are
// laid out in the order of their decorated names, which constrains the names: enter <
// handleCommand < handleGameTimer < handleQueueEvent < handleResendTimer <
// handleTimeout < leave < receive* (the messages in alphabetical order).
#pragma once
#include <boost/asio.hpp>
#include "Console.h"
#include <deque>
#include <string>

class ProtocolContext;
struct FrameInput;
struct ColorPalette;
struct SyncBlock;

class ProtocolState {
public:
    typedef boost::asio::ip::udp::endpoint Endpoint;

    ProtocolState();
    virtual ~ProtocolState();
    virtual ProtocolState &operator=(ProtocolState &&other);
    // Called by setState on the new state, and on the old one when it is replaced.
    virtual void enter(ProtocolContext &context);
    virtual void leave(ProtocolContext &context);
    // MessageInit, the request a joining client or spectator sends (field 1 = 1) and
    // the host's confirmation (field 1 = 0).
    virtual void receiveConnectRequest(ProtocolContext &context, int game, int version,
                                       int role, std::wstring name, bool practiceKeys,
                                       const Endpoint &from);
    virtual void receiveConnectConfirm(ProtocolContext &context, int game, int version,
                                       int player, int role, int seed, std::wstring name1,
                                       std::wstring name2, bool practiceKeys,
                                       const Endpoint &from);
    virtual void receiveChangeRole(ProtocolContext &context, int role, const Endpoint &from);
    virtual void receivePing(ProtocolContext &context, const Endpoint &from);
    virtual void receivePong(ProtocolContext &context, const Endpoint &from);
    // MessageInput: an acknowledgement of the inputs up to a frame (field 1 = 1), or
    // inputs from a frame on (field 1 = 0).
    virtual void receiveInputAck(ProtocolContext &context, int frame, int count,
                                 const Endpoint &from);
    virtual void receiveInput(ProtocolContext &context, int ack, int frame,
                              std::deque<FrameInput> inputs, const Endpoint &from);
    virtual void receiveQuit(ProtocolContext &context, const Endpoint &from);
    virtual void receivePalette(ProtocolContext &context, const ColorPalette &palette, int player,
                                const Endpoint &from);
    virtual void receiveSync(ProtocolContext &context, const std::deque<SyncBlock> &blocks,
                             const Endpoint &from);
    virtual void receiveSyncRequest(ProtocolContext &context, int frame, int count,
                                    const Endpoint &from);
    virtual void receiveRedirect(ProtocolContext &context, const Endpoint &target,
                                 const Endpoint &from);
    virtual void receiveDone(ProtocolContext &context, int player, const Endpoint &from);
    virtual void receivePunch(ProtocolContext &context, const Endpoint &target,
                              const Endpoint &from);
    // Never overridden, never called from the launcher's own code that is known.
    virtual void handleTimer(ProtocolContext &context);
    // A peer was not heard from for 8 seconds (checked by the timeout timer).
    virtual void handleTimeout(ProtocolContext &context, const Endpoint &peer);
    // ProtocolContext's three general timers, and the event of the input queue the
    // game writes.
    virtual void handleResendTimer(ProtocolContext &context);
    virtual void handleGameTimer(ProtocolContext &context);
    virtual void handleQueueEvent(ProtocolContext &context);
    // A line typed on the console.
    virtual void handleCommand(ProtocolContext &context, std::string command);
    // Whether the session is over (only ProtocolStateEnd).
    virtual bool isOver();

protected:
    Console console_;
};
