// The custom music's file list (Music.cpp, with MusicPlayer). The sessions hold a
// Playlist by value, so their headers include this one, and declare MusicPlayer only:
// Music.h brings in ATL, and of the objects that include the session headers only those
// of the four sessions with music (and Music.cpp) have ATL's registrar strings;
// EfzRevival.cpp and TournamentSession.cpp have none.
#pragma once
#include <string>
#include <vector>

// The music files of a folder. 0x10 bytes.
class Playlist {
public:
    Playlist();
    ~Playlist();
    unsigned int size();
    void clear();
    // The file at the current position, or L"" past the end.
    std::wstring current();
    // Moves on to the next file, wrapping around; L"" when there are none.
    std::wstring next();
    // Adds the music files in folder (a "\\" may be written as a yen sign).
    void load(std::wstring folder);
    void shuffle();

private:
    std::vector<std::wstring> files_;           // 0x00
    unsigned int index_;                        // 0x0c
};
