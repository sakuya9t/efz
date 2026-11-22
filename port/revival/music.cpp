// EfzRevival's music (music.h).
#include "music.h"

#include <SDL3/SDL.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <random>
#include <string>
#include <vector>

#include "efz.h"
#include "config.h"
#include "keys.h"
#include "../platform.h"
#include "../log.h"

#include "dr_mp3.h"
#include "dr_flac.h"
#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"

namespace efz {
namespace revival {

namespace {

// A file's samples as 32-bit floats, a frame (all its channels) at a time.
struct Decoder {
    virtual ~Decoder() {}
    int channels = 2;
    int rate = 44100;
    // Up to `frames` frames into out (channels floats each); fewer at the end.
    virtual size_t Read(float* out, size_t frames) = 0;
    virtual void Rewind() = 0;
};

struct Pcm : Decoder {
    std::vector<float> samples;
    size_t pos = 0; // in frames
    size_t Read(float* out, size_t frames) override
    {
        size_t total = samples.size() / channels;
        size_t n = std::min(frames, total - std::min(pos, total));
        memcpy(out, samples.data() + pos * channels, n * channels * sizeof(float));
        pos += n;
        return n;
    }
    void Rewind() override { pos = 0; }
};

struct Mp3 : Decoder {
    std::vector<unsigned char> data;
    drmp3 mp3;
    bool open = false;
    ~Mp3() override
    {
        if (open)
            drmp3_uninit(&mp3);
    }
    size_t Read(float* out, size_t frames) override
    {
        return (size_t)drmp3_read_pcm_frames_f32(&mp3, frames, out);
    }
    void Rewind() override { drmp3_seek_to_pcm_frame(&mp3, 0); }
};

struct Flac : Decoder {
    std::vector<unsigned char> data;
    drflac* flac = nullptr;
    ~Flac() override
    {
        if (flac)
            drflac_close(flac);
    }
    size_t Read(float* out, size_t frames) override
    {
        return (size_t)drflac_read_pcm_frames_f32(flac, frames, out);
    }
    void Rewind() override { drflac_seek_to_pcm_frame(flac, 0); }
};

struct Vorbis : Decoder {
    std::vector<unsigned char> data;
    stb_vorbis* vorbis = nullptr;
    ~Vorbis() override
    {
        if (vorbis)
            stb_vorbis_close(vorbis);
    }
    size_t Read(float* out, size_t frames) override
    {
        return (size_t)stb_vorbis_get_samples_float_interleaved(vorbis, channels, out,
                                                                 (int)(frames * channels));
    }
    void Rewind() override { stb_vorbis_seek_start(vorbis); }
};

std::string Lower(std::string s)
{
    for (char& c : s)
        c = (char)tolower((unsigned char)c);
    return s;
}

std::string Extension(const std::string& path)
{
    size_t dot = path.rfind('.');
    size_t slash = path.find_last_of("/\\");
    if (dot == std::string::npos || (slash != std::string::npos && dot < slash))
        return "";
    return Lower(path.substr(dot));
}

bool ReadFile(const std::string& path, std::vector<unsigned char>* out)
{
    FILE* f = OpenPath(path.c_str(), "rb");
    if (!f)
        return false;
    unsigned char buf[65536];
    size_t got;
    while ((got = fread(buf, 1, sizeof(buf), f)) > 0)
        out->insert(out->end(), buf, buf + got);
    fclose(f);
    return !out->empty();
}

Decoder* OpenDecoder(const std::string& path, std::string* why)
{
    std::string ext = Extension(path);
    std::vector<unsigned char> data;
    if (!ReadFile(path, &data)) {
        *why = "can't read it";
        return nullptr;
    }
    if (ext == ".mp3") {
        Mp3* d = new Mp3;
        d->data.swap(data);
        if (!drmp3_init_memory(&d->mp3, d->data.data(), d->data.size(), nullptr)) {
            delete d;
            *why = "not an MP3 file dr_mp3 reads";
            return nullptr;
        }
        d->open = true;
        d->channels = (int)d->mp3.channels;
        d->rate = (int)d->mp3.sampleRate;
        return d;
    }
    if (ext == ".flac") {
        Flac* d = new Flac;
        d->data.swap(data);
        d->flac = drflac_open_memory(d->data.data(), d->data.size(), nullptr);
        if (!d->flac) {
            delete d;
            *why = "not a FLAC file dr_flac reads";
            return nullptr;
        }
        d->channels = (int)d->flac->channels;
        d->rate = (int)d->flac->sampleRate;
        return d;
    }
    if (ext == ".ogg") {
        Vorbis* d = new Vorbis;
        d->data.swap(data);
        int error = 0;
        d->vorbis = stb_vorbis_open_memory(d->data.data(), (int)d->data.size(), &error, nullptr);
        if (!d->vorbis) {
            delete d;
            *why = "not an Ogg Vorbis file stb_vorbis reads (error " + std::to_string(error) + ")";
            return nullptr;
        }
        stb_vorbis_info info = stb_vorbis_get_info(d->vorbis);
        d->channels = info.channels;
        d->rate = (int)info.sample_rate;
        return d;
    }
    if (ext == ".wav") {
        SDL_IOStream* io = SDL_IOFromConstMem(data.data(), data.size());
        SDL_AudioSpec spec;
        Uint8* buf = nullptr;
        Uint32 len = 0;
        if (!io || !SDL_LoadWAV_IO(io, true, &spec, &buf, &len)) {
            *why = std::string("not a WAV file SDL reads: ") + SDL_GetError();
            return nullptr;
        }
        SDL_AudioSpec want = spec;
        want.format = SDL_AUDIO_F32;
        Uint8* converted = nullptr;
        int convertedLen = 0;
        bool ok = SDL_ConvertAudioSamples(&spec, buf, (int)len, &want, &converted, &convertedLen);
        SDL_free(buf);
        if (!ok) {
            *why = std::string("can't convert it: ") + SDL_GetError();
            return nullptr;
        }
        Pcm* d = new Pcm;
        d->channels = spec.channels;
        d->rate = spec.freq;
        d->samples.assign((float*)converted, (float*)converted + convertedLen / sizeof(float));
        SDL_free(converted);
        return d;
    }
    *why = "not a kind of file this plays (.wav, .mp3, .ogg, .flac)";
    return nullptr;
}

// What the mixer plays, under the audio lock.
struct Playing {
    Decoder* decoder = nullptr;
    bool running = false;  // IMediaControl::Run'd, not stopped
    bool finished = false; // played to its end
    float gain = 1.0f;
    // The decoded frames being played (stereo) and where in them, in the file's frames:
    // frame 0 is the one before the last read, kept for the interpolation.
    std::vector<float> chunk;
    size_t frames = 0;
    double pos = 0;
    long long played = 0; // the file's frames played, for the log
};
Playing g_play;

struct Music {
    bool on = false;
    bool tournament = false;
    bool muted = false; // MusicPlayer::muted: MuteBGM, ToggleBGM
    std::vector<std::string> files; // the playlist, shuffled
    size_t index = 0;
    std::string current; // the file loaded
    std::map<std::string, bool> failed;
    int lastScene = -1;
};
Music g_music;

const std::string& Current()
{
    static const std::string none;
    return g_music.index < g_music.files.size() ? g_music.files[g_music.index] : none;
}

void Next()
{
    if (!g_music.files.empty())
        g_music.index = (g_music.index + 1) % g_music.files.size();
}

void Load(const std::string& folderIn)
{
    std::string folder = folderIn;
    // A yen sign (Shift-JIS's backslash) as the separator, as Revival takes it.
    for (size_t at; (at = folder.find("\xc2\xa5")) != std::string::npos;)
        folder.replace(at, 2, "\\");
#ifndef _WIN32
    std::replace(folder.begin(), folder.end(), '\\', '/');
#endif
    SDL_PathInfo info;
    if (folder.empty() || !SDL_GetPathInfo(folder.c_str(), &info) ||
        info.type != SDL_PATHTYPE_DIRECTORY) {
        if (!folderIn.empty())
            LogInfo("music", "BGMFolder %s: no such folder; the game's own music", folderIn.c_str());
        return;
    }
    struct Found {
        std::string folder;
        std::vector<std::string>* files;
    } found = {folder, &g_music.files};
    SDL_EnumerateDirectory(
        folder.c_str(),
        [](void* user, const char*, const char* name) -> SDL_EnumerationResult {
            Found* f = (Found*)user;
            std::string ext = Extension(name);
            std::string path = f->folder;
            if (!path.empty() && path.back() != '/' && path.back() != '\\')
                path += "/";
            path += name;
            SDL_PathInfo info;
            if ((ext == ".wav" || ext == ".mp3" || ext == ".ogg" || ext == ".flac") &&
                SDL_GetPathInfo(path.c_str(), &info) && info.type == SDL_PATHTYPE_FILE)
                f->files->push_back(path);
            else if (ext == ".wma")
                LogInfo("music", "%s: .wma isn't played here (Revival plays it through Windows)",
                        path.c_str());
            return SDL_ENUM_CONTINUE;
        },
        &found);
    std::sort(g_music.files.begin(), g_music.files.end());
    std::random_device device;
    std::mt19937 generator(device());
    std::shuffle(g_music.files.begin(), g_music.files.end(), generator);
    LogInfo("music", "BGMFolder %s: %zu music files", folder.c_str(), g_music.files.size());
}

bool IsPlaying()
{
    LockAudio(true);
    bool playing = g_play.decoder && g_play.running;
    LockAudio(false);
    return playing;
}

bool IsFinished()
{
    LockAudio(true);
    bool finished = g_play.decoder && g_play.finished;
    LockAudio(false);
    return finished;
}

void StopMusic()
{
    LockAudio(true);
    g_play.running = false;
    LockAudio(false);
}

void SetGain(int volume)
{
    LockAudio(true);
    g_play.gain = volume <= -10000 ? 0.0f : (float)pow(10.0, volume / 2000.0);
    LockAudio(false);
}

// MusicPlayer::play: the file from its start (the one loaded again, in place). Nothing
// while muted, nor a file that failed once.
bool PlayFile(const std::string& file)
{
    if (g_music.muted || file.empty() || g_music.failed[file])
        return true;
    if (g_play.decoder && g_music.current == file) {
        LockAudio(true);
        g_play.decoder->Rewind();
        g_play.frames = 0;
        g_play.pos = 0;
        g_play.played = 0;
        g_play.finished = false;
        g_play.running = true;
        LockAudio(false);
        return true;
    }
    std::string why;
    Decoder* d = OpenDecoder(file, &why);
    if (!d) {
        g_music.failed[file] = true;
        LogWarn("music", "can't play %s: %s", file.c_str(), why.c_str());
        return false;
    }
    LockAudio(true);
    Decoder* old = g_play.decoder;
    g_play.decoder = d;
    g_play.frames = 0;
    g_play.pos = 0;
    g_play.played = 0;
    g_play.finished = false;
    g_play.running = true;
    LockAudio(false);
    delete old;
    g_music.current = file;
    LogInfo("music", "playing %s (%d Hz, %d channels)", file.c_str(), d->rate, d->channels);
    return true;
}

bool IsMusic(unsigned short id)
{
    CGame* game = Objects().game;
    return game && id == (unsigned short)game->m_music;
}

int Scene()
{
    unsigned char* scene = Objects().scene;
    return scene ? *scene : -1;
}

// Reads the file's next frames after the last one kept (frame 0 of the chunk).
bool Refill(Playing& p)
{
    const size_t kFrames = 1024;
    std::vector<float> raw(kFrames * (size_t)std::max(1, p.decoder->channels));
    size_t got = p.decoder->Read(raw.data(), kFrames);
    if (got == 0)
        return false;
    float lastL = 0, lastR = 0;
    if (p.frames > 0) {
        lastL = p.chunk[(p.frames - 1) * 2];
        lastR = p.chunk[(p.frames - 1) * 2 + 1];
    }
    p.chunk.resize((got + 1) * 2);
    p.chunk[0] = lastL;
    p.chunk[1] = lastR;
    int c = p.decoder->channels;
    for (size_t i = 0; i < got; i++) {
        float l = raw[i * c];
        float r = c > 1 ? raw[i * c + 1] : l;
        p.chunk[(i + 1) * 2] = l;
        p.chunk[(i + 1) * 2 + 1] = r;
    }
    p.frames = got + 1;
    return true;
}

} // namespace

void InitMusic(bool tournament)
{
    const Config& ini = GetConfig();
    g_music.on = true;
    g_music.tournament = tournament;
    g_music.muted = ini.muteBGM;
    if (!tournament)
        Load(ini.bgmFolder);
}

void MusicFrame()
{
    if (!g_music.on)
        return;
    int scene = Scene();
    if (scene != g_music.lastScene) {
        if (scene == 2)
            Next();
        g_music.lastScene = scene;
    }
    if (IsFinished() && scene == 3) {
        LockAudio(true);
        long long played = g_play.played;
        LockAudio(false);
        LogInfo("music", "%s played to its end (%lld frames): again", g_music.current.c_str(),
                 played);
        PlayFile(Current());
    }
    if (Pressed(GetConfig().toggleBGM)) {
        g_music.muted = !g_music.muted;
        LogInfo("music", "music %s (ToggleBGM)", g_music.muted ? "off" : "on");
        GameObjects o = Objects();
        if (o.game && o.sound) {
            if (g_music.muted)
                o.sound->Stop((WORD)o.game->m_music);
            else
                o.sound->Play((WORD)o.game->m_music, 1);
        }
    }
}

bool MusicPlay(unsigned short id, int)
{
    if (!g_music.on || !IsMusic(id))
        return false;
    int scene = Scene();
    if (!g_music.tournament && !g_music.files.empty() && (scene == 2 || scene == 3)) {
        PlayFile(Current());
        return true;
    }
    return g_music.muted; // the game's music, not heard
}

bool MusicSetVolume(unsigned short id, int volume)
{
    if (!g_music.on || g_music.files.empty() || !IsMusic(id) || !IsPlaying())
        return false;
    SetGain(volume);
    return true;
}

bool MusicStop(unsigned short id)
{
    if (!g_music.on || g_music.files.empty() || !IsMusic(id) || !IsPlaying())
        return false;
    StopMusic();
    return true;
}

void MixMusic(float* out, int frames, int rate)
{
    Playing& p = g_play;
    if (!p.decoder || !p.running || p.finished)
        return;
    double step = (double)p.decoder->rate / rate;
    for (int i = 0; i < frames; i++) {
        while (p.pos + 1 >= (double)p.frames) {
            double used = p.frames > 0 ? (double)(p.frames - 1) : 0;
            if (!Refill(p)) {
                p.finished = true;
                return;
            }
            p.played += (long long)(p.frames - 1);
            p.pos -= used;
            if (p.pos < 0)
                p.pos = 0;
        }
        size_t f = (size_t)p.pos;
        float t = (float)(p.pos - (double)f);
        float l = p.chunk[f * 2] * (1 - t) + p.chunk[(f + 1) * 2] * t;
        float r = p.chunk[f * 2 + 1] * (1 - t) + p.chunk[(f + 1) * 2 + 1] * t;
        out[i * 2] += l * p.gain;
        out[i * 2 + 1] += r * p.gain;
        p.pos += step;
    }
}

} // namespace revival
} // namespace efz
