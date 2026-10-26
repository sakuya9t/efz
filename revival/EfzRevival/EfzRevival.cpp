// EfzRevival.dll's entry: init, which the launcher calls in the game's process, creates
// the session for the launcher's mode and hooks WinMain's first frame; that frame
// installs the rest of the hooks into efz.exe (setup). Every frame then switches to the
// practice or replay session when the game's menus ask for one, reads the keyboard and
// the joystick, and runs the session.
#include "../EfzRevivalLauncher/Config.h"
#include "EfzRevival.h"
#include "EfzGame.h"
#include "EfzReplay.h"
#include "Hook.h"
#include "Log.h"
#include "../EfzRevivalLauncher/Version.h"
#include "OnlineSession.h"
#include "OnlineSpectatorSession.h"
#include "PracticeSession.h"
#include "ReplaySession.h"
#include "TournamentSession.h"
#include <psapi.h>
#include <math.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <random>

// GLOBAL: 0x100a02a8
// The joystick the players' button A is on (CInput's device numbers, 0 the keyboard).
BYTE g_joystick;
// GLOBAL: 0x100a02a9
bool g_unknown2a9;
// GLOBAL: 0x100a02ac
bool g_buttonPressed[0x20];
// GLOBAL: 0x100a02cc
bool g_buttonReleased[0x20];
// GLOBAL: 0x100a02ec
Session *g_session;
// GLOBAL: 0x100a02f0
bool g_keyHeld[0x100];
// GLOBAL: 0x100a03f0
bool g_keyPressed[0x100];
// GLOBAL: 0x100a04f0
bool g_keyReleased[0x100];
// GLOBAL: 0x100a05f0
int g_mode;
// GLOBAL: 0x100a05f4
// The scene switchSession last saw.
int g_lastScene;

// GLOBAL: 0x100a0710
Log g_log;
// GLOBAL: 0x100a070c
// In place of the game's rand, so that both sides of a netplay match draw the same
// numbers (and a replay or save state can restore them).
std::minstd_rand g_rng(timeGetTime());
// GLOBAL: 0x100a0780
Game g_game;

// In the practice mode the game's own menus pick replays and VS PLAYER: their sessions
// take over from the one the launcher started.
// FUNCTION: 0x1006e090
static void switchSession()
{
    if (g_lastScene != g_game.sceneId()) {
        if (g_lastScene == 0) {
            if (g_game.sceneId() == 8 && g_mode == 2 && g_game.menuChoice() == 4) {
                delete g_session;
                g_session = new ReplaySession();
                g_session->start();
            } else if (g_game.sceneId() == 1 && g_mode == 2
                       && (g_game.menuChoice() == 3 || g_game.menuChoice() == 2)) {
                delete g_session;
                g_session = new PracticeSession();
                g_session->start();
            }
        }
        g_lastScene = g_game.sceneId();
    }
}

// In place of the CRT's rand (efz.exe 0x777d61).
// FUNCTION: 0x1006e1a0
static int random()
{
    std::uniform_int_distribution<int> distribution(0, 0x7fff);
    return distribution(g_rng);
}

// The module the crash happened near, for the stack trace's offsets.
class Module {
public:
    Module(const int &base, const int &size);
    // "0x" and the address, or its offset into the module.
    std::string describe(const int *address);

private:
    int base_;
    int size_;
};

// FUNCTION: 0x1006e7d0
std::string Module::describe(const int *address)
{
    std::stringstream text;
    int value = *address;
    if (value >= base_ && value < base_ + size_)
        text << "0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0')
             << value - base_ << " OFFSET";
    else
        text << "0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0')
             << value;
    return text.str();
}

// FUNCTION: 0x1006e930
Module::Module(const int &base, const int &size)
{
    base_ = base;
    size_ = size;
}

