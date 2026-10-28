// Custom background music: DirectShow playback of the files in [Global] BGMFolder.
#include "stdafx.h"
#include "Music.h"
#include <algorithm>
#include <random>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include "Log.h"

// FUNCTION: 0x100705e0
Playlist::Playlist()
{
    clear();
}

// FUNCTION: 0x100705d0
Playlist::~Playlist()
{
}

// FUNCTION: 0x10070160
void Playlist::load(std::wstring folder)
{
    boost::filesystem::directory_iterator end;
    const wchar_t *name = folder.c_str();
    g_log << "Adding Folder: " << std::string(name, name + folder.size()) << "\n";
    g_log << "Exists: " << boost::filesystem::exists(folder) << " is directory: "
          << boost::filesystem::is_directory(folder) << "\n";
    for (std::wstring::iterator it = folder.begin(); it != folder.end(); ++it) {
        wchar_t &c = *it;
        if (c == 0xa5) {
            c = L'\\';
            g_log << " replacing folder separator\n";
        }
    }
    if (boost::filesystem::exists(folder) && boost::filesystem::is_directory(folder)) {
        for (boost::filesystem::directory_iterator it(folder); it != end; ++it) {
            std::string extension = boost::filesystem::extension(it->path());
            bool music = boost::iequals(extension, ".wav") || boost::iequals(extension, ".mp3")
                || boost::iequals(extension, ".ogg") || boost::iequals(extension, ".flac")
                || boost::iequals(extension, ".wma");
            if (boost::filesystem::is_regular_file(it->status()) && music)
                files_.push_back(it->path().generic_wstring());
        }
    }
}

// FUNCTION: 0x100700b0
void Playlist::shuffle()
{
    std::random_device device;
    std::mt19937 generator(device());
    std::shuffle(files_.begin(), files_.end(), generator);
}

// FUNCTION: 0x10070090
void Playlist::clear()
{
    files_.clear();
    index_ = 0;
}

// FUNCTION: 0x10070080
unsigned int Playlist::size()
{
    return files_.size();
}

// FUNCTION: 0x10070020
std::wstring Playlist::next()
{
    if (files_.size() == 0)
        return L"";
    index_ = (index_ + 1) % files_.size();
    return files_[index_];
}

// FUNCTION: 0x1006ffd0
std::wstring Playlist::current()
{
    if (index_ >= files_.size())
        return L"";
    return files_[index_];
}

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
