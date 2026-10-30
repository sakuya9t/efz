// CInput on SDL3, in place of src/input.cpp's DirectInput.
//
// The keyboard state is DirectInput's: 256 bytes indexed by DIK_ code, 0x80 for a key
// that is down. key.ini stores bindings as those codes, and the title and replay
// scenes read the whole state through the keyboard device. Up to two game controllers
// stand in for DirectInput's joysticks: the left stick and the d-pad as the X and Y
// axes (-1000 to 1000), and the buttons in XInput's order, which is DirectInput's for
// those controllers. GetInput, LoadBindings and LoadPreset are the original's.
#include <SDL3/SDL.h>

#include "efz.h"
#include "platform.h"

namespace {

BYTE g_keys[0x100];

// DIK_ codes by SDL scancode: the key in that place on a US keyboard.
BYTE DikOf(SDL_Scancode sc)
{
    // Keys whose code depends on the layout: DirectInput gives a Japanese keyboard's
    // its own codes, which key.ini files made on one hold.
    switch (SDL_GetKeyFromScancode(sc, SDL_KMOD_NONE, false)) {
    case '@': return 0x91;  // DIK_AT
    case '^': return 0x90;  // DIK_CIRCUMFLEX
    case ':': return 0x92;  // DIK_COLON
    case '[': return 0x1a;  // DIK_LBRACKET
    case ']': return 0x1b;  // DIK_RBRACKET
    }
    if (sc >= SDL_SCANCODE_A && sc <= SDL_SCANCODE_Z) {
        static const BYTE letters[26] = {
            0x1e, 0x30, 0x2e, 0x20, 0x12, 0x21, 0x22, 0x23, 0x17, 0x24, 0x25, 0x26, 0x32,
            0x31, 0x18, 0x19, 0x10, 0x13, 0x1f, 0x14, 0x16, 0x2f, 0x11, 0x2d, 0x15, 0x2c};
        return letters[sc - SDL_SCANCODE_A];
    }
    if (sc >= SDL_SCANCODE_1 && sc <= SDL_SCANCODE_0)
        return 0x02 + (sc - SDL_SCANCODE_1);
    if (sc >= SDL_SCANCODE_F1 && sc <= SDL_SCANCODE_F10)
        return 0x3b + (sc - SDL_SCANCODE_F1);
    switch (sc) {
    case SDL_SCANCODE_ESCAPE: return 0x01;
    case SDL_SCANCODE_MINUS: return 0x0c;
    case SDL_SCANCODE_EQUALS: return 0x0d;
    case SDL_SCANCODE_BACKSPACE: return 0x0e;
    case SDL_SCANCODE_TAB: return 0x0f;
    case SDL_SCANCODE_LEFTBRACKET: return 0x1a;
    case SDL_SCANCODE_RIGHTBRACKET: return 0x1b;
    case SDL_SCANCODE_RETURN: return 0x1c;
    case SDL_SCANCODE_LCTRL: return 0x1d;
    case SDL_SCANCODE_SEMICOLON: return 0x27;
    case SDL_SCANCODE_APOSTROPHE: return 0x28;
    case SDL_SCANCODE_GRAVE: return 0x29;
    case SDL_SCANCODE_LSHIFT: return 0x2a;
    case SDL_SCANCODE_BACKSLASH: return 0x2b;
    case SDL_SCANCODE_NONUSHASH: return 0x2b;
    case SDL_SCANCODE_COMMA: return 0x33;
    case SDL_SCANCODE_PERIOD: return 0x34;
    case SDL_SCANCODE_SLASH: return 0x35;
    case SDL_SCANCODE_RSHIFT: return 0x36;
    case SDL_SCANCODE_KP_MULTIPLY: return 0x37;
    case SDL_SCANCODE_LALT: return 0x38;
    case SDL_SCANCODE_SPACE: return 0x39;
    case SDL_SCANCODE_CAPSLOCK: return 0x3a;
    case SDL_SCANCODE_NUMLOCKCLEAR: return 0x45;
    case SDL_SCANCODE_SCROLLLOCK: return 0x46;
    case SDL_SCANCODE_KP_7: return 0x47;
    case SDL_SCANCODE_KP_8: return 0x48;
    case SDL_SCANCODE_KP_9: return 0x49;
    case SDL_SCANCODE_KP_MINUS: return 0x4a;
    case SDL_SCANCODE_KP_4: return 0x4b;
    case SDL_SCANCODE_KP_5: return 0x4c;
    case SDL_SCANCODE_KP_6: return 0x4d;
    case SDL_SCANCODE_KP_PLUS: return 0x4e;
    case SDL_SCANCODE_KP_1: return 0x4f;
    case SDL_SCANCODE_KP_2: return 0x50;
    case SDL_SCANCODE_KP_3: return 0x51;
    case SDL_SCANCODE_KP_0: return 0x52;
    case SDL_SCANCODE_KP_PERIOD: return 0x53;
    case SDL_SCANCODE_NONUSBACKSLASH: return 0x56;
    case SDL_SCANCODE_F11: return 0x57;
    case SDL_SCANCODE_F12: return 0x58;
    case SDL_SCANCODE_INTERNATIONAL2: return 0x70; // DIK_KANA
    case SDL_SCANCODE_INTERNATIONAL1: return 0x73; // DIK_ABNT_C1, the Japanese \ key
    case SDL_SCANCODE_INTERNATIONAL4: return 0x79; // DIK_CONVERT
    case SDL_SCANCODE_INTERNATIONAL5: return 0x7b; // DIK_NOCONVERT
    case SDL_SCANCODE_INTERNATIONAL3: return 0x7d; // DIK_YEN
    case SDL_SCANCODE_KP_ENTER: return 0x9c;
    case SDL_SCANCODE_RCTRL: return 0x9d;
    case SDL_SCANCODE_KP_DIVIDE: return 0xb5;
    case SDL_SCANCODE_PRINTSCREEN: return 0xb7;
    case SDL_SCANCODE_RALT: return 0xb8;
    case SDL_SCANCODE_PAUSE: return 0xc5;
    case SDL_SCANCODE_HOME: return 0xc7;
    case SDL_SCANCODE_UP: return 0xc8;
    case SDL_SCANCODE_PAGEUP: return 0xc9;
    case SDL_SCANCODE_LEFT: return 0xcb;
    case SDL_SCANCODE_RIGHT: return 0xcd;
    case SDL_SCANCODE_END: return 0xcf;
    case SDL_SCANCODE_DOWN: return 0xd0;
    case SDL_SCANCODE_PAGEDOWN: return 0xd1;
    case SDL_SCANCODE_INSERT: return 0xd2;
    case SDL_SCANCODE_DELETE: return 0xd3;
    case SDL_SCANCODE_LGUI: return 0xdb;
    case SDL_SCANCODE_RGUI: return 0xdc;
    case SDL_SCANCODE_APPLICATION: return 0xdd;
    default: return 0;
    }
}

struct Keyboard : IDirectInputDevice7 {
    ULONG Release()
    {
        delete this;
        return 0;
    }
    HRESULT GetDeviceState(DWORD size, LPVOID data)
    {
        memcpy(data, g_keys, size < sizeof(g_keys) ? size : sizeof(g_keys));
        return DI_OK;
    }
    HRESULT Acquire() { return DI_OK; }
};

// A game controller, as a DirectInput joystick.
struct Joystick : IDirectInputDevice7 {
    SDL_Gamepad* pad;
    SDL_JoystickID id;

