// The records the launcher and EfzRevival.dll exchange through SharedQueue (shared
// memory), one queue per kind: "PaletteP1"/"PaletteP2" (ColorPalette), "InputP1"/
// "InputP2" (FrameInput), "Init" (GameInfo), "LoadMatch" (MatchInfo), "Net"
// (PingStats), "Sync" (SyncBlock) and "Quit" (a bool). Their layouts are fixed by the
// DLL.
//
// The names are lost; these sort as the original's code does. SharedQueue<T>'s
// functions are laid out by T's decorated name: ColorPalette < FrameInput < GameInfo <
// MatchInfo < PingStats < SyncBlock < bool (`_N`, after every struct). The constructors
// sort among ProtocolContext's object's: GameInfo < Log < PingStats < ProtocolContext.
// FrameInput is a struct, not an unsigned short: SharedQueue<T>::pop returns it
// through a hidden pointer, which MSVC does for every class type that a member
// function returns, and none for a scalar.
#pragma once
#include <string.h>
#include <sstream>
#include <string>

// A player's palette as EfzRevival.dll gives it (MessagePalette field 2).
struct ColorPalette {
    unsigned char data[0xa4];
};

// One player's input for one frame.
struct FrameInput {
    // FUNCTION: 0x434a90 ??8FrameInput@@QBE_NABU0@@Z
    bool operator==(const FrameInput &other) const
    {
        return first == other.first && second == other.second;
    }

    char first;
    char second;
};

// What EfzRevival.dll needs to start a match. 0x114 bytes.
struct GameInfo {
    // FUNCTION: 0x432580
    GameInfo()
        : player(0), delay(0), rollback(0), seed(0), practiceKeys(false)
    {
        memset(names, 0, sizeof(names));
        launcher = 0;
    }

    int player;             // 0x000 the local player, 0 or 1
    char delay;             // 0x004 input delay
    char rollback;          // 0x005 MaxRollback, at most 9
    int seed;               // 0x008 the host's timeGetTime(), shared through MessageInit
    bool practiceKeys;      // 0x00c AllowPracticeKeys, on both sides
    wchar_t names[2][64];   // 0x00e
    unsigned long launcher; // 0x110 the launcher's process id
};

// The match a spectator is watching (MessageInput field 6).
struct MatchInfo {
    int match;
    int unknown4;
    int unknown8;
};

// Round-trip times in milliseconds, for the DLL's display ("Net" queue).
struct PingStats {
    // FUNCTION: 0x4325e0
    PingStats()
        : minimum(1000000), average(0), last(0), maximum(0)
    {
    }

    int minimum;  // 0x00 lowest ever
    int average;  // 0x04 over the last 20
    int last;     // 0x08
    int maximum;  // 0x0c highest of the last 20
};

// One frame's state, for desync detection: the DLL writes the local side's, the
// network brings the remote side's (MessageSync field 4), and they are compared frame
// by frame.
struct SyncBlock {
    // FUNCTION: 0x434ab0 ??8SyncBlock@@QBE_NABU0@@Z
    bool operator==(const SyncBlock &other) const
    {
        return frame == other.frame && fpuCW == other.fpuCW && state == other.state
            && stateP1 == other.stateP1 && stateP2 == other.stateP2
            && inputP1 == other.inputP1 && inputP2 == other.inputP2 && rng == other.rng
            && p1x == other.p1x && p1y == other.p1y && p2x == other.p2x
            && p2y == other.p2y;
    }

    // FUNCTION: 0x442d70
    std::string toString() const
    {
        std::stringstream stream;
        stream << "Frame " << frame << " " << "FpuCW " << std::hex << "0x" << std::uppercase
               << fpuCW << " " << std::dec << std::nouppercase << "State " << state << " "
               << "StateP1 " << stateP1 << " " << "StateP2 " << stateP2 << " "
               << "P1 input " << (int)inputP1.first << " " << (int)inputP1.second << " "
               << "P2 input " << (int)inputP2.first << " " << (int)inputP2.second << " "
               << "Rng " << rng << " " << "P1 pos " << p1x << " " << p1y << " "
               << "P2 pos " << p2x << " " << p2y << "\n";
        return stream.str();
    }

    int frame;              // 0x00
    int state;              // 0x04
    unsigned int fpuCW;     // 0x08 the x87 control word
    short stateP1;          // 0x0c
    short stateP2;          // 0x0e
    FrameInput inputP1;     // 0x10
    FrameInput inputP2;     // 0x12
    double p1x;             // 0x18
    double p1y;             // 0x20
    double p2x;             // 0x28
    double p2y;             // 0x30
    unsigned int rng;       // 0x38
};
