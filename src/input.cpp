// Seventh object of efz.exe (0x40c5e0-0x40d80f): CInput, the DirectInput layer.
#include "efz.h"

// GLOBAL: 0x78ad6c _IID_IDirectInput7A
// GLOBAL: 0x78abdc _GUID_SysKeyboard
// GLOBAL: 0x78acec _IID_IDirectInputDevice7A
// GLOBAL: 0x78998c _c_dfDIKeyboard
// GLOBAL: 0x7899a4 _c_dfDIJoystick

// Zero-initialised, like main.cpp's globals, so .bss keeps them in declaration order.
// GLOBAL: 0x7b1278
// The CInput whose Init is enumerating joysticks, for EnumJoysticks.
CInput* g_enumInput = NULL;
// GLOBAL: 0x7b127c
// 16 bytes no code uses (a GUID's size); only the original's layout shows them.
BYTE g_unused7b127c[16] = { 0 };
// GLOBAL: 0x7b128c
BYTE g_joystickCount = 0;

BOOL CALLBACK EnumJoysticks(LPCDIDEVICEINSTANCE instance, LPVOID context);

CInput::CInput()
{
    m_bindings[0][0] = DIK_J;
    m_bindings[0][1] = DIK_G;
    m_bindings[0][2] = DIK_N;
    m_bindings[0][3] = DIK_Y;
    m_bindings[0][4] = DIK_Q;
    m_bindings[0][5] = DIK_W;
    m_bindings[0][6] = DIK_E;
    m_bindings[0][7] = DIK_D;
    m_bindings[1][3] = DIK_UP;
    m_bindings[1][2] = DIK_DOWN;
    m_bindings[1][1] = DIK_LEFT;
    m_bindings[1][0] = DIK_RIGHT;
    m_bindings[1][4] = DIK_P;
    m_bindings[1][5] = DIK_AT;
    m_bindings[1][6] = DIK_LBRACKET;
    m_bindings[1][7] = DIK_RBRACKET;
    m_di = NULL;
    m_keyboard = NULL;
    m_joysticks[0] = NULL;
    m_joysticks[1] = NULL;
}

BOOL CInput::Init(HWND hWnd)
{
    HRESULT hr;

    m_hwnd = hWnd;
    hr = DirectInputCreateEx((HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE), DIRECTINPUT_VERSION,
                             IID_IDirectInput7, (void**)&m_di, NULL);
    if (FAILED(hr))
        return FALSE;
    // The result is not stored, so this tests DirectInputCreateEx's again.
    m_di->CreateDeviceEx(GUID_SysKeyboard, IID_IDirectInputDevice7, (void**)&m_keyboard, NULL);
    if (FAILED(hr)) {
        Fail();
        return FALSE;
    }
    hr = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(hr)) {
        Fail();
        return FALSE;
    }
    hr = m_keyboard->SetCooperativeLevel(m_hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY);
    if (FAILED(hr)) {
        Fail();
        return FALSE;
    }
    hr = m_keyboard->Acquire();
    if (FAILED(hr)) {
        Fail();
        return FALSE;
    }
    g_enumInput = this;
    hr = m_di->EnumDevices(DIDEVTYPE_JOYSTICK, EnumJoysticks, m_di, DIEDFL_ATTACHEDONLY);
    if (FAILED(hr)) {
        Fail();
        return FALSE;
    }
    return TRUE;
}

void CInput::Shutdown()
{
    int i;

    if (m_di) {
        if (m_keyboard) {
            m_keyboard->Unacquire();
            m_keyboard->Release();
            m_keyboard = NULL;
        }
        for (i = 0; i < 2; i++) {
            if (m_joysticks[i]) {
                m_joysticks[i]->Unacquire();
                m_joysticks[i]->Release();
                m_joysticks[i] = NULL;
            }
        }
        m_di->Release();
        m_di = NULL;
    }
}

CInput::~CInput()
{
    int i;

    if (m_di) {
        if (m_keyboard) {
            m_keyboard->Unacquire();
            m_keyboard->Release();
            m_keyboard = NULL;
        }
        for (i = 0; i < 2; i++) {
            if (m_joysticks[i]) {
                m_joysticks[i]->Unacquire();
                m_joysticks[i]->Release();
                m_joysticks[i] = NULL;
            }
        }
        m_di->Release();
        m_di = NULL;
    }
}

void CInput::Fail()
{
    MessageBox(NULL, "DirectInputの初期化に失敗", "ERROR", MB_OK);
    PostMessage(m_hwnd, WM_CLOSE, 0, 0);
}