// The 150 stack words above the crash, with the frames ebp links.
// FUNCTION: 0x1006e950
static void stackTrace(int *esp, int *ebp, int base, int size)
{
    g_log << "\nStack Trace\n";
    Module module(base, size);
    int *end = esp + 150;
    while (esp < end) {
        while (esp < ebp) {
            g_log << std::hex << "0x" << esp << " " << module.describe(esp) << std::endl;
            esp++;
        }
        ebp = (int *)*esp;
        esp++;
        g_log.width(4);
        g_log.fill('0');
        g_log << "Stack frame end return to " << module.describe(esp) << std::endl;
        esp++;
    }
    g_log.flush();
}

// The unhandled exception filter: the registers and the stack into the log.
// FUNCTION: 0x1006e1c0
static LONG WINAPI crashHandler(EXCEPTION_POINTERS *info)
{
    MODULEINFO module;
    GetModuleInformation(GetCurrentProcess(), GetModuleHandleW(L"EfzRevival"), &module,
                         sizeof(module));
    g_log << "\n\n!!!Crash!!!\n"
          << "EfzRevival Base:   0x" << std::uppercase << std::hex << std::setw(8)
          << std::setfill('0') << module.lpBaseOfDll << std::endl
          << "Exception Address: 0x" << std::uppercase << std::hex << std::setw(8)
          << std::setfill('0') << (int)info->ExceptionRecord->ExceptionAddress << std::endl
          << "Exception Code:    0x" << std::uppercase << std::hex << std::setw(8)
          << std::setfill('0') << (int)info->ExceptionRecord->ExceptionCode << std::endl
          << "EIP 0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0')
          << (int)info->ContextRecord->Eip << std::endl
          << "ESP 0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0')
          << (int)info->ContextRecord->Esp << std::endl
          << "EBP 0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0')
          << (int)info->ContextRecord->Ebp << std::endl
          << "EAX 0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0')
          << (int)info->ContextRecord->Eax << std::endl
          << "EBX 0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0')
          << (int)info->ContextRecord->Ebx << std::endl
          << "ECX 0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0')
          << (int)info->ContextRecord->Ecx << std::endl
          << "EDX 0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0')
          << (int)info->ContextRecord->Edx << std::endl
          << "ESI 0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0')
          << (int)info->ContextRecord->Esi << std::endl
          << "EDI 0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0')
          << (int)info->ContextRecord->Edi << std::endl;
    g_log.flush();
    stackTrace((int *)info->ContextRecord->Esp, (int *)info->ContextRecord->Ebp,
               (int)module.lpBaseOfDll, module.SizeOfImage);
    g_log.close();
    return EXCEPTION_EXECUTE_HANDLER;
}

// A mouse move of nothing, every frame: keeps the screen saver and the display's sleep
// away during play with a pad.
// FUNCTION: 0x1006eaa0
static void keepAwake()
{
    INPUT input;
    ZeroMemory(&input, sizeof(input));
    input.type = INPUT_MOUSE;
    input.mi.dx = 0;
    input.mi.dy = 0;
    SendInput(1, &input, sizeof(INPUT));
}

// FUNCTION: 0x1006eae0
void onReplayDone()
{
    ((ReplayFile *)&g_game.scene(3)->game->replay)->close();
    g_game.setNetplay(false);
}

// The hook targets below are reached through Hook.h's saving trampoline: their caller's
// frame holds the flags, the game's registers (pushad) and then its stack.

// At CScene3::Vf2's 0x7668e5: the kept boxes of this frame.
// FUNCTION: 0x1006eb00
static void updateRectsHook()
{
    g_game.updateRects();
}

// At CScene3::Vf2's 0x7656a7.
// FUNCTION: 0x1006eb10
static void fightUpdateHook()
{
    void *frame;
    __asm {
        mov ebx, ebp
        add ebx, 0x34
        mov frame, ebx
    }
    g_session->fightUpdate(frame);
}

