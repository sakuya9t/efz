// CSound on SDL3, in place of src/sound.cpp's DirectSound.
//
// Each of the 150 sound slots is a buffer as before: a .wav file's PCM data in the
// arena, played from the start, once or looping, at a volume in hundredths of a
// decibel. A mixer on SDL's audio thread adds the playing buffers together. The music's
// loop (LoadLoop's cue points) is taken at the exact sample instead of when the frame
// loop next looks at the play cursor, so it no longer skips.
#include <SDL3/SDL.h>
#include <math.h>

#include "efz.h"
#include "platform.h"

namespace {

const int kRate = 44100;

SDL_AudioStream* g_stream;

} // namespace

// One sound slot's playback state; the data stays in CSound::m_data.
struct IDirectSoundBuffer : IUnknown {
    const BYTE* data;
    DWORD size;
    int channels;
    int bits;
    int rate;
    bool playing;
    bool looping;
    double pos;      // in sample frames
    float gain;
    DWORD loopEnd;    // bytes; 0: no loop points
    DWORD loopLength;

    ULONG Release()
    {
        if (g_stream)
            SDL_LockAudioStream(g_stream);
        playing = false;
        if (g_stream)
            SDL_UnlockAudioStream(g_stream);
        delete this;
        return 0;
    }
    int Frame() const { return channels * bits / 8; }
    float Sample(int frame, int ch) const
    {
        const BYTE* p = data + frame * Frame() + ch * (bits / 8);
        if (bits == 8)
            return (p[0] - 128) / 128.0f;
        return (int16_t)(p[0] | (p[1] << 8)) / 32768.0f;
    }
};

struct IDirectSound : IUnknown {
    ULONG Release()
    {
        delete this;
        return 0;
    }
};

namespace {

CSound* g_sound;

void SDLCALL Mix(void*, SDL_AudioStream* stream, int additional, int)
{
    float out[2048];
    while (additional > 0) {
        int frames = additional / 8;
        if (frames > 1024)
            frames = 1024;
        if (frames == 0)
            frames = 1;
        memset(out, 0, sizeof(out));
        for (int id = 0; g_sound && id < 0x96; id++) {
            IDirectSoundBuffer* b = g_sound->m_buffers[id];
            if (!b || !b->playing || !b->data)
                continue;
            int total = b->size / b->Frame();
            double step = (double)b->rate / kRate;
            for (int i = 0; i < frames && b->playing; i++) {
                int f = (int)b->pos;
                if (f >= total) {
                    if (!b->looping) {
                        b->playing = false;
                        break;
                    }
                    b->pos -= total;
                    f = (int)b->pos;
                }
                float l = b->Sample(f, 0);
                float r = b->channels > 1 ? b->Sample(f, 1) : l;
                out[i * 2] += l * b->gain;
                out[i * 2 + 1] += r * b->gain;
                b->pos += step;
                if (b->loopEnd && b->pos * b->Frame() >= b->loopEnd)
                    b->pos -= (double)b->loopLength / b->Frame();
            }
        }
        for (int i = 0; i < frames * 2; i++)
            out[i] = out[i] > 1.0f ? 1.0f : out[i] < -1.0f ? -1.0f : out[i];
        SDL_PutAudioStreamData(stream, out, frames * 8);
        additional -= frames * 8;
    }
}

struct AudioLock {
    AudioLock()
    {
        if (g_stream)
            SDL_LockAudioStream(g_stream);
    }
    ~AudioLock()
    {
        if (g_stream)
            SDL_UnlockAudioStream(g_stream);
    }
};

uint32_t Read32(const BYTE* p)
{
    return p[0] | (p[1] << 8) | (p[2] << 16) | ((uint32_t)p[3] << 24);
}

} // namespace

CSound::CSound()
{
    m_loopEnd = 0;
    m_loopLength = 0;
    for (int i = 0; i < 0x96; i++) {
        m_data[i] = NULL;
        m_buffers[i] = NULL;
    }
}

CSound::~CSound()
{
    Shutdown();
}

void CSound::Shutdown()
{
    if (g_stream) {
        SDL_DestroyAudioStream(g_stream);
        g_stream = nullptr;
    }
    for (WORD i = 0; i < 0x96; i++) {
        if (m_buffers[i]) {
            ReleaseBuffer(i);
            if (m_data[i]) {
                delete[] (BYTE*)m_data[i];
                m_data[i] = NULL;
            }
        }
    }
    if (m_ds) {
        m_ds->Release();
        m_ds = NULL;
    }
    g_sound = nullptr;
}

void CSound::Init(HWND hWnd)
{
    m_hwnd = hWnd;
    for (WORD i = 0; i < 0x96; i++)
        m_buffers[i] = NULL;
    m_ds = new IDirectSound;
    g_sound = this;
    SDL_AudioSpec spec = {SDL_AUDIO_F32, 2, kRate};
    g_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, Mix, nullptr);
    if (!g_stream) {
        // Without sound the game still runs; DirectSound's failure was fatal.
        SDL_Log("no audio device: %s", SDL_GetError());
        return;
    }
    SDL_ResumeAudioStreamDevice(g_stream);
}

void CSound::Fill(WORD)
{
}

void CSound::ReleaseBuffer(WORD id)
{
    if (m_buffers[id]) {
        AudioLock lock;
        IDirectSoundBuffer* b = m_buffers[id];
        m_buffers[id] = NULL;
        b->playing = false;
        delete b;
    }
}