// FUNCTION: 0x40cae0
// Opens each attached joystick, up to two, with a range of -1000 to 1000 on both axes.
BOOL CALLBACK EnumJoysticks(LPCDIDEVICEINSTANCE instance, LPVOID context)
{
    HRESULT hr;
    DIPROPRANGE range;

    hr = g_enumInput->m_di->CreateDeviceEx(instance->guidInstance, IID_IDirectInputDevice7,
                                           (void**)&g_enumInput->m_joysticks[g_joystickCount],
                                           NULL);
    if (FAILED(hr))
        return DIENUM_CONTINUE;
    hr = g_enumInput->m_joysticks[g_joystickCount]->SetDataFormat(&c_dfDIJoystick);
    if (FAILED(hr))
        return DIENUM_CONTINUE;
    hr = g_enumInput->m_joysticks[g_joystickCount]->SetCooperativeLevel(
        g_enumInput->m_hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY);
    if (FAILED(hr))
        return DIENUM_CONTINUE;
    range.diph.dwSize = sizeof(DIPROPRANGE);
    range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    range.diph.dwObj = DIJOFS_X;
    range.diph.dwHow = DIPH_BYOFFSET;
    range.lMin = -1000;
    range.lMax = 1000;
    hr = g_enumInput->m_joysticks[g_joystickCount]->SetProperty(DIPROP_RANGE, &range.diph);
    if (FAILED(hr))
        return DIENUM_CONTINUE;
    range.diph.dwObj = DIJOFS_Y;
    hr = g_enumInput->m_joysticks[g_joystickCount]->SetProperty(DIPROP_RANGE, &range.diph);
    if (FAILED(hr))
        return DIENUM_CONTINUE;
    hr = g_enumInput->m_joysticks[g_joystickCount]->Acquire();
    if (FAILED(hr))
        return DIENUM_CONTINUE;
    g_joystickCount++;
    if (g_joystickCount < 2)
        return DIENUM_CONTINUE;
    return DIENUM_STOP;
}

BYTE CInput::GetInput(BYTE player)
{
    BYTE result;
    HRESULT hr;
    WORD type;
    BYTE dik;
    short* binding;
    int i;

    if (player > 1)
        return 0;
#ifdef EFZ_TRACE
    if (TraceInput(player, &result))
        return result;
#endif
    result = 0;
    binding = m_bindings[player];
    if (m_keyboard) {
        hr = m_keyboard->GetDeviceState(sizeof(m_keyState), m_keyState);
        if (FAILED(hr) && hr == DIERR_INPUTLOST)
            m_keyboard->Acquire();
    }
    if (m_joysticks[0]) {
        hr = m_joysticks[0]->Poll();
        if (SUCCEEDED(hr)) {
            hr = m_joysticks[0]->GetDeviceState(sizeof(DIJOYSTATE), &m_joyState[0]);
            if (FAILED(hr) && hr == DIERR_INPUTLOST)
                m_joysticks[0]->Acquire();
        }
    }
    if (m_joysticks[1]) {
        hr = m_joysticks[1]->Poll();
        if (SUCCEEDED(hr)) {
            hr = m_joysticks[1]->GetDeviceState(sizeof(DIJOYSTATE), &m_joyState[1]);
            if (FAILED(hr) && hr == DIERR_INPUTLOST)
                m_joysticks[1]->Acquire();
        }
    }
    for (i = 0; i < 8; i++) {
        dik = *binding & 0xff;
        type = *binding & 0xf00;
        switch (type) {
        case 0:
            if (m_keyboard && (m_keyState[dik] & 0x80))
                result |= 1 << i;
            break;
        case 0x100:
            if (m_joysticks[0]) {
                if (m_joyState[0].lX < -500 && dik == 0x12) {
                    result |= 1 << i;
                    break;
                }
                if (m_joyState[0].lX > 500 && dik == 0x13) {
                    result |= 1 << i;
                    break;
                }
                if (m_joyState[0].lY < -500 && dik == 0x10) {
                    result |= 1 << i;
                    break;
                }
                if (m_joyState[0].lY > 500 && dik == 0x11) {
                    result |= 1 << i;
                    break;
                }
                if ((m_joyState[0].rgbButtons[dik] & 0x80) && dik < 0x10) {
                    result |= 1 << i;
                    break;
                }
            }
            break;
        case 0x200:
            if (m_joysticks[1]) {
                if (m_joyState[1].lX < -500 && dik == 0x12) {
                    result |= 1 << i;
                    break;
                }
                if (m_joyState[1].lX > 500 && dik == 0x13) {
                    result |= 1 << i;
                    break;
                }
                if (m_joyState[1].lY < -500 && dik == 0x10) {
                    result |= 1 << i;
                    break;
                }
                if (m_joyState[1].lY > 500 && dik == 0x11) {
                    result |= 1 << i;
                    break;
                }
                if ((m_joyState[1].rgbButtons[dik] & 0x80) && dik < 0x10) {
                    result |= 1 << i;
                    break;
                }
            }
            break;
        }
        binding++;
    }
    return result;
}

