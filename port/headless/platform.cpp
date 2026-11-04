// The headless platform: what port/main.cpp, video.cpp, input.cpp and sound.cpp are on
// SDL3, for a game without a window, sound or keyboard.
//
// - The screen: nothing is shown. A game that draws (Globals::drawing) still draws into
//   CGraphics's back buffer, which the program reads (env.cpp's efz_env_render).
// - The clock: timeGetTime advances 16 ms with each call, so the game's waits for the
//   next frame (CScene::FadeIn, FadeOut) end at once and every run is the same.
// - The controls: GetInput gives each player the bits the program set in
//   Globals::input; the keyboard is never pressed and there are no joysticks.
// - Sound: the sound slots are taken and given back as on SDL3, so the game's sound
//   IDs are the same, but nothing is loaded beyond the .wav header and nothing plays.
#include <stdio.h>
#include <string.h>

#include "efz.h"
#include "headless.h"
#include "platform.h"

namespace {

bool g_messages = true;

} // namespace

namespace efz {

void RequestQuit()
{
    G()->quit = 1;
}

bool QuitRequested()
{
    return G()->quit != 0;
}

void PumpEvents()
{
}

bool OpenScreen(int, int)
{
    return true;
}

void Present(IDirectDrawSurface*, const PALETTEENTRY* palette)
{
    // The frame stays in the back buffer for FrameRGB; the palette is CGraphics's own.
    G()->root[headless::kRootPalette] = Handle(palette);
}

void CloseScreen()
{
}

bool Drawing()
{
    return G()->drawing != 0;
}

namespace headless {

void SetMessages(bool show)
{
    g_messages = show;
}

void CreateGame(bool drawing, BYTE mode)
{
    const HWND window = 1; // the game passes its window around: any nonzero value
    Globals* g = G();
    g->drawing = drawing;
    g->clock = 0;
    g->quit = 0;
    g->input[0] = g->input[1] = 0;

    CGraphics* graphics = new CGraphics;
    CInput* input = new CInput;
    CSound* sound = new CSound;
    graphics->Init(window, mode);
    input->Init(window);
    sound->Init(window);

    CGame* game = new CGame(graphics, input, sound);
    game->LoadSounds();
    game->LoadEffectAnims();
    game->LoadEffects();

    PTR32(CPlayer)* players = new PTR32(CPlayer)[2];
    PTR32(CPlayer)* p1 = &players[0];
    PTR32(CPlayer)* p2 = &players[1];
    CScene* scenes[9];
    scenes[0] = new CScene0(window, p1, p2, game, graphics, input, sound);
    scenes[1] = new CScene1(window, p1, p2, game, graphics, input, sound);
    scenes[2] = new CScene2(window, p1, p2, game, graphics, input, sound);
    scenes[3] = new CScene3(window, p1, p2, game, graphics, input, sound);
    scenes[4] = NULL;
    scenes[5] = new CScene5(window, p1, p2, game, graphics, input, sound);
    scenes[6] = new CScene6(window, p1, p2, game, graphics, input, sound);
    scenes[7] = new CScene7(window, p1, p2, game, graphics, input, sound);
    scenes[8] = new CScene8(window, p1, p2, game, graphics, input, sound);

    g = G();
    g->root[kRootGraphics] = Handle(graphics);
    g->root[kRootInput] = Handle(input);
    g->root[kRootSound] = Handle(sound);
    g->root[kRootGame] = Handle(game);
    g->root[kRootPlayers] = Handle(players);
    g->root[kRootScene] = 0;
    for (int i = 0; i < 9; i++)
        g->root[kRootScenes + i] = Handle(scenes[i]);
}

bool FrameRGB(uint8_t* out, int* width, int* height)
{
    CGraphics* graphics = Graphics();
    IDirectDrawSurface* back = graphics->m_back;
    if (!Drawing() || !back)
        return false;
    const PALETTEENTRY* pal = (const PALETTEENTRY*)Ptr(G()->root[kRootPalette]);
    for (int y = 0; y < back->height; y++) {
        const BYTE* row = back->pixels + y * back->pitch;
        for (int x = 0; x < back->width; x++, out += 3) {
            if (pal) {
                const PALETTEENTRY& e = pal[row[x]];
                out[0] = e.peRed;
                out[1] = e.peGreen;
                out[2] = e.peBlue;
            } else {
                out[0] = out[1] = out[2] = 0;
            }
        }
    }
    *width = back->width;
    *height = back->height;
    return true;
}

void RunFrame()
{
    CGame* game = Game();
    uint32_t& scene = SceneIndex();
    game->m_oddFrame = !game->m_oddFrame;
    if (CScene* s = Scene(scene)) {
        Sound()->UpdateLoop(game->m_music);
        scene = s->Update();
    }
}

} // namespace headless
} // namespace efz

// --- The Win32 functions of the game code that go to the window system.

int MessageBoxA(HWND, LPCSTR text, LPCSTR caption, UINT)
{
    if (g_messages)
        fprintf(stderr, "efz: %s: %s\n", caption ? caption : "", text ? text : "");
    return 1;
}

