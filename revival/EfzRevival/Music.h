// Custom background music (Music.cpp, 0x1006faf0-0x10070600): the [Global] BGMFolder's
// .wav/.mp3/.ogg/.flac/.wma files in random order, played through DirectShow instead of
// the game's own BGM. Every session that has music (online, spectator, practice,
// replay, tournament) holds a Playlist and a MusicPlayer, and its sound slots
// (Session.h) send the game's BGM calls here while a file is playing.
//
// The original used ATL's CComPtr (atlbase.h): the registrar's strings of atlbase.h
// lead the string data of each object that includes this header.
#pragma once
#include <windows.h>
#include <ddraw.h>
#include <dshow.h>
#include <map>
#include <string>
#include <vector>
#include "stubs/atlcomcli.h"

// A DirectShow filter graph that plays one file at a time. 0x38 bytes, allocated by
// the sessions' start().
class MusicPlayer {
public:
    MusicPlayer();
    // FUNCTION: 0x10022500 ??_GMusicPlayer@@QAEPAXI@Z
    // (the scalar deleting destructor: the sessions delete their MusicPlayer)
    ~MusicPlayer();
    // Whether the graph is running (or its state can't be told).
    bool isPlaying();
    // IBasicAudio::put_Volume (hundredths of a decibel, 0 is full volume)
    void setVolume(int volume);
    void stop();
    // Whether the current file has played to its end.
    bool isFinished();
    // Plays file from its start, replaying the current one in place. A file that
    // failed once is skipped; false when it fails now.
    bool play(std::wstring file);

    bool muted;                                 // 0x00 MuteBGM, toggled by ToggleBGM
private:
    std::wstring current_;                      // 0x04
    CComPtr<IGraphBuilder> graph_;              // 0x1c
    CComPtr<IMediaControl> control_;            // 0x20
    CComPtr<IBasicAudio> audio_;                // 0x24
    CComPtr<IMediaSeeking> seeking_;            // 0x28
    CComPtr<IMediaFilter> filter_;              // 0x2c
    std::map<std::wstring, bool> failed_;       // 0x30 files that could not be rendered
};

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
