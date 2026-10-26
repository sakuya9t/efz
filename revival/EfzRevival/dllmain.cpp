// The Visual Studio template's DllMain: EfzRevival.dll does its work in init(), which
// the launcher calls in the game's process after injecting the DLL.
#include <windows.h>

// FUNCTION: 0x1006abc0
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
