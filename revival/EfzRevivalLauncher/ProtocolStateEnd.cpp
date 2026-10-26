// The end of a session.
#include "ProtocolStateEnd.h"
// OBJECT: 0x445280 0x445300
#include "ProtocolContext.h"
#include <cstdlib>

// FUNCTION: 0x445280
ProtocolStateEnd::ProtocolStateEnd()
{
}

// FUNCTION: 0x4452a0
ProtocolStateEnd::~ProtocolStateEnd()
{
}

// FUNCTION: 0x4452e0
void ProtocolStateEnd::enter(ProtocolContext &context)
{
    context.close();
    system("pause");
}

// Folded with every `return true` (0x401500).
bool ProtocolStateEnd::isOver()
{
    return true;
}