// CSound::Stop's start (efz.exe 0x40de40): the sound's ID is the game's first argument.
// FUNCTION: 0x1006eb30
static void stopSoundHook()
{
    WORD id;
    __asm {
        mov ebx, [esp + 0x38]
        mov id, bx
    }
    g_session->stopSound(id);
}

// CSound::SetVolume's start (efz.exe 0x40e5d0).
// FUNCTION: 0x1006eb50
static void setVolumeHook()
{
    WORD id;
    int volume;
    __asm {
        mov ebx, [ebp + 0x30]
        mov id, bx
        mov ebx, [ebp + 0x34]
        mov volume, ebx
    }
    g_session->setVolume(id, volume);
}

// CSound::Play's start (efz.exe 0x40de80).
// FUNCTION: 0x1006eb80
static void playSoundHook()
{
    WORD id;
    int repeat;
    __asm {
        mov ebx, [esp + 0x3c]
        mov id, bx
        mov ebx, [esp + 0x40]
        mov repeat, ebx
    }
    g_session->playSound(id, repeat);
}

// CScene3::Draw's call of CScene3::Unk7631f0 (efz.exe 0x76479c), replaced.
// FUNCTION: 0x1006ebb0
static void drawBoxesHook()
{
    g_game.drawBoxes();
}

// In CInput::GetInput (efz.exe 0x40d131), with the player's controls in eax: left and
// right together become left, then the session reads or replaces them.
// FUNCTION: 0x1006ebc0
static void inputHook()
{
    char *frame;
    __asm mov frame, ebp
    int player = (*(char **)frame)[8];
    BYTE *input = (BYTE *)(frame + 0x28);
    if ((*input & 2) && (*input & 1))
        *input &= ~1;
    g_session->input(input, player);
}

// FUNCTION: 0x1006ec00
static void updateKeys()
{
    static bool down[0x100];
    memset(g_keyReleased, 0, sizeof(g_keyReleased));
    memset(g_keyPressed, 0, sizeof(g_keyPressed));
    memset(g_keyHeld, 0, sizeof(g_keyHeld));
    BYTE keys[0x100];
    g_game.readKeyboard(keys);
    for (int i = 0; i < 0x100; i++) {
        if ((char)keys[i] < 0) {
            if (!down[i])
                g_keyPressed[i] = true;
            down[i] = true;
            g_keyHeld[i] = true;
        } else {
            if (keys[i] == 0 && down[i])
                g_keyReleased[i] = true;
            down[i] = false;
        }
    }
}

// FUNCTION: 0x1006eca0
static void updateButtons()
{
    static bool down[0x20];
    memset(g_buttonReleased, 0, sizeof(g_buttonReleased));
    memset(g_buttonPressed, 0, sizeof(g_buttonPressed));
    IDirectInputDevice7 *joystick = g_game.device(g_joystick);
    if (joystick && g_joystick) {
        DIJOYSTATE state;
        memset(&state, 0, sizeof(state));
        joystick->Acquire();
        joystick->GetDeviceState(sizeof(state), &state);
        for (int i = 0; i < 0x20; i++) {
            if ((char)state.rgbButtons[i] < 0) {
                if (!down[i])
                    g_buttonPressed[i] = true;
                down[i] = true;
            } else {
                if (state.rgbButtons[i] == 0 && down[i])
                    g_buttonReleased[i] = true;
                down[i] = false;
            }
        }
    }
}

// Keys as 0-0xff, buttons as 0x201-0x220.
// FUNCTION: 0x1006ed90
static void sendKeys()
{
    updateKeys();
    updateButtons();
    for (int i = 0; i < 0x100; i++)
        if (g_keyPressed[i])
            g_session->keyPressed(i);
    for (int i = 0; i < 0x20; i++)
        if (g_buttonPressed[i])
            g_session->keyPressed(0x201 + i);
}

// Every frame, from WinMain's loop (hookCall at efz.exe 0x401642).
// FUNCTION: 0x1006edf0
static void frameHook()
{
    switchSession();
    keepAwake();
    sendKeys();
    g_session->update();
}

