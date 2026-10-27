// The game state (EfzGame.cpp, 0x1006abd0-0x1006d5b0): one object, g_game (0x100a0780,
// defined in EfzRevival.cpp), through which the DLL reads and drives efz.exe: its scenes
// and players, input devices, sounds, the extended replay, the text overlay and the
// hit/hurt/collision box display (drawn with DDRAW.dll's EfzRender).
//
// Link-time code generation sees that most members are only ever called on g_game and
// builds the object's address into them: their callers don't load ecx, and they read
// the fields at fixed addresses. The members whose callers pass ecx are those it did
// not specialise.
#pragma once
// The launcher's version, first: every object that includes this header has its own
// copy of the suffix (REVIVAL_SUFFIX, L"h!!!"), constructed before its other statics
// (fifteen of them in the original's static initializers).
#include "../EfzRevivalLauncher/Version.h"
#include "Efz.h"
#include "Hook.h"
#include "../EfzRevivalLauncher/SharedData.h"
#include <iosfwd>
#include <list>
#include <string>
#include <vector>

class EfzRender;
struct EfzTimer;

// DDRAW.dll's other exports (DDRAW.def)
extern "C" __declspec(dllimport) EfzTimer *getEfzTimer();
extern "C" __declspec(dllimport) char getEfzInput(bool player2);

// The kinds of box (Game::showBoxes)
enum BoxKind {
    BOX_HIT,                    // red, the frame's hitBoxes
    BOX_HURT,                   // blue, its hurtBoxes
    BOX_COLLISION,              // yellow, the collision box and the crossup midline
};

// A player's boxes to draw each frame.
struct BoxRequest {
    // FUNCTION: 0x1000dab0
    BoxRequest(int player_, int kind_)
    {
        kind = kind_;
        player = player_;
    }

    int player;
    int kind;
};

// A box kept from frame to frame: Mishio's (character 15) 0x199 objects leave their
// hitboxes on screen. 0x20 bytes.
struct HitRect {
    // FUNCTION: 0x1000da70
    HitRect(RECT rect_, DWORD color_, unsigned int flags_, int object_, int box_)
        : rect(rect_), color(color_), flags(flags_), object(object_), box(box_)
    {
    }

    RECT rect;                  // 0x00 in the overlay's coordinates, before the camera
    DWORD color;                // 0x10
    unsigned int flags;         // 0x14 EfzRender's stipple pattern
    int object;                 // 0x18 the object's slot
    int box;                    // 0x1c which of its boxes
};

// Where a recording is saved: a wstring in a struct of its own. Game's constructor and
// destructor call the struct's (implicit) ones, which the link folds with
// boost::filesystem::path's (a wstring is all either holds, at its start); everything
// else uses the wstring itself.
struct ReplayTarget {
    std::wstring name;
};

class Game {
public:
    Game();
    ~Game();
    // Once, from the first frame: the ini's options, DDRAW.dll's renderer and timer.
    void init();

    // --- Scenes and players
    int sceneId();
    CScene *scene(int index);
    CScene *currentScene();
    // Runs one update of the current scene (WinMain's loop body).
    void runFrame();
    CGame *getGame();
    CPlayer *player(int index);
    char menuChoice();
    int humanPlayer();
    int roundWinner();
    int character(int player);
    std::string characterName(int character);
    std::wstring characterNameW(int character);
    bool isRoundOver();
    bool isMatchOver();
    int playerAction(int player);
    short actionFrame(int player);
    int playerFlagAc(int player);
    bool isRecoilGuarding(int player);
    bool isGuarding(int player);
    bool isWakingUp(int player);
    bool isTeching(int player);
    bool isHit(CPlayer *player);
    void setGameSpeed(char speed);
    void setRendering(bool enable);
    void setNetplay(bool netplay);
    void setSpectating();
    void setGameFlag1366(bool value);

    // --- Palettes
    bool canChoosePalette(int player);
    bool hasPalette(int player);
    int paletteNumber(int player);
    void setPalette(int player, const ColorPalette &palette);
    void refreshPalette(int player);

