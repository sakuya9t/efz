// The program's entry point. SDL_main.h makes main into what the platform calls (WinMain
// on Windows) and declares Windows types of its own, so it stays out of the files that
// include efz.h.
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int EfzMain(int argc, char** argv);

int main(int argc, char** argv)
{
    return EfzMain(argc, argv);
}