// The first frame (hooked at efz.exe 0x401582 by init): the window's title, then
// everything else.
// FUNCTION: 0x1006ee10
static void setup()
{
    HWND window = GetActiveWindow();
    std::wstringstream title;
    title << L"Eternal Fighter Zero -Revival- " << (int)floor(REVIVAL_VERSION / 100.0) << ".0"
          << REVIVAL_VERSION % 100 << REVIVAL_SUFFIX;
    SetWindowTextW(window, title.str().c_str());
    BYTE code[3];
    code[0] = 0xeb;
    patchCode((void *)0x776053, code, 1);
    hook((void *)0x40d131, 6, (void *)inputHook);
    hook((void *)0x7656a7, 6, (void *)fightUpdateHook);
    hookCall((void *)0x401642, 8, (void *)frameHook);
    hookCall((void *)0x76479c, 5, (void *)drawBoxesHook);
    g_game.setRendering(true);
    replaceFunction((void *)0x777d61, (void *)random);
    void (ReplayFile::*write)(short) = &ReplayFile::write;
    replaceFunction((void *)0x406020, *(void **)&write);
    short (ReplayFile::*read)() = &ReplayFile::read;
    replaceFunction((void *)0x405fb0, *(void **)&read);
    void (ReplayFile::*openWrite)(const char *) = &ReplayFile::openWrite;
    replaceFunction((void *)0x405f00, *(void **)&openWrite);
    DWORD (ReplayFile::*openRead)(const char *) = &ReplayFile::openRead;
    replaceFunction((void *)0x405e90, *(void **)&openRead);
    void (ReplayFile::*close)() = &ReplayFile::close;
    replaceFunction((void *)0x405f50, *(void **)&close);
    code[0] = 0xe9;
    code[1] = 0xa9;
    code[2] = 0x00;
    patchCode((void *)0x40de98, code, 3);
    hook((void *)0x40de80, 6, (void *)playSoundHook);
    hook((void *)0x7668e5, 7, (void *)updateRectsHook);
    code[0] = 0xeb;
    patchCode((void *)0x40de56, code, 1);
    hook((void *)0x40de40, 7, (void *)stopSoundHook);
    code[0] = 0x90;
    code[1] = 0x90;
    patchCode((void *)0x40e5e0, code, 2);
    hook((void *)0x40e5d0, 7, (void *)setVolumeHook);
    g_game.init();
    g_session->start();
    g_game.setGameFlag1366(true);
    char *bindings = (char *)g_game.bindings();
    g_joystick = bindings[9];
    if (g_joystick == 0)
        g_joystick = bindings[0x19];
}

// args[0] is the mode, args[1] the launcher's version.
// FUNCTION: 0x1006f0b0
extern "C" __declspec(dllexport) void init(int *args)
{
    g_lastScene = 0;
    Config config(L"./EfzRevival.ini");
    g_log.open("logEfz.txt", false, true);
    SetUnhandledExceptionFilter(crashHandler);
    timeBeginPeriod(1);
    g_log << args[1] << " " << args[0] << "\n";
    g_log.flush();
    if (args[1] != REVIVAL_VERSION) {
        MessageBoxA(0, "EfzRevival.exe and EfzRevival.dll are not the same version.", "Error", 0);
        TerminateProcess(GetCurrentProcess(), 0);
    }
    g_log << "Random state: " << g_rng << "\n";
    g_unknown2a9 = false;
    g_mode = args[0];
    switch (g_mode) {
    case 0:
        g_session = new OnlineSession();
        break;
    case 1:
        g_session = new SpectatorSession();
        break;
    case 2:
        g_session = new PracticeSession();
        break;
    case 3:
        g_session = new TournamentSession();
        break;
    default:
        return;
    }
    hook((void *)0x401582, 10, (void *)setup);
}
