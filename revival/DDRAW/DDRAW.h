// The Visual Studio DLL template's header: its sample class, which the developer kept.
#pragma once

#ifdef DDRAW_EXPORTS
#define DDRAW_API __declspec(dllexport)
#else
#define DDRAW_API __declspec(dllimport)
#endif

class DDRAW_API CDDRAW {
public:
    CDDRAW(void);
};