    ULONG Release()
    {
        if (pad)
            SDL_CloseGamepad(pad);
        delete this;
        return 0;
    }
    HRESULT GetDeviceState(DWORD size, LPVOID data)
    {
        DIJOYSTATE st;
        memset(&st, 0, sizeof(st));
        int x = SDL_GetGamepadAxis(pad, SDL_GAMEPAD_AXIS_LEFTX) * 1000 / 32767;
        int y = SDL_GetGamepadAxis(pad, SDL_GAMEPAD_AXIS_LEFTY) * 1000 / 32767;
        if (SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_DPAD_LEFT))
            x = -1000;
        if (SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_DPAD_RIGHT))
            x = 1000;
        if (SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_DPAD_UP))
            y = -1000;
        if (SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_DPAD_DOWN))
            y = 1000;
        st.lX = x;
        st.lY = y;
        static const SDL_GamepadButton buttons[] = {
            SDL_GAMEPAD_BUTTON_SOUTH, SDL_GAMEPAD_BUTTON_EAST, SDL_GAMEPAD_BUTTON_WEST,
            SDL_GAMEPAD_BUTTON_NORTH, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER,
            SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, SDL_GAMEPAD_BUTTON_BACK,
            SDL_GAMEPAD_BUTTON_START, SDL_GAMEPAD_BUTTON_LEFT_STICK,
            SDL_GAMEPAD_BUTTON_RIGHT_STICK};
        for (int i = 0; i < (int)(sizeof(buttons) / sizeof(buttons[0])); i++)
            st.rgbButtons[i] = SDL_GetGamepadButton(pad, buttons[i]) ? 0x80 : 0;
        // The triggers as the next two buttons.
        st.rgbButtons[10] = SDL_GetGamepadAxis(pad, SDL_GAMEPAD_AXIS_LEFT_TRIGGER) > 16000 ? 0x80 : 0;
        st.rgbButtons[11] = SDL_GetGamepadAxis(pad, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) > 16000 ? 0x80 : 0;
        memcpy(data, &st, size < sizeof(st) ? size : sizeof(st));
        return DI_OK;
    }
    HRESULT Acquire() { return DI_OK; }
};

