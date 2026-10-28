// The playlist (0x1006ffd0-0x10070600): the music files of [Global] BGMFolder. It
// doesn't include Music.h, so it has no ATL strings (see Music.cpp).
#include "stdafx.h"
#include "Playlist.h"
#include <algorithm>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
// After boost.filesystem: random_device's header functions follow its.
#include <random>
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
