// The settings' keys (keys.h).
#include "keys.h"

#include <string.h>

#include "config.h"
#include "../platform.h"

namespace efz {
namespace revival {

namespace {

bool g_down[0x100], g_pressed[0x100];
bool g_buttonDown[32], g_buttonPressed[32];

} // namespace

void UpdateKeys()
{
    const unsigned char* keys = KeyboardState();
    for (int i = 0; i < 0x100; i++) {
        bool down = (keys[i] & 0x80) != 0;
        g_pressed[i] = down && !g_down[i];
        g_down[i] = down;
    }
    unsigned char buttons[32];
    bool have = RevivalPadButtons(buttons);
    for (int i = 0; i < 32; i++) {
        bool down = have && (buttons[i] & 0x80) != 0;
        g_buttonPressed[i] = down && !g_buttonDown[i];
        g_buttonDown[i] = down;
    }
}

bool Pressed(int key)
{
    if (key >= 0 && key < 0x100)
        return g_pressed[key];
    if (key > kButton && key <= kButton + 32)
        return g_buttonPressed[key - kButton - 1];
    return false;
}

bool Held(int key)
{
    if (key >= 0 && key < 0x100)
        return g_down[key];
    if (key > kButton && key <= kButton + 32)
        return g_buttonDown[key - kButton - 1];
    return false;
}

int PressedKeys(int* out, int max)
{
    int n = 0;
    for (int i = 0; i < 0x100 && n < max; i++)
        if (g_pressed[i])
            out[n++] = i;
    for (int i = 0; i < 32 && n < max; i++)
        if (g_buttonPressed[i])
            out[n++] = kButton + 1 + i;
    return n;
}

} // namespace revival
} // namespace efz