CInput* g_input;

} // namespace

namespace efz {

void KeyEvent(int scancode, bool down)
{
    BYTE dik = DikOf((SDL_Scancode)scancode);
    if (dik)
        g_keys[dik] = down ? 0x80 : 0;
}

void ResetInput()
{
    memset(g_keys, 0, sizeof(g_keys));
}

// Opens controllers into the free joystick slots and closes the ones unplugged.
void UpdateJoysticks()
{
    if (!g_input)
        return;
    for (int i = 0; i < 2; i++) {
        Joystick* j = (Joystick*)(IDirectInputDevice7*)g_input->m_joysticks[i];
        if (j && !SDL_GamepadConnected(j->pad)) {
            j->Release();
            g_input->m_joysticks[i] = NULL;
        }
    }
    int count = 0;
    SDL_JoystickID* ids = SDL_GetGamepads(&count);
    for (int k = 0; ids && k < count; k++) {
        bool open = false;
        for (int i = 0; i < 2; i++) {
            Joystick* j = (Joystick*)(IDirectInputDevice7*)g_input->m_joysticks[i];
            open |= j && j->id == ids[k];
        }
        for (int i = 0; i < 2 && !open; i++) {
            if (g_input->m_joysticks[i])
                continue;
            SDL_Gamepad* pad = SDL_OpenGamepad(ids[k]);
            if (!pad)
                break;
            Joystick* j = new Joystick;
            j->pad = pad;
            j->id = ids[k];
            g_input->m_joysticks[i] = j;
            open = true;
        }
    }
    SDL_free(ids);
}

} // namespace efz

CInput::CInput()
{
    m_bindings[0][0] = 0x24; // DIK_J
    m_bindings[0][1] = 0x22; // DIK_G
    m_bindings[0][2] = 0x31; // DIK_N
    m_bindings[0][3] = 0x15; // DIK_Y
    m_bindings[0][4] = 0x10; // DIK_Q
    m_bindings[0][5] = 0x11; // DIK_W
    m_bindings[0][6] = 0x12; // DIK_E
    m_bindings[0][7] = 0x20; // DIK_D
    m_bindings[1][3] = 0xc8; // DIK_UP
    m_bindings[1][2] = 0xd0; // DIK_DOWN
    m_bindings[1][1] = 0xcb; // DIK_LEFT
    m_bindings[1][0] = 0xcd; // DIK_RIGHT
    m_bindings[1][4] = 0x19; // DIK_P
    m_bindings[1][5] = 0x91; // DIK_AT
    m_bindings[1][6] = 0x1a; // DIK_LBRACKET
    m_bindings[1][7] = 0x1b; // DIK_RBRACKET
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
    g_input = this;
    efz::UpdateJoysticks();
    return TRUE;
}

