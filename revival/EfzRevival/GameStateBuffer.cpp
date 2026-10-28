// A save state's buffer (GameStateBuffer.h).
#include "stdafx.h"
#include "GameStateBuffer.h"
#include <string.h>
#include <stdlib.h>

// FUNCTION: 0x1006f730
void StateBuffer::restore()
{
    for (std::list<Region>::iterator it = regions_.begin(); it != regions_.end(); ++it)
        memcpy(it->address, it->copy, it->size);
}

// FUNCTION: 0x1006f6e0
void StateBuffer::add(void *address, int size)
{
    if (address != 0 && size != 0) {
        Region region;
        region.copy = cursor_;
        region.address = address;
        region.size = size;
        memcpy(cursor_, address, size);
        cursor_ += size;
        regions_.push_back(region);
    }
}

// FUNCTION: 0x1006f6d0
__declspec(naked) void StateBuffer::saveFpu()
{
    __asm {
        fsave [ecx]
        frstor [ecx]
        ret
    }
}

// FUNCTION: 0x1006f690
void StateBuffer::reset()
{
    unsigned int used = cursor_ - buffer_;
    maxUsed_ = maxUsed_ > used ? maxUsed_ : used;
    cursor_ = buffer_;
    regions_.clear();
}

// FUNCTION: 0x1006f640
StateBuffer::StateBuffer(int capacity)
{
    capacity_ = capacity;
    buffer_ = (char *)malloc(capacity);
    cursor_ = buffer_;
    maxUsed_ = 0;
    memset(fpu_, 0, sizeof(fpu_));
}
