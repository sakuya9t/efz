// The last state: the session is over. Entering it closes the session and waits for a
// key; the launcher's main loop stops when isOver says so. 0x28 bytes.
#pragma once
#include "ProtocolState.h"

class ProtocolStateEnd : public ProtocolState {
public:
    ProtocolStateEnd();
    ~ProtocolStateEnd();
    void enter(ProtocolContext &context);
    bool isOver();
};