void CInput::Shutdown()
{
    if (m_keyboard) {
        m_keyboard->Release();
        m_keyboard = NULL;
    }
    for (int i = 0; i < 2; i++) {
        if (m_joysticks[i]) {
            m_joysticks[i]->Release();
            m_joysticks[i] = NULL;
        }
    }
    if (g_input == this)
        g_input = nullptr;
}

void CInput::Fail()
{
    MessageBox(0, "DirectInputの初期化に失敗", "ERROR", MB_OK);
    PostMessage(m_hwnd, WM_CLOSE, 0, 0);
}

BYTE CInput::GetInput(BYTE player)
{
    BYTE result;
    WORD type;
    BYTE dik;
    short* binding;
    int i;

    if (player > 1)
        return 0;
    if (TraceInput(player, &result))
        return result;
    result = 0;
    binding = m_bindings[player];
    if (m_keyboard)
        m_keyboard->GetDeviceState(sizeof(m_keyState), m_keyState);
    if (m_joysticks[0])
        m_joysticks[0]->GetDeviceState(sizeof(DIJOYSTATE), &m_joyState[0]);
    if (m_joysticks[1])
        m_joysticks[1]->GetDeviceState(sizeof(DIJOYSTATE), &m_joyState[1]);
    for (i = 0; i < 8; i++) {
        dik = *binding & 0xff;
        type = *binding & 0xf00;
        switch (type) {
        case 0:
            if (m_keyboard && (m_keyState[dik] & 0x80))
                result |= 1 << i;
            break;
        case 0x100:
        case 0x200: {
            int pad = type == 0x100 ? 0 : 1;
            if (m_joysticks[pad]) {
                if (m_joyState[pad].lX < -500 && dik == 0x12) {
                    result |= 1 << i;
                    break;
                }
                if (m_joyState[pad].lX > 500 && dik == 0x13) {
                    result |= 1 << i;
                    break;
                }
                if (m_joyState[pad].lY < -500 && dik == 0x10) {
                    result |= 1 << i;
                    break;
                }
                if (m_joyState[pad].lY > 500 && dik == 0x11) {
                    result |= 1 << i;
                    break;
                }
                if ((m_joyState[pad].rgbButtons[dik] & 0x80) && dik < 0x10) {
                    result |= 1 << i;
                    break;
                }
            }
            break;
        }
        }
        binding++;
    }
    return result;
}

// key.ini stores each binding as two bytes, device then code, in the order up, down,
// left, right, then the buttons. A stored device byte of n > 0 gives the binding
// (n << 8) + code - 1. Preset `set` starts 39 bytes per set into the file.
static void ReadBindings(short bindings[2][8], int base)
{
    DWORD dwRead;
    HANDLE hFile = CreateFile("key.ini", GENERIC_READ, 0, NULL, OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE && GetFileSize(hFile, NULL) >= (DWORD)base + 0x20) {
        DWORD size = GetFileSize(hFile, NULL);
        BYTE* data = new BYTE[size];
        ReadFile(hFile, data, size, &dwRead, NULL);
        static const int order[8] = {3, 2, 1, 0, 4, 5, 6, 7};
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 8; k++) {
                const BYTE* b = data + base + j * 16 + k * 2;
                bindings[j][order[k]] = b[1] + (b[0] << 8) - (b[0] > 0);
            }
        }
        delete[] data;
    }
    CloseHandle(hFile);
}

void CInput::LoadBindings()
{
    ReadBindings(m_bindings, 0);
}

void CInput::LoadPreset(int set)
{
    ReadBindings(m_bindings, set * 39);
}