// key.ini stores each binding as two bytes, device then code, in the order up, down,
// left, right, then the buttons. A stored device byte of n > 0 gives the binding
// (n << 8) + code - 1.

void CInput::LoadBindings()
{
    int j;
    BYTE* data;
    DWORD dwRead;
    DWORD size;
    HANDLE hFile = NULL;

    hFile = CreateFile("key.ini", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE && GetFileSize(hFile, NULL) >= 0x20) {
        size = GetFileSize(hFile, NULL);
        data = new BYTE[size];
        ReadFile(hFile, data, size, &dwRead, NULL);
        for (j = 0; j < 2; j++) {
            m_bindings[j][3] = data[j * 16 + 1] + (data[j * 16] << 8) - (data[j * 16] > 0);
            m_bindings[j][2] = data[j * 16 + 3] + (data[j * 16 + 2] << 8) - (data[j * 16 + 2] > 0);
            m_bindings[j][1] = data[j * 16 + 5] + (data[j * 16 + 4] << 8) - (data[j * 16 + 4] > 0);
            m_bindings[j][0] = data[j * 16 + 7] + (data[j * 16 + 6] << 8) - (data[j * 16 + 6] > 0);
            m_bindings[j][4] = data[j * 16 + 9] + (data[j * 16 + 8] << 8) - (data[j * 16 + 8] > 0);
            m_bindings[j][5] = data[j * 16 + 11] + (data[j * 16 + 10] << 8) - (data[j * 16 + 10] > 0);
            m_bindings[j][6] = data[j * 16 + 13] + (data[j * 16 + 12] << 8) - (data[j * 16 + 12] > 0);
            m_bindings[j][7] = data[j * 16 + 15] + (data[j * 16 + 14] << 8) - (data[j * 16 + 14] > 0);
        }
        delete data;
    }
    CloseHandle(hFile);
}

void CInput::LoadPreset(int set)
{
    int j;
    BYTE* data;
    DWORD dwRead;
    DWORD size;
    HANDLE hFile = NULL;

    hFile = CreateFile("key.ini", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE && GetFileSize(hFile, NULL) >= 0x20) {
        size = GetFileSize(hFile, NULL);
        data = new BYTE[size];
        ReadFile(hFile, data, size, &dwRead, NULL);
        for (j = 0; j < 2; j++) {
            m_bindings[j][3] = data[set * 39 + j * 16 + 1] + (data[set * 39 + j * 16] << 8) -
                                  (data[set * 39 + j * 16] > 0);
            m_bindings[j][2] = data[set * 39 + j * 16 + 3] + (data[set * 39 + j * 16 + 2] << 8) -
                                  (data[set * 39 + j * 16 + 2] > 0);
            m_bindings[j][1] = data[set * 39 + j * 16 + 5] + (data[set * 39 + j * 16 + 4] << 8) -
                                  (data[set * 39 + j * 16 + 4] > 0);
            m_bindings[j][0] = data[set * 39 + j * 16 + 7] + (data[set * 39 + j * 16 + 6] << 8) -
                                  (data[set * 39 + j * 16 + 6] > 0);
            m_bindings[j][4] = data[set * 39 + j * 16 + 9] + (data[set * 39 + j * 16 + 8] << 8) -
                                  (data[set * 39 + j * 16 + 8] > 0);
            m_bindings[j][5] = data[set * 39 + j * 16 + 11] + (data[set * 39 + j * 16 + 10] << 8) -
                                  (data[set * 39 + j * 16 + 10] > 0);
            m_bindings[j][6] = data[set * 39 + j * 16 + 13] + (data[set * 39 + j * 16 + 12] << 8) -
                                  (data[set * 39 + j * 16 + 12] > 0);
            m_bindings[j][7] = data[set * 39 + j * 16 + 15] + (data[set * 39 + j * 16 + 14] << 8) -
                                  (data[set * 39 + j * 16 + 14] > 0);
        }
        delete data;
    }
    CloseHandle(hFile);
}