    // --- Input
    HWND window();
    bool keyIniChanged();
    void reloadKeys();
    void reacquireJoysticks();
    bool joystickAdded();
    bool pollDevices(int player);
    IDirectInputDevice7 *device(char index);
    KeyBindings *bindings();
    void swapBindings();
    char cleanInput(char input);
    char efzInput(int player);
    void readKeyboard(BYTE *keys);
    BYTE functionKeys();

    // --- Sound
    WORD musicId();
    bool isMusic(WORD id);
    void setSoundVolume(WORD id, int volume);
    int stopSound(WORD id);
    int playSound(WORD id, int loop);

    // --- Random numbers (g_rng)
    void setRandomState(unsigned int state);
    void loadRandomState(int state);
    int newRandomSeed();

    // --- Replays (EfzReplay.cpp's ReplayFile replaces CReplayFile's methods)
    CReplayFile *replayFile();
    char replayMode();
    void setReplayMode(char mode);
    void setReplayName(const std::wstring &name);
    void setRandomSeed(int seed);
    void setSaveReplays(bool save);
    void setWriteReplay(bool write);
    void setReadReplay(bool read);
    void recordInputs(FrameInput p1, FrameInput p2);
    std::iostream *openReplayRead(const char *name);
    std::iostream *openReplayWrite(const char *name);
    short readInput(std::iostream *file);
    int writeInput(std::iostream *file, short input);
    void closeReplay(std::iostream *&file);
    void closeStream(std::iostream *&stream);
    bool flushReplay();
    void writeExtendedReplay(std::iostream *file);
    bool isExtendedReplay(std::iostream *file);
    int readExtendedOffset(std::iostream *file);
    void readExtendedReplay(std::vector<FrameInput> &inputs);

    // --- Text overlay
    void setTextRender(bool enable);
    void clearText();
    void addText(std::wstring text, int x, int y, DWORD color);

    // --- Boxes
    void showBoxes(int player, int kind);
    void clearBoxes();
    void clearRects();
    void updateRects();
    void drawBoxes();
    void getCollisionInfo(int player, CollisionInfo *info);
    void getPatternFrame(int player, short pattern, short frame, PatternFrame *out);
    POINT getCamera();
    void toScreen(RECT *rect);
    void drawBoxRequest(BoxRequest *request);
    void collectRects(BoxRequest *request, std::vector<HitRect> &rects);

    int unknown0;                           // 0x00
    EfzTimer *timer;                        // 0x04 DDRAW.dll's frame timer
private:
    friend class SaveState;

    std::vector<HitRect> rects_;            // 0x08
    bool initialized_;                      // 0x14
    bool rendering_;                        // 0x15 false: the game's drawing is patched out
    bool unknown16_;                        // 0x16
    EfzRender *render_;                     // 0x18
    std::vector<FrameInput> inputs_;        // 0x1c the extended replay's inputs
    std::iostream *pendingReplay_;          // 0x28 a recording not yet written out
    int joystickCount_;                     // 0x2c
    FILETIME keyIniTime_;                   // 0x30
    ReplayTarget replay_;                   // 0x38 where a recording is saved
    bool saveReplays_;                      // 0x50 SaveAllReplays
    bool writeReplay_;                      // 0x51 write inputs to the replay
    bool readReplay_;                       // 0x52 read inputs from it
    int rngSeed_;                           // 0x54 the replay's random state
    void *graphics_;                        // 0x58 efz.exe's g_graphics, g_inputDev,
    CInput *input_;                         // 0x5c   g_sound and g_game
    CSound *sound_;                         // 0x60
    CGame *game_;                           // 0x64
    bool muteBGM_;                          // 0x68 MuteBGM
    bool recording_;                        // 0x69 the replay open is being recorded
    std::list<BoxRequest> boxes_;           // 0x6c
    Detours patches_;                       // 0x74
};

// EfzRevival.cpp
extern Game g_game;
