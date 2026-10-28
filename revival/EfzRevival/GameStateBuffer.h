// A save state's buffer (GameStateBuffer.cpp, 0x1006f640-0x1006f7a0), an object of its
// own after GameState.cpp's: the buffer's functions come after SaveState's, and its
// list's header functions after those of GameState.obj (vector<HitRect>::insert and
// what it uses), as the original's do. It is the 22nd object the Rich header counts
// (the one with no static initializers: it includes neither EfzGame.h nor Log.h). Its
// name is a guess; it sorts between GameState.cpp and Hook.cpp.
#pragma once
#include <list>

class StateBuffer {
public:
    StateBuffer(int capacity);
    // Forgets the regions, keeping the most it ever used.
    void reset();
    // FNSAVE and FRSTOR: the x87 state, control word included.
    void saveFpu();
    // Copies size bytes at address into the buffer.
    void add(void *address, int size);
    // Copies every region back.
    void restore();

private:
    struct Region {
        void *address;
        char *copy;
        int size;
        int unused;
    };

    char fpu_[0x200];                       // 0x000
    std::list<Region> regions_;             // 0x200
    char *buffer_;                          // 0x208
    char *cursor_;                          // 0x20c
    int capacity_;                          // 0x210
    unsigned int maxUsed_;                  // 0x214
};
