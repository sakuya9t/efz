// The replay tool's entry point (efz-convert): the game started in its tool mode
// (port/tool.cpp), a small window to convert records and replays and to make videos of
// fights. As sdlmain.cpp, SDL_main.h stays out of the files that include efz.h.
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>

int EfzMain(int argc, char** argv);

int main(int argc, char** argv)
{
    std::vector<char*> args(argv, argv + argc);
    static char tool[] = "--tool";
    args.insert(args.begin() + (argc > 0 ? 1 : 0), tool);
    args.push_back(nullptr);
    return EfzMain((int)args.size() - 1, args.data());
}