BOOL PostMessageA(HWND, UINT msg, WPARAM, LPARAM)
{
    if (msg == WM_CLOSE)
        efz::RequestQuit();
    return TRUE;
}

DWORD timeGetTime()
{
    return efz::G()->clock += 16;
}

// --- CInput: the keyboard, never pressed, and the program's controls.

namespace {

struct Keyboard : IDirectInputDevice7 {
    ULONG Release()
    {
        delete this;
        return 0;
    }
    HRESULT GetDeviceState(DWORD size, LPVOID data)
    {
        memset(data, 0, size);
        return DI_OK;
    }
    HRESULT Acquire() { return DI_OK; }
};

} // namespace

CInput::CInput()
{
    memset(m_bindings, 0, sizeof(m_bindings));
    m_di = NULL;
    m_keyboard = NULL;
    m_joysticks[0] = NULL;
    m_joysticks[1] = NULL;
}

CInput::~CInput()
{
    Shutdown();
}

BOOL CInput::Init(HWND hWnd)
{
    m_hwnd = hWnd;
    m_keyboard = new Keyboard;
    return TRUE;
}

void CInput::Shutdown()
{
    if (m_keyboard) {
        m_keyboard->Release();
        m_keyboard = NULL;
    }
}

void CInput::Fail()
{
    MessageBox(0, "DirectInputの初期化に失敗", "ERROR", MB_OK);
    PostMessage(m_hwnd, WM_CLOSE, 0, 0);
}

BYTE CInput::GetInput(BYTE player)
{
    BYTE result;

    if (player > 1)
        return 0;
    if (TraceInput(player, &result))
        return result;
    return efz::G()->input[player];
}

void CInput::LoadBindings()
{
}

void CInput::LoadPreset(int)
{
}

// --- CSound: the slots without the sounds.

// A taken slot.
struct IDirectSoundBuffer : IUnknown {
    ULONG Release()
    {
        delete this;
        return 0;
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
    for (WORD i = 0; i < 0x96; i++)
        ReleaseBuffer(i);
    if (m_ds) {
        m_ds->Release();
        m_ds = NULL;
    }
}

void CSound::Init(HWND hWnd)
{
    m_hwnd = hWnd;
    for (WORD i = 0; i < 0x96; i++)
        m_buffers[i] = NULL;
    m_ds = new IDirectSound;
}

void CSound::Fill(WORD)
{
}

void CSound::ReleaseBuffer(WORD id)
{
    if (m_buffers[id]) {
        m_buffers[id]->Release();
        m_buffers[id] = NULL;
    }
}

void CSound::CreateBuffer(WORD id, WAVEFORMATEX*)
{
    m_buffers[id] = new IDirectSoundBuffer;
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

void CSound::Stop(WORD)
{
}

void CSound::Play(WORD, BOOL)
{
}

void CSound::Release(WORD id)
{
    if (id < 0x96)
        ReleaseBuffer(id);
}

// As SDL3's Load: the same files are taken (a RIFF WAVE with PCM data) and the same
// slots given, but from the header only.
WORD CSound::Load(const char* name)
{
    FILE* f = efz::OpenGameFile(name, "rb");
    if (!f)
        return 0x96;
    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    BYTE head[12];
    bool wave = fileSize >= 12 && fseek(f, 0, SEEK_SET) == 0 && fread(head, 1, 12, f) == 12 &&
                !memcmp(head, "RIFF", 4) && !memcmp(head + 8, "WAVE", 4);
    if (!wave) {
        fclose(f);
        MessageBox(m_hwnd, "WAVEファイルではありません", "DS", MB_OK);
        return 0x96;
    }
    WAVEFORMATEX wfx;
    bool haveFormat = false, haveData = false;
    DWORD dataSize = 0;
    for (long p = 12; p + 8 <= fileSize;) {
        BYTE chunk[8 + 16];
        if (fseek(f, p, SEEK_SET) != 0 || fread(chunk, 1, 8, f) != 8)
            break;
        DWORD size = Read32(chunk + 4);
        if (!memcmp(chunk, "fmt ", 4) && size >= 16) {
            if (p + 8 + 16 <= fileSize && fread(chunk + 8, 1, 16, f) == 16) {
                memcpy(&wfx, chunk + 8, 16);
                haveFormat = true;
            }
        } else if (!memcmp(chunk, "data", 4)) {
            haveData = true;
            dataSize = size;
            if (p + 8 + (long)dataSize > fileSize)
                dataSize = (DWORD)(fileSize - p - 8);
            break;
        }
        p += 8 + size + (size & 1);
    }
    fclose(f);
    if (!haveFormat || wfx.wFormatTag != 1 || !haveData) {
        MessageBox(m_hwnd, "WAVEファイルはPCMフォーマットではありません", "DS", MB_OK);
        return 0x96;
    }
    WORD ch = FindFreeSlot();
    if (ch == 0x96)
        return 0x96;
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
    if (cue == 0 || len == 0)
        return;
    m_loopEnd = (cue + len) * 4;
    m_loopLength = len * 4;
}

void CSound::UpdateLoop(WORD)
{
}

void CSound::SetVolume(WORD, int)
{
}
