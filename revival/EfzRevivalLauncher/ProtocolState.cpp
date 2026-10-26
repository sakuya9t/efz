// The protocol states' base: a console of their own and empty handlers.
#include "ProtocolState.h"
// OBJECT: 0x444550 0x444660
#include "ProtocolContext.h"

// <system_error>'s categories, which every object here emits; their link copies are an
// earlier object's and the last one's, and the state constructors have the same bytes.
// FUNCTION: 0x405f90 ??0_Generic_error_category@std@@QAE@XZ
// FUNCTION: 0x405fb0 ??0_Iostream_error_category@std@@QAE@XZ
// FUNCTION: 0x44a5f0 ??0_System_error_category@std@@QAE@XZ

// FUNCTION: 0x444550
ProtocolState::ProtocolState()
{
}

// FUNCTION: 0x444570
ProtocolState::~ProtocolState()
{
}

// FUNCTION: 0x444580
ProtocolState &ProtocolState::operator=(ProtocolState &&other)
{
    console_ = std::move(other.console_);
    return *this;
}

// The handlers that take only 4 bytes of arguments are folded with every other `ret 4`
// (0x43b6f0), isOver with every `return false` (0x44d8d0). Of the others, identical
// ones are folded into the last by name.
void ProtocolState::enter(ProtocolContext &)
{
}

void ProtocolState::leave(ProtocolContext &)
{
}

// FUNCTION: 0x444610
void ProtocolState::receiveConnectRequest(ProtocolContext &, int, int, int, std::wstring, bool,
                                          const Endpoint &)
{
}

// FUNCTION: 0x4445f0
void ProtocolState::receiveConnectConfirm(ProtocolContext &, int, int, int, int, int,
                                          std::wstring, std::wstring, bool, const Endpoint &)
{
}

void ProtocolState::receiveChangeRole(ProtocolContext &, int, const Endpoint &)
{
}

void ProtocolState::receivePing(ProtocolContext &, const Endpoint &)
{
}

void ProtocolState::receivePong(ProtocolContext &, const Endpoint &)
{
}

void ProtocolState::receiveInputAck(ProtocolContext &, int, int, const Endpoint &)
{
}

// FUNCTION: 0x444620
void ProtocolState::receiveInput(ProtocolContext &, int, int, std::deque<FrameInput>,
                                 const Endpoint &)
{
}

// FUNCTION: 0x444630
void ProtocolState::receiveQuit(ProtocolContext &, const Endpoint &)
{
}

void ProtocolState::receivePalette(ProtocolContext &, const ColorPalette &, int, const Endpoint &)
{
}

// FUNCTION: 0x444640
void ProtocolState::receiveSync(ProtocolContext &, const std::deque<SyncBlock> &, const Endpoint &)
{
}

// FUNCTION: 0x444650
void ProtocolState::receiveSyncRequest(ProtocolContext &, int, int, const Endpoint &)
{
}

void ProtocolState::receiveRedirect(ProtocolContext &, const Endpoint &, const Endpoint &)
{
}

void ProtocolState::receiveDone(ProtocolContext &, int, const Endpoint &)
{
}

void ProtocolState::receivePunch(ProtocolContext &, const Endpoint &, const Endpoint &)
{
}

void ProtocolState::handleTimer(ProtocolContext &)
{
}

void ProtocolState::handleTimeout(ProtocolContext &, const Endpoint &)
{
}

void ProtocolState::handleResendTimer(ProtocolContext &)
{
}

void ProtocolState::handleGameTimer(ProtocolContext &)
{
}

void ProtocolState::handleQueueEvent(ProtocolContext &)
{
}

// FUNCTION: 0x4445e0
void ProtocolState::handleCommand(ProtocolContext &, std::string)
{
}

bool ProtocolState::isOver()
{
    return false;
}