void CSound::CreateBuffer(WORD id, WAVEFORMATEX* format)
{
    IDirectSoundBuffer* b = new IDirectSoundBuffer;
    b->data = m_data[id];
    b->size = m_size[id];
    b->channels = format->nChannels;
    b->bits = format->nBlockAlign * 8 / format->nChannels;
    b->rate = format->nSamplesPerSec;
    b->gain = 1.0f;
    AudioLock lock;
    m_buffers[id] = b;
}

WORD CSound::FindFreeSlot()
{
    WORD i;
    for (i = 0; i < 0x96; i++) {
        if (!m_buffers[i])
            break;
    }
    if (i == 0x96)
        MessageBox(m_hwnd, "使用できるチャンネルがありません", "DS使用できるチャンネルがありません", MB_OK);
    return i;
}

void CSound::Stop(WORD id)
{
    if (id < 0x96 && m_buffers[id]) {
        AudioLock lock;
        m_buffers[id]->playing = false;
    }
}

void CSound::Play(WORD id, BOOL loop)
{
    if (id < 0x96 && m_buffers[id]) {
        AudioLock lock;
        IDirectSoundBuffer* b = m_buffers[id];
        b->pos = 0;
        b->looping = loop == 1;
        b->playing = true;
    }
}

void CSound::Release(WORD id)
{
    if (id >= 0x96)
        return;
    ReleaseBuffer(id);
    if (m_data[id]) {
        delete[] (BYTE*)m_data[id];
        m_data[id] = NULL;
    }
}

WORD CSound::Load(const char* name)
{
    FILE* f = efz::OpenGameFile(name, "rb");
    if (!f)
        return 0x96;
    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);
    BYTE* file = new BYTE[fileSize > 0 ? fileSize : 1];
    long got = (long)fread(file, 1, fileSize, f);
    fclose(f);
    WAVEFORMATEX wfx;
    const BYTE* data = nullptr;
    DWORD dataSize = 0;
    bool haveFormat = false;
    if (got < 12 || memcmp(file, "RIFF", 4) || memcmp(file + 8, "WAVE", 4)) {
        delete[] file;
        MessageBox(m_hwnd, "WAVEファイルではありません", "DS", MB_OK);
        return 0x96;
    }
    for (long p = 12; p + 8 <= got;) {
        DWORD size = Read32(file + p + 4);
        if (!memcmp(file + p, "fmt ", 4) && size >= 16) {
            memcpy(&wfx, file + p + 8, 16);
            haveFormat = true;
        } else if (!memcmp(file + p, "data", 4)) {
            data = file + p + 8;
            dataSize = size;
            if (data + dataSize > file + got)
                dataSize = (DWORD)(file + got - data);
            break;
        }
        p += 8 + size + (size & 1);
    }
    if (!haveFormat || wfx.wFormatTag != 1 || !data) {
        delete[] file;
        MessageBox(m_hwnd, "WAVEファイルはPCMフォーマットではありません", "DS", MB_OK);
        return 0x96;
    }
    WORD ch = FindFreeSlot();
    if (ch == 0x96) {
        delete[] file;
        return 0x96;
    }
    BYTE* pcm = new BYTE[dataSize];
    memcpy(pcm, data, dataSize);
    delete[] file;
    m_data[ch] = pcm;
    m_size[ch] = dataSize;
    CreateBuffer(ch, &wfx);
    return ch;
}

void CSound::LoadLoop(const char* name)
{
    BYTE buf[0x140 + 0x14]; // the search reads up to 0x13 bytes past what it finds
    DWORD cue = 0;
    DWORD len = 0;
    DWORD dw;

    memset(buf, 0, sizeof(buf));
    HANDLE h = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE || GetFileSize(h, NULL) == 0) {
        CloseHandle(h);
        m_loopEnd = 0;
        m_loopLength = 0;
        return;
    }
    SetFilePointer(h, -0x140, NULL, FILE_END);
    ReadFile(h, buf, 0x140, &dw, NULL);
    CloseHandle(h);
    for (int j = 0; j < 0x140; j++) {
        if (buf[j] == 'c' && buf[j + 1] == 'u' && buf[j + 2] == 'e')
            cue = Read32(buf + j + 0x10);
        else if (buf[j] == 'a' && buf[j + 1] == 'd' && buf[j + 2] == 't' && buf[j + 3] == 'l')
            len = Read32(buf + j + 0x10);
    }
    // Without both, the previous music's loop stays, as in the original.
    if (cue == 0 || len == 0)
        return;
    m_loopEnd = (cue + len) * 4;
    m_loopLength = len * 4;
}

void CSound::UpdateLoop(WORD id)
{
    if (id >= 0x96 || !m_buffers[id] || !m_data[id])
        return;
    AudioLock lock;
    m_buffers[id]->loopEnd = m_loopEnd;
    m_buffers[id]->loopLength = m_loopLength;
}

void CSound::SetVolume(WORD id, int volume)
{
    if (id >= 0x96 || !m_buffers[id])
        return;
    AudioLock lock;
    // DirectSound's volume: hundredths of a decibel, from -10000 (silent) to 0.
    m_buffers[id]->gain = volume <= -10000 ? 0.0f : (float)pow(10.0, volume / 2000.0);
}
