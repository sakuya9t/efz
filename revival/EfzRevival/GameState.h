// Save states (GameState.cpp, 0x1006f260-0x1006f7a0): a copy of the game's memory that
// can be written back, for the practice session's save/load and the online session's
// rollback (one per frame of its window). StateBuffer copies each region into one
// buffer and remembers where it came from; SaveState decides the regions.
#pragma once
#include <list>
#include <string>
#include <vector>
#include "EfzGame.h"

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

class SaveState {
public:
    SaveState();
    ~SaveState();
    void clear();
    // full: the whole fight scene; otherwise without CScene3 0x434-0x43f.
    void save(bool full);
    void load();
    // A variable of the session's to keep with the state.
    void addInt(int *value, int size = sizeof(int));

private:
    void addPlayer(CPlayer *player);

    StateBuffer *buffer_;                   // 0x00
    std::vector<HitRect> rects_;            // 0x04 Game's kept boxes
    std::string random_;                    // 0x10 g_rng's state
};
