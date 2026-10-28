// The music player (0x1006faf0-0x1006ffd0): DirectShow playback of one file. An object
// of its own, before MusicList.cpp's playlist: in the original the player's header
// functions (CComPtr's, the failed-files map's, boost::iequals for two wstrings) come
// before the playlist's, and its string ("Could not play music: ", after the ATL
// registrar strings Music.h brings) before the playlist's; its static initializers are
// only Log.h's (the one object between Hook.cpp and the playlist's that has nothing
// else). The two objects' names are guesses; they sort between Hook.cpp and
// OnlineSession.cpp.
#include "stdafx.h"
#include "Music.h"
#include <boost/algorithm/string/predicate.hpp>
#include "Log.h"

// FUNCTION: 0x1006ff10
MusicPlayer::MusicPlayer()
{
    graph_ = NULL;
    control_ = NULL;
    audio_ = NULL;
    seeking_ = NULL;
    muted = false;
    filter_ = NULL;
    CoInitialize(NULL);
}

// FUNCTION: 0x1006fe90
MusicPlayer::~MusicPlayer()
{
    stop();
}

// The two branches' control_->Run() and return true are one block, after the seek: the
// seek branch returns itself (falling through to the function's return instead, it
// would jump to the RenderFile branch's copy). The original's tail at 0x1006fd40 is a
// separate function in the Ghidra export.
// FUNCTION: 0x1006fc10
bool MusicPlayer::play(std::wstring file)
{
    if (muted || failed_[file])
        return true;
    if (graph_ && boost::iequals(current_, file)) {
        LONGLONG start = 0;
        LONGLONG end = 0;
        control_->Stop();
        seeking_->GetDuration(&end);
        seeking_->SetPositions(&start, AM_SEEKING_AbsolutePositioning, &end,
                               AM_SEEKING_AbsolutePositioning);
        control_->Run();
        return true;
    } else {
        graph_.CoCreateInstance(CLSID_FilterGraph);
        graph_->QueryInterface(IID_PPV_ARGS(&control_));
        graph_->QueryInterface(IID_PPV_ARGS(&audio_));
        graph_->QueryInterface(IID_PPV_ARGS(&seeking_));
        graph_->QueryInterface(IID_PPV_ARGS(&filter_));
        HRESULT hr = graph_->RenderFile(file.c_str(), NULL);
        if (SUCCEEDED(hr)) {
            failed_[file] = false;
            current_ = file;
            if (control_)
                control_->Run();
        } else {
            failed_[file] = true;
            WCHAR error[0x100];
            DWORD length = AMGetErrorTextW(hr, error, 0x100);
            g_log << "Could not play music: " << std::string(error, error + length);
            return false;
        }
    }
    return true;
}

// FUNCTION: 0x1006fb90
bool MusicPlayer::isFinished()
{
    if (!seeking_)
        return false;
    LONGLONG duration = 0;
    LONGLONG position = 0;
    seeking_->GetDuration(&duration);
    seeking_->GetCurrentPosition(&position);
    return position >= duration;
}

// FUNCTION: 0x1006fb70
void MusicPlayer::stop()
{
    if (!control_)
        return;
    control_->Stop();
}

// FUNCTION: 0x1006fb40
void MusicPlayer::setVolume(int volume)
{
    if (!audio_)
        return;
    audio_->put_Volume(volume);
}

// FUNCTION: 0x1006faf0
bool MusicPlayer::isPlaying()
{
    if (!filter_)
        return false;
    FILTER_STATE state = State_Stopped;
    HRESULT hr = filter_->GetState(1, &state);
    return hr != S_OK || state == State_Running;
}
